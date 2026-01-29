inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/kalaman/local.h"



void
create_armour()
{
    set_name("helmet");
    set_ac(20);
    set_at(A_HEAD);
    set_am( ({ -5, 0, 5 }) );
    set_adj("winged");
    add_adj("eagle-winged");
    set_short("eagle-winged helmet");
    set_long("This is a steel helmet that is adorned with eagle "+
      "wings on both sides, crafted out of silver.\n");
    add_prop(OBJ_I_VOLUME, 150);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(9, A_HEAD));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(9));
    add_prop(KALAMAN_NOBUY,1);
}


