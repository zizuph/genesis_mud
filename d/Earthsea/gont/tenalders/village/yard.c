/*
 * coded by Amelia 6/1/97
 * path through Ten Alders
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/gont/tenalders/std/base_herb_room";

#include "defs.h"
#include "/d/Earthsea/herbs/herb_sets/garden_herbs.h"

public void
create_herb_room()
{
    set_short("Yard outside a cottage");
    set_long("You find yourself in a small yard outside " +
        "a pleasant little stone cottage that is just to the north. " +
        "There are herbs planted around the border and a " +
        "small aspen tree in the middle.\n");
    add_item("yard", "Set a little aside from the village " +
        "path, the yard is just to the south of a small cottage.\n");
    add_item((({ "herbs", "border" })),
        "Flowers planted around the borders of the yard and " +
        "next to the cottage make it a very pleasant scene.\n");
    add_item((({ "cottage", "stone cottage" })),
        "A very small stone cottage with a thatch roof stands " +
        "just to the north.\n");
    add_item((({ "tree", "aspen tree" })),
        "This is an aspen tree, which is too small to climb.\n");
    set_up_herbs(select_herb_files(GARDEN_HERBS), GARDEN_LOCATIONS, 3);
    add_herb_file("/d/Earthsea/herbs/herb_files/aspen_bark");
    add_item((({"huts", "thatch-covered huts"})),
        "There are a number of small thatch-covered huts " +
        "that comprise this small village.\n");
    add_exit("se3", "west");
    clone_object("/d/Earthsea/gont/tenalders/obj/doors/cottage_out")->move(
        this_object());
}
