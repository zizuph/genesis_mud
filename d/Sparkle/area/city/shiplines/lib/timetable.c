/*
 * Genesis ShipLines Office Timetable
 *
 * Inherit this to create your own GSL Office Timetable in your domain. 
 * Simply specify the domain that the timetable should show.
 *
 * Code originally written by Tapakah. Original comments:
 *     Genesis ShipLines - Sparkle office.
 *     Ship timetable
 *     TAPAKAH, 10/2008
 *     To be transferred later into /d/Sparkle
 *
 * Ported by Petros, April 2009
 */
#pragma no_clone
#pragma save_binary
#pragma strict_types

#include <std.h>
#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "gs_office.h"

inherit OBJECT_OBJECT;
inherit TRADE_LIBRARY;

// Global Variables
private int      Cost; // cost in coppers to see the Timelines
private string   Domain; // domain key to use in querying for timetables

// Prototypes //

//   Action Interface Functions 
public int      pay_timetable (string str);
public int      read_timetable (string str);

//   Customization Functions
public void     create_timetable();
public string   query_timetable_display(string table);

//   Getters and Setters
public void     set_timetable_cost(int coppers);
public int      query_timetable_cost();
public void     set_timetable_domain(string domain);
public string   query_timetable_domain();

/*
 * Function:    create_timetable
 * Description: Mask this function to set up the timetable object
 *              and customize it for the specific office.
 */
public void
create_timetable ()
{
}

/*
 * Function:    query_timetable_display
 * Description: Mask this to customize the way that the timetable is
 *              displayed to the player. It is called both in
 *              read_timetable and in the long description
 * Arguments:   table - the string retrieved from the SHIP_MANAGER
 */
public string
query_timetable_display (string table)
{
    return "The " + short() + " reads:\n" + table;
}

public void
init ()
{
    ::init();
    add_action(read_timetable, "read");
    add_action(pay_timetable, "pay");
    add_action(pay_timetable, "insert");
}

public nomask void
create_object ()
{
    ::create_object();

    set_name("timetable");
    set_short("timetable");
    set_long("This is a timetable.");
    add_prop(OBJ_M_NO_GET, "The timetable is bolted to the wall.\n");
    
    config_default_trade();

    // Call customized creation code for timetable instances
    create_timetable();
}

public int
read_timetable (string str)
{
    if (!strlen(str)
        || (str != "timetable"
            && str != "table"))
    {
        notify_fail("Read what?\n");
        return 0;
    }
    
    // If successful, display the timetable
    write(query_timetable_display(NAVIGATION_MANAGER->query_timetable(
                                            query_timetable_domain())));
    return 1;
}

public int
pay_timetable (string str)
{
    mixed * results;
    object coin_obj;
    
    if (!str)
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }
    
    if (!parse_command(str, this_player(), "%o", coin_obj)
        || !IS_COINS_OBJECT(coin_obj))
    {
        notify_fail("Maybe you can <" + query_verb() + " coin>.\n");
        return 0;
    }
    
    results = pay(query_timetable_cost(), this_player(), 0, 0, 0, 0, 1);
    if (sizeof(results) <= 1)
    {
        notify_fail("The " + short() + " only accepts platinum coins.\n");
        return 0;
    }
        
    write("You slip the platinum coin into the slit. The " + short()
        + " flickers and the display changes.\n\n");    
    write(
        query_timetable_display(
            NAVIGATION_MANAGER->query_timetable(
                query_timetable_domain(), 1)));
    write("\nThe timetable resets immediately again.\n");

    return 1;
}

// GETTERS AND SETTERS

public void
set_timetable_cost(int coppers)
{
    Cost = coppers;
}

public int
query_timetable_cost()
{
    return Cost;
}

public void
set_timetable_domain(string domain)
{
    Domain = domain;
}

public string
query_timetable_domain()
{
    return Domain;
}

/*
 * Function:    exa_timetable
 * Description: This function is called as VBFC inside the long description
 */
public string
exa_timetable()
{
    return query_timetable_display(NAVIGATION_MANAGER->query_timetable(
                                            query_timetable_domain()));
}

