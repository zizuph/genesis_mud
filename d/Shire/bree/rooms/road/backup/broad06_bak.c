/*
 * Road in Bree
 * By Finwe, June  2001
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h"
#include "defs.h"

inherit ROAD_BASE;

object human;

void
create_road_room()
{

    set_areadesc("large");
    set_area("busy");
    set_areaname("road");
    set_land("Bree");

    add_my_desc("The road winds northeast and south. East is a " +
        "square building. Houses line the road while a stone wall " +
        "runs along the western side of the road. Looking south and " +
        "west is a large inn.\n");

    add_item(({"prancing pony", "prancing pony inn", "the prancing pony", 
            "the prancing pony inn", "inn"}),
        "The large inn stands to the southeast. It is clearly one " +
        "of the biggest buildings in Bree.\n");
    add_item(({"square building", "adventurer's guild", "adventurers guild"}),
        "The square building is shorter than others in the town. A " +
        "sign swings from above the door.\n");
    add_item("sign", 
        "It is square and hangs above the door. A figure of a man, " +
        "straining and lifting a large boulder above his head, is " +
        "painted on the sign.\n");
    add_cmd_item("sign", "read", "@@read_sign@@");

    set_add_houses();
    set_add_hill();
    reset_shire_room();


    add_exit(ROAD_DIR + "broad07", "northeast");
    add_exit(ROAD_DIR + "broad02", "south");
    add_exit(TOWN_DIR + "adv_guild", "east");

}

string
read_sign()
{
    return "On the sign, above the figure of the man, painted in " +
        "bright silver letters are the words: 'Adventurers Guild " +
        "of Bree'.\n";
}

void
reset_shire_room()
{
    setuid();
    seteuid(getuid());

    if(!objectp(human))
    {
        human = clone_object(NPC_DIR + "human");
        human->move(TO);
        human->set_restrain_path("/d/Shire/bree");
        human->set_random_move(2);

    }
}
