#pragma once
#include "../formats_pch.h"

#include <string>
#include <vector>

// #TODO: Fix premake.lua to make utilities as includelib
// -- idk why it is not working now
#include "../../utilities/stream.h"
#include "../../utilities/interfaces.h"

#define RWFORCEENUMSIZEINT ((int)((~((unsigned int)0))>>1))
#define MAKECHUNKID(vendorID, chunkID) (((vendorID & 0xFFFFFF) << 8) | (chunkID & 0xFF))

namespace rw
{
	enum RwPluginVendor
	{
		rwVENDORID_CORE = 0x000000L,
		rwVENDORID_CRITERIONTK = 0x000001L,
		rwVENDORID_REDLINERACER = 0x000002L,
		rwVENDORID_CSLRD = 0x000003L,
		rwVENDORID_CRITERIONINT = 0x000004L,
		rwVENDORID_CRITERIONWORLD = 0x000005L,
		rwVENDORID_BETA = 0x000006L,
		rwVENDORID_CRITERIONRM = 0x000007L,
		rwVENDORID_CRITERIONRWA = 0x000008L,
		rwVENDORID_CRITERIONRWP = 0x000009L,
		rwPLUGINVENDORFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
	};

	enum RwCorePluginID
	{
		rwID_NAOBJECT = MAKECHUNKID(rwVENDORID_CORE, 0x00),
		rwID_STRUCT = MAKECHUNKID(rwVENDORID_CORE, 0x01),
		rwID_STRING = MAKECHUNKID(rwVENDORID_CORE, 0x02),
		rwID_EXTENSION = MAKECHUNKID(rwVENDORID_CORE, 0x03),
		rwID_CAMERA = MAKECHUNKID(rwVENDORID_CORE, 0x05),
		rwID_TEXTURE = MAKECHUNKID(rwVENDORID_CORE, 0x06),
		rwID_MATERIAL = MAKECHUNKID(rwVENDORID_CORE, 0x07),
		rwID_MATLIST = MAKECHUNKID(rwVENDORID_CORE, 0x08),
		rwID_ATOMICSECT = MAKECHUNKID(rwVENDORID_CORE, 0x09),
		rwID_PLANESECT = MAKECHUNKID(rwVENDORID_CORE, 0x0A),
		rwID_WORLD = MAKECHUNKID(rwVENDORID_CORE, 0x0B),
		rwID_SPLINE = MAKECHUNKID(rwVENDORID_CORE, 0x0C),
		rwID_MATRIX = MAKECHUNKID(rwVENDORID_CORE, 0x0D),
		rwID_FRAMELIST = MAKECHUNKID(rwVENDORID_CORE, 0x0E),
		rwID_GEOMETRY = MAKECHUNKID(rwVENDORID_CORE, 0x0F),
		rwID_CLUMP = MAKECHUNKID(rwVENDORID_CORE, 0x10),
		rwID_LIGHT = MAKECHUNKID(rwVENDORID_CORE, 0x12),
		rwID_UNICODESTRING = MAKECHUNKID(rwVENDORID_CORE, 0x13),
		rwID_ATOMIC = MAKECHUNKID(rwVENDORID_CORE, 0x14),
		rwID_TEXTURENATIVE = MAKECHUNKID(rwVENDORID_CORE, 0x15),
		rwID_TEXDICTIONARY = MAKECHUNKID(rwVENDORID_CORE, 0x16),
		rwID_ANIMDATABASE = MAKECHUNKID(rwVENDORID_CORE, 0x17),
		rwID_IMAGE = MAKECHUNKID(rwVENDORID_CORE, 0x18),
		rwID_SKINANIMATION = MAKECHUNKID(rwVENDORID_CORE, 0x19),
		rwID_GEOMETRYLIST = MAKECHUNKID(rwVENDORID_CORE, 0x1A),
		rwID_ANIMANIMATION = MAKECHUNKID(rwVENDORID_CORE, 0x1B),
		rwID_HANIMANIMATION = MAKECHUNKID(rwVENDORID_CORE, 0x1B),
		rwID_TEAM = MAKECHUNKID(rwVENDORID_CORE, 0x1C),
		rwID_CROWD = MAKECHUNKID(rwVENDORID_CORE, 0x1D),
		rwID_DMORPHANIMATION = MAKECHUNKID(rwVENDORID_CORE, 0x1E),
		rwID_RIGHTTORENDER = MAKECHUNKID(rwVENDORID_CORE, 0x1f),
		rwID_MTEFFECTNATIVE = MAKECHUNKID(rwVENDORID_CORE, 0x20),
		rwID_MTEFFECTDICT = MAKECHUNKID(rwVENDORID_CORE, 0x21),
		rwID_TEAMDICTIONARY = MAKECHUNKID(rwVENDORID_CORE, 0x22),
		rwID_PITEXDICTIONARY = MAKECHUNKID(rwVENDORID_CORE, 0x23),
		rwID_TOC = MAKECHUNKID(rwVENDORID_CORE, 0x24),
		rwID_PRTSTDGLOBALDATA = MAKECHUNKID(rwVENDORID_CORE, 0x25),
		rwID_ALTPIPE = MAKECHUNKID(rwVENDORID_CORE, 0x26),
		rwID_PIPEDS = MAKECHUNKID(rwVENDORID_CORE, 0x27),
		rwID_PATCHMESH = MAKECHUNKID(rwVENDORID_CORE, 0x28),
		rwID_CHUNKGROUPSTART = MAKECHUNKID(rwVENDORID_CORE, 0x29),
		rwID_CHUNKGROUPEND = MAKECHUNKID(rwVENDORID_CORE, 0x2A),
		rwID_UVANIMDICT = MAKECHUNKID(rwVENDORID_CORE, 0x2B),
		rwID_COLLTREE = MAKECHUNKID(rwVENDORID_CORE, 0x2C),
		rwID_ENVIRONMENT = MAKECHUNKID(rwVENDORID_CORE, 0x2D),
		rwID_COREPLUGINIDMAX = MAKECHUNKID(rwVENDORID_CORE, 0x2E),


