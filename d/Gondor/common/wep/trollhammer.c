/* heavy trollhammer  */
inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

create_weapon()
{
    set_name(({ "troll-hammer", "weapon", "hammer" }));
    set_pname("troll-hammers");
    add_pname("hammers");
    set_short("heavy iron hammer");
    set_pshort("heavy iron hammers");
    set_long("A large, heavy two-handed troll's hammer, made out of iron.\n");
    set_adj("troll");
    add_adj(({ "heavy", "iron", "large", "two-handed" }));
    set_default_weapon(28, 26, W_CLUB, W_BLUDGEON, W_BOTH, 0);
    add_prop(OBJ_I_WEIGHT, 9600);
    add_prop(OBJ_I_VOLUME, 3400);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(28,26)+random(200)-100);
}
