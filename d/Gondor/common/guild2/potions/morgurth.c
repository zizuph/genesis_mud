/*
 * This is the potion for the morthul spell of the Morgul Mages
 *
 * It is created from the ingredients:
 *    - drink of alco > 40
 *    - morgurth herb
 *    - angurth herb
 *
 * Olorin, July 1994
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/guild2/potions/morgul_potion";

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
    set_potion_name("morgurth potion");
    set_id_long("This black potion is a morgurth potion. Mages "
      + "can use it to cast poison spells. The potion is made from "
      + "the angurth herb, a body part, and lots of alcohol.\n");
    set_adj("black");
    set_unid_long("This is a strange black herb potion.\n");
    set_soft_amount(10);
    set_alco_amount(0);
    set_potion_value(1728);
    set_id_smell("The potion smells pungently of decay. You also " +
        "notice fumes of alcohol, the smell of rotten flesh and of " +
        "an angurth herb.\n");
    set_id_taste("The potion tastes pungently of decay. You also " +
        "notice fumes of alcohol, the taste of rotten flesh and of " +
        "an angurth herb.\n");
    set_unid_smell("The potion smells pungently of decay.\n");
    set_unid_taste("The potion tastes pungently of decay.\n");
}

void
set_up_effect(int soft, int alco)
{
    int     strength;

    set_soft_amount(soft);
    set_alco_amount(alco);

    if (alco < 40)
        strength = 0;
    else
        strength = 50 + (alco - 40) * 5;
    if (strength > 100)
        strength = 100;

    set_strength(strength);

    set_effect(HERB_SPECIAL, "morgurth", strength);
}

void
special_effect()
{
    int     strength;
    object  ob;

    if (!query_spell_active(this_player(), MS_MORTH_MIN))
    {
        write("You feel no effect.\n");
        return;
    }

    if (strength = query_strength())
    {
        write("You can now cast \"morthul\".\n");
        seteuid(getuid());
        ob = clone_object(MORGUL_S_MORGURTH_EFFECT);
        ob->set_duration(strength * 12);
        if (ob->move(this_player()))
            ob->move(this_player(), 1);
    }
    else
        write("The potion was too weak and failed.\n");
}
