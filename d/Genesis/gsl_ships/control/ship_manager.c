/*
 * Ship Manager
 *
 * This manager takes care of the ship information and is used by the
 * control room.
 *
 * Created by Tapakah, Refactored by Petros to use a DB
 */
#pragma no_clone
#pragma strict_types

#include <std.h>
#include <macros.h>

#include "../ships.h"
#include "../navigation.h"

inherit (SHIP_DIR + "control/control_utility");

#include "/d/Genesis/specials/debugger/debugger_tell.h"

varargs
int     load_ship        (mapping ship, string loader);
int     help_ship        ();
int     list_ships       (string arg);
int     may_modify_ship  (object wizard, int pier_id);
int     enable_ship      (string ship_id_string);
int     do_enable_ship   (mapping this_ship);
int     start_ship       (string ship_id_string);
int     do_start_ship    (mapping this_ship);
int     pause_ship       (string ship_id_string);
int     resume_ship      (string ship_id_string);
int     stop_ship        (string ship_id_string);
int     disable_ship     (string ship_id_string);
int     delete_ship      (string ship_id_string);
int     show_ship        (string ship_id_string);
int     goto_ship        (string ship_id_string);
int     parse_ship       (string str);

public void
create()
{
    setuid();
    seteuid(getuid());
}

public void
log_ship_action (mixed *args)
{
    send_debug_message("gslcontrol_ship_action", implode(args, " "),
        SHIP_ACCESS_LOG);
}
 
public varargs int
load_ship(mapping ship, string loader = "Autoload")
{
    if (!objectp(safely_load_master_file(ship["filename"])))
    {
        log_ship_action(({ loader, "ERROR: Failed to load " 
            + ship["filename"] + ".\n" }));        
        return 0;
    }

    if (objectp(ship["instance"]))
    {
        send_debug_message("ship_manager", "Ship " + ship["filename"]
            + " already exists. Removing the existing instance.");
        ship["instance"]->remove_object();
        SHIP_DATABASE->set_ship_instance(0, ship["id"]);
    }

    do_enable_ship(ship);
    do_start_ship(ship);

    return 1;
}

public int
may_modify_ship(object wizard, int ship_id)
{
    return 1;
}

public int
help_ship()
{
	write("General ship commands are:\n"
		+ "ship list [<domain>|<port>]               - list the ships\n"
		+ "ship show <id>                            - show ship data<ID>\n"
		+ "ship goto <id>                            - goto to ship's deck\n"
		+ "ship timetable <domain>|<port>            - show the timetable\n"
		+ "\n"
		+ "Management ship commands are:\n"
		+ "ship enable <id>                          - enable ship\n"
		+ "ship disable <id>                         - stop ship and destroy it\n"
		+ "ship start <id>                           - start ship navigation\n"
		+ "ship stop <id>                            - stop ship and return it\n"
		+ "ship delete <id>                          - delete ship from list\n"
        + "ship point <pier-id> <x1,y1> <x2,y2> .... - set points of route\n"
//		+ "ship pause <ID>                           - pause ship at sea\n"
//		+ "ship resume <ID>                          - resume ship where paused\n"
	);
	return 1;
}

public string
query_ship_status(mapping ship)
{
    string ship_status;
    object captain;
    
    if (ship["active"])
    {
        switch (ship["enroute"])
        {
        case 2:
            if (objectp(ship["instance"])
                && ship["instance"]->query_is_at_harbor() >= 0)
            {
                ship_status = "PARKED";
            }
            else
            {
                ship_status = "PAUSED";
            }
            break;
        case 0:
            ship_status = "STOPPED";
            break;
        default:
            if (!objectp(ship["instance"]))
            {
                // means that the status has been set to
                ship_status = "BROKEN";
            }
            else if (ship["instance"]->query_is_at_harbor() >= 0)
            {
                if (objectp(captain = ship["instance"]->query_captain())
                    && captain->query_active_loading())
                {
                    ship_status = "BOARDING";
                }
                else
                {
                    ship_status = "STOPPED";
                }
            }
            else if (!NAVIGATION_MANAGER->has_active_alarm(ship["id"]))
            {
                ship_status = "STUCK";
            }
            else
            {
                ship_status = "ENROUTE";
            }
        }
    }
    else
    {
        ship_status = "DISABLED";
    }  
    
    return ship_status;
}

