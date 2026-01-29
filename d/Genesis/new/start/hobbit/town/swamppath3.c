/*
 * File         : /d/Genesis/start/hobbit/town/swamppath3.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 1/13/99
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
      "The ground is covered with green moss, different kinds of lichen " +
      "as well as odd looking flowers which all seems to feel very well " +
      "in this marshy environment. Some rough buildings can be seen " +
      "northwest of here.\n");
    add_item("smell", 
      "A faint smell of rotten egg is mixed with the fresh sea air " +
      "here. \n");
    add_item(({ "vegatation", "moss", "lichen" }), 
      "The swamp is filled with green moss, herbs and lichen \n");
    
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 1/13/99.\n");
    
    add_exit("swamppath2.c", "north");
    add_exit("swamppath4.c", "southwest");
    
    
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



