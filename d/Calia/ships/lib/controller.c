/*
 * Genesis Ship Controller
 *
 * This controller communicates with the piers and ships and
 * allows the holder to check the status as well as restart
 * the ships safely.
 *
 * Created by Petros, March 2009
 */
 
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <language.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <state_desc.h>
#include <cmdparse.h>
#include "ship.h"

// Prototypes
public int  list_ships(string arg);
public int  ship_info(string arg);
public int  restart_ship(string arg);

public string
query_recover(void)
{
    return 0;
}

/*
 * Function name: query_auto_load
 * Description  : Returns the path to this object
 * Returns      : string - the path.
 */
public string
query_auto_load(void)
{
    return MASTER;
}

/*
 * Function name: create_object
 * Description:   Create the object (Default for clones)
 */
private void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_name("genesis_ship_controller");
    add_name("_genesis_ship_controller");
    add_name("controller");
    add_name("ship controller");
    set_short("ship controller");
    set_long("Use this object to control ships.\n"
        + "Available Commands: \n"
        + "\tlist ships              - Lists all the ships that can be controlled\n"
        + "\tlist <domain> ships     - Lists all ships in a particular domain\n"
        + "\tshipinfo <num>          - Show information about a particular line\n"
        + "\tshipinfo <domain> <num> - Show information about a line in a domain\n"
        + "\trestart <num>           - Restarts a ship\n"
        + "\trestart <domain> <num>  - Restarts a shipline in a domain\n\n");

    add_prop(OBJ_I_VALUE, 1);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_NO_INS, 1);
    add_prop(OBJ_I_NO_STEAL, 1);    
}

/*
 * Function name: init
 * Description  : Add the 'command items' of this object. Note that if
 *                you redefine this function, the command items will not
 *                work unless you do ::init(); in your code!
 */
public void
init()
{
    ::init();

    add_action(list_ships,      "list");
    add_action(ship_info,       "shipinfo");
    add_action(restart_ship,    "restart");
}

// ========================= //
// Interface Functions Below //
// ========================= //

public int
list_ships(string arg)
{
    return SHIP_CONTROL_ROOM->list_ships(arg);
}

public int
ship_info(string arg)
{
    return SHIP_CONTROL_ROOM->ship_info(arg);
}

public int
restart_ship(string arg)
{
    return SHIP_CONTROL_ROOM->restart_ships(arg);
}
