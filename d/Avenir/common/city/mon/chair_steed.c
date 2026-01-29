/*
 * This is a modification of the flying steed.
 * /d/Avenir/inherit/air_steed
 * Lilith June 2003
 * Lilith May 2014 Changed move delay to 3 
 */
#pragma strict_types

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/smis/sys/statserv.h"
#include <files.h>
#include <options.h>

/*
 * /sys/files.h will be updated if the steeds ever obtain
 * mudlib support to define STEED_OBJECT, so no update
 * should necessart when the migration taked place.
 */
#ifndef STEED_OBJECT
#define STEED_OBJECT    "/d/Genesis/steed/steed"
#endif

inherit STEED_OBJECT;

/* GLOBAL VARIABLES */
static mapping places = ([ "nowhere" : ({}) ]);
static int     location_index,
               move_delay = 3;
static string  trip_type;
static object  a_room;

/* FUNCTION PROTOTYPES */
public           object   get_a_room();
public varargs   string   a_room_short(object for_obj);


/* FUNCTION BLOCKS */
public void
create_chair_steed()
{

}

public nomask void
create_steed()
{
    ::create_steed();

    create_chair_steed();
}

void
set_move_delay(int how_long)
{
    move_delay = how_long;
}


public void
set_places(string desc, string *locations)
{
    places[desc] = locations;
}

public int
set_trip_type(string str)
{
    if(!sizeof(places[str]))
        return 0;
    trip_type = str;
    return 1;
}

public string
query_trip_type()
{
    return trip_type;
}

public void
reset_trip()
{
    trip_type = "";
    location_index = 0;
}

/*
 * Function name: as_hook_riders_launched
 * Returns:       The string the riders will see when the
 *                steed leaves
 */
public string
as_hook_riders_launched()
{
    return QCTNAME(this_object()) + " heaves into motion.\n";
    STATSERV_LOG_EVENT("city", "Sedan chair rides");

}

/*
 * Function name: as_hook_launched
 * Returns:       The string the room will see when the
 *                steed leaved the ground
 */
public string
as_hook_launched()
{
    return QCTNAME(this_object()) + " heaves into motion.\n";
}

/*
 * Function name: as_hook_default_room_long
 * Returns:       The default long description of a room
 *                the steed will by flying in.
 */
public string
as_hook_default_room_long()
{
    return "Moving along at a steady pace.\n";
}

/*
 * Function name: as_hook_default_room_short
 * Returns:       The default short description of a room
 *                the steed will by flying in.
 */
public string
as_hook_default_room_short()
{
    return "path";
}

/*
 * Function name: as_hook_left_room
 * Returns:       The string players in the room below
 *                the steed will see when the steed flies on to
 *                the next room.
 */
public string
as_hook_left_room()
{
    return QCTNAME(this_object()) + " moves along at a steady pace.\n";
}

/*
 * Function name: as_hook_entered_room
 * Returns:       The string players in the room below
 *                the steed will see when the steed enters
 */
public string
as_hook_entered_room()
{
    return QNAME(this_object()) + " arrives at a trot.\n";
}

/*
 * Function name: as_hook_riders_entered_room
 * Returns:       the string the players riding the steed will
 *                see when the steed enters a room.
 */
public string
as_hook_riders_entered_room()
{
    return QCTNAME(this_object()) + " continues moving along the path.\n"
           + capitalize(a_room_short()) + ".\n";
}

/*
 * Function name: as_hook_riders_entered_room
 * Returns:       The string the riders will see when the
 *                steed lands in a room.
 */
public string
as_hook_riders_landed_room()
{
    return QCTNAME(this_object()) + " eases to a stop.\n";
}

/*
 * Function name: as_hook_landed_room
 * Returns:       The string the room will see when the steed
 *                lands in it.
 */
public string
as_hook_landed_room()
{
    return QCNAME(this_object()) + " eases to a stop.\n";
}

/*
 * Function name: get_below_room
 * Description:   obtain the room object that we are
 *                flying over, so we can set our air_room
 *                long and short descriptions to its
 *                equivalent, also so we can send messages
 *                to the players we are flying over.
 * Returns:       The room object we are flying over, if
 *                it could be obtained.
 */
