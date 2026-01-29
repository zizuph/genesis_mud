/*
 * /d/Gondor/lebennin/wroad/cabin.c
 *
 */

#pragma strict_types

#include "/d/Gondor/lebennin/std/defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit LEBENNIN_STD_DIR + "base";

static object door;

public void
create_plains_room()
{
    set_short("Inside a small hunting cabin");
    set_long("The interior of the hunting cabin indicates a practical owner " +
        "A bed is placed in the corner, a solid butcher's block is set " +
        "underneath the only window. The walls are adorned with hunting " +
        "trophies.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_item("bed", "The bed is made from pine planks, and is decorated with " +
        "carvings depicting a herd of deer.\n");
    add_item("chair","Home-made, of wood. Quite rickety and old, actually.\n");
    add_item(({"floor","ground"}), "The floor is made of wide pine planks, " +
        "a dark path surrounds the floor underneath the butcher's block.\n");
    add_item("window", "A plate of glass is set into the south wall. You " +
        "can see the plains outside, and in the far distance you can " +
        "glimpse Ethir Anduin\n");
    add_item(({"butcher's block","block"}), "A solid chopping block made of " +
        "walnut wood, it looks like it has seen heavy use.\n");

    add_exit(AREA_DIR + "wroad/wr14", "out",  0, 1);
    set_no_exit_msg(get_all_no_exits(({})), 
        "The only exit from this cabin is out.\n");

    door = clone_object(AREA_DIR + "wroad/obj/cabin_door_in");
    door->move(this_object());

    add_npc(AREA_DIR + "wroad/npc/dolmien");
}
