/*  Standard (flag) carried by Ensigns
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           7/15/96  Created
**
**/
inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void create_weapon() {
    set_name("pole");
    add_name(({"flag","standard","banner","spear"}));
    set_adj(({"Kretan","long","kretan","black-shafted","black"}));
    set_short("standard-bearing pole");
    set_long(
       "It is a long pole with a sharp steel spear-head set on a black "+
       "orichalcum shaft. It bears a standard or flag, made of black "+
       "silk and embroidered with a seven-headed hydra in red thread.\n");
    set_hit(12); set_pen(10);
    set_dt(W_IMPALE | W_SLASH);
    set_wt(W_POLEARM);
}
