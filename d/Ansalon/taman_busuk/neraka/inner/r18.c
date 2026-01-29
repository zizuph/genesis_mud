/* Ashlar, 19 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_OUT;

void
create_neraka_room()
{
    set_short("on the Queen's Way, beside the Red Gate");
    set_extra_long("You are walking along the Queen's Way, " +
        "just north of the Red Gate. The street leads northeast " +
        "and west, flanked on both sides by the tall city walls. " +
        "An archway leads north through the city wall.");

    add_item_citywalls();
    add_item_street1();
    add_item(({"gate","red gate"}),"The Red Gate stands to the " +
        "south, leading out of the city. The gate is set in between " +
        "two tall massive towers.\n");
    add_item(({"towers","tower","tall towers","massive towers"}),
        "Two tall massive towers stand on each side of the Red Gate. " +
        "The towers are quite a bit taller than the walls.\n");
    add_item("archway","The archway is the entrance to a short tunnel " +
        "through the city wall.\n");
    add_item(({"tunnel","short tunnel"}),
        "The short tunnel leads through the city wall.\n");
        
    add_exit(NOUTER + "red/tunnel", "south");
    add_exit(NINNER + "r19", "northeast");
    add_exit(NINNER + "r17", "west");
    add_exit(NINNER + "g4", "north");
}


