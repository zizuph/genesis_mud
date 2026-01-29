/*
 * File         : /d/Genesis/start/hobbit/town/portroad4.c
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
      "This dirtroad connects the village north of here with the port to " +
      "the south. Rippling south a nice creek flows east of the road " +
      "and falls into a small pond. A small shed-like buiding can be " +
      "seen to the west and at the opposite side of the creek a post " +
      "office.\n");
    add_item("creek", 
      "The creek flows gently south towards the open water. \n");
    add_item(({ "dirtroad", "road" }), 
      "Packed yellow dirt and pebbles makes up the road. \n");
    add_item("pier", 
      "The pier can be reached further down the road to the south \n");
    add_item("pond", 
      "An u-shaped pier has been built on this side of the pond. \n");
    add_item(({ "post", "post office", "office" }), 
      "The post office can't be entered from this side. \n");
    add_item(({ "shed-like building", "building" }), 
      "It appears to be used for commersial purposes. It can't be " +
      "entered from this side. \n");
    add_item("village", 
      "The village to the north is centered arround a large building " +
      "with a small tower on top. \n");
    add_item("water", 
      "A small pond can be seen further south. \n");
    
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/27/99.\n");
    
    add_exit("portroad3.c", "north");
    add_exit("portroad5.c", "south");
    
    
    
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



