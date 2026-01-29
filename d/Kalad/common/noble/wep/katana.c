/*
 * /d/Kalad/common/noble/wep/katana.c
 * Purpose    : A nicely crafted, one handed katana.
 * Located    : 
 * Created By : Sarr
 * Modified By: Sarr, Rico
 * First Modif: 12.Feb.97
 */

inherit "/d/Kalad/std/weapon";

#include "/d/Kalad/defs.h"

void
create_weapon()
{
   ::create_weapon();

   set_name("katana");
    add_name("sword");
   set_adj("steel");
   add_adj("silver-steel");
   set_short("silver-steel katana");
   set_long("This sword has a shiny silver blade. It seems to be some "+
      "kind of a silver and steel alloy. It looks razor sharp, and "+
      "deadly. The handle is wrapped tightly with black cloth. "+
      "Not a speck mars its perfect beauty.\n");

   set_dt(W_SLASH | W_IMPALE);
   set_wt(W_SWORD);
   set_hit(34); /* 4 points for its incredibly light design */
   set_pen(25); /* 4 points for the design of the blade itself. That
                   number would be MUCH higher for an authentic katana,
                   but this isn't an Oriental based domain anyway. */

   add_prop(OBJ_I_WEIGHT, 5000);
   /* I'd call the katana a curved one-handed sword, most closely
      resembling the scimitar in the weapon_guide. I've modified
      it accordingly. */
   add_prop(OBJ_I_VOLUME, 3000);
   add_prop(OBJ_I_VALUE, 2000);
}

