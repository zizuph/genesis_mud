/*
 * Varian - November 2 2015
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>
#include <state_desc.h>

int do_push(string str);

void

create_room()

{
    set_short("Dark tunnel");
    set_long("You are in a dark, underground corridor. Wooden posts and " +
        "beams line the hallway, supporting the hard-packed dirt which " +
        "forms the ground, walls and ceiling. This was probably one large " +
        "room at one point in time, but large slabs of broken stone at " +
        "the west end have made this looking more tunnel-like. You spot " +
        "the remnants of a stone staircase in the middle of the rubble " +
        "here, but there is a large stone slab covering the top portion. " +
        "The tunnel continues to the east.\n");
    add_item(({"ceiling", "up"}),
        "The ceiling here is made of dirt, cleverly packed and " +
        "supported by some wooden beams. The only exception is the west " +
        "end of the hall where large slabs of broken stone seem to have " +
        "collapsed.\n");
    add_item(({"wall", "walls"}),
        "All of the walls here look the same, they are just packed " +
        "dirt, with the occasional wooden post that helps to support " +
        "the ceiling beams above your head. At the west end of the " +
        "hall, the walls seem to become broken rubble.\n");
    add_item(({"north wall", "northern wall"}),
        "The north wall is well packed dirt with several wooden posts " +
        "placed every so often to help support the ceiling above.\n");
    add_item(({"south wall", "southern wall"}),
        "The south wall is well packed dirt with several wooden posts " +
        "placed every so often to help support the ceiling above.\n");
    add_item(({"west wall", "western wall"}),
        "The western end of this tunnel ends in a wall of broken slabs " +
        "of white stone and other rubble. In the middle of the debris, " +
        "a stone staircase is visible.\n");
    add_item(({"floor", "down", "ground"}),
        "The floor here is just packed dirt. There are many footprints " +
        "left all around from previous occupants.\n");
    add_item(({"prints", "footprints"}),
        "You see a few sets of footprints which seem to be going east " +
        "into the darkness of the tunnel.\n");
    add_item(({"beam", "beams", "post", "posts"}),
        "Every beam is supported at a joint with two posts to keep the " +
        "ceiling stable above your head. There is nothing special about " +
        "them.\n");
    add_item(({"join", "joint"}),
        "These joints are rather simple, yet effective in keeping the " +
        "structure of the tunnel together so that the dirt walls and " +
        "ceiling do not come crashing down.\n");
    add_item(({"stairs", "stair", "staircase", "stone staircase", 
            "stone stairs", "stone stair"}),
        "Upon closer inspection, you notice that this stone staircase is " +
        "actually in surprisingly good condition. Well, as long as you don't " +
        "consider the broken stone slabs which are covering it.\n");
    add_item(({"dirt", "brown dirt", "brown soil", "soil"}),
        "Dirt, dirt, dirt. Almost everywhere you look, it seems like " +
        "that is all you can see here. Brown and hard-packed, the soil fills " +
        "the ceiling, walls and floor.\n");
    add_item(({"chamber", "room", "large chamber"}),
        "The west end of this tunnel, where all the broken slabs of stone " +
        "are, looks like it might have been one large room at one point " +
        "in time.\n");
    add_item(({"tunnel", "corridor", "here", "hall", "hallway"}),
        "You are in a dark, underground corridor. Wooden posts and " +
        "beams line the hallway, supporting the hard-packed dirt which " +
        "forms the ground, walls and ceiling. This was probably one large " +
        "room at one point in time, but large slabs of broken stone at " +
        "the west end have made this looking more tunnel-like. You spot " +
        "the remnants of a stone staircase in the middle of the rubble " +
        "here, but there is a large stone slab covering the top portion. " +
        "The tunnel continues to the east.\n");
    add_item(({"slab", "slabs", "stone slab", "broken slab", "stone slabs", 
            "broken slabs", "broken stone", "stone", "rubble", "white stone",
            "white slab"}),
        "Dozens of broken slabs of white stone have collapsed around a " +
        "staircase at the western end of the tunnel. These slabs were " +
        "probably a part of a much larger structure which has now become " +
        "northing more than rubble.\n");
    
    add_exit(THIS_DIR + "base2", "east");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    reset_room();
}

void

init()
{
    ::init();
    add_action("do_push","push");
}

int
do_push(string str)
{
if(!str)
{
write("Push what?\n");
return 1;
}
    if((str != "slab"))
{ write("Push what?\n");
return 1;
}
write("Climbing to the top of the stairs, you brace your body and push " +
    "upwards against the stone slab. Once there is enough of an opening, " +
    "you squeeze out into what appears to be the ruined foundation of " +
    "an old mansion. You notice that the stone slab has fallen back into " +
    "place, once again covering the stairs.\n");
SAYBB(" climbs up the stairs and pushes against the stone slab just " +
    "enough to squeeze out beyond. As soon as they leave, the stone slab " +
    "slips back into place, covering the top of the stone staircase.");
TP->move_living("M",WILD_DIR + "mansion",1,0);
SAYBB(" climbs up and out from behind a white stone slab.");
return 1;
}

public string
do_search(object pl, string arg)
{
    if (member_array(arg,
        ({ "rubble", 
           "slab", 
           "stone",
           "stone slab",
           "white stone",
           "stair",
           "debris",
           "stone slabs",
           "stones",
           "white slab",
           "slabs",
           "white slabs",
           "stairs",
           "staircase",
           "stone staircase",
        }) ) == -1)
    {
        return "Your search reveals nothing special.\n";
    }

    return "As you carefully inspect all of the slabs across the western " +
        "end of the tunnel around the stone staircase, you notice that the " +
        "slab at the top of the staircase can move a little. You could " +
        "probably push on it, but you are not sure if it would cause " +
        "the ceiling to fall down on your head or not.\n";

}