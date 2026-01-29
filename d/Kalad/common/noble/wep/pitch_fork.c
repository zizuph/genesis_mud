/*
 * /d/Kalad/common/noble/wep/p_fork.c
 * Purpose    : A simple pitch fork.
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

   set_name("fork");
   set_adj("pitch");
   set_short("pitch fork");
   set_long("This is a simple pitch fork, like the kind used by "+
      "farmers.  It has a long haft with three nasty looking prongs "+
      "at the end.\n");

   set_hit(20);
   set_pen(20); 
   set_hands(W_BOTH);
   set_wt(W_POLEARM);
   set_dt(W_IMPALE);

   add_prop(OBJ_I_WEIGHT, 2130);
   add_prop(OBJ_I_VOLUME, 1700);
}

