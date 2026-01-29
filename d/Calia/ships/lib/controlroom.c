/*
 * Genesis Ship Control Room
 *
 * This room keeps track of all the ships that have been cloned.
 * It applies only to the old Genesis ship system, and not the
 * new Genesis Shiplines created by Tapakah.
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
#include "ship.h"

inherit "/std/room";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Global Variables
public mapping      cloned_ships = ([ ]);

// Prototypes
public int  list_ships(string arg);
public int  ship_info(string arg);
public int  restart_ship(string arg);

/*
 * Function:    save_data
 * Description: Call this to persist the data into a file.
 */
public void
save_data()
{
    save_object(STORED_DATA);    
}

/*
 * Function:    load_data
 * Description: Call this to load the data from a persisted file.
 */
public void
load_data()
{
    // Restore the values from the file
    if (file_size(STORED_DATA + ".o") > 0)
    {
        restore_object(STORED_DATA);
    }    
}

public void
create_room()
{
    set_short("Genesis Ship Control Room");
    set_long("This is the Genesis Ship Control Room. Inside this room, "
        + "you can see information about all the ships that are running "
        + "in Genesis.\n\n"
        + "Available Commands: \n"
        + "\tlist ships              - Lists all the ships that can be controlled\n"
        + "\tlist <domain> ships     - Lists all ships in a particular domain\n"
        + "\tshipinfo <num>          - Show information about a particular line\n"
        + "\tshipinfo <domain> <num> - Show information about a line in a domain\n"
        + "\trestart <num>           - Restarts a ship\n"
        + "\trestart <domain> <num>  - Restarts a shipline in a domain\n\n");
    
    setuid();
    seteuid(getuid());
    
    load_data();
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

    add_action(list_ships, "list");
    add_action(ship_info, "shipinfo");
    add_action(restart_ship, "restart");
}

/*
 * Function:    start_ship
 * Description: This function checks for existing ships. If there is
 *              already one, it does nothing. If there are no
 *              existing ships, it will go ahead and clone it and
 *              start it.
 * Arguments:   bRestart - Set this to true if you want it to destroy
 *                         existing ships and start a new one.
 * Returns:     0/1 - failure/success
 */
public int
start_ship(object pier, int bRestart = 0)
{
    object master_ship;
    string shipfile;
    
    if (!objectp(pier))
    {
        return 0;
    }
    
    shipfile = pier->query_ship_file();
    if (!strlen(shipfile))
    {
        return 0;
    }
    
    // Get the properly loaded master ship file
    if (!objectp(master_ship = find_object(shipfile)))
    {
        if (LOAD_ERR(shipfile)
            || !objectp(master_ship = find_object(shipfile)))
        {
            send_debug_message("ship_control", "Could not locate proper "
                + "shipfile " + shipfile + ".");
            return 0;
        }
    }
    
    shipfile = MASTER_OB(master_ship); // cleans up any instances with ".c"
    if (objectp(cloned_ships[shipfile]))
    {
        if (!bRestart)
        {
            // Already have a ship out there.
            send_debug_message("ship_control", "Ship is already running "
                + "and doesn't need to be started.");
            return 0;
        }
        
        send_debug_message("ship_control", "Ship is already running. "
            + "Restarting and removing existing instance.");
        // If specified to restart, we remove all existing instances
        // of the ship object.
        object old_captain;
        if (objectp(old_captain = cloned_ships[shipfile]->query_captain()))
        {
            old_captain->remove_object();
        }
        cloned_ships[shipfile]->remove_object();
        cloned_ships[shipfile] = 0;
    }
    
    send_debug_message("ship_control", "Cloning new ship.");
    
    object new_ship = clone_object(shipfile);
    new_ship->start_ship();
    cloned_ships[shipfile] = new_ship;
    
    save_data();
        
    return 1;    
}

/*
 * Function:    query_cloned_ship
 * Description: Returns the cloned ship currently being managed by
 *              the control room.
 */
public object
query_cloned_ship(string shipfile)
{
    object ship;
    object * clones;
    
    if (!objectp(ship = cloned_ships[shipfile])
        && objectp(ship = find_object(shipfile)))
    {
        // It could be that the control room does not handle this
        // ship yet. In this case, let's look it up in object_clones
        if (sizeof(clones = object_clones(ship)))
        {
            ship = clones[0];
        }
    }

    return ship;
}



public void
display_rows(mixed * rows)
{
    write("          =============================\n");
    write("          = Genesis Ships Information =\n");
    write("          =============================\n\n");
    write(sprintf("Ship #     %15-s %50-s\n", "Shipline", "Ship File"));
    write(sprintf("%75'='s\n", ""));
    int index = 1;
    foreach (mixed row : rows)
    {
        write(sprintf("%9-d  %15-s %50-s\n", index++, row["name"], row["shipfile"]));
    }
    write("\n");
    write("For more info, use the <shipinfo> command.\n");
}

// ============================== //
// Data Retrieval/Update Functions Below //
// ============================== //

public mixed
query_row_by_index(int index, string domain = "")
{
    mixed * rows;
    
    if (strlen(domain))
    {
        rows = SHIP_DATABASE->query_rows ( ([ "domain" : lower_case(domain) ]) );
    }
    else
    {    
        rows = SHIP_DATABASE->query_rows( ([ ]) );
    }
    
    if (index < 0 || index >= sizeof(rows))
    {
        notify_fail("There is no such line. Please select a proper "
            + "ship number.\n");
        return 0;
    }
    
    return rows[index];    
}