public object
get_below_room()
{
    string *locs = places[trip_type],
            where;
    object room;

    if(environment() != a_room)
       return environment();

    if(!sizeof(locs) || location_index >= sizeof(locs))
       return 0;

    where = locs[location_index];
    if(!strlen(where))
       return 0;

    room = find_object(where);

    if(!room)
    {
       catch((where)->telendensanka());
       room = find_object(where);
    }

    if(!room)
       return 0;
    else
       return room;
}

public varargs string
a_room_long(object for_obj)
{
    object room;
    string desc;

    room = get_below_room();

    desc = room->long(for_obj);

    /*
     * If the long description of the room contains the word
     * "you" (e.g., "You feel the soft grass on your feet"),
     * then there is a good chance that the long desc of the
     * room is not suitable for the description from above.
     * In these cases, use the short desc of the room instead.
     */
//    if(wildmatch("*you*", desc) || wildmatch("*You*", desc))
//       desc = capitalize(a_room_short(for_obj)) + ".\n";

    if(!room)
       return as_hook_default_room_long();

    return "From your seat in the sedan chair you see:\n" + desc;
}    

/*
 * Function name: check_for_common_preposition
 * Description:   Checks to see if the input string
 *                begins with a common preposition, such
 *                as "in", "on", "between". If so, return
 *                1. This is used so we can have a neat,
 *                English version of a "Flying over..."
 *                short description in the room.
 * Argument:      str - the string to check for the preposition
 * Returns:       1 if the string starts with a preposition
 */
private int
check_for_common_preposition(string str)
{
    string *props = ({ "on", "around", "between", "over", 
                       "near", "in", "above" });
    int     i;

    for(i=0; i < sizeof(props); i++)
    {
       if(str[0 .. strlen(props[i]) - 1] == props[i])
          return 1;
     }

     return 0;
}

/*
 * Function name: fix_short_desc
 * Description:   Fix the short description of a room from common
 *                mistakes, such as capitalizing the string and
 *                puncuating the desc. Also adds on "a" or "an"
 *                if the short desc does not already have it.
 *                This is used in a_room_short() so we can
 *                have a nice, pretty version of the room's
 *                short description. E.g.,
 *                "In the water"->"Flying over an area in the water"
 * Argument:      The old short desc
 * Returns:       The fixed short desc, lower case and no puncuation
 */
private string
fix_short_desc(string str)
{
    str = lower_case(str[0 .. 0]) + str[1 ..];

    if(str[strlen(str) - 1] == '.')
       str = str[0 .. strlen(str) - 1];

    if(check_for_common_preposition(str))
       str = "an area " + str;
    else if((str[0 .. 1] != "a ") && 
            (str[0 .. 2] != "an ") && 
            (str[0 .. 3] != "the "))
       str = LANG_ADDART(str);

    return str;
}

public varargs string
a_room_short(object for_obj)
{
    object room;

    room = get_below_room();

    if(!room)
       return as_hook_default_room_short();

    return "trotting through " + fix_short_desc(room->short(for_obj));
}    

public object
make_a_room()
{
    object ob;

    reset_euid();

    ob = clone_object(ROOM_OBJECT);

    ob->set_long(a_room_long);
    ob->set_short(a_room_short);
    ob->add_prop(ROOM_I_TYPE, ROOM_IN_AIR);
    ob->add_prop(ROOM_I_INSIDE, 1);

    return ob;
}

public object
get_a_room()
{
    if(!a_room)
      a_room = make_a_room();

    return a_room;
}

public int
establish_trip_type()
{
    string *types;
    int i;

    types = m_indices(places);

    for(i=0; i < sizeof(types); i++)
    { 
       if(sizeof(places[types[i]]) && (places[types[i]][0] == file_name(environment())))
           return set_trip_type(types[i]);
    }

    return 0;
}

public void
riders_glance()
{
    object *people = query_riders();
    int i;

    if(!sizeof(people))
       return;

    for(i=0;i<sizeof(people);i++)
       people[i]->do_glance(people[i]->query_option(OPT_BRIEF));
}

