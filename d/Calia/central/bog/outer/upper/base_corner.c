// ROOM:  base_corner.c

    /*  Calia Domain

    HISTORY

    [99-06-09] created by Uhclem from
    [D:\CALIA\CENTRAL\BOG\OUTER\UPPER\BASE_COR.DOC].

    PURPOSE

    This is the base for corner rooms at the top of the wall of the
    Sanctimonian fortress.  The fortress is octagonal; rooms at this level are
    based either on base_side if they are sides or base_corner if they are
    corners of the octagon.

    */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/bog/baseroom";

#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>
#include "defs.h"

// GLOBAL VARIABLES

mixed Sightings = ({});  /*  livings actually sighted in Ground_Rooms  */
object *Ground_Rooms = ({});  /*  ground rooms visible from here  */
string Face_Direction;  /*  direction the outer wall faces  */
string This_Location;
int Recently_Visited = 1;

// FUNCTIONS

// Function:  add_sighting(distance, factor, direction, ob)

/*

Purpose:  add an entry to the table of living objects on the ground visible
from this room.  This function is called by the room containing the sighted
object when the object enters that room.

Arguments:
int    distance -  number of rooms between the observer and 'ob';
int    factor -    indicates how well 'ob' is hiding, 0-99;
string direction - the compass direction from this room to 'ob'.
object ob -        the visible object;

Returns: nothing.

*/

void
add_sighting(int distance, int factor, string direction, object ob)

{

    int m = sizeof(Sightings);
    int n = 0;

    /*
     *  Use a loop to find the insertion point so we keep the list sorted by 
     *  distance, nearest objects first.    
     */

    while (n < m && distance > Sightings[n])

    {

        n += 4;

    }

    /*
     *  We put the new entry either at the beginning, in the middle, or at the 
     *  end of the list.    
     */

    /*
     *  If n is 0, either the Sightings array is empty or the new distance is 
     *  smaller than or equal to the first distance in the array, so we put the
     *  new entry first.    
     */

    if (!n)

    {

        Sightings = ({distance, factor, direction, ob}) + Sightings;

    }

    /*
     *  If n is greater than 0 but less than the number of elements in 
     *  Sightings, indicating that the new distance is between two existing
     *  distances, we need to insert the new entry in the middle.    
     */

    else if (n < m)

    {

        Sightings = Sightings[0..(n - 1)] +
            ({distance, factor, direction, ob}) +
            Sightings[n..(m - 1)];

    }

    /*
     *  If n is greater than the number of elements in Sightings, we have run 
     *  through the whole array and found the new distance to larger than any
     *  existing value, so the new entry goes at the end.    
     */

    else

    {

        Sightings = Sightings + ({distance, factor, direction, ob});

    }

}

// Function:  remove_sighting(ob)

/*

Purpose:  remove an object from the Sightings array.  This function is called
by the room containing the sighted object when the object leaves that room.

Arguments:  ob, the object to be reomved.

Returns: nothing.

*/

void
remove_sighting(object ob)

{

    int m = member_array(ob, Sightings);
    int n = sizeof(Sightings) - 1;

    if (m != -1)

    {

        /*
         *  As with add_sighting, we have to use different statements to remove 
         *  an entry from the beginning, middle, or end of the list.  There's
         *  also an additional case to be considered first:  that there is only
         *  one entry and thus we are setting Sightings to a null array.  Since
         *  the object is always the fourth element in the list entry, we begin
         *  by subtracting 3 to get the first element to be removed.    
         */

        m -= 3;

        if (n == 3)

        {

            Sightings = ({});

        }

        else if (!m)

        {

            Sightings = Sightings[4..n];

        }

        else if (m < n)

        {

            Sightings = Sightings[0..(m - 1)] +
                Sightings[(m + 4)..n];

        }

        else

        {

            Sightings = Sightings[0..(m - 1)];

        }

    }

}

// Function:  ground_desc()

/*

Purpose:  describe the ground outside including any living objects the player
can detect.

Arguments:  none.

Returns: string containing ground description.

*/

string
ground_desc()

