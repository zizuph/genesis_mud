inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include <macros.h>
#include "/d/Gondor/rohan/isengard/defs.h"

create_armour() {
  set_name(({"helm","iron helm","helmet","iron helmet"}));
  set_short("iron helm");
  set_pshort("iron helms");
  set_long("This iron helm is the standard helm for lesser Orcs.\n"+
    "On the front you see the rune S, wrought of some white metal.\n");
  set_default_armour(8,A_HEAD,({ -2, 1, 0}),0);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(8,A_HEAD));
  add_prop(OBJ_I_VOLUME, 380);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(8)+random(10)-20);
  add_prop(ISEN_I_ARMOUR, 1);
}

query_recover() { return MASTER+":"+query_arm_recover(); }
init_recover(arg) { init_arm_recover(arg); }
