/* 
 * Mortis 09.2014
 *
 * Standard Tower of Arms guards.
 *
 * If players can become Constable, these will change
 * to match their guild, but this is the default guard.
 *
 * The guards carry gold coin. They are well paid. These should only be
 * good xp for medium levels where players are broke spending on training.
 * I want to make them worthwhile for folks at this level who can get decent
 * xp from killing them as well as funds. They're not worthwhile xp for huge
 * players who are already rich or capable of making money hand over fist.
 * - Plus, there is nowhere to sell any of their gear yet, so the money is
 * there to cover that downfall as well.
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

    set_name("guard");
    add_name(({"guardsman"}));

    string mysh = my_short();
    set_short(mysh);
    set_long("A young guardsman of the city of Palanthas sworn to uphold "
    + "the laws and treat the citizenry with respect. The guard's open "
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

    set_alarm(1.0, 0.0, &arm_me());
    set_alarm(2.0, 0.0, &arm_me2());
}

void
arm_me()
{
    string whichbody, whichwep;
    object ghead, gwep;

    if (random(4) == 1)
    {
        whichbody = "shirt";
    }
    else
    {
        whichbody = one_of_list(({"coat", "vest"}));
    }

    // Guard's standard weapon.
    whichwep = one_of_list(({"gwep_sword", "gwep_spear", "gwep_club_cmdr"}));
    gwep = clone_object(OBJ + whichwep);
    gwep->move(TO);

    if (whichwep != "gwep_spear")
    {
        clone_object(OBJ + "garmour_shield")->move(TO);
    }

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

    // Guard's custom body armour.
    clone_object(OBJ + "garmour_" + whichbody)->move(TO);

    // Guard's standard issue overcoat.
    if (random(2) == 1)
    {
        clone_object(OBJ + "garmour_overcoat")->move(TO);
    }

    // Guard's standard issue greaves.
    if (random(2) == 1)
    {
        clone_object(OBJ + "garmour_greaves")->move(TO);
    }

    // Guard's standard issue payment.
    MONEY_MAKE_GC(12 + random(24))->move(TO);

}

void
arm_me2()
{
    command("wield all");
    command("wear all");
    command("unkeep all");
}
