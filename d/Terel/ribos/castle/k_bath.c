/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * k_bath.c
 *
 * Vader
 * Recoded by Sorgum 950708
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
    return ({CASTLE_DIR + "monster/king",
	     CASTLE_DIR + "monster/servgirl",
	     CASTLE_DIR + "monster/servgirl"});		     
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("The Kings Bath");
    set_long("The light coming in here from the skylight reflects " +
	     "against the bath water, which looks more like a swimming " +
	     "pool, casts eerie light patterns on the stone walls.  " + 
	     "Along the west wall, there is a balcony where musicians " +
	     "sit and entertain the King.  All around are ornate " +
	     "chairs.  All around are servants who see to the Kings every " +
	     "need.\n");

    add_item(({"bath", "water", "pool"}),
	     "The water is sloshing around quite actively.  Probably " +
	     "because the King is not JUST taking a bath.\n");

    add_item(({"balcony"}), 
	     "Musicians are normally here, but the king has sent them away, " +
	     "probably because he doesn't want too many people spreading " +
	     "rumours about how much fun he has taking a bath.\n");

    add_item(({"skylight"}), "Light enters the room from here.\n");
    
    add_item(({"chairs", "chair"}), 
	     "They are special chairs.  They don't get wet when wet " +
	     "bodies sit on them.\n");

    INSIDE;

    add_exit(CASTLE_DIR + "r_hall1_5", "southwest", 0);
    add_exit(TOWER_DIR + "ne_tower1",  "northeast", 0);
    reset_room();
}

