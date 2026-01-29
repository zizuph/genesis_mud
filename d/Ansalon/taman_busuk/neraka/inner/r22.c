/* Ashlar, 19 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_OUT;

void
create_neraka_room()
{
    set_short("on the Queen's Way, beside the Blue Gate");
    set_extra_long("You are walking along the Queen's Way, " +
        "just northwest of the Blue Gate. The street leads north " +
        "and southwest, flanked on both sides by the tall city walls.");

    add_item_citywalls();
    add_item_street1();
    add_item(({"gate","blue gate"}),"The Blue Gate stands to the " +
        "southeast, leading out of the city. The gate is set in between " +
        "two tall massive towers.\n");
    add_item(({"towers","tower","tall towers","massive towers"}),
        "Two tall massive towers stand on each side of the Blue Gate. " +
        "The towers are quite a bit taller than the walls.\n");

    add_exit(NOUTER + "blue/tunnel", "southeast");
    add_exit(NINNER + "r23", "north");
    add_exit(NINNER + "r21", "southwest");
}


