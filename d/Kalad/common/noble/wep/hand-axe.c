/*
 * /d/Kalad/common/noble/wep/h_axe.c
 * Purpose    : A simple hand axe.
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

   set_name("hand-axe");
   add_name("axe");
   set_short("hand-axe");
   set_long("This is a small hand-axe made for chopping wood. "+
      "It wouldn't do you a whole lot of good in a fight.\n");
   set_hit(12);
   set_pen(13);
   set_wt(W_AXE);
   set_dt(W_SLASH);

   add_prop(OBJ_I_WEIGHT, 1050);
   add_prop(OBJ_I_VOLUME, 520);
}