public int
query_ship_is_running(mapping ship)
{
    string ship_status;

    ship_status = query_ship_status(ship);    
    switch (ship_status)
    {
    case "ENROUTE":
    case "BOARDING":
        return 1;
    }
    
    return 0;
}

public string
query_ship_location(mapping ship)
{
    string route = "nowhere";
    
    if (ship["active"] && objectp(ship["instance"])
        && pointerp(ship["location"]))
    {
        route = ship["location"][0] + "," + ship["location"][1]
              + " (" + ENVX(ship["instance"])->short() + ")";
    }
    
    return route;
}

public string
query_ship_route(mapping ship, int show_points = 0, int show_circle = 0)
{
    string route, segment;
    mapping pier, segment_routes;
    string * segments;
    int pier_idx;
    
    segment_routes = ([ ]);
    if (sizeof(ship["piers"]))
    {
        segments = ({ });
        route = "";
        foreach (string pierfile : ship["piers"])
        {
            pier = PIER_DATABASE->query_row_by_filename(pierfile);
            if (!mappingp(pier))
            {
                continue;
            }
            segment = pier["port"];
            segments += ({ segment });
            segment_routes[segment] = "";
            if (show_points
                && (pier_idx = member_array(pierfile, ship["piers"])) != -1
                && sizeof(ship["points"]) > pier_idx)
            {
                mixed location = ship["points"][pier_idx];
                if (sizeof(location))
                {
                    foreach (int * point : location)
                    {
                        segment_routes[segment] += point[0] + "," 
                            + point[1] + " ";
                    }
                }
            }
        }
        if (sizeof(segments))
        {
            route += implode(segments, " -> ");
            if(show_circle) {
              route += " -> " + segments[0];
            }
            foreach (string segment, string segment_via : segment_routes)
            {
                if (strlen(segment_via))
                {
                    route += "\n               From " + segment 
                        + " via " + segment_via;
                }
            }
        }
    }
    else
    {
       route = "No route defined for this ship\n";
    }
    
    return route;
}

public string
query_all_routes(string domain = 0)
{
    mixed * ships;
    string route;
    
    route = "";    
    if (strlen(domain))
    {
        ships = SHIP_DATABASE->query_rows_by_domain(domain);
    }
    else
    {
        ships = SHIP_DATABASE->query_rows( ([ ]) );
    }    
    foreach (mapping ship_row : ships)
    {
        if (ship_row["active"] == 0
            || !sizeof(ship_row["piers"]))
        {
            continue;
        }
        
        route += query_ship_route(ship_row, 0, 1) + "\n";
    }
    
    return route;
}

public mixed *
query_ships_for_port(string port)
{
    string * ports;
    mixed * ships, * ships_in_port;

    ports = map(PIER_MANAGER->query_all_ports(), lower_case);
    if (!IN_ARRAY(lower_case(port), ports))
    {
        return ({ });
    }
    
    ships = SHIP_DATABASE->query_rows( ([ ]) );
    ships_in_port = ({ });
    foreach (mapping ship : ships)
    {
        foreach (string pierfile : ship["piers"])
        {
            mapping pier = PIER_DATABASE->query_row_by_filename(pierfile);
            if (!mappingp(pier))
            {
                continue;
            }
            if (lower_case(pier["port"]) == port)
            {
                ships_in_port += ({ ship });
                break;
            }
        }
    }
    
    return ships_in_port;
}

