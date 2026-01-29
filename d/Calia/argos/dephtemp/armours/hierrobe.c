/*  Robe of the Hierophant, the one she is wearing
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
    set_name("robe");
    set_adj("red");
    set_adj("jeweled");
    set_adj("silk");
    set_short("jeweled robe");
    set_long(break_string(
       "It is a long red robe made of fine silk. There is a raven "+
       "embroidered on the front in black thread, encircled by "+
       "twelve sparkling rubies.\n",70));
 
    set_ac(1);
    set_at(A_BODY);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE,  320); /* she is hard to kill, make it worth it */
}
