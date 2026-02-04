/* A steel club. Mortricia 920729 
 * Used by std_goblin_grd.c   -- Tomas Dec 1999
 */
#include "/d/Terel/include/Terel.h"
inherit STDWEAPON;

#include <wa_types.h>
#include <stdproperties.h>


public void
create_weapon()
{
    set_name("club");
   set_short("heavy stone club");
   set_pshort("heavy stone clubs");
    set_long("It's a heavy stone club.\n");
    set_adj(({"heavy", "stone"}));
    set_hit(20);
    set_pen(35);
    add_prop(OBJ_I_WEIGHT, 15000);
    add_prop(OBJ_I_VOLUME, 5000);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_BOTH);
}
