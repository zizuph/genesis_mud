// OBJECT:  flask

    /* Calia Domain

    HISTORY

    [04-12-23] Created from [C:\CALIA\YULEWARE\FLASKS\FLASK.DOC] by Uhclem.

    PURPOSE

    A generic flask that is used as an ornament on the Gelan Yule tree.
    Players can take a flask and break the seal, at which point this flask
    object is replaced by an open flask containing a volatile liquid whose
    fumes may be inhaled.  */

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

// Function:  hook_smelled()

/*

Purpose:  add smell characteristics to this object.

Arguments:  none.

Returns:  nothing.

*/

void
hook_smelled()

{

    write("The " + short() + " smells vaguely of cheese fuzzies.\n");

}

// Function:  break_seal(item_text)

/*

Purpose:  break seal on flask, making the elixir within drinkable.

Arguments:  string specifying seal on this flask.

Returns:  0/1

*/

int
break_seal(string command_text)

{

    object tp = this_player();
    object flask;
    int n;

    if (!wildmatch("seal*", command_text))

    {

        notify_fail("Break what? The seal?\n");

        return 0;

    }

    /*
     *  Filenames of the opened flasks correspond to the colors of the sealed 
     *  flasks.    
     */

    flask = clone_object(FLASKS + "flask_open");
    flask->configure_flask(query_adj(1));
    flask->move(tp);

    write("You break the seal on the " + short() + ".\n");

    tell_room(environment(tp),
        QCTNAME(tp) + " breaks the seal on the " + short() + ".\n", ({tp}));

    tell_room(environment(tp), "The liquid inside the " + flask->short() +
        " begins to bubble and emit fumes.\n");

    remove_object();

    return 1;

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
            " is instantly destroyed.",
            "is instantaneously and inexplicably absorbed by one" +
            " of the other flasks!",
            "hides behind one of the other flasks, and then it doesn't" +
            " seem to be there at all!"
            })[random(5)] + "\n");

    }

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

    /*
     *  This test makes sure that we don't generate runtime errors when the 
     *  object is moved around by any wizard commands or system functions.    
     */

    if (!ob_to || !ob_from)

    {

        return;

    }

    else if (ob_to->query_prop(ROOM_I_IS))

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

}

// Function:  configure_flask(flask_type)

/*

Purpose:  create descriptive text appropriate to the color and texture.
    Called by gelan_tree when a player takes a flask.

Arguments:  string of text containing one adjective for
    texture/brightness/clarity/etc. and one for color.

Returns:  nothing.

*/

void
configure_flask(string flask_type)

{

    string *words = explode(flask_type, " ");
    string adj = words[0];
    string color = words[1];

    /*
     *  DESCRIPTION    
     */

    add_adj(({words[0], words[1]}));

    set_long("The " + short() + " is quite tiny, barely bigger" +
        " than a gnome's little toe, shaped more-or-less like" +
        " a sphere, and glows faintly with an eerie," +
        " flickering light. It's cool to the touch, and the" +
        " flask is sealed with a globule of clay, so you know that" +
        " it can't be fire that's causing the glow, and" +
        " the light isn't strong enough to illuminate anything" +
        " else, so if its purpose is anything but ornamental," +
        " it isn't obvious from the outside.\n");

    add_item(({"seal", "clay", "globule", "globule of clay"}),
        "It's a bit crumbly, suggesting both that the flask was" +
        " sealed a long time ago and that the seal would be" +
        " easy to break.\n");

    add_item(({"glow", "light", "flickering light"}),
        "The glow is pale " + color + " and flickers" +
        " erratically like a sputtering lamp or candle that's" +
        " about to go out.\n");

    add_prop(OBJ_I_NO_SELL,
        "The " + short() + " suddenly stops glowing and hides" +
        " whenever you try to offer it for sale, then" +
        " bafflingly reappears just as soon as you turn" +
        " your attention to other matters.\n");

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
    add_action(break_seal,   "break");

}

// OBJECT DEFINITION

void
create_object()

{

    set_name("flask");

    add_prop(OBJ_I_WEIGHT, 35);
    add_prop(OBJ_I_VOLUME, 30);

}
