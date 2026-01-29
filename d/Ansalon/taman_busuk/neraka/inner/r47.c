/* Ashlar, 20 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_OUT;

void
create_neraka_room()
{
    set_short("on the Queen's Way");
    set_extra_long("You are walking along the Queen's Way, the main street " +
        "of Neraka. The street leads north and south, flanked on both " +
        "sides by the tall city walls. There is a tall building to the " +
        "east.");

    add_item_citywalls();
    add_item_street1();

    add_item(({"building","tall building","post","post office"}),
        "The building to the east is tall and circular. It has a door " +
        "facing the street.\n");
    add_item(({"door"}),"The door leads into the building to the east.\n");

    add_exit(NINNER + "r46", "south");
    add_exit(NINNER + "r48", "north");
    add_exit(NINNER + "po", "east", "@@go_po");
}

int
go_po()
{
    write("You open the door and enter the building.\n");
    return 0;
}
