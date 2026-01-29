/*  Axe of an Argosian imperial guard
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
    set_name("waraxe");
    add_name("axe");
    set_adj(({"argosian","silver","tempered","war"}));
    set_short("silver tempered waraxe");
    set_long(
       "It is a broad waraxe cast of tempered orichalcum and enameled "+
       "silver. An escutcheon on its hammer end bears the emblem of a "+
       "winged horse.\n");
    set_hit(27); set_pen(37);
    set_dt(W_SLASH | W_BLUDGEON);
    set_wt(W_AXE);
}
