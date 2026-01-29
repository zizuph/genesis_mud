/* Ring worn as a replacement for the magic ring. */

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
   
    set_adj("thick");
    add_adj("gold");
    set_short("thick gold ring");    set_long("This is a thick ring of gold, with no visible ornaments.\n");
   
    set_ac(ARMOUR_CLASS);
    set_at(A_ANY_FINGER);
   
    add_prop(OBJ_I_WEIGHT, 120);
    add_prop(OBJ_I_VOLUME, 70);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(ARMOUR_CLASS) + random(500) + 600);
}

