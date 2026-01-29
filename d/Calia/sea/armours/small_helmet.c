/*     
        Black helmet for the small water-krougs

        Coded by Digit and Maniac
*/

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_armour()
{
    set_name("helmet");
    set_adj("black");
    set_short("black helmet");
    set_long("A black helmet.\n");
    set_ac(11);
    set_at(A_HEAD);
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 2000);
}

