/*
 * /d/Kalad/common/noble/wep/g_halb.c
 * Purpose    : 
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

   set_name("halberd");
   set_adj("great");
   set_short("great halberd");
   set_long("Though this is certainly one of the largest halberds "+
      "you have ever seen, it has been crafted with such keen and "+
      "efficient balance that it maneuvers with simple ease. "+
      "This is truly the product of a master, and a weapon to be "+
      "treasured.\n");

   set_hit(28);
   set_pen(39); 
   set_hands(W_BOTH);
   set_wt(W_POLEARM);
   set_dt(W_SLASH | W_IMPALE);

   add_prop(OBJ_I_WEIGHT, 6730);
   add_prop(OBJ_I_VOLUME, 5000);
   add_prop(OBJ_I_VALUE, 2000);
}

