// OBJECT:  black ribbon

    /* Calia Domain

    HISTORY

    [2004-12-23] Created from [C:\CALIA\YULEWARE\RIBBON_B.DOC] by Uhclem.

    PURPOSE

    At the request of several players, I created this ribbon to tie around a
    guelph.  It makes a most unpleasant Yule gift that can delivered by the
    Gifteroo. */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

// GLOBAL VARIABLES

string Color;

// FUNCTIONS

// Function:  query_recover()

/*

Purpose:  this object is never recovered.

Arguments:  none.

Returns:  0.

*/

int
query_recover()

{

    return 0;

}

// Function:  query_ribbon_config()

/*

Purpose:  return the color of the ribbon.  This function is provided purely for
compatibility with Yule routines that normally handle ribbons of various
colors.

Arguments:  none.

Returns:  string containing the color description.

*/

string
query_ribbon_config()

{

    return "black";

}

// Function:  tie_ribbon(around_what)

/*

Purpose:  tie the ribbon around a guelph to produce a wrapped present.

Arguments:  string indicating around what to tie the ribbon.

Returns:  0/1.

*/

int
tie_ribbon(string around_what)

{

    object tp = this_player();
    object this_ribbon;
    object target;
    object wrapped_fruit;

    if (environment() != tp)

    {

        return 0;

    }

    if (!stringp(around_what))

    {

        notify_fail("Tie what around what?\n");
        return 0;

    }

    if (parse_command(around_what, all_inventory(tp),
        "%o 'around' %o", this_ribbon, target) ||
        this_ribbon != this_object())

    {

        if (this_ribbon != this_object() || !target)

        {

            notify_fail("Tie what around what?\n");
            return 0;

        }

        if (wildmatch(FRUITS + "*", file_name(target)) &&
            wildmatch("*guelph*", around_what))

        {

            /*
             *  To avoid the unwanted insertion of an article, use 
             *  query_short() instead of short when getting the short
             *  description of a heap item.    
             */

            write("You tie the " + short() +
                " around the " + target->query_short() + ".\n");

            say(QCTNAME(tp) + " ties a " + short() +
                " around a " + target->query_short() + ".\n");

            wrapped_fruit = clone_object(FRUITS + "wrapped_guelph");

            wrapped_fruit->move(tp);
            target->remove_object();
            remove_object();

        }

        else

        {

            write("The " + short() + " is ill-suited for this purpose.\n");

        }

        return 1;

    }

    else

    {

        notify_fail("Tie what around what?\n");
        return 0;

    }

}

// Function:  blow_me_away()

/*

Purpose:  get rid of this object; invoked only by enter_env below.

Arguments:  none.

Returns:  nothing.

*/

void
blow_me_away()

{

    /*
     *  The only reason not to remove this object is if it has been picked up 
     *  by someone.    
     */

    if (!living(environment()))

    {

        tell_room(environment(), "The " + short() + " " +
            ({
            "blows away.",
            "slinks away with a snakelike motion.",
            "rises and floats out of sight.",
            "curls itself into a ball, getting ever tighter" +
            " and smaller until it disappears altogether!",
            "bends until its two ends touch and form a loop," +
            " and then a mysterious force sets it upright and" +
            " rolls it away.",
            "disintegrates into the thousands of flower petals" +
            " from which it was made, and the petals immediately" +
            " scatter in all directions.",
            "melts and dissipates.",
            "flutters away like a butterfly."
            })[random(8)] + "\n");

        remove_object();

    }

}

// Function:  enter_env(ob_to, ob_from)

/*

Purpose:  called by system when this object moves to a new environment; used
here to get rid of the ribbon when it is dropped.

Arguments:  object moved to, object moved from.

Returns:  nothing.

*/

void
enter_env(object ob_to, object ob_from)

{

    ::enter_env(ob_to, ob_from);

    /*
     *  This test makes sure that we don't generate runtime errors when the 
     *  object is moved around by any wizard commands or system functions,
     *  especially the split and merge heap routines.    
     */

    if (ob_to && ob_to->query_prop(ROOM_I_IS))

    {

        if (query_verb() == "drop" || query_verb() == "$drop")

        {

            set_alarm(0.0, 0.0, blow_me_away);

        }

        else

        {

            if (random(2))

            {

                set_alarm(12.0, 0.0, blow_me_away);

            }

            else

            {

                set_alarm(30.0, 0.0, blow_me_away);

            }

        }

    }

}

// Function:  init

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
    add_action(tie_ribbon, "tie");

}

// Function:  hook_smelled()

/*

Purpose:  add smell characteristics to this object.

Arguments:  none.

Returns:  nothing.

*/

void
hook_smelled()

{

    write(
        ({
        "It reveals the subtle fragrance of rodent" +
        " hairs and insect fragments.\n",
        "It smells as if someone had been hiding it in his armpit" +
        " for a long time.\n",
        "It smells like one hand clapping.\n",
        "One might characterize the aroma as a real rip-roarer.\n",
        "Nothing living smells like this, so you feel confident" +
        " that it's not some kind of monster in disguise.\n"
        })[random(5)]);

}

// OBJECT DEFINITION

void
create_object()

{

    /*
     *  DESCRIPTION    
     */

    set_name("ribbon");

    add_adj(({"crude", "black"}));

    set_long("The " + short() + " ribbon has a rough surface" +
        " and ragged edge. It can probably be tied" +
        " around something, perhaps to secure a small bundle" +
        " of rubbish or restrain some minor vermin.\n");

    add_item(({"surface", "rough surface"}),
        "It seems limp and greasy, as if it had been stored under" +
        " a bunch of rotten bananas. It seems to have been made" +
        " to only hold firmly onto a specific surface.\n");

    add_item(({"edge", "ragged edge"}),
        "Obviously whoever cut the edge didn't have a proper" +
        " knife or scissors: it looks as if it has been" +
        " hacked, chewed, and torn by blindfolded drunkards on a" +
        " leaky boat in the middle of a hurricane.\n");

    /*
     *  PROPERTIES    
     */

    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 11);

    setuid();  /*  "uid" settings required for cloning. */
    seteuid(getuid());
}
