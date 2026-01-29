// filename:        /d/Avenir/common/holm/sea_shawl.c
// creator(s):      Lilith  04/16/97
// purpose:         Shawl of the selkie Erinys
// note:            Raises awareness 25;
/*
 * Revisions:
 * 	Lilith, Sep 1997: Made changes to prevent runtime error.
 * 	Lucius, Aug 2017: Stripped never-used hizarbin code,
 * 			  un-randomized AC.
 */
inherit "/d/Avenir/inherit/cloth_arm";
//inherit "/lib/keep";

#include "/d/Avenir/common/holm/holm.h"
#include <formulas.h>
#include <ss_types.h>
#include <wa_types.h>

#define MANA_COST 30
#define WEAR_PROP "_wearing_sea_shawl"

public void
create_armour()
{
    if (!IS_CLONE)
        return;

    set_name("shawl");
    add_name(({"erinys_shawl", "sea_shawl"}));
    set_short("translucent fringed shawl");
    set_adj(({"translucent", "fringed"}));
    set_long ("This shawl is made of a material previously "+
        "unknown to you. It is translucent, with the sheen of "+
        "a pearl, and has a fine fringe around the edges. It "+
        "is an article of inspired beauty.\n");

//    set_keep(1);
    set_ac(30);
    set_at(A_ROBE);
    set_af(this_object());

    add_prop(OBJ_I_VALUE, 3000);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(TO->query_ac(), A_ROBE) / 2);
    add_prop(OBJ_M_NO_SELL, "The shopkeeper whispers to you: Too "+
        "rich for my blood!\n");
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 40, "life" }));
    add_prop(MAGIC_AM_ID_INFO, ({"This is the shawl of Erinys, the "+
       "selkie daughter of Hizarbin, the sea god of Sybarus. "+
       "It is reputed to heighten the awareness of the wearer."+
       "\n", 30}));
}

mixed
wear(object ob)
{
    object tp = this_player();

    if (TP->query_mana() <= MANA_COST)
    {
        return "You do not have the mental strength to wear "+
               "this shawl.\n";
    }

    tp->add_mana(-MANA_COST);
    if (!tp->query_prop(WEAR_PROP))
    {
        tp->add_prop(WEAR_PROP, 1);
        tp->catch_msg("You feel an increased sensitivity to and "+
            "awareness of your environment.\n");
        tp->set_skill_extra(SS_AWARENESS,
            this_player()->query_skill_extra(SS_AWARENESS) + 25);
    }
    return 0;
}

mixed
remove(object ob)
{
    object tp = query_worn();
    if (tp->query_prop(WEAR_PROP))
    {
        tp->remove_prop(WEAR_PROP);
        tp->catch_msg("You feel a sense of loss as your heightened awareness "+
            "of your environment diminishes.\n");
        tp->set_skill_extra(SS_AWARENESS,
            tp->query_skill_extra(SS_AWARENESS) - 25);
    }
    return 0;
}
