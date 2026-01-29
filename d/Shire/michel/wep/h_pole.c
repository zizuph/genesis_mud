/* Standard hobbits equipment coded by Anri */                                  
inherit "/std/weapon";                                                          
                                                                                
#include <wa_types.h>                                                           
#include <stdproperties.h>                                                      
#include "/sys/formulas.h"                                                      
#include <macros.h>                                                             
                                                                                
void                                                                            
create_weapon() {                                                               
set_name("pole");                                                               
set_short("long ash-tree pole");                                                
set_long("This is a long wooden stick with sharpened end. \n"                   
   + "It is made of an ash-tree. \n");                                          
set_adj(({"long","ash-tree","wooden"}));                                        
set_hit(11);                                                                    
set_pen(7);                                                                     
set_wt(W_POLEARM);                                                              
set_dt(W_IMPALE|W_BLUDGEON);                                                    
set_hands(W_BOTH);                                                              
add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(11,7));                                     
add_prop(OBJ_I_VOLUME,120);                                                     
add_prop(OBJ_I_WEIGHT,900);                                                     
}                                                                               
                                                                                
string query_recover()                                                          
{                                                                               
    return MASTER + ":" + query_wep_recover();                                  
}                                                                               
                                                                                
                                                                                
void init_recover(string arg)                                                   
{                                                                               
    init_wep_recover(arg);                                                      
}                                                                               
