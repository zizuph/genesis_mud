/*
 * /d/Gondor/common/npc/farm/dunlending.c
 *
 * Revision history:
 *
 *   - Removal of inappropriate language for a Tolkien theme
 *       Gorboth, May 1997
 *
 *	 - Commented out set_whimpy()
 *        Raymundo, April 2020
 */
#pragma strict_types

inherit "/std/monster";
inherit "/d/Gondor/common/lib/logkill.c";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_monster()
{
    set_name("dunlending");
    add_name(({"man"}));
    set_pname("dunlendings");
    add_pname("men");
    set_pshort("men");
    set_race_name("human"); 
    set_adj("dark-haired");
    set_long("A dunlending, dark-haired and green-eyed.\n");
    default_config_npc(60+random(10));
    set_base_stat(SS_INT, 75+random(5));
    set_aggressive(1);     
    set_restrain_path(({FARM_DIR + "farm"}));
    set_alignment(-150-random(10)*20);
    set_skill(SS_WEP_SWORD, random(15)+60);
    set_skill(SS_PARRY,     random(15)+30);
    set_skill(SS_BLIND_COMBAT, 50);
    set_skill(SS_DEFENCE,   random(20)+60);
    set_skill(SS_AWARENESS, random(21)+10);
    add_prop(CONT_I_HEIGHT,   180);
    add_prop(CONT_I_WEIGHT, 75000);
    add_prop(CONT_I_VOLUME, 60000);    
    add_prop(LIVE_I_NEVERKNOWN, 1);

   // set_whimpy(30);

    set_chat_time(30 + random(15));
    add_chat("That wasn't much we got, but at least we killed some Rohirrim.");
    add_chat("Let's hurry!");
    set_cchat_time(5 + random(9));
    add_cchat("Let's kill everyone and then go home!");
    add_cchat("Finish him!");
    add_cchat("No prisoners, no witnesses!");
    add_cchat("Damn! If the Rohirrim or the Rangers learn about us, we're dead!");
    set_act_time(10+random(15));
    add_act("burp");
    add_act("get all");
    add_act("hiss");
}

void
arm_me()
{
    object wep, arm;

    FIX_EUID

    if (!random(3))
        wep=clone_object(WEP_DIR + "dulsword");
    else 
    {
        wep = clone_object(WEP_DIR + "dubsword");
	arm = clone_object(ARM_DIR + "dushield");
	arm->move(TO);
    }
    wep->move(TO);
    command("wield all");

    arm = clone_object(ARM_DIR + "dustlarm");
    arm->move(TO);

    if (random(10) > 5)
    {
	arm = clone_object(ARM_DIR + "lphelmet");
	arm ->move(TO);
    }
    command("wear all");

    MONEY_MAKE_CC(random(350)+150)->move(TO, 1);
    MONEY_MAKE_SC(random( 15)+  5)->move(TO, 1);
}

int    query_knight_prestige() { return 750; }

