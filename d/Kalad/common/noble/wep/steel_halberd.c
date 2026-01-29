/*
 * /d/Kalad/common/noble/wep/s_halberd.c
 * Purpose    : A steel halberd.
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
   set_adj("steel");
   set_short("steel halberd");
   set_long("This vicious halberd is made of steel and looks very "+
      "sharp. The fine, polished wooden haft makes you grim with "+
      "anticipation. The blade is large, but surprisingly light.\n");

   set_hit(26);
   set_pen(39);
   set_hands(W_BOTH);
   set_wt(W_POLEARM);
   set_dt(W_SLASH | W_IMPALE);

   add_prop(OBJ_I_WEIGHT, 6825);
   add_prop(OBJ_I_VOLUME, 1520);
   add_prop(OBJ_I_VALUE, 1500);
}

