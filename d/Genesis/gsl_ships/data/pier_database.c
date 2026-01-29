/* 
 * Piers Database
 *  
 * This object stores everything about piers in its own database
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
public mapping      filename_row_cache = ([ ]);
public mapping      domain_ports_cache = ([ ]);
public mapping      ports_piers_cache = ([ ]);

/*
 * Function:    query_database_file
 * Description: Mask this function to specify where the data should
 *              be stored.
 */
public string
query_database_file()
{
    return FILE_PATH(MASTER_OB(this_object())) + "pier_database";
}

public void
create_database()
{
    add_column("filename", 1);
    add_column("directions");
    add_column("location");
    add_column("description");
    add_column("port");

    // Status Information
    add_column("active"); 
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
    string * parts;
    
    if (!mappingp(row)
        || !mappingp(conditions)
        || !m_sizeof(conditions)
        || !strlen(conditions["domain"]))
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
    
    // Compare against the Pier's filename
    if (strlen(row["filename"]))
    {
        parts = explode(row["filename"], "/");
        if (sizeof(parts) > 2
            && lower_case(parts[2]) == domain)
        {
            return 1;
        }
    }
    
    return 0;
}

public mixed * 
query_rows_by_domain(string domain)
{
    // Cache the domain rows since they never change.
    if (domain_row_cache[domain])
    {
        return domain_row_cache[domain];
    }
    
    mixed * results = filter_rows(filter_matches_domain, ([ "domain" : domain ]) );
    domain_row_cache[domain] = results;
    return results;  
}

public void
clear_cache()
{
    domain_row_cache = ([ ]);
    filename_row_cache = ([ ]);
    domain_ports_cache = ([ ]);
    ports_piers_cache = ([ ]);
}

public int
add_pier_entry(string filename, string port, string description)
{
    int result;
    
    setuid();
    seteuid(getuid());
    
    clear_cache();
    result = add_or_update_row( ([ 
                "filename"      : filename,
                "port"          : port,
                "description"   : description ]) );
    
    // We need to set some defaults if they aren't set.
    update_rows( ([ "sign" : STDSIGN ]), 
                 ([ "sign" : 0 ]) );
    update_rows( ([ "location" : ({ 0, 0 }) ]), 
                 ([ "location" : 0 ]) );
    update_rows( ([ "directions" : ([ "se" : ({ 1, 1 }) ]) ]), 
                 ([ "directions" : 0 ]) );
    update_rows( ([ "active" : 1 ]), 
                 ([ "active" : 0 ]) );
}

public int
set_pier_active(int value, mixed conditions)
{
    clear_cache();
    if (intp(conditions))
    {
        // We have been passed a row id
        m_rows[conditions]["active"] = value;
        save_data();
        return 1;
    }
    else if (mappingp(conditions))
    {
        mixed * rows = query_rows(conditions);
        foreach (mixed row : rows)
        {
            row["active"] = value;
        }
        save_data();
        return 1;
    }
    
    return 0;
}

public void
set_pier_location(mixed value, int id)
{
    clear_cache();
    mapping pier;
    
    pier = query_row_by_id(id);
    if (!mappingp(pier))
    {
        return;
    }
    
    pier["location"] = value;
    save_data();
}

public void
set_pier_sign(string value, int id)
{
    clear_cache();
    mapping pier;
    
    pier = query_row_by_id(id);
    if (!mappingp(pier))
    {
        return;
    }
    
    pier["sign"] = value;
    save_data();
}

public void
set_pier_directions(mixed value, int id)
{
    clear_cache();
    mapping pier;
    
    pier = query_row_by_id(id);
    if (!mappingp(pier))
    {
        return;
    }
    
    pier["directions"] = value;
    save_data();
}

public mapping
query_row_by_filename(string filename)
{
    mixed * rows;
    
    if (filename_row_cache[filename])
    {
        rows = filename_row_cache[filename];
    }
    else
    {
        rows = query_rows( ([ "filename" : filename ]) );
        filename_row_cache[filename] = rows;
    }
    if (!sizeof(rows))
    {
        return 0;
    }
    
    return rows[0];
}

public string *
query_ports_for_domain(string domain)
{
    mixed * rows;
    string * ports = ({ });
    
    if (domain_ports_cache[domain])
    {
        rows = domain_ports_cache[domain];
    }
    else
    {
        rows = query_rows_by_domain(domain);
        domain_ports_cache[domain] = rows;
    }
    
    foreach (mapping row : rows)
    {
        if (!IN_ARRAY(row["port"], ports))
        {
            ports += ({ row["port"] });
        }
    }
    
    return ports;
}

public mixed *
query_piers_in_port(string port)
{
    if (ports_piers_cache[port])
    {
        return ports_piers_cache[port];
    }
    
    mixed * results = query_rows( ([ "port" : port ]) );
    ports_piers_cache[port] = results;
    return results;
}
