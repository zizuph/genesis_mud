// OBJECT:  gingerbread punishment object

    /* Calia Domain

    HISTORY

    [2002-01-10] Created with glee by Uhclem from
        [C:\CALIA\YULEWARE\GINGER\PUNISH.DOC].

    PURPOSE

    A way to punish players who repeatedly log out and in as a way of
    persuading the baker to give them lots of free cookies.  He tends to forget
    players who have logged out and thus gives them another cookie the next
    time they drop by the bakery.  Getting a big collection of cookies is
    itself not a problem - they're needed for the gingerbread quest - but
    players must use methods to obtain them that are not a ridiculous strain on
    game resources.  */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

// FUNCTIONS

// Function:  end_punishment()

/*

Purpose:  release the player from his gingerbread torment.

Arguments:  none.

Returns:  joy to the afflicted player, but no variables or values.

*/

void
end_punishment()

{

    environment()->catch_msg("Somewhere in the distance, you" +
        " hear the faint sound of a frog munching on a" +
        " gingerbread cookie and cackling his little head off!\n");

    remove_object();

}

// Function:  phase_2_punishment()

/*

Purpose:  continue to inflict merciless torture on a player.

Arguments:  none needed, we're on a roll.

Returns:  misery and despair, but no variables or values.

*/

void
phase_2_punishment()

{

    object tp = environment();
    object room = environment(tp);
    object baker = present("donut", room);

    /*
     *  If the player has quickly left the bakery, the visible effects are 
     *  cancelled.    
     */

    if (baker)

    {

        baker->command("say to " + tp->query_real_name() + " " +
            ({
            "Looks like you're suffering from too much gingerbread!",
            "If you continue abusing the gingerbread you'll go blind!",
            "Hmmm... I think you may have had too much gingerbread.",
            "Gingerbread intoxication - the dark side of the yule season."
            })[random(4)] +
            " I'll have to put you on my list of people who can't" +
            " have any more cookies.");

        tp->command("blush");

    }

    set_alarm(600.0, 0.0, end_punishment);

}

// Function:  start_punishment()

/*

Purpose:  inflict merciless torture on a player, even more than usual.

Arguments:  none, the player to be tortured is already within our grasp.

Returns:  nothing but agony.

*/

void
start_punishment()

{

    object tp = environment();
    object room = environment(tp);
    object baker = present("donut", room);
    string tp_pronoun = tp->query_pronoun();
    string tp_object = tp->query_objective();
    string tp_possess = tp->query_possessive();

    /*
     *  This object should only be deployed in the bakery, and the baker should 
     *  be present.  If he isn't, there will be no obvious effect.  The
     *  presence of this object in the player's inventory will still prevent
     *  the receipt of cookies if he should encounter the baker later.    
     */

    if (baker)

    {

        tp->catch_msg("[A little green-and-red striped frog]" +
            " scurries between your legs as it rushes" +
            " outside and trips you!\n" +
            "You fall to the floor clumsily but get back" +
            " on your feet quickly.\n");

        tell_room(room,
            QCTNAME(tp) + " stumbles and falls face-down on" +
            " the floor with a loud THUD! " + capitalize(tp_pronoun) +
            " drags " + tp_object + "self to " + tp_possess +
            " feet, wobbly and confused, and barely" +
            " manages to mumble in the baker's general" +
            " direction: " +
            ({"gingerbreb", "glingerbed", "bingergleb"})[random(3)] +
            "?\n", ({tp}));

    }

    set_alarm(1.0, 0.0, phase_2_punishment);

}

// Function:  enter_env(ob_to, ob_from)

/*

Purpose:  called by system when this object moves to a new environment.

Arguments:  object moved to, object moved from.

Returns:  nothing.

*/

void
enter_env(object ob_to, object ob_from)

{

    object baker;
    object holiday_room;

    ::enter_env(ob_to, ob_from);

    /*
     *  This object will be moved to a player's inventory where it will begin 
     *  the punishment process.  When its task is complete, it will remove
     *  itself from the game.    
     */

    if (!ob_to || !interactive(ob_to))

    {

        return;

    }

    holiday_room = find_object(HOLIDAY_ROOM);

    if (!holiday_room)

    {

        holiday_room = call_other(HOLIDAY_ROOM, "this_object");

    }

    set_alarm(0.5, 0.0, start_punishment);

    tell_room(holiday_room,
        ob_to->query_name() + " is punished for abuse of gingerbread.\n");

    log_file("gingerbread_quest",
        ctime(time()) + " " + ob_to->query_name() +
        " is punished for abuse of gingerbread.\n");

}

// Function:  create_object()

void
create_object()

{

    set_no_show();
    set_name("_calia_gingerbread_punishment");
    set_short("gingerbread punishment");
    add_name("_calia_gingerbread_cookie");  /*  prevents receipt of cookies  */

    set_long("This invisible object is given to players" +
        " who abuse the gingerbread in Gelan.\n");

    /*
     *  PROPERTIES    
     */

    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_DROP, 1);

}
