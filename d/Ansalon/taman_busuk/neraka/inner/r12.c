/* Ashlar, 5 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_OUT;

void
create_neraka_room()
{
    set_short("on the Queen's Way");
    set_extra_long("You are walking along the Queen's Way, the main street " +
        "of Neraka. The street leads south and north, flanked on both " +
        "sides by the tall city walls. There is an entrance to a " +
        "building to the west.");

    add_item_citywalls();
    add_item_street1();

    add_item(({"building","smithy"}),
        "Judging by the sounds coming from the building to the west, you " +
        "guess it is a smithy.\n");
    add_item(({"entrance","entrance to shop"}),
        "The entrance leads west into what looks like a smithy.\n");

    add_exit(NINNER + "r11", "north");
    add_exit(NINNER + "r13", "south");
    add_exit(NINNER + "smith", "west", "@@go_smithy");
}

int
go_smithy()
{
    write("A wave of heat greets you as you enter the building.\n");
    return 0;
}
