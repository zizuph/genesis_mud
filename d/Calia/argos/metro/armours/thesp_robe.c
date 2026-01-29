/*  Robe worn by members of the Thespian Guild
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
    set_adj(({"long","red"}));
    set_short("long red robe");
    set_long("It is a long red robe with a wide black strip from "+
             "the neck to the hem. Actor's masks are embroidered over "+
             "both breasts.\n");
    set_ac(1);
    set_at(TS_ROBE);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME,  900);
}
