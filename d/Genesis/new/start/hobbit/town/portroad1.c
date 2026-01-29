/*
 * File         : /d/Genesis/start/hobbit/town/portroad1.c
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
object Guard;

/*
 * Function name:       create_room
 * Description  :       set up the room
 */
void
create_room()
{
    set_short("Port road");
    set_long(
      "This dirtroad connects the village with the port to the south. A " +
      "nice creek flows east of the road which is connected to the east " +
      "part of the village by a number of well built wooden bridges. " +
      "The bridge just east of here is extra wide and there are marks " +
      "of wagon wheels on the iron reinforced planks. A pleasent smell " +
      "from an open door to the west reveals the village bakery.\n");
    add_item("bakery", 
      "A low building with white chalked walls and a straw roof. \n");
    add_item("bridge", 
      "The iron reinforced bridge is made wider to enable cargo " +
      "transports. \n");
    add_item("bridges", 
      "The sturdy bridges are made by skilled craftsmen. \n");
    add_item("chimney", 
      "The chimney is black and penetrates the straw layer on the " +
      "back side of the roof. \n");
    add_item("creek", 
      "The creek flows gently under the bridges. \n");
    add_item(({ "dirtroad", "road" }), 
      "Packed yellow dirt and pebbles makes up the road. \n");
    add_item("door", 
      "It is open. \n");
    add_item("marks", 
      "The marks shows that heavy traffic has been using this bridge " +
      "for quite a while. \n");
    add_item("roof", 
      "The roof has one of the biggest chimneys in the village. \n");
    add_item(({ "smell", "air" }), 
      "The smell of newly baked bread and candy can be found in the " +
      "air. \n");
    add_item(({ "walls", "wall" }), 
      "The white chalked walls has a door and a round window. \n");
    add_item("window", 
      "The window is round which is common in this village. \n");
    
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/27/99.\n");
    
    add_exit("woodenbridge1.c", "east");
    add_exit("portroad2.c", "south");
    add_exit("bakery.c", "west");
    
    
    
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
    if (!objectp(Guard))
    {
        Guard = clone_object(EX_MON + "guard");
        Guard->configure_me(100);  // Make Papa Mungar
        Guard->grid_set_size(4,3); // Set patrol area
        Guard->grid_set_pos(1,3);  // Set position of this room in area
        Guard->move(this_object(), 1);
        tell_room(TO, QCTNAME(Guard) + " walks in.\n");
    }
    
}



