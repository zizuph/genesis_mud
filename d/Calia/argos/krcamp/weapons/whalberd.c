/*  Halberd of a Kretan Warrior
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
    set_adj(({"kretan","orichalcum","polished"}));
    set_short("polished orichalcum halberd");
    set_long(
       "It is a polished halberd with a strong staff, topped with large axe "+
       "blade and sharp spearhead, with a vicious hook on the end. A "+
       "circular inset in the axe blade bears the emblem of a seven-headed "+
       "hydra.\n");
    set_hit(26); set_pen(39);
    set_hands(W_BOTH);
    set_dt(W_IMPALE | W_BLUDGEON);
    set_wt(W_POLEARM);
}
