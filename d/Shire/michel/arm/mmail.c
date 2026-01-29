/* Standard hobbits equipment coded by Anri */                                  
inherit "/std/armour";                                                          

#include "/sys/macros.h"                                                        
#include <stdproperties.h>                                                      
#include <wa_types.h>                                                           
#include "/sys/formulas.h"                                                      

void                                                                            
create_armour()                                                                 
{ set_name("chainmail");                                                        
   set_short("heavy chainmail");                                                   
   set_long("This heavy chainmail is somewhat rusted, but it should "+
   "provide good protection against slashing.\n");
   set_adj(({"heavy","iron"}));                                                  
   set_ac(10);                                                                     
   set_at(A_BODY);                                                                 
   set_am(({0,1,-1}));                                                             
   add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(10));                                       
   add_prop(OBJ_I_VOLUME,150);                                                     
   add_prop(OBJ_I_WEIGHT,990);                                                     
}                                                                               

