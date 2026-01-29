/*
 * Varian - October 5 2015
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>
#include <state_desc.h>

void

create_room()

{
    set_short("Dark tunnel");
    set_long("You are in a dark, underground corridor. Wooden posts and " +
        "beams line the tunnel, supporting the hard-packed dirt which " +
        "forms the ground, walls and ceiling. The tunnel is otherwise " +
        "rather featureless, following footprints which lead off into " +
        "darkness to both the east and the west.\n");
    add_item(({"ceiling", "up"}),
        "The ceiling here is made of dirt, cleverly packed and " +
        "supported by some wooden beams.\n");
    add_item(({"wall", "walls"}),
        "All of the walls here look the same, they are just packed " +
        "dirt, with the occasional wooden post that helps to support " +
        "the ceiling beams above your head.\n");
    add_item(({"north wall", "northern wall"}),
        "The north wall is well packed dirt with several wooden posts " +
        "placed every so often to help support the ceiling above.\n");
    add_item(({"south wall", "southern wall"}),
        "The south wall is well packed dirt with several wooden posts " +
        "placed every so often to help support the ceiling above.\n");
    add_item(({"floor", "down", "ground"}),
        "The floor here is just packed dirt. There are many footprints " +
        "left all around from previous occupants.\n");
    add_item(({"prints", "footprints"}),
        "Several sets of footprints run east and west fading away into " +
        "the distant darkness of the tunnel.\n");
    add_item(({"beam", "beams", "post", "posts"}),
        "Every beam is supported at a joint with two posts to keep the " +
        "ceiling stable above your head. There is nothing special about " +
        "them.\n");
    add_item(({"join", "joint"}),
        "These joints are rather simple, yet effective in keeping the " +
        "structure of the tunnel together so that the dirt walls and " +
        "ceiling do not come crashing down.\n");
    add_item(({"dirt", "brown dirt", "brown soil", "soil"}),
        "Dirt, dirt, dirt. Almost everywhere you look, it seems like " +
        "that is all you can see here. Brown and hard-packed, the soil fills " +
        "the ceiling, walls and floor.\n");
    add_item(({"tunnel", "corridor", "here", "hallway"}),
        "You are in a dark, underground corridor. Wooden posts and " +
        "beams line the tunnel, supporting the hard-packed dirt which " +
        "forms the ground, walls and ceiling. The tunnel is otherwise " +
        "rather featureless, following footprints which lead off into " +
        "darkness to both the east and the west.\n");
    
    add_exit(THIS_DIR + "base1", "west");
    add_exit(THIS_DIR + "base3", "east");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);

    reset_room();

}
