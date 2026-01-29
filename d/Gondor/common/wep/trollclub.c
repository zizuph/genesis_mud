/* heavy troll-club  */
inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void
create_weapon()
{
    set_name(({ "troll-club", "weapon", "club" }));
    set_pname("troll-clubs");
    add_pname("clubs");
    set_short("heavy stone troll-club");
    set_pshort("heavy stone troll-clubs");
    set_long("A large, heavy two-handed troll's club, made out of stone.\n");
    set_adj("troll");
    add_adj(({ "heavy", "stone", "large", "two-handed" }));
    set_default_weapon(20, 27, W_CLUB, W_BLUDGEON, W_BOTH, 0);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 4300);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(20,27)+random(200)-100);
}
