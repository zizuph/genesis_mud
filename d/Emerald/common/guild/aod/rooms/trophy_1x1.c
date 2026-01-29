/*
 *  /d/Emerald/common/guild/aod/rooms/trophy_1x1.c
 *
 *  One of the 100 rooms that the Ogre guild has at its disposal for
 *  trophy storage.
 *
 *  Created June 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"
#include <stdproperties.h>

inherit AOD_ROOM_DIR + "cave_room";
inherit AOD_LIB_DIR + "add_spike";

/* prototypes */
public void        create_cave_room();
public void        add_trophy_items();



/*
 * Function name:        create_cave_room
 * Description  :        set up the room
 */
public void
create_cave_room()
{
    set_short("in a vast trophy chamber");
    set_em_long("Though thick and crusted, the walls here are"
      + " softened by smooth rounded curves and corners. This appears"
      + " to be some sort of large hollowed-out chamber within a"
      + " magma deposit. Many dozens of trophy spikes are visible"
      + " in the chamber. Apparently, this area is used to store the"
      + " spoils of various exploits that the Ogre Chieftains have"
      + " produced over the years.\n");

    add_trophy_items();
    add_cave_items();

    add_spike("trophy_1x1");

    add_exit("trophy_1x2", "east");
    add_exit("trophy_2x2", "southeast");
    add_exit("trophy_2x1", "south");
} /* create_cave_room */


/*
 * Function name:        add_trophy_items
 * Description  :        add items that are specific to the trophy
 *                       chamber for the guild.
 */
public void
add_trophy_items()
{
    add_name("_sph_chamber");

    add_item( ({ "deposit", "magma deposit" }),
        "The chamber you are standing in is embedded within the magma"
      + " deposit. Lets just hope the volcano chooses to keep still"
      + " today.\n");
    add_item( ({ "chamber", "large chamber", "hollowed-out chamber",
                 "large hollowed-out chamber" }),
        "This chamber is perfect for storing trophies. At least,"
      + " that is how the mind of an Ogre works.\n");
    add_item( ({ "trophies" }),
        "There must be close to a hundred in this chamber!\n");
    add_item( ({ "spoils" }),
        "Just walk around and look at the spikes to see for yourself.\n");
    add_item( ({ "exploits" }),
        "Quite so. Perhaps some of the exploits were your own?\n");
    add_item( ({ "wall", "walls", "thick wall", "thick walls",
                   "crust", "crusted wall", "crusted walls",
                   "crusty wall", "crusty walls" }),
        "There is a surreal quality to these walls. They are"
      + " so crusty, and yet they flow smoothly, like the"
      + " inside of a macaroni noodle.\n");
    add_item( ({ "noodle", "macaroni", "noodles",
                 "macaroni noodle", "macaroni noodles" }),
        "Mmmmmm ... macaroni ...\n");
    add_item( ({ "curve", "corner", "curves", "corners",
                 "smooth curve", "smooth corners",
                 "round curve", "round corners",
                 "smooth corner", "round corner",
                 "smooth curves", "smooth corners",
                 "smooth curves and corners",
                 "round curves and corners",
                 "rounded curve", "rounded corners",
                 "rounded curves", "rounded corner",
                 "rounded curves and corners",
                 "smooth and rounded curves and corners" }),
        "Such formations can only be the result of moving"
      + " liquid passing through them.\n");
    add_item( ({ "liquid", "moving liquid" }),
        "Fortunately for you, there isn't any right now. Swimming"
      + " through piping hot magma tends to irritate the skin.\n");
    add_item( ({ "magma" }),
        "There isn't any here right now. That's a good thing, so"
      + " just move along.\n");
    add_item( ({ "hot magma", "piping hot magma" }),
        "Um ... yes. It doesn't tend to flow in any other way.\n");
    add_item( ({ "floor", "ground" }),
        "The ground here is not well defined. It is just as"
      + " rounded and smooth as the walls.\n");
    add_item( ({ "ceiling", "roof" }),
        "The roof of this chamber is rounded and smooth, just like the"
      + " walls.\n");
    add_item( ({ "volcano", "volcanos" }),
        "Powerful and, fortunately for you, sleeping at the moment.\n");
    add_item( ({ "glow", "warm glow" }),
        "Ahh ... its rather cozy in here. Deadly cozy.\n");
    add_item( ({ "dome", "magma dome" }),
        "You seem to be inside it.\n");
} /* add_trophy_items */
