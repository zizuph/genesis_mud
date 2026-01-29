/* Ashlar, 20 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_OUT;

void
create_neraka_room()
{
    set_short("on the Queen's Way");
    set_extra_long("You are walking along the Queen's Way, the main street " +
        "of Neraka. The street leads south and north, flanked on both " +
        "sides by the tall city walls. There is a low stone building to the " +
        "west.");

    add_item_citywalls();
    add_item_street1();

    add_item(({"building","low building","stone building","bank"}),
        "The building to the west is fortified with iron bars in the " +
        "windows and a heavy door. Golden letters over the door proclaim " +
        "it to be the Bank of Neraka.\n");
    add_item(({"window","windows"}),"The windows of the bank are fortified " +
        "with thick iron bars.\n");
    add_item(({"bars","iron bars","thick iron bars","thick bars"}),
        "The thick iron bars help protect the bank from burglary.\n");
    add_item(({"door","heavy door"}),"The heavy door is reinforced with " +
        "iron, making it very sturdy and resistant to violence.\n");

    add_exit(NINNER + "r38", "north");
    add_exit(NINNER + "r40", "south");
    add_exit(NINNER + "bank", "west", "@@go_bank");
}

int
go_bank()
{
    write("You step into the bank.\n");
    return 0;
}
