/*  Argosian stilleto
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
    set_name("stilleto");
    set_adj(({"argosian","orichalcum","sharp"}));
    set_short("orichalcum stilleto");
    set_long("It is a sharp stilleto made of orichalcum. It has a long "+
             "thin blade and a small blue stone on the hilt.\n");
    set_hit(12); set_pen(16);
    set_hands(W_NONE);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE | W_SLASH);
}
