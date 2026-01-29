#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include ARND_MEET

/* Ashlar */

inherit OUTER_OUT;

object sarge, soldier1, soldier2, soldier3;

void
reset_neraka_room()
{
	if (!objectp(soldier3))
        soldier3 = clone_npc(GET_RANDOM_NAME(NT_OUTERSOLDIER),"blue");
	if (!soldier2)
        soldier2 = clone_npc(GET_RANDOM_NAME(NT_OUTERSOLDIER),"blue");
	if (!soldier1)
        soldier1 = clone_npc(GET_RANDOM_NAME(NT_OUTERSOLDIER),"blue");
    if (!sarge)
    {
    	sarge = clone_npc(NNPC + "humsergeant","blue");
        sarge->start_patrol();
        sarge->set_patrol_time(30);
        sarge->set_patrol_path(({"w","s","s","sw","sw","ne","ne",
            "n","n","e"}));
    }
}

void
create_neraka_room()
{
	set_short("market square in Blue Quarter");
    set_extra_long("You are at the west end of the market square. The square " +
        "continues to the east, and roads branch off to the north and west. " +
        "The market square is crowded with merchants and various people " +
        "perusing the stalls and goods.");
    set_quarter(BLUE);

    add_item_sidewalks();
    add_item_buildings();
    add_item_market("square");

    add_exit(NOUTER+"blue/b9","north");
    add_exit(NOUTER+"blue/b12","east");
    add_exit(NOUTER+"blue/b13","southeast");
    add_exit(NOUTER+"blue/b5","west");

    reset_room();
}


