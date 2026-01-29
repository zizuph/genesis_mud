/*
 * Road leading to farm
 * By Finwe, August 2006
 */
 
#pragma strict_types
 
#include "/d/Faerun/defs.h"
#include "defs.h"

inherit BASE_FARM;

object ob;

void
create_farm_room()
{
    set_short("A quiet farm road");
    add_prop(ROOM_S_MAP_FILE, "farm_w_map.txt");

    set_extraline("The quiet road runs north and southwest. It cuts across " +
        "a wide meadow and past tall trees. Ruts run down the center of " +
        "the road from years of wagons using it.");

    set_add_road();
    reset_room();

    add_exit(FARM2_DIR + "rd02", "north");
    add_exit(HR_DIR + "srd01", "southwest");
}

void reset_room()
{
    ::reset_room();

    if ((ob))
    {
        return;
    }

    ob = clone_object(FNPC_DIR + "girl");
    ob->set_monster_home(FARM2_DIR + "rd01");
    ob->set_random_move(8);
    ob->set_restrain_path(FARM2_DIR);
    ob->move(this_object());

}
