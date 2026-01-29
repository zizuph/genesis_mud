// OBJECT:  fountain_protection

    /* Calia Domain

    HISTORY

    [2001-04-02] Created by Uhclem from [C:\CALIA\GELAN\SPECIALS\FOUNTAIN.DOC].

    [2001-04-24] Uhclem improved log text and corrected bug in kender
    processing.

    PURPOSE

    This object is the first step in the evolution of Gelan into more of a
    social and less of a combat area.  Both the rooms in Gelan's central square
    and the fountain will contain magical effects that make the town, its
    residents, and visitors more resistant to attack.

    This object gives a player magical protection against various evil forces.
    It is deployed by the fountain in downtown Gelan; players who are -
    generally speaking - good, wise, and brave are eligible to receive this
    protection when they drink the water, but it is not guaranteed.  The
    protection, once conferred, lasts while the player remains close to Gelan
    and Mt. Kyrus.  The farther he roams from these areas, the faster the
    protection will wear off.

    As of its original coding, the only protection offered is immunity to
    dragonfear (inflicted by Krynn/Ansalon dragons).  As other evils are
    deployed by other domains, protection against them may be added to this
    object.  A likely problem to be addressed in the near future is magic cast
    by evildoers; as with the dragons, both the rooms and the fountain may
    contain features that inhibit the effectiveness of such magic.  */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <ss_types.h>
#include <stdproperties.h>

#define LIVE_I_NO_DRAGONFEAR             "_live_i_no_dragonfear"
#define CALIA_AS_ROOM_PROPS              "_calia_as_room_props"
#define CALIA_I_FOUNTAIN_PROTECTION      "_calia_i_fountain_protection"

// GLOBAL VARIABLES

object Tp;                     /*  The player possessing this object  */
string *Areas_Visited = ({});  /*  Filenames of rooms visited by Tp  */
string *Props_Added = ({});    /*  Props added to Tp by this object  */
int Timer;                     /*  Determines duration of protection  */
int Decay_Rate;                /*  Subtracted from Timer every minute  */

// FUNCTIONS

// Function:  date_time_string()

/*

Purpose:  produces a short string containing current date/time for use in log
files.

Arguments:  none

Returns:  string

*/

string
date_time_string()

{

    /*
     *  Standard function ctime(time()) returns a string in the form: 
     *  Sun Apr  1 18:02:01 2001
     *  This function trims it down to:
     *  Apr 1 18:02:01
     *  There's no chance that records of fountain effects will ever be needed
     *  more than one year, but the seconds indicator may be useful.    
     */

    string *date_time_array = explode(ctime(time()), " ");

    return
        implode(date_time_array[1..sizeof(date_time_array)-2], " ");

}

// Function:  reset_effects()

/*

Purpose:  sets the starting values for the protection effects.  Called when
this object first enters a player's inventory and whenever the cycle is
restarted (such as when drinking from the fountain when this object is already
present).

Arguments:  none.

Returns:  nothing.

*/

void
reset_effects()

{

    /*
     *  According to the formula below, a player with DIS and WIS stats of 120 
     *  and alignment of 1200 (the max allowable) will get protection for a
     *  maximum of 30 minutes.  The timer is only invoked when the player moves
     *  beyond the Gelan - Mt. Kyrus region; as long as he stays within that
     *  region, the protection will not dissipate.

     *  Once the player leaves Calia, the decay rate will accelerate and cancel
     *  the protection quickly.  The purpose of the protection is to give
     *  defenders of Gelan an advantage over attackers; it is NOT intended to
     *  give players extra ability to go hunting evildoers elsewhere.    
     */

    Timer =
        (Tp->query_stat(SS_DIS) * 10 +
        Tp->query_stat(SS_WIS) * 10 +
        Tp->query_alignment()) / 120;

    Decay_Rate = 0;

    log_file("gelan_fountain",
        date_time_string() + " " +
        Tp->query_name() + " timer set to " +
        Timer + ".\n");

}

// Function:  remove_protection()

/*

Purpose:  cancels all effects of this object and removes it from the game.

Arguments:  none.

Returns:  nothing.

*/

int
remove_protection()

