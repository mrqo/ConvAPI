// conv_api.cpp : Defines the entry point for the console application.
//

#include "conv_api\conv_api_pch.h"
#include <cstdio>
#include <cstdlib>

#include "formats\rw\rwcore.h"
#include "formats\xml\node.h"

#include "converters\DffToXml.h"

void ReadVCDff(const char* fname)
{
	in_stream<EStreamType::BINARY> dff_stream;

	if (dff_stream.Open(fname))
	{
		rw::core::clump dff;
		dff.Read(dff_stream);
		dff_stream.Close();
		printf(" %s\n", dff.ToString().c_str());
	}
}

void ConvertDffToXml(const char* file_name, const char* out_file_name)
{
	printf("Converting %s to %s...\n", file_name, out_file_name);
	in_stream<EStreamType::BINARY> dff_stream;

	if (dff_stream.Open(file_name))
	{
		rw::core::clump chunk_a;
		chunk_a.Read(dff_stream);
		dff_stream.Close();

		xml::node node = CConverter::From<rw::core::clump, xml::node>(chunk_a);

		out_stream<EStreamType::TEXT> xml_stream;
		xml_stream.Open(out_file_name);
		node.Write(xml_stream);
		xml_stream.Close();

		printf("Conversion ended successfully.\n");
	}	
	else
	{
		printf("Failed to convert.\n");
	}
}

int main()
{
	ConvertDffToXml("assets\\dff\\vc\\dt_bowlsign.dff", "assets\\xml\\vc\\dt_bowlsign.xml");
	//ConvertDffToXml("assets\\dff\\sa\\sv_ground_04_sfs.dff", "assets\\xml\\sa\\sv_ground_04_sfs.xml");
	//ReadVCDff("assets\\dt_bowlsign.dff");
	system("PAUSE");
    return 0;
}

