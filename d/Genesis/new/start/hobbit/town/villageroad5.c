/*
 * File         : /d/Genesis/start/hobbit/town/villageroad5.c
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
      "A village dirt road runs around the village hall ending here at " +
      "the stone paved south side. The creek is crossed here by a " +
      "wooden bridge catching the road to the harbour area to the west. " +
      "At a distance laughs and shouts can be heard eastwards.\n");
    add_item("bell", 
      "The small bronze bell is used to gather the village garde when " +
      "someone is endangered. \n");
    add_item(({ "village hall", "hall" }), 
      "A small copper tower with a bell adorns the white painted " +
      "village hall. \n");
    
    add_exit("villageroad4.c", "east");
    add_exit("villagehall.c", "north");
    add_exit("post.c", "south");
    add_exit("woodenbridge3.c", "west");
    
    
    
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



