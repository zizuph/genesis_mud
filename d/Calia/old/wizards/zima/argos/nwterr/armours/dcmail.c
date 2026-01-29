/*
** Mail of a Deuterian Commander
**
** HISTORY
** Date       Action
** ---------- -----------------------------------
** 8/24/93    Created
** 8/3/95     metal changed to orichalcum, "historically argosian" metal
*/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void create_armour() {
    set_name(({"mail","chainmail"}));
    set_adj(({"gold-trimmed","orichalcum","argosian"}));
    set_short("gold-trimmed orichalcum mail");
    set_long("It is a suit of mail made of orichalcum, a fiery red " +
             "alloy forged in Argos. It is trimmed with gold and cast "+
             "with a winged horse on the breast.\n");
    set_ac(22);
    set_at(A_BODY);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 5300);
    add_prop(OBJ_I_VOLUME, 3300);
}
