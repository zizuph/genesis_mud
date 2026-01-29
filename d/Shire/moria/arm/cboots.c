/*
 * Dwarven mining boots. When worn, raises climb skill.
 * Based on gloves from Gondor Shades that do the same.
 * Finwe, January 2005
 */

#include "/d/Shire/sys/defs.h"
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit "/std/armour";
inherit "/lib/keep";

#define AC  15

int added_skill;

void
create_armour()
{
    add_name(({"pair","pair of boots", "boots"}));
    add_pname("pairs of boots");
    add_adj(({"steel","mining"}));
    set_short("pair of steel mining boots");
    set_pshort("pairs of steel mining boots");
    set_long("This pair of steel mining boots was forged by dwarves " +
        "many years ago. They are heavy duty and designed to assist " +
        "in mining and to protect the feet. Steel spurs pattern the " +
        "soles of the boots and the toe tips.\n");
    set_default_armour(AC,A_FEET,({0,0,0}),0);
    set_af(TO);
    set_ac(5);
    add_prop(OBJ_I_WEIGHT,1000);
    add_prop(OBJ_I_VOLUME,1500);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(5)+random(10)+5);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
    add_prop(MAGIC_AM_MAGIC,({55,"enchantment"}));
    add_prop(OBJ_S_WIZINFO,"The boots are on random orcs in Moria. They " +
        "are dwarven mining boots that raise climb 10 + 1/5 the player's " +
        "current skill level.\n");
    add_prop(MAGIC_AM_ID_INFO,({"The boots improve the wearer's climb " +
        "skill when worn.",10}));
    set_keep(1);
}

public int
wear(object arm)
{

    TP->catch_msg("You slip the " + short() + " onto your feet. They " +
        "suddenly feel more nimble.\n");
    say(QCTNAME(TP) + " slips the " + short() + " onto " + HIS_HER(TP) + " feet.\n");

    added_skill = (3 + (TP->query_skill(SS_CLIMB)/ 5));
    if ((TP->query_skill(SS_CLIMB) + added_skill) > 100)
    {
        added_skill = (100-(TP->query_skill(SS_CLIMB)));
    }
    TP->set_skill_extra(SS_CLIMB, (TP->query_skill_extra(SS_CLIMB) + added_skill));
    return 1; 
}

int remove(object arm)
{
    object holder = query_worn();

    if(!holder || !living(holder))
    {
        return 0;
    }

    holder->catch_msg("You tug on the boots and they come off your feet. They " +
        "feel tired now.\n");
    say(QCTNAME(TP)+" tugs on the "+short()+" and they come off.\n");
    holder->set_skill_extra(SS_CLIMB, (holder->query_skill_extra(SS_CLIMB) - added_skill));
    return 1; 
}

