/* 
 * /d/Kalad/common/central/arm/lord_boots.c
 * Purpose    : Boots worn by the high lord in the citadel
 * Located    : /d/Kalad/common/central/arm/
 * Created By : Korat 1995
 * Modified By: 
 */ 

/*
High Lords boots
Made by korat
feb 14. 1995
*/

inherit "/d/Kalad/std/armour.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"

create_armour()
{
   ::create_armour();
   set_name("boots");
   set_short("pair of black combat boots");
   set_pshort("pairs of black combat boots");
   set_adj(({"black","combat"}));

   set_long("This is a excellent pair of combat boots, made of an unknown "+
      "sheeted black metal, riveted to hard leather. The edges of the "+
      "sheets seems to glow "+
      "in a golden colour, making you think of sunbeams. The heels "+
      "on the boots are strenghtened with added pieces of metal.\n");

   set_ac(17);
   set_at(A_FEET);
   add_prop(OBJ_I_VALUE,500);
   add_prop(OBJ_I_WEIGHT,3500);
   add_prop(OBJ_I_VOLUME,2000);
}  
