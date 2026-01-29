inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include <macros.h>

create_armour() {
  set_name("leather armour");
  add_name("armour");
  set_adj("leather");
  set_adj("studded");
  set_adj("dirty");
  set_short("dirty studded leather armour");
  set_pshort("studded leather armours");
  set_long(break_string("The studded leather armour is made of closely set metal "+
    "studs embedded in leather armour. It is very dirty, covered with mud, " + 
    "and it smells like a corpse that has been dead for a week.\n",60));
  set_default_armour(14,A_BODY, (({0, 1,-1})),0);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(14)+random(100)-50);
 }
