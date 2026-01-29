/* 
 * Ships and Piers Database
 *  
 * This object keeps track of the piers and boats in a pseudo
 * database table. It is used by the ship controller to query
 * for the right information.
 *
 * Created by Petros, March 2009
 */

#pragma strict_types
#pragma save_binary

#include <composite.h>
#include <std.h>
#include <const.h>
#include <macros.h>
#include <ss_types.h>
#include <filepath.h>

inherit "/d/Genesis/specials/lib/database";

/*
 * Function:    query_database_file
 * Description: Mask this function to specify where the data should
 *              be stored.
 */
public string
query_database_file()
{
    return FILE_PATH(MASTER_OB(this_object())) + "ships_and_piers";
}

public void
create_database()
{
    add_column("name");
    add_column("shipfile", 1);
    add_column("description");
    add_column("domain");
}

public int
add_ship_entry(string name, string shipfile, string description)
{
    setuid();
    seteuid(getuid());
    
    string domain = "";
    string * parts;
    
    parts = explode(shipfile, "/");
    if (sizeof(parts) > 2)
    {
        domain = lower_case(parts[2]);
    }
    
    return add_row( ([ 
                "name"          : name,
                "shipfile"      : shipfile,
                "description"   : description,
                "domain"        : domain,
                ]) );    
}
