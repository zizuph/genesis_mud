/*  Tunic worn by Argosian Nobles
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           13/5/95  Created
**
**/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void create_armour() {
    set_name("tunic");
    set_adj(({"white","long"}));
    set_short("long white tunic");
    set_long("It is a long white tunic embroidered with gold thread "+
             "around the cuffs and hem.\n");
    set_ac(1);
    set_at(A_BODY);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 700);
    add_prop(OBJ_I_VOLUME, 1500);
}
