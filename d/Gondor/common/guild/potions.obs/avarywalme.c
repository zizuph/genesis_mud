/*
 * A potion of poison resistance. The resistance will be additive,
 * but trying to drink too many of this will have ugly consequences.
 *
 * It is created from the ingredients:
 *    - some alcohol, alco-value between 10 and 50
 *    - foxglove herb
 *    - alfirin herb
 *
 * Elessar, April 1996
 *
 * Modification log:
 *  3-Dec-1996, Olorin: Changed to inherit ranger_potion
 *                      made compatible with shops
 *                      fixed messages and adjectives
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/guild/potions/ranger_potion.c";

#include <herb.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

public void
create_ranger_potion()
{
    set_potion_name("avarywalme potion");
    set_unid_long("This is a strange purple brew.\n");
    set_id_long(BSN("This is an Avarywalme potion, a potion "+
      "that will lessen the effects of poison."));
    set_adj( ({"purple", }) );
    set_id_diff(24);
    set_soft_amount(30);
    set_alco_amount(20);
    set_potion_value(1670);
    set_id_smell("A waft of bitter air attacks your senses. "
      + "You recognize the sharp smell of foxglove, and know this "
      + "potion may protect against poison.\n");
    set_id_taste("It tastes rather bitter, very typically the "
      + "taste of the foxglove herb.\n");
    set_unid_smell("The potion smells quite bitter.\n");
    set_unid_taste("The potion tastes rather bitter.\n");
}

public varargs void
set_up_effect(int soft, int alco, int rank)
{
    set_soft_amount(soft);
    set_alco_amount(alco);
    set_rank(rank);

    if (Rank <= 10)
        Strength = 1;
    else if (alco < 10)
        Strength = 0;
    else if (alco > 50)
        Strength = 5;
    else
        Strength = (alco / 2) + (Rank / 10);
    if (Strength > 35)
        Strength = 35;

    set_effect(HERB_SPECIAL, "avarywalme", Strength);
}

void
special_effect()
{
    object  ob;
    string  how;

    if (Strength)
    {
        ob = clone_object("/std/resistance");
        ob->set_res_type(MAGIC_I_RES_POISON);
        ob->set_strength(Strength);
        ob->set_time(Strength*10 + random(Strength)*15);
        ob->move(TP);
	switch (Strength)
	{
	case 1..10:
	    how = "a little "; break;
	default:
	case 11..20:
	    how = ""; break;
	case 21..100:
	    how = "much "; break;
	}
        TP->catch_msg("You feel " + how + "better prepared to resist poisons now.\n");
    }
    else
        write("The potion was too weak and failed.\n");
}

public string
strength_adj()
{
    if (!query_identified())
        return "unknown";

    switch(Strength)
    {
        default:
        case 0..2:
            return "watery";
        case 3..8:
            return "thin";
        case 9..17:
            return "light";
        case 18..30:
            return "strong";
        case 31..50:
            return "powerful";
     }
}

