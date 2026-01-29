/*
 * /d/Kalad/common/noble/wep/h_shovel.c
 * Purpose    : A simple shovel.
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

   set_name("hand-shovel");
   add_name("shovel");
   set_short("hand-shovel");
   set_long("This is a small hand shovel used for gardening by "+
      "those with a green thumb in these parts.\n");

   set_hit(8);
   set_pen(8); 
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);

   add_prop(OBJ_I_WEIGHT, 2000);
   add_prop(OBJ_I_VOLUME, 600);
}

