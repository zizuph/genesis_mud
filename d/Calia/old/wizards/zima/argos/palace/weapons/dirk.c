/*  Argosian dirk
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           5/25/96  Created
**
**/
inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void create_weapon() {
    set_name("dirk");
    set_adj(({"polished","argosian","orichalcum"}));
    set_short("polished orichalcum dirk");
    set_long("It is a heavy knife with two arching spikes at the base of "+
             "its sharpe blade. A circular inset on the hilt bears a "+
             "rampant winged horse.\n");
    set_hit(16); set_pen(15);
    set_hands(W_NONE);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE | W_SLASH);
}
