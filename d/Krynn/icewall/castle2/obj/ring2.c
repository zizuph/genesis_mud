inherit "/std/armour";
inherit "/lib/keep";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

#define ARMOUR_CLASS 1

void
create_armour()
{
    set_name("ring");
   
    set_adj("simple");
    add_adj("silver");
    set_short("simple silver ring");    
    set_long("This is a simple and unadorned silver band.\n");
   
    set_ac(ARMOUR_CLASS);
    set_at(A_ANY_FINGER);
   
    add_prop(OBJ_I_WEIGHT, 80);
    add_prop(OBJ_I_VOLUME, 60);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(ARMOUR_CLASS) + random(500));
}

