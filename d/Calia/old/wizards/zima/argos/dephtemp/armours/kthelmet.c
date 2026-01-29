/*
** Helmet of a Kretan Triterian Commander
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
#include "defs.h"
 
void create_armour() {
    set_name("helmet");
    set_adj(({"silver-trimmed","charred","orichalcum","kretan"}));
    set_short("silver-trimmed charred orichalcum helmet");
    set_long("It is a helmet made of orichalcum, charred black and "+
             "trimmed with silver. It is worn by the officers of the "+
             "rebel army of Kretos.\n");
    set_ac(18);
    set_at(A_HEAD);
    add_prop(OBJ_I_WEIGHT, 2100);
    add_prop(OBJ_I_VOLUME, 2100);
}
