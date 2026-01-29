/* 
 * /d/Kalad/common/wild/pass/wep/bed_edag.c
 * Purpose    : A curved dagger used by strong Bedlans
 * Located    : The Bedlans in the desert
 * Created By : Antharanos  ??.??.??
 * Modified By: 
 * First Modif: 
 */ 

inherit "/d/Kalad/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_weapon()
{
   ::create_weapon();
   set_name("jambiya");
   add_name("dagger");
   set_adj("terrible");
   add_adj("steel");
   set_long("A dagger with an unusually curved blade, perfect for "+
      "simultaneously impaling and slashing an opponent. A symbol of a "+
      "red sun has been engraved upon its handle.\n");
   set_hit(14);
   set_pen(14);
   set_wt(W_KNIFE);
   set_dt(W_SLASH | W_IMPALE);
   add_prop(OBJ_I_VALUE,200);
   add_prop(OBJ_I_WEIGHT,1500);
   add_prop(OBJ_I_VOLUME,1500);
}