{

    int m = sizeof(Sightings);
    int n;
    int aware = this_player()->query_skill(SS_AWARENESS);

    string text = "The ground outside lies far below you, a" +
        " hill covered with bushes and tree stumps surrounded by a" +
        " bog on all sides.\n";

    /*
     *  Distances should always be in the range of 0..4, but just to prevent 
     *  any runtime errors I added a few extra range indicators.    
     */

    string *range_text = ({"By the wall ",
        "A short distance away",
        "About halfway up the hill",
        "Not far from the bog",
        "At the bottom of the hill",
        "At the bottom of the hill",
        "At the bottom of the hill",
        "At the bottom of the hill"});

    for (n = 0; n < m; n += 4)

    {

        /*
         *  if the object is hiding too well, you don't detect him at all.    
         */

        if (aware >= Sightings[n + 1])

        {

            /*
             *  If the object is not sneaking/hiding or your awareness is 
             *  really high, you can see who it is.  Otherwise, you just detect
             *  "someone" or "movement."    
             */

            if ((aware / 2) > Sightings[n + 1])

            {

                text = text +
                    range_text[Sightings[n]] +
                    " to the " + Sightings[n + 2] +
                    " you see " + QNAME(Sightings[n + 3]) +
                    ".\n";

            }

            else

            {

                text = text +
                    range_text[Sightings[n]] +
                    " to the " + Sightings[n + 2] +
                    ({" someone is sneaking around",
                    " you detect some movement",
                    " someone is moving"})[random(3)] +
                    ".\n";

            }

        }

    }

    this_player()->catch_msg(text);

    return "";

}

// Function:  add_ground_room(rooms)

/*

Purpose:  add an object to the Ground_Rooms array.  This function is called by
the sightline checker.

Arguments:  room, an object representing a hill room.

Returns: nothing.

*/

void
add_ground_room(object rooms)

{

    Ground_Rooms += ({rooms});

}

// Function:  observe_ground()

/*

Purpose:  let the player observe activity on the ground outside the fortress.

Arguments:  string containing "ground" or equivalent.

Returns: 0/1.

*/

int
observe_ground()

{

    notify_fail("'Observe' function isn't ready yet.\n");
    return 0;

}

// Function:  init()

/*

Purpose:  add local commands.

Arguments:  none.

Returns: nothing.

*/

void
init()

{

    ::init();
    add_action(observe_ground, "observe");

}

// Function:  enter_inv(object, from_object)

/*

Purpose:  register a player (or foreign npc) with the Sanctimonian control
room.

Arguments:  object entering the room, object from whence it came.

Returns:  nothing.

*/

void
enter_inv(object ob, object from)

{

    ::enter_inv(ob, from);

    if (living(ob) && !ob->sanctimonian()) register_player(ob);

}

// Function:  create_wall(location)

/*

Purpose:  Create the room description and add standard attributes.

Arguments:  string containing the filename of this room.  The same filename is
assumed to be used in other directories for rooms directly below or above this
one.

Returns:  nothing.

*/

void
create_wall(string location, string *adjacent_rooms)

