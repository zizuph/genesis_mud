/* 
* Standard guard for Gont Port
*
* Coded by Porta, Dec 97
* updated by Amelia to use basic_guard.c  2/98
*/

#pragma strict_types

inherit "/d/Earthsea/gont/gont_city/liv/basic_guard";

#define ASSIST_ME_HP 500

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include "basic_guard.h"
#include "assist.h"

public void
create_guard()
{
    set_gender(0);
    set_levels(5);
    set_long("This guard is a very experienced veteran. " +
        "They've been in numerous battles and of course " +
        "came back alive each time. " +
        "A seal on his platemail indicates that he is " +
        "an elite guard.\n");
    add_name("_guard5_");
    add_prop(LIVE_I_QUICKNESS, 150);
    (MONEY_MAKE_GC(random(5)))->move(this_object());
    add_equipment(({ WEP + "g_elite_lngsword", ARM + "g_elite_platemail",
        ARM + "g_elite_shin_guards", ARM + "g_elite_helmet",
        ARM + "g_elite_shield" }));
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_PARRY, 75);
    set_skill(SS_WEP_SWORD, 95);
    set_skill(SS_BLIND_COMBAT, 70);
}
