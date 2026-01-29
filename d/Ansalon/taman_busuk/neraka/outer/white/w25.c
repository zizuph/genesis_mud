#include "/d/Ansalon/common/defs.h"
#include "../local.h"

/* Ashlar, 14 Jun 97 */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("In the White Army camp");
    set_extra_long("You are in the White Army camp. Tents are placed at " +
        "irregular intervals around the camp, leaving winding pathways " +
        "around them. There is an entrance to a tent to the northwest.");
    set_quarter(WHITE);
    add_item_camp();

    remove_item("tent");
    add_item(({"tent","canvas tent"}),"It is a canvas tent, big enough " +
        "for about five people. There is a flap covering the entrance.\n");
    add_item(({"flap","canvas flap","tent flap","entrance"}),
        "A flap covers the entrance to the tent, to keep the heat in " +
        "on cold nights.\n");

    add_exit(NOUTER+"white/t1","northwest","@@msg");
    add_exit(NOUTER+"white/w24","east");

}

int
msg()
{
	write("You pull aside the flap and enter the tent.\n");
    return 0;
}

