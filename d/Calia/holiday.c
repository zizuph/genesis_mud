// OBJECT:  holiday room

    /* Calia Domain

    HISTORY

    [2001-12-16] Created by Uhclem from [C:\CALIA\HOLIDAY.DOC].
    [2002-01-12] Uhclem fixed Recovery mapping bug.

    PURPOSE

    This room receives information from special holiday objects and broadcasts
    news of their actions to anyone in this room.  A status board is also
    provided for anyone who wants a summary of recent activity.

    MONITORED OBJECTS

    Gingerbread

    When two or more gingerbread men (or women) are dropped in a room, they
    will begin to build a gingerbread house if they are not aware of any
    mortals watching them.  This house begins as a simple hut and eventually,
    if the construction site is undisturbed, develops into a vast gingerbread
    empire.  No matter what its stage of development, the gingerbread structure
    is a single object; it simply has an increasingly complex description the
    longer it is allowed to grow.  The latter stages are large objects which
    cannot be eaten whole, but they break easily into edible cookies unusual
    design.  These cookies are used in the Gingerbread Quest.

    Because there's no way to predict how many construction sites will be
    started by mortals simply dropping gingerbread men, all construction is
    controlled by a single repeating alarm in this room rather than by alarms
    in the individual structures.  The locations of the construction sites are
    stored in an array whose contents are used to provide the messages in this
    room.

    MEMORY BACKUP AND COOKIE RECOVERY

    Construction sites are kept in an array in this room.  If for any reason
    this room must be updated, this important information is lost.  Therefore,
    whenever the array is updated, it is copied to a backup object that is not
    in this room; in fact, it isn't anywhere (has no environment), so it's
    difficult for a wizard to accidentally erase it.  Should it be necessary to
    purge the backup object, a Wipe command is provided.

    It takes hours to acquire the complete set of cookies that is required for
    maximum xp in the Gingerbread Quest, so we keep a record of who has
    acquired the special cookies.  The record is kept in a stored mapping which
    is written by this room but read by the dispenser in the Gelan bakery.  In
    the event that a crash or reboot robs a player of his special cookies, he
    can get replacements in the bakery.  Players must use their own ingenuity
    to replenish their stock of regular cookies.  */

// INCLUSIONS AND DEFINITIONS

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <options.h>
#include <composite.h>
#include <filter_funs.h>
#include "/d/Calia/yuleware/defs.h"

#define GINGERBREAD_MEMORY_BACKUP "/d/Calia/yuleware/ginger/backup"

// GLOBAL VARIABLES

mapping Recovery = ([]);        /*  used to recover quest objects  */
object *Sites = ({});           /*  rooms with construction sites  */
object Backup;                  /*  memory backup for Sites array  */
int Construction = 0;           /*  1 when construction is underway  */

// FUNCTIONS

// Function:  build_structures()

/*

Purpose:  (gingerbread) executes one construction cycle at each room in Sites
array.

Arguments:  none; the conditions in each room in the Sites array determine what
happens next at each construction site.

Returns:  nothing

*/

void
build_structures()

{

    int cookie_count;
    int object_count;
    int numlocs;
    int m = 0;
    int n = 0;
    string building_type;
    object room;
    object building;
    object here = this_object();
    object *cookies = ({});
    object *everyone = ({});
    object *room_inventory = ({});
    object *players_watching = ({});

    Construction = 0;  /*  only set to 1 later if another cycle is needed  */
    Sites -= ({0});  /*  removes unneeded entries (may be updated rooms)  */
    numlocs = sizeof(Sites);

    if (!numlocs)

    {

        return;

    }

    while (n < numlocs)

    {

        /*
         *  Building activity only occurs if more than one cookie is in the 
         *  room and the cookies don't notice any mortals watching them.
         *  Wizards can watch, and it's pretty easy to hide from a cookie, so
         *  any nonzero query_hidden value will do the trick for mortals.    
         */

        room = Sites[n];
        room_inventory = all_inventory(room);
        cookies = filter(room_inventory, &->is_calian_gingerbread());
        everyone = FILTER_PLAYERS(room_inventory);
        cookie_count = 0;
        object_count = sizeof(cookies);

        m = 0;

        while (m < object_count)

        {

            cookie_count += cookies[m]->num_heap();
            m += 1;

        }

        if (cookie_count < 2)

        {

            Sites[n] = 0;  /*  room will be deleted from array later  */

        }

        else

        {

            players_watching = FILTER_CAN_SEE(everyone, cookies[0]);

            /*
             *  The check for a room is redundant since the cookies themselves 
             *  only register with the monitor when they enter a room, but just
             *  to be sure (and to accommodate any future changes in the
             *  cookies) I check again here.    
             */

            if (room->query_prop(ROOM_I_IS) && !sizeof(players_watching))

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

                    /*
                     *  The build_me function returns a string containing the 
                     *  building type if it changes during this cycle;
                     *  otherwise it returns 0.    
                     */

                    if (building_type = building->build_me(cookie_count - 1))

                    {

                        tell_room(here,
                            file_name(room) + ": " + building_type +
                            " (" + cookie_count + " cookies)\n");

                    }

                    if (building_type == "empire")

                    {

                        Sites[n] = 0;

                    }

                }

                else

                {

                    building = clone_object(GINGERBREAD_BUILDING);
                    building->move(room);

                    tell_room(here, file_name(room) +
                        ": gingerbread construction started\n");

                }

            }

        }

        n += 1;

    }

    Sites -= ({0});  /*  removes unneeded entries  */

    /*
     *  As long as at least one site is under construction, repeat the cycle in 
     *  30 seconds.    
     */

    if (sizeof(Sites))

    {

        set_alarm(30.0, 0.0, build_structures);
        Construction = 1;

    }

    Backup->backup_gingerbread_memory(Sites);

}

