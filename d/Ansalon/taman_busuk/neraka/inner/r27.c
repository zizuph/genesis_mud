/* Ashlar, 20 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_OUT;

void
create_neraka_room()
{
    set_short("on the Queen's Way");
    set_extra_long("You are walking along the Queen's Way, the main street " +
        "of Neraka. The street leads north and southeast, flanked on both " +
        "sides by the tall city walls. There is an entrance to a small " +
        "building to the east.");

    add_item_citywalls();
    add_item_street1();

    add_item(({"building","small building","shop"}),
        "The building to the east seems to house some sort of a shop.\n");
    add_item(({"entrance","entrance to shop"}),
        "The entrance leads east into the small building.\n");

    add_exit(NINNER + "r26", "southeast");
    add_exit(NINNER + "r28", "north");
    add_exit(NINNER + "wshop", "east", "@@go_shop");
}

int
go_shop()
{
    write("You step inside the small building.\n");
    return 0;
}
