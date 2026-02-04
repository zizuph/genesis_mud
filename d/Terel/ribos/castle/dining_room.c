/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * dining_room.c
 *
 * Vader
 * Recoded by Sorgum 950602
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit STDROOM;

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({CASTLE_DIR + "monster/boy" });
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Dining room");
    set_long("This is where the King eats his meals, along with " +
	     "his guests.  The table is made of a polished stone " +
	     "slab, and is round in shape.  There is an inscription " +
	     "on the middle of the table.  This entire " +
	     "room is decorated in extremes.  Plenty of wealth " +
	     "is displayed in this room, but it is all protected " +
	     "by magic.\n");

    add_item(({"table", "round table", "stone slab"}),
	     "It is the smoothest, most shiny piece of stone you " +
	     "have ever seen.\n");
    
    add_item(({"inscription"}),
	     "It depicts a huge creature, with a longsword embedded " +
	     "in its chest.\n");

    INSIDE;

    add_exit(CASTLE_DIR + "l_hall1_1", "north", 0);
    add_exit(CASTLE_DIR + "kitchen",   "west",  0);

    reset_room();
}
 
