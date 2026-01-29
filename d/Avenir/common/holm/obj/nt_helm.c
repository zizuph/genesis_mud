inherit "/std/armour";
#include <formulas.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("helm");
    set_short("bright helm");
    set_long("A helm so highly polished and smooth that it reflects " +
           "any light source. Small steel plates have been riveted together " +
           "to form this helm. It is of very good make and the "+
           "steel plates have obviously been chosen with great " +
           "care.\n");
 
    set_adj("bright");
    set_ac(30);
    set_at(A_HEAD);
    /* IMPALE, SLASH, BLUDGEON */
    set_am(({1,1,-2}));
    set_af(0);
  
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20) +random (20) - 10);
}

