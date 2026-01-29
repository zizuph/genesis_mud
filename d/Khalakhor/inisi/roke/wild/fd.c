/*
 * fd.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 *
 * Updated to an abandoned camp with the Golbar camp moved to a new position, Treacher 08/2021
 */

/* ged */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

void
create_room()
{
    set_short("Abandoned camp");
    set_long("You are in a clearing in the forest, surrounded by an old barricade. " +
             "The barricade looks abandoned and has partly collapsed, but is still " +
             "effectivly stopping anyone from entering the clearing except through its " +
             "exits. On the ground several large patches of barren " +
             "ground form a pattern around the center of the clearing, as if " +
             "something was placed there for a very long time. In the center of " +
             "the clearing there are traces of an old large campfire.\n");

    add_item("clearing",
             "It's a rather large clearing, that was created by cutting down trees " +
             "in the forst. A few tree stumps are still showing here and there.\n");
    add_item(({"barricade", "old barricade"}),
             "The barricade run around the entire clearing, providing a protection " +
             "for the camp from the surrounding forest. Parts of the barricades have " +
             "collapsed and is starting to be overgrown by the vegetation.\n");
    add_item(({"patches", "large patches", "pattern", "barren ground"}),
             "The patches of barren ground are spread out around the center in a circle, " +
             "and you notice some old rusty tent peggs laying around the patches.");
    add_item(({"peggs", "tent peggs"}),
             "They are bent and rusty, cleary used and maybe left behind due to their state.\n");
    add_item(({"stump", "stumps", "tree stump", "tree stumps"}),
             "It is the remains of dead trees. Probably cut down to create a larger " +
             "clearing.\n");
    add_item(({"campfire", "large campfire", "old campfire"}),
             "The ground is scorched by fire and there are still some burned out " +
             "firewood, but now the campfire is abandoned like the camp.\n");
    
    add_exit("fc", "north");
    add_exit("fb", "northwest");
    add_exit("ff", "west");

}
