// ROOM:  base_hill.c

    /*  Calia Domain

    HISTORY

    [99-06-25] created by Uhclem from
    [D:\CALIA\CENTRAL\BOG\OUTER\GROUND\BASE_HIL.DOC].

    PURPOSE

    This is the base for ground-level rooms surrounding the Sanctimonian
    fortress.

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

object *Sentry_Rooms;  /* fortress rooms that can observe this room */
string Fortress_Direction;  /* compass direction pointing to the fortress */
string Opposite_Direction;  /*  opposite compass direction to the above  */
string Sentry_Text;  /*  used to compute 'sentry' description  */
int Sentry_Range;  /*  distance (in rooms) to nearest sentry position  */
int Sentry_Alert;  /*  indicates whether sentry is looking at this room  */

// FUNCTIONS

// Function:  update_sentry_text(text)

/*

Purpose:  called by the fortress wall rooms to update the description of the
sentries (or other livings) visible from the ground.

Arguments:  string containing a complete sentence or nothing at all if there
are no livings present.

Returns:  nothing.

*/

void
update_sentry_text(string text)

{

    Sentry_Text = text;

}

// Function:  sentry_description()

/*

Purpose:  returns the appropriate value for the add_item 'sentry'.

Arguments:  none.

Returns:  string containing complete description.

*/

void
sentry_description()

{

    string text;

    if (Sentry_Text == "")

    {

        text = "You see nobody on top of the fortress wall right now.";

    }

    else if (wildmatch("*fight*", Sentry_Text))

    {

        text = Sentry_Text;

    }

    else if (Sentry_Alert)

    {

        if (wildmatch("*sentries*", Sentry_Text))

        {

            text = Sentry_Text + " One of them seems to be" +
                " peering in your direction.";

        }

        else

        {

            text = Sentry_Text + " He seems to be" +
                " peering in your direction.";

        }

    }

    else

    {

        if (wildmatch("*sentries*", Sentry_Text))

        {

            text = Sentry_Text + " None of them seem to be" +
                " looking in your direction right now.";

        }

        else

        {

            text = Sentry_Text + " He seems to be looking at" +
                " something far away from you.";

        }

    }

    return text + "\n";

}

// Function:  sentry_look_away()

/*

Purpose:  let the nearest sentry go on his rounds after failing to notice
anybody lurking in this room.  If he did indeed notice somebody already, this
function won't make him forget it!

Arguments:  none.

Returns:  nothing.

*/

void
sentry_look_away()

{

    Sentry_Alert = 0;

}

// Function:  sentry_look_here()

/*

Purpose:  let the nearest sentry notice some movement in this room whenever
somebody enters.  He'll look straight at this room for a random number of
seconds, then go observe some other area.  If a player moves while the sentry
is watching this room, it's likely he will be detected.

Arguments:  none.

Returns:  nothing.

*/

void
sentry_look_here()

{

    /*
     *  The idea behind the two delay periods is to let players get accustomed 
     *  to the 5-second delay and then be surprised by the 15 once in a while.
     *  If they move too soon, their cover is blown.    
     */

    Sentry_Alert = 1;

    if (random(5))

    {

        set_alarm(5.0, 0.0, sentry_look_away);

    }

    else

    {

        set_alarm(15.0, 0.0, sentry_look_away);

    }

}

// Function:  add_sightline(room)

/*

Purpose:  add a sightline definition.

Arguments:  object representing the fortress room which has a sightline to this
room.

Returns:  nothing.

*/

void
add_sightline(object room)

{

    if (member_array(room, Sentry_Rooms) == -1)

    {

        Sentry_Rooms += ({room});

    }

}

// Function:  enter_inv(object, from_object)

/*

Purpose:  update information for observers on the fortress walls.

Arguments:  object entering the room, object from whence it came.

Returns:  nothing.

*/

void
enter_inv(object ob, object from)

{

    object *armours_worn = ({});
    int stealth_factor;
    int m;
    int n;

    ::enter_inv(ob, from);

    /*
     *  Objects with a hide value of 100 are invisible, so they are never 
     *  observed from the fortress walls.  Players must wait to move until the
     *  sentry isn't looking in their direction.  If they don't, they leave the
     *  room with the dreaded CALIA_DETECTED property which pretty much cuts
     *  their stealth factor down to a level where any newbie can spot them as
     *  they enter the next room.  They can determine the sentry's disposition
     *  by periodically looking at the fortress, and the waiting period for him
     *  to look elsewhere is never more than 15 seconds.  Players wearing green
     *  and/or brown armours are camouflaged and get extra stealth points.    
     */

    if (!living(ob)) return;

    register_player(ob);

    if (ob->query_prop(OBJ_I_HIDE) < 100)

    {

        stealth_factor = ob->query_prop(OBJ_I_HIDE) +
            ((Sentry_Range) * 5) - ob->query_prop(CALIA_DETECTED);

        armours_worn = ob->query_worn();
        n = sizeof(armours_worn);

        for (m = 0; m < n; m += 1)

        {

            if (wildmatch("*green*", armours_worn[m]->short()) ||
                wildmatch("*brown*", armours_worn[m]->short()))

            {

                stealth_factor += 5;

            }

        }

        n = sizeof(Sentry_Rooms);

        for (m = 0; m < n; m += 1)

        {

            Sentry_Rooms[m]->add_sighting(Sentry_Range, stealth_factor,
                Opposite_Direction, ob);

        }

        sentry_look_here();

    }

}

