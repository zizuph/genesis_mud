/*
 * Pier Utility Functions
 *
 * This object is inherited by the main Ship control room. It contains
 * helper functions that manage the pier information.
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

// Prototypes
//   Command Interface Function
public int              parse_pier       (string str);
//   Command Implementation Function
public int              help_pier        ();
public int              list_piers       (string str);
public int              direction_pier   (string pier_direction);
public int              location_pier    (string pier_location);
public int              enable_pier      (string str);
public int              disable_pier     (string str);
public int              delete_pier     (string str);
public int              show_pier        (string str);
public int              goto_pier        (string str);
public int              sign_pier        (string str);
//    Helper Functions
public varargs int      load_pier        (mapping pier, string loader);
public int              may_modify_pier  (object wizard, int pier_id);

public void
create()
{
    setuid();
    seteuid(getuid());
}

public void
log_pier_action (mixed *args)
{
    send_debug_message("gslcontrol_pier_action", implode(args, " "), 
        PIER_ACCESS_LOG);
}

public int
help_pier ()
{
    write("General pier commands are:\n"
        + "pier list [<domain>|<pier>]             - show list of piers\n"
        + "pier show <ID>                          - show pier's information\n"
        + "pier goto <ID>                          - go to the pier\n"
        + "\n"
        + "Management pier commands are:\n"
        + "pier direction <ID> <direction> <X> <Y> - set navigation direction(s)\n"
        + "pier location <ID> <X> <Y>              - set pier's coordinates\n"
        + "sign pier <ID>                          - set custom pier sign\n"
        + "pier delete <ID>                        - delete a pier from the list\n"
//        + "pier enable <ID>                        - activate the pier\n"
//        + "pier disable <ID>                       - deactivate the pier\n"
    	);
    return 1;
}

public int
parse_pier (string str)
{
    string keyword, rest;
    string * words;
    
    if(!str || str == "help")
    {
        return help_pier();
    }

    words = explode(str, " ");
    keyword = words[0];
    rest = implode(words[1..], " ");
    switch(keyword) 
    {
    case "list":
        return list_piers(rest);
        
    case "direction":
        return direction_pier(rest);

    case "location":
        return location_pier(rest);
/*
    case "disable":
        return disable_pier(rest);

    case "enable":
        return enable_pier(rest);
*/
    case "delete":
        return delete_pier(rest);
        
    case "show":
        return show_pier(rest);
    case "sign":
      return sign_pier(rest);
    case "goto":
        return goto_pier(rest);

    default:
        NF0("Unknown command for pier");
    }
    return 0;
}

public varargs int
load_pier(mapping pier, string loader = "Autoload")
{
    if (!objectp(safely_load_master_file(pier["filename"])))
    {
        log_pier_action( ({ loader, "ERROR: Failed to load " 
            + pier["filename"] + " for pier " + pier["id"] + "\n" }) );
        return 0;
    }

    log_pier_action( ({ loader, "SUCCESS: loaded " + pier["filename"] 
        + ".\n" }) );

    return 1;
}

public int
may_modify_pier (object wizard, int pier_id)
{
    return 1;
}

public mixed *
query_piers_in_port(string port)
{
    mixed * rows, * results;
    
    rows = PIER_DATABASE->query_rows( ([ ]) );
    results = ({ });
    foreach (mapping pier : rows)
    {
        if (lower_case(port) == lower_case(pier["port"]))
        {
            results += ({ pier });
        }
    }
    
    return results;
}

/*
 * Function:    list_piers
 * Description: Loops through the piers and displays them in a list.
 */
