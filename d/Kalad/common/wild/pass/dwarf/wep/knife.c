/*
Made by korat
August 14. 1996
*/

inherit "/d/Kalad/std/weapon.c";
#include "/d/Kalad/defs.h"

create_weapon()
{
   ::create_weapon();
   set_dt(W_IMPALE);
   set_hands(W_ANYH);
   set_name("dagger");
   set_adj("long");
   add_adj("sharp");
   set_wt(W_KNIFE);
   set_hit(12);
   set_pen(10);
   add_prop(OBJ_I_WEIGHT,1000);
   add_prop(OBJ_I_VOLUME,1000);
   add_prop(OBJ_I_VALUE, 300);
   set_long("This is a dangerous weapon "+
      "in the correct hands. Large runes are roughly cut into "+
      "the shaft by the former owner, for protection and branding "+
      "it as belonging to him or her.\n");
   add_item("runes","They are too hard to read, being "+
      "cut straight into the handle with some sharp object.\n");
}
