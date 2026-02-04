/* A dagger. Mortricia 920729 */
inherit "/std/weapon";
#include <stdproperties.h>
#include <wa_types.h>

void
create_weapon()
{
    set_short("sharp dagger");
    set_name("dagger");
    set_long("It's a sharp-looking dagger.\n");
    set_adj("sharp");
    set_wt(W_KNIFE);
    set_dt(W_IMPALE);
    set_hands(W_ANYH);
    add_prop(OBJ_I_VOLUME, 80);
    add_prop(OBJ_I_WEIGHT, 320);
    set_hit(14);
    set_pen(13);
}
