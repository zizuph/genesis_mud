/*  common dagger of argos
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/30/95  Created
**
**/
inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void
create_weapon()
{
    set_name("dagger");
    set_adj("steel");
    set_short("steel dagger");
    set_long("It is a common steel dagger, with a winged horse engraved "+
             "on the hilt.\n");
 
    set_hit(18);
    set_pen(15);
 
    set_hands(W_NONE);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE | W_SLASH);
 
    add_prop(OBJ_I_WEIGHT,  800);
    add_prop(OBJ_I_VOLUME,  500);
}
