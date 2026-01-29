/* 
 * /d/Kalad/common/wild/pass/arm/gchide.c
 * Purpose    : Hide armour of many animals
 * Located    : Used by giants
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
   set_name("armour");
   add_name("hide armour");
   add_name("hide");
   set_adj("hide");
   set_long("This is an extremely large suit of hide armour, made from "+
      "the multiple tanned hides of several animals. It smells really bad.\n");
   set_ac(8);
   set_at(A_BODY);
   add_prop(OBJ_I_VALUE, 100);
   add_prop(OBJ_I_WEIGHT,30000);
   add_prop(OBJ_I_VOLUME,15000);
}
