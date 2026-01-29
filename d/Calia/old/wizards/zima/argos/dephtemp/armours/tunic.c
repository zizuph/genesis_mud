/*  Tunic worn by the priests and priestesses of Dephonia
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/12/94  Created
**
**/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void
create_armour()
{
    set_name(({"raven-crested tunic","black tunic","tunic"}));
    set_adj("black");
    set_adj("raven-crested");
    set_short("raven-crested tunic");
    set_long("A black tunic embroidered with a raven crest.\n");
    set_ac(1);
    set_at(A_BODY);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 1000);
}
