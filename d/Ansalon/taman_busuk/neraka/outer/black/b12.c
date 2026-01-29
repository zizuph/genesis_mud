#include "/d/Ansalon/common/defs.h"
#include "../local.h"

/* Ashlar, 21 May 97 */

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
	set_short("Dirt road in Black Quarter, outside a guard tower");
    set_extra_long("You are walking on a dirt road in the Black Quarter. " +
        "The road leads northwest and southeast. " +
        "A guard tower stands to the northeast, keeping a solitary vigil " +
        "here at the entrance to the Black Quarter. " +
        "There are wooden sidewalks along the roads " +
        "here, since the roads are often used for wagons and horses.");
    set_quarter(BLACK);

    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();
    add_item(({"tower","guard tower"}),
        "The guard tower stands here at the entrance to the Black Quarter.\n");

    add_exit(NOUTER+"black/b11","southeast");
    add_exit(NOUTER+"main/r4","northwest");
    add_exit(NOUTER+"black/tow1","northeast");

    reset_room();
}

