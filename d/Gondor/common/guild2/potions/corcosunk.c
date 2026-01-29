/*
 * This is the potion for the crabandir spell of the Morgul Mages
 * for the Genesis mortar.
 *
 * It is created from the ingredients:
 *    - drink of alco > 10 and soft > 20
 *    - tuo herb, myrtle herb
 *    - an eye
 *
 * Olorin, Dec 1995
 */
#pragma strict_types

inherit "/d/Gondor/common/guild2/potions/morgul_potion.c";

#include <herb.h>
#include <poison_types.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/newspells/spells.h"
#include "potion_defs.h"

public void
create_morgul_potion()
{
    set_potion_name("corcosunk potion");
    set_id_long("This green potion is a corcosunk potion. When "
      + "quaffed by mages "
      + "who are learnt in the proper spells, it can be used to summon "
      + "birds from the realm of the shadows. It can be mixed using "
      + "an eye, a tuo lichen, a myrtle berry and some alcohol.\n");
    set_adj("green");
    set_unid_long("This is a strange green herb potion.\n");
    set_soft_amount(10);
    set_alco_amount(0);
    set_potion_value(1296);
    set_id_smell("The potion smells slightly of lichen and myrtle berries.\n");
    set_id_taste("The potion tastes slightly of lichen and myrtle berries.\n");
    set_unid_smell("The potion smells of nothing.\n");
    set_unid_taste("The potion tastes of nothing.\n");
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
        strength = 50 + (alco - 10) * 4;
    if (strength > 100)
        strength = 100;

    set_strength(strength);

    set_effect(HERB_SPECIAL, "corcosunk", strength);
}

void
special_effect()
{
    int     strength;
    object  ob;

    if (!query_spell_active(this_player(), MS_CRABA_MIN))
    {
        write("You feel no effect.\n");
        return;
    }

    if (strength = query_strength())
    {
        write("You can now cast \"crabandir\".\n");
        seteuid(getuid());
        ob = clone_object(MORGUL_S_CORCOSUNK_EFFECT);
        ob->set_duration(strength * 6);
        if (ob->move(this_player()))
            ob->move(this_player(), 1);
    }
    else
        write("The potion was too weak and failed.\n");
}
