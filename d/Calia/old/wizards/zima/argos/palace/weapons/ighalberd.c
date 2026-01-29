/*  Halberd of an imperial palace guard
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           8/25/96  Created
**
**/
inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void create_weapon() {
    set_name("halberd");
    set_adj(({"argosian","silver","tempered"}));
    set_short("tempered argosian halberd");
    set_long(
       "It is a long halberd with a strong staff, topped with large axe "+
       "blade and sharp spearhead, with a vicious hook on the end. It is "+
       "made of silver-enameled orichalcum with a hilt bearing an escutcheon "+
       "cast with a winged horse.\n");
    set_hit(29); set_pen(39);
    set_hands(W_BOTH);
    set_dt(W_IMPALE | W_BLUDGEON);
    set_wt(W_POLEARM);
}
