/* A sword. Mortricia 920729 */
inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("sword");
    set_short("simple sword");
    set_long("It's a simple sword, fairly sharp though\n");
    set_adj("simple");
    add_prop(OBJ_I_WEIGHT, 7000);
    add_prop(OBJ_I_VOLUME, 1000);
    set_hit(15);
    set_pen(15);
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_ANYH);
}
