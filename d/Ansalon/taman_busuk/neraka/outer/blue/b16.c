#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include ARND_MEET

/* Ashlar, 26 Jun 97 */

inherit OUTER_OUT;

object p1, p2, pl;

void
reset_neraka_room()
{
	if(!objectp(p1))
        p1 = clone_npc(GET_RANDOM_NAME(NT_OUTERSOLDIER),"blue");
    if(!objectp(p2))
        p2 = clone_npc(GET_RANDOM_NAME(NT_OUTERSOLDIER),"blue");
    if(!objectp(pl))
    {
    	pl = clone_npc(NNPC+"humsergeant","blue");
        pl->start_patrol();
        pl->set_patrol_time(30);
        pl->set_patrol_path(({"e","se","nw","w","se","nw","ne","sw",
            "nw","w","e","se"}));
    }
	
}

void
create_neraka_room()
{
	set_short("Dirt road in Blue Army camp");
    set_extra_long("You are walking on a dirt road in the Blue Army camp. " +
        "To the northwest the road leads to the market square. There is a " +
        "tent to the south, and the camp spreads out in the other " +
        "directions.");
    set_quarter(BLUE);

    add_item_dirtroad();
    add_item_camp();
    remove_item("tent");
    add_item(({"tent","canvas tent"}),"It is a canvas tent, big enough " +
        "for about five people. There is a flap covering the entrance.\n");
    add_item(({"flap","canvas flap","tent flap"}),"The flap covers the " +
        "entrance to the tent, to keep the heat in on cold nights.\n");

    add_exit(NOUTER+"blue/b15","northwest");
    add_exit(NOUTER+"blue/b17","northeast");
    add_exit(NOUTER+"blue/b18","east");
    add_exit(NOUTER+"blue/b20","southeast");
    add_exit(NOUTER+"blue/t1","south","@@msg");
    reset_room();
}

int
msg()
{
	write("You pull aside the flap and enter the tent.\n");
    return 0;
}

