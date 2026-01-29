/* This file is a copy and adaption from the dragonbone. */

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <options.h>
#include <tasks.h>
#include <formulas.h>
#include <filter_funs.h>
#include "/d/Krynn/common/defs.h"

inherit "/std/weapon";
inherit "/lib/keep";

void
create_weapon()
{
    set_name("mace");
    add_name("club");
    add_adj("large");
    add_adj("sturdy");
    set_short("large sturdy mace");
    set_long("This is a large sturdy mace. " +
             "It looks like it would requite a " +
             "lot of strength to wield this weapon effectively.\n");

    set_default_weapon(40,50, W_CLUB, W_BLUDGEON, W_BOTH);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 50, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, ({"This weapon is enchanted to last " +
                                 "longer and hit the enemy harder.\n", 35}));
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_WEIGHT, 30000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(40,50) + random(500));

    set_likely_dull(1);
    set_likely_corr(1);
    set_likely_break(1);

    seteuid(getuid(TO));
}

varargs void
remove_broken(int silent = 0)
{
    if (calling_function() == "item_expiration_break") 
        ::remove_broken(silent);

    return;
}

int
set_dull(int du)
{
    return 0;
}
