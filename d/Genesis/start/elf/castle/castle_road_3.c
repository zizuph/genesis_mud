
#include "../stddefs.h"
#include "../desc_include/castle_road.h"

#pragma save_binary

inherit DIRROOM;
inherit ELFAREA;
inherit STRINGLIB;
inherit MISCLIB;

#define NORTH  CASTLEDIR + "castle_road_2"
#define SOUTH  CASTLEDIR + "castle_road_4"


#define LEAVE_LONG \
  "  As you walk towards the north, the sun suddenly peeks up above the west "+\
  "horizon, painting everything with it's red glow. Far in the north you "+\
  "the roofs of several small houses glowing brick red from the early "+\
  "rays.\n"+\
  "Wait a minute. The sun rising in the west?\n"

#define ENTER_LONG \
  "  The sun is setting with the same frightening speed, and it's starting "+\
  "to get dark. The red light of the sinking sun is colouring the castle "+\
  "a fragile pink, with sparkles of pure ruby.\n"

#define LONG \
  "  In the south, the walls of the castle is painted pink from the twilight "+\
  "sun.\n"


#define CASTLE_ITEM ({"castle", "palace", "tower", "towers"})
#define CASTLE_NDESC \
  "The towers of King Oberon's and Queen Titania's castle " + \
  "shimmers reddishly from the red sunlight reflected and "+\
  "refracted by the thousands of " +\
  "jewels that has been set into the castle walls.\n" 
#define CASTLE_FDESC \
  "The towers of a castle shimmers in the red sunlight, as if " +\
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
