
#include "../stddefs.h"
#include "../desc_include/castle_road.h"

#pragma save_binary

inherit DIRROOM;
inherit ELFAREA;
inherit STRINGLIB;
inherit MISCLIB;

#define NORTH  CASTLEDIR + "castle_road_4"
#define SOUTH  CASTLEDIR + "castle_gate_2"

#define NAT_SHORT "Before the main gate of the Castle"
#define FOR_SHORT "Before the main gate of a castle"

#define LEAVE_LONG \
  "Leaving through the main gate, you can see a wide, tree-lined avenue "+\
  "before you. It is lit by the shining moon in the sky, and the stones "+\
  "that pave it shimmers mysteriously in the moonlight.\n"
#define ENTER_LONG \
  "You have arrived at the main gate of the castle. High above you the "+\
  "windows glow warmly against the cold white of the moonlit walls. "+\
  "More yellow light spills out through a crack in the gate, and laughter "+\
  "and music can be faintly heard.\n"
#define LONG \
  "You are standing before the main gate of the castle. High above you the "+\
  "windows glow warmly against the cold white of the moonlit walls. "+\
  "More yellow light spills out through a crack in the gate, and laughter "+\
  "and music can be faintly heard.\n"

#define SOUND_ITEM ({"sound", "music", "laughter"})
#define SOUND_DESC \
  "It is too muffled to be recognizable.\n"

#define CRACK_ITEM ({"crack"})
#define CRACK_DESC \
  "It is too narrow to see anything through.\n"

#define MOON_ITEM ({"moon", "new moon"})
#define MOON_DESC \
  "It is a huge celestial object of unknown origin.\n"

#define MOONLIGHT_ITEM ({"moonlight"})
#define MOONLIGHT_DESC \
  "It is pale white, and comes from the moon above.\n"

#define LIGHT_ITEM ({"light", "yellow light", "warm light"})
#define LIGHT_DESC \
  "It is warm and yellow. It may come from candles or good quality torches.\n"

#define WINDOWS_ITEM ({"window", "windows"})
#define WINDOWS_DESC \
  "The windows are placed by far too high above you to see through.\n"

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
  set_short(N_KNOW(NAT_SHORT, FOR_SHORT));
  set_long(DPHRASE("long"));

  CASTLE_ROAD_STD_ITEMS;
  add_item(    SOUND_ITEM,     SOUND_DESC);
  add_item(    CRACK_ITEM,     CRACK_DESC);
  add_item(     MOON_ITEM,      MOON_DESC);
  add_item(MOONLIGHT_ITEM, MOONLIGHT_DESC);
  add_item(    LIGHT_ITEM,     LIGHT_DESC);
  add_item(  WINDOWS_ITEM,   WINDOWS_DESC);
  add_item(   CASTLE_ITEM, N_KNOW(WRAP(CASTLE_NDESC),
			          WRAP(CASTLE_FDESC)));

  add_dir_phrase("long", NORTH, WRAP(ENTER_LONG));
  add_dir_phrase("long", SOUTH, WRAP(LEAVE_LONG));
  add_dir_phrase("long",     0, WRAP(      LONG));

  add_exit(SOUTH, "south", NYI);
  add_exit(NORTH, "north", 0);
}

init()
{
  elfarea::init();
  dir_room::init();
}

