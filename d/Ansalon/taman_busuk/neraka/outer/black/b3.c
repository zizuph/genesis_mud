#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include ARND_MEET

/* Ashlar, 19 May 97 */

inherit OUTER_OUT;

object d1;

void
reset_neraka_room()
{
    if (!objectp(d1))
        d1 = clone_npc(GET_RANDOM_NAME(NT_OUTER),"black");
}

void
create_neraka_room()
{
	set_short("Dirt road junction in Black Quarter");
    set_extra_long("You stand at a junction of two dirt roads in the Black " +
        "Quarter. The main road leads north and south, while another road " +
        "branches off to the northeast. " +    
        "There are wooden sidewalks along the " +
        "roads here, since the roads are often used for wagons and horses.");
    set_quarter(BLACK);

    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();
    add_item("junction","It is a three-way junction, with roads leading " +
        "north, northeast and south.\n");

    add_exit(NOUTER+"black/b4","north");
    add_exit(NOUTER+"black/b14","northeast");
    add_exit(NOUTER+"black/b2","south");

    reset_room();
}

