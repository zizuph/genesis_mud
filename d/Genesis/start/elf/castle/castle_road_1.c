
#include "../stddefs.h"
#include "../desc_include/castle_road.h"

#pragma save_binary

inherit DIRROOM;
inherit ELFAREA;
inherit STRINGLIB;
inherit MISCLIB;

#define NORTH    ROOMDIR +   "vill_road_6"
#define SOUTH  CASTLEDIR + "castle_road_2"

#define LEAVE_LONG \
  "  The sun rises with an abnormal speed as you walk towards the north, and "+\
  "soon it is blazing with all its might from the zenith. As you look "+\
  "behind yourself, you can see the walls and towers of the castle glitter "+\
  "and glare in all their glory.\n"

#define ENTER_LONG \
  "  Before you in the south you can see the castle walls glitter and sparkle "+\
  "in the bright midday sun.\n"

#define LONG \
  "  In the south, the walls of the castle glitters and sparkles in the sun.\n"


#define CASTLE_ITEM ({"castle", "palace", "tower", "towers"})
#define CASTLE_NDESC \
  "The towers of King Oberon's and Queen Titania's castle " + \
  "shimmers from the sunlight reflected and refracted by the thousands of " +\
  "jewels that has been set into the castle walls.\n" 
#define CASTLE_FDESC \
  "The towers of a castle shimmers in the sunlight, as if " +\
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
