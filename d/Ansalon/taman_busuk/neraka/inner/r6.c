/* Ashlar, 4 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_OUT;

void
create_neraka_room()
{
    set_short("on the Queen's Way, beside the White Gate");
    set_extra_long("You are walking along the Queen's Way, " +
        "just southeast of the White Gate. The street leads south " +
        "and northeast, flanked on both sides by the tall city walls.");

    add_item_citywalls();
    add_item_street1();
    add_item(({"gate","white gate"}),"The White Gate stands to the " +
        "northwest, leading out of the city. The gate is set in between " +
        "two tall massive towers.\n");
    add_item(({"towers","tower","tall towers","massive towers"}),
        "Two tall massive towers stand on each side of the White Gate. " +
        "The towers are quite a bit taller than the walls.\n");

    add_exit(NOUTER + "white/tunnel", "northwest");
    add_exit(NINNER + "r7", "south");
    add_exit(NINNER + "r5", "northeast");
}


