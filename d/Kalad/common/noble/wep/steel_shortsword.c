/*
 * /d/Kalad/common/noble/wep/s_ssword.c
 * Purpose    : Steel shortsword.
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

   set_name("shortsword");
   add_name("sword");
   set_adj("steel");
   add_adj("short");
   set_short("steel shortsword");
   set_long("This is a short bladed sword made of very fine steel. "+
      "The edge gleams in the light.\n");

   set_hit(21);
   set_pen(17); 
   set_wt(W_SWORD);
   set_dt(W_SLASH | W_IMPALE);

   add_prop(OBJ_I_WEIGHT, 1265);
   add_prop(OBJ_I_VOLUME, 700);
   add_prop(OBJ_I_VALUE, 300);
}

