/*
 * File         : /d/Genesis/start/hobbit/town/swamppath2.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 2/27/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        The swamp is filled with snakes, frogs and undereartlings. It
 *        stretches south to the canal where boats can be seen passing by
 *        to the pier. NB The canal is between the sea and the pier. The
 *        pier is built in the pond where the creek exits. The swamp has
 *        potential to have more dangers added. Also some herbs could be
 *        placed here and maybe some poisonous berries with a similar
 *        effect as the spider in the ware house.
 * 
 * TODO         :

 *
 * Modifications:
 *     N.B. This file is generated from templates hosted elsewhere and
 *     if someone corrects something in this file, please mail Seaweed
 * 
 */

#pragma strict_types

/* inherits */
inherit "/std/room";



/* includes */
#include <stdproperties.h> 
#include <macros.h> 

#include "../hobbit.h"

/* defines */



/* prototypes */
void create_room();
void reset_room();

/* globals */


/*
 * Function name:       create_room
 * Description  :       set up the room
 */
void
create_room()
{
    set_short("A swamp");
    set_long(
      "A backwall of a warehouse can be seen to the west. The ground is " +
      "marshy and filled of green growing vegetables and more reed like " +
      "grass can be seen southwards. To the north a small meadowlike " +
      "area can be seen.\n");
    add_item(({ "backwall", "wall" }), 
      "The backwall of the warehouse seems to have a loose plank. \n");
    add_item("opening", 
      "Try to enter opening, if you want to get into the warehouse. \n");
    add_item("plank", 
      "The loose plank reveals an opening into the warehouse. \n");
    add_item("smell", 
      "A faint smell of rotten egg is mixed with the fresh sea air " +
      "here. \n");
    add_item(({ "vegatation", "moss", "lichen" }), 
      "The swamp is filled with green moss and lichen \n");
    
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/27/99.\n");
    
    add_exit("swamppath1.c", "north");
    add_exit("swamppath3.c", "south");
    
    
    add_exit("warehouse4", "enter", 0, 1, 1);
    reset_room();
}
/*
 * Function name:       reset_room
 * Description  :       replenish npc & stuff, if needed
 */
void
reset_room()
{
    setuid();
    seteuid(getuid());
    
}



