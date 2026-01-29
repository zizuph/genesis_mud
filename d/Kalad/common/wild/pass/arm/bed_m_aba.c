/* 
 * /d/Kalad/common/wild/pass/arm/bed_m_aba.c
 * Purpose    : A robe
 * Located    : Used by the Bedlans in the desert
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
   set_name("aba");
   add_name("robe");
   set_adj("pure");
   add_adj("white");
   set_long("A loose-fitting robe that is perfectly suited to a life "+
      "within the intense heat of the Great Kalad Waste. An image of a "+
      "red sun has been sewn onto the amazingly white cloth, creating a "+
      "stark contrast.\n");
   set_ac(3);
   set_at(A_ROBE);
   add_prop(OBJ_I_VALUE,200);
   add_prop(OBJ_I_VOLUME,2000);
   add_prop(OBJ_I_WEIGHT,2000);
}
