/*
Made by korat
August 14. 1996
*/

inherit "/d/Kalad/std/weapon.c";
#include "/d/Kalad/defs.h"

create_weapon()
{
   ::create_weapon();
   set_dt(W_SLASH | W_IMPALE);
   set_hands(W_ANYH);
   set_name("battleaxe");
   set_adj("large");
   add_adj("black");
   set_hit(23);
   set_pen(27);
   set_wt(W_AXE);
   add_prop(OBJ_I_VALUE, 900);
   add_prop(OBJ_I_WEIGHT, 7000);
   add_prop(OBJ_I_VOLUME, 5000);
   
   set_long("This is a dangerous weapon "+
      "in the correct hands. Large runes are roughly cut into "+
      "the shaft by the former owner, for protection and branding "+
      "it as belonging to him or her.\n");
   add_item("runes","They are too hard to read, being "+
      "cut straight into the handle with some sharp object.\n");
}