public int
list_ships(string arg)
{
    int     i, s;
    string  route, ship_status, ship_speed, header;
    mapping ship;
    mixed * rows;
    string * domain_list;
    
    header = "Registered Ships";    
    domain_list = map(SECURITY->query_domain_list(), lower_case);
    if (strlen(arg) && IN_ARRAY(lower_case(arg), domain_list))
    {
        if (lower_case(arg) == "sparkle")
        {      
            rows = ({ });
            mixed * temprows = SHIP_DATABASE->query_rows_by_domain(arg)
                + SHIP_DATABASE->query_rows_by_domain("genesis");
            mixed * allrows = SHIP_DATABASE->query_rows( ([ ]) );
            foreach (mapping row : allrows)
            {
                if (IN_ARRAY(row, temprows))
                {
                    rows += ({ row });
                }
            }
        }
        else
        {
            rows = SHIP_DATABASE->query_rows_by_domain(arg);
        }
        header += " in " + capitalize(arg) + " Domain";
    }
    else if (strlen(arg) && sizeof(rows = query_ships_for_port(arg)))
    {
        header += " in the Port of " + implode(map(explode(arg, " " ), capitalize), " ");
    }
    else
    {
        rows = SHIP_DATABASE->query_rows( ([ ]) );
    }
    
    header = "| " + header + " |";
    write(sprintf("%|80s\n", sprintf("%'='" + strlen(header) + "s", ""))
        + sprintf("%|80s\n", header)
        + sprintf("%|80s\n", sprintf("%'='" + strlen(header) + "s", "")));

    if(!sizeof(rows)) 
    {
        write("None\n");
        return 1;
    }

    write(sprintf("%-5s %-10s %-s\n", "Id", "Status", "Route (File)"));
    write(sprintf("%'='80s\n", ""));
    for (int i = 0; i < sizeof(rows); ++i)
    {
        ship = rows[i];
        ship_status = query_ship_status(ship);

        route = query_ship_route(ship);

        write(sprintf("%-5d %-10s %-s\n", ship["id"], ship_status, route + " (" + ship["filename"] + ")"));
    }
    
    return 1;
}

public int
enable_ship(string str)
{
    int     ship_id;
    string  error_message;
    mapping this_ship;

    if(sscanf(str, "%d", ship_id) != 1)
    {
        NF0("Usage: ship enable <ID>");
    }
    this_ship = SHIP_DATABASE->query_row_by_id(ship_id);
    if (!mappingp(this_ship))
    {
        NF0("Non-existant ship ID " + ship_id);
    }
    if (this_ship["active"])
    {
        NF0("Ship id " + ship_id + " is enabled, won't change");
    }
    if (!may_modify_ship(TP, ship_id))
    {
        NF0("You are not allowed to modify this ship");
    }
    setuid();
    seteuid(getuid());
    error_message = "";
    if(sizeof(this_ship["piers"]) < 2)
    {
        error_message += "Not enough destinations to form a route\n";
    }
    if (!strlen(this_ship["captain"]))
    {
        error_message += "Warning: No captain defined for this ship\n";
    }
    if(! strlen(this_ship["ticket"]))
    {
      //        error_message += "Warning: No ticket defined for this ship\n";
    }

    if(strlen(error_message))
    {
        NF0("Enabling failed for the following reasons:\n" + error_message);
    }

    return do_enable_ship(this_ship);
}

public string
construct_route_text(mixed * rows)
{
    string * destinations;
    
    if (!sizeof(rows))
    {
        return "";
    }
    
    destinations = ({ });
    foreach (mapping row : rows)
    {
        destinations += ({ row["port"] });
    }
    
    return implode(destinations, " - ");
}

public void
configure_signs(mapping ship)
{
  int ticket_price;
  mixed * results;
    string route_text;
    
    results = ({ });    
    // Go through each Pier in this ship's path and collect all the rows
    foreach (string pierfile : ship["piers"])
    {
        object pier_room = find_object(pierfile);
        if (!objectp(pier_room))
        {
            continue;
        }
        results += ({ PIER_DATABASE->query_row_by_filename(pierfile) });
    }
    
    route_text = construct_route_text(results);
    // Configure the Signs in each of the Pier's Rooms
    foreach (mapping pier_row : results)
    {
        object * signs = filter(all_inventory(find_object(pier_row["filename"])),
            &wildmatch(pier_row["sign"] + "*") @ file_name);
        if (!sizeof(signs))
        {
          signs = filter(all_inventory(find_object(pier_row["filename"])),
                         &->is_pier_sign());
          if (!sizeof(signs)) {
            continue;
          }
        }
        if(strlen(ship["ticket"])) {
          ticket_price = ship["ticket"]->query_price();
        }
        else {
          ticket_price = 0;
        }
        foreach (object sign : signs)
        {
            if (ship["active"])
            {
                sign->configure_sign(pier_row["port"],
                                     ticket_price,
                                     route_text);
            }
            else
            {
                sign->configure_sign(pier_row["port"], 0, "");
            }
	    }
	}
}

