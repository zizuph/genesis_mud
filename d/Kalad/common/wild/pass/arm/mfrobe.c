/* 
 * /d/Kalad/common/wild/pass/arm/mfrobe.c
 * Purpose    : A red robe
 * Located    : Used by the mind flayers in underdark
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("robe");
   set_adj("fine");
   add_adj("red");
   set_long("A long full robe, colored the deepest crimson. Upon it are "+
      "many excryptic sigils, unfortunately you cannot understand their "+
      "meaning.\n");
    set_ac(3);
   set_at(A_ROBE);
   add_prop(OBJ_I_VALUE,1200);
   add_prop(OBJ_I_VOLUME,2500);
   add_prop(OBJ_I_WEIGHT,2500);
}
