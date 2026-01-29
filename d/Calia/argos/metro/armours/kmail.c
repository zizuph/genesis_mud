/*
** Shield of a kretan warrior
**
** HISTORY
** Date       Action
** ---------- -----------------------------------
** 8/24/93    Created
** 8/5/95     Changed metal to orichalcum, historically "argosian"
**            charred metal indicates kretan rebel material
*/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void create_armour() {
    set_name(({"mail","chainmail"}));
    set_adj(({"charred","orichalcum","kretan"}));
    set_short("charred orichalcum mail");
    set_long("It is a suit of mail made of orichalcum, charred black, "+
             "cast with a seven-headed Hydra on the breast. It is worn by "+
             "the warriors of the rebel army of Kretos.\n");
    set_ac(15);
    set_at(A_BODY);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 3000);
}