		rwID_MORPHPLG = 0x105,
		rwID_BINMESHPLG = 0x050E,
		rwID_SKYMIPMAPVALPLG = 0x0110,
		rwID_HANIMPLG = 0x011E,
		rwID_FRAMEPLG = 0x0253F2FE,

		rwCOREPLUGINIDFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
	};

	enum RpGeometryFlag
	{
		rpGEOMETRYTRISTRIP = 0x00000001,
		rpGEOMETRYPOSITIONS = 0x00000002,
		rpGEOMETRYTEXTURED = 0x00000004,
		rpGEOMETRYPRELIT = 0x00000008,
		rpGEOMETRYNORMALS = 0x00000010,
		rpGEOMETRYLIGHT = 0x00000020,
		rpGEOMETRYMODULATEMATERIALCOLOR = 0x00000040,
		rpGEOMETRYTEXTURED2 = 0x00000080,
		rpGEOMETRYNATIVE = 0x01000000,
		rpGEOMETRYNATIVEINSTANCE = 0x02000000,
		rpGEOMETRYFLAGSMASK = 0x000000FF,
		rpGEOMETRYNATIVEFLAGSMASK = 0x0F000000,
	};

	std::string Decode(const RpGeometryFlag& flag);
	std::string Decode(const RwCorePluginID& flag);
	std::string Decode(const RwPluginVendor& flag);

	class chunk_base : public common::IBinReadable
	{
		CONVERTIBLE_ENTITY
	protected:
		uint32_t type;
		uint32_t size;
		uint32_t version;

	public:
		uint32_t DecodeVersion() const;
		bool Read(in_stream<EStreamType::BINARY>& stream) override;
	};

	class string : public chunk_base, public std::vector<uint8_t>
	{
		CONVERTIBLE_ENTITY
	public:
		bool Read(in_stream<EStreamType::BINARY>& stream) override;
	};

}