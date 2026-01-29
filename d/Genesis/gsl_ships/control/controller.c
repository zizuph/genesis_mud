/*
 * Genesis ShipLines Controller
 *
 * This controller communicates with the GSL Control Room to
 * operate all the stuff remotely.
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
#include "../ships.h"

// Prototypes
public int      ship_command(string str);
public int      pier_command(string str);

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
        + "\tship                   - Operates all ship commands.\n"
        + "\tpier                   - Operates all pier commands.\n"
        + "\n\n");

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

    add_action(ship_command, "ship");
    add_action(pier_command, "pier");
}

// ========================= //
// Interface Functions Below //
// ========================= //

public int
ship_command(string arg)
{
    return SHIP_MANAGER->parse_ship(arg);
}

public int
pier_command(string arg)
{
    return PIER_MANAGER->parse_pier(arg);
}