public void
configure_all_signs()
{
    mixed * results;
    
    results = SHIP_DATABASE->query_rows( ([ ]) );
    foreach (mixed row : results)
    {
        configure_signs(row);
    }
}

public int
do_enable_ship(mapping this_ship)
{
    int     t, r, route_length, ship_id;
    string  route_text, main_deck;
    mapping pier;
    object  ship, captain, sign, old_captain, t_p;

    ship_id = this_ship["id"];
    if (!objectp(this_ship["instance"]))
    {
        ship = clone_object(this_ship["filename"]);
        send_debug_message("ship_manager", "cloning new ship.");
    }
    else
    {
        ship = this_ship["instance"];
        send_debug_message("ship_manager", "using existing ship.");
    }
    
    setuid();
    seteuid(getuid());
    ship->set_ship_id(ship_id);
    SHIP_DATABASE->set_ship_current(0, ship_id);
    SHIP_DATABASE->set_ship_active(1, ship_id);    
    pier = SHIP_DATABASE->query_current_pier(ship_id);
    ship->move(pier["filename"]);
    // Setting the instance MUST go after moving the object initially.
    SHIP_DATABASE->set_ship_instance(ship, ship_id);
    if (mappingp(pier) && sizeof(pier["location"]) >= 2)
    {
        SHIP_DATABASE->set_ship_location(({ }) + pier["location"], ship_id);
    }

    tell_room(ENVX(ship), capitalize(LANG_ASHORT(ship)) + " arrives from "
        + "the docks.\n");
    write("Ship " + ship_id + " enabled successfully.\n");
    log_ship_action( ({ TP->query_real_name(), "enable", ship_id }) );
    
    configure_signs(this_ship);
	
    // Replace the captain if he doesn't exist. We do this last since
    // move_living sets this_player.
    if (!objectp(captain = ship->query_captain()))
    {
        object oldtp = this_player();
        captain = clone_object(this_ship["captain"]);
        captain->move_living("descends from above", ship->query_deck()[0]);
        set_this_player(oldtp); // strange bug with move_living
        ship->set_captain(captain);
    }

    return 1;
}

public int
start_ship (string str)
{
    int     ship_id;
    mapping this_ship;

    if(sscanf(str, "%d", ship_id) != 1)
    {
        NF0("Usage: ship start <ID>");
    }
    this_ship = SHIP_DATABASE->query_row_by_id(ship_id);
    if (!mappingp(this_ship))
    {
        NF0("Non-existant ship ID " + ship_id);
    }
    if(!this_ship["active"])
    {
        NF0("Ship id " + ship_id + " is NOT enabled, won't start");
    }
    string ship_status = query_ship_status(this_ship);
    if (ship_status == "ENROUTE"
        || ship_status == "BOARDING")
    {
        NF0("Ship id " + ship_id + " is already started!");
    }
    if(!may_modify_ship(TP, ship_id))
    {
        NF0("You are not allowed to modify this ship");
    }

    if (ship_status == "STUCK")
    {
        stop_ship("" + this_ship["id"]);
    }
    else if (ship_status == "BROKEN")
    {
        disable_ship(sprintf("%d", ship_id));
        do_enable_ship(this_ship);
    }
    
    return do_start_ship(this_ship);
}

public int
do_start_ship(mapping this_ship)
{
    int    ship_id;
    object ship;
    mapping current_pier, next_pier;

    ship_id = this_ship["id"];
    ship = this_ship["instance"];
    current_pier = SHIP_DATABASE->query_current_pier(ship_id);
    next_pier = SHIP_DATABASE->query_next_pier(ship_id);

    SHIP_DATABASE->set_ship_enroute(1, this_ship["id"]);
    ship->start_loading(next_pier["port"]);
    
    configure_signs(this_ship);
	    
    write("Ship " + ship_id + " starts loading at " + current_pier["port"] 
        + " successfully.\n");
    log_ship_action( ({ TP->query_real_name(), "start", ship_id }) );
    return 1;
}

