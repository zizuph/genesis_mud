// OBJECT:  open flask

    /* Calia Domain

    HISTORY

    [04-12-23] Created from [C:\CALIA\YULEWARE\FLASKS\FLASK_OP.DOC] by Uhclem.

    PURPOSE

    An open flask of volatile elixir that quickly evaporates.  Players can
    inhale the fumes to enjoy some harmless changes to the standard emotes.
    Type of change is dependent on elixir color.  */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>
#include <language.h>
#include <ss_types.h>
#include "defs.h"

// FUNCTIONS

// Function:  is_calian_yule_flask()

/*

Purpose:  identifies this object as a genuine Calian yule flask - your
guarantee of quality!

Arguments:  none.

Returns:  1.

*/

int
is_calian_yule_flask()

{

    return 1;

}

// Function:  query_recover()

/*

Purpose:  prevent this object from ever being recovered.

Arguments:  none.

Returns:  0.

*/

int
query_recover()

{

    return 0;

}

// Function:  inhale_fumes()

/*

Purpose:  inhale the fumes from the elixir; player receives invisible object
that applies changes to standard emotes.  A different object producing
different changes is applied for each color.

Arguments:  string specifying fumes.  If the player to tries to inhale the
flask or the liquid he gets an appropriate response.

Returns:  0/1

*/

int
inhale_fumes(string command_text)

{

    object tp = this_player();
    object flask;
    object fume_effect;
    int n;

    /*
     *  First, check to see if the player is trying to inhale an object in his 
     *  inventory (one never knows).  If it's an object, it's either this one -
     *  in which case we have our own response - or another that can take care
     *  of its own processing.    
     */

    if (parse_command(command_text, all_inventory(tp),
        " %o ", flask))

    {

        if (flask == this_object())

        {

            write("You try to inhale the " + short() + ", but it" +
                " won't fit into your nostril, so you" +
                " try the fumes instead.\n");

            command_text = "fumes";

        }

    }

    if (!command_text || !wildmatch("*fume*", command_text))

    {

        notify_fail("Inhale what? The fumes?\n");

        return 0;

    }

    /*
     *  Filenames of the effects correspond to the colors of the flasks.    
     */

    fume_effect = clone_object(FLASKS + query_adj(1)[2] + "_effect");
    fume_effect->move(tp);

    write("You inhale the " + query_adj(1)[2] + " fumes and" +
        " suddenly feel that you can express your sentiments" +
        " about Yule better than ever before regardless" +
        " of whether the season makes you want to bounce, brighten," +
        " laugh, mumble, panic, ponder, smirk, or tingle.\n");

    tell_room(environment(tp),
        QCTNAME(tp) + " inhales the " + query_adj(1)[2] +
        " fumes and, with a peculiar " + query_adj(1)[2] +
        " twinkle in " + tp->query_possessive() + " eye," +
        " briefly grins a particularly mischevious grin.\n.", tp);

    return 1;

}

// Function:  hook_smelled()

/*

Purpose:  give the player a clue about using this object.

Arguments:  none.

Returns:  nothing.

*/

void
hook_smelled()

{

    write("There's some vague aroma of " +
        ({"cranberry", "turkey", "ham", "mint", "coal tar"})[random(5)] +
        ", perhaps" +
        " mixed with " +
        ({"nutmeg", "eggnog", "honey", "sugar", "blood"})[random(5)] +
        " and " +
        ({"cloves", "apple", "sage", "pepper", "brimstone"})[random(5)] +
        ", but you can't really tell for sure unless you" +
        " inhale the fumes.\n");

}

// Function:  how_many_flasks()

/*

Purpose:  cause problems if too many flasks are gathered in one place, whether
in a player's inventory or in a container or room.

Arguments:  none.

Returns:  nothing.

*/

void
how_many_flasks()

{

    object tp = this_player();

    int num_flasks =
        sizeof(filter(all_inventory(tp), &->is_calian_yule_flask()));

    if (num_flasks > (random(tp->query_stat(SS_DEX))/10)+2)

    {

        tell_room(environment(),
            capitalize(LANG_THESHORT(this_object())) + " " +
            ({
            "gently strikes another flask, producing a cheerful 'ping!'" +
            " that causes all the other flasks to vibrate and" +
            " pronglong the note. Then the " + short() + "" +
            " cracks into several pieces, and each piece" +
            " continues breaking into ever smaller pieces as you" +
            " watch in utter fascination until the pieces become too" +
            " tiny to be seen.",
            "jostles another flask, and the two flicker" +
            " brightly, even fiercely, for a moment as if" +
            " arguing over something; in the end the " + short() +
            " droops, folds up in a way that one rarely sees" +
            " a spherical object fold, and implodes, leaving" +
            " no trace behind.",
            "smashes against another flask and" +
            " is instantly destroyed!",
            "is instantaneously and inexplicably absorbed by one" +
            " of the other flasks!",
            "hides behind one of the other flasks, and then it doesn't" +
            " seem to be there at all!"
            })[random(5)] + "\n");

    }

        remove_object();

}

