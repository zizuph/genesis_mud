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
        "sides by the tall city walls. There is an entrance to a low " +
        "building to the west.");

    add_item_citywalls();
    add_item_street1();

    add_item(({"building","low building","shop"}),
        "The building to the west seems to house some sort of a shop.\n");
    add_item(({"entrance","entrance to shop"}),
        "The entrance leads west into the low building.\n");

    add_exit(NINNER + "r7", "north");
    add_exit(NINNER + "r9", "south");
    add_exit(NINNER + "gshop", "west", "@@go_shop");
}

int
go_shop()
{
    write("You step inside the low building.\n");
    return 0;
}
