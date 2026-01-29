/*  Crude staff of a Satyr
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           3/21/95  Created
**
**/
inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void create_weapon() {
    set_name("staff");
    set_adj(({"crude","wooden"}));
    set_short("crude wooden staff");
    set_long("It is a crude staff made of wood, not much more than a "+
             "long, thick hardwood branch which seems to have been chewn "+
             "into shape.\n");
    set_hit(3);
    set_pen(3);
 
    set_hands(W_BOTH);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE | W_SLASH);
 
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME,  800);
}
