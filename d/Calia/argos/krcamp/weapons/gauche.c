/*  Kretan gauche
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
    set_name("gauche");
    set_adj(({"kretan","orichalcum"}));
    set_short("tempered orichalcum gauche");
    set_long("It is a large dagger with a downward curved crossguard, "+
             "commonly used with a sword. A seven-headed hydra is "+
             "set in an inescutcheon on the middle of the crossguard.\n");
    set_hit(15); set_pen(15);
    set_hands(W_NONE);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE | W_SLASH);
}
