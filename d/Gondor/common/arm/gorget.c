/*  Armour coded by Arren, November 93 */

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name("gorget");
    set_pname("gorget");
    set_adj("iron");
    add_adj("orc");
    set_short("iron gorget");
    set_long(BSN("A neck protection, typically worn by orcs fearful of "+
    "dwarves hewing with axes."));

    set_default_armour(9, A_NECK, ({ 0, 0, 0 }), 0);

    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 400); 
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(9)+random(50)-25);
}
