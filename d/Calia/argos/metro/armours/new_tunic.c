/*  New Tunic made by seamstress in rooms/woolwrk
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           8/25/95  Created
**
**/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
#include "defs.h"
 
void create_armour() {
    set_name("tunic");
    add_name(ARGOS_NEW_TUNIC);
    set_adj(({"new","white"}));
    set_short("new white tunic");
    set_long("It is a long white tunic commonly worn by the citizens "+
             "of Argos. It looks as if it has just been woven.\n");
    set_ac(1);
    set_at(A_BODY);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 700);
    add_prop(OBJ_I_VOLUME, 1500);
}
