inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

create_armour() {
  set_name("leather armour");
  add_name("armour");
  set_pname("armours");
  set_adj("leather");
  set_adj("studded");
  set_short("studded leather armour");
  set_pshort("studded leather armours");
  set_long("The studded leather armour is made of closely set metal\n"+
    "studs embedded in hard leather.\n");
  set_default_armour(15,A_BODY,0,0);
  add_prop(OBJ_I_WEIGHT,2300);
  add_prop(OBJ_I_VOLUME,600);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(15)+random(50)-25);
}

