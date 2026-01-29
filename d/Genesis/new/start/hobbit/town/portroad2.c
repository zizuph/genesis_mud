/*
 * File         : /d/Genesis/start/hobbit/town/portroad2.c
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
      "This dirtroad connects the village with the port to the south. A " +
      "rippling creek flows southwards east of the road which is " +
      "connected to the east part of the village by a number of well " +
      "built wooden bridges. At this point a bridge leads over to the " +
      "village hall to the east. A peculiar tent-like building can be " +
      "seen to the west and appearantly it is the village blacksmith.\n");
    add_item("bell", 
      "The small bronze bell is used to gather the village garde when " +
      "someone is endangered. \n");
    add_item(({ "bridge", "bridges" }), 
      "The sturdy bridges are made by skilled craftsmen. \n");
    add_item("creek", 
      "The creek flows gently under the bridges. \n");
    add_item(({ "dirtroad", "road" }), 
      "Packed yellow dirt and pebbles makes up the road. \n");
    add_item("smell", 
      "Hot metal mixed with sea air makes up a distinct smell here. \n");
    add_item(({ "smith", "blacksmith" }), 
      "Metalic sounds and smoke reveals the village blacksmith's " +
      "workshop west of here. \n");
    add_item(({ "tent-like building", "building" }), 
      "The blacksmith's workshop seems to have been portable a long " +
      "time ago. \n");
    add_item(({ "village hall", "hall" }), 
      "A small copper tower with a bell adorns the white painted " +
      "village hall. \n");
    
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/27/99.\n");
    
    add_exit("woodenbridge2.c", "east");
    add_exit("portroad1.c", "north");
    add_exit("portroad3.c", "south");
    add_exit("blacksmith.c", "west");
    
    
    
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



