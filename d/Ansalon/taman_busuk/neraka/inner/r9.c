/* Ashlar, 6 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_OUT;

void
create_neraka_room()
{
    set_short("on the Queen's Way");
    set_extra_long("You are walking along the Queen's Way, the main street " +
        "of Neraka. The street leads south and north, flanked on both " +
        "sides by the tall city walls. A small alley leads west right up " +
        "to the city wall.");

    add_item_citywalls();
    add_item_street1();

    add_exit(NINNER + "r8", "north");
    add_exit(NINNER + "r10", "south");
    add_exit(NINNER + "al1", "west");
}


