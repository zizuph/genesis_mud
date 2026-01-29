/*
The High Lords dagger
Made by korat
feb 14. 1995
*/

inherit "/d/Kalad/std/weapon.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"

create_weapon()
{
   ::create_weapon();
   set_name("dagger");
   set_adj("ornate");
   add_adj("keen");
   set_long("This ornate dagger has several engraved patterns on its "+
      "handle and the keen silverish blade. The dagger is very balanced "+
      "making it perfect for stabbing rather than other kinds of attacks.\n");
   set_hit(16);
   set_pen(12);
   set_wt(W_KNIFE);
   set_dt(W_IMPALE);
   add_prop(OBJ_I_VALUE, 600);
   add_prop(OBJ_I_WEIGHT,2500);
   add_prop(OBJ_I_VOLUME,1500);
}

