/*
 * /d/Gondor/guilds/rangers/potions/wenya.c
 *
 * Ranger potion for enhancing strenth.
 *
 * Originally coded by Elessar in August 1994
 *
 * Modification log:
 *  3-Dec-1996, Olorin: Changed inheritance to ranger_potion
 *  7-Feb-2001, Alto: Moved to new ranger path, no major modifications.
 * 23-Feb-2013, Mercade: updated for heapable potions.
 */
#include "../rangers.h"

inherit RANGERS_POTION + "ranger_potion.c";

#include <herb.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

public void
create_ranger_potion()
{
    set_potion_name("wenya");
    set_unid_long("This is a strange herb brew.\n");
    set_id_long("This is a Wenya potion, a strengthening " +
        "potion that Rangers can mix.\n");
    set_id_diff(10);
    set_soft_amount(20);
    set_alco_amount(4);
    set_adj("green");
    set_potion_value(1228);
    set_id_smell("The potion smells strongly, an odour that seems to " +
        "tickle your nostrils. There is obviously suranie and tuo in it, " +
        "and some alcohol as well. You know this potion will strengthen " +
        "you.\n");
    set_id_taste("A rather bitter taste spreads in your mouth. You guess " +
        "it is made from herbs and some alcohol. Strengthening, perhaps?\n");
    set_unid_smell("The potion has a strong, pungent herb odour.\n");
    set_unid_taste("The potion tastes strongly of herbs and alcohol.\n");

    set_effect(HERB_ENHANCING, "str", "@@query_strength@@");
}

int
query_strength()
{
    int alco = query_alco_strength();

    if (alco < 25)
        return 0;

    return min(100, (50 + (alco - 25) * 5));
}
