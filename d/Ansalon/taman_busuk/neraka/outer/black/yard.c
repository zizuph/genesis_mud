/* Ashlar, 4 Jun 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("Yard outside an inn");
    set_extra_long("You are standing in a yard outside the Black Ship " +
        "Inn. The entrance to the inn is to the east, and a stable lies " +
        "to the southeast. To the north is a small dirt road. ");
    set_quarter(BLACK);

    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();
    add_item(({"inn","black ship inn","building"}),
        "The inn is a large, one-story building built together with a " +
        "stable.\n");
    add_item("stable","The stable is to the southeast.\n");
    add_item(({"entrance","entrance to inn"}),
        "The entrance to the inn is to the east.\n");

    add_exit(NOUTER+"black/inn","east");
	add_exit(NOUTER+"black/stable","southeast");
    add_exit(NOUTER+"black/b15","north");
}

int
stable()
{
	write("The stable is closed.\n");
    return 1;
}

