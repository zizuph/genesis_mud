/*
 * File         : /d/Genesis/start/hobbit/town/woodpath1.c
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
 *        maybe something interesting could fall off in the speed.
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
      "A thick wood to the south begins here with some tiny pine plants. " +
      "Large boulders and rocks surrounded by grass and flowers fills " +
      "the area. There is a fresh smell of the sea in the air and it " +
      "can be seen a bit further south. The well travelled mountain " +
      "path winds up further to the north.\n");
    add_item(({ "boulder", "boulders", "rock", "rocks" }), 
      "Big rock pieces are scattered over the hillside. \n");
    add_item("grass", 
      "The grass is quite long and dark green. \n");
    add_item("path", 
      "The path is well travelled by foot, horse and by carriage. \n");
    add_item("sea", 
      "Far south you can see the mighty sea all the way to the " +
      "horizon. \n");
    add_item("small", 
      "The fresh air smells slighly of saltwater from the sea south " +
      "of here. \n");
    add_item(({ "tiny pine plants", "pine plants" }), 
      "A small conifer with sharp needles. \n");
    add_item("wood", 
      "It is a pine wood and grows thicker to the south. \n");
    
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 1/18/99.\n");
    
    add_exit("woodpath2.c", "south");
    
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



