#include "/d/Ansalon/common/defs.h"
#include "../local.h"

/* Ashlar, 11 Jun 97 */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("market square in the White Quarter");
    set_extra_long("You are in the middle of the market square in the White " +
        "Quarter. Shops line the square, and other merchants wander around, " +
        "hawking their wares. To the northwest is a small shack, and a " +
        "larger building is to the south.");
    set_quarter(WHITE);

    add_item_market("square");
    add_item_sidewalks();
    add_item_buildings();
    add_item(({"shack","small shack"}),"The small shack to the northwest " +
        "is constructed of some loose boards. It looks like it could fall " +
        "apart at any moment.\n");
    add_item(({"large building","larger building","south building",
        "building to the south"}),
        "The building to the south seems to house some sort of tavern.\n");

    add_exit(NOUTER+"white/w5","north");
    add_exit(NOUTER+"white/w15","east");
    add_exit(NOUTER+"white/w7","southeast");
    add_exit(NOUTER+"white/pub","south","@@go_s");
    add_exit(NOUTER+"white/w10","southwest");
    add_exit(NOUTER+"white/w17","west");
    add_exit(NOUTER+"white/scarfs", "northwest", "@@go_nw");
}

int
go_nw()
{
    write("You enter a small shack.\n");
    return 0;
}

int
go_s()
{
    write("The door is locked and as you rattle the handle, a voice " +
        "on the other side shouts: The tavern is closed for repairs!\n");
    return 1;
}
