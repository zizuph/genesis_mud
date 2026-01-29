/*
 * File         : /d/Genesis/start/hobbit/town/swamppath1.c
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
      "The vegatation grows thicker here and prevents further passage " +
      "north and eastwards. A backwall of a warehouse can be seen to " +
      "the west. The ground is covered with green moss, different kinds " +
      "of lichen as well as odd looking flowers which all seems to feel " +
      "very well in this marshy environment.\n");
    add_item(({ "backwall", "wall" }), 
      "The backwall of the warehouse looks sturdy and has a small " +
      "window. \n");
    add_item(({ "flowers", "flower" }), 
      "The flowers are small and oddly shaped. \n");
    add_item("smell", 
      "A faint smell of rotten egg is mixed with the fresh sea air " +
      "here. \n");
    add_item(({ "vegatation", "moss", "lichen" }), 
      "The swamp is filled with green moss, herbs and lichen \n");
    add_item("window", 
      "The small window lets some light into the warehouse. \n");
    
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/27/99.\n");
    
    add_exit("swamppath2.c", "south");
    
    
    
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



