#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "../desc_include/fir_forest.h"

#pragma save_binary

inherit ELFROOM;

#define EAST    ROOMDIR + "trade_road_2"
#define INTO    ROOMDIR + "gibber_lair_1"

#define SHORT  "At a cairn in the forest"

#define LONG \
  "You are standing at a huge stone cairn, made out of heavy, massive, " +\
  "round stones, heaped upon each other. A path comes from the east, " +\
  "and circles the cairn, " +\
  "rejoining itself.\n"

#define CAIRN_ITEM ({"cairn", "mound", "stone", "stones", "rocks"})
#define CAIRN_DESC \
  "The stones in the cairn are of gray or pinkish gray granite. They are "+\
  "largely covered by yellow lichen and thick, moist, green moss, except "+\
  "for a few stones on the west side, which all lie around or below a deep " +\
  "black hole that leads down into the inside of the cairn. An acrid smell "+\
  "comes from the hole.\n"

#define PATH_ITEM ({"path", "ground", "circle"})
#define PATH_DESC \
  "The path runs in a complete circle around the cairn. The dry fir "+\
  "needles has been tread into the ground, exposing the dark earth "+\
  "beneath. Some gnarly fir roots have also had their bark worn away " +\
  "where they cross the path.\n"

#define HOLE_ITEM ({"hole", "black hole", "inside"})
#define HOLE_DESC \
  "It seems to be very dark down there.\n"

#define MOSS_ITEM ({"moss", "green moss", "cover"})
#define MOSS_DESC \
  "It is thick, moist and green.\n"
#define MOSS_KNIFE_DESC \
  "It is thick, moist and green, and someone seems to have lost a " +\
  "knife in it.\n"

#define KNIFE_ITEM ({"knife", "lost knife", "knife in moss"})
#define KNIFE_ID     "knife"
#define KNIFE_PRS_DESC "It is just lying there.\n"
#define KNIFE_ABS_DESC "You cannot see any knife here.\n"
#define KNIFE_GET_SUCC "You pick up the knife.\n"
#define KNIFE_GET_FAIL "You cannot see any knife here.\n"

create_room()
{
  set_short(SHORT);
  set_long(WRAP(LONG));

  add_item(CAIRN_ITEM, WRAP(CAIRN_DESC));
  add_item( PATH_ITEM, WRAP( PATH_DESC));
  add_item( HOLE_ITEM, WRAP( HOLE_DESC));
  add_item( MOSS_ITEM, H_ITEM(KNIFE_ID, 
			      WRAP(MOSS_KNIFE_DESC), 
			      WRAP(MOSS_DESC)));
  add_item(KNIFE_ITEM, H_ITEM(KNIFE_ID, 
			      KNIFE_PRS_DESC, KNIFE_ABS_DESC));
  add_cmd_item(KNIFE_ITEM, "get", 
	       GET_H_ITEM(KNIFE_ID, KNIFE_GET_SUCC, KNIFE_GET_FAIL));
  add_cmd_item(KNIFE_ITEM, "take", 
	       GET_H_ITEM(KNIFE_ID, KNIFE_GET_SUCC, KNIFE_GET_FAIL));


  FIR_FOREST_STD_ITEMS;
  add_exit(EAST, "east", 0);

  tie_to_map(CENTER_SQUARE, CENTER_X, 3, CENTER_Y, 4);

  stock();
}

stock()
{
  restock_hidden_item(OBJDIR + "gibber_knife", 1, KNIFE_ID);
}

reset_room()
{
  stock();
}


init()
{
  ::init();
  
  add_action("do_enter", "enter");
  add_action("do_enter", "go");
  add_action("do_enter", "go into");
}

do_enter(arg)
{
  if (arg == "cairn" ||
      arg == "mound" ||
      arg == "hole") {
    this_player()->move_living("into the cairn", INTO);
    return 1;
  }

    notify_fail(capitalize(query_verb()) + " what?\n");
}
