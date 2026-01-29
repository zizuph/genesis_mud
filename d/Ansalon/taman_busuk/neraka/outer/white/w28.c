#include "/d/Ansalon/common/defs.h"
#include "../local.h"

/* Ashlar, 18 Aug 97 */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("In the White Army camp");
    set_extra_long("You are in the White Army camp. Tents are placed at " +
        "irregular intervals around the camp, leaving winding pathways " +
        "around them.");
    set_quarter(WHITE);
    add_item_camp();

    add_exit(NOUTER+"white/w26","northeast");
    add_exit(NOUTER+"white/w29","south");

}

