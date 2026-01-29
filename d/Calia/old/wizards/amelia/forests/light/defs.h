#ifdef FPATH
#undef FPATH
#endif
#define FPATH "/d/Calia/amelia/forests/light/"
/* ~malcontent/shale/defs.h */

#include "/d/Calia/domain.h"

#define RANDOM_HEADER "/d/Calia/sys/random.h"
#define MAP_HEADER "/d/Calia/sys/map.h"

#define SHALE DOMAIN_DIR + "malcontent/shale/"
#define WEAPONS SHALE + "weapons/"
#define ARMOURS SHALE + "armours/"
#define CLOTHES ARMOURS + "clothes/"
#define FORESTS SHALE + "forests/"
#define LAKE SHALE + "lake/"
#define ROADS SHALE + "roads/"
#define ROADSF ROADS + "forest/"
#define ROADSS ROADS + "shore/"
#define ROADSE ROADS + "entrance/"
#define ROADSV ROADS + "village/"
#define OBJECTS SHALE + "objects/"
#define MISC SHALE + "misc/"
#define DOORS OBJECTS + "doors/"
#define MONSTERS SHALE + "monsters/"
#define TOBACCO SHALE + "tobacco/"
#define VILLAGE SHALE + "village/"
#define NWTERR DOMAIN_DIR + "zima/argos/nwterr/rooms/"

#define TP this_player()
#define TO this_object()
#define ETO environment(this_object())
#define PRESTIGE (query_alignment() > 0 ? -1 : -1 * query_average_stat() * \
	query_average_stat() / 30 * query_alignment() / 300)
#define GLYKRON_SPECIALS DOMAIN_DIR + "glykron/palace/specials/"
#define OBJECT(a) (GLYKRON_SPECIALS + "path")->object_path(a)
#define INTRO MISC + "intro.c"
#define HAUNT DOMAIN_DIR + "maniac/gelan/specials/haunt_code.h"
#define CD COMMAND_DRIVER->
#define CALIAN_HEADER "/d/Calia/glykron/palace/specials/calian.h"
#define COUNCIL_HEADER "/d/Calia/glykron/palace/specials/council.h"


