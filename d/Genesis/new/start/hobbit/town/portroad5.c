/*
 * File         : /d/Genesis/start/hobbit/town/portroad5.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 2/27/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
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
    set_short("Port road");
    set_long(
      "This dirtroad connects the village northwards with the port here. " +
      "A rippling creek fall into the pond right bellow a wooden bridge " +
      "east of here. The pond is bordered by a pier to the east and " +
      "west of here and a lot of thick reed on the other side. The port " +
      "is full of life including travellers, sailors, seagulls and and " +
      "a salty breeze.\n");
    add_item(({ "breeze", "salty breeze" }), 
      "The sea brings a salty breeze to here even though the pond " +
      "itself mainly consists of sweet water. \n");
    add_item("creek", 
      "The creek falls into the pond here and comes from the village " +
      "north. \n");
    add_item(({ "dirtroad", "road" }), 
      "Packed yellow dirt and pebbles makes up the road. \n");
    add_item(({ "life", "travellers" }), 
      "All kinds of travellers passes here every day on their way to " +
      "and from foreign lands. \n");
    add_item(({ "pier", "piers" }), 
      "The piers east and west makes it possible to land there with " +
      "boats from foreign lands. \n");
    add_item("pond", 
      "The pond is calm and was once a small cove but a thick belt of " +
      "reed now separates it from the sea. \n");
    add_item("reed", 
      "The belt of reed protects this pond from the sea. A lot of " +
      "seabirds have their nests there. \n");
    add_item("sailors", 
      "The sailors here have seen many foreign lands. \n");
    add_item("sea", 
      "Not too far south, beyond the belt of reed, is the salty sea. \n");
    add_item("seagulls", 
      "Seagull is the most common bird here and they are very good at " +
      "fishing. \n");
    add_item("village", 
      "The village northwards consists of many low buildings and a " +
      "large building with a small tower on top. \n");
    
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/27/99.\n");
    
    add_exit("portroad4.c", "north");
    add_exit("westpier1.c", "south");
    
    
    
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



