/* This file has some bits taken from Jeremiahs code of Verminaards mace.*/

// Navarre Nov 4th 2008, changing add_name("heavy") to add_adj("heavy").

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
    set_name(({"dragonbone","bone"}));
    add_adj("heavy");
    set_short("heavy dragonbone");
    set_long("This huge and heavy thighbone has been cut from a creature " +
       "of legend, a mighty dragon! This remnant of this mythical beast " +
       "emanates power, almost as if the mystical energies of the dragon " +
       "still remained and embued this bone.\n");

    set_default_weapon(40,50, W_CLUB, W_BLUDGEON, W_BOTH);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 50, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, ({"A great thighbone from an ancient dragon. " +
       "This bone still has the magical energies of the beast it came from " +
       "embued in it, making it incredibly damaging if used as a club. " +
       "It is also unlikely to break through mundane means.\n",35}));


    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_WEIGHT, 30000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(40,50) + random(500));

    set_likely_dull(1);
    set_likely_corr(1);
    set_likely_break(1);

    set_wf(TO);

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

void
wield_message1()
{
    wielder->catch_msg("You hear a serpentine hiss behind you as you grip " +
       "the heavy dragonbone... but there is nothing there. Must be your " +
       "imagination.\n");

}
 
mixed
wield(object what)
{
    set_alarm(1.0, 0.0, "wield_message1");
 
    return 0;
}
