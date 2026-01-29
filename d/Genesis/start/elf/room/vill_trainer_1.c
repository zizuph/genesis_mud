#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "vill_road.h"

#pragma save_binary

inherit ELFROOM;

#define SOUTH     ROOMDIR + "vill_road_3"
#define NORTH     ROOMDIR + "vill_trainer_2"

#define NAT_SHORT "In the garden of sergeant Bullwhip"
#define FOR_SHORT "On a garden path"

#define NAT_LONG \
  "You are on a small path in the garden of the sergeant Bullwhip. North is "+\
  "a door into a stone house, while in the " + \
  "south the path leads out on the road. " +\
  "There is a small sign firmly planted into the grass beside the path.\n"
#define FOR_LONG \
  "You are on a small path in a garden. North is " + \
  "a door into a stone house, while in the " + \
  "south the path leads out on the road. " +\
  "There is a small sign firmly planted into the grass beside the path.\n"

#define SIGN_TEXT \
  "Weapon skills trained here.\n"

#define HOUSE_ITEM ({"house", "stone house"})
#define HOUSE_DESC \
  "It is a massive, uninviting stone house with narrow window-openings and " +\
  "low, arched doors."

#define GARDEN_ITEM ({"garden"})
#define GARDEN_DESC \
  "The garden seem neglected and untended. The weeds are by far in majority "+\
  "and are waging a winning war on the few herbs and ornamental plants left.\n"

#define PATH_ITEM ({"path", "small path", "garden path"})
#define PATH_DESC \
  "It is a small, gravel path that goes straight to the house.\n"

#define WEED_ITEM ({"weed", "weeds"})
#define WEED_DESC \
  "The weeds are vigorous and robust, strangling the rest of the garden.\n"

#define GRASS_ITEM ({"grass", "grasss", "cluster", "personel"})
#define GRASS_DESC \
  "The grass has gone feral, and is long, yellow, and weed-filled.\n"

#define SIGN_ITEM ({"sign", "plate" })
#define SIGN_DESC   "The sign reads:\n" 

  
create_room()
{
  set_short(N_KNOW(NAT_SHORT, FOR_SHORT));
  set_long( N_KNOW(WRAP(NAT_LONG),
		   WRAP(FOR_LONG)));

  add_item(  HOUSE_ITEM, WRAP(  HOUSE_DESC));
  add_item( GARDEN_ITEM, WRAP( GARDEN_DESC));
  add_item(   WEED_ITEM, WRAP(   WEED_DESC));
  add_item(   PATH_ITEM, WRAP(   PATH_DESC));
  add_item(  GRASS_ITEM, WRAP(  GRASS_DESC));
  add_item(   SIGN_ITEM, WRAP(   SIGN_DESC + SIGN_TEXT)); 

  add_cmd_item(SIGN_ITEM, "read", WRAP(SIGN_DESC + SIGN_TEXT));

  add_exit(SOUTH,      "south", 0);
  add_exit(NORTH,      "north", 0);

  stock();
}


stock()
{
}