public int
list_piers(string str)
{
    mixed * rows;
    mapping pier;
    string header;
    string * domain_list;
    
    header = "Registered Piers";
    domain_list = map(SECURITY->query_domain_list(), lower_case);
    if (strlen(str) && IN_ARRAY(lower_case(str), domain_list))
    {
        if (lower_case(str) == "sparkle")
        {
            rows = ({ });
            mixed * temprows = PIER_DATABASE->query_rows_by_domain(str)
                + PIER_DATABASE->query_rows_by_domain("genesis");
            mixed * allrows = PIER_DATABASE->query_rows( ([ ]) );
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
            rows = PIER_DATABASE->query_rows_by_domain(str);
        }        
        header += " in " + capitalize(str) + " Domain";
    }
    else if (strlen(str) && sizeof(rows = query_piers_in_port(str)))
    {
        header += " in the Port of " + implode(map(explode(str, " " ), capitalize), " ");
    }
    else
    {
        rows = PIER_DATABASE->query_rows( ([ ]) );
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

    write(sprintf("%-5s %-15s %-25s %-s\n", "Id", "Port", "Description", "File"));
    write(sprintf("%'='80s\n", ""));

    foreach (mapping pier : rows)
    {
        write(sprintf("%-5d %-15s %-25s %-s\n", pier["id"], pier["port"], 
            pier["description"], pier["filename"]));
    }
    return 1;
}

public int
direction_pier(string str) 
{
    int     id, x, y;
    string  direction;
    mapping this_direction, pier;

    if(sscanf(str, "%d %s %d %d", id, direction, x, y) != 4)
    {
        NF0("Usage: pier direction <ID> <n|ne|e|se|s|sw|w|nw> <X> <Y>.");
    }    
    if(x > X_OCEAN_SIZE || y > Y_OCEAN_SIZE)
    {
        NF0("Coordinates out of range (" + X_OCEAN_SIZE + "x" + Y_OCEAN_SIZE + ").");
    }
    if(!IN_ARRAY(direction, DIR_ESE))
    {
        NF0("Invalid direction - should be one of n|ne|e|se|s|sw|w|nw.");
    }
    pier = PIER_DATABASE->query_row_by_id(id);
    if(!mappingp(pier))
    {
        NF0("Non-existant pier id " + id);
    }
    if(!may_modify_pier(TP, id))
    {
        NF0("You are not allowed to modify this pier");
    }

    this_direction = ([ direction : ({x, y}) ]);
/*
    Not currently allowing more than one direction.
    
    if (mappingp(pier["directions"]))
    {
        this_direction = pier["directions"] + this_direction;
    }
*/
    PIER_DATABASE->set_pier_directions(this_direction, id);
    write("pier " + id + " added coordinates " + x + "," + y + " at " 
        + direction + "\n");
    log_pier_action( ({ TP->query_real_name(), "direction", id, direction,
        x + "," + y }) );
    return 1;
}

public int
location_pier (string str)
{
    int     id, x, y;
    string *domain_data;
    mapping pier;

    if(sscanf(str, "%d %d %d", id, x, y) != 3)
    {
        NF0("Usage: pier location <ID> <X> <Y>.");
    }
    if(x > X_OCEAN_SIZE || y > Y_OCEAN_SIZE)
    {
        NF0("Coordinates out of range (" + X_OCEAN_SIZE + "x" + Y_OCEAN_SIZE + ").");
    }
    pier = PIER_DATABASE->query_row_by_id(id);
    if (!mappingp(pier))
    {
        NF0("Non-existant pier id " + id);
    }
    if (!may_modify_pier(TP, id))
    {
        NF0("You are not allowed to modify this pier");
    }
/*
    domain_data = get_continent_by_xy(x, y);
    if (!sizeof(domain_data))
    {
        NF0("This location doesn't belong to a continent!\n");
    }
    if (pier["domain"] != "backbone" 
       && domain_data[1] != pier["domain"])
    {
        NF0("This location belongs to domain " + domain_data[1] 
          + " rather than " + pier["domain"]);
    }
*/    
    PIER_DATABASE->set_pier_location( ({ x, y }), id );
    write("Pier " + id + " added coordinates " + x + "," + y 
        + " for location.\n");
    log_pier_action( ({ TP->query_real_name(), "location", id,
        x + "," + y }) );
    return 1;
}

public int
sign_pier (string str)
{
  int id;
  string sign_file;
  mapping pier;

  if(sscanf(str, "%d %s", id, sign_file) != 3) {
    NF0("Usage: pier location <ID> <X> <Y>.");
  }
  pier = PIER_DATABASE->query_row_by_id(id);
  if (!mappingp(pier)) {
    NF0("Non-existant pier id " + id);
  }
  if (!may_modify_pier(TP, id)) {
    NF0("You are not allowed to modify this pier");
  }
  if (! sign_file->is_pier_sign()) {
    NF0(sign_file + " is not a valid sign file");
  }
  PIER_DATABASE->set_pier_sign(sign_file);
  
  return 1;
}

public int
enable_pier(string str)
{
    int     id;
    string  error_message;
    mapping pier;
    
    if (!str || sscanf(str, "%d", id) != 1)
    {
        NF0("Usage: pier enable <ID>\n");
    }
    
    pier = PIER_DATABASE->query_row_by_id(id);
    if(!mappingp(pier))
    {
        NF0("Non-existant pier id " + id);
    }
    
    if (pier["active"])
    {
        NF0("Pier id " + id + " is already active, won't change");
    }
    
    if(!may_modify_pier(TP, id))
    {
        NF0("You are not allowed to modify this pier");
    }

    error_message = "";
    if (!m_sizeof(pier["directions"]))
    {
        error_message += "\t- Missing at least one direction out of port.\n";
    }
    if (!sizeof(pier["location"]))
    {
        error_message += "\t- Missing pier's location.\n";
    }
    if (!strlen(pier["port"]))
    {
        error_message += "\t- No pier port supplied.\n";
    }
    if (strlen(error_message))
    {
        NF0("Activation failed for the following reasons:\n" 
            + error_message);
    }

    PIER_DATABASE->set_pier_active(1, id);
    if(!load_pier(pier, TP->query_real_name())) 
    {
        write("Pier load failed - see log for details.\n");
        return 1;
    }
    
    write("Pier " + id + " status changed to active.\n");
    log_pier_action( ({ TP->query_real_name(), "enable", id }) );
    return 1;
}

public int
disable_pier(string str)
{
    int     id;
    mapping pier;
    object  sign;
    
    if(sscanf(str, "%d", id) != 1)
    {
        NF0("Usage: pier disable <ID>\n");
    }
    
    pier = PIER_DATABASE->query_row_by_id(id);
    if(!mappingp(pier))
    {
        NF0("Non-existant pier id " + id);
    }
    if(!pier["active"])
    {
        NF0("Pier id " + id + " is already inactive, won't change.");
    }    
    if(!may_modify_pier(TP, id))
    {
        NF0("You are not allowed to modify this pier.");
    }

    PIER_DATABASE->set_pier_active(0, id);
    if (strlen(pier["sign"]))
    {
        sign = present("sign", find_object(pier["filename"]));
        if (sign)
        {
            sign->configure_sign(pier["port"], 0, "");
        }
    }
    
    write("pier " + id + " status changed to inactive\n");
    log_pier_action( ({ TP->query_real_name(), "disable", id }) );
    return 1;
}

public int
delete_pier(string str)
{
    int     id;
    mapping pier;
    object  sign;
    
    if(sscanf(str, "%d", id) != 1)
    {
        NF0("Usage: pier delete <ID>\n");
    }
    
    pier = PIER_DATABASE->query_row_by_id(id);
    if(!mappingp(pier))
    {
        NF0("Non-existant pier id " + id);
    }
    if(!may_modify_pier(TP, id))
    {
        NF0("You are not allowed to modify this pier.");
    }

    disable_pier(str);
    PIER_DATABASE->remove_rows( ([ "id" : id ]) );
    
    write("Pier " + id + " deleted.\n");
    log_pier_action( ({ TP->query_real_name(), "delete", id }) );
    return 1;
}

public int
show_pier (string str)
{
    int      id;
    mapping pier;

    if(sscanf(str, "%d", id) != 1)
    {
        NF0("Usage: pier show <ID>\n");
    }
    pier = PIER_DATABASE->query_row_by_id(id);
    if(!mappingp(pier))
    {
        NF0("Non-existant pier id " + id);
    }

    write("Pier ID " + id + " status report:\n");
    write("=================================\n");
    write("Pier filename: " + pier["filename"]    + "\n");
    write("Description:   " + pier["description"] + "\n");
    write("Port:          " + pier["port"]        + "\n");
    if (sizeof(pier["location"]))
    {
        write("Location:      " + pier["location"][0] + "," 
            + pier["location"][1] + "\n");
    }
    else
    {
        write("Location:      NO LOCATION DEFINED!\n");
    }
    write("Sign:          " + pier["sign"] + "\n");

    // Display the directions available from this pier
    if (!m_sizeof(pier["directions"]))
    {
        write("Direction:     NO DIRECTIONS DEFINED\n");
    }
    foreach (mixed direction, mixed coordinate : pier["directions"])
    {
        write("Direction:     " + direction + " leads to " 
            + coordinate[0] + ","  
            + coordinate[1] + "\n");
    }    

    return 1;
}

public int
goto_pier(string str)
{
    int id;
    mapping pier;
    
    if(sscanf(str, "%d", id) != 1)
    {
        NF0("Usage: pier goto <ID>\n");
    }
    
    pier = PIER_DATABASE->query_row_by_id(id);
    if(!mappingp(pier))
    {
        NF0("Non-existant pier id " + id);
    }

    TP->move_living("X", pier["filename"]);
    return 1;
}

public mapping
query_next_pier_in_route(int ship_id, int pier_id)
{
    mapping current_pier, next_pier, ship;
    int pier_idx;
    
    ship = SHIP_DATABASE->query_row_by_id(ship_id);
    current_pier = PIER_DATABASE->query_row_by_id(pier_id);
    
    if (!mappingp(ship) || !mappingp(current_pier))
    {
        return 0;
    }
    
    pier_idx = member_array(current_pier["filename"], ship["piers"]);
    if (pier_idx == -1)
    {
        return 0;
    }
    
    pier_idx = (pier_idx + 1) % sizeof(ship["piers"]);
    next_pier = PIER_DATABASE->query_row_by_filename(ship["piers"][pier_idx]);
    
    return next_pier;
}

public string *
query_all_ports()
{
    mixed * rows;
    string * ports;
    
    rows = PIER_DATABASE->query_rows( ([ ]) );
    ports = ({ });
    foreach (mapping row : rows)
    {
        if (!IN_ARRAY(row["port"], ports))
        {
            ports += ({ row["port"] });
        }
    }
    
    // Remove the example port names
    ports -= ({ "Port One", "Port Two" });
    return ports;
}
