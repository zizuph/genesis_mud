/* Stralle @ Genesis 031109
 */

#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <formulas.h>

void
create_weapon()
{
    set_name("dagger");
    set_adj(({"steel", "parrying"}));
    set_short("steel parrying dagger");
    set_pshort("steel parrying daggers");
    set_long("Slightly triangular, the base near the hilt being " +
        "wider than your fist, this steel dagger would make for " +
        "an excellent parrying dagger. It extends about half " +
        "a foot to its sharp point while the edges does not look " +
        "that sharp. Obviously this weapon was made for thrusting " +
        "instead of slicing.\n");
    
    set_dt(W_IMPALE);
    set_hands(W_ANYH);
    set_hit(25);
    set_pen(30);
    set_wt(W_KNIFE);
    set_wf(this_object());
    
    add_prop(OBJ_I_WEIGHT, 800);
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(25, 30));
}

mixed
wield(object weapon)
{
    this_player()->set_skill_extra(SS_PARRY,
        this_player()->query_skill_extra(SS_PARRY) + 7);
    return 0;
}

mixed
unwield(object weapon)
{
    (this_object()->query_wielded())->set_skill_extra(SS_PARRY,
        (this_object()->query_wielded())->query_skill_extra(SS_PARRY) - 7);
    return 0;
}
