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
        "around them. There is an entrance to a tent to the northeast. " +
        "A metal grating covers a pit in the ground here.");
    set_quarter(BLACK);

    add_item_camp();

    remove_item("tent");
    add_item(({"tent","canvas tent"}),"It is a canvas tent, big enough " +
        "for about five people. There is a flap covering the entrance.\n");
    add_item(({"flap","canvas flap","tent flap","entrance"}),
        "A flap covers the entrance to the tent, to keep the heat in " +
        "on cold nights.\n");
    add_item(({"grating","metal grating"}),"The metal grating covers " +
        "a pit in the ground, leading down into murky darkness.\n");
    add_item(({"pit","hole"}),"The pit leads down into murky darkness. " +
        "A foul smell comes from the hole.\n");

    add_exit(NOUTER+"black/b20","west");
    add_exit(NOUTER+"black/t3","northeast","@@msg");
    add_exit(NOUTER+"black/b23","south");
    add_exit(NOUTER+"pens/p1","down","@@grating",1,1);
}

int
grating()
{
	write("You pull the grating aside and jump down into the pit.\n");
    return 0;
}

int
msg()
{
	write("You pull aside the flap and enter the tent.\n");
    return 0;
}

