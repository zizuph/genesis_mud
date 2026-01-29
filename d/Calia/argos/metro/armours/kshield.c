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
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
 
void create_armour() {
    set_name("shield");
    set_adj(({"charred","orichalcum","kretan"}));
    set_short("charred orichalcum shield");
    set_long("It is a shield made of orichalcum, charred black, emblazoned "+
             "with a seven-headed Hydra. It is worn by warriors in the rebel "+
             "army of Kretos.\n");
    set_ac(15);
    set_at(A_SHIELD);
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VOLUME, 1500);
}
