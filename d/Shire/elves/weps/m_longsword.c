/*
 * Common longsword for wandering elves
 * By Finwe, February 2018
 */
inherit "/std/weapon";

#include "/d/Shire/sys/defs.h"
#include <composite.h>
#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <options.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>

int added_skill;

void
create_weapon()
{
    set_name(({"sword", "longsword"}));
    set_pname(({"swords", "longswords"}));
    set_adj("ancient");
    set_short("ancient longsword");
    
    set_long("This longsword was forged by the elves of Imladris. It is made of high-steel and shows no signs of battle. The blade is long and looks cumbersome, but it feels perfectly balanced in your hands. The blade is decorated with intricate designs, running from the tip to the handle/\n");


    add_item(({"designs", "design", "intricate designs", 
            "intricate design", "fancy ornamentation", "flourishes"}),
      "The designs are flourishes and fancy ornamentation that " +
      "decorate the blade. They are very intricate and show great " +
      "skill by elven metalsmiths.\n");
    add_item(({"crossguard"}),
        "It is a horizontal bar at the base of the blade that " +
        "protects the wielder. The bar is curves upwards slightly.\n");
    add_item(({"handle"}),
        "The handle of the blade is long and made of dark wood. " +
        "It is slightly ridged to provide a good grip.\n");
    add_item(({"pommel"}),
        "The pommel of the sword extends from the base of the " +
        "handle. It is made of steel and is rounded.\n");

    set_default_weapon(45,40, W_SWORD, W_SLASH | W_IMPALE, W_BOTH);
    set_wf(TO);

    add_prop(OBJ_I_VOLUME, 3600);
    add_prop(OBJ_I_WEIGHT, 11500);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(45,40)); /* magic sword */
    add_prop(OBJ_M_NO_BUY, 1);

}

public mixed
wield(object weapon)
{
    object  tp = TP;

    added_skill = -1;

    added_skill = (10 + ((tp->query_skill(SS_PARRY))/5));
    if ((tp->query_skill(SS_PARRY) + added_skill) > 100)
    {
        added_skill = (100 - (tp->query_skill(SS_PARRY)));
    }
    tp->set_skill_extra(SS_PARRY,(tp->query_skill_extra(SS_PARRY) + added_skill));

    tp->add_magic_effect(TO);

    write("You wield the longsword, and suddenly feel able to protect yourself.\n");
    TP->tell_watcher(QCTNAME(TP) + " wields an elven longsword.\n");     
    return 1;
}

public mixed
unwield(object weapon)
{
    object  tp = query_wielded();

    if (added_skill < 0)
        return 0;

    if (!living(tp))
        return 0;

    tp->set_skill_extra(SS_PARRY, (tp->query_skill_extra(SS_PARRY) - added_skill));

    tp->remove_magic_effect(TO);
    write("You unwield the "+short()+" and feel more vulnerable.\n");
    TP->tell_watcher(QCTNAME(TP) + " unwields the "+short()+".");
    return 1;
}
