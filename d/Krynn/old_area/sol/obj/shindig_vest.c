inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
   set_name("vest");
   set_ac(15);
   set_at(A_BODY);
   set_short("blue fur trimmed vest");
   add_adj(({"blue","fur"}));
   set_long("This is a bright blue vest, trimmed with dark "+
      "brown fur. It's very soft, and looks warm enough "+
      "for relatively cold climates, but not too hot for "+
      "warmer climates. It is quite small, probably worn "+
      "by a kender or gnome.\n");
   add_prop(OBJ_I_VOLUME, 4750);
   add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(15, A_BODY));
   add_prop(OBJ_I_VALUE, 400);
}

