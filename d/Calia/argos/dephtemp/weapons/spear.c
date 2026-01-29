/*  Spear of Priest of Dephonia
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima          12/14/94  Created
**
**/
inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void
create_weapon()
{
    set_name("spear");
    set_adj("silver-headed");
    set_short("silver-headed spear");
    set_long(break_string(
             "It is a tall spear with of a mohagany shaft and a long "+
             "silver spear head. Ravens are carved along its length.\n",70));
    set_hit(30);
    set_pen(30);
 
    set_wt(W_POLEARM);
    set_dt(W_IMPALE | W_SLASH);
 
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 2000);
}
