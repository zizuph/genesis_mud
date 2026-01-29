/*  Axe of an imperial guard
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
    set_name("waraxe");
    add_name("axe");
    set_adj(({"kretan","black","tempered","war"}));
    set_short("black tempered waraxe");
    set_long(
       "It is a broad waraxe cast of tempered orichalcum and enameled "+
       "black. An escutcheon on its hammer end bears the emblem of a "+
       "seven-headed hydra.\n");
    set_hit(27); set_pen(37);
    set_dt(W_SLASH | W_BLUDGEON);
    set_wt(W_AXE);
}
