#pragma strict_types

#include "/d/Krynn/common/defs.h"
#include "locals.h"
#include CLOCKH

inherit "/d/Krynn/std/room.c";


// We have six fields in each area, that means the area grows with 6 elements each
// time someone conquers an area, it also means we need the constant to calculate
// number of records the size of the area divided with 6 is the number of records
#define NUM_OF_FIELDS 5

mapping gAreas = ([ ]);

public string query_conquer_time();
public mixed query_area_history(string area, int verbose = 0);
public void conquered_area( string area, string oldArmy, string newArmy, string conquer_time, int killed, int survived );
public void init;


/*
 * Function name: create_krynn_room
 * Description:   Called to construct a room in Krynn. Read 'kman room.doc'
 *                to see how this is used in your area.
 */
public void
create_krynn_room()
{
    restore_object(HISTORY_MASTER);
    set_short("The room of history");
    set_long("The walls of this room are covered with historic "
            + "events, they are not fixed in one spot, and they "
            + "are not images, they are floating among each other "
            + "without taking shape or form, the colours as well "
            + "as the sounds are vivid beyond recognistion, every "
            + "event of the past are occuring right here.\n");

    add_item("walls", "Staring into the walls you realize "
                + "'area_history' has a special meaning.\n");




    restore_object(HISTORY_MASTER);
}

public void
init()
{
    add_action(query_area_history, "area", 1);
    ::init();
}

/*
 * Function name: reset_krynn_room
 * Description:   This is called periodically in the room to
 *                reset it.
 */
public void
reset_krynn_room()
{
}

////////////////////////////////////////
// Functions for manipulating the data

/*
 * area_name:       string the area name that was conquered
 * old_army:        The army which we just conquered from
 * period_start:    When the area was conquered by old army
 * period_end:      When old army lost the area to new army
 * new_army:        The army which just conquered the area
 * killed:          The number of guards killed from the old army
 * survived:        Number of guards who survived.
 */
public void
conquered_area( string area, string oldArmy, string newArmy, string conquer_time, int killed, int survived )
{
    mixed   tmpArea;

    if (m_sizeof(gAreas))
    {
        // Extract the area mapping
        tmpArea = gAreas[area];
    }

    // If we couldn't extract a mapping lets initialize tmpArea manually
    if (!pointerp(tmpArea))
    {
        tmpArea = ({ oldArmy, newArmy, conquer_time, killed, survived });
    }
    else
    {
        // Add the new info to the area mapping
        tmpArea += ({ oldArmy, newArmy, conquer_time, killed, survived });
    }


    // Now add the info to the history module for areas
    gAreas += ([area : tmpArea ]);

    save_object(HISTORY_MASTER);
}

////////////////////////////////////////
// Functions for presenting data
/*
 * Function name: query_area_history
 * Description:   Presents/returns the historic data for a specific area
 */
public mixed
query_area_history(string area, int verbose = 1)
{
    int i;
    int a;
    int records;
    string result;
    mixed tmpArea;

    if (verbose)
    {
        // Extract the area mapping
        tmpArea = gAreas[area];

        // If we couldn't extract a mapping lets initialize
        // tmpArea manually
        if (pointerp(tmpArea))
        {
            records = (sizeof(tmpArea) / NUM_OF_FIELDS);
            result = "Area history:\t\t" + area + "\n";

            for (i = 0; i <= (records - 1); i++)
            {

                a = (i * NUM_OF_FIELDS);

                result += "\n\tOld army:\t"     +   tmpArea[0 + a] + "\t"
                        + "New army:\t\t"     +   tmpArea[1 + a] + "\n\t"
                        + "Guards killed:\t"+   tmpArea[3 + a] + "\t"
                        + "Guards survived:\t\t"+   tmpArea[4 + a] + "\n\t"
                        + "Conquer time:\t\t" +   tmpArea[2 + a] + "\n";
            }
        }
        else
        {
            result = "No history recorded for the " + area + ".\n";
        }

        write( result + "\n");

        return 1;
    }

    return gAreas[area];
}

/*
 * Function name: query_conquer_time
 * Description:   Returns the time in a format we would like to store
 * Returns:       A string with the current time.
 */
public string
query_conquer_time()
{
    return ( (CLOCK->query_time12_string()) + " at "
                + (CLOCK->query_day()) + "/"
                + (CLOCK->query_month()) + "/"
                + (CLOCK->query_year()) );
}