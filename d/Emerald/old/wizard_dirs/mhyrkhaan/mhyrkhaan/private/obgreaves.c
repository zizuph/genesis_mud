inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

create_armour()
{
   ::create_armour();
   set_name("greaves");
   set_short("a pair of glossy obsidian greaves");
   set_adj("obsidian");
   add_adj("glossy");
   set_long("This pair of graves is made from magically shaped interlocking "+
   "obsidian plates. There are small runes on the greaves that glow with "+
   "a pale green light.\n");
   set_ac(32);
   set_at(A_LEGS);
   add_prop(OBJ_I_LIGHT,1);
   add_prop(OBJ_I_VALUE, 650);
   add_prop(OBJ_I_VOLUME, 800);
   add_prop(OBJ_I_WEIGHT, 1000);
}
