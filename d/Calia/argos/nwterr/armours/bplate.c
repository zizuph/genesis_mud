/*  Breastplate worn by the Priests and Priestesses of Dephonia
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           2/03/94  Created
**
**/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void
create_armour()
{
    set_name(({"jeweled breastplate","breastplate"}));
    set_adj("silver");
    set_adj("jeweled");
    set_short("jeweled breastplate");
    set_long(break_string(
       "A diamond-shaped breastplate made of polished silver. " +
       "It is cast with a crested raven and bordered with red rubies.\n",70));
    set_ac(10);
    set_at(A_ROBE);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VOLUME, 1500);
}
