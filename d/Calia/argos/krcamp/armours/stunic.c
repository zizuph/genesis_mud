/*  Tunic worn by kretan sentries
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/30/95  Created
**
**/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void create_armour() {
    set_name("tunic");
    set_adj(({"short","black","kretan"}));
    set_short("short black tunic");
    set_long("It is a short black tunic made of wool. Designed to be "+
             "worn in battle, it is embroidered with a seven-headed "+
             "hydra in red thread over the heart.\n");
    set_ac(10);
    set_at(A_ROBE);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 700);
    add_prop(OBJ_I_VOLUME, 600);
}
