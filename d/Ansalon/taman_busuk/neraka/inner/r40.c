/* Ashlar, 20 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_OUT;

void
create_neraka_room()
{
    set_short("on the Queen's Way");
    set_extra_long("You are walking along the Queen's Way, the main street " +
        "of Neraka. The street leads southeast and north, flanked on both " +
        "sides by the tall city walls. To the southwest, an archway leads " +
        "through the city wall.");

    add_item_citywalls();
    add_item_street1();
    add_item("archway","The archway is the entrance to a short tunnel " +
        "through the city wall.\n");
    add_item(({"tunnel","short tunnel"}),
        "The short tunnel leads through the city wall.\n");

    add_exit(NINNER + "r39", "north");
    add_exit(NINNER + "r41", "southeast");
    add_exit(NINNER + "g3", "southwest");
}


