#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include ARND_MEET

/* Ashlar, 11 Jun 97 */

inherit OUTER_OUT;

object s1,s2,serg;

reset_neraka_room()
{
    if (!objectp(s1))
        s1 = clone_npc(GET_RANDOM_NAME(NT_OUTERSOLDIER),"white");
    if (!objectp(s2))
        s2 = clone_npc(GET_RANDOM_NAME(NT_OUTERSOLDIER),"white");
    if (!objectp(serg))
    {
        serg = clone_npc(NNPC + "humsergeant","white");
        serg->start_patrol();
        serg->set_patrol_time(30);
        serg->set_patrol_path(({"e","ne","ne","sw","sw","w","sw","s",
            "se","se","nw","nw","sw","sw","s","se","s","n","nw","n",
            "ne","ne","n","ne"}));
    }
}

void
create_neraka_room()
{
	set_short("Dirt road in White Quarter");
    set_extra_long("You are walking on a dirt road in the White Quarter. " +
        "The road leads east and southwest, where it meets a market square. " +
        "There are wooden sidewalks along the roads " +
        "here, since the roads are often used for wagons and horses.");
    set_quarter(WHITE);

    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();
    add_item_market("square");

    add_exit(NOUTER+"white/w5","southwest");
    add_exit(NOUTER+"white/w3","east");

    reset_room();
}

