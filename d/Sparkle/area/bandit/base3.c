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

int do_dig(string str);

void

create_room()

{
    set_short("Dark tunnel");
    set_long("You are in a dark, underground corridor. Wooden posts and " +
        "beams line the tunnel, supporting the hard-packed dirt which " +
        "forms the ground, walls and ceiling. The tunnel trails off " +
        "in the darkness to the west, but to the east it ends in what " +
        "is apparently mid-construction. Perhaps there is somebody " +
        "who will continue to extend it one day.\n");
    add_item(({"ceiling", "up"}),
        "The ceiling here is made of dirt, cleverly packed and " +
        "supported by some wooden beams.\n");
    add_item(({"east wall", "eastern wall"}),
        "The eastern wall of this tunnel is, well, unfinished. It appears " +
        "as if somebody is still working on extending this tunnel to " +
        "lead somewhere.\n");
    add_item(({"north wall", "northern wall"}),
        "The north wall is well packed dirt with several wooden posts " +
        "placed every so often to help support the ceiling above.\n");
    add_item(({"south wall", "southern wall"}),
        "The south wall is well packed dirt with several wooden posts " +
        "placed every so often to help support the ceiling above.\n");
    add_item(({"wall", "walls"}),
        "All of the walls here look the same, they are just packed " +
        "dirt, with the occasional wooden post that helps to support " +
        "the ceiling beams above your head.\n");
    add_item(({"construction", "extension", "work"}),
        "The eastern wall of this tunnel is unfinished, and is apparently " +
        "under construction. Perhaps you should check it again later?\n");
    add_item(({"three walls", "three wall"}),
        "There are three walls here, to the north, east and south. There is " +
        "no wall to the west, as the tunnel leads off into the darkness that " +
        "way.\n");
    add_item(({"floor", "down", "ground"}),
        "The floor here is just packed dirt. There are many footprints " +
        "left all around from previous occupants.\n");
    add_item(({"prints", "footprints"}),
        "Several sets of footprints seem to circle around the three walls " +
        "here before they run west, fading away into " +
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
    
    add_exit(THIS_DIR + "base2", "west");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    reset_room();

}

void

init()
{
    ::init();
    add_action("do_dig","dig");
}

int
do_dig(string str)
{
if(!str)
{
write("Dig where?\n");
return 1;
}
    if((str != "north wall"))
{ write("Dig where?\n");
return 1;
}
write("You start digging away into the soft dirt of the northern wall and " +
    "discover a narrow opening you can squeeze yourself into.\n");
SAYBB(" begins to dig at the dirt in the north wall and is suddenly " +
    "no longer here!");
TP->move_living("M",THIS_DIR + "ban7",1,0);
SAYBB(" squeezes out from the dirty hole in the south wall.");
return 1;
}

public string
do_search(object pl, string arg)
{
    if (member_array(arg,
        ({ "north wall", 
           "dirt", 
           "northern wall",
        }) ) == -1)
    {
        return "Your search reveals nothing special.\n";
    }

    return "As you search the northern wall, you notice that some of the " +
    "dirt here is not very well packed, in fact, it is rather loose! You " +
    "think that if you were to dig a little deeper in the north wall " +
    "you might be able to find something hidden there.\n";

}
