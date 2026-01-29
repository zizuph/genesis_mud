inherit "/std/armour";

#include "/sys/wa_types.h"       
#include "/sys/formulas.h"      
#include "/sys/stdproperties.h"  

 void
   create_armour()
   {
      set_name("cloak");
      set_short("very desirable cloak");
      set_long("You don't know why, but you desire this cloak!\n");

      set_default_armour(
         10,          
         A_ROBE,     
         0,           
         0);          

      add_prop(OBJ_I_WEIGHT, 2000); 
      add_prop(OBJ_I_VOLUME,  2000); 
      add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10) + random(200) - 100);
                  
   }
