 
/*  Staff of Priestesses of Dephonia
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           2/03/94  Created
**
**/
inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void
create_weapon()
{
    set_name("staff");
    set_adj("runed");
    set_adj("silver");
    set_short("runed silver staff");
    set_long(break_string(
             "A long staff of silver covered in ancient runes. A " +
             "raven is crafted on top, its upraised wings as sharp " +
             "as razors.\n",70));
    set_hit(30);
   set_pen(25);
 
    set_hands(W_BOTH);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE | W_SLASH);
 
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 2000);
}