public int
pause_ship (string str)
{
    int     ship_id;
    mapping row;
    object  ship;

    if(sscanf(str, "%d", ship_id) != 1)
    {
        NF0("Usage: ship pause <ID>");
    }
    row = SHIP_DATABASE->query_row_by_id(ship_id);
    if (!mappingp(row))
    {
        NF0("Non-existant ship ID " + ship_id);
    }
    if(!row["enroute"])
    {
        NF0("Ship id " + ship_id + " is NOT EN ROUTE, won't pause");
    }
    if(!may_modify_ship(TP, ship_id))
    {
        NF0("You are not allowed to modify this ship");
    }

    ship = row["instance"];
    SHIP_DATABASE->set_ship_enroute(2, ship_id);
    if(ship->query_is_at_harbor() != -1)
    {
        ship->relay_message("The ship exit is delayed. Please stay calm.\n");
        ship->set_board_enabled(0);
    }
    else
    {
        remove_alarm(row["alarm"]);
        SHIP_DATABASE->set_ship_alarm(0, ship_id);
        ship->relay_message("The ship folds the sails and stands unnervingly still.\n");
    }
    write("Ship " + ship_id + " paused at "
        + implode(row["location"], ",") + "\n");
    log_ship_action( ({ TP->query_real_name(), "pause", ship_id }) );
    return 1;
}

public int
resume_ship(string str)
{
    int     ship_id, alarmid;
    mapping row;
    object  ship;

    if(sscanf(str, "%d", ship_id) != 1)
    {
        NF0("Usage: ship resume <ID>");
    }
    row = SHIP_DATABASE->query_row_by_id(row);
    if (!mappingp(row))
    {
        NF0("Non-existant ship ID " + ship_id);
    }
    if(row["enroute"] != 2)
    {
        NF0("Ship id " + ship_id + " is NOT paused, won't resume");
    }
    if(!may_modify_ship(TP, ship_id))
    {
        NF0("You are not allowed to modify this ship");
    }

    ship = row["instance"];
    if(ship->query_is_at_harbor() != -1) 
    {
        mapping next_pier = SHIP_DATABASE->query_next_pier(ship_id);
        if (!mappingp(next_pier))
        {
            NF0("Ship id " + ship_id + " has some real problems! Cannot "
                + "find the next port.\n");
        }        
        ship->start_loading(next_pier["port"]);
    }
    else
    {
        ship->communicate_resume();
/*        alarmid = set_alarm(STOP_TIME_AT_SEA, 0.0,
                            &place_regular_ship_in_sea(
                            ship,
                            ship_info[ship_id]["route"],
                            ship_info[ship_id]["final_destination"],
                            ship_info[ship_id]["stop"],
                            ship_info[ship_id]["pier"]));*/
        SHIP_DATABASE->set_ship_alarm(alarmid, ship_id);
    }
    SHIP_DATABASE->set_ship_enroute(1, ship_id);
    write("Ship " + ship_id + " has been resumed.\n");
    log_ship_action( ({ TP->query_real_name(), "resume", ship_id }) );
    return 1;
}

public int
stop_ship (string str)
{
    int     ship_id;
    mapping row, pier_row;
    object  ship;

    if(sscanf(str, "%d", ship_id) != 1)
    {
        NF0("Usage: ship stop <ID>");
    }
    row = SHIP_DATABASE->query_row_by_id(ship_id);
    if (!mappingp(row))
    {
        NF0("Non-existant ship ID " + ship_id);
    }
    if (!row["enroute"])
    {
        NF0("Ship id " + ship_id + " is NOT ENROUTE, won't stop");
    }
    if (!may_modify_ship(TP, ship_id))
    {
        NF0("You are not allowed to modify this ship");
    }

    ship = row["instance"];
    pier_row = SHIP_DATABASE->query_current_pier(ship_id);
    if (mappingp(pier_row))
    {
        NAVIGATION_MANAGER->arrive_into_harbor(ship, pier_row["id"], "stop");
    }
    remove_alarm(row["alarm"]);
    SHIP_DATABASE->set_ship_alarm(0, ship_id);
    SHIP_DATABASE->set_ship_enroute(0, ship_id);
    ship->set_board_enabled(0);
    write("Ship " + ship_id + " stopped successfully.\n");
    log_ship_action( ({ TP->query_real_name(), "stop", ship_id }) );
    return 1;
}

