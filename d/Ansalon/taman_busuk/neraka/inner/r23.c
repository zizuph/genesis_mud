/* Ashlar, 19 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_OUT;

void
create_neraka_room()
{
    set_short("on the Queen's Way");
    set_extra_long("You are walking along the Queen's Way, the main street " +
        "of Neraka. The street leads north and south, flanked on both " +
        "sides by the tall city walls. There is an entrance to a low " +
        "building to the east, and an archway leads west through the " +
        "city wall.");

    add_item_citywalls();
    add_item_street1();

    add_item(({"building","low building","shop"}),
        "The building to the east seems to house some sort of a shop.\n");
    add_item(({"entrance","entrance to shop"}),
        "The entrance leads east into the low building.\n");
    add_item("archway","The archway is the entrance to a short tunnel " +
        "through the city wall.\n");
    add_item(({"tunnel","short tunnel"}),
        "The short tunnel leads through the city wall.\n");
        
    add_exit(NINNER + "r22", "south");
    add_exit(NINNER + "r24", "north");
    add_exit(NINNER + "ashop", "east", "@@go_shop");
    add_exit(NINNER + "g5", "west");
}

int
go_shop()
{
    write("You step inside the low building.\n");
    return 0;
}
