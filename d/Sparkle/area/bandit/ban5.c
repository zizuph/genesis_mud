/*
 * Varian - October 5 2015
 */

#pragma save_binary

inherit "/std/room";

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>
#include <state_desc.h>

static object bandit, bandit2;

int do_push(string str);

void

create_room()

{
    set_short("Dark tunnel");
    set_long("You are in a dark, underground corridor. Wooden posts and " +
        "beams line the tunnel, supporting the hard-packed dirt which " +
        "forms the ground, walls and ceiling. Footprints seem to move " +
        "east and west along the tunnel, which is rather odd since " +
        "the eastern wall appears to be a dead end. The tunnel is " +
        "otherwise rather bland and featureless.\n");
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
    add_item(({"east wall", "eastern wall"}),
        "The east wall appears to be a dead end, but as you look a little " +
        "bit closer, you can see the faint outline of what might be " +
        "a door frame.\n");
    add_item(({"door", "door frame", "frame", "outline", "doorframe"}),
        "Yes, there is definitely the outline of a door framed in the " +
        "eastern wall. Perhaps if you were to search it, you might figure " +
        "out how to open it.\n");
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
    
    add_exit(THIS_DIR + "ban6", "west");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(ROOM_S_MAP_FILE, "bandit.txt");

    reset_room();

}


void

reset_room() 
{
    if(!bandit) bandit = clone_object(NPC_DIR + "bandit.c");
    if (!present(bandit)) bandit->move(this_object());

    if(!bandit2) bandit2 = clone_object(NPC_DIR + "bandit2.c");
    if (!present(bandit2)) bandit2->move(this_object());
}

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
    if((str != "door"))
{ write("Push what?\n");
return 1;
}
write("Pushing against the outline of the door, you move into a large " +
    "chamber.\n");
SAYBB(" presses on the eastern wall and leaves into a secret chamber.");
TP->move_living("M",THIS_DIR + "ban4",1,0);
SAYBB(" enters through a secret door in the west wall.");
return 1;
}

public string
do_search(object pl, string arg)
{
    if (member_array(arg,
        ({ "east wall",
           "eastern wall",
           "outline",
           "door",
           "frame",
        }) ) == -1)
    {
        return "Your search reveals nothing special.\n";
    }

    return "As you feel around the edges of the frame, you notice that this " +
        "is the back end of a secret door. You are confident that a " +
        "firm push against the door would grant you access through the " +
        "eastern wall.\n";

}