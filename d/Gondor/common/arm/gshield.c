/* Shield of the Gondorian soldiers */
/* Slight increase in AC to strengthen the NPCs that use them, Eowul, 2009 */

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

create_armour()
{
  set_name("shield");
  add_name("Gondor_Shield");
  set_pname("shields");
  set_short("steel shield");
  set_pshort("steel shields");
  set_adj("steel");
  set_adj("black");
  set_long("This is a black steel shield, and on the front is a crest; a white\n"+
    "tree, surrounded by seven stars.\n");
  set_default_armour(27,A_SHIELD,0,0);
  add_prop(OBJ_I_WEIGHT, 3000);
  add_prop(OBJ_I_VOLUME, 880);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(27)+random(10)-20);
  add_prop(GONDOR_M_TIRITH_NO_SELL,1);
}
