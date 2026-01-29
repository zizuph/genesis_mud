/*  file:  /d/Calia/sea/weapons/fishing_pole.c
 *  description:  This fishing pole is carried by the unlucky
 *    fisherman on the Calian beach area.
 */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("pole");
    add_name("stick");
    set_adj("fishing");
    set_short("fishing pole");
    set_pshort("fishing poles");
    set_long("This is a simple fishing pole, judging"+
      " from the coarse string dangling from one end. You"+
      " notice that the string has no hook or lure attached."+
      "\n");

    set_hit(1);
    set_pen(1);

    set_wt(W_POLEARM);
    set_dt(W_BLUDGEON);

    set_hands(W_LEFT);

    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 300);
}

