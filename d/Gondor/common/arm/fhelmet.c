/* Helmet on ground */
inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include <macros.h>

create_armour() {
  set_name("helmet");
  set_pname("helmets");
  set_adj("iron");
  set_short("iron helmet");
  set_pshort("iron helmets");
  set_long("This is an very heavy helmet. It must be made of iron.\n");
  set_default_armour(8,A_HEAD,({ 0, 0, 0 }),0);
  add_prop(OBJ_I_WEIGHT,3200);
  add_prop(OBJ_I_VOLUME,750);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(8)+random(10)-5);
 }
