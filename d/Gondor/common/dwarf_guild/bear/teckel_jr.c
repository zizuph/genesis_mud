/*
 * /d/Gondor/common/dwarf_guild/bear/tTeckel.c
 *
 * A new addition to the family, this is a teckel.
 *
 * Created by Mercade, 22 July 2009.
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

#define TECKEL_ID (DWARVEN_RACE_GUILD_PREFIX + "teckel")

/*
 * Global variables.
 */
int autoloadable = 0;
int greeting_alarm = 0;

/*
 * Function name: create_container
 * Description  : Creator.
 */
void
create_container()
{
    set_name("teckel");
    add_name("keffer");
    add_name("doggie");
    add_name("shiraz");

    set_pname("teckels");
    add_pname("keffers");

    set_adj("cute");
    add_adj("junior");
    add_adj("furry");
    add_adj("jr");

    set_short("cute furry jr teckel");
    set_pshort("cute furry jr teckels");

    set_long("It is a long and narrow jr teckel. Its fur is smooth and " +
        "coloured chocolate brown with patches of light brown and it " +
        "even kefs cutely. The jr teckel is wearing a fashionable brown " +
        "leather collar with a cool snap buckle. It has everything you " +
        "ever looked for in a teckel and looks very huggable.\n");

    add_prop(OBJ_I_VALUE,   2000);
    
    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_HIDDEN, 1);
    add_prop(CONT_I_VOLUME, 4000);
    add_prop(CONT_I_MAX_VOLUME, 4000+2000);
    add_prop(CONT_I_WEIGHT, 2500);
    add_prop(CONT_I_MAX_WEIGHT, 2500+2000);
    
    add_prop(OBJ_M_NO_SELL, "The " + short() + " is too valuable to sell.\n");
    add_prop(OBJ_M_NO_BUY,  "The " + short() + " is priceless.\n");
}

void
init_greeting()
{
    tell_room(ENV(), "The " + short() + " kefs " +
        one_of_list( ({ "adorably", "affectionately", "casually",
            "cheerfully", "coyly", "cutely", "energetically",
            "enthusiastically", "firmly", "girlishly", "happily", "heartily",
            "hungrily", "innocently", "joyously", "majestically", "merrily",
            "moodily", "musically", "playfully", "politely", "proudly",
            "provocatively", "quietly", "royally", "smartly", "softly",
            "sternly", "sweetly", "tenderly", "vigorously", "wildly",
            "wickedly" }) ) + ".\n");
    greeting_alarm = 0;
}

/* 
 * Function name: init
 * Description  : Whenever an interactive approaches, greet him.
 */
void
init()
{
    ::init();

    if (!interactive(this_player())) return;

    if (!greeting_alarm)
    {
        greeting_alarm = set_alarm(2.0, 0.0, init_greeting);
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