public int
do_disable_ship (int ship_id)
{
  mapping row;
  object  ship;
  
  row = SHIP_DATABASE->query_row_by_id(ship_id);
  if (!mappingp(row))
    {
      NF0("Non-existant ship ID " + ship_id);
    }
  if(!row["active"])
    {
      NF0("Ship id " + ship_id + " is NOT ENABLED, won't disable");
    }
  if(!may_modify_ship(TP, ship_id))
    {
      NF0("You are not allowed to modify this ship");
    }
  
  SHIP_DATABASE->set_ship_active(0, ship_id);
  ship = row["instance"];
  if (!objectp(ship))
    {
      send_debug_message("ship_manager", "Instance is not an object");
    }
  
  if (query_ship_status(row) == "ENROUTE")
    {
      NAVIGATION_MANAGER->arrive_into_harbor(ship, row["piers"][row["current"]], "disable");
      remove_alarm(row["alarm"]);
      SHIP_DATABASE->set_ship_alarm(0, ship_id);
      SHIP_DATABASE->set_ship_enroute(0, ship_id);
      ship->remove_object();
      SHIP_DATABASE->set_ship_instance(0, ship_id);
      log_ship_action( ({ TP->query_real_name(), "disable", ship_id }) );
    }
  else
    {
      if(objectp(ship))
        {
          tell_room(ENVX(ship), capitalize(LANG_THESHORT(ship))
                    + " leaves for the docks abruptly.\n");
          ship->remove_object();
          SHIP_DATABASE->set_ship_instance(0, ship_id);
        }
      log_ship_action( ({ TP->query_real_name(), "disable", ship_id }) );
    }
  
  configure_signs(row);
  
  write("Ship " + ship_id + " disabled successfully.\n");
  return 1;
}

public int
disable_ship (string str)
{
  int     ship_id;
  mixed  *ship_rows;

  if(sscanf(str, "%d", ship_id) == 1) {
    return do_disable_ship(ship_id);
  }
  else if(str == "all") {
    ship_rows = SHIP_DATABASE->query_rows( ([ ]) );
    foreach (mapping ship_row : ship_rows) {
      do_disable_ship(ship_row["id"]);
    }
    return 1;
  }
}

public int
delete_ship (string str)
{
    int     ship_id;
    mapping row;
    object  ship;

    if(sscanf(str, "%d", ship_id) != 1)
    {
        NF0("Usage: ship delete <ID>");
    }
    row = SHIP_DATABASE->query_row_by_id(ship_id);
    if (!mappingp(row))
    {
        NF0("Non-existant ship ID " + ship_id);
    }
    if(!may_modify_ship(TP, ship_id))
    {
        NF0("You are not allowed to modify this ship");
    }
    
    SHIP_DATABASE->remove_rows( ([ "id" : ship_id ]) );
    write("Ship " + ship_id + " deleted successfully.\n");
    return 1;
}

public int
show_ship (string str)
{
    string shipfile, captainfile, next_stop;
    int id;
    mapping ship, next_pier;
    
    if(sscanf(str, "%d", id) != 1)
    {
        NF0("Usage: ship show <ID>\n");
    }
    ship = SHIP_DATABASE->query_row_by_id(id);
    if (!mappingp(ship))
    {
        NF0("Non-existant ship id " + id);
    }

    shipfile = ship["filename"];
    captainfile = ship["captain"];
    next_stop = "Unknown";
    if (objectp(ship["instance"]))
    {
        shipfile = file_name(ship["instance"]);
        if (objectp(ship["instance"]->query_captain()))
        {
            captainfile = file_name(ship["instance"]->query_captain());
        }
        
        next_pier = SHIP_DATABASE->query_next_pier(id);
        if (mappingp(next_pier))
        {
            next_stop = next_pier["port"];
        }
    }
    
    write("Ship ID " + id + " status report:\n");
    write("=================================\n");
    write("Ship:          " + shipfile + "\n");
    write("Captain:       " + captainfile  + "\n");
    write("Ticket:        " + ship["ticket"]   + "\n");
    write("Status:        " + query_ship_status(ship) + "\n");
    write("Route:         " + query_ship_route(ship, 1) + "\n");
    write("Location:      " + query_ship_location(ship) + "\n");
    write("Next Stop:     " + next_stop + "\n");
    
    return 1;
}

