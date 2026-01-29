/* Ashlar, 4 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_OUT;

void
create_neraka_room()
{
    set_short("on the Queen's Way");
    set_extra_long("You are walking along the Queen's Way, the main street " +
        "of Neraka. The street leads south and northeast, flanked on both " +
        "sides by the tall city walls. West of here is a small building, " +
        "where you can see a lot of people coming and going.");

    add_item_citywalls();
    add_item_street1();
    add_item(({"building","small building"}),
        "The small building is built of black stone, and there are a lot " +
        "people going to and from the building.\n");

    add_exit(NINNER + "r3", "northeast");
    add_exit(NINNER + "r5", "south");
    add_exit(NINNER + "board", "west");
}


