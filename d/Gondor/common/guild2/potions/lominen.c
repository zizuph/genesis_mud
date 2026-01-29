/*
 * This is the potion for the artirith spell of the Morgul Mages
 *
 * It is created from the ingredients:
 *    - drink of alco > 10 and soft > 50
 *    - ? mushroom
 *    - corpse of a rat
 *
 * Olorin, Nov 1994
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
    set_potion_name("lominen potion");
    set_id_long("This silvery potion is a lominen potion. Mages can "
      + "use it to enter the realm of shadows. The potion is made from "
      + "some liquid with some alcohol in it, a curugwath herb, and a "
      + "mushroom.\n");
    set_adj("silvery");
    set_unid_long("This is a strange silvery herb potion.\n");
    set_soft_amount(10);
    set_alco_amount(0);
    set_potion_value(720);
    set_id_smell("The potion smells like a mushroom.\n");
    set_id_taste("The potion tastes like a mushroom.\n");
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
        strength = 50 + (alco - 10) * 2;
    if (strength > 100)
        strength = 100;

    set_strength(strength);

    set_effect(HERB_SPECIAL, "artirith", strength);
}

void
special_effect()
{
    int     strength;
    object  ob;

    if (!query_spell_active(this_player(), MS_ARTIR_MIN))
    {
        write("You feel no effect.\n");
        return;
    }

    if (strength = query_strength())
    {
        write("You can now cast \"artirith\".\n");
        seteuid(getuid());
        ob = clone_object(MORGUL_S_LOMINEN_EFFECT);
        ob->set_duration(strength * 6);
        if (ob->move(this_player()))
            ob->move(this_player(), 1);
    }
    else
        write("The potion was too weak and failed.\n");
}
