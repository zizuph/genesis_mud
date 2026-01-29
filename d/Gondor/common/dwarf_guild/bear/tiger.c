/*
 * /d/Gondor/common/dwarf_guild/bear/tiger.c
 *
 * Copyright (C) Stas van der Schaaf - March 20 2009
 *
 * This is a tiger. It is based on the idea of the bear that Glindor has
 * in his ugly studentisomething. The coding is not related to his bear
 * though.
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

#define TEDDYTIGER_ID (DWARVEN_RACE_GUILD_PREFIX + "tiger")

/*
 * Global variables.
 */
int autoloadable = 0;

/*
 * Prototypes.
 */


/*
 * Function name: create_container
 * Description  : Creator.
 */
void
create_container()
{
    set_name("tiger");
    add_name(TEDDYTIGER_ID);

    set_pname("tigers");
    add_pname("teddies");
    add_pname("teddys");

    set_adj("teddy");
    add_adj("jr");
    add_adj("cute");
    add_adj("furry");

    set_short("cute furry jr tiger");
    set_pshort("cute furry jr tigers");

    set_long("It is a medium-sized cute teddy tiger. It is fluffy and " +
        "furry, and even growls in a cute manner. It has everything you " +
        "ever looked for in a tiger and looks very huggable.\n");

    add_prop(OBJ_I_VALUE,   2000);
    
    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_HIDDEN, 1);
    add_prop(CONT_I_VOLUME, 25000);
    add_prop(CONT_I_MAX_VOLUME, 25000+20000);
    add_prop(CONT_I_WEIGHT, 15000);
    add_prop(CONT_I_MAX_WEIGHT, 15000+10000);
    
    add_prop(OBJ_M_NO_SELL, "The " + short() + " is too valuable to sell.\n");
    add_prop(OBJ_M_NO_BUY,  "The " + short() + " is priceless, money cannot buy a tiger.\n");
}


/*
 * Function name: bear_hug
 */
int
bear_hug(string str)
{
    if (!strlen(str) ||
        !parse_command(str, ({ }), "[the] [cute] [furry] [jr] [teddy] 'tiger'"))
    {
        notify_fail(CAP(query_verb()) + " what?\n");
	return 0;
    }

    switch(query_verb())
    {
    case "bearhug":
    case "tigerhug":
        write("You hug the " + short() + " fondly. Even though " +
              "you squeeze it tight, you make sure you do not hurt it. " +
	      "Hugging the tiger is a great relief. Did it just growl " +
	      "softly at you?\n");
        SAYBB(" hugs a " + short() + " fondly. Even though " +
	    PRONOUN(TP) + " squeezes it tight, " + PRONOUN(TP) + " makes " +
	    "sure the tiger doesn't get hurt. Hugging the tiger, " +
	    PRONOUN(TP) + " looks relieved and shines bright.");
	return 1;

    default:
        write("You hug the " + short() + ". The world looks a lot brighter now.\n");
        SAYBB(" hugs a " + short() + ". The world looks a lot brighter now.");
	return 1;
    }
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
    add_action(bear_hug,     "tigerhug");
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
