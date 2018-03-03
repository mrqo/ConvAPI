// conv_api.cpp : Defines the entry point for the console application.
//

#include "conv_api\conv_api_pch.h"
#include <cstdio>
#include <cstdlib>
#include <filesystem>

#include "formats\rw\rwcore.h"
#include "formats\xml\node.h"

#include "converters\DffToXml.h"
#include "converters\FbxToDff.h"

namespace fs = std::experimental::filesystem;

void ConvertDffToXml(const char* in_path, const char* out_path)
{
	fs::path dff_path(in_path);
	fs::path xml_path(out_path);

	printf("Converting %s to %s... ", 
		dff_path.filename().string().c_str(), 
		xml_path.filename().string().c_str()
	);

	in_stream<EStreamType::BINARY> dff_stream;

	if (dff_stream.Open(in_path))
	{
		auto chunk_a = new rw::core::clump();
		chunk_a->Read(dff_stream);
		dff_stream.Close();

		auto node = CConverter::From<rw::core::clump*, xml::node*>(chunk_a);

		out_stream<EStreamType::TEXT> xml_stream;
		xml_stream.Open(out_path);
		node->Write(xml_stream);
		xml_stream.Close();
		
		printf("OK\n");
	}	
	else
	{
		printf("FAIL\n");
	}
}

void TestWriteEmptyDff(const char* out_path)
{
	out_stream<EStreamType::BINARY> dff_stream;

	printf("Saving empty model to %s... ", out_path);
	if (dff_stream.Open(out_path))
	{
		auto chunk = new rw::core::clump();
		chunk->Write(dff_stream);
		dff_stream.Close();

		printf("OK\n");
	}
	else 
	{
		printf("FAIL\n");
	}
}

void TestReadAndSaveDff(const char* in_path, const char* out_path)
{
	fs::path dff_path(in_path);
	fs::path xml_path(out_path);

	printf("Converting %s to %s... ",
		dff_path.filename().string().c_str(),
		xml_path.filename().string().c_str()
	);

	in_stream<EStreamType::BINARY> in_dff_stream;

	if (in_dff_stream.Open(in_path))
	{
		auto chunk_a = new rw::core::clump();
		chunk_a->Read(in_dff_stream);
		in_dff_stream.Close();

		out_stream<EStreamType::BINARY> out_dff_stream;
		out_dff_stream.Open(out_path);
		chunk_a->Write(out_dff_stream);
		out_dff_stream.Close();

		printf("OK\n");
	}
	else
	{
		printf("FAIL\n");
	}
}

int main()
{
	// Vice City DFF test
	//ConvertDffToXml("assets\\dff\\vc\\dt_bowlsign.dff", "assets\\xml\\vc\\dt_bowlsign.xml");
	ConvertDffToXml("assets\\dff\\vc\\sabre.dff", "assets\\xml\\vc\\sabre.xml");

	// San Andreas DFF test
	ConvertDffToXml("assets\\dff\\sa\\sv_ground_04_sfs.dff", "assets\\xml\\sa\\sv_ground_04_sfs.xml");
	
	// Test saving empty dff
	TestWriteEmptyDff("assets\\dff\\sa\\empty.dff");

	// Test resave dff
	TestReadAndSaveDff("assets\\dff\\vc\\sabre.dff", "assets\\dff\\vc\\sabre_resaved.dff");
	system("PAUSE");
    return 0;
}

