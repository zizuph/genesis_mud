inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

create_armour() {
  set_name(({"helm","steel helm","helmet","steel helmet"}));
  set_pname("helms");
  add_pname("helmets");
  set_short("light steel helm");
  set_pshort("light steel helms");
  set_adj("rohirrim");
  set_adj("light");
  set_adj("steel");
  set_long("The helm is made of light steel, with a long nose-guard in front.\n"+
    "From the top of the helm as a crest flows a white horse-tail.\n");
  set_default_armour(9,A_HEAD,({ -1, 1, 0}),0);
  add_prop(OBJ_I_WEIGHT, 3300);
  add_prop(OBJ_I_VOLUME, 560);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(9)+random(10)-20);
}
