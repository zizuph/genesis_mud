/*  The short white tunic of an Argosian Slave
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
    set_adj("white");
    set_adj("short");
    set_short("short white tunic");
    set_long(
       "It is a short white tunic worn by the slaves of Argos.\n");
 
    set_ac(1);
    set_at(A_BODY);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 700);
}
