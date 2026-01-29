/*
 * /d/Gondor/guilds/rangers/potions/este.c
 *
 * A potion of poison resistance. The resistance will be additive,
 * but trying to drink too many of this will have ugly consequences.
 *
 * It is created from the ingredients:
 *    - some alcohol, alco-value between 10 and 50
 *    - foxglove herb
 *    - alfirin herb
 *
 * Originally coded by Elessar in April 1996
 *
 * Modification log:
 *  3-Dec-1996, Olorin: Changed to inherit ranger_potion
 *                      made compatible with shops
 *                      fixed messages and adjectives
 *  7-Feb-2001, Alto: Moved to new ranger path.
 * 23-Feb-2013, Mercade: updated for heapable potions.
 *
 * 03-June-2019, Arman: This potion seems to break a lot of rules
 * in relation to how resistance potions should work. This is a 
 * test potion to see if it can be fixed.
 */
#pragma save_binary
#pragma strict_types

#include "../rangers.h"

inherit RANGERS_POTION + "ranger_potion.c";

#include <herb.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

public void
create_ranger_potion()
{
    set_potion_name("avarywalme");
    set_unid_long("This is a strange purple brew.\n");
    set_id_long("This is an Avarywalme potion, a potion " +
        "that will lessen the effects of poison.\n");
    set_adj( ({"purple", }) );
    set_id_diff(24);
    set_soft_amount(30);
    set_alco_amount(20);
    set_potion_value(1670);
    set_id_smell("A waft of bitter air assaults your senses. " +
        "You recognize the sharp smell of foxglove, and know this " +
        "potion may protect against poison.\n");
    set_id_taste("It tastes rather bitter, very typically the " +
        "taste of the foxglove herb.\n");
    set_unid_smell("The potion smells quite bitter.\n");
    set_unid_taste("The potion tastes rather bitter.\n");

    // set_effect(HERB_SPECIAL, "avarywalme", "@@query_strength@@");
    set_effect(HERB_ENHANCING, "poison", 35);
}

int
query_strength()
{
    int alco = query_alco_strength();

    if (alco < 15)
        return 0;

    return min(100, (5 + (alco - 15) * 3));
}

/*
void
special_effect()
{
    object  ob;
    string  how;
    int strength = query_strength();

    if (strength)
    {
        seteuid(getuid());
        ob = clone_object("/std/resistance");
        ob->set_res_type(MAGIC_I_RES_POISON);
        ob->set_strength(strength);
        ob->set_time(strength * 10 + random(strength) * 15);
        ob->move(TP);
        switch (strength)
        {
        case 1..20:
            how = "a little ";
            break;
        case 21..40:
            how = "somewhat ";
            break;
        case 41..60:
            how = "";
            break;
        case 61..100:
            how = "much ";
            break;
        }

        write("You feel " + how + "better prepared to resist poisons now.\n");
    }
    else
        write("The potion was too weak and failed.\n");
}

*/