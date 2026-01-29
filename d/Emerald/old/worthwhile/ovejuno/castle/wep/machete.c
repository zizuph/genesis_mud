/* Machete. To be used by the insectoids in the manor garden
in Re Albi. Coded by Marisol (1/20/98) Marisol Ramos @ 1998*/


inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>


void
create_weapon()
{
    set_name("machete");
    set_short("large machete");
    set_long("It's large and sharp.\n");

    set_adj("large");

    set_hit(10);
    set_pen(10);

    set_wt(W_KNIFE);
    set_dt(W_SLASH | W_IMPALE);

    set_hands(W_ANYH);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(10,10) + random(25) -10);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/1);

}
