/*
* fieldward/rooms/northgate.c
* This is the northgate, the main northern entrance into the city of Waterdeep
*
* Created Feb 2022 by Brine
*/

#pragma strict_types

#include "../defs.h"
#include <macros.h>

inherit FIELDW_STD_ROOM;
#include "../objects/northgate_gate_functions.o"


private object gate;
int test_gate();

void
create_fieldward_room()
{
    set_short("Waterdeep, at the Northgate");
    set_extraline(
        "You stand before the Northgate, the main northern entrance into "
        + "the bustling, cosmopolitan metropolis that is Waterdeep. This "
        + "imposing gatehouse fortifies the gateway that grants passage "
        + "through the outer wall and into the city to the south. To "
        + "the northeast, the High Road slopes down towards a fork in the "
        + "road.\n"
    );

    set_area(OUTSKIRTS);
    set_road_type(HIGH_ROAD);
    add_in_waterdeep();
    add_northgate();
    add_outer_wall();
    add_plateau();

    add_exit(FIELDW_ROOM + "fork", "northeast");
    add_exit(FIELDW_ROOM + "northyard", "south", test_gate);
}

int
test_gate()
{
    if (!gate)
    {
        LOAD_ERR(FIELDW_OBJ + "northgate_gate");
        gate = find_object(FIELDW_OBJ + "northgate_gate");
        gate->setup_gate();
    }

    if (gate->query_open())
    {
        write(
            "You pass through the " + gate->query_short() + ".\n"
        );
        return 0;
    } else {
        write("The " + gate->short() + " is closed.\n");
        return 1;
    }
}

int
do_knock(string arg)
{
    notify_fail("Knock on what?\n");
    if (!stringp(arg))
        return 0;

    gate->set_open(gate->query_open() ? 0 : 1);
    write("You knock, yo.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_knock, "knock");
}
