/* Ashlar, 20 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_OUT;

void
create_neraka_room()
{
    set_short("in a small alley");
    set_extra_long("You are standing in a small alley. To the north is " +
        "the main street, and to the south an archway leads through the " +
        "city wall.");

    add_item_citywalls();
    add_item_street1();
    add_item("alley","The alley is filled with dirt and litter, and " +
        "more, judging by the smell.\n");
    add_item(({"dirt","litter"}),"You don't want to mess with that mess.\n");
    add_item("archway","The archway is the entrance to a short tunnel " +
        "through the city wall.\n");
    add_item(({"tunnel","short tunnel"}),
        "The short tunnel leads through the city wall.\n");

    add_exit(NINNER + "r32", "north");
    add_exit(NINNER + "g6", "south");
}


