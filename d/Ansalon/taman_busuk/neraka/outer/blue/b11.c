#include "/d/Ansalon/common/defs.h"
#include "../local.h"

/* Ashlar */

inherit OUTER_OUT;

object g1,g2;

void
reset_neraka_room()
{
    if (!objectp(g1))
        g1 = clone_npc(NNPC + "cityguard");
    if (!objectp(g2))
        g2 = clone_npc(NNPC + "cityguard");
}

void
create_neraka_room()
{
	set_short("Dirt road between Blue and Black Quarter");
    set_extra_long("You are walking on a dirt road, at the perimeter " +
        "between the Blue and the Black Quarter. A guard tower stands " +
        "to the northeast, keeping vigil over the perimeter. " +
        "There are wooden sidewalks along the roads " +
        "here, since the roads are often used for wagons and horses.");
    set_quarter(BLUE);

    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();
    add_item(({"tower","guard tower"}),"The guard tower rises above " +
        "the surrounding buildings.\n");

    add_exit(NOUTER+"black/b1","northwest");
    add_exit(NOUTER+"blue/tow1","northeast");
    add_exit(NOUTER+"blue/b10","south");

    reset_room();
}


