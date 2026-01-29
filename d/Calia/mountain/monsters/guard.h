
#include "/d/Calia/domain.h"
#include CALIAN_GUILD_BASE_DEF

#define CALIAN_GUARD (CRPALACE_MONSTERS + "calian")
#define ETO environment(this_object())
#define PRESTIGE (query_alignment() > 0 ? -1 : -1 * query_average_stat() * \
	query_average_stat() / 30 * query_alignment() / 300)
#define INTRO MISC + "intro.c"
#define HAUNT DOMAIN_DIR + "gelan/specials/haunt_code.h"
#define CD COMMAND_DRIVER->

#define MOUNTAIN	"/d/Calia/mountain/"
#define TUNNELS_OBJS    "/d/Calia/mountain/obj/"
#define TUNNELS_ARMS    TUNNELS_OBJS + "armours/"
#define TUNNELS_WEAP    TUNNELS_OBJS + "weapons/"
#define TUNNELS_NPCS    MOUNTAIN + "monsters/"

#define OPEN_DOOR ({"open", "open the door", "to open the door", \
   "open door", "out"})
#define EAST_EXIT	"/d/Calia/mountain/croad/croad24.c"
#define WEST_EXIT "/d/Calia/mountain/road/road19"
#define SOUTH_EXIT "/d/Calia/mountain/foothill/fh97"
#define QUESTIONS ({"who is outside", "outside", "who's outside"})
#define TRAINROOM "/d/Calia/palace/rooms/light/trainroom.c"
