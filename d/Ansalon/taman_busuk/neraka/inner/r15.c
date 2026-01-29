/* Ashlar, 5 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_OUT;

void
create_neraka_room()
{
    set_short("on the Queen's Way");
    set_extra_long("You are walking along the Queen's Way, the main street " +
        "of Neraka. The street leads southeast and northwest, flanked on both " +
        "sides by the tall city walls. There is an entrance to a " +
        "building to the south, from which you hear laughter and the " +
        "clinking of cups. A sign hangs above the entrance.");

    add_item_citywalls();
    add_item_street1();

    add_item(({"building","tavern"}),
        "You hear drunken laughter coming from the building to the south.\n");
    add_item(({"entrance","entrance to tavern"}),
        "The entrance leads south into a building.\n");
    add_item("sign","@@sign");
    add_cmd_item("sign","read","@@sign");
    
    add_exit(NINNER + "r14", "northwest");
    add_exit(NINNER + "r16", "southeast");
    add_exit(NINNER + "pub1", "south", "@@go_pub");
}

string
sign()
{
    return "The sign reads:\n" +
        "+---------------------+\n" +
        "|The Red Dragon Tavern|\n" +
        "|    Cheap Drinks!    |\n" +
        "+---------------------+\n";
}

int
go_pub()
{
    write("You enter the building and walk down a few steps.\n");
    return 0;
}