{

    string *compass = ({"north", "northeast", "east", "southeast", "south",
        "southwest", "west", "northwest"});

    int m;
    int n;

    This_Location = location;

    if (adjacent_rooms[0]) add_exit(adjacent_rooms[0], "north", 0, 1);
    if (adjacent_rooms[1]) add_exit(adjacent_rooms[1], "northeast", 0, 1);
    if (adjacent_rooms[2]) add_exit(adjacent_rooms[2], "east", 0, 1);
    if (adjacent_rooms[3]) add_exit(adjacent_rooms[3], "southeast", 0, 1);
    if (adjacent_rooms[4]) add_exit(adjacent_rooms[4], "south", 0, 1);
    if (adjacent_rooms[5]) add_exit(adjacent_rooms[5], "southwest", 0, 1);
    if (adjacent_rooms[6]) add_exit(adjacent_rooms[6], "west", 0, 1);
    if (adjacent_rooms[7]) add_exit(adjacent_rooms[7], "northwest", 0, 1);

    /*
     *  Two exits are generated by the block of functions above.  From the 
     *  directions of the exits, determine which directions the associated
     *  walls face.    
     */

    m = member_array(query_exit_cmds()[0], compass);
    n = member_array(query_exit_cmds()[1], compass);

    if (n == (m + 5) % 8) m = (m + 2) % 8;
    else m = (n + 2) % 8;
    n = (m + 1) % 8;

    add_exit(BOG_INNER_UPPER + This_Location, "down", 0, 1);

    set_short("Atop a fortress at the corner of the " + compass[m] +
        " and " + compass[n] + " walls");

    set_long("You stand atop the wall of a massive log fortress." +
        " The " + compass[m] + " and " + compass[n] +
        " walls are joined at this corner, which has" +
        " additional timbers that connect to a spiral" +
        " staircase leading down and a raised" +
        " triangular structure that prevents anyone from" +
        " falling over the edge.\n");

    add_item(({"wall", "logs", "immense logs"}),
        "The logs are cut and fitted together so that they" +
        " interlock, and they have been squared" +
        " off a bit to make walking on them easy. You see no" +
        " evidence of nails or pegs," +
        " but the immense size of the logs suggests that" +
        " no fasteners are needed to keep them in place.\n");

    add_item(({"structure", "triangular structure"}),
        "A number of the timbers have been joined together" +
        " in a triangular structure that prevents anyone" +
        " or anything from falling over the edge, yet allows" +
        " a sentry to comfortably observe the ground below.\n");

    add_item(({"side", "irregular side", "sides", "irregular sides",
        compass[m] + " side", compass[n] + " side"}),
        "The sides of the fortress are constructed of" +
        " immense logs, tightly stacked and" +
        " securely joined together.\n");

    add_item(({"log", "massive log", "immense log"}),
        "This log looks like the trunk of a" +
        " " + ({"cedar", "pine", "fir", "spruce"})[random(4)] +
        " tree, expertly hewn and meticulously fitted" +
        " into the wall.\n");

    add_item(({"timbers", "timber", "sturdy timbers", "sturdy timber",
        "framework", "dense framework"}),
        "Like the logs, the timbers are rough-cut but solid." +
        " Cleaned of bark and squared off for easy assembly, " +
        " they have been fitted together into a framework" +
        " that will obviously support a lot of weight and stand" +
        " up to rugged use. Some of the timbers form a" +
        " spiral staircase that leads down from here.\n");

    add_item(({"log fortress", "fortress", "fortress interior", "inside"}),
        "The framework of timbers obstructs your view" +
        " of the fortress interior.\n");

    add_item(({"staircase", "stairs", "spiral staircase", "stair", "spiral"}),
        "The timbers have been cut and smoothed to make" +
        " a secure walking surface, and each stair is firmly" +
        " joined to the framework that surrounds it. The" +
        " spiral of timbers blocks your view of the area below.\n");

    add_item(({"ground", "ground outside", "sunlit ground",
        "outside", "forest", "dark forest", "mist", "swirling mist"}),
        "The ground outside lies far below you, and in the" +
        " distance you can make out the dark forest behind a" +
        " shroud of swirling mist. The contrast of dark" +
        " forest and sunlit ground makes it difficult to" +
        " discern much detail with just a quick examination;" +
        " if you're worried about intruders, perhaps you" +
        " should observe the ground for a while to see" +
        " if anything moves.\n");

    /*
     *  The following exit is a dummy to allow shouts to be heard at all levels 
     *  of the fortress.  The corners of the fortress are not climbable, so
     *  there's no need to process the low and middle levels.    
     */

    add_exit(BOG_OUTER_LOW + This_Location, "d", 1, 1, 1);
    add_exit(BOG_OUTER_GROUND + This_Location, "d", 1, 1, 1);

    add_prop(ROOM_I_HIDE, -1);  /*  Impossible to hide. */
    add_prop(ROOM_I_LIGHT, 3);  /*  Plenty of sunlight. */

    /*
     *  "uid" settings required for cloning objects.    
     */

    setuid();
    seteuid(getuid());

    /*
     *  SPECIAL FUNCTION    
     */

    /*
     *  Tell the Sanctimonian central control room that this room has been 
     *  loaded.  Function is found in /d/Calia/central/bog/baseroom.c.    
     */

    register_room();

}
