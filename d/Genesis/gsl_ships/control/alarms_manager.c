/*
 * Genesis ShipLines Alarm Manager
 *
 * Alarms are start and retrieved in this manager. This way, we can
 * load the other managers without affecting the running of ships.
 *
 * Created by Petros, April 2009
 */
 
#pragma no_clone
#pragma strict_types

#include <macros.h>
#include <money.h>
#include <files.h>
#include "../navigation.h"
#include "../ships.h"

// Prototypes
public void arrive_into_harbor(object ship, int pier_id);
public void place_regular_ship_in_sea(object ship, mixed *route, int stop_n, int pier_id);

/* 
 * Function:    create
 * Description: Set up the effective uids when this object is first
 *              created.
 */
public void
create()
{
    setuid();
    seteuid(getuid());
}

/*
 * Function:    set_arrive_into_harbor_alarm
 * Description: Use this function to set the alarm from the
 *              navigation manager.
 */
public int
set_arrive_into_harbor_alarm(object ship, int pier_id)
{
    return set_alarm(0.0, 0.0, &arrive_into_harbor(ship, pier_id));
}

/*
 * Function:    set_place_regular_ship_in_sea_alarm
 * Description: Use this function to set the alarm to place a ship in
 *              the ocean along its route.
 */
public int
set_place_regular_ship_in_sea_alarm(object ship, mixed *route, int stop_n, int pier_id)
{
    return set_alarm(STOP_TIME_AT_SEA, 0.0,
        &place_regular_ship_in_sea(ship, route, stop_n, pier_id));
}

public mixed *
retrieve_alarm(int alarmid)
{
    return get_alarm(alarmid);
}

// Wrapper functions used to call the same ones in the Navigation Manager

public void
arrive_into_harbor(object ship, int pier_id)
{    
    NAVIGATION_MANAGER->arrive_into_harbor(ship, pier_id);
}

public void
place_regular_ship_in_sea(object ship, mixed *route, int stop_n, int pier_id)
{    
    NAVIGATION_MANAGER->place_regular_ship_in_sea(ship, route, stop_n, pier_id);
}

/*
 * Function name: query_alarms
 * Description:   This function gives all alarms set in this object.
 * Returns:       The list as given by get_all_alarms.
 */
mixed
query_alarms()
{
    return get_all_alarms();
}