// Function:  leave_inv()

/*

Purpose:  remove the departing object's sighting reference from the fortress
wall rooms.

Arguments:  object leaving the room, object destination.

Returns:  nothing.

*/

void
leave_inv(object ob, object dest)

{

    int m;
    int n;

    ::leave_inv(ob, dest);

    if (living(ob))

    {

        n = sizeof(Sentry_Rooms);

        for (m = 0; m < n; m += 1)

        {

            Sentry_Rooms[m]->remove_sighting(ob);

        }

    }

}

// Function:  check_sightline()

/*

Purpose:  If the local sightline has not already been checked, get a drudge (a
tiny invisible object) and move it in the direction of the fortress until no
exit in that direction exists, all the while keeping a list of rooms
transited.  If the room where the drudge stops is at the foot of the fortress,
send it to the upper level and register the sight lines between the fortress
and ground rooms.  If not (an error in room configuration), simply remove this
drudge.

Arguments:  none.

Returns:  nothing.

*/

void
check_sightline()

{

    string *compass = ({"north", "northeast", "east", "southeast", "south",
        "southwest", "west", "northwest"});

    object drudge = clone_object(DRUDGE);
    object room = this_object();
    string *text_array;
    int k;
    int n;

    Sentry_Rooms = ({});
    Sentry_Text = "";
    Sentry_Range = 0;
    Sentry_Alert = 1;

    drudge->move(room);
    text_array = room->query_exit_cmds();
    n = member_array(Fortress_Direction, text_array);

    /*
     *  The following loop moves the drudge in a straight line all the way to 
     *  the room at the base of the fortress (or just out into the bog if
     *  there's an error).  Hill rooms always have seven or eight exits.
     *  Excluding the dummy exits named "u", a room at the corner of the
     *  fortress will have six exits, one at the side will have 5, so we can
     *  use this pattern to detect the end of the run, and we also use six as
     *  the limit of the run since the hill extends at most 5 rooms in any
     *  direction from the fortress.    
     */

    while (sizeof(text_array - ({"u"})) > 6 && Sentry_Range < 6)

    {

        drudge->move(environment(drudge)->query_exit_rooms()[n]);
        text_array = environment(drudge)->query_exit_cmds();
        n = member_array(Fortress_Direction, text_array);
        Sentry_Range += 1;

    }

    /*
     *  Assuming that the drudge has indeed stopped at the base of the fortress 
     *  wall, we go up to the top and register that room and the adjacent wall
     *  rooms with the collection of hill rooms.    
     */

    text_array = explode(file_name(environment(drudge)), "/");

    if (!drudge->move(implode(text_array[0..5], "/") + "/upper/" +
        text_array[7]))  /* zero indicates move was successful. */

    {

        room = environment(drudge);
        room->add_ground_room(this_object());
        add_sightline(room);
        text_array = room->query_exit();
        k = sizeof(text_array);

        for (n = 1; n < k; n += 3)

        {

            if (member_array(text_array[n], compass) != -1)

            {

                room = environment(drudge);
                drudge->move(text_array[n-1]);
                add_sightline(environment(drudge));
                environment(drudge)->add_ground_room(this_object());
                drudge->move(room);

            }

        }

    }

    drudge->remove_object();

    switch (Sentry_Range)

    {

        case 0:

        set_short("On the " + Opposite_Direction +
            " side of a log fortress");

        set_long("You are on the " + Opposite_Direction +
            " side of an immense log fortress. The ground" +
            " slopes away from the fortress in all" +
            " directions and is covered with tree stumps and" +
            " bushes on a carpet of thick grass. At the bottom" +
            " of the hill a bog lies in the shadow of a" +
            " dark forest and further concealed by swiring mist.\n");

        break;

        case 1:

        set_short("A short distance " + Opposite_Direction +
            " of a log fortress");

        set_long("An immense log fortress stands only a" +
            " short distance to the " + Fortress_Direction +
            " atop a hill studded with tree stumps and" +
            " bushes. The ground slopes down to the" +
            " " + Opposite_Direction + " and is bordered less" +
            " than a hundred meters away by a bog" +
            " shrouded in swirling mist. Both fortress and bog," +
            " equally dark and forbidding, contrast sharply" +
            " with the bright sunlight illuminating the hill.\n");

        break;

        case 2:

        set_short(capitalize(Opposite_Direction) + " of a log fortress");

        set_long("You are about halfway up a hill studded" +
            " with tree stumps and bushes. The ground is" +
            " brilliantly sunlit and slopes upward to" +
            " the " + Fortress_Direction + " where" +
            " an immense log fortress stands alone. On all" +
            " sides of the hill the ground descends into a" +
            " bog shrouded in swirling mist.\n");

        break;

        case 3:

        set_short("On the " + Opposite_Direction + " slope of a hill");

        set_long("Tree stumps dot the carpet of thick grass," +
            " and bushes of all sizes grow vigorously here. To" +
            " the " + Fortress_Direction + " the hilltop is" +
            " dominated by an immense log fortress," +
            " its straight sides rising in sharp contrast" +
            " to the gentle slope. The hill is brilliantly" +
            " sunlit and encircled by a dark bog obscured by" +
            " the tall trees that grow from it and the mist" +
            " that swirls between them.\n");

        break;

        case 4:

        set_short("On a hill that rises to the " + Fortress_Direction);

        set_long("The ground here rises to the" +
            " " + Fortress_Direction + ", and about a" +
            " hundred meters in that direction an" +
            " immense log fortress dominates the brilliantly" +
            " sunlit hilltop. The hill is ringed by a dark" +
            " bog cloaked in swirling mist, and the carpet of" +
            " thick grass is studded with numerous tree stumps" +
            " and bushes of various size.\n");

        break;

        default:

        set_short("Near a bog at the bottom of a hill");

        set_long("The ground here rises to the" +
            " " + Fortress_Direction + ", a gentle sunlit slope" +
            " that culminates in a hilltop dominated by" +
            " an immense log fortress. The hill is ringed by" +
            " a dark bog cloaked in swirling mist, and the" +
            " carpet of thick grass is studded with" +
            " numerous tree stumps and bushes of various size.\n");

    }

    /*
     *  Don't itemize the exits if they occur in all directions.    
     */

    if (sizeof(query_exit_cmds()) == 8)

    {

        set_noshow_obvious(1);

        set_long(query_long() + "There are obvious" +
            " exits in every direction.\n");

        set_short(query_short() + ".\nThere are obvious" +
            " exits in every direction");

    }

    /*
     *  If we are missing one exit, it MUST be because we are adjacent to a 
     *  diagonal fortress wall in a location where we can't reach the wall
     *  directly.  This situation is analogous to the situation on a chessboard
     *  in which a bishop can't capture a rook sitting on the wrong color
     *  square regardless of how it maneuvers.  To give some rational reason
     *  for being so close yet unable to touch the wall, I put a buttress
     *  outside the fortress to block the way.    
     */

    else

    {

        text_array = explode(query_long(), ".");

        set_long(text_array[0] + "." +
            " A buttress of long straight logs supports the" +
            " wall here. Driven deep into the ground, it rises at" +
            " a sharp angle and forms part of the smooth joint at" +
            " the corner of the fortress. " +
            implode(text_array[1..(sizeof(text_array) - 1)], "."));

        add_item(({"buttress", "straight logs", "long straight logs"}),
            "The buttress is made of logs that are" +
            " particularly long and straight. All of their" +
            " branches have been removed and any" +
            " irregularities have been smoothed out.\n");

        add_item(({"joint", "smooth joint", "seamless joint",
            "joints", "smooth joints", "seamless joints"}),
            "While most of the logs forming the fortress wall appear" +
            " to be in their natural state, the corners" +
            " have been expertly crafted into smooth," +
            " seamless joints supported by buttresses. If" +
            " there's any weakness in the fortress, it's certainly" +
            " not at the corners.\n");

    }

}

