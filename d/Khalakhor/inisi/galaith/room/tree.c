/**********************************************************************
 * - tree.c                                                         - *
 * - entrance to tree                                               - *
 * - Created by Damaris 03/2001                                     - *
 * - Recoded by Damaris 2/2002                                      - *
 * - Updated by Valen 2/2002                                        - *
 **********************************************************************/ 
 
#pragma strict_types

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/basic.h"
inherit "/d/Khalakhor/std/room";

public void
create_khalakhor_room()
{
    set_short("Inside a strange tree");

    set_long("   Inside a strange looking tree. There are small "+
      "openings that lead off in various directions. The walls are "+
      "made of bark and there is what looks like a stairway made of "+
      "vines and limbs spiraling downward.\n");
    
    add_item(({"walls", "wall"}),
        "The walls are simply made from bark and there is a mysterious " +
        "light emanating from it.\n");

    add_item(({"bark"}),
        "The bark looks unusual from the inside. " +
        "Perhaps if you pushed on it.\n");

    add_item(({"light"}),
        "It seems to emanate from the walls.\n");

    add_item(({"floor","ground"}),
        "The floor on which you are standing seems very firm, and is " +
        "made from the tree. It appears the tree has grown limbs " +
        "intertwine just to create the floor.\n");

    add_item(({"counter", "small counter", "wooden counter"}),
        "The small counter is made from the tree itself. It has " +
        "grown into a perfect counter with a few leaves growing out of " +
        "it in certain spots.\n");

    add_item(({"ceiling"}),
        "The ceiling is made from intertwining limbs.\n");   

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
  
    add_exit("bank", "north");
    add_exit("pub", "east");
    add_exit("shop", "west");
    add_exit("pool", "down");
    add_exit("ashop", "northeast");
    add_exit("wshop", "northwest");
    add_exit("post2", "southeast");
    
}
int
push_bark(string str)
{
    if (str != "bark")
    {
        return notify_fail("Push what?\n");
    }

    write("You push on a piece of bark from inside the odd shaped tree " +
        "and suddenly you're pulled outside.\n");

    say(QCTNAME(TP) + " pushes on some bark and is pulled " +
        "out of the tree.\n");

    TP->move_living("M", ROOM + "isl0505", 1, 0);

    say(QCTNAME(TP)+" suddenly appears.\n");

    return 1;
}

void
init()
{
    ::init();

    add_action(push_bark, "push");

}
