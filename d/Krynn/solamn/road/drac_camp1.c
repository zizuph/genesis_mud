/* Aridor, 08/98 */

#include "local.h"

inherit ROOM_BASE
inherit CONQUER_BASE

string
current_army()
{
    return ARMYMASTER->army_in_area(AREA_NAME);
}

void
create_road_room()
{
    set_short("In a military camp");
    set_long("This seems to be a military campsite. You can see a " +
        "fireplace, and around it a cleared area. Currently, the " +
        "area is occupied by the @@current_army@@.\n");
    add_item(({"fire", "fireplace", "ashes", "pile"}),
        "The fireplace is nothing more than a pile of ashes.\n");
    add_item(({"plains", "plains of solamnia"}), "Spreading out before " +
        "you as far as the eye can see are the Eastern Plains of " +
        "Solamnia.\n");

    if (LOAD_ERR(ROAD_OBJECT))
    {
        write("Bug! please report immediately.\n");
	return;
    }

    add_exit("", "west", "@@enter_map:" + ROAD_OBJECT + "|C@@",6,1);
    add_exit("", "east", "@@enter_map:" + ROAD_OBJECT + "|C@@",6,1);
    add_exit("", "south","@@enter_map:" + ROAD_OBJECT + "|C@@",6,1);
    add_exit("", "north","@@enter_map:" + ROAD_OBJECT + "|C@@",6,1); 

    set_area_name(AREA_NAME);
    set_num_npc(5);
    set_npc_chance(1);
    reset();
}

void
init()
{
    init_conquer();
    ::init();
}

void
reset_road_room()
{
    reset_conquer_room();
}
