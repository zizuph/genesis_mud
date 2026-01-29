// ROOM:  base_side.c

    /*  Calia Domain

    HISTORY

    [99-06-09] created by Uhclem from
    [D:\CALIA\CENTRAL\BOG\OUTER\UPPER\BASE_SID.DOC].

    PURPOSE

    This is the base for side rooms at the top of the wall of the Sanctimonian
    fortress.  The fortress is octagonal; rooms at this level are based either
    on base_side if they are sides or base_corner if they are corners of the
    octagon.

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

#define DROPPED_OBJECTS "_dropped_objects"
#define CALIA_ON_WALL_EDGE "_calia_on_wall_edge"

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

// Function:  add_ground_room(room)

/*

Purpose:  add an object to the Ground_Rooms array.  This function is called by
the sightline checker which is deployed by any hill room visible from this
location.

Arguments:  room, an object representing a hill room.

Returns: nothing.

*/

void
add_ground_rooms(object room)

{

    Ground_Rooms += ({room});

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

// Function:  move_check()

/*

Purpose:  Check the player's ability to move to an adjacent room other than
climbing back down the wall outside.  The result is simply determined by the
presence of the fall-from-wall object.  If the player manages to stabilize his
position, the object will remove itself.  If he has not, then the player is not
yet ready to move.

Arguments:  none.

Returns: 1/0.

*/

int
move_check()

{

    if (present(BOG_FALL_FROM_WALL, this_player()))

    {

        write ("Your balance on the wall is too precarious for" +
            " you to move around!\n");

        return 1;

    }

    else return 0;

}

// Function:  drop_object()

/*

Purpose:  Make a dropped object fall; this function is called after a very
short delay when an object is dropped in the room.

Arguments:  none.

Returns:  nothing.

*/

void
drop_object()

{

    object *dropped_objects = query_prop(DROPPED_OBJECTS);

    string target_room = BOG_OUTER_GROUND + This_Location;

    if (!dropped_objects) return;
    else dropped_objects = FILTER_DEAD(dropped_objects);

    while (sizeof(dropped_objects))

    {

        /*
         *  The following check is just to account for a nimble player who 
         *  grabs an object after someone drops it but before it leaves the
         *  room.   
         */

        if (environment(dropped_objects[0]) == this_object())

        {

            dropped_objects[0]->move(target_room);

        }

        dropped_objects -= ({dropped_objects[0]});

    }

    remove_prop(DROPPED_OBJECTS);

}

// Function:  leave_inv()

/*

Purpose:
(1) provide messages for non-living items falling to the ground.
(2) give player a chance to stabilize his position when a defender dies.

Arguments:  object leaving the room, object destination.

Returns:  nothing.

*/

void
leave_inv(object ob, object dest)

{

    object fall_from_wall;

    ::leave_inv(ob, dest);

    if (living(ob))

    {

        /*
         *  If a player is teetering on the edge of the wall, give him a chance 
         *  to stabilize his position now that there's one less living thing to
         *  take up space.    
         */

        if (fall_from_wall = present(BOG_FALL_FROM_WALL, ob))

        {

            fall_from_wall->stabilize_position();

        }

        /*
         *  Any living leaving this room marks it as "recently visited."  See 
         *  function reset_room for the use of this value.    
         */

        Recently_Visited = 1;

    }

    else

    {

        /*
         *  This routine provides messages for falling dead objects only. 
         *  Livings that fall do so under the effect of the fall_from_wall
         *  object, which provides suitable messages.    
         */

        if (!dest) return;  /* Covers updates and destructs by wizards. */

        if (file_name(dest) != BOG_OUTER_GROUND + This_Location) return;

        if (ob->num_heap() > 1)

        {

            tell_room(this_object(),
                capitalize(LANG_THESHORT(ob)) + " fall to the ground.\n");

            tell_room(dest,
                capitalize(LANG_ASHORT(ob)) +
                " fall from the top of the fortress.\n");

        }

        else

        {

            tell_room(this_object(),
                capitalize(LANG_THESHORT(ob)) + " falls to the ground.\n");

            tell_room(dest,
                capitalize(LANG_ASHORT(ob)) +
                " falls from the top of the fortress.\n");

        }

    }

}

// Function:  enter_inv(object, from_object)

/*

Purpose:
(1) cause non-living objects that enter this room to drop to ground level.
(2) add CALIA_ON_WALL_EDGE property to living objects to indicate they they
have only a tenuous foothold in the room; players who arrive by climbing up the
wall must stabilize their position before they can move to adjacent rooms.

Arguments:  object entering the room, object from whence it came.

Returns:  nothing.

*/

void
enter_inv(object ob, object from)

{

    object *dropped_objects;
    object fall_from_wall;

    ::enter_inv(ob, from);

    if (from
        && !living(ob)
        && environment(from) == this_object()
        && query_verb() == "drop")

    {

        if (from->query_prop(CALIA_ON_WALL_EDGE))

        {

            dropped_objects = query_prop(DROPPED_OBJECTS);

            if (dropped_objects)
                add_prop(DROPPED_OBJECTS, dropped_objects + ({ob}));

            else add_prop(DROPPED_OBJECTS, ({ob}));

        }

        set_alarm(0.5, 0.0, drop_object);

    }

    else if (living(ob) &&
        query_verb() == "up" &&
        !ob->query_wiz_level())

    {

        /*
         *  Unlike the fall_from_tree object in the forest, the fall_from_wall 
         *  object will not knock a player down automatically.  It repeatedly
         *  tests conditions in the room and eventually stabilizes the player's
         *  position or knocks him to the ground.  The conditions are complex,
         *  but if he is fighting alone against four or more defenders, he has
         *  no chance of success.

         *  Only one player can be teetering on the edge at a time!  If a
         *  second player tries to climb up while the first has not yet
         *  stabilized his position, he will find no room and be forced back
         *  down.

         *  This routine is only executed when the player gets here with a
         *  "climb" command from the wall outside.  Anyone who can fly or
         *  arrive by other magical means gets a big advantage from doing so.
         *    
         */

        if (member_array(BOG_FALL_FROM_WALL,
            deep_inventory(this_object())) != -1)

        {

            write("There's too much commotion at" +
                " the top! A heated battle at the edge" +
                " of the wall leaves you no place to climb" +
                " up. You are forced to retreat back" +
                " down the wall.\n");

            ob->command("$outside");

        }

        else

        {

            fall_from_wall = clone_object(BOG_FALL_FROM_WALL);
            fall_from_wall->move(ob);
            fall_from_wall->start_teetering();

            if (!ob->sanctimonian()) register_player(ob);

        }

    }

}

// Function:  destroy_scaffold()

/*

Purpose:  change the item descriptions and remove the exit when the adjacent
scaffold room is destroyed.  This function is called by the scaffold room.

Arguments:  none.

Returns: nothing.

*/

void
destroy_scaffold()

{

    add_item(({"scaffolds", "scaffold"}),
        "Scaffolds are built along other of the fortress interior," +
        " but there is no scaffold at this location on the wall.\n");

    add_item(({"planks", "plank", "broad planks", "broad plank", "floor"}),
        "You can see planks forming the floors of scaffolds along" +
        " the wall in other parts of the fortress.\n");

    add_item(({"timbers", "timber", "sturdy timbers", "sturdy timber",
        "framework", "solid framework"}),
        "Some timbers stand upright, and others are parallel" +
        " to the ground. They make a solid framework, but" +
        " you don't see anything here for them to support.\n");

    set_long("You stand atop the " + Face_Direction +
        " wall of a massive log fortress. Your footing on" +
        " the rounded surfaces of the logs is precarious at" +
        " best. Outside, the irregular sides of the fortress" +
        " lead straight down to the ground and inside just beside" +
        " you are some timbers that look to be part" +
        " of an unfinished construction project. Farther" +
        " below, the fortress interior is dotted with neat" +
        " rows of small structures.\n");

    remove_exit("inside");

}

// Function:  create_wall(location, direction, *adjacent_rooms)

/*

Purpose:  Create the room description and add standard attributes.

Arguments:
string containing the filename of this room,
string containing the direction which the outer wall faces,
string array containing adjacent rooms.

The same "filename" is assumed to be used in other directories for rooms
directly below or above this one.

Returns:  nothing.

*/

void
create_wall(string location, string direction, string *adjacent_rooms)

{

    This_Location = location;
    Face_Direction = direction;

    set_short("Atop the " + Face_Direction + " fortress wall");

    set_long("You stand atop the " + Face_Direction +
        " wall of a massive log fortress. Your footing on" +
        " the rounded surfaces of the logs" +
        " is precarious at best. Outside, the irregular sides" +
        " of the fortress lead straight down to the ground," +
        " and inside just beside you are rugged scaffolds made" +
        " of timbers and planks. Farther below, the fortress" +
        " interior is dotted with neat rows of small structures.\n");

    add_item(({"side", "irregular side", "sides", "irregular sides"}),
        "The sides of the fortress are constructed of" +
        " immense logs, tightly stacked and" +
        " securely joined together.\n");

    add_item(({"wall", "logs", "section"}),
        "The logs at this level are dry and smooth," +
        " although their rounded surfaces make for difficult" +
        " and dangerous walking so high above the ground outside.\n");

    add_item(({"log", "massive log"}),
        "This log looks like the trunk of a massive" +
        " " + ({"cedar", "pine", "fir", "spruce"})[random(4)] +
        " tree, expertly hewn and meticulously fitted" +
        " into the wall.\n");

    add_item(({"scaffolds", "scaffold"}),
        "The scaffolds serve as the floors for the upper levels" +
        " of the fortress interior. They're constructed" +
        " of broad planks supported by sturdy timbers.\n");

    add_item(({"planks", "plank", "broad planks", "broad plank", "floor"}),
        "The planks are laid on the framework of timbers to" +
        " form a spacious floor. Although they are broad and" +
        " fitted together to eliminate any gaps, they also look a" +
        " bit thin, perhaps not intended to hold great weight.\n");

    add_item(({"timbers", "timber", "sturdy timbers", "sturdy timber",
        "framework", "solid framework"}),
        "Some timbers stand upright, and others are parallel" +
        " to the ground. They're cut so that they interlock and" +
        " make a solid framework for the planks that form the" +
        " floor at this level.\n");

    add_item(({"log fortress", "fortress", "fortress interior",
        "inside", "interior"}),
        "The wall encloses an interior that has scaffolds" +
        " encircling an open center. The scaffolds block most of" +
        " your view of the activity in the center, but you can make" +
        " out a few small structures.\n");

    add_item(({"small structures", "structures", "neat rows",
        "rows", "center", "ground inside"}),
        "Some small structures arrayed in neat rows in the" +
        " center of the fortress are visible from up here," +
        " but beyond noting that they are wooden you" +
        " can't discern any details.\n");

    add_item(({"forest", "dark forest", "mist", "swirling mist",
        "bog", "dark bog", "trees", "tall trees"}),
        "The hill upon which the fortress stands is surrounded" +
        " by a bog shrouded in swirling mist. Tall trees rise" +
        " from the mist, the first ranks of a dark forest that" +
        " continues as far as you can see.\n");

    add_item(({"ground", "ground outside", "outside"}),
        "@@ground_desc@@");

    add_exit(BOG_INNER_UPPER + This_Location, "inside", "@@move_check@@", 1);
    add_exit(BOG_OUTER_MIDDLE + This_Location, "outside", 0, 10);

    if (adjacent_rooms[0])
        add_exit(adjacent_rooms[0], "north", "@@move_check@@", 1);

    if (adjacent_rooms[1])
        add_exit(adjacent_rooms[1], "northeast", "@@move_check@@", 1);

    if (adjacent_rooms[2])
        add_exit(adjacent_rooms[2], "east", "@@move_check@@", 1);

    if (adjacent_rooms[3])
        add_exit(adjacent_rooms[3], "southeast", "@@move_check@@", 1);

    if (adjacent_rooms[4])
        add_exit(adjacent_rooms[4], "south", "@@move_check@@", 1);

    if (adjacent_rooms[5])
        add_exit(adjacent_rooms[5], "southwest", "@@move_check@@", 1);

    if (adjacent_rooms[6])
        add_exit(adjacent_rooms[6], "west", "@@move_check@@", 1);

    if (adjacent_rooms[7])
        add_exit(adjacent_rooms[7], "northwest", "@@move_check@@", 1);

    /*
     *  The following exits are dummies to allow shouts from the top of the 
     *  wall to be heard at all levels of the fortress exterior.   
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
