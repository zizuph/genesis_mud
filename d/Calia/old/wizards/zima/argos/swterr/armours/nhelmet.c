/* helmet of a kretan warrio,   level 40
 
    coder(s):   Zima   10/22/93
 
 
*/
 
inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void
create_armour()
{
    set_name(({"helmet","kretan helmet","steel helmet"}));
    set_adj("steel");
    set_short("kretan helmet");
    set_long("A steel helmet worn by the soldiers of the Kretan army.\n");
    set_ac(15);
    set_at(A_HEAD);
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 2000);
}
