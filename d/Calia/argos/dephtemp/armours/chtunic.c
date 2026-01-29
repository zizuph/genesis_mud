/*  The small tunic of a child
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/1/95   Created
**
**/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void
create_armour()
{
    set_name("tunic");
    set_adj("small");
    set_short("small tunic");
    set_long(
       "It is a small white wool tunic for a child.\n");
 
    set_ac(1);
    set_at(A_BODY);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 300);
}
