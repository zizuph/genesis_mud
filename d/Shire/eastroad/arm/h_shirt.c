/* Adapted from Anri's hobbit's equipment */
/* Standard hobbits equipment coded by Anri */                                  
inherit "/std/armour";                                                          

#include "/sys/macros.h"                                                        
#include <stdproperties.h>                                                      
#include <wa_types.h>                                                           
#include "/sys/formulas.h"                                                      

void                                                                            
create_armour()                                                                 
{ set_name("shirt");                                                            
   set_short("soft leather shirt");                                                
   set_long("This shirt is made of soft leather, and looks " +
      "very comfortable and stylish, but wouldn't stop " +
      "much in the way of a weapon blow.\n");
   set_adj(({"soft","leather"}));                                                  
   set_ac(3+random(4));
   set_at(A_BODY);                                                                 
   set_am(({1,1,-2}));                                                             
   add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(7)+random(20));                             
   add_prop(OBJ_I_VOLUME,100);                                                     
   add_prop(OBJ_I_WEIGHT,290);                                                     
}                                                                               

string query_recover()                                                          
{                                                                               
   return MASTER + ":" + query_arm_recover();                                  
}                                                                               


void init_recover(string arg)                                                   
{                                                                               
   init_arm_recover(arg);                                                      
}                                                                               
