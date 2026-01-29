/* 
 * Mortis 09.2014
 *
 * Tower of Arms guard found in the barracks where their state of preparedness
 * varies from guard to guard. Some may be caught in compromising positions.
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

/* Prototypes */
void arm_me();
void arm_me2();

/* String gdo is a good example of why I can't get anything done in a
 * reasonable amount of time. */
string gdo = one_of_list(({"touching themself", "shaving", "reading a risque' "
+ "novelette", "looking at pornographic playing cards", "dancing in underwear",
"writing vampire fantasy", "singing naked in the shower", "doodling stick "
+ "figures doing it", "shaving pubes", "polishing armour", "sharpening "
+ "weaponry", "binge eating", "boozing", "passed out on a she-male hooker",
"reading poetry", "writing a love letter", "angrily questioning whether "
+ "there is a Paladine or not", "working out while looking in the mirror",
"sleeping", "writing a bad application to the Morgul Mages about how "
+ "hobbits raped and pillaged their way through the guard's orphanage "
+ "until it burned to the ground leaving the survivors with a deep hatred "
+ "for the West", "praying to Psuchae", "jumping in the air, waving a wand "
+ "frantically, and shouting 'Arresto Momentum'", "eating from a dirty "
+ "toaster oven", "farting", "smelling its finger", "scrubbing furiously at "
+ "a pair of underpants with skidmarks in them", "tying a fellow guard up "
+ "with a grey necktie"}));

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
    + "the laws and treat the citizenry with respect. These are off hours, "
    + "and you caught the guard " + gdo + "!\n");
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
    if (random(3) == 1)
    {
        whichwep = one_of_list(({"gwep_sword", "gwep_spear", "gwep_club_cmdr"}));
        gwep = clone_object(OBJ + whichwep);
        gwep->move(TO);
    }

    if (whichwep != "gwep_spear" && random(4) == 1)
    {
        clone_object(OBJ + "garmour_shield")->move(TO);
    }

    // Guard's custom headware.
    if (random(4) == 1)
    {
        ghead = clone_object(MY_ARMOUR);
        ghead->set_armour_data("plain" + "&&"
                                + "grey" + "&&"
                                + "studded" + "&&"
                                + "cap");
        ghead->move(TO);
    }

    // Guard's standard issue boots.
    if (random(4) == 1)
    {
        clone_object(OBJ + "garmour_boots")->move(TO);
    }

    // Guard's standard issue gloves.
    if (random(4) == 1)
    {
        clone_object(OBJ + "garmour_gloves")->move(TO);
    }

    // Guard's standard issue belt.
    if (random(4) == 1)
    {
        clone_object(OBJ + "garmour_belt")->move(TO);
    }

    // Guard's custom body armour.
    if (random(4) == 1)
    {
        clone_object(OBJ + "garmour_" + whichbody)->move(TO);
    }

    // Guard's standard issue overcoat.
    if (random(5) == 1)
    { 
        clone_object(OBJ + "garmour_overcoat")->move(TO); 
    }

    // Guard's standard issue greaves.
    if (random(4) == 1)
    {
        clone_object(OBJ + "garmour_greaves")->move(TO);
    }

    // Guard's standard issue payment.
    if (random(1) == 0)
    {
        MONEY_MAKE_GC(12 + random(24))->move(TO);
    }

}

void
arm_me2()
{
    command("wield all");
    command("wear all");
    command("unkeep all");
}
