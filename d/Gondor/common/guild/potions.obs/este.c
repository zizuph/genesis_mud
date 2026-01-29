/*
 * This is the healing potion that Rangers can make from Athelas
 *
 * It is created from the ingredients:
 *    - pint of water
 *    - athelas herb
 *
 * Elessar, August 1994
 *
 * Modification log:
 * Added in overdosing to prevent overuse. Initial 5 potions, then 1
 * every 30 seconds for non rangers. Initial 5 potions, then 2 every
 * 30 seconds for rangers. Potion strength halved for people under 0
 * alignment. - Gwyneth, January 9, 2001
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/guild/potions/ranger_potion.c";

#include <herb.h>
#include "/d/Gondor/defs.h"

#define DOSE			(50)
#define MAX_STR			(250)
#define OD_OBJ			("/d/Gondor/common/lib/overdose.c")
#define RATE			(50)
#define RRATE			(100)
#define RECOVER_TIME		(30)

public void
create_ranger_potion()
{
    set_potion_name("este potion");
    set_unid_long("This is a strange herb brew.\n");
    set_id_long(BSN("This is an Este potion, a refreshing and healing "+
      "potion the Rangers can make. If mixed by the "+
      "most skilled hands, it can even cure poisoning. However, too " +
      "much of a good thing can be bad."));
    set_adj("clear");
    set_id_diff(17);
    set_soft_amount(30);
    set_alco_amount(0);
    set_potion_value(1100);
    set_id_smell("The potion smells refreshing, a pungent smell that seems "+
     "to clear even the air around it. You recognize the smell of athelas, "+
     "and know this potion heals well.\n");
    set_id_taste("A clear fresh taste spreads in your mouth. You recognize " +
        "the refreshing taste of kingsfoil.\n");
    set_unid_smell("The potion smells pungently refreshing.\n");
    set_unid_taste("The potion tastes pungently refreshing.\n");
}

public varargs void 
set_up_effect(int soft, int alco, int rank)
{
    set_soft_amount(soft);
    set_alco_amount(alco);
    set_rank(rank);

    if (alco > 10)
        Strength = 0;
    else
        Strength = 50 + (10-alco) * 5 + Rank;
    if (Strength > 100)
        Strength = 100;
    if (Rank <= 0)
	Strength /= 3;

    set_effect(HERB_SPECIAL, "este", Strength);
}

public int
check_overdose()
{
    int i, level;
    object ob;

    if (ob = present("este_overdose", this_player()))
    {
        i = ob->calculate_overdose();

        if (i < 1)
        {
            ob->reset_overdose();
        }

        /* Adds to the overdose tally */
        ob->set_overdose_dose(DOSE);
        level = ob->calculate_overdose();
    }
    else
    {
        ob = clone_object(OD_OBJ);

        /* Rangers have an advantage */
        if (IS_RANGER(this_player()))
            ob->set_overdose(DOSE,MAX_STR,RRATE,RECOVER_TIME,"este_overdose");
        else
            ob->set_overdose(DOSE,MAX_STR,RATE,RECOVER_TIME,"este_overdose");

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

    if (Strength)
    {
        if (check_overdose())
        {
            write("You feel a bit dizzy.\n");
        }
        else
        {
            if (TP->query_alignment() < 0)
                Strength /= 2;

            TP->heal_hp(Strength + random(Strength/2));
            TP->add_fatigue(Strength);
            TP->add_mana(Strength/10);
            if (objectp(poison = present("poison", TP)))
                poison->cure_poison( ({ "all" }), Strength/2);
        }
    }
    else
        write("The potion was too weak and failed.\n");
}
