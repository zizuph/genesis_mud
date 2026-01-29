/*  Kretan stiletto
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/25/96  Created
**
**/
inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void create_weapon() {
    set_name("stiletto");
    set_adj(({"kretan","orichalcum","sharp"}));
    set_short("orichalcum stiletto");
    set_long("It is a sharp stiletto made of orichalcum. It has a long "+
             "thin blade and a small red stone on the hilt.\n");
    set_hit(12); set_pen(16);
    set_hands(W_NONE);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE | W_SLASH);
}
