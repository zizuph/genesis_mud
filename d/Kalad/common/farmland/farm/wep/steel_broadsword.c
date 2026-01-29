/*
 * /d/Kalad/common/noble/wep/s_bsword.c
 * Purpose    : A steel broadsword.
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

   set_name("broadsword");
   add_name("sword");
   set_adj("steel");
   set_short("steel broadsword");
   set_long("This is a sharp looking broadsword made of very fine "+
     "quality steel. You could proably slash someone to shreads with "+
     "this quite easily.\n");

   set_hit(28);
   set_pen(28);
   set_wt(W_SWORD);
   set_dt(W_SLASH);

   add_prop(OBJ_I_WEIGHT, 2900);
   add_prop(OBJ_I_VOLUME, 1320);
   add_prop(OBJ_I_VALUE, 1100);
}

