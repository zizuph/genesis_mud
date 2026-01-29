#pragma strict_types
#include "/d/Avenir/common/common.h"
#include "./defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>

inherit "/std/room";
int gate();

void
create_room()
{
    set_short("A small path");
    set_long("You are standing right behind the opening in " +
        "the hedge. The path follows a straight direction " +
        "eastwards through some trees and its seems to slope " +
        "down a bit.\n");
    add_item("trees","You look at the trees. " +
        "Pines without doubt. They grow quite narrow, so " +
        "from here its impossible see further east.\n");
    add_item("path","You feel the small path between your feet. It has " +
        "not been used during the last years and its all cowered with pine " +
        "needles.\n");
    add_item("pines", "Normal pines, tall and proud, grow close to the path.\n");
    add_item(({"needles","pine needles"}),"You kneel down and take a handful " +
        "of the pine needles. They are brown and dry and you let them slowly " +
        "glide through your fingers down on the path again.\n");
    add_item("gate","Hidden in the hedge is a small iron gate. The gate has " +
        "no lock so its easy to push it open to get back to the yard outside " +
        "the farm house.\n");
    add_exit("east_side","west","@@gate");
    add_exit("track2","east");
    reset_room();
}

void
reset_room()
{

}

int
gate()
{
    object east_side;

    east_side = find_object(THIS_DIR + "east_side");
    if (!(east_side->query_gate_open()))
    {
        tell_room(east_side, "The gate in the hedge swing open.\n");
        east_side->do_open_gate();
}
    return 0;
}
