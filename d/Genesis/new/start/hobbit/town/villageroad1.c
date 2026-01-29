/*
 * File         : /d/Genesis/start/hobbit/town/villageroad1.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 11/26/1998
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        There is a village road connecting all buildings in the village.
 *        It is made of packed dirt except for some flat stones
 *        surrounding the village hall. When it is raining the road gets
 *        really slippry but they are well packed so the water dries up
 *        pretty quickly afterwords.
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
    set_short("A village dirt road");
    set_long(
      "A village dirt road starts north of here near the gate and passes " +
      "here going east. A creek flows gently under a wooden bridge " +
      "westward and disappears to the south behind a corner of the " +
      "biggest building in the village, the village hall, wich can be " +
      "visited to the south. At some distance east along the dirt road " +
      "you see a stone house.\n");
    add_item("bell", 
      "The small bronze bell is used to gather the village garde when " +
      "someone is endangered. \n");
    add_item(({ "village hall", "hall" }), 
      "A small copper tower with a bell adorns the white painted " +
      "village hall. \n");
    
    add_exit("villageroad2.c", "east");
    add_exit("gateroad1.c", "north");
    add_exit("villagehall.c", "south");
    add_exit("woodenbridge1.c", "west");
    
    
    
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