public int
goto_ship(string str)
{
    int ship_id;
    mapping ship;
    object deck;
    
    if(sscanf(str, "%d", ship_id) != 1)
    {
        NF0("Usage: ship goto <ID>");
    }
    ship = SHIP_DATABASE->query_row_by_id(ship_id);
    if(!mappingp(ship))
    {
        NF0("Non-existant ship ID " + ship_id);
    }
    if (!objectp(ship["instance"])
        || !objectp(deck = find_object(ship["instance"]->query_deck()[0])))
    {
        NF0("The ship or its deck has not been properly loaded.");
    }
    TP->move_living("X", deck);
    return 1;
}

public int
point_ship (string point_data)
{
    int     ship_id, pier_id, pier_idx, x0, y0, scans;
    string  point_string;
    mapping ship;
    mixed  *continent;

    if (sscanf(point_data, "%d %d %s", ship_id, pier_id, point_string) != 3)
    {
        NF0("Usage: ship point <ID> <PIER-ID> <x1,y1>, <x2,y2> ...");
    }
    mapping ship_row = SHIP_DATABASE->query_row_by_id(ship_id);
    if (!mappingp(ship_row))
    {
        NF0("Non-existant ship ID " + ship_id);
    }
    if (ship_row["active"])
    {
        NF0("Ship id " + ship_id + " is active, can't change an active ship.");
    }
    if (!may_modify_ship(TP, ship_id))
    {
        NF0("You are not allowed to modify this ship");
    }

    mapping pier_row = PIER_DATABASE->query_row_by_id(pier_id);
    if (!mappingp(pier_row))
    {
        NF0("Pier " + pier_id + " does not exist.");
    }
    if((pier_idx = member_array(pier_row["filename"], ship_row["piers"])) == -1)
    {
        NF0("Pier " + pier_id + " is not in route of ship " + ship_id + "\n");
    }

    scans = 3;
    mixed * ship_points;
    if (!pointerp(ship_row["points"]))
    {
        ship_points = allocate(sizeof(ship_row["piers"]));
    }
    else
    {
        ship_points = ship_row["points"] + ({ });
    }
    ship_points[pier_idx] = ({ });
    while(scans > 2)
    {
        scans = sscanf(point_string, "%d,%d %s", x0, y0, point_string);
        if (scans > 1) 
        {
            continent = NAVIGATION_MANAGER->get_continent_by_xy(x0, y0);
            if(sizeof(continent))
            {
                write("Warning: point " + x0 + "," + y0 + " is in continent " + continent[0] + "!\n");
            }
            if(NAVIGATION_MANAGER->route_has_point(ship_points[pier_idx], x0, y0))
            {
                NF0("Ship already has point " + x0 + "," + y0 + " in route "
                    + "from pier " + pier_id + "\n");
            }
            ship_points[pier_idx] += ({ ({x0, y0}) });
        }
    }
    SHIP_DATABASE->set_ship_points(ship_points, ship_id);
    log_ship_action( ({ TP->query_real_name(), "points", ship_id, pier_id,
        implode(ship_points, ",") }) );
    return 1;

}

public int
timetable_ship(string str)
{
    string timetable;
    mapping ports;
    mixed * rows;
    
    if (!strlen(str))
    {
        NF0("Usage: ship timetable <domain>|<port>");
    }
    
    str = implode(map(explode(str, " "), capitalize), " ");    
    timetable = NAVIGATION_MANAGER->query_timetable(str, 2);
    if (sizeof(explode(timetable, "\n")) <= 3)
    {
        ports = ([ ]);
        write("The port you specified does not have any running "
            + "ships. Please specify a Port from this list: \n");
        rows = PIER_DATABASE->query_rows( ([ ]) );
        foreach (mapping pier : rows)
        {
            ports[pier["port"]] = 1;
        }
        write("\t" + implode(m_indices(ports), ", ") + "\n");
        return 1;
    }
    
    write(timetable);
    
    return 1;
}

