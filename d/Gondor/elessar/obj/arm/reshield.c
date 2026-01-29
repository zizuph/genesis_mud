/* Shield of the Mordor Uruk-hais */
#include "/sys/stdproperties.h"
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

create_armour()
{
  set_name("shield");
  add_name("Mordor_Shield");
  set_short("iron shield");
  set_pshort("iron shields");
  set_adj("normal");
  set_adj("iron");
  set_long("This is a normal iron shield. On the front is a crest; a small red\n"+
    "lidless eye in the centre of a black field.\n");
  set_default_armour(8,A_SHIELD,({ -2, 1, 0}),0);
  add_prop(OBJ_I_WEIGHT, 3000);
  add_prop(OBJ_I_VOLUME, 880);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(8)+random(10)-20);
}

query_recover() { return MASTER+":"+query_arm_recover(); }
init_recover(arg) { init_arm_recover(arg); }
