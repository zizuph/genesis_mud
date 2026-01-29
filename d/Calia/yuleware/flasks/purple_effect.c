// OBJECT:  purple fume effect

    /* Calia Domain

    HISTORY

    [2004-12-28] Created by Uhclem from [C:\CALIA\YULEWARE\FLASKS\PURPLE.DOC].

    PURPOSE

    This object masks some emotes - mostly ones that don't take or need an
    adverb - and gives them a Yule flavor.  Among the objects in the "flasks"
    directory, darker colors express a more cynical or curmudgeonly attitude
    while lighter colors fully embrace the Yule spirit.  */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";
inherit "/lib/commands";

#include <adverbs.h>
#include <cmdparse.h>
#include <composite.h>
#include <const.h>
#include <files.h>
#include <filter_funs.h>
#include <language.h>
#include <living_desc.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <options.h>
#include "defs.h"

#define SUBLOC_SOULEXTRADESC ("_soul_cmd_extra")
#define SOULDESC(x)          (this_player()->add_prop(LIVE_S_SOULEXTRA, (x)))
#define DEPTH                (1)  /* How many rooms away scream is heard. */
#define DUMP_EMOTIONS_OUT    ("/open/dump_emotions")

// FUNCTIONS

// Function:  is_calian_fume_effect()

/*

Purpose:  identifies this object as a genuine Calian fume effect - your
guarantee of potency!

Arguments:  none.

Returns:  1.

*/

int
is_calian_fume_effect()

{

    return 1;

}

// BOUNCE: masks standard emote

int
bounce(string str)

{

    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, BLANK_ADVERB, 0);

    if (!stringp(str))

    {

        write("You bounce around with grim determination in an" +
            " effort to shake free all traces of holly, mistletoe," +
            " or other Yule tidbits that may be clinging to you.\n");

        all(" bounces around with grim determination in an" +
            " effort to shake free all traces of holly, mistletoe," +
            " or other Yule tidbits that may be clinging to " +
            this_player()->query_objective() + ".", how[1],
            ACTION_HACTIVITY | ACTION_VISUAL);
            return 1;

    }

    return 0;

}

// BRIGHTEN: masks standard emote

int
brighten(string str)

{

    if (stringp(str))

    {

        return 0;

    }

    write("You think about it, then it dawns on you - Yule" +
        " season comes but once a year, and you only have to deal with" +
        " it a few more days! Your face brightens!\n");

    all(" thinks about it, then it dawns on " +
        this_player()->query_objective() + " - Yule season comes" +
        " but once a year, and " + this_player()->query_pronoun() +
        " only has to deal with it a few more" +
        " days! " + capitalize(this_player()->query_possessive()) +
        " face brightens.", "",
        ACTION_OTHER);

    return 1;

}

// DANCE: masks standard emote

int
dance(string str)

{

    object *oblist;

    if (!stringp(str))

    {

        write("You dance a strange and twisted jig in honor of the" +
            " New Year, or perhaps Arbor Day, or maybe" +
            " even Mecklenberg Day... anything but Yule!\n");

        all(" dances a strange and twisted jig in honor of the" +
            " New Year, or perhaps Arbor Day, or maybe" +
            " even Mecklenberg Day... anything but Yule!");
            return 1;

    }

    return 0;

}

// FART: masks standard emote and cancels the effect of this object

int
fart(string str)

{

    if (stringp(str))

    {

        notify_fail("Fart how?\n");
        return 0;

    }

    write("How rude, farting!\n" +
        "A little purple cloud briefly forms behind you" +
        " and then quickly dissipates.\n");

    all(" lets off a real rip-roarer!\n" +
        "A little purple cloud briefly forms behind " +
        this_player()->query_objective() +
        " and then quickly dissipates.");

    remove_object();
    return 1;

}

// LAUGH: masks standard emote

int
laugh(string str)

{

    object *oblist;
    string *how;

    if (!stringp(str))

    {

        write("You laugh with a full and hearty voice - Ho! Ho! Ho!" +
            " - but you make it clear that you're laughing at" +
            " Yule, not with it.\n");

        all(" laughs with a full and hearty voice - Ho! Ho! Ho! -" +
            " but makes it clear that " + this_player()->query_pronoun() +
            "'s laughing at Yule, not with it.");

        SOULDESC("laughing");
        return 1;

    }

    return 0;

}

