/*
 * /d/Kalad/common/noble/wep/k_hooks.c
 * Purpose    : A serrated hook, used as a shortsword.
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

   set_name("hook");
   set_adj("black");
   add_adj("serrated");
   set_short("black serrated hook");
   set_long("This is a nasty looking hook. The inside and outside "+
      "of the hook is covered with serrated spikes like a saw. The "+
      "hook point is sharp and lethal. There is black cloth wrapped "+
      "around the handle of it to give it a better grip. The hooks "+
      "extend about the size of a shortsword.\n");

   set_wt(W_SWORD);
   set_hit(20);
   set_pen(24);

   add_prop(OBJ_I_WEIGHT, 2500);
   add_prop(OBJ_I_VOLUME, 760);
   add_prop(OBJ_I_VALUE, 600);
}