// Function:  flask_self_destruct()

/*

Purpose:  get rid of the flask whether it has been used or not.

Arguments:  none.

Returns:  nothing.

*/

void
flask_self_destruct()

{

    object whereami = environment();

    if (living(whereami))

    {

        whereami = environment(whereami);

    }

    tell_room(whereami,
        capitalize(LANG_THESHORT(this_object())) + " stops" +
        " emitting fumes and crumbles to dust.\n");

    remove_object();

}

// Function:  smash_flask()

/*

Purpose:  provide a message to the room and remove the object.  This function
is called with a 0.01 second delay to allow it to "hit the floor" after it is
dropped.

Arguments:  none.

Returns:  nothing.

*/

void
smash_flask()

{

    if (environment()->query_prop(ROOM_I_IS))

    {

        tell_room(environment(),
            capitalize(LANG_THESHORT(this_object())) + " " +
            ({
            "strikes the ground with tremendous impact and smashes" +
            " into millions - yes, literally millions - of tiny pieces" +
            " that disperse in generally indescribable directions.",
            "plumments downward with ever-increasing velocity until" +
            " it is abruptly stopped by the ground, whereupon it ceases" +
            " to be a flask but instead magically transforms into a" +
            " little cloud of crystalline dust that drifts away.",
            "impertinently refuses to fall and shatter in the customary" +
            " manner of a fragile object and instead floats" +
            " away until it disappears from view.",
            "falls to the ground and miraculously bounces once, then" +
            " twice, but on the third impact smashes into tiny" +
            " bits that disperse in every direction.",
            "is subsumed into the unknowable."
            })[random(5)] + "\n");

        remove_object();

    }

}

// Function:  enter_env(ob_to, ob_from)

/*

Purpose:  called by system when this object moves to a new environment; used
here to detect when the flask is dropped or when too many flasks are in the
same environment.

Arguments:  object moved to, object moved from.

Returns:  nothing.

*/

void
enter_env(object ob_to, object ob_from)

{

    int n;

    ::enter_env(ob_to, ob_from);

    if (ob_to->query_prop(ROOM_I_IS))

    {

        if (query_verb() == "drop"  || query_verb() == "$drop")

        {

            set_alarm(0.1, 0.0, smash_flask);

        }

        else

        {

            set_alarm(0.1, 0.0, how_many_flasks);

        }

    }

    /*
     *  The open flask is entering a player's inventory.  Set an alarm to 
     *  self-destruct if it is not used quickly.    
     */

    set_alarm(15.1, 0.0, flask_self_destruct);

}

// Function:  configure_flask(flask_type)

/*

Purpose:  create descriptive text appropriate to the color and texture.
    Called by the original sealed flask when a player breaks the seal.

Arguments:  string array containing adjectives of sealed flask.

Returns:  nothing.

*/

void
configure_flask(string *words)

{

    string adj = words[0];
    string color = words[1];

    set_adj("open");
    add_adj(words);

    set_long("The " + short() + " is quite tiny, barely bigger" +
        " than a gnome's little toe, and shaped more-or-less like" +
        " a sphere. A liquid within glows faintly with an eerie," +
        " flickering light, and it bubbles gently through the" +
        " opening in the flask as it vaporizes" +
        " into shimmering" + color + " fumes.\n");

    add_item(({"seal", "clay", "bit of clay", "opening"}),
        "There's a bit of clay around the opening in the" +
        " flask, suggesting that it was once sealed.\n");

    add_item(({"glow", "light", "flickering light"}),
        "The glow is pale " + color + " and flickers" +
        " erratically like a sputtering lamp or candle that's" +
        " about to go out.\n");

    add_item(({"fume", "fumes", "bubble", "bubbles"}),
        "A " + color + " liquid bubbles gently inside the" +
        " flask. There's not much in there, and it dminishes" +
        " quickly as it turns into a little " + color + " cloud.\n");

    add_item(({"cloud", color + " cloud", "little " + color + " cloud"}),
        "The little " + color + " cloud is hovering dangerously" +
        " close to you, but it's dissipating quickly. Thank goodness" +
        " - if it stayed around much longer, you" +
        " might accidentally inhale it!\n");

    add_prop(OBJ_I_NO_SELL,
        "Eh, what? Your " + short() + " is leaking and fuming and" +
        " has a bit knocked off one end. Who'd want to buy" +
        " a thing like that?\n");

    add_prop(OBJ_I_WEIGHT, 30);
    add_prop(OBJ_I_VOLUME, 25);

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
    add_action(inhale_fumes,   "inhale");

}

// OBJECT DEFINITION

void
create_object()

{

    /*
     *  DESCRIPTION    
     */

    set_name("flask");
    add_name("liquid");

}
