/* 
 * /d/Kalad/common/wild/pass/arm/bed_h_med.c
 * Purpose    : A medallion
 * Located    : Worn by the Bedlans in the desert
 * Created By : Antharanos  ??.??.??
 * Modified By: 
 * First Modif: 
 */ 

inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("medallion");
   set_adj("t'har");
   set_short("medallion of T'har");
   set_long("A superbly crafted medallion made of pure gold. The symbol "+
      "engraved upon it is that of a red sun, spreading fiery light over all "+
      "of creation.\n");
   set_ac(1);
   set_at(A_NECK);
   add_prop(OBJ_I_VALUE,0);
   add_prop(OBJ_I_VOLUME,500);
   add_prop(OBJ_I_WEIGHT,500);
}
