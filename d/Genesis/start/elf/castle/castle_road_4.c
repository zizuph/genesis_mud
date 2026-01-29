
#include "../stddefs.h"
#include "../desc_include/castle_road.h"

#pragma save_binary

inherit DIRROOM;
inherit ELFAREA;
inherit STRINGLIB;
inherit MISCLIB;

#define NORTH  CASTLEDIR + "castle_road_3"
#define SOUTH  CASTLEDIR + "castle_gate_1"


#define LEAVE_LONG \
  "  Behind you the castle is painted by a pale moonlight from "+\
  "the setting new moon. It shimmers ghostly white in the darkness, and the "+\
  "high, narrow windows in its high walls and towers are lighted with a "+\
  "warm, festive yellow glow from within.\n"

#define ENTER_LONG \
  "  The sun is gone now, and the castle is painted by a pale moonlight "+\
  "from the rising new moon. It shimmers ghostly white in the darkness, and "+\
  "the high, narrow windows in its high walls and towers are lighted with a "+\
  "warm, festive yellow glow from within.\n"

#define LONG \
  "  The castle is painted by a pale moonlight from "+\
  "the new moon. It shimmers ghostly white in the darkness, and the "+\
  "high, narrow windows in its high walls and towers are lighted with a "+\
  "warm, festive yellow glow from within.\n"


#define CASTLE_ITEM ({"castle", "palace", "tower", "towers"})
#define CASTLE_NDESC \
  "The towers of King Oberon's and Queen Titania's castle " + \
  "shimmers from the moonlight reflected and "+\
  "refracted by the thousands of " +\
  "jewels that has been set into the castle walls.\n" 
#define CASTLE_FDESC \
  "The towers of a castle shimmers in the moonlight, as if " +\
  "jewels had been set into its walls.\n"


create_room()
{
  set_short(N_KNOW(CASTLE_ROAD_NAT_SHORT, CASTLE_ROAD_FOR_SHORT));
  set_long(N_KNOW(WRAP(CASTLE_ROAD_NAT_LONG),
		  WRAP(CASTLE_ROAD_FOR_LONG)) + 
	   DPHRASE("long"));

  CASTLE_ROAD_STD_ITEMS;
  add_item(CASTLE_ITEM, N_KNOW(WRAP(CASTLE_NDESC),
			       WRAP(CASTLE_FDESC)));

  add_dir_phrase("long", NORTH, WRAP(ENTER_LONG));
  add_dir_phrase("long", SOUTH, WRAP(LEAVE_LONG));
  add_dir_phrase("long",     0, WRAP(      LONG));

  add_exit(SOUTH, "south", 0);
  add_exit(NORTH, "north", 0);
}

init()
{
  elfarea::init();
  dir_room::init();
}
