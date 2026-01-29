#include "/d/Ansalon/common/defs.h"
#include "../local.h"

/* Ashlar */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("Dirt road in Blue Army camp");
    set_extra_long("You are walking on a dirt road in the Blue Army camp. " +
        "There are a couple of tents to the south and southwest, and the " +
        "road leads northwest.");
    set_quarter(BLUE);

    add_item_dirtroad();
    add_item_camp();
    
    add_item(({"tent","canvas tent"}),"It is a canvas tent, big enough " +
        "for about five people. There is a flap covering the entrance.\n");
    add_item(({"flap","canvas flap","tent flap"}),"The flap covers the " +
        "entrance to the tent, to keep the heat in on cold nights.\n");

    add_exit(NOUTER+"blue/b16","northwest");
    add_exit(NOUTER+"blue/t3","south","@@msg");
    add_exit(NOUTER+"blue/t2","southwest","@@msg");
}

int
msg()
{
	write("You pull aside the flap and enter the tent.\n");
    return 0;
}

