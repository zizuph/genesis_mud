/* 
 * Mortis 10.2014
 *
 * Standard skeleton in the crypt underneath the Tower of Arms.
 * They take 1/4 damage from pierce, 1/2 damage from slash,
 * and full damage from bludgeon. Player gets messages about those while
 * fighting.
 *
 * Added lightning and death magic protection in base file. Made gold and
 * jewelry partially destroyed if you're too big and powerful, because your
 * killing blow just annhilates them. This is to prevent myths from taking
 * advantage of the area designed for mid levels.
 */

#pragma strict_types

#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <language.h>
#include "../../../local.h"

inherit UTOA_SKELETON;

/*prototype*/
void arm_me();

int mygold = 2 + random(5);
object jewel1, jewel2, jewel3;

void
create_utoa_skeleton()
{
    seteuid(getuid(TO));

    set_name("skeleton");

    string mysh = my_short();
    set_short(mysh);
    set_long("Darkness blazes from the hollows in the eye sockets of this "
    + "dusty skeleton's skull. Its jaw gapes hungrily, and it moves with "
    + "a jagged, uneven gait.\n");
    string myrace = my_race();
    set_race_name(myrace);
    
    set_skill(SS_DEFENCE,      60);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_AWARENESS,    20);
    set_skill(SS_BLIND_COMBAT, 20);

    set_stats((({135, 135, 135, 65, 65, 65})), 7);
    set_all_attack_unarmed(28, 18);
    set_all_hitloc_unarmed(15);

    set_alarm(1.0, 0.0, &arm_me());
}

void
arm_me()
{
    // Skeleton's standard burial funds.
    if (random(5) != 1)
    {
        MONEY_MAKE_GC(mygold)->move(TO);
    }
    // Set gold factorable gold coin count to 0.
    else
    {
        mygold = 0;
    }

    // Skeleton's standard burial rites.
    jewel1 = clone_object(UTOA + "arms/burial_ornament");
    jewel1->make_the_jewel();
    jewel1->move(TO);

    if (random(2) == 1)
    {
        jewel2 = clone_object(UTOA + "arms/burial_ornament");
        jewel2->make_the_jewel();
        jewel2->move(TO);
    }

    if (random(5) == 1)
    {
        jewel3 = clone_object(UTOA + "arms/burial_ornament");
        jewel3->make_the_jewel();
        jewel3->move(TO);
    }
}

/* Say something cool on death. Destroy some of the loot if someone too big
 * gets the killing blow. */
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
            + "of shattered gold and jewelry flying.";
    }
    if (kstat > 125)
    {
        goldfactor = 45;
        golddamage = "Your killing blow massacres your foe spraying the "
            + "area with bits of gold and jewelry.";
    }
    if (kstat > 135)
    {
        goldfactor = 20;
        golddamage = "Your mighty killing blow overpowers the skeleton's "
            + "form destroying it along with most of its belongings in a "
            + "haze of gold and silver.";
    }
    if (kstat > 145)
    {
        goldfactor = 0;
        golddamage = "Your massive killing blow vaporizes the skeleton "
            + "and nearly all its belongings.";
    }

    // Reduce gold coins by goldfactor.
    if (mygold != 0)
    {
        mygold = mygold * goldfactor / 100;

        object gcoins = present("coin", TO);
        gcoins->set_heap_size(mygold);
    }

    // Reduce jewelry held by goldfactor as a % of destruction as low as 10%.
    if (present(jewel1, TO))
    {
        if (random(109) >= (goldfactor + 10))
        {
            jewel1->remove_object();
        }
    }
    if (present(jewel2, TO))
    {
        if (random(109) >= (goldfactor + 10))
        {
            jewel2->remove_object();
        }
    }
    if (present(jewel3, TO))
    {
        if (random(109) >= (goldfactor + 10))
        {
            jewel3->remove_object();
        }
    }

    if (golddamage != "" && present(killer, E(TO)))
    {
        killer->catch_msg(golddamage + "\n");
    }    

    if (random(1) == 1)
    {
        command("emote shatters into bone and dust.");
    }
    else if (goldfactor == 0) // Skip this if we vaporized them.
    {
        command("emote collapses into a heap of bone and dust.");
    }

    ::do_die(killer);
}