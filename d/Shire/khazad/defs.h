/*
 * Defines for Khazad-Dum
 * Finwe, January 2003
 */

/*****************************************************************/

#define KHAZAD_DIR          "/d/Shire/khazad/"
#define ROOM_DIR            (KHAZAD_DIR + "rooms/")
#define DEEP1_DIR           (ROOM_DIR + "deep1/")

#define NORTH(where)        add_exit(where,"north",0)
#define EAST(where)         add_exit(where,"east",0)
#define WEST(where)         add_exit(where,"west",0)
#define SOUTH(where)        add_exit(where,"south",0)
#define UP(where)           add_exit(where,"up",0)
#define DOWN(where)         add_exit(where,"down",0)
#define NORTHEAST(where)    add_exit(where,"northeast",0)
#define SOUTHEAST(where)    add_exit(where,"southeast",0)
#define NORTHWEST(where)    add_exit(where,"northwest",0)
#define SOUTHWEST(where)    add_exit(where,"southwest",0)

#define LIGHTS_OFF          add_prop(ROOM_I_LIGHT,0);
#define LIGHTS_ON           add_prop(ROOM_I_LIGHT,1);
#define ROOM_TELL_TIME      45+random(135)

#define BASE_COMMON         (KHAZAD_DIR + "base_common")
#define BASE_ROOM           (KHAZAD_DIR + "base_room")

#define TUN_DIR             (KHAZAD_DIR + "rooms/tunnels/")