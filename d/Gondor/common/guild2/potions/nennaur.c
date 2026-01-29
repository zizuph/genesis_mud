/*
 * This is the potion for the morthul spell of the Morgul Mages
 *
 * It is created from the ingredients:
 *    - drink of alco > 44
 *    - red pepper
 *    - pile of ashes (from ranger campfire)
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
    set_potion_name("nennaur potion");
    set_adj(({"ash-grey", "grey", "gray", }));
    set_id_long("This ash-grey potion is a nennaur potion, the "
      + "'Water of Fire'. " +
        "Mages can use it to cast fire spells. The potion is made " +
        "from the some ashes, a red pepper, and lots of alcohol.\n");
    set_unid_long("This is a strange ash-grey herb potion.\n");
    set_soft_amount(10);
    set_alco_amount(0);
    set_potion_value(2016);
    set_id_smell("The potion smells pungently of ashes. You also " +
        "notice fumes of alcohol and the smell of red pepper.\n");
    set_id_taste("The potion tastes pungently of ashes. You also " +
        "notice fumes of alcohol and the smell of red pepper.\n");
    set_unid_smell("The potion smells pungently of ashes.\n");
    set_unid_taste("The potion tastes pungently of ashes.\n");
}

void
set_up_effect(int soft, int alco)
{
    set_soft_amount(soft);
    set_alco_amount(alco);

    if (alco < 44)
        set_strength(0);
    else
        set_strength(50 + (alco - 44) * 10);
    if (query_strength() > 100)
        set_strength(100);

    set_effect(HERB_SPECIAL, "nennaur", query_strength());
}

void
special_effect()
{
    object  ob;

    if (!query_spell_active(this_player(), MS_THUNA_MIN))
    {
        write("You feel no effect.\n");
        return;
    }

    if (query_strength())
    {
        write("You can now cast \"thunaur\".\n");
        seteuid(getuid());
        ob = clone_object(MORGUL_S_NENNAUR_EFFECT);
        ob->set_duration(query_strength() * 12);
        if (ob->move(this_player()))
            ob->move(this_player(), 1);
    }
    else
        write("The potion was too weak and failed.\n");
}
