inherit "/std/armour";

#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/formulas.h"
#include "/sys/wa_types.h"

create_armour() {

  set_name("boots");
  set_short("pair of soft boots");
  set_adj("soft");
  set_long("A pair of soft leather boots.\n");
  set_default_armour(
    5,
    A_FEET,
    0,
    0
  );
  add_prop(OBJ_I_WEIGHT, 300);
  add_prop(OBJ_I_VOLUME, 400);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5));
}


string query_recover()
{
    return MASTER + ":" + query_arm_recover();
}


void init_recover(string arg)
{
    init_arm_recover(arg);
}
