/* Ashlar, 20 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_OUT;

void
create_neraka_room()
{
    set_short("on the Queen's Way");
    set_extra_long("You are walking along the Queen's Way, the main street " +
        "of Neraka. The street leads east and west, flanked on both " +
        "sides by the tall city walls. A small alley leads south towards " +
        "the city wall.");

    add_item_citywalls();
    add_item_street1();
    add_item("alley","The small, narrow alley leads south in between " +
        "buildings.\n");

    add_exit(NINNER + "r41", "west");
    add_exit(NINNER + "r43", "east");
    add_exit(NINNER + "al2", "south");
}


