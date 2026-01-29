/* Created by Mortis 07.21.05 */

#include "/d/Krynn/common/defs.h"

/* Pathname aliases */
#define PARENT1		"/d/Krynn/solamn/"
#define PARENT2		"/d/Krynn/solamn/"
#define TDIR		PARENT1 + "palanthas/"
#define LIV			TDIR + "living/"
#define OBJ			TDIR + "obj/"
#define ROOM		TDIR + "city/"
#define PALACE		TDIR + "palace/"
#define MONKS		TDIR + "aesthetics/"
#define MERCH		TDIR + "merchants/"
#define SEWER		TDIR + "sewers/"
#define NOBLE		TDIR + "nobles/"
#define SHIP		TDIR + "shipping/"
#define ROOF		TDIR + "roofs/"

#define PALANTHAS_BOARD	TDIR + "log/board/"

#define CITY_BASE		ROOM + "city_base"
#define CITY_ROOMBASE	ROOM + "city_roombase"
#define NOBLE_BASE		NOBLE + "noble_base"
#define NOBLE_ROOMBASE	NOBLE + "noble_roombase"
#define NOBLE_DOOR		NOBLE + "doors/"
#define MONKS_BASE		MONKS + "aesthetic_base"
#define MONKS_ROOMBASE	MONKS + "aesthetic_roombase"
#define MERCH_BASE		MERCH + "merchant_base"
#define MERCH_ROOMBASE	MERCH + "merchant_roombase"
#define SHIP_BASE		SHIP + "shipping_base"
#define SHIP_ROOMBASE	SHIP + "shipping_roombase"
#define SEWER_BASE		SEWER + "sewer_base"
#define ROOF_BASE		ROOF + "roof_base"
#define ROOF_ROOMBASE	ROOF + "roof_roombase"

/* Special Rooms */
#define LIBRARY_PUBLIC TDIR + "library/public"
#define CLUB_ENTRANCE  (CLUB_DIR + "pkc/club1")
#define PIER1          TDIR + "ship2/pier"
#define PIER2          TDIR + "ship/pier"
#define PIER3          TDIR + "ship3/pier"
#define PIER4          TDIR + "ship4/pier"
#define PIER5          TDIR + "ship5/pier"
#define PIER6          TDIR + "ship6/pier"

/* the outside room base file */
#define STREET_BASE    TDIR + "city_base";
/* the indoor room base file */
#define ROOM_BASE      TDIR + "room_base";

#define TSIT            "_sitting_at_table"
#define FSIT            "_sitting_at_fireplace"
#define BSIT            "_sitting_at_bar"

/*the npc base*/
#define CITIZEN                      LIV + "friendly_human"
#define LIVE_I_ATTACKED_PALANTHAS   "_live_i_attacked_palanthas"
#define HAS_NO_LEFT_LEG             "_has_no_left_leg"


/* Connections to the World:
Vingaard Mountains */
#define VINMOUNT       PARENT1 + "vin_mount/room/road2"
#define MOOR           PARENT1 + "moor/room/road1"
#define THIEF_ENTRANCE PARENT1 + "thief/cavern/pal7"

/* Code aid */

#define SHORT(x) set_short(x)
#define LONG(x) set_long(x)
#define EXIT(w,x,y,z) add_exit(w,x,y,z)
#define ITEM(x,y) add_item(x,y)
#define RITEM(x) remove_item(x)
#define CMD(x,y,z) add_cmd_item(x,y,z)
#define ACT(x,y) add_act(x,y)
#define RTELL(x) add_tell(x)