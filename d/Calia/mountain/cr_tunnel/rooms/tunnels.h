/*  Amelia --Tunnels defs.h  */

#include "/d/Calia/domain.h"
#include CALIAN_GUILD_BASE_DEF

#define ETO environment(this_object())
#define PRESTIGE (query_alignment() > 0 ? -1 : -1 * query_average_stat() * \
	query_average_stat() / 30 * query_alignment() / 300)
#define INTRO MISC + "intro.c"
#define HAUNT DOMAIN_DIR + "gelan/specials/haunt_code.h"
#define CD COMMAND_DRIVER->

#define MOUNTAIN	"/d/Calia/mountain/"
#define TUNNELS		MOUNTAIN + "cr_tunnel/"
#define TUNNELS_ROOMS   TUNNELS + "rooms/"
#define TUNNELS_OBJS	MOUNTAIN + "obj/"
#define TUNNELS_ARMS	TUNNELS_OBJS + "armours/"
#define TUNNELS_WEAP	TUNNELS_OBJS + "weapons/"
#define TUNNELS_NPCS	MOUNTAIN + "monsters/"
#define TUNNELS_SPEC    MOUNTAIN + "special/"

#define OPEN_DOOR ({"open", "open the door", "open door"})
#define EAST_EXIT	MOUNTAIN + "croad/croad24.c"
#define WEST_EXIT	MOUNTAIN + "road/road19.c"
#define TRAINROOM	(CRPALACE_LIGHT_ROOMS + "trainroom.c")
#define VERY_SLIP TUNNELS_SPEC + "very_slip.c"
#define SLIP      TUNNELS_SPEC + "tunnel_slip.c"
#define ROOM_TELL TUNNELS_SPEC + "room_tell.c"
