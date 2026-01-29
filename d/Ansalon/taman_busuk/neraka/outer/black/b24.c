#include "/d/Ansalon/common/defs.h"
#include "../local.h"

/* Ashlar, 24 May 97 */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("In the Black Army camp");
    set_extra_long("You are in the Black Army camp. Tents are placed at " +
        "irregular intervals around the camp, leaving winding pathways " +
        "around them.");
    set_quarter(BLACK);

    add_item_camp();

    add_exit(NOUTER+"black/b23","north");
    add_exit(NOUTER+"black/b21","west");
    add_exit(NOUTER+"black/b25","south");

}

