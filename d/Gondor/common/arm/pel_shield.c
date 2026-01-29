/* Shield of the Pelargir soldiers */
#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

create_armour()
{
  set_name("shield");
  add_name("Pelargir_Shield");
  set_short("steel shield");
  set_pshort("steel shields");
  set_adj("steel");
  set_adj("blue");
  set_long("This is a blue steel shield, and on the front is a crest; three white\n"+
    "ships, surmounted by a silver crown.\n");
  set_default_armour(21,A_SHIELD,0,0);
  add_prop(OBJ_I_WEIGHT, 3000);
  add_prop(OBJ_I_VOLUME, 880);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(21)+random(10)-20);
  add_prop(GONDOR_M_TIRITH_NO_SELL,1);
}
