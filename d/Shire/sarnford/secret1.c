/*
 * Road between Greenway and Sarn Ford
 * Varian - February 2015
 */

#pragma save_binary
#pragma strict_types

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <state_desc.h>

inherit "/d/Shire/std/room";
inherit "/d/Shire/lib/inn";
inherit "/d/Gondor/common/lib/time.c";
inherit "/d/Shire/lib/herbsearch";

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
        "The ceiling here is made of dirt, cleaverly packed and " +
        "supported by some wooden beams.\n");
    add_item(({"wall", "walls"}),
        "All of the walls here look the same, they are just packed " +
        "dirt, with the occasional wooden post that helps to support " +
        "the ceiling beams above your head.\n");
    add_item(({"floor", "down"}),
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
    
    add_exit(SARNFORD_DIR + "wroad2.c", "out");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);

}
