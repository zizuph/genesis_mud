/*
** Shield of an Argosian guard/soldier
**
** HISTORY
** Date       Action
** ---------- -----------------------------------
** 8/24/93    Created
** 8/5/95     Changed metal to orichalcum, historically "argosian"
*/
inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
 
void create_armour() {
    set_name("shield");
    set_adj(({"orichalcum","argosian"}));
    set_short("orichalcum shield");
    set_long("It is a shield made of orichalcum, a fiery red "+
             "alloy forged in Argos. It is emblazoned with a rampant "+
             "winged horse.\n");
    set_ac(15);
    set_at(A_SHIELD);
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VOLUME, 1500);
}
