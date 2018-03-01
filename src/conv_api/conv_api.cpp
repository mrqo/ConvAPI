// conv_api.cpp : Defines the entry point for the console application.
//

#include "conv_api\conv_api_pch.h"
#include <cstdio>
#include <cstdlib>
#include <filesystem>

#include "formats\rw\rwcore.h"
#include "formats\xml\node.h"

#include "converters\DffToXml.h"

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

int main()
{
	// Vice City DFF test
	//ConvertDffToXml("assets\\dff\\vc\\dt_bowlsign.dff", "assets\\xml\\vc\\dt_bowlsign.xml");
	ConvertDffToXml("assets\\dff\\vc\\sabre.dff", "assets\\xml\\vc\\sabre.xml");

	// San Andreas DFF test
	ConvertDffToXml("assets\\dff\\sa\\sv_ground_04_sfs.dff", "assets\\xml\\sa\\sv_ground_04_sfs.xml");
	system("PAUSE");
    return 0;
}

