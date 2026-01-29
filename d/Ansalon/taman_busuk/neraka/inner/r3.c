/* Ashlar, 4 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_OUT;

void
create_neraka_room()
{
    set_short("on the Queen's Way");
    set_extra_long("You are walking along the Queen's Way, the main street " +
        "of Neraka. The street leads southwest and northeast, flanked on both " +
        "sides by the tall city walls. There is an entrance to a tall " +
        "building to the north.");

    add_item_citywalls();
    add_item_street1();

    add_item(({"building","tall building","inn"}),
        "You can hear laughter and music coming from the tall building. A " +
        "sign hangs above the entrance.\n");
    add_item(({"entrance","entrance to inn"}),
        "The entrance leads north into the tall building.\n");
    add_item("sign","@@sign");
    add_cmd_item("sign","read","@@sign");

    add_exit(NINNER + "r2", "northeast");
    add_exit(NINNER + "r4", "southwest");
    add_exit(NINNER + "inn1", "north", "@@go_inn");
}

string
sign()
{
    return "The sign reads:\n" +
        "+-------------------------+\n" +
        "|The Swan and Hedgehog Inn|\n" +
        "|     Food and Drinks     |\n" +
        "|  No goblins No dracos   |\n" +
        "+-------------------------+\n";
}

int
go_inn()
{
    write("You enter the inn.\n");
    return 0;
}
