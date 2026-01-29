// This makes a pair of leather gloves. Cloned in l4/n23 and n15.
// Made by Boriska, Dec 1994

#include <stdproperties.h>
#include <wa_types.h>
#include <const.h>

inherit "/d/Avenir/inherit/cloth_arm";

void
create_armour()
{
  set_name ("glove");
  set_short ("leather glove");
  add_adj (({"leather","right"}));
  set_long (
    "A leather glove with the fingers' ends cut off to provide "+
    "both protection for your right hand and a better grip on "+
    "your weapon.\n");

  set_ac(5);
  set_at(A_R_HAND);
  
  add_prop (OBJ_I_WEIGHT, 70);
  add_prop (OBJ_I_VOLUME, 40);
  add_prop (OBJ_I_VALUE, 80);
}

