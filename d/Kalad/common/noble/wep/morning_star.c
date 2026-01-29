/*
 * /d/Kalad/common/noble/wep/m_star.c
 * Purpose    : Morning star.
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

   set_name("morning-star");
   add_adj("morning");
   add_name("star");
   set_adj("steel");
   add_adj("spiked");
   set_short("steel spiked morning-star");
   set_long("A steel handle with a long, barbed chain hanging "+
      "from it. At the end of it, is a very nasty looking spiked, "+
      "ball. The ball is quite heavy.\n");

   set_hit(28); /* slower than mace */
   set_pen(32); /* but hurts more when hits */
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON | W_IMPALE); /* spikes impale */

   add_prop(OBJ_I_WEIGHT, 3000);
   add_prop(OBJ_I_VOLUME, 1520);
   add_prop(OBJ_I_VALUE, 890);
}

