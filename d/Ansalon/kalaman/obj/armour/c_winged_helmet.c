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
    set_pname("helmets");
    set_ac(26);
    set_at(A_HEAD);
    set_am( ({ -5, 0, 5 }) );
    set_adj("winged");
    add_adj("golden");
    add_adj("gold");
    add_adj("eagle-winged");
    add_adj("eagle winged");
    set_short("golden eagle-winged helmet");
    set_pshort("golden eagle-winged helmet");
    set_long("It is a steel helmet that is adorned with eagle "+
      "wings on both sides, crafted out of gold. The wings are "+
      "spread as if ready to take flight. The inside of the helmet "+
      "is lined with soft leather to give comfort to the wearer.\n");
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(12, A_HEAD));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(12));
    add_prop(KALAMAN_NOBUY, 1);
}



