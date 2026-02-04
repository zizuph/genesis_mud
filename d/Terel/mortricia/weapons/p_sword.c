/*
    A sword. Mortricia 920729
 */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("sword");
    set_short("beautiful sword");
    set_long("It's a beautiful sword, almost like a souvenir.\n");
    set_adj("beautiful");

    set_hit(30);
    set_pen(30);
    add_prop(OBJ_I_WEIGHT, 12000);
    add_prop(OBJ_I_VOLUME, 9000);
    
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);

    set_hands(W_ANYH);
}
