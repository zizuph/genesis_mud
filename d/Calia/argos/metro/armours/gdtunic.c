/*  Tunic worn by Argosian guards
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/30/95  Created
**
**/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void
create_armour()
{
    set_name("tunic");
    set_adj(({"white","blue-trimmed","argosian"}));
    set_short("white blue-trimmed tunic");
    set_long("It is a short tunic made of thick wool trimmed with "+
             "blue. It is worn by members of the Argosian military.\n");
    set_ac(1);
    set_at(A_BODY);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 1000);
}
