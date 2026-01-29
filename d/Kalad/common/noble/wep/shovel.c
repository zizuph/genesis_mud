/*
 * /d/Kalad/common/noble/wep/shovel.c
 * Purpose    : An old steel shovel.
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

   set_name("shovel");
   set_short("old shovel");
   add_adj(({ "old", "steel" }));
   set_long("This is an old steel shovel used for digging.\n");

   set_hit(11);
   set_pen(5); 
   set_hands(W_BOTH);
   set_wt(W_POLEARM);
   set_dt(W_BLUDGEON);

   add_prop(OBJ_I_WEIGHT, 3030);
   add_prop(OBJ_I_VOLUME, 2700);
   add_prop(OBJ_I_VALUE, 200);
}

