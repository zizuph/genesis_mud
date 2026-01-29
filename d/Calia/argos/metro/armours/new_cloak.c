/*  New cloak made by seamstress in rooms/woolwrk
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           8/25/95  Created
**
**/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
#include "defs.h"
 
#define colors ({"blue","red","yellow","brown","green","purple"})
 
void create_armour() {
    string color=colors[(random(sizeof(colors)))];
    set_name("cloak");
    add_name(ARGOS_NEW_CLOAK);
    set_adj(({"new",color}));
    set_short("new "+color+" cloak");
    set_long("It is a long "+color+" cloak which drapes over one shoulder "+
             "and hangs down below the knees. It looks like it was just "+
             "woven.\n");
    set_ac(1);
    set_at(TS_ROBE);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 1000);
}