{

    while (sizeof(Props_Added))

    {

        Tp->remove_prop(Props_Added[0]);
        Props_Added -= ({Props_Added[0]});

    }

    log_file("gelan_fountain",
        date_time_string() + " " +
        Tp->query_name() + " loses protection.\n");

    remove_object();

    return 1;

}

// Function:  protection_cycle()

/*

Purpose:  check for conditions that cause the protection to dissipate; called
once a minute by repeating alarm.

Arguments:  none.

Returns:  nothing.

*/

void
protection_cycle()

{

    /*
     *  The name of the "area" the player is visiting is built from the 
     *  filename of the room he's in; each combination of domain name and the
     *  first subdirectory name constitute a distinct area.    
     */

    string current_area =
        implode(explode(file_name(environment(Tp)), "/")[2..3], "/");

    if (current_area == "Calia/gelan")

    {

        if (Decay_Rate > 0)

        {

            reset_effects();

        }

        return;

    }

    if (current_area == "Calia/palace" ||
        current_area == "Calia/glykron" ||
        current_area == "Calia/mountain")

    {

        return;

    }

    if (member_array(current_area, Areas_Visited) == -1)

    {

        Areas_Visited += ({current_area});
        Decay_Rate += 1;

        log_file("gelan_fountain",
            date_time_string() + " " +
            Tp->query_name() + " in " + current_area +
            ", timer=" + Timer +
            ", decay=" + Decay_Rate + ".\n");

    }

    Timer -= Decay_Rate;

    /*
     *  The following messages are only meaningful if the player has received 
     *  some protective effects (indicated by more than one element in
     *  Props_Added); otherwise they are suppressed.    
     */

    if (Timer < (Decay_Rate / 2) && sizeof(Props_Added) > 1)

    {

        Tp->catch_msg(({"You feel the invigorating effect of the" +
            " water from Gelan diminishing.\n",
            "You feel that you could use another drink from" +
            " the fountain in Gelan.\n",
            "Your throat feels dry, and nothing would feel quite" +
            " so good right now as a long, cool drink from" +
            " the fountain in Gelan.\n"})[random(3)]);

    }

    if (Timer < 0)

    {

        remove_protection();

    }

}

// Function:  enter_env(player, previous_env)

/*

Purpose:  called when an object enters a new environment.  Used here to start
the protection cycle.  This object should only enter an environment once - the
affected player - and then remove itself from the game when its work is done.

Arguments:  object being entered (player), object being left (usually null).

Returns:  nothing.

*/

void
enter_env(object player, object previous_env)

