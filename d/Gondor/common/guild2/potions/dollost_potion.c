/*
 * This is the potion for the dollost spell of the Morgul Mages
 *
 * It is created from the ingredients:
 *    - drink of alco > 25
 *    - madwort herb
 *
 * Olorin, May 1994
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/guild2/potions/morgul_potion.c";

#include <herb.h>
#include <macros.h>
#include <poison_types.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/newspells/spells.h"
#include "potion_defs.h"

public void
create_morgul_potion()
{
    set_potion_name("dollost potion");
    set_adj("golden");
    set_unid_long("This is a strange golden herb wine.\n");
    set_id_long("This is a dollost potion, a poisonous golden wine made from madwort.\n");
    set_soft_amount(10);
    set_alco_amount(0);
    set_potion_value(432);
    set_id_smell("The potion smells pungently of madwort.\n");
    set_id_taste("The potion tastes pungently of madwort.\n");
    set_unid_smell("The potion smells rather pungent.\n");
    set_unid_taste("The potion tastes rather pungent.\n");
}

public void
set_up_effect(int soft, int alco)
{
    int     strength;

    set_soft_amount(soft);
    set_alco_amount(alco);

    if (alco < 25)
        strength = 0;
    else
        strength = 50 + (alco - 25) * 2;

    if (strength)
    {
        set_poison_file(MORGUL_S_DOLLOST_POISON);
        set_poison_damage(({POISON_HP, 50, POISON_STAT, SS_CON}));
        set_effect(HERB_POISONING,"dollost", strength);
    }
    else
    {
        set_poison_damage(({POISON_HP, 50, POISON_FATIGUE, 20, POISON_MANA, 50, POISON_STAT, SS_CON}));
        set_effect(HERB_POISONING,"madwort", 100);
    }

    set_strength(strength);

    add_effect(HERB_SPECIAL, "dollost", strength);
}

void
special_effect()
{
    if (!query_spell_active(this_player(), MS_DOLLO_MIN))
        return;

    if (query_strength())
        write("As long as the poisoning is effective, you can cast \"dollost\".\n");
    else
        write("The potion was too weak and failed.\n");
}

string
strength_adj()
{
    if (!query_identified())
        return "strange";

    switch (query_strength())
    {
        default:
        case 0..50:
            return "watery";
        case 51..70:
            return "light";
        case 71..90:
            return "strong";
        case 91..100:
            return "powerful";
        case 101..1000:
            return "poisonous";
     }
}
