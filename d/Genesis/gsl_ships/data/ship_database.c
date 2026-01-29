/* 
 * Ships Database
 *  
 * This object stores everything about ships in its own database
 * table that can be queried and filtered.
 *
 * Created by Petros, April 2009
 */

#pragma strict_types
#pragma save_binary

#include <composite.h>
#include <std.h>
#include <const.h>
#include <macros.h>
#include <ss_types.h>
#include <filepath.h>

#include "../ships.h"

inherit "/d/Genesis/specials/lib/database";

// Global Variables
public mapping      domain_row_cache = ([ ]);
public mapping      captain_row_cache = ([ ]);
public mapping      location_cache = ([ ]);

/*
 * Function:    query_database_file
 * Description: Mask this function to specify where the data should
 *              be stored.
 */
public string
query_database_file()
{
    return FILE_PATH(MASTER_OB(this_object())) + "ship_database";
}

public void
create_database()
{
    add_column("filename", 1);
    add_column("piers");
    add_column("captain");
    add_column("ticket");
    add_column("points");
    add_column("instance"); // Actual ship object
    // Status Information
    add_column("alarm");    // The alarm used for movement
    add_column("current");  // the current pier index
    add_column("location"); // Current Grid Location
    add_column("enroute");
    add_column("active");
}

public int
pier_matches_domain(string pierfile, string domain)
{
    string * parts;
    
    if (strlen(pierfile))
    {
        parts = explode(pierfile, "/");
        if (sizeof(parts) > 2
            && lower_case(parts[2]) == domain)
        {
            return 1;
        }
    }
    
    return 0;
}

/*
 * Function:    filter_matches_domain
 * Description: Checks whether the row matches the domain using
 *              a domain check in either the source or destination
 *              pier.
 * Argument:    row - mapping of the row's values
 *              conditions - mapping of the conditions
 * Returns:     Whether it matches the condition or not
 */
public int
filter_matches_domain(mapping row, mapping conditions)
{
    string domain;
    
    if (!mappingp(row)
        || !mappingp(conditions)
        || !m_sizeof(conditions)
        || !strlen(conditions["domain"])
        || !sizeof(row["piers"]))
    {
        return 0;
    }
    
    // Check both the Source and Destination Piers to see if there
    // is a match in the domain
    domain = lower_case(conditions["domain"]);
    if (domain == "all")
    {
        return 1;
    }
    
    foreach (string pierfile : row["piers"])
    {
        if (pier_matches_domain(pierfile, domain))
        {
            return 1;
        }
    }
    
    return 0;
}

public mixed * 
query_rows_by_domain(string domain)
{
    mixed * results = ({ });
    int * ids_by_domain = ({ });
    if (domain_row_cache[domain])
    {
        ids_by_domain = domain_row_cache[domain];
        foreach (int row_id : ids_by_domain)
        {
            results += ({ query_row_by_id(row_id) });
        }
    }
    else
    {
        results = filter_rows(filter_matches_domain, ([ "domain" : domain ]) );
        foreach (mixed row : results)
        {
            ids_by_domain += ({ row["id"] });
        }
        domain_row_cache[domain] = ids_by_domain;
    }
    return results;
}

public mapping
query_ship_by_captain(string captain_file)
{
    mixed * results = ({ });
    int * ids_by_captain = ({ });
    if (captain_row_cache[captain_file])
    {
        ids_by_captain = captain_row_cache[captain_file];
        foreach (int row_id : ids_by_captain)
        {
            results += ({ query_row_by_id(row_id) });
        }
    }
    else
    {
        results = query_rows( ([ "captain" : captain_file ]) );
        foreach (mixed row : results)
        {
            ids_by_captain += ({ row["id"] });
        }
        captain_row_cache[captain_file] = ids_by_captain;
    }
    if (!sizeof(results))
    {
        return 0;
    }
    return results[0];
}

public void
clear_cache()
{
    domain_row_cache = ([ ]);
    captain_row_cache = ([ ]);
    location_cache = ([ ]);
}

public int
add_ship_entry(string filename, string captain, string ticket,
               string * piers)
{
    setuid();
    seteuid(getuid());
    
    clear_cache();
    return add_or_update_row( ([ 
                "filename"      : filename,
                "captain"       : captain,
                "ticket"        : ticket,
                "piers"         : piers
                ]) );    
}