{

    /*
     *  First, get a list of any properties added to the player by the room. 
     *    
     */

    string *room_props;

    ::enter_env(player, previous_env);
    Tp = player;

    /*
     *  This object is designed to work only in a living object.  Should it be 
     *  deployed for any reason into a nonliving, just throw it away.    
     */

    if (!living(Tp))

    {

        remove_object();
        return;

    }

    /*
     *  A coding complication is introduced by the fact that the 
     *  _live_i_no_dragonfear property may be added to a player by both this
     *  object and by the Gelan room in which this object is deployed.  If the
     *  room has already added the property, it will be listed in a special
     *  property _calia_s_room_props, a text array.  If the no_dragonfear
     *  property is listed in the array, its name is deleted from the array,
     *  which means that this object rather than the room is now managing the
     *  player's dragonfear immunity.

     *  If the player has redundant properties that were not added by Calian
     *  rooms, we don't touch them - there's no telling where they came from,
     *  and we don't want to override any guild-supplied properties.  
     */

    room_props = Tp->query_prop(CALIA_AS_ROOM_PROPS);

    /*
     *  If the list of room-added properties is undefined, turn it into an 
     *  empty array so we don't get a runtime error when we run it through an
     *  array function.    
     */

    if (!room_props)

    {

        room_props = ({});

    }

    //  BEGIN LIST OF PROPERTIES ADDED BY THIS OBJECT

    /*
     *  LIVE_I_NO_DRAGONFEAR:  players get immunity from dragonfear for a 
     *  period of time depending on their WIS, DIS, and alignment.  Kender are
     *  not affected; Krynn/Ansalon wizards have designed special reactions to
     *  dragons for kenders and I have no reason to override them.  On a
     *  thematic note, kender are not native to Calia, nor were there any
     *  around during the wars or the time of the Confederation, so it's easy
     *  to excuse their omission from the fountain magic.    
     */

    if (Tp->query_race_name() != "kender" &&
        (!Tp->query_prop(LIVE_I_NO_DRAGONFEAR) ||
        member_array(LIVE_I_NO_DRAGONFEAR, room_props) != -1))

    {

        /*
         *  This object now takes over control of the dragonfear property.  Add 
         *  the property, record it in the list of properties controlled by
         *  this object, remove it from the list of properties controlled by
         *  the room, and then store the updated list of room properties in the
         *  player.    
         */

        Tp->add_prop(LIVE_I_NO_DRAGONFEAR, 1);
        Props_Added += ({LIVE_I_NO_DRAGONFEAR});
        room_props -= ({LIVE_I_NO_DRAGONFEAR});
        Tp->add_prop(CALIA_AS_ROOM_PROPS, room_props);

        Tp->catch_msg(
            ({"The water is cool and refreshing, ",
            "The water refreshes and invigorates you, ",
            "The clean, cool water gives you renewed vigour, "})[random(3)]
            +
            ({"and in the shadow of the great statue ",
            "and as you stand before the statue of Caliana" +
            " and the dragon "})[random(2)]
            +
            ({"you suddenly have an impertinent thought: ",
            "you find yourself entertaining" +
            " an audacious notion: "})[random(2)]
            +
            ({"if you were to come across a dragon like the" +
            " one in the statue, ",
            "should you come face-to-face with a real dragon, "})[random(2)]
            +
            ({"you'd probably spit right in its eye!\n",
            "you could take it on just like Caliana!\n"})[random(2)]
            );

    }

    //  END LIST OF PROPERTIES ADDED BY THIS OBJECT

    /*
     *  Add a property to the player to indicate that he's under the effect of 
     *  the fountain's magic.  For easy diagnosis, the fountain protection
     *  property is coded as a string that lists the properties for which this
     *  object is responsible.  It is possible that the player has received
     *  this object but not received any protective effects (kender, for
     *  example, never receive dragonfear protection).  In this case, the array
     *  Props_Added contains no elements.    
     */

    if (sizeof(Props_Added))

    {

        Tp->add_prop(CALIA_I_FOUNTAIN_PROTECTION,
            " *** this prop controls " +
            implode(Props_Added, " "));

        log_file("gelan_fountain",
            "                " +
            Tp->query_name() + " " +
            "dis=" + Tp->query_stat(SS_DIS) + " " +
            "wis=" + Tp->query_stat(SS_WIS) + " " +
            "align=" + Tp->query_alignment() + "\n" +
            "                " +
            "props: " + implode(Props_Added, " ")  + "\n");

    }

    else

    {

        Tp->add_prop(CALIA_I_FOUNTAIN_PROTECTION, 1);

        log_file("gelan_fountain",
            "                " +
            Tp->query_name() + " " +
            "dis=" + Tp->query_stat(SS_DIS) + " " +
            "wis=" + Tp->query_stat(SS_WIS) + " " +
            "align=" + Tp->query_alignment() + "\n" +
            "                " +
            "props: none\n");

    }

    /*
     *  Now add the protection property itself to the Props_Added array.  If 
     *  the player has received no protective effects, Props_Added will contain
     *  only one element.    
     */

    Props_Added += ({CALIA_I_FOUNTAIN_PROTECTION});

    /*
     *  Set the timer and start the cycle.    
     */

    reset_effects();
    set_alarm(60.0, 60.0, protection_cycle);

}

// Function:  init()

/*

Purpose:  define commands available in this object (called by system when
object enters a player's inventory).  This particular command is for easy
removal of the object during testing.

Arguments:  none

Returns:  nothing

*/

void
init()

{

    ::init();
    add_action(remove_protection, "calia_unprotect");

}

// OBJECT DEFINITION

void
create_object()

{

    set_no_show();
    set_name("_calia_fountain_protection");
    set_short("_calia_fountain_protection");
    set_long("_calia_fountain_protection");

    /*
     *  PROPERTIES    
     */

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);

}