// Function:  add_quest_cookie(player, cookie_type)

/*

Purpose:  (gingerbread) adds a cookie to the player's list of quest items that
will be recovered.

Arguments:  player, string containing real name of player,
cookie_type, integer 17-32.

Returns:  nothing.

*/

void
add_quest_cookie(string player, int cookie_type)

{

    if (!Recovery[player])

    {

        Recovery[player] = ({});

    }

    if (member_array(cookie_type, Recovery[player]) == -1)

    {

        Recovery[player] += ({cookie_type});

    }

    save_map(Recovery, GINGERBREAD_MAP_FILE);

}

// Function:  remove_quest_cookie(player, cookie_type)

/*

Purpose:  (gingerbread) removes a cookie from the player's list of quest items
that will be recovered.

Arguments:  player, string containing real name of player,
cookie_type, integer 17-32.

Returns:  nothing.

*/

void
remove_quest_cookie(string player, int cookie_type)

{

    if (Recovery[player])

    {

        Recovery[player] -= ({cookie_type});

    }

    save_map(Recovery, GINGERBREAD_MAP_FILE);

}

// Function:  remove_quest_player(player)

/*

Purpose:  (gingerbread) removes a player from the recovery list when he
completes the quest.

Arguments:  player, string containing real name of player.

Returns:  nothing.

*/

void
remove_quest_player(string player)

{

    if (Recovery[player])

    {

        Recovery = m_delete(Recovery, player);

    }

    save_map(Recovery, GINGERBREAD_MAP_FILE);

}

// Function:  wipe_memory()

/*

Purpose:  (gingerbread) clears the memory object; used for testing only.

Arguments:  none.

Returns:  nothing.

*/

void
wipe_memory()

{

    object *backup_clones = object_clones(Backup);

    while (sizeof(backup_clones))

    {

        backup_clones[0]->remove_object();
        backup_clones -= ({backup_clones[0]});

    }

    tell_room(this_object(),
        QCTNAME(this_player()) + " clears the room's memory.\n");

}

// Function:  add_location(room)

/*

Purpose:  (gingerbread) adds a new construction site to the array Sites.

Arguments:  room, object representing the location of a new construction site

Returns:  nothing.

*/

void
add_location(object room)

{

    if (member_array(room, Sites) == -1)

    {

        Sites += ({room});
        Backup->backup_gingerbread_memory(Sites);

        /*
         *  If a construction cycle is not currently scheduled, start one.    
         */

        if (!Construction)

        {

            set_alarm(30.0, 0.0, build_structures);
            Construction = 1;

        }

    }

}

// Function:  init()

/*

Purpose:  define commands available in this object (called by system when
object enters a player's inventory)

Arguments:  none

Returns:  nothing

*/

void
init()

{

    ::init();
    add_action(wipe_memory, "Wipe");

}

// OBJECT DEFINITION

void
create_room()

{

    Backup = find_object(GINGERBREAD_MEMORY_BACKUP);
    Recovery = restore_map(GINGERBREAD_MAP_FILE);

    set_long("The Calia holiday headquarters.\n");
    set_short("Calia Holiday Headquarters");
    add_exit("/w/uhclem/workroom", "out", 0);

    /*
     *  PROPERTIES    
     */

    setuid();  /*  "uid" settings required for cloning. */
    seteuid(getuid());

    if (Backup)

    {

        Sites = Backup->restore_gingerbread_memory();

        if (sizeof(Sites))

        {

            set_alarm(30.0, 0.0, build_structures);
            Construction = 1;

        }

    }

    else

    {

        Backup = clone_object(GINGERBREAD_MEMORY_BACKUP);

    }

}
