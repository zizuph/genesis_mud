/*  Halberd of an imperial guard
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/30/96  Created
**
**/
inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void create_weapon() {
    set_name("halberd");
    set_adj(({"kretan","black","tempered"}));
    set_short("black tempered halberd");
    set_long(
       "It is a long halberd with a strong staff, topped with large axe "+
       "blade and sharp spearhead, with a vicious hook on the end. It is "+
       "made of black-enameled orichalcum with a hilt bearing an escutcheon "+
       "cast with a seven-headed hydra.\n");
    set_hit(29); set_pen(39);
    set_hands(W_BOTH);
    set_dt(W_IMPALE | W_BLUDGEON);
    set_wt(W_POLEARM);
}
