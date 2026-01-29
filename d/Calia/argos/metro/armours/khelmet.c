/*
** Helmet of a kretan warrior
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
#include "defs.h"
 
void create_armour() {
    set_name("helmet");
    set_adj(({"charred","orichalcum","kretan"}));
    set_short("charred orichalcum helmet");
    set_long("It is a helmet made of orichalcum, charred black. "+
             "It is worn by the warriors of the rebel army of Kretos.\n");
    set_ac(15);
    set_at(A_HEAD);
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 2000);
}
