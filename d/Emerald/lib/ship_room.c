/*
 * /d/Emerald/lib/ship_room.c
 *
 * Use this in dock rooms to simplify the process of adding
 * and managing docks/ships.
 *
 * Example usage:
 * 
 * inherit "/d/Emerald/std/room";
 * inherit "/d/Emerald/lib/ship_room";
 *
 * void
 * create_emerald_room()
 * {
 *     ... room configuration code ...
 *     set_ship_file("/d/Emerald/area/ship");
 *     add_ship();
 * }
 */

#pragma strict_types

#include <stdproperties.h>

static object ship;
private string ship_file;

/*
 * Function name: add_ship
 * Description:   Clone the ship and get it started on its route.
 */
static void
add_ship()
{
    if (ship || !strlen(ship_file))
    {
        return;
    }

    setuid();
    seteuid(getuid());

    this_object()->add_prop(ROOM_I_NO_CLEANUP, 1);

    ship = clone_object(ship_file);
    ship->move(this_object());
    ship->start_ship();
}

/*
 * Function name: set_ship_file
 * Description:   Give the filename of the ship that should be cloned for
 *                this dock.
 */
static void
set_ship_file(string arg)
{
    ship_file = arg;
}

/*
 * Function name: query_ship
 * Returns:       The ship object that is registered here.
 */
public object
query_ship()
{
    return ship;
}

/*
 * Function name: query_ship_file
 * Returns:       The filename of the ship that starts here.
 */
public string
query_ship_file()
{
    return ship_file;
}

/*
 * Function name: remove_object
 * Description:   Remove the room
 */
public void
remove_object()
{
    if (ship)
    {
        throw("Cannot destruct room while ship is active.  " +
            "Use remove_ship_room() to override.\n");
        return;
    }

    destruct();
}

/*
 * Function name: remove_ship_room
 * Description:   Remove the room and the ship that's registered.
 */
public void
remove_ship_room()
{
    ship->query_captain()->remove_object();
    ship->remove_object();
    destruct();
}
