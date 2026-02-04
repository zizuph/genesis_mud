/* A wooden club. Mortricia 920729 */
inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

void
create_weapon()
{
    set_name("club");
    set_short("heavy wooden club");
    set_long("It's a heavy wooden club.\n");
    set_adj("wooden");
    add_adj("heavy");
    set_hit(23);
    set_pen(18);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 1000);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);
}
