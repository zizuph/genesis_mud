/*
 * File         : /d/Genesis/start/hobbit/town/portroad3.c
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
      "part of the village by a number of well built wooden bridges. A " +
      "small shed-like building with a sign on the roof can be seen to " +
      "the southwest and further south a nice pond can be seen in front " +
      "of the sea.\n");
    add_item(({ "bridge", "bridges" }), 
      "The sturdy bridges are made by skilled craftsmen. \n");
    add_item("creek", 
      "The creek flows gently under the bridges. \n");
    add_item(({ "dirtroad", "road" }), 
      "Packed yellow dirt and pebbles makes up the road. \n");
    add_item(({ "pond", "sea" }), 
      "The water can be reached further south along this road. \n");
    add_item(({ "shed-like building", "building" }), 
      "The small shed-like building is the village shop \n");
    add_item("sign", 
      "The sign reads \"Soltan's shop\". \n");
    
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/27/99.\n");
    
    add_exit("woodenbridge3.c", "east");
    add_exit("portroad2.c", "north");
    add_exit("portroad4.c", "south");
    add_exit("shop.c", "southwest");
    
    
    
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
        Guard->configure_me(70);   // Make Mungar III the youngest son
        Guard->grid_set_size(4,3); // Set patrol area
        Guard->grid_set_pos(1,1);  // Set position of this room in area
        Guard->move(this_object(), 1);
        tell_room(TO, QCTNAME(Guard) + " walks in.\n");
    }
    
}



