inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

create_armour() {
  set_name("helm");
  set_short("iron helm");
  set_pshort("iron helms");
  set_adj("iron");
  set_adj("dented");
  set_long("This iron helm with tabard was wrought by orcs, and on the front you\n"+
    "see a strange symbol: A red, lidless eye on a black background.\n");
  set_default_armour(19,A_HEAD,({ -1, 1, 0}),0);
  add_prop(OBJ_I_WEIGHT, 1900);
  add_prop(OBJ_I_VOLUME, 380);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(19)+random(10)-20);
}

query_recover() { return MASTER+":"+query_arm_recover(); }
init_recover(arg) { init_arm_recover(arg); }
