/*
Made by korat
August 14. 1996
*/

inherit "/d/Kalad/std/weapon.c";
#include "/d/Kalad/defs.h"

create_weapon()
{
   ::create_weapon();
   set_name("warhammer");
   set_adj("heavy");
   add_adj("two-handed");
   set_wt(W_CLUB);
   set_hands(W_BOTH);
   set_dt(W_BLUDGEON);
   set_hit(20);
   set_pen(29);
   add_prop(OBJ_I_VALUE, 700);
   add_prop(OBJ_I_WEIGHT, 9000);
   add_prop(OBJ_I_VOLUME, 9000);
   set_long("This is a dangerous weapon "+
      "in the correct hands. Large runes are roughly cut into "+
      "the shaft by the former owner, for protection and branding "+
      "it as belonging to him or her.\n");
   add_item("runes","They are too hard to read, being "+
      "cut straight into the handle with some sharp object.\n");
}
