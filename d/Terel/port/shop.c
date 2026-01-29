/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * shop.c
 *
 * Original version based on Nick's shop and Trick'y shop in hobbittown.
 * This is the Terel Port version, Modified by Mortricia on 12/13/92
 */

#include "/d/Terel/include/Terel.h"
inherit STD_DIR + "shop";

#define STORE_ROOM       PORT_DIR + "store"

/*
 * Function name:   create_room
 * Description:     Initialize this room
 * Returns:
 */
void
create_shop()
{
    set_store_room(STORE_ROOM);

    set_short("fisherman's shop");
    set_long("You have entered the Fisherman's shop. "
	     + "There are many shelves "
	     + "here where various goods are kept.  "
	     + "There is a counter here, "
	     + "and behind it some words have been painted. They "
	     + "read: WELCOME TO FISHERMAN'S SHOP. "
	     + "There is a small opening behind the counter to the "    
	     + "south, and the exits are to the north and east. "
	     + "There is also a small sign with more instructions.\n");

    set_shop_name("Fisherman's Shop");
    set_keeper_file(PORT_DIR + "monster/shop_keeper");

    hated_race = ({"elf", "hobbit"});
    favoured_race = ({"human"});    
    suspected_race = ({"dwarf", "goblin", "gnome"});
  
    add_exit(PORT_DIR +  "path1", "north", 0);
    add_exit(PORT_DIR +  "road8", "east",  0);
    add_exit(STORE_ROOM,          "south", "@@wiz_check");
}
