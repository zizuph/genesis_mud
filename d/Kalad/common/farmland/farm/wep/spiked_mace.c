/*
 * /d/Kalad/common/noble/wep/sp_mace.c
 * Purpose    : A black spiked mace.
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

   set_name("mace");
   set_adj("black");
   add_adj("spiked");
   set_short("black spiked mace");
   set_long("This mace is made of blackened steel. It has a winged "+
      "shape with many nasty, razor sharp spikes jutting out of it.\n");

   set_hit(25);
   set_pen(21);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON | W_IMPALE);

   add_prop(OBJ_I_WEIGHT, 2065);
   add_prop(OBJ_I_VOLUME, 1520);
   add_prop(OBJ_I_VALUE, 500);
}

