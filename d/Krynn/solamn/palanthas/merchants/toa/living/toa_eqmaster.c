/* 
 * Mortis 09.2014
 *
 * Quartermaster of the Tower of Arms, the Constabulary of Palanthas.
 *
 * If players can become Constable, these will change
 * to match their guild, but this is the default guard.
 *
 */

#pragma strict_types

#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <language.h>
#include "../../../local.h"

#define MY_CLOTHING       NOBLE + "arms/parmour"
#define MY_ARMOUR         MERCH + "arms/larmour"
#define MY_GENERAL        MERCH + "obj/lgeneral"

inherit TOA_GUARD;

/*prototype*/
void arm_me();
void arm_me2();

void
create_toa_guard()
{
    seteuid(getuid(TO));

    set_name("bugsly");
    add_name(({"guard", "guardsman"}));
    add_adj(({"old", "balding"}));
    set_title("the Quartermaster of the Constabulary of Palanthas");
    set_introduce(1);

    set_short("old balding guardsman");
    set_pshort("old balding guardsmen");
    set_long("An old, balding guardsman of the city of Palanthas sworn to "
    + "uphold the laws and treat the citizenry with respect. The guard's open "    
    + "white tunic bears " + "@@constable_symbol@@" + " above its left "
    + "breast.\n");
    set_race_name("human");
    
    set_skill(SS_DEFENCE,      65);
    set_skill(SS_PARRY,        40);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_AWARENESS,    30);
    set_skill(SS_WEP_SWORD,    70);
    set_skill(SS_WEP_CLUB,     65);
    set_skill(SS_WEP_POLEARM,  60);
    set_skill(SS_BLIND_COMBAT, 25);

    set_stats((({130, 130, 100, 120, 140, 180})), 7);
    set_all_attack_unarmed(15, 10);
    set_all_hitloc_unarmed(10);

    set_default_answer("say I'm afraid I have too much administrative work "
    + "to deal with that.");

    add_ask(({"work", "administrative work"}), "asay helpl It's like I'm "
    + "the only one doing real work around here. Everyone else is in the "
    + "action. Oh well, I'm getting too old for that anyway.", 1);

    set_alarm(1.0, 0.0, &arm_me());
    set_alarm(2.0, 0.0, &arm_me2());
}

void
arm_me()
{
    object ghead, tkey;

    // Guard's custom headware.
    ghead = clone_object(MY_ARMOUR);
    ghead->set_armour_data("plain" + "&&"
                            + "grey" + "&&"
                            + "studded" + "&&"
                            + "cap");
    ghead->move(TO);

    // Guard's standard issue boots.
    clone_object(OBJ + "garmour_boots")->move(TO);

    // Guard's standard issue gloves.
    clone_object(OBJ + "garmour_gloves")->move(TO);

    // Guard's standard issue belt.
    clone_object(OBJ + "garmour_belt")->move(TO);

    // Guard's standard issue payment.
    MONEY_MAKE_GC(24 + random(27))->move(TO);

    // Routine to make sure door is closed and locked on reset.
    tkey = clone_object(TOA + "doors/toa_stores_key");
    tkey->move(TO);
    
    command("close door");
    command("lock door with key");
}

void
arm_me2()
{
    command("wield all");
    command("wear all");
    command("unkeep all");
}
