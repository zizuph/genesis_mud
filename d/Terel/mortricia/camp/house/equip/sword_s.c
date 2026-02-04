/* A sword. Mortricia 920729 */
inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

void
create_weapon()
{
    set_name("sword");
    set_short("short steel sword");
    set_long("It's a short steel sword, fairly sharp though.\n");
    set_adj("steel");
    add_adj("short");
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 500);
    set_hit(20);
    set_pen(20);
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_ANYH);
}