/* 
 * Function name: move_chair_steed
 * Description:   The core movement function: called via an
 *                alarm when the player mounts, and continues
 *                to fly until the last member of the places
 *                array is reached.
 * Returns:       void
 */
public void
move_chair_steed(object o)
{
    string *locs;
    int     move_res;

    locs = places[trip_type];

    if (!o)
        o = this_player();

    if (!o->query_prop(LIVE_O_STEED))
    {
        // We don't want it taking off w/o a rider.
        return;
    }
    if (!location_index)   // => beginning of the trip
    {
        if(!establish_trip_type())
        {
            return;
        }
        else
        {
            tell_room(environment(), as_hook_launched(), query_riders());
            query_riders()->catch_msg(as_hook_riders_launched());
            move_living("M", get_a_room(), 1, 1);
       }
    }
    else tell_room(get_below_room(), as_hook_left_room());

    location_index++;

    if((location_index + 1) == sizeof(locs))  // => end of trip
    {
        move_res = move_living("M", locs[location_index], 1, 1);

        if(move_res)   // Uh oh....
            query_riders()->catch_tell("Panic!! Land failure to: " + locs[location_index]
                + ". Result code was " + move_res + ".\nContact a wizard.\n");

        tell_room(environment(), as_hook_landed_room(), query_riders());

        reset_trip();

        query_riders()->catch_msg(as_hook_riders_landed_room());
    }
    else    // => in transit
    {
        tell_room(get_below_room(), as_hook_entered_room());
        query_riders()->catch_msg(as_hook_riders_entered_room());

        if(environment() != get_a_room())
            move_living("M", get_a_room(), 1, 1);

        riders_glance();

        set_alarm(itof(move_delay), 0.0, move_chair_steed);
    }

}

/* 
 * Function name: check_destination
 * Description:   Additional check to see if the steed is allowed
 *                to fly into a room. the steed can only fly into (over)
 *                a room on the pre-defined places mapping list.
 * Arguments:     mixed - the destination object / file
 * Returns:       int - true if destination is OK
 */
public int
check_destination(mixed to_dest)
{
    string dest;

    /* We were cloned to this place */
    if(!environment())
       return 1;
    // Resolve to_dest into a string.
    if(objectp(to_dest))
       dest = file_name(to_dest);
    else if(stringp(to_dest))
       dest = to_dest;
    else
       return 0;

    // Check to see if this is a valid area that the steed should be
    // passing through by comparing it to the array of places
    // we are traved through.
    if(member_array(dest, places[trip_type]) < 0 && ((object)to_dest != a_room))
    {
       return 0;
    }
    else
       return 1;
//       default check_destination() checks for things like
//       ROOM_I_INSIDE, and thus is not suitable for Avenir.
//       return ::check_destination(to_dest);

}

/* Function name: do_mount
 * Description:   Let a player mount, calls can_mount and check_combat
 *                to see if it is possible to mount.
 *                Additionally, if successfuly, start the steed a-flyin'
 * Arguments:     object - the player object
 *                int - if true: silent mode, don't tell the environment
 * Returns:       0 - could not mount, 1 - if successful
 */
public varargs int
do_mount(object o, int silent = 0)
{
    int ret;

    ret = ::do_mount(o, silent);

    if (ret)
    {
        set_alarm(itof(move_delay), 0.0, &move_chair_steed(o));
    }
    return ret;
}

/* Function name: do_dismount
 * Description:   Let a player dismount, and remove the shadow.
 *                Masked to prevent players from dismounting
 *                while in the air.
 * Arguments:     object - the player object
 *                int - if silent don't tell the environment
 * Returns:       0 - failed to dismount, 1 - successful
 */
public varargs int
do_dismount(object o, int silent = 0)
{
    if(environment()->query_prop(ROOM_I_TYPE) == ROOM_IN_AIR)
    {
        notify_fail("You should wait until the sedan chair stops "+
            "or you could be badly hurt.\n");
        return 0;
    }

    return ::do_dismount(o, silent);
}


void
init_living()
{
   ::init_living();
   add_action(mount, "climb");
   add_action(mount, "board");
}
    
