#include "/d/Ansalon/common/defs.h"
#include "../local.h"
/* Ashlar, 14 Jun 97 */

inherit OUTER_OUT;
inherit RANTEAM;

void
create_neraka_room()
{
	set_short("dirt road in the White Quarter");
    set_extra_long("You are walking on a dirt road in the White Quarter. " +
        "The road leads west towards the army camp " +
        "and east towards a market square. " +
        "There are wooden sidewalks along the roads " +
        "here, since the roads are often used for wagons and horses.");
    set_quarter(WHITE);

    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();
    add_item_market("square");
    add_item(({"camp","army camp"}),
        "The army camp is spread out west of here.\n");

    add_exit(NOUTER+"white/w17","east");
    add_exit(NOUTER+"white/w19","west");

    set_team_size(2);
    set_random_table(NT_OUTER);

    reset_room();
}

