#include "/d/Ansalon/common/defs.h"
#include "../local.h"

/* Ashlar, 11 Jun 97 */

inherit OUTER_OUT;
inherit RANTEAM;

void
create_neraka_room()
{
	set_short("Dirt road in White Quarter");
    set_extra_long("You are walking on a dirt road in the White Quarter. " +
        "The road leads northeast and west. " +
        "There are wooden sidewalks along the roads " +
        "here, since the roads are often used for wagons and horses.");
    set_quarter(WHITE);

    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();

    add_exit(NOUTER+"white/w4","west");
    add_exit(NOUTER+"white/w2","northeast");

    set_team_size(2);
    set_random_table(NT_OUTER);

    reset_room();
}

