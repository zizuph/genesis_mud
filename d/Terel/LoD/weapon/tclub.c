/* A steel club. Mortricia 920729 */
#include "/d/Terel/include/Terel.h"
inherit STDWEAPON;

#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

public void
create_weapon()
{
    set_name("club");
    set_long("It's a heavy stone club.\n");
    set_adj(({"heavy", "stone"}));
    set_hit(23);
    set_pen(34);
    add_prop(OBJ_I_WEIGHT, 15000);
    add_prop(OBJ_I_VOLUME, 3000);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);
}
