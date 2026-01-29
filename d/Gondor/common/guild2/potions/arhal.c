/*
 * This is the potion for the arhalgul spell of the Morgul Mages
 *
 * It is created from the ingredients:
 *    - drink of alco > 10
 *    - sage herb
 *
 * Olorin, July 1994
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/guild2/potions/morgul_potion";

#include <herb.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/newspells/spells.h"
#include "potion_defs.h"

public void
create_morgul_potion()
{
    set_potion_name("arhal potion");
    set_unid_long("This is a strange clear herb potion.\n");
    set_id_long("This clear potion is an arhal potion. Mages "
      + "can use it to cast reveal spells. The potion is made from "
      + "the sage herb and a little alcohol.\n");
    set_adj("clear");
    set_soft_amount(10);
    set_alco_amount(0);
    set_potion_value(144);
    set_id_smell("The potion smells pungently of sage. You also " +
        "notice fumes of alcohol.\n");
    set_id_taste("The potion tastes pungently of sage. You also " +
        "notice fumes of alcohol.\n");
    set_unid_smell("The potion smells pungently of herbs.\n");
    set_unid_taste("The potion tastes pungently of herbs.\n");
}

public void
set_up_effect(int soft, int alco)
{
    int     strength;

    set_soft_amount(soft);
    set_alco_amount(alco);

    if (alco < 10)
        strength = 0;
    else
        strength = 20 + (alco - 10) * 4;
    if (strength > 100)
        strength = 100;

    set_strength(strength);

    set_effect(HERB_SPECIAL, "arhal", strength);

    return 0;
}

void
special_effect()
{
    int     strength = query_strength();
    object  ob;

    if (!query_spell_active(this_player(), MS_ARHAL_MIN))
    {
        write("You feel no effect.\n");
        return;
    }

    if (strength)
    {
        write("You can now cast \"arhalgul\".\n");
        seteuid(getuid());
        ob = clone_object(MORGUL_S_ARHAL_EFFECT);
        ob->set_duration(strength * 3);
        if (ob->move(this_player()))
            ob->move(this_player(), 1);
    }
    else
        write("The potion was too weak and failed.\n");
}
