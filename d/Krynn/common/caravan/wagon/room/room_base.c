/*
 *  Filename:       wagon/room/room_base.c
 *  Description     This is the base files for rooms around a caravan
 *                  wagon.
 *
 *  Copyright (c) Aug. 2003 by Daniel W. Mathiasen
 */
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/clock/clock.h"
#include "../wagon.h"
#include "/sys/language.h"
#include "/sys/macros.h"
#include "../wagon.h"

/* Inherit the Krynn room */
inherit OR_FILE

#define CREATE "create_wagon_room"
#define RESET  "reset_wagon_room"

int    gRoomType;

object myWagon;

/*
 * IN NORMAL CASES YOU SHOULDN'T NEED TO CHANGE ANYTHING BELOW
 */
public void
set_wagon(object wagon)
{
    myWagon = wagon;
}

public object
query_wagon()
{
    return myWagon;
}

public string
query_wagon_description()
{
    string desc;

    if (objectp(query_wagon()))
        desc = query_wagon()->long();
    else
        desc = "Unable to get the wagon long desc, this is a bug!\n";

    return desc;
}

/*
 * This function is called from the main Krynn room. It checks
 * weather or not the room should be reseted.
 * The function returns TRUE if there should be a reset.
 */
nomask public int
query_reset()
{
    if (function_exists(RESET, TO))
        return 1;
    return 0;
}

/*
 * Leaves the caravan.
 */

public int
leave_caravan(string str)
{

    if (str == "caravan" || str == "wagon")
    {
        write("You leave the caravan.\n");
        say(QCTNAME(TP) + " leaves the caravan.\n", TP);
        tell_room(E(query_wagon()), QCTNAME(TP) + " arrives from the caravan.\n");
        TP->move_living("M", E(query_wagon()) );
        return 1;
    }
    else
        return 0;

}

public int
enter_wagon(string str)
{

    if (str == "wagon")
    {
        if (!myWagon->check_enter_wagon())
            return 0;

        write("You enter the wagon.\n");
        say(QCTNAME(TP) + " enters the wagon.\n", TP);
        tell_room(query_wagon()->query_room(R_WAGON, M_OBJECT), QCTNAME(TP) + " enters the wagon.\n");
        TP->move_living("M", query_wagon()->query_room(R_WAGON, M_OBJECT) );
        return 1;
    }
    else
        return 0;

}


public int
burn_wagon(string str)
{
    return query_wagon()->burn_wagon(str);
}


public string
surroundings()
{
    string desc;

    if (objectp(E(myWagon)))
        desc = call_other(E(myWagon), "long");

    return desc;
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
create_krynn_room()
{

    add_item("wagon", "@@query_wagon_description@@");
    call_other(TO, CREATE);
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);
}

/*
 *  function:          make_connections
 *  description:       This function connects this room to the neighbour rooms
 *                      so the mortals can move forward, back, left and right
 */
static void
make_connections()
{

}

/*
 * function:        connect_rooms
 * description:     this is a stub function for make_connections, it is in place
 *                  so we can make nicer recursive calls.
 *
 *                  Boron: This function might be obsolete later, but for now it
 *                          makes the code slightly more readable ;-)
 */
public void
connect_rooms()
{
    set_alarm(0.0, 0.0, make_connections);
}

public string
long_desc(string longdesc)
{
    return longdesc;
}

varargs public mixed
long(string str)
{

    return ::long(str);
}

public void
init()
{
    ::init();

    add_action(leave_caravan, "leave");
    add_action(enter_wagon, "enter");
    set_dircmd("wagon");
    add_item("surroundings", "@@surroundings@@");
    add_action(burn_wagon, "burn");

}