public int
parse_ship (string str) 
{
    string command, rest;
    string * words;
    
    if(!str || str == "help")
    {
        return help_ship();
    }

    words = explode(str, " ");
    command = words[0];
    rest = implode(words[1..], " ");
    switch(command) 
    {
    case "list":
        return list_ships(rest);
        
    case "point":
        return point_ship(rest);

    case "enable":
        return enable_ship(rest);

    case "start":
        return start_ship(rest);
/*
    case "pause":
        return pause_ship(rest);

    case "resume":
        return resume_ship(rest);
*/
    case "stop":
        return stop_ship(rest);

    case "disable":
        return disable_ship(rest);

    case "delete":
        return delete_ship(rest);
        
    case "show":
        return show_ship(rest);

    case "goto":
        return goto_ship(rest);
    
    case "timetable":
        return timetable_ship(rest);

    default:
        NF0("Unknown command for ship");
    }

    return 0;
}

public object
get_ship_object(int ship_id)
{
    mixed ship;
    
    ship = SHIP_DATABASE->query_row_by_id(ship_id);
    if (!mappingp(ship))
    {
        return 0;
    }
    
    return ship["instance"];
}

public int *
get_ship_location(int ship_id)
{
    mixed ship;
    
    ship = SHIP_DATABASE->query_row_by_id(ship_id);
    if (!mappingp(ship))
    {
        return 0;
    }
    
    return ship["location"];    
}

public string
get_ship_description(int ship_id)
{
    object ship;
    
    ship = get_ship_object(ship_id);
    if (!objectp(ship))
    {
        return "unknown ship";
    }
    
    return ship->short();
}

public string
construct_captain_route_reply(int ship_id)
{
	int     p;
	string  reply;
	mapping row;

    row = SHIP_DATABASE->query_row_by_id(ship_id);
    if (!mappingp(row))
    {
		return "This ship currently is broken\n";
	}
        
	if(sizeof(row["piers"]) < 2)
	{
		return "This ship is currently parked.\n";
    }
    
	reply = "The ship travels between ";
	
	string * destinations = ({ });
    foreach (string pier : row["piers"])
    {
        mapping pier_row = PIER_DATABASE->query_row_by_filename(pier);
        if (!mappingp(pier_row))
        {
            continue;
        }
        string domain = capitalize(explode(pier, "/")[2]);
        if (domain != pier_row["port"])
        {
            destinations += ({ pier_row["port"] + " in "
                + capitalize(explode(pier, "/")[2]) });
        }
        else
        {
            // If the port name equals the domain, don't repeat it.
            destinations += ({ pier_row["port"] });
        }
    }
    reply += implode(destinations, " and ") + ".\n";
	return reply;
}

public int
find_ship_by_captain(string captain_file)
{
    mapping ship_by_captain = SHIP_DATABASE->query_ship_by_captain(captain_file);
    if (!mappingp(ship_by_captain))
    {
        return -1;
    }
    return ship_by_captain["id"];
}

public string
get_ticket_for_ship(int ship_id)
{
    mapping ship;
    
    ship = SHIP_DATABASE->query_row_by_id(ship_id);
    if (!mappingp(ship))
    {
        return 0;
    }
    
    return ship["ticket"];
}

public void
set_ship_in_harbor(int ship_id, int pier_id)
{
    mapping ship_row, pier_row;
    int index;
    object ship;
    
    ship_row = SHIP_DATABASE->query_row_by_id(ship_id);
    pier_row = PIER_DATABASE->query_row_by_id(pier_id);
    if (!mappingp(ship_row) || !mappingp(pier_row)
        || !pointerp(ship_row["piers"]) || !strlen(pier_row["filename"]))
    {
        return;
    }
    // We need to find the correct "current" index for piers to set
    index = member_array(pier_row["filename"], ship_row["piers"]);
    if (index >= 0)
    {
        SHIP_DATABASE->set_ship_current(index, ship_id);    
    }
    
    if (objectp(ship = ship_row["instance"]))
    {
        ship->set_is_near_harbor(0);
    }
}
