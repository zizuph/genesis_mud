/*  Kretan dagger
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
    set_name("dagger");
    set_adj(({"sharp","orichalcum","kretan"}));
    set_short("sharp orichalcum dagger");
    set_long("It is a dagger with a sharp blade made of orichalcum and "+
             "a hilt wrapped with black leather.\n");
    set_hit(14); set_pen(14);
    set_hands(W_NONE);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE | W_SLASH);
}
