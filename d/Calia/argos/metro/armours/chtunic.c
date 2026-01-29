/*  Tunic worn by Argosian children
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
    set_name("tunic");
    set_adj(({"white","short"}));
    set_short("short white tunic");
    set_long("It is a short white tunic commonly worn by the children "+
             "of Argos.\n");
    set_ac(1);
    set_at(A_BODY);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 350);
    add_prop(OBJ_I_VOLUME,  750);
}
