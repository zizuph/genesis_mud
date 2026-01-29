#pragma strict_types

#include "defs.h"

inherit TEMPLE + "std_dung.c";

void
create_temple_room()
{
    

    set_short("Standard prisoner cell");
    set_long("Room with basic items for the prisoner cells.\n");

    add_item(({"door", "small door"}),
        "This is a small wooden door which leads out of the cell.\n");

    add_item(({ "bed of straw", "bed"}),
        "This is a heap of straw shoved into a corner to form a crude " +
        "bed.\n");

    add_item(({ "straw", "heap of straw", "heap"}),
        "The straw is very dirty.\n");

    add_cmd_item(({ "bed if straw", "bed", "straw", "heap of straw", "heap" }),
        ({"touch", "feel"}), "The dirty straw is very damp.\n");

    add_cmd_item(({ "bed if straw", "bed", "straw", "heap of straw", "heap" }),
        "smell", "The straw wreaks of mold.\n");

    add_cmd_item(({"air", "cell", "room"}), 
        ({"smell", "sniff"}), "There is a distinct smell of damp mold in " +
        "the air.\n");
}
