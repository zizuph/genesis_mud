#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include ARND_MEET

/* Ashlar */

/* Added connection to Templars of Takhisis in */
/* Krynn/guilds/templar/room/road1 - Louie */
inherit OUTER_OUT;

object d1;

void
reset_neraka_room()
{
    if (!objectp(d1))
        d1 = clone_npc(GET_RANDOM_NAME(NT_OUTER),"blue");
}

void
create_neraka_room()
{
	set_short("Dirt road in Blue Quarter");
    set_extra_long("You are walking on a dirt road in the Blue Quarter. " +
        "Going north would take you closer to the Black Quarter, and the " +
        "road also leads south. There are wooden sidewalks along the roads " +
    "here, since the roads are often used for wagons and horses.  " +
   "It appears a new path is being made to the east."+
"");
    set_quarter(BLUE);

    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();

    add_exit(NOUTER+"blue/b11","north");
    add_exit(NOUTER+"blue/b9","south");
   add_exit("/d/Krynn/guilds/templar/room/road1","east");

    reset_room();
}


