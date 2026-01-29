#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "vill_road.h"

#pragma save_binary

inherit ELFROOM;

#define SOUTH     ROOMDIR + "vill_road_1"
#define NORTH     ROOMDIR + "vill_scholar_2"

#define NAT_SHORT "In the garden of the widow Wormwood"
#define FOR_SHORT "On a garden path"

#define NAT_LONG \
  "You are on a small path in the garden of the widow Wormwood. North is " + \
  "a door into a wooden house, while in the " + \
  "south the path leads out on the road. " +\
  "There is a small sign firmly planted into the grass among some dark "+\
  "green bushes.\n"
#define FOR_LONG \
  "You are on a small path in a garden. North is " + \
  "a door into a wooden house, while in the " + \
  "south the path leads out on the road. " +\
  "There is a small sign firmly planted into the grass among some dark "+\
  "green bushes.\n"

#define SIGN_TEXT \
  "Mrs Wormwood - teacher for hire\n"

#define HOUSE_ITEM ({"house", "wooden house"})
#define HOUSE_DESC \
  "It is a simple, undecorated wooden house with large windows and " +\
  "green-painted doors that are both wide and tall."

#define GARDEN_ITEM ({"garden"})
#define GARDEN_DESC \
  "The garden is not that very impressive. No blooming flowers, no exotic " + \
  "trees, no carefully arranged plants. Just some long, richly green grass " +\
  "and a few dark-green bushes.\n"

#define PATH_ITEM ({"path", "small path", "garden path"})
#define PATH_DESC \
  "It is a small, earthen path that goes straight to the house. You notice "+\
  "hoofmarks in the dark soil.\n"

#define HOOFMARKS_ITEM ({"hoofmarks"})
#define HOOFMARKS_DESC \
  "The marks seem rather small for a horse. And they lead straight into the house, " +\
  "which definitely does not look like a stable.\n"

#define BUSH_ITEM ({"bush", "bushes"})
#define BUSH_DESC \
  "The bushes are quite anonymous, and could belong to any of a dozen " +\
  "species. The leaves are dark green and heart-shaped, and throw dense " +\
  "shadows on the grass.\n"
#define BUSH_BOOK_DESC \
  "You see an abandoned notebook under one of the bushes.\n"

#define GRASS_ITEM ({"grass", "grasss", "cluster", "personel"})
#define GRASS_DESC \
  "The grass is rather long, but still green and juicy, growing in a " +\
  "thick carpet all around the house.\n"

#define BOOK_ITEM ({"notebook", "note book", "note-book"})
#define BOOK_ID     "notebook"
#define BOOK_PRS_DESC "It is just lying there.\n"
#define BOOK_ABS_DESC "You cannot see any notebook here.\n"
#define BOOK_GET_SUCC "You pick up the notebook.\n"
#define BOOK_GET_FAIL "You cannot see any notebook here.\n"

#define SIGN_ITEM ({"sign", "plate" })
#define SIGN_DESC   "The sign reads:\n" 

  
create_room()
{
  set_short(N_KNOW(NAT_SHORT, FOR_SHORT));
  set_long( N_KNOW(WRAP(NAT_LONG),
		   WRAP(FOR_LONG)));

  add_item(    HOUSE_ITEM, WRAP(    HOUSE_DESC));
  add_item(   GARDEN_ITEM, WRAP(   GARDEN_DESC));
  add_item(     PATH_ITEM, WRAP(     PATH_DESC));
  add_item(    GRASS_ITEM, WRAP(    GRASS_DESC));
  add_item(     SIGN_ITEM, WRAP(     SIGN_DESC + SIGN_TEXT)); 
  add_item(HOOFMARKS_ITEM, WRAP(HOOFMARKS_DESC));

  add_item(BUSH_ITEM, H_ITEM(BOOK_ID, 
			     WRAP(BUSH_DESC + BUSH_BOOK_DESC), 
			     WRAP(BUSH_DESC)));
  add_item(BOOK_ITEM, H_ITEM(BOOK_ID, 
			     BOOK_PRS_DESC, BOOK_ABS_DESC));

  add_cmd_item(SIGN_ITEM, "read", WRAP(SIGN_DESC + SIGN_TEXT));
  add_cmd_item(BOOK_ITEM, "get",  
	       GET_H_ITEM(BOOK_ID, BOOK_GET_SUCC, BOOK_GET_FAIL));
  add_cmd_item(BOOK_ITEM, "take", 
	       GET_H_ITEM(BOOK_ID, BOOK_GET_SUCC, BOOK_GET_FAIL));

  add_exit(SOUTH,      "south", 0);
  add_exit(NORTH,      "north", 0);

  stock();
}


stock()
{
  restock_hidden_item(OBJDIR + "notebook", 1, BOOK_ID);
}

reset_room()
{
  stock();
}