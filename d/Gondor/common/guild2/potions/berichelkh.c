/*
 * This is the potion for the ringurth spell of the Morgul Mages
 * for the Genesis mortar.
 *
 * It is created from the ingredients:
 *    - drink of alco > 10 and soft > 150
 *    - frostheal herb
 *
 * Olorin, May 1994
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/guild2/potions/morgul_potion.c";

#include <ss_types.h>
#include <herb.h>
#include <poison_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/newspells/spells.h"
#include "potion_defs.h"

public void
create_morgul_potion()
{
    set_potion_name("berichelkh potion");
    set_id_long("This white potion is a berichelkh potion. Mages can "
      + "use it to protect themselves. The potion is made from the "
      + "frostheal herb and some liquid with a little alcohol in it.\n");
    set_adj("white");
    set_unid_long("This is a strange white herb potion.\n");
    set_soft_amount(10);
    set_alco_amount(0);
    set_potion_value(864);
    set_id_smell("The potion smells slightly of frostheal.\n");
    set_id_taste("The potion tastes slightly of frostheal.\n");
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

    if (strength)
    {
        set_poison_file(MORGUL_S_BERICHELKH_POISON);
        set_poison_damage(({POISON_STAT, SS_CON}));
        set_effect(HERB_POISONING, "berichelkh", strength);
    }

    if (!pointerp(effects))
        effects = ({ });

    add_effect(HERB_ENHANCING, "cold", strength/2);
    add_effect(HERB_SPECIAL, "ringurth", strength);

    set_strength(strength);
}

void
special_effect()
{
    if (!query_spell_active(this_player(), MS_RINGU_MIN))
        return;

    if (query_strength())
        write("You can now cast \"ringurth\".\n");
    else
        write("The potion was too weak and failed.\n");
}
