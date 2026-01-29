/* wagons.c
 * Ashlar, 28 Jul 97
 * This is the wagon administration for Neraka.
 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <files.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

#define DEBUG(x)    (find_player("ashlar")->catch_msg("NWAGON: " + x + "\n"))

mapping wagons =
    ([ "sanction" : ({ NERAKA + "caravan/", 0 }) ]);
#define AW_PATH 0
#define AW_OBJ  1

/* Prototypes */
void start_wagon(string s);
void monitor_status();

void
create_room()
{
    set_short("Wagon Admin");
    set_long("This is the administration object of Neraka Wagons.\n");
    // monitor_status will start the wagonrides and other periodic running
    // things. I delay it for 60 seconds so it won't slow down the reboot.
    set_alarm(10.0, 60.0, monitor_status);
}

/*
 * Function name: start_wagon
 * Description:   Starts a wagonride
 * Arguments:     string s - the id of the wagonride to start
 */
void
start_wagon(string s)
{
    object w;
    mixed *data;

    data = wagons[s];
    if (!pointerp(data))
    {
        return;
    }

    w = clone_object(data[AW_PATH] + "wagon");
    if (!objectp(w))
    {
        return;
    }

    NERAKA_ADMIN->adminlog("Starting the wagon '" + s + "'");
    data[AW_OBJ] = w;
    w->start_moving();
}

/*
 * Function name: query_wagon
 * Description:   Checks the wagon object for the indicated ride
 * Arguments:     string s - the id of the wagonride
 * Returns:       The wagon obj
 */
object
query_wagon(string s)
{
    mixed *data;

    data = wagons[s];
    if (!pointerp(data))
        return 0;
    else
        return data[AW_OBJ];
}

/*
 * Function name: monitor_status
 * Description:   Internal function to monitor the status of Neraka, and to
 *                make sure things are running smoothly.
 */
void
monitor_status()
{
    if (!objectp(query_wagon("sanction")))
        start_wagon("sanction");
}

