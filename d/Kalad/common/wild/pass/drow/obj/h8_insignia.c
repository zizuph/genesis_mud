inherit "/std/object";
inherit "/lib/keep";
#include "/d/Kalad/defs.h"
/* by Antharanos */
void
create_object()
{
   ::create_object();
   set_name("insignia");
   set_adj("house");
   set_long("An insignia that bears the runes indicative of House Noquar, "+
      "the eighth house of the city of Undraeth.\n");
   add_prop(OBJ_I_WEIGHT,250);
   add_prop(OBJ_I_VOLUME,250);
}
void
init()
{
   ::init();
   AA(show,show);
}
int
show(string str)
{
   if(!str || str != "insignia")
      {
      NF("Show what?\n");
      return 0;
   }
   write("You proudly show the insignia of House Noquar.\n");
   say(QCTNAME(TP) + " proudly shows the insignia of House Noquar.\n");
   return 1;
}
