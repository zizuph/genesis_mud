/* 
 * /d/Kalad/common/central/arm/lord_greaves.c
 * Purpose    : Greaves worn by the high lord in the citadel
 * Located    : /d/Kalad/common/central/arm/
 * Created By : Korat 1995
 * Modified By: 
 */ 

/*
High Lords greaves
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
   set_name("greaves");
   set_pname("greaveses");
   set_adj("black");
   add_adj("combat");
   set_long("This is a excellent pair of combat greaves, made of an unknown "+
      "sheeted black metal, riveted to hard leather. They will protect "+
      "your legs very well. The edges of the sheets seems to glow "+
      "in a golden colour, making you think of sunbeams.\n");

   set_ac(20);
   set_at(A_LEGS);
   add_prop(OBJ_I_VALUE,500);
   add_prop(OBJ_I_WEIGHT,3500);
   add_prop(OBJ_I_VOLUME,2000);
}  
