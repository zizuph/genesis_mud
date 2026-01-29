/*
 * File         : /d/Genesis/start/hobbit/town/woodenbridge3.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 2/12/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        The village resides around a creek flowing from north to south
 *        crossed by 3-4 wooden bridges.
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
    set_short("A wooden bridge");
    set_long(
      "The sturdy woodenbridge spans over the calm and gently flowing " +
      "creek. The old oak planks show signs of skillful use of axes. " +
      "There are rings on the water indicating the extistance of life " +
      "below.\n");
    add_item(({ "bridge", "wooden bridge" }), 
      "The bridge is skillfully made by craftsmen. \n");
    add_item("bridges", 
      "There are three or four of them along the creek. \n");
    add_item("creek", 
      "The creek flows gently under the bridges. \n");
    add_item(({ "fish", "fishes" }), 
      "It is impossible to see exactly from here but they seems to " +
      "eat bread crums that has fallen down from the bridge. \n");
    add_item(({ "mark", "marks" }), 
      "The marks shows that heavy traffic has been using this bridge " +
      "for quite a while. \n");
    add_item("water", 
      "In the water below you can see one or two fishes swimming " +
      "around. \n");
    
    add_prop(ROOM_S_EXIT_FROM_DESC,
      "from over the bridge.");
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/12/99.\n");
    
    add_exit("villageroad5.c", "east");
    add_exit("portroad3.c", "west");
    
    
    
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



