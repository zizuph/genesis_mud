/* 
 * /d/Kalad/common/wild/pass/wep/bed_dag.c
 * Purpose    : A curved dagger used by the Bedlans
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
   set_adj("steel");
   set_long("A dagger with an unusually curved blade, perfect for "+
      "simultaneously impaling and slashing an opponent. A symbol of a "+
      "red sun has been engraved upon its handle.\n");
   set_hit(13);
   set_pen(13);
   set_wt(W_KNIFE);
   set_dt(W_SLASH | W_IMPALE);
   add_prop(OBJ_I_VALUE,180);
   add_prop(OBJ_I_WEIGHT,1250);
   add_prop(OBJ_I_VOLUME,1250);
}
