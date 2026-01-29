/* Standard hobbits equipment coded by Anri */                                  
inherit "/std/armour";                                                          
                                                                                
#include "/sys/macros.h"                                                        
#include <stdproperties.h>                                                      
#include <wa_types.h>                                                           
#include "/sys/formulas.h"                                                      
                                                                                
void                                                                            
create_armour()                                                                 
{ set_name("cloak");                                                            
set_short("short blue cloak");                                                  
set_long("This is a short cloak of Hobbiton style. \n"                          
       + "Its colour is blue and it has few white strips. \n");                 
set_adj(({"small","short","blue"}));                                            
set_ac(5);                                                                      
set_at(A_ROBE);                                                                 
set_am(({-1,-1,2}));                                                            
add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(5)+random(20));                             
add_prop(OBJ_I_VOLUME,50);                                                      
add_prop(OBJ_I_WEIGHT,190);                                                     
}                                                                               
                                                                                
string query_recover()                                                          
{                                                                               
    return MASTER + ":" + query_arm_recover();                                  
}                                                                               
                                                                                
                                                                                
void init_recover(string arg)                                                   
{                                                                               
    init_arm_recover(arg);                                                      
}                                                                               
