/* Standard hobbits equipment coded by Anri */                                  
inherit "/std/armour";                                                          
                                                                                
#include "/sys/macros.h"                                                        
#include <stdproperties.h>                                                      
#include <wa_types.h>                                                           
#include "/sys/formulas.h"                                                      
                                                                                
void                                                                            
create_armour()                                                                 
{ set_name("chainmail");                                                        
set_short("short chainmail");                                                   
set_long("This is a small bronze chainmail. This armour is crafted in \n"       
    + "Hobbiton. Alas, hobbits are not very skillful smiths though. \n");       
set_adj(({"short","bronze"}));                                                  
set_ac(12);                                                                     
set_at(A_BODY);                                                                 
set_am(({0,1,-1}));                                                             
add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(12));                                       
add_prop(OBJ_I_VOLUME,150);                                                     
add_prop(OBJ_I_WEIGHT,990);                                                     
}                                                                               
                                                                                
string query_recover()                                                          
{                                                                               
    return MASTER + ":" + query_arm_recover();                                  
}                                                                               
                                                                                
                                                                                
void init_recover(string arg)                                                   
{                                                                               
    init_arm_recover(arg);                                                      
}                                                                               
