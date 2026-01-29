/*
** Helmet of a Deuterian Commander
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
#include "defs.h"
 
void create_armour() {
    set_name("helmet");
    set_adj(({"gold-trimmed","orichalcum","argosian"}));
    set_short("gold-trimmed orichalcum helmet");
    set_long("It is a gold-trimmed helmet made of orichalcum, a fiery red "+
             "alloy forged in Argos.\n");
    set_ac(22);
    set_at(A_HEAD);
    add_prop(OBJ_I_WEIGHT, 2200);
    add_prop(OBJ_I_VOLUME, 2200);
}
