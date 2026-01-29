/*  Axe of a Kretan Warrior
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
    set_name("battleaxe");
    add_name("axe");
    set_adj(({"kretan","orichalcum","polished","battle"}));
    set_short("polished orichalcum battleaxe");
    set_long(
       "It is a polished battleaxe with a broad head and sharp blade. The "+
       "head is cast with a circular inset bearing the emblem of a "+
       "seven-headed hydra.\n");
    set_hit(24); set_pen(31);
    set_dt(W_SLASH | W_BLUDGEON);
    set_wt(W_AXE);
}
