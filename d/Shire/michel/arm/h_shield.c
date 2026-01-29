/* Standard hobbits equipment coded by Anri */                                  
inherit "/std/armour";                                                          
                                                                                
#include "/sys/macros.h"                                                        
#include <stdproperties.h>                                                      
#include <wa_types.h>                                                           
#include "/sys/formulas.h"                                                      
                                                                                
void                                                                            
create_armour()                                                                 
{ set_name("shield");                                                           
set_short("small square shield");                                               
set_long("This shield is of square form and made of fine bronze. \n"            
       + "It has a funny hobbits face painted on its surface. \n"               
       + "This armour is crafted in Hobbiton.\n"                                
       + "Alas, hobbits are not very skillful smiths though. \n");              
set_adj(({"small","square","bronze"}));                                         
set_ac(10);                                                                     
set_at(A_SHIELD);                                                               
set_am(({0,-1,1}));                                                             
add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(10));                                       
add_prop(OBJ_I_VOLUME,150);                                                     
add_prop(OBJ_I_WEIGHT,590);                                                     
}                                                                               
                                                                                
string query_recover()                                                          
{                                                                               
    return MASTER + ":" + query_arm_recover();                                  
}                                                                               
                                                                                
                                                                                
void init_recover(string arg)                                                   
{                                                                               
    init_arm_recover(arg);                                                      
}                                                                               