// Function:  get_short_desc()

/*

Purpose:  generate the short description by calling check_sightline and
generating the appropriate "perspective" text.  The long description is set at
the same time.

Arguments:  none.

Returns:  string containing the room's short description.

*/

string
get_short_desc()

{

    check_sightline();
    return query_short();

}

// Function:  get_long_desc()

/*

Purpose:  generate the long description by calling check_sightline and
generating the appropriate "perspective" text.  The short description is set at
the same time.

Arguments:  none.

Returns:  string containing the room's long description.

*/

string
get_long_desc()

{

    check_sightline();
    return query_long();

}

// Function:  create_hill(direction, *adjacent_rooms)

/*

Purpose:  Create the room description and add standard attributes.

Arguments:  string containing the compass direction to the fortress, string
array of adjacent room file names.

Returns:  nothing.

*/

void
create_hill(string direction, string *adjacent_rooms)

{

    string *compass = ({"north", "northeast", "east", "southeast", "south",
        "southwest", "west", "northwest"});

    int hill_fatigue;
    int n;

    Fortress_Direction = direction;
    Opposite_Direction = compass[(member_array(direction, compass) + 4) % 8];

    set_short("@@get_short_desc@@");
    set_long("@@get_long_desc@@");

    add_item(({"bog", "mist-enshrouded bog", "trees", "tall trees"}),
        "The bog and trees surround the fortress in" +
        " every direction, separated from its walls by a circle" +
        " of ground that, judging from the stumps," +
        " has been painstakingly cleared of many large trees.\n");

    add_item(({"tree stump", "tree stumps", "stump", "stumps",
        "grass", "lush grass"}),
        "The stumps are proof that at one time massive trees" +
        " grew here. Between the stumps grow many bushes atop a" +
        " carpet of lush grass, both obviously thriving" +
        " without the stunting effect of" +
        " an overshadowing forest.\n");

    add_item(({"fortress", "log fortress", "hilltop"}),
        "The high vertical walls of the fortress stand in stark" +
        " contrast to the gentle slope of the hill. It appears" +
        " to be roughly octagonal in shape, with the" +
        " walls built higher at the corners than at the" +
        " sides, giving an impression of a rough" +
        " wooden crown centered precisely on the hilltop." +
        " You see no gates, doors, or windows; indeed, no" +
        " sign at all that there is any provision for letting" +
        " people enter or exit. Occasionally you see figures" +
        " - perhaps sentries - walking on the top.\n");

    add_item(({"sunlight", "sun", "high sun", "sky", "cloud", "clouds"}),
        "The sky is bright with only a few clouds. The high sun" +
        " hurts your eyes and blurs your vision a bit when you try" +
        " to look at the top of the fortress.\n");

    add_item(({"wall", "walls", "logs", "top"}),
        "The walls are made of logs of prodigious size. They" +
        " have been fitted together precisely so that no gaps" +
        " are visible. Each corner is smooth and seamless and rises" +
        " to a point that's higher than the surrounding wall.\n");

    add_item(({"corner", "corners", "point", "points"}),
        "Great care and expertise has obviously gone into" +
        " the construction of the corners. They are smoothest" +
        " part of the fortress and rise to a point well above the" +
        " rest of the wall.\n");

    add_item(({"figure", "figures", "sentry", "sentries"}),
        "@@sentry_description@@");

    /*
     *  The following items are crucial hints.  Players who sneak (as opposed 
     *  to ordinary walking) up to the fortress may be overlooked by the
     *  sentries and thus mount a surprise attack.  Wearing green and/or brown
     *  armours also helps.    
     */

    add_item(({"hill", "ground", "circle", "circle of ground",
        "slope", "gentle slope", "sunlit slope"}),
        "A circle of ground covered with lush grass and" +
        " studded with many stumps and bushes extends in" +
        " every direction from the fortress. It makes" +
        " a kaleidoscopic pattern of various shades of green and" +
        " brown as it descends gently toward the mist-enshrouded" +
        " bog less than a hundred meters from the walls.\n");

    add_item(({"pattern", "kaleidoscopic pattern"}),
        "The random mix of all shades of green and brown" +
        " among the bushes, stumps, and grass here" +
        " is certainly distracting. You've looked at it for only" +
        " a moment, and already the kaleidoscopic pattern" +
        " interferes with your ability to" +
        " discern individual objects.\n");

    add_item(({"bushes", "bush"}),
        "Some grow low to the ground, others tall as a small" +
        " tree. They don't seem to be of any particularly" +
        " rare or useful variety, but they do concern you as" +
        " you realize that they could provide good cover" +
        " for anyone who might be sneaking around here.\n");

    /*
     *  EXITS    
     */

    /*
     *  Let's make it harder to walk uphill than downhill!    
     */

    for (n = 0; n < 8; n += 1)

    {

        if (adjacent_rooms[n])

        {

            if (Fortress_Direction == compass[n])

            {

                hill_fatigue = 8;  /*  straight uphill  */

            }

            else if (wildmatch("*" + Fortress_Direction + "*", compass[n]) ||
                wildmatch("*" + compass[n] + "*", Fortress_Direction))

            {

                hill_fatigue = 4;  /*  angle uphill  */

            }

            else

            {

                hill_fatigue = 2;  /*  sideways or downhill  */

            }

            add_exit(adjacent_rooms[n], compass[n], 0, hill_fatigue);

        }

    }

    /*
     *  PROPERTIES    
     */

    add_prop(ROOM_I_HIDE, 75);  /*  Some good hiding places. */
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
