inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/formulas.h"

create_armour() {
  set_name(({"helm","mithril helm","helmet","mithril helmet"}));
  set_short("winged mithril helm");
  set_pshort("winged mithril helms");
  set_adj("mithril");
  set_adj("winged");
  set_adj("high-crowned");
  set_long("This is a helm of strange shape: It is high-crowned, with long\n"+
    "cheek-guards close-fitting to the face of the wearer. Above the\n"+
    "cheek-guards white wings of sea-birds are set. The helm gleams with\n"+
    "a flame of silver, as it is indeed wrought of mithril.\n");
  set_default_armour(10,A_HEAD,({ 0, 1, 0}),0);
  add_prop(OBJ_I_WEIGHT, 2900);
  add_prop(OBJ_I_VOLUME, 680);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10)+random(10)-20);
}
