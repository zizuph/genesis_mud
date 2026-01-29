/*  Tunic worn by Argosian citizens
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/30/95  Created
**
**/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
#define colors ({"blue","red","yellow","brown","green","purple"})
 
void
create_armour()
{
    string color=colors[(random(sizeof(colors)))];
    set_name("cloak");
    set_adj(color);
    set_short(color+" cloak");
    set_long("It is a long "+color+" cloak which drapes over one shoulder "+
             "and hangs down below the knees. It is commonly worn in "+
             "Argos.\n");
    set_ac(1);
    set_at(TS_ROBE);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 1000);
}
