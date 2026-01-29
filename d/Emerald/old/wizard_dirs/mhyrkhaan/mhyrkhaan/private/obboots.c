inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("boots");
   set_adj("obsidian");
   add_adj("shiny");
   set_short("a pair of shiny obsidian boots");
   set_long("These are a pair of obsidian boots, there are small runes etched "+
   "alone the ankle, the runes glow with a pale green light.\n");
   set_ac(25);
   set_at(A_FEET);
   add_prop(OBJ_I_VALUE, 240);
   add_prop(OBJ_I_VOLUME, 800);
   add_prop(OBJ_I_WEIGHT, 1500);
}
