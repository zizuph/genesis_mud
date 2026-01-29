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

int do_lift(string str);

void

create_room()

{
    set_short("A secret cubby hole");
    set_long("This is a cramped little cubby hole that someone has " +
        "hidden underneath this bridge. While the ceiling is low, " +
        "you realize that someone has dug out a fair bit of space " +
        "here. The room itself is quite dark, aside from whatever " +
        "light you are able to provide, and extremely empty. However, " +
        "you are fairly certain you could remain here undisturbed " +
        "for quite some time. There only exit here is the door you " +
        "came in from.\n");
    add_item(({"ceiling", "up"}),
        "The ceiling here is made of dirt, cleverly packed and " +
        "supported by some wooden beams.\n");
    add_item(({"wall", "walls"}),
        "All of the walls here look the same, they are just packed " +
        "dirt, with the occasional wooden post that helps to support " +
        "the ceiling beams above your head.\n");
    add_item(({"floor", "down", "ground"}),
        "The floor here is just packed dirt. There are many footprints " +
        "left all around from previous occupants.\n");
    add_item(({"prints", "footprints"}),
        "You have no idea whose footprints they are, and they don't " +
        "lead anywhere, just back through the door you came in.\n");
    add_item(({"beam", "beams", "post", "posts"}),
        "Every beam is supported at a joint with two posts to keep the " +
        "ceiling stable above your head. There is nothing special about them.\n");
    add_item(({"join", "joint"}),
        "As you look carefully at the joints, you notice that one of them " +
        "conceals a hidden niche.\n");
    add_item(({"niche", "hidden niche"}),
        "This is a hidden niche for putting things in.\n");
    add_item(({"dirt", "brown dirt", "brown soil", "soil"}),
        "Dirt, dirt, dirt. Almost everywhere you look, it seems like " +
        "that is all you can see here. Brown and hard-packed, the soil fills " +
        "the ceiling, walls and floor.\n");
    add_item(({"door", "stone", "stone door", "fieldstone", "brown fieldstone"}),
        "This brown fieldstone is very large and it serves as a door " +
        "leading out from this secret chamber.\n");
    add_item(({"chamber", "room", "here", "hole", "cubby hole"}),
        "This is a cramped little cubby hole that someone has " +
        "hidden underneath this bridge. While the ceiling is low, " +
        "you realize that someone has dug out a fair bit of space " +
        "here. The room itself is quite dark, aside from whatever " +
        "light you are able to provide, and extremely empty. However, " +
        "you are fairly certain you could remain here undisturbed " +
        "for quite some time. There only exit here is the door you " +
        "came in from.\n");
    add_item(({"trapdoor"}),
        "This trapdoor seems to lead down into the inky darkness of the " +
        "earth below. It would probably be a good idea to take some " +
        "light with you before going down there.\n");
    
    add_exit(THIS_DIR + "ban1", "out");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    reset_room();
}

void

init()
{
    ::init();
    add_action("do_lift","lift");
}

int
do_lift(string str)
{
if(!str)
{
write("Lift what?\n");
return 1;
}
    if((str != "trapdoor"))
{ write("Lift what?\n");
return 1;
}
write("You quickly lift up the trapdoor and climb down into the " +
    "dark tunnel below.\n");
SAYBB(" lifts up a trapdoor in the floor and disappears into the darkness");
TP->move_living("M",THIS_DIR + "ban3",1,0);
SAYBB(" arrives climbing down from above.");
return 1;
}

public string
do_search(object pl, string arg)
{
    if (member_array(arg,
        ({ "floor", 
           "ground", 
        }) ) == -1)
    {
        return "Your search reveals nothing special.\n";
    }

    return "Digging through the dirt on the ground, you notice one part " +
        "is unusually hard! This appears to be a trapdoor! You can " +
        "easily lift it open.\n";

}
