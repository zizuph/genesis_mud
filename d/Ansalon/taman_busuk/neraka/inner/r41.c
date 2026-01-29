/* Ashlar, 20 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_OUT;

void
create_neraka_room()
{
    set_short("on the Queen's Way");
    set_extra_long("You are walking along the Queen's Way, the main street " +
        "of Neraka. The street leads east and northwest, flanked on both " +
        "sides by the tall city walls. There is an entrance to a fancy " +
        "building to the south.");

    add_item_citywalls();
    add_item_street1();

    add_item(({"building","fancy building","shop"}),
        "The building to the south seems to house some sort of a shop. " +
        "It is richly decorated, and reeks of wealth.\n");
    add_item(({"entrance","entrance to shop"}),
        "The entrance leads south into the fancy building.\n");
        
    add_exit(NINNER + "r40", "northwest");
    add_exit(NINNER + "r42", "east");
    add_exit(NINNER + "shop", "south", "@@go_shop");
}

int
go_shop()
{
    write("A small bell above the door jingles as you enter the shop.\n");
    return 0;
}
