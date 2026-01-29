inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"

void
create_armour()
{
   ::create_armour();
   set_name("platemail");
   set_adj("obsidian");
   add_adj("rune-covered");
   set_short("rune-covered obsidian platemail");
   set_long("This armour has obviously been well cared for, it "+
  "has a very bright gleam, you can see your dark reflection in the "+
  "black crystal. THe runes that are etched into it glow faintly.\n");
   set_at(A_TORSO);
   set_ac(40);
   add_prop(OBJ_I_WEIGHT,5000);
   add_prop(OBJ_I_VOLUME,3000);
   add_prop(OBJ_I_VALUE,10000);
}
