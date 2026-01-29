/*  Robe worn by Master of the Thespian Guild
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           8/25/95  Created
**
**/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void create_armour() {
    set_name("robe");
    set_adj(({"long","white"}));
    set_short("long white robe");
    set_long("It is a long white robe with a wide red strip embroidered "+
             "with gold trim that runs from "+
             "the neck to the hem. Actor's masks are embroidered over "+
             "both breasts.\n");
    set_ac(1);
    set_at(TS_ROBE);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 450);
    add_prop(OBJ_I_VOLUME,  950);
}
