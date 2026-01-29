#pragma strict_types

#include "locals.h"

inherit "/d/Krynn/std/room.c";

public int conquer_area(string args);
public void init();

/*
 * Function name: create_krynn_room
 * Description:   Called to construct a room in Krynn. Read 'kman room.doc'
 *                to see how this is used in your area.
 */
public void
create_krynn_room()
{
    restore_object(HISTORY_MASTER);
    set_short("The history test room");
    set_long("\nThe history test room.\n"
            + "You can 'conquer <areaName> <loosingTroops> <conuqeringTroops>'\n");

}

public void
init()
{
    add_action(conquer_area, "conquer", 1);
    ::init();
}

/*
 * Function name: reset_krynn_room
 * Description:   This is called periodically in the room to
 *                reset it.
 */
public void
reset_krynn_room()
{
}



////////////////////////////////////////
// Functions for presenting data

public int
conquer_area(string args)
{
    string area;
    string oldArmy;
    string newArmy;

    sscanf(args, "%s %s %s", area, oldArmy, newArmy);

    write(area + " " + oldArmy + " " + newArmy + "\n");

    HISTORY->conquered_area(area, oldArmy, newArmy, (HISTORY->query_conquer_time()), 100, 150);
    return 1;
}