public object
query_master_ship_by_index(int index, string domain = "")
{
    mixed row;
    object master_ship;
    string shipfile;
    
    row = query_row_by_index(index, domain);
    if (!row)
    {
        return 0;
    }

    shipfile = row["shipfile"];
    if (!strlen(shipfile) || !file_size(shipfile))
    {
        notify_fail("Invalid ship file: " + row["shipfile"] + ".\n");
        return 0;
    }
    
    // Get the properly loaded master ship file
    if (!objectp(master_ship = find_object(shipfile)))
    {
        if (LOAD_ERR(shipfile)
            || !objectp(master_ship = find_object(shipfile)))
        {
            notify_fail("Cannot find ship information for "
                + row["shipfile"] + ".\n");
            return 0;
        }
    }
    
    return master_ship;
}

public string
query_pier_by_index(int index, string domain = "")
{
    object master_ship;
    mixed * places;
            
    if (!objectp(master_ship = query_master_ship_by_index(index, domain)))
    {
        return 0;
    }
    
    places = master_ship->query_places_to_go();
    return places[0];
}

/*
 * Function:    set_ship_line
 * Description: This should be called by each pier to indicate
 *              the details of the Ship Line. The shipfile indicates
 *              what ship this pier creates.
 */
public int
set_ship_line(string short_desc, string shipfile, string long_desc)
{
    mixed * rows;
    mixed row;
    
    rows = SHIP_DATABASE->query_rows( ([ "shipfile" : shipfile ]) );
    if (!sizeof(rows))
    {
        SHIP_DATABASE->add_ship_entry(short_desc, shipfile, long_desc);
    }
    else
    {
        row = rows[0];
        if (short_desc == row["name"]
            && long_desc == row["description"])
        {
            // No update necessary.
            return 0;
        }
        
        SHIP_DATABASE->update_row( ([ "name" : short_desc,
                                      "description" : long_desc ]),
                                   ([ "shipfile" : shipfile ]) );
    }
    
    return 1;                
}

// ========================= //
// Interface Functions Below //
// ========================= //

public int
list_ships(string arg)
{
    mixed * rows;
    string domain;
    
    if (!arg || !wildmatch("*ships", arg))
    {
        notify_fail("List ships?\n");
        return 0;
    }
    
    setuid();
    seteuid(getuid());
    if (sscanf(arg, "%s ships", domain))
    {
        rows = SHIP_DATABASE->query_rows( ([ "domain" : lower_case(domain) ]) );
    }
    else
    {
        rows = SHIP_DATABASE->query_rows( ([ ]) );
    }
    
    display_rows(rows);
    
    return 1;
}

public int
ship_info(string arg)
{
    int index;
    mixed * rows;
    object master_ship, ship, captain, deck;
    string domain = "";
    
    if (!strlen(arg))
    {
        notify_fail("Shipinfo which ship?\n");
        return 0;
    }

    if (!sscanf(arg, "%d", index)
        && !sscanf(arg, "%s %d", domain, index))
    {
        notify_fail("Shipinfo which ship?\n");
        return 0;
    }
    
    index--;
    mixed row;
    if (!(row = query_row_by_index(index, domain)))
    {
        return 0;
    }
    
    if (!objectp(master_ship = query_master_ship_by_index(index, domain)))
    {
        return 0;
    }
    
    string header = "Ship Information for " + row["name"] + "\n";
    write(header);
    write(sprintf("%" + strlen(header) + "'='s\n", "="));
    write(row["description"] + "\n\n");
    if (!objectp(ship = query_cloned_ship(row["shipfile"])))
    {
        write(" - Ship has no running instances - \n");
        return 1;
    }
    write("Ship Details\n");
    write("------------\n");
    write(sprintf("  %15-s %s\n", "Ship:", file_name(ship)));
    if (objectp(captain = ship->query_captain()))
    {
        write(sprintf("  %15-s %s\n", "Captain:", file_name(captain)));
    }
    write(sprintf("  %15-s %s\n", "Deck:", ship->query_deck()[0]));
    string pier = query_pier_by_index(index, domain);
    if (strlen(pier))
    {
        write(sprintf("  %15-s %s\n", "Pier:", pier));
    }
    write("\nCurrent Location\n");
    write(  "----------------\n");
    write(sprintf("  %15-s %s\n", "Room:", 
        file_name(ship->query_present_location())));
    write(sprintf("  %15-s %d of %d\n", "Step #:",
        ship->query_location(), sizeof(ship->query_places_to_go())));
    
    object deckroom;
    if (objectp(deckroom = find_object(ship->query_deck()[0])))
    {
        object * players = FILTER_PLAYER_OBJECTS(all_inventory(deckroom));
        write("\nPlayers On Ship\n");
        write(  "---------------\n");
        if (sizeof(players))
        {
            foreach (object player : players)
            {
                write("  " + capitalize(player->query_real_name()) + "\n");
            }
        }
        else
        {
            write("  None\n");
        }
    }
    return 1;
}

public int
restart_ship(string arg)
{
    int index;
    string domain = "";
    object pierroom;
    
    notify_fail("Restart which ship?\n");
    if (!strlen(arg))
    {
        return 0;
    }

    if (!sscanf(arg, "%d", index)
        && !sscanf(arg, "%s %d", domain, index))
    {
        return 0;
    }
    
    index--;

    notify_fail("Could not find the pier for the ship.\n");
    string pier = query_pier_by_index(index, domain);
    if (!strlen(pier))
    {
        return 0;
    }
    
    if (!objectp(pierroom = find_object(pier)))
    {
        return 0;
    }
    
    if (!pierroom->is_controllable_pier())    
    {
        notify_fail("Pier " + pier + " is not controllable so the ship "
            + "there cannot be restarted.\n");
        return 0;
    }
    
    start_ship(pierroom, 1);
    write("Ship at " + pier + " has been restarted.\n");
    return 1;
}