public void
set_ship_active(int value, int id)
{
    mapping ship;
    
    ship = query_row_by_id(id);
    if (!mappingp(ship))
    {
        return;
    }
    
    ship["active"] = value;
    save_data();
}

public void
set_ship_instance(object instance, int id)
{
    mapping ship;
    
    ship = query_row_by_id(id);
    if (!mappingp(ship))
    {
        return;
    }
    
    ship["instance"] = instance;
    save_data();
}

public void
set_ship_alarm(int alarmid, int id)
{
    mapping ship;
    
    ship = query_row_by_id(id);
    if (!mappingp(ship))
    {
        return;
    }
    
    ship["alarm"] = alarmid;
}

public void
set_ship_enroute(int value, int id)
{
    mapping ship;
    
    ship = query_row_by_id(id);
    if (!mappingp(ship))
    {
        return;
    }
    
    ship["enroute"] = value;
    save_data();
}

public void
set_ship_current(int value, int id)
{
    mapping ship;
    
    ship = query_row_by_id(id);
    if (!mappingp(ship))
    {
        return;
    }
    
    ship["current"] = value;
}

public void
add_location_cache_entry(mixed location, int id)
{
    if (!pointerp(location) || sizeof(location) != 2)
    {
        return;
    }
    int x = location[0];
    int y = location[1];
    if (!mappingp(location_cache[x]))
    {
        location_cache[x] = ([ ]);
    }
    if (!pointerp(location_cache[x][y]))
    {
        location_cache[x][y] = ({ });
    }
    location_cache[x][y] += ({ id });
}

public void
remove_location_cache_entry(mixed location, int id)
{
    if (!pointerp(location) || sizeof(location) != 2)
    {
        return;
    }
    int x = location[0];
    int y = location[1];
    if (!mappingp(location_cache[x]))
    {
        location_cache[x] = ([ ]);
    }
    if (!pointerp(location_cache[x][y]))
    {
        location_cache[x][y] = ({ });
    }
    location_cache[x][y] -= ({ id });
}

public void
set_ship_location(mixed value, int id)
{
    mapping ship;
    
    ship = query_row_by_id(id);
    if (!mappingp(ship))
    {
        return;
    }
    
    remove_location_cache_entry(ship["location"], id);
    ship["location"] = value;    
    add_location_cache_entry(ship["location"], id);
}

public mixed
query_ships_at_location(int x, int y)
{
    if (!mappingp(location_cache[x]))
    {
        location_cache[x] = ([ ]);
    }
    if (!pointerp(location_cache[x][y]))
    {
        location_cache[x][y] = ({ });
    }
    return location_cache[x][y];
}

public void
set_ship_points(mixed value, int id)
{
    mapping ship;
    
    ship = query_row_by_id(id);
    if (!mappingp(ship))
    {
        return;
    }
    
    ship["points"] = value;
    save_data();
}

public mapping
query_current_pier(int id)
{
    int current_index;
    mapping ship, pier;
    string pierfile;
    
    ship = query_row_by_id(id);
    if (!mappingp(ship))
    {
        return 0;
    }
    
    current_index = ship["current"];
    if (current_index < 0 || current_index >= sizeof(ship["piers"]))
    {
        return 0;
    }
    
    pierfile = ship["piers"][current_index];
    pier = PIER_DATABASE->query_row_by_filename(pierfile);
    if (!mappingp(pier))
    {
        return 0;
    }
    
    return pier;
}

public mapping
query_next_pier(int id)
{
    int current_index, next_index;
    mapping ship, pier;
    string pierfile;
    
    ship = query_row_by_id(id);
    if (!mappingp(ship))
    {
        return 0;
    }
    
    current_index = ship["current"];
    if (current_index < 0 || current_index >= sizeof(ship["piers"]))
    {
        return 0;
    }
    next_index = (current_index + 1) % (sizeof(ship["piers"]));
    
    pierfile = ship["piers"][next_index];
    pier = PIER_DATABASE->query_row_by_filename(pierfile);
    if (!mappingp(pier))
    {
        return 0;
    }
    
    return pier;
}
