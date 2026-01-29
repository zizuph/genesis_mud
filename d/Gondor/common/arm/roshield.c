/* Shield of the Rohirrim */
#include "/sys/stdproperties.h"
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

create_armour()
{
  set_name("shield");
  add_name("Rohan_Shield");
  set_pname("shields");
  set_short("painted steel shield");
  set_pshort("painted steel shields");
  set_adj("rohirrim");
  set_adj("painted");
  set_adj("green");
  set_adj("round");
  set_adj("steel");
  set_long("This is a round shield of steel, painted green, with a white running\n"+
    "horse in the centre.\n");
  set_default_armour(20,A_SHIELD,({ -1, 1, 0}),0);
  add_prop(OBJ_I_WEIGHT, 2600);
  add_prop(OBJ_I_VOLUME, 800);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20)+random(10)-20);
}
