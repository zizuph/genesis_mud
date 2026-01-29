/* 
 * /d/Kalad/common/wild/pass/wep/bed_sword.c
 * Purpose    : A simple scimitar used by the Bedlans
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
   set_name("scimitar");
   add_name("sword");
   set_adj("steel-bladed");
   set_long("A sword similar to a long sword, save that the blade is "+
      "curved into a slight crescent. An image of a red sun has been "+
      "engraved into the leather pommel.\n");
   set_hit(28);
   set_pen(20);
   set_wt(W_SWORD);
   set_dt(W_SLASH | W_IMPALE);
   add_prop(OBJ_I_VALUE,400);
   add_prop(OBJ_I_WEIGHT,3000);
   add_prop(OBJ_I_VOLUME,3000);
}
