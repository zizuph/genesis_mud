/*
 * /d/Gondor/guilds/rangers/potions/este.c
 *
 * Ranger potion for healing.
 *
 * Originally coded by Elessar in August 1994
 *
 * Modification log:
 *  3-Dec-1996, Olorin: Changed inheritance to ranger_potion
 *   Added in overdosing to prevent overuse. Initial 5 potions, then 1
 *   every 30 seconds for non rangers. Initial 5 potions, then 2 every
 *   30 seconds for rangers. Potion strength halved for people under 0
 *   alignment. - Gwyneth, January 9, 2001
 *  7-Feb-2001, Alto: Moved to new ranger path.
 *   Reduced strength of potion by an additional third if used by
 *   by a non-ranger. For evil non-rangers this results in 1/6 strength.
 *   This should reduce the stockpiling of healing potions by non-ranger
 *   guilds.
 * 23-Feb-2013, Mercade: updated for heapable potions.
 */

#include "../rangers.h"

inherit RANGERS_POTION + "ranger_potion.c";

#include <herb.h>
#include "/d/Gondor/defs.h"

#define DOSE            (50)
#define MAX_STR         (250)
#define OD_OBJ          ("/d/Gondor/common/lib/overdose.c")
#define RATE            (50)
#define RRATE           (100)
#define RECOVER_TIME    (30)

public void
create_ranger_potion()
{
    set_potion_name("este");
    set_unid_long("This is a strange herb brew.\n");
    set_id_long("This is an Este potion, a refreshing and healing " +
        "potion the Rangers can make. If mixed by the most skilled hands, " +
        "it can even cure poisoning. However, too much of a good thing " +
        "can be bad.\n");
    set_adj("clear");
    set_id_diff(17);
    set_soft_amount(30);
    set_alco_amount(0);
    set_potion_value(1100);
    set_id_smell("The potion smells refreshing, a pungent smell that " +
        "seems to clear even the air around it. You recognize the smell " +
        "of athelas, and know this potion heals well.\n");
    set_id_taste("A clear fresh taste spreads in your mouth. You recognize " +
        "the refreshing taste of kingsfoil.\n");
    set_unid_smell("The potion smells pungently refreshing.\n");
    set_unid_taste("The potion tastes pungently refreshing.\n");

    set_effect(HERB_SPECIAL, "este", "@@query_strength@@");
}

int
query_strength()
{
    int alco = query_alco_strength();

    if (alco > 10)
        return 0;

    return min(100, (50 + (10 - alco) * 5));
}

public int
check_overdose()
{
    int level;
    object ob;

    if (ob = present("este_overdose", this_player()))
    {
        if (ob->calculate_overdose() < 1)
            ob->reset_overdose();

        /* Adds to the overdose tally */
        ob->set_overdose_dose(DOSE);
        level = ob->calculate_overdose();
    }
    else
    {
        ob = clone_object(OD_OBJ);

        /* Rangers have an advantage */
        if (RANGERS_MEMBER(this_player()))
            ob->set_overdose(DOSE, MAX_STR, RRATE, RECOVER_TIME, "este_overdose");
        else
            ob->set_overdose(DOSE, MAX_STR, RATE, RECOVER_TIME, "este_overdose");

        ob->move(this_player(), 1);
        level = DOSE;
    }

    if (level >= MAX_STR)
        return 1;
    else
        return 0;
}

void
special_effect()
{
    object  poison;
    int strength = query_strength();

    if (!strength)
    {
        write("The potion was too weak and failed.\n");
	return;
    }
    if (check_overdose())
    {
        write("You feel a bit dizzy.\n");
	return;
    }

    if (TP->query_alignment() < 0)
        strength /= 2;
    if (!RANGERS_MEMBER(this_player()))
        strength /= 3;

    TP->heal_hp(strength + random(strength/2));
    TP->add_fatigue(strength);
    TP->add_mana(strength/10);
    if (objectp(poison = present("poison", TP)))
        poison->cure_poison( ({ "all" }), strength / 2);
}
