/* Shield of the Rohirrim */
#include "/sys/stdproperties.h"
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include <macros.h>

create_armour()
{
  set_name("shield");
  set_short("crude and heavy iron shield");
  set_pshort("iron shields");
  set_adj("heavy");
  set_adj("iron");
  set_long(break_string("This is a crude iron shield. Actually it is more a piece of iron hammered into a somewhat circular shape, with two handles added to it. But it will probably serve its purpose.\n",75));
  set_default_armour(30,A_SHIELD,({ -5,-5,10}),0);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(30,A_SHIELD)+500+random(500));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(30)+200-random(500));
}
