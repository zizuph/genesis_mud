/*
** Shield of a Kretan Triterian Commander
**
** HISTORY
** Date       Action
** ---------- -----------------------------------
** 11/12/94    Created
** 8/5/95     Changed metal to orichalcum, historically "argosian"
**            charred metal indicates kretan rebel material
*/
inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
 
void create_armour() {
    set_name("shield");
    set_adj(({"silver-trimmed","charred","orichalcum","kretan"}));
    set_short("silver-trimmed charred orichalcum shield");
    set_long("It is a shield made of orichalcum, charred black and trimmed "+
             "with silver. It is emblazoned with a seven-headed Hydra and "+
             "worn by officers in the rebel army of Kretos.\n");
    set_ac(18);
    set_at(A_SHIELD);
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 2700);
    add_prop(OBJ_I_VOLUME, 1600);
}
