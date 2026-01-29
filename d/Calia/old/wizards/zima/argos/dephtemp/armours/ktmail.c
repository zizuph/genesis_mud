/*
** Mail of a Kretan Triterian Commander
**
** HISTORY
** Date       Action
** ---------- -----------------------------------
** 11/12/94    Created
** 8/5/95     Changed metal to orichalcum, historically "argosian"
**            charred metal indicates kretan rebel material
*/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void create_armour() {
    set_name(({"mail","chainmail"}));
    set_adj(({"silver-trimmed","charred","orichalcum","kretan"}));
    set_short("silver-trimmed charred orichalcum mail");
    set_long("It is a suit of mail made of orichalcum, charred black "+
             "and trimmed with silver. It is cast with a seven-headed "+
             "Hydra on the breast and is worn by "+
             "the officers of the rebel army of Kretos.\n");
    set_ac(18);
    set_at(A_BODY);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 5200);
    add_prop(OBJ_I_VOLUME, 3200);
}
