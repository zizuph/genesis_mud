/*  Spear of an Argosian Guard
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
 
void create_weapon() {
    set_name("spear");
    set_adj(({"Argosian","tall"}));
    set_short("tall Argosian spear");
    set_long(
       "It is a tall spear with of a steel shaft and a long "+
       "silver spear head. A flat triangular plate beneath the "+
       "spear head bears the emblem of a winged horse.\n");
    set_hit(28); set_dt(W_IMPALE | W_SLASH);
    set_pen(33); set_wt(W_POLEARM);
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 2000);
}
