/* Ashlar, 5 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_OUT;

void
create_neraka_room()
{
    set_short("on the Queen's Way, beside the Green Gate");
    set_extra_long("You are walking along the Queen's Way, " +
        "just northeast of the Green Gate. The street leads southeast " +
        "and north, flanked on both sides by the tall city walls. " +
        "An archway leads northeast through the city wall.");

    add_item_citywalls();
    add_item_street1();
    add_item(({"gate","green gate"}),"The Green Gate stands to the " +
        "southwest, leading out of the city. The gate is set in between " +
        "two tall massive towers.\n");
    add_item(({"towers","tower","tall towers","massive towers"}),
        "Two tall massive towers stand on each side of the Green Gate. " +
        "The towers are quite a bit taller than the walls.\n");
    add_item("archway","The archway is the entrance to a short tunnel " +
        "through the city wall.\n");
    add_item(({"tunnel","short tunnel"}),
        "The short tunnel leads through the city wall.\n");

    add_exit(NOUTER + "green/tunnel", "southwest");
    add_exit(NINNER + "r15", "southeast");
    add_exit(NINNER + "r13", "north");
    add_exit(NINNER + "g3", "northeast");
}


