inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

create_armour() {
  set_name(({"surcoat","armour"}));
  set_short("black surcoat");
  set_pshort("black surcoats");
  set_adj("black");
  set_adj("dunedain");
  set_long("The black surcoat is of the kind that is only worn by the Guards of\n"+
    "the Citadel in Minas Tirith. On the front is embroidered in white a\n"+
    "tree blossoming like snow beneath a silver crown and many-pointed stars.\n");
  set_default_armour(5,A_BODY,({ -2, 3, -3}),0);
  add_prop(OBJ_I_WEIGHT, 3200);
  add_prop(OBJ_I_VOLUME, 1000);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5)+random(20)-10);
}
