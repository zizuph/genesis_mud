// OBJECT:  gingerbread monitor

    /* Calia Domain

    HISTORY

    [2001-12-07] Created by Uhclem from [C:\CALIA\YULEWARE\GINGER\MONITOR.DOC].

    PURPOSE

    This object monitors the construction activity of the gingerbread men
    available in Gelan during the Yule season.  When two or more gingerbread
    men (or women) are dropped in a room, they will begin to build a
    gingerbread house if they are not aware of any mortals watching them.  This
    house begins as a simple hut and eventually, if the construction site is
    undisturbed, develops into a vast gingerbread empire.  No matter what its
    stage of development, the gingerbread structure is a single object; it
    simply has an increasingly complex description the longer it is allowed to
    grow.  The latter stages are large objects which cannot be eaten whole, but
    they break easily into edible cookies of rare and unusual design.

    Because there's no way to predict how many construction sites will be
    started by mortals simply dropping gingerbread men, all construction is
    controlled by a single repeating alarm in this object rather than by alarms
    in the individual structures.  The locations of the construction sites are
    stored in an array, and this object resides in the Calia central workroom
    where the wizards can keep an eye on construction activity.  */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <options.h>
#include "defs.h"

// GLOBAL VARIABLES

object *Locations = ({});  /*  rooms with construction sites  */

// FUNCTIONS

// Function:  add_location(room)

/*

Purpose:  adds a new construction site to the array Locations.

Arguments:  room, object representing the location of a new construction site

Returns:  nothing

*/

void
add_location(object room)

{

    if (member_array(Locations, room) == -1)

    {

        Locations += ({room});
        tell_room(environment(), room->file_name() + ": started");

    }

}

// Function:  build_structures()

/*

Purpose:  executes one construction cycle at each room in Locations array.

Arguments:  none; the conditions in each room in the Locations array determine
what happens next at each construction site.

Returns:  nothing

*/

void
build_structures()

{

    int cookie_count;
    int object_count;
    int numlocs = sizeof(Locations);
    int m;
    int n;
    string building_type;
    object room;
    object building;
    object my_environment = environment();
    object *cookies = ({});
    object *room_inventory = ({});
    object *players_watching = ({});

    while (n < numlocs)

    {

        /*
         *  Building activity only occurs if more than one cookie is in the 
         *  room and the cookies don't notice any mortals watching them.
         *  Wizards can watch, and it's pretty easy to hide from a cookie, so
         *  any nonzero query_hidden value will do the trick for mortals.    
         */

        room = Locations[n];
        room_inventory = all_inventory(room);
        cookies = filter(room_inventory, is_calian_gingerbread);
        cookie_count = 0;
        object_count = sizeof(cookies);
        m = 0;

        while (m < object_count)

        {

            cookie_count += cookies[m]->num_heap();
            m += 1;

        }

        if (cookie_count lt 2)

        {

            tell_room(my_environment,
                room->file_name() + ": construction terminated");

            Locations[n] = 0;  /*  room will be deleted from array later  */

        }

        else

        {

            players_watching = filter(everyone, &->check_seen(cookies[0]));

            /*
             *  The check for a room is redundant since the cookies themselves 
             *  only register with the monitor when they enter a room, but just
             *  to be sure (and to accommodate any future changes in the
             *  cookies) I check again here.    
             */

            if (room->is_room() && !sizeof(players_watching))

            {

                building = present("_calia_gingerbread_building", room);

                /*
                 *  The higher the cookie_count, the faster the building 
                 *  progresses.  The result from build_me is the current type
                 *  of building.  A result of "empire" indicates that the
                 *  building has reached maximum level of development and
                 *  should no longer be processed.    
                 */

                if (building)

                {

                    if (building_type = building->build_me(cookie_count - 1))

                    {

                        tell_room(my_environment,
                            room->short() + ": " + building_type);

                    }

                    else

                    {

                        Locations[n] = 0;

                    }

                }

                else

                {

                    building = clone_object(GINGERBREAD_BUILDING);
                    building->move(room);

                }

            }

            n += 1;

        }

        Locations -= ({0});  /*  removes unneeded entries  */

    }

}

// OBJECT DEFINITION

void
create_object()

{

    set_long("This device monitors the progress" +
        " of gingerbread construction throughout Genesis." +
        " It automatically announces the level of development" +
        " in each room with a construction site.\n");

    set_short("gingerbread monitor");
    set_name("monitor");
    set_adj("gingerbread");

    /*
     *  PROPERTIES    
     */

    add_prop(OBJ_I_WEIGHT, 100000);
    add_prop(OBJ_I_VOLUME, 100000);
    add_prop(OBJ_I_VALUE, 100000);
    add_prop(OBJ_M_NO_GET, "Do not attempt to move this object.\n");

    setuid();  /*  "uid" settings required for cloning. */
    seteuid(getuid());

    /*
     *  Start building cycle when object is first cloned.    
     */

    set_alarm(60.0, 60.0, build_structures);

}
