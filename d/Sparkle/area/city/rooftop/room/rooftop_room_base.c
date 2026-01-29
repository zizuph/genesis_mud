/*
 *  /w/petros/sparkle/rooftop/room/rooftop_room_base.c
 *
 *  This will be the base file for every rooftop room
 *
 *  Created April 2008, by Petros
 */
#pragma strict_types

#include "defs.h"
#include "/d/Sparkle/sys/defs.h"
#include <stdproperties.h>

inherit SPARKLE_ROOM_BASE;
inherit "/d/Sparkle/lib/room_tell";

/* Global Variables */

/* Prototypes */
nomask void        create_sparkle();
public void        create_rooftop_room();
public void        init();

/*
 * Function name:        create_sparkle
 * Descriptionn :        dummy routine for inheriting files
 */
nomask void
create_sparkle()
{
    // Call the base creation function for libraries
    create_rooftop_room();

    // Add the try_items after create_rooftop_room so that it will not
    // replace the items added by subclasses
    try_item( ({ "sparkle", "view", "light" }),
                 "Sparkle is truly a beautiful city set along the coast. "
               + "The endless light here makes everything look wonderfully "
               + "pleasant and bright, which is probably why it is so "
               + "aptly named Sparkle."
               + "\n");
    
    try_item( ({ "gates", "road", "city gates", "city gate", "gate" }),
                 "The city gates guard the city of Sparkle from the "
               + "wilderness beyond. There is one gate that lies along "
               + "the road which leads west out of the city."
               + "\n");
               
    try_item( ({ "forests", "mountains", "forest", "mountain", 
                 "wilderness" }),
                 "Looking west, you see the wilderness beyond the "
               + "city gates. The mountains and the forests dot the "
               + "landscape and is quite expansive."
               + "\n");

    try_item( ({ "citizens" }),
                 "The citizens below are all going about their business. "
               + "It's hard to tell who is who since you can only see "
               + "their heads from here."
               + "\n");

    try_item( ({ "rooftop", "rooftops" }),
                 "All around you are various rooftops in Sparkle. You are "
               + "surprised how close they have all been built together. "
               + "\n");

    try_item( ({ "room" }),
                 "You are on a rooftop on top of a building in Sparkle."
               + "\n");

    try_item( ({ "street", "ants" }),
                 "From up here on the rooftop, you can see the street "
               + "below. There always appears to be activity, but from "
               + "here, everyone looks like little ants."
               + "\n");

    // Properties Section
    add_prop(ROOM_I_INSIDE, 0);
    
} // create_sparkle

/*
 * Function name:        create_rooftop_room
 * Descriptionn :        dummy routine for inheriting files
 */
public void
create_rooftop_room()
{
    
} // create_rooftop_room


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();
} // init
