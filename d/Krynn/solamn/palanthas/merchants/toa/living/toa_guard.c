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
 * Just like utoa skeletons, these are intended for mid-levels to benefit
 * from. Big players do big hits, so those hits have a higher chance to
 * destroy weapons and armour the bigger they are. Same for gold. That
 * should reduce the imbue-hunting from myths on these guys.
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

int mygold = 12 + random(13);
object gwep, ggloves, gboots, gbelt, gbody, gcoat, ggreaves, ghead, garm, gshield;

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

    set_stats((({110, 110, 100, 60, 80, 140})), 7);
    set_all_attack_unarmed(15, 10);
    set_all_hitloc_unarmed(10);

    set_alarm(1.0, 0.0, &arm_me());
    set_alarm(2.0, 0.0, &arm_me2());
}

void
arm_me()
{
    string whichbody, whichwep;

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
        gshield = clone_object(OBJ + "garmour_shield")->move(TO);
    }

    // Guard's custom headware.
    ghead = clone_object(MY_ARMOUR);
    ghead->set_armour_data("plain" + "&&"
                            + "grey" + "&&"
                            + "studded" + "&&"
                            + "cap");
    ghead->move(TO);

    // Guard's custom pauldrons.
    garm = clone_object(MY_ARMOUR);
    garm->set_armour_data("plain" + "&&"
                            + "grey" + "&&"
                            + "studded" + "&&"
                            + "pauldrons");
    garm->move(TO);

    // Guard's standard issue boots.
    gboots = clone_object(OBJ + "garmour_boots");
    gboots->move(TO);

    // Guard's standard issue gloves.
    ggloves = clone_object(OBJ + "garmour_gloves");
    ggloves->move(TO);

    // Guard's standard issue belt.
    gbelt = clone_object(OBJ + "garmour_belt");
    gbelt->move(TO);

    // Guard's custom body armour.
    gbody = clone_object(OBJ + "garmour_" + whichbody);
    gbody->move(TO);

    // Guard's standard issue overcoat.
    if (random(2) == 1)
    {
        gcoat = clone_object(OBJ + "garmour_overcoat");
        gcoat->move(TO);
    }

    // Guard's standard issue greaves.
    if (random(2) == 1)
    {
        ggreaves = clone_object(OBJ + "garmour_greaves");
        ggreaves->move(TO);
    }

    // Guard's standard issue payment.
    MONEY_MAKE_GC(mygold)->move(TO);

}

void
arm_me2()
{
    command("wield all");
    command("wear all");
    command("unkeep all");
}

/* Function:         do_die()
 * What's it do:     Ordinarily initiates death in slain monster.
 * What's it do now: Destroys some to all gold and armaments with a higher
 *                   chance the bigger the player. */

void
do_die(object killer)
{
    int goldfactor = 100;
    int kstat = killer->query_average_stat();
    string golddamage = "";

    if (kstat > 115)
    {
        goldfactor = 65;
        golddamage = "Your killing blow destroys your foe sending bits "
            + "of shattered gold and steel flying.";
    }
    if (kstat > 125)
    {
        goldfactor = 45;
        golddamage = "Your killing blow massacres your foe spraying the "
            + "area with bits of gold, steel, and blood.";
    }
    if (kstat > 135)
    {
        goldfactor = 20;
        golddamage = "Your mighty killing blow overpowers the guard's "
            + "body destroying it along with most of its belongings in a "
            + "haze of gold, steel, and blood.";
    }
    if (kstat > 145)
    {
        goldfactor = 0;
        golddamage = "Your massive killing blow turns the guard into red "
            + "mist along with nearly all of its belongings.";
    }

    // Reduce gold coins by goldfactor.
    if (mygold != 0)
    {
        mygold = mygold * goldfactor / 100;

        object gcoins = present("coin", TO);
        gcoins->set_heap_size(mygold);
    }

    // Reduce armaments dropped by goldfactor as a % of destruction as low as 10%.
    if (present(gwep, TO))
    {
        if (random(109) >= (goldfactor + 10))
        {
            gwep->remove_object();
        }
    }
    if (present(gboots, TO))
    {
        if (random(109) >= (goldfactor + 10))
        {
            gboots->remove_object();
        }
    }
    if (present(ggloves, TO))
    {
        if (random(109) >= (goldfactor + 10))
        {
            ggloves->remove_object();
        }
    }
    if (present(gbelt, TO))
    {
        if (random(109) >= (goldfactor + 10))
        {
            ggloves->remove_object();
        }
    }
    if (present(gbody, TO))
    {
        if (random(109) >= (goldfactor + 10))
        {
            gbody->remove_object();
        }
    }
    if (present(gcoat, TO))
    {
        if (random(109) >= (goldfactor + 10))
        {
            gcoat->remove_object();
        }
    }
    if (present(ggreaves, TO))
    {
        if (random(109) >= (goldfactor + 10))
        {
            ggreaves->remove_object();
        }
    }
    if (present(ghead, TO))
    {
        if (random(109) >= (goldfactor + 10))
        {
            ghead->remove_object();
        }
    }
    if (present(gshield, TO))
    {
        if (random(109) >= (goldfactor + 10))
        {
            gshield->remove_object();
        }
    }

    if (golddamage != "" && present(killer, E(TO)))
    {
        killer->catch_msg(golddamage + "\n");
    }    

    ::do_die(killer);
}