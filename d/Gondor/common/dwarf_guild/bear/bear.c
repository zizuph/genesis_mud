/*
 * /d/Gondor/common/dwarf_guild/bear/bear.c
 *
 * Copyright (C) Stas van der Schaaf - Februari 11 1994
 *               Mercade @ Genesis
 *
 * This is a bear. It is based on the idea of the bear that Glindor has
 * in his ugly studentisomething. The coding is not related to his bear
 * though.
 *
 * Modified to support dressing the bear in things by Arandir, 23Oct2005.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/container";

#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/dwarf_guild/dwarf.h"

#define TEDDYBEAR_ID (DWARVEN_RACE_GUILD_PREFIX + "bear")
#define ALARM_TIME   (itof(600 + random(600)))

/* Adjectives used for the bear. Repeat text to increase their chance. */
#define BEAR_ADJECTIVES ({ "cute furry", "furry", "cute and furry", \
    "soft and furry", "cute", "adorable", "big", "cuddly" })
/* Names used for the bear. Repeat names to increase their chance. */
#define BEAR_NAMES ({ "bear", "friend", "companion", "teddy", "teddybear" })
/* These names must have "your" as article. Otherwise could be "the". */
#define YOUR_NAMES ({ "friend", "companion" })

/*
 * Global variables.
 */
object oDress = 0;
int alarm_id = 0;
int autoloadable = 0;

/*
 * Prototypes.
 */
string bear_long();
int bear_hug(string str);
int bear_dress(string str);
int bear_undress(string str);


/*
 * Function name: create_container
 * Description  : Creator.
 */
void
create_container()
{
    set_name("bear");
    add_name("teddy");
    add_name("teddybear");
    add_name(TEDDYBEAR_ID);

    set_pname("bears");
    add_pname("teddies");
    add_pname("teddys");
    add_pname("teddybears");

    set_adj("teddy");
    add_adj("cute");
    add_adj("furry");
    add_adj("fluffy");
    add_adj("soft");
    add_adj("rather");
    add_adj("large");

    set_short("cute furry bear");
    set_pshort("cute furry bears");

    set_long(bear_long);

    add_prop(OBJ_I_VALUE,   2000);
    
    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_HIDDEN, 1);
    add_prop(CONT_I_VOLUME, 25000);
    add_prop(CONT_I_MAX_VOLUME, 25000+20000);
    add_prop(CONT_I_WEIGHT, 15000);
    add_prop(CONT_I_MAX_WEIGHT, 15000+10000);
    
    add_prop(OBJ_M_NO_SELL, "The " + short() + " is too valuable to sell.\n");
    add_prop(OBJ_M_NO_BUY,  "The " + short() + " is priceless, money cannot buy a bear.\n");
}


/*
 * Function name: bear_long
 */
string
bear_long()
{
    string sDesc = "It is a rather large, but cute teddybear. It is fluffy " +
                   "and furry. It has everything you ever looked for in a " +
                   "teddy and looks very huggable.";
    if (oDress)
    {
         sDesc += " It is dressed in " + LANG_ASHORT(oDress) + ".";
    }
    
    sDesc += "\n";
    
    return sDesc;
}


/*
 * Function name: bear_hug
 */
int
bear_hug(string str)
{
    if (!strlen(str) ||
        !parse_command(str, ({ }), "[the] [soft] [furry] [teddy] 'bear' / 'teddybear' / 'teddy'"))
    {
        notify_fail(CAP(query_verb()) + " what?\n");
	return 0;
    }

    switch(query_verb())
    {
    case "bearhug":
        write("You hug the " + short() + " fondly. Even though " +
              "you squeeze it tight, you make sure you do not hurt it. " +
	      "Hugging the bear is a great relief.\n");
        SAYBB(" hugs a " + short() + " fondly. Even though " +
	    PRONOUN(TP) + " squeezes it tight, " + PRONOUN(TP) + " makes " +
	    "sure the bear doesn't get hurt. Hugging the bear, " +
	    PRONOUN(TP) + " looks relieved and shines bright.");
	return 1;

    default:
        write("You hug the " + short() + ". The world looks a lot brighter now.\n");
        SAYBB(" hugs a " + short() + ". The world looks a lot brighter now.");
	return 1;
    }
}


/*
 * Function name: bear_dress
 */
int
bear_dress(string str = "")
{
    object oNewDress;
    object oBear;
    string *words;

    if ((sizeof(words = explode(str, " in ")) != 2) &&
        (sizeof(words = explode(str, " with ")) != 2))
    {
        notify_fail(CAP(query_verb()) + " whom in what?\n");
        return 0;
    }

    oBear = PARSE_COMMAND_ONE(words[0], environment(this_player()), "[the] %i");
    if (!objectp(oBear))
    {
        notify_fail(CAP(query_verb()) + " whom in what?" +
            (PARSE_COMMAND_SIZE ? " Please select just one bear." : "") + "\n");
	return 0;
    }

    oNewDress = PARSE_COMMAND_ONE(words[1], environment(this_player()), "[the] %i");
    if (!objectp(oNewDress))
    {
        notify_fail(CAP(query_verb()) + " " + LANG_THESHORT(oBear) + " in what?" +
            (PARSE_COMMAND_SIZE ? " Please select just one garment." : "") + "\n");
	return 0;
    }

    if (oBear != this_object())
    {
//      notify_fail(CAP(query_verb()) + " which bear in what?\n");
        return 0;
    }

    if (!oNewDress->bear_query_bearable())
    {
        notify_fail("You would not want to dress the " + short() + " in that!\n");
        return 0;
    }
    
    if (oDress)
    {
        notify_fail("The " + short() + " is already wearing " + LANG_ASHORT(oDress) + "!\n");
        return 0;
    }

    if (oNewDress->move(this_object (), 0))
    {
        notify_fail("You failed to dress the " + short() + "!\n");
        return 0;
    }

    oDress = oNewDress;
    
    write("You dress the cute furry teddybear in " + LANG_THESHORT(oDress) + 
           ". The " + short() + " wiggles its bottom.\n");
    SAYBB(" dresses " + TP->query_possessive() + " " + short() + " in " + LANG_ASHORT(oDress) + ".");

    return 1;
}


