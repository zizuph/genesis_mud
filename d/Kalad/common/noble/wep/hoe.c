/*
 * /d/Kalad/common/noble/wep/hoe.c
 * Purpose    : A simple garden hoe.
 * Located    : 
 * Created By : Sarr
 * Modified By: Rico
 * First Modif: 15.Feb.97
 */

inherit "/d/Kalad/std/weapon";

#include "/d/Kalad/defs.h"

void
create_weapon()
{
   ::create_weapon();

   set_name("hoe");
   add_name("garden hoe");
   set_adj("garden");
   set_short("garden hoe");
   set_long("This is a simple garden hoe. One of those must "+
      "have tools for gardeners.\n");

   set_hit(8);
   set_pen(8); 
   set_hands(W_BOTH);
   set_wt(W_POLEARM);
   set_dt(W_BLUDGEON);

   add_prop(OBJ_I_WEIGHT, 2100);
   add_prop(OBJ_I_VOLUME, 600);
}

