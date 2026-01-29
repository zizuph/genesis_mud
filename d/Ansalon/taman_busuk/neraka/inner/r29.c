/* Ashlar, 20 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_OUT;

void
create_neraka_room()
{
    set_short("on the Queen's Way, beside the Black Gate");
    set_extra_long("You are walking along the Queen's Way, " +
        "just west of the Black Gate. The street leads northwest " +
        "and south, flanked on both sides by the tall city walls.");

    add_item_citywalls();
    add_item_street1();
    add_item(({"gate","black gate"}),"The Black Gate stands to the " +
        "east, leading out of the city. The gate is set in between " +
        "two tall massive towers.\n");
    add_item(({"towers","tower","tall towers","massive towers"}),
        "Two tall massive towers stand on each side of the Black Gate. " +
        "The towers are quite a bit taller than the walls.\n");

    add_exit(NOUTER + "black/tunnel", "east");
    add_exit(NINNER + "r30", "northwest");
    add_exit(NINNER + "r28", "south");
}


