inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

create_armour()
{
   ::create_armour();
   set_name("gauntlets");
   set_short("pair of obsidian-plated leather gloves");
   set_adj("obsidian-plated");
   add_adj("leather");
   set_long("These are a pair of black leather gloves, which have "+
   "magically shaped, interlocking plated of obsidian on top of them.\n");
   set_ac(15);
   set_at(A_HANDS);
   add_prop(OBJ_I_VALUE, 150);
   add_prop(OBJ_I_VOLUME, 300);
   add_prop(OBJ_I_WEIGHT, 400);
}
