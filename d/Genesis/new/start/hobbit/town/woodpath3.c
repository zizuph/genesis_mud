/*
 * File         : /d/Genesis/start/hobbit/town/woodpath3.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 1/18/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        Through the wood a narrow path on dark soil runs. It is travelled
 *        by tradesmen from abroad as well as those from the village.
 *        Around the path there are a tight wood which filters the sun
 *        light to reach ground. The temperature is lower here than normal
 *        and the air is moisty. A perfect place for mushrooms maybe?
 *        Maybe a traffic object could simulate wagons passing by and
 *        maybe something interesting could fall off in the speed
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
inherit "/d/Gondor/common/lib/herbsearch";



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
    set_short("A path through a dark wood");
    set_long(
      "The narrow path goes between tall pine trees and is well " +
      "travelled also by horses and waggons. Very little light reaches " +
      "down to the ground and the soil is black and moisty almost " +
      "without any vegetation. The path winds among the trees to the " +
      "north and south.\n");
    
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 1/18/99.\n");
    
    add_exit("wooda3.c", "east");
    add_exit("woodpath2.c", "north");
    add_exit("woodpath4.c", "south");
    add_exit("woodb3.c", "southeast");
    add_exit("woodb1.c", "southwest");
    add_exit("wooda1.c", "west");
    
    // Add herbs found in this room
        set_up_herbs(({GONDOR_HERBS + "blueberry",
                       KRYNN_HERBS  + "cranberry"}),
    
                       ({"soil","ground"}),
    
                       3);
    
    
    
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



