/*
 * This is the potion for the narusse spell of the Morgul Mages
 * for the Genesis mortar.
 *
 * It is created from the ingredients:
 *    - drink of alco > 30
 *    - thyme, tyelka, snake meat
 *
 * Olorin, September 1996
 *
 *	Copyright (c) 1996 by Christian Markus
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/guild2/potions/morgul_potion.c";

#include <herb.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/newspells/spells.h"
#include "potion_defs.h"

public void
create_morgul_potion()
{
    set_potion_name("bragollach potion");
    set_unid_long("This is a strange brown herb potion.\n");
    set_id_long("This brown potion is a bragollach potion. Mages "
      + "can use it to cast enchantment spells. The potion is made from "
      + "the tyelka mushroom, the thyme herb, snake meat and a strong "
      + "alcoholic drink.\n");
    set_adj("brown");
    set_soft_amount(10);
    set_alco_amount(0);
    set_potion_value(2160);
    set_id_smell("The potion smells pungently of mushrooms and "
	  + "decaying flesh. The fumes rising from the potion burn "
	  + "in your nose like a hot fire, but you can also recognize "
	  + "the faint smell of thyme among them.\n");
    set_id_taste("The potion tastes pungently of mushrooms and "
	  + "decaying flesh. It burns hotly on your tongue, but you "
     + "can also recognize the faint taste of thyme.\n");
    set_unid_smell("The potion smells pungently of mushrooms.\n");
    set_unid_taste("The potion tastes pungently of mushrooms.\n");
}

public void
set_up_effect(int soft, int alco)
{
    int     strength;

    set_soft_amount(soft);
    set_alco_amount(alco);

    if (alco < 30)
        strength = 0;
    else
        strength = 40 + (alco - 30) * 4;
    if (strength > 100)
        strength = 100;

    set_strength(strength);

    set_effect(HERB_SPECIAL, "bragollach", strength);
}

void
special_effect()
{
    int     strength;
    object  ob;

    if (!query_spell_active(this_player(), MS_NARUS_MIN))
    {
        write("You feel no effect.\n");
        return;
    }

    if (strength = query_strength())
    {
        write("You can now cast \"narusse\".\n");
        seteuid(getuid());
        ob = clone_object(MORGUL_S_BRAGOLLACH_EFFECT);
        ob->set_duration(strength * 3);
        if (ob->move(this_player()))
            ob->move(this_player(), 1);
    }
    else
        write("The potion was too weak and failed.\n");
}
