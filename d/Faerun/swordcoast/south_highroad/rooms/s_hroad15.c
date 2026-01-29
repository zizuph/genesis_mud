/*
* south_highroad/rooms/s_hroad01.c
* A room in the southern High Road, close to the City of Waterdeep
*
* Created Jan 2021 by Brine
* ---------
* CHANGELOG
* ---------
* August '21    Brine   Fixes to patrol_obj integration
*/

#pragma strict_types

#include "../defs.h"
#include "../mobiles/road_patrol.h"
#include <filter_funs.h>

inherit SOUTH_HIGHROAD_STD_ROOM;

int block_exit();
void clone_guards();

object *guards = allocate(NUM_GUARDS);
object patrol_controller;

void
create_shr_room()
{
    set_short("An old stone road before the city of Waterdeep");
    set_extraline(
        "You stand before an elevated plateau upon which lies the city of "
        + "Waterdeep. The road leads northwest and south, where it slopes up "
        + "towards the north gate."
    );

    set_area(ON_ROAD);
    set_road(HIGH_ROAD);

    add_waterdeep();
    add_item(
        ({ "gate", "massive gate", "north gate", "northgate", "Northgate" }),
        "It is a massive gate, clearly the main point of entry into Waterdeep "
        + "from the north. It is known as the \"North Gate\", or simply "
        + "\"Northgate\".\n"
    );

    add_exit(SOUTH_HIGHROAD_ROOM + "s_hroad14", "northwest");
    add_exit(WATERDEEP_LINK, "south", block_exit);

    reset_faerun_room();
}

int
block_exit()
{
    if (TP->query_wiz_level())
    {
        write("Wizards may pass.");
        return 0;
    }

    write(
        "A jet of sharp, blue flame shoots out from the ground in front of "
        + "you as you try to travel south! The mages of Waterdeep will likely "
        + "seal off this anomaly soon, but for now it is safest not to tangle "
        + "with it.\n"
    );
    return 1;
}

void
reset_faerun_room()
{
    ::reset_faerun_room();

    if (!patrol_controller)
    {
        patrol_controller = clone_object(WATERDEEP_DIR + "control/patrol_obj");
        patrol_controller->move(TO, 1);
        patrol_controller->register_patrol(PATROL_PATH, guards);
        patrol_controller->set_how_arrive_on_join("arrives running");
        clone_guards();
        patrol_controller->start_patrol();
        return;
    }

    if (sizeof(FILTER_LIVE(guards)) == 0)
        patrol_controller->reset_patrol();

    clone_guards();
}

void
clone_guards()
{
    for (int i = 0; i < NUM_GUARDS; i++)
    {
        if (!guards[i])
        {
            guards[i] = clone_object(WATERDEEP_DIR + "mobiles/guard_base");
            // higher rank to index 0, patrol leader
            int rank = i ? 0 : 1;
            guards[i]->set_rank(rank);
            patrol_controller->join_mobile(guards[i]);
        }
    }
}
