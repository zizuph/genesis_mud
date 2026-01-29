/*
 * Elessar, August 1994
 *
 * Modification log:
 *  3-Dec-1996, Olorin: Changed inheritance to ranger_potion
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/guild/potions/ranger_potion.c";

#include <herb.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

public void
create_ranger_potion()
{
    set_potion_name("wenya potion");
    set_unid_long("This is a strange herb brew.\n");
    set_id_long(BSN("This is a Wenya potion, a strengthening "+
      "potion that Rangers can mix."));
    set_id_diff(10);
    set_soft_amount(20);
    set_alco_amount(4);
    set_adj("green");
    set_potion_value(1228);
    set_id_smell("The potion smells strongly, an odour that seems "+
     "to tickle your nostrils. There is obviously suranie and tuo in it, "+
     "and some alcohol as well. You know this potion will strengthen you.\n");
    set_id_taste("A rather bitter taste spreads in your mouth. You guess " +
        "it is made from herbs and some alcohol. Strengthening, perhaps?\n");
    set_unid_smell("The potion has a strong, pungent herb odour.\n");
    set_unid_taste("The potion tastes strongly of herbs and alcohol.\n");
}

public varargs void 
set_up_effect(int soft, int alco, int rank)
{
    set_soft_amount(soft);
    set_alco_amount(alco);
    set_rank(rank);

    if (alco < 25)
        Strength = 0;
    else
        Strength = 50 + (alco - 25) * 5 + Rank;
    if (Strength > 100)
        Strength = 100;
    if (Rank <= 0)
	Strength /= 3;

    set_effect(HERB_ENHANCING, "str", Strength);
}


