/*
 * Genesis ShipLines Control Room
 * 
 * This control room gives access to the functionality to manage all
 * the stored ship lines.
 * 
 * Created by Tapakah, Refactored by Petros
 */

#include <std.h>
#include <macros.h>

#include "../ships.h"
#include "../navigation.h"

inherit ROOM_OBJECT;

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Prototypes
public void         log_general(mixed *args);
public void         load_data();

public void
create_room ()
{
  ::create_room();

  setuid();
  seteuid(getuid());
  set_short("Ship control room");
  set_long(
					 "The central ship control room.\n"+
					 "Use '<help>' for help.\n"
					 );
  load_data();
}

public void
log_general (mixed *args) 
{
    send_debug_message("gslcontrol_general", implode(args, " "),
        CONTROL_LOG);
}

/*
 * Function:    load_pier
 * Description: This makes the actual call to the pier manager
 *              to load all the relevent objects for the pier.
 *              It is called in load_data using an alarm.
 */
public void
load_pier(mapping pier)
{
    PIER_MANAGER->load_pier(pier);
}

/*
 * Function:    load_ship
 * Description: This makes the actual call to the ship manager
 *              to load all the relevent objects for the ship.
 *              It is called in load_data using an alarm.
 */
public void
load_ship(mapping ship)
{
    SHIP_MANAGER->load_ship(ship);
}

void
load_data () 
{
    // Because of the number of ships and piers that are being
    // loaded, we must load everything using alarms so that the
    // eval cost will not be too high, causing everything to
    // not load successfully.
    mixed * pier_rows = PIER_DATABASE->query_rows( ([ ]) );
    foreach (mapping pier_row : pier_rows)
    {
        set_alarm(0.0, 0.0, &load_pier(pier_row));
    }

    mixed * ship_rows = SHIP_DATABASE->query_rows( ([ ]) );
    foreach (mapping ship_row : ship_rows)
    {
        set_alarm(0.0, 0.0, &load_ship(ship_row));
    }
}

public int
parse_ship(string str)
{
    return SHIP_MANAGER->parse_ship(str);
}

public int
parse_pier(string str)
{
    return PIER_MANAGER->parse_pier(str);
}

void
init() {

  ::init();

  add_action("parse_help",    "help");
  add_action("parse_pier",    "pier");
  add_action("parse_ship",    "ship");
}
