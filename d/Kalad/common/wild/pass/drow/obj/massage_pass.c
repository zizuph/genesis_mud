inherit "/std/object";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_object()
{
   ::create_object();
   set_name("pass");
   add_name("_massage_pass");
   set_adj("massage");
   set_long("This small obsidian pyramid allows any that bears it to "+
      "obtain a massage at the massage parlour of Undraeth.\n");
   add_prop(OBJ_I_WEIGHT,100);
   add_prop(OBJ_I_VOLUME,100);
}
