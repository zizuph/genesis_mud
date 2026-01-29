/*
 * /d/Krynn/gnome/boulder.c
 *
 * This room is the boulder that players must kick to enter the home of
 * the gnomes.
 *
 * Code cleanup FEB 22 2009, by Aeg (Matthew Morin) 
 */

/* Includes */ 
#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>

/* Inherits */
inherit "/d/Krynn/std/room";

/* Defines */
#define ENTRANCE     (TDIR + "entrance")

/* 
 * Function name:       create_room
 * Description  :       Sets up the room
 * Arguments    :       none
 * Returns      :       void/nothing
 */
 
void
create_room()
{
    set_short("On top of the boulder");
    set_long("You stand on top of a suspiciously round boulder. The "
        + "sounds from below are clearer now. You wonder how you could "
        + "get the attention of whoever (or whatever) seems so busy down "
        + "there.\n");
    
    add_item(({"rock", "boulder", "large rock"}), 
	        "Closer examination reveals that the boulder has been hewn "
        + "into this shape. It is basically spherical. You stand "
        + "on top of it, and could climb down safely.\n");
	     
    OUTSIDE;
    LIGHT;
    
    add_cmd_item(({"rock", "down", "boulder"}), "climb", "@@climb");
    add_cmd_item(({"rock", "boulder"}), "hit", "@@mech");
    add_cmd_item(({"rock", "boulder"}), "kick", "@@mech");
    add_cmd_item(({"rock", "on rock", "boulder", "on boulder"}),
		 "bang", "@@mech");
    add_cmd_item(({"rock", "on rock", "boulder", "on boulder"}),
		 "knock", "@@mech");
} /* create_room */

/* 
 * Function name:       climb
 * Description  :       This allows a player to climb back to the entrance
 * Arguments    :       none
 * Returns      :       1 success
 */
 
int
climb()
{
    write("You climb down off the boulder.\n");
    say(QCTNAME(TP) + " climbs down off the boulder.\n");
    TP->move_living("down the rock", ENTRANCE);
    return 1;
} /* climb */

/* 
 * Function name:       mech
 * Description  :       This function is the mechanical process that opens the 
 *                      elevator.
 * Arguments    :       none
 * Returns      :       1 success
 */
 
int
mech()
{
    int i;
    object *people;
    string str;
    
    ENTRANCE->load_me();

    people = all_inventory(TO);
    if (sizeof(people) == 1)
      str = "You";
    if (sizeof(people) == 2)
      str = "You and your companion";
    if (sizeof(people) > 2)
      str = "You and your party";
    
    for (i = 0; i < sizeof(people); i++)
      {
	  tell_object(people[i], str +
		      " are thrown off the boulder as it begins to move!\n");
	  people[i]->move_living("falling off the rock", ENTRANCE);
      }
    
    ENTRANCE->trig();
    return 1;
    
} /* mech */
