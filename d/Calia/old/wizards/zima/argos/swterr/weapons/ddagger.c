/*  Dagger of the Priestesses of Defonia
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/12/94  Created
**
**/
inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void
create_weapon()
{
    set_name(({"silver dagger","dagger"}));
    set_adj("silver");
    set_short("silver dagger");
    set_long("A silver dagger engraved with a raven on the hilt.\n");
 
    set_hit(20);
    set_pen(20);
 
    set_hands(W_NONE);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE | W_SLASH);
 
    add_prop(OBJ_I_WEIGHT,  800);
    add_prop(OBJ_I_VOLUME,  500);
}