/*
 * Function name: bear_undress
 */
int
bear_undress(string str)
{
    if (!strlen(str) ||
        !parse_command(str, ({ }), "[the] [soft] [furry] [teddy] 'bear' / 'teddybear' / 'teddy'"))
    {
        notify_fail(CAP(query_verb()) + " what?\n");
	return 0;
    }

    if (!oDress)
    {
        notify_fail("The " + short() + " is not wearing anything!\n");
        return 0;
    }

    if (oDress->move(this_player (), 0))
    {
        notify_fail("You failed to undress the " + short() + "!\n");
        return 0;
    }

    oDress = 0;

    write("You undress the " + short() + ".\n");
    SAYBB(" undresses " + TP->query_possessive() + " " + short() + ".");

    return 1;
}


/*
 * Function name: init
 */
void
init()
{
    ::init();

    add_action(bear_hug,     "hug");
    add_action(bear_hug,     "bearhug");
    add_action(bear_dress,   "dress");
    add_action(bear_undress, "undress");
}


/*
 * Function name: bear_message
 * Description  : Gives a random message to whoever carries the bear.
 */
void
bear_message()
{
    string *messages = ({
	"%s embraces you tenderly#.",
	"%s gives you a true bearhug#, leaving you breathless!",
	"%s growls softly# as you squeeze him involuntarily.",
	"%s looks pleadingly at you with its big brown eyes.",
	"%s nuzzles his soft nose against you#.",
	"%s rubs your back with its paws#.",
	"%s snuggles up to you#.",
	"%s squeezes you fondly in the side#.",
	"%s wiggles its short tail against you#.",
	"%s wraps his furry paws fondly around your waist#.",
	"Covertly#, %s cuddles you with its soft paws.",
	"The eyes of %s emit a warm kind of friendship.",
	"Two cuddly teddybear paws give you a sweet hug#.",
	"With its gentle, furry paws, %s gives you a strong hug#.",
	"You hear a soft growl from %s#.",
	"You think to make out an encouraging smile on the face of %s.",
        });
    object robe = (object)environment()->query_armour(TS_ROBE);
    string robe_message = "";
    string adjective = one_of_list(BEAR_ADJECTIVES);
    string bear = one_of_list(BEAR_NAMES);
    string article = (IN_ARRAY(bear, YOUR_NAMES) ? "your" : "the");
    string message = sprintf(one_of_list(messages), (article + " " + adjective + " " + bear));

    /* 50% chance if you wear a robe. */
    if (objectp(robe) && random(2))
    {
	robe_message = (" under the cover of your " + robe->short());
    }

    tell_object(environment(),
	capitalize(implode(explode(message, "#"), robe_message)) + "\n");

    alarm_id = set_alarm(ALARM_TIME, 0.0, bear_message);
}


/*
 * Function name: enter_env
 * Description  : When entering a living player, give random messages from
 *                time to time.
 * Arguments    : object to   - the environment we are entering.
 *                object from - the environment we are leaving.
 */
void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!alarm_id &&
        interactive(to))
    {
        alarm_id = set_alarm(ALARM_TIME, 0.0, bear_message);
    }
}


/*
 * Function name: leave_env
 * Description  : When leaving a living player, reset the alarm.
 * Arguments    : object from - the environment we are leaving.
 *                object to   - the environment we are entering.
 */
void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    if (alarm_id)
    {
        remove_alarm(alarm_id);
        alarm_id = 0;
    }
}


/*
 * Function name: set_autoloadable
 * Description  : Set or unset the variable controlling autoloadability.
 * Arguments    : int value - 1/0 - set/unset.
 */
void
set_autoloadable(int value)
{
    autoloadable = value;
}


/*
 * Function name: query_autoloadable
 * Description  : Query the autoloadability of this bear for mortals.
 * Returns      : int 1/0 - autoloadable or not.
 */
int
query_autoloadable()
{
    return autoloadable;
}


/*
 * Function name: query_recover
 * Description  : This object will recover for mortal players.
 * Returns      : string - the MASTER for mortals, else 0.
 */
string
query_recover()
{
    return ((autoloadable || ENV()->query_wiz_level()) ? 0 : MASTER);
}


/*
 * Function name: query_auto_load
 * Description  : This object will auto load for wizards. We need to return
 *                the autoloadable marker so that init_arg() is called to
 *                preserve the autoloadability for mortals.
 * Returns      : string - the MASTER for wizards, else 0.
 */
string
query_auto_load()
{
    if (autoloadable)
    {
        return MASTER + ":autoloadable";
    }

    return ((ENV()->query_wiz_level()) ? MASTER : 0);
}


/*
 * Function name: init_arg
 * Description  : When this bear is autoloadable for a mortal player,
 *                retain the autoloadability.
 * Arguments    : string arg - if "autoloadable" retain autoloadability.
 */
void
init_arg(string arg)
{
    autoloadable = (arg == "autoloadable");
}