// MUMBLE: masks standard emote

int
mumble(string str)

{

    object *oblist;

    if (!stringp(str))

    {

        SOULDESC("mumbling about something");

        write("You mumble something about peace and good will" +
            " toward men being some sort of rubbish.\n");

        all(" mumbles something about peace and good will toward" +
            " men being some sort of rubbish.");
            return 1;

    }

    return 0;

}

// PANIC: masks standard emote

int
panic(string str)

{

    if (stringp(str))

    {

        notify_fail("Panic what?\n");
        return 0;

    }

    write("PANIC!!!!! You panic and look for a place to" +
        " hide until Yule season is over.\n");

    allbb(" panics and looks for a place to hide until Yule season is over.");

    return 1;

}

// PONDER: masks standard emote

int
ponder(string str)

{

    object *oblist;

    if (!stringp(str))

    {

        SOULDESC("pondering the true meaning of Yule");

        write("You ponder the true meaning of Yule - ah, yes," +
            " the reaping of huge profits from the sale" +
            " of holly, mistletoe, and other utterly useless" +
            " trappings of the season.\n");

        all(" ponders the true meaning of Yule - ah, yes, the" +
            " reaping of huge profits from the sale of" +
            " holly, mistletoe, and other utterly useless" +
            " trappings of the season.");

        return 1;

    }

    return 0;

}

// SMIRK: masks standard emote

int
smirk(string str)

{

    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, BLANK_ADVERB, 0);

    if (!stringp(how[0]))

    {

        SOULDESC("smirking" + how[1]);
            write("You smirk with a momentary gleam of purple in your" +
            " eye that makes it obvious to others that" +
            " you've been inhaling something interesting.\n");

        all(" smirks with a momentary gleam of purple in " +
            this_player()->query_possessive() + " eye that suggests" +
            this_player()->query_pronoun() +
            "'s been inhaling something interesting.", how[1]);
            return 1;

    }

    return 0;

}

// TINGLE: masks standard emote

int
tingle(string str)

{

    if (stringp(str))

    {

        notify_fail("Tingle how?\n");
        return 0;

    }

    write("You tingle with excitement because Yule season is" +
        " almost over, which means that folks can get back" +
        " to killing and plundering, which is what we're" +
        " all here for anyway.\n");

    allbb(" tingles with excitement because Yule season is" +
        " almost over, which means that folks can get back" +
        " to killing and plundering, which is what we're" +
        " all here for anyway.");

    return 1;

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

    object *other_effects;
    object holiday_room;

    ::enter_env(ob_to, ob_from);

    /*
     *  This object will be moved to a player's inventory when he breaks the 
     *  seal on a purple flask from the Gelan yule tree and inhales the fumes
     *  that ensue.    
     */

    if (!ob_to || !interactive(ob_to))

    {

        return;

    }

    /*
     *  If the player already has a fume effect object, get rid of it.    
     */

    other_effects = filter(all_inventory(ob_to), &->is_calian_fume_effect())
        - ({this_object()});

    if (sizeof(other_effects))

    {

        other_effects[0]->remove_object();

    }

    holiday_room = find_object(HOLIDAY_ROOM);

    if (!holiday_room)

    {

        holiday_room = call_other(HOLIDAY_ROOM, "this_object");

    }

    tell_room(holiday_room,
        ob_to->query_name() + " inhales some purple fumes.\n");

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
    add_action(bounce,   "bounce");
    add_action(brighten, "brighten");
    add_action(dance,    "dance");
    add_action(fart,     "fart");
    add_action(laugh,    "laugh");
    add_action(mumble,   "mumble");
    add_action(panic,    "panic");
    add_action(ponder,   "ponder");
    add_action(smirk,    "smirk");
    add_action(tingle,   "tingle");

}

// Function:  create_object()

void
create_object()

{

    set_no_show();
    set_name("_calia_purple_fumes_effect");
    set_short("purple_effect");
    add_name("_calia_yule_fumes_effect");

    set_long("This invisible object is given to players" +
        " who inhale the fumes from decorations on the yule tree in Gelan.\n");

    /*
     *  PROPERTIES    
     */

    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_DROP, 1);

}
