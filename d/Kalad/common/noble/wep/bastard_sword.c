/*
 * /d/Kalad/common/noble/wep/b_sword.c
 * Purpose    : A nice, two handed sword.
 * Located    : 
 * Created By : Sarr
 * Modified By: Sarr
 * First Modif: 12.Feb.97
 */

inherit "/d/Kalad/std/weapon";

#include "/d/Kalad/defs.h"

void
create_weapon()
{
   ::create_weapon();

   set_name("sword");
   set_adj("serrated");
   add_adj("bastard");
   set_short("serrated bastard sword");
   set_long("This is one big, nasty looking sword. It has a long "+
      "hilt and an ornate crosspiece. A very sharp, strong, jagged "+
      "edged blade juts out of the hilt. You can see your face "+
      "reflected on its polished edge.\n");

   set_hit(33);
   set_pen(28);
   set_hands(W_BOTH);
   set_wt(W_SWORD);
   set_dt(W_SLASH | W_IMPALE);

   add_prop(OBJ_I_WEIGHT, 3640);
   add_prop(OBJ_I_VOLUME, 2000);
}

