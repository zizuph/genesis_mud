/* test weapon created by Anri 940608 */                                        
inherit "/std/weapon";                                                          
#include <wa_types.h>                                                           
#include <stdproperties.h>                                                      
#include <macros.h>                                                             
                                                                                
void                                                                            
create_weapon()                                                                 
{                                                                               
set_name("sword");                                                              
set_short("novice smith sword");                                                
set_long("This is a long steel sword crafted by novice Shire smith. \n"         
        + "Its has a big hilt with a ruby incrusted in it. \n");                
set_adj("novice");                                                              
set_hit(20);                                                                    
set_pen(20);                                                                    
set_wt(W_SWORD);                                                                
set_dt(W_SLASH|W_IMPALE);                                                       
set_hands(W_BOTH);                                                              
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(20,20) + 250);
add_prop(OBJ_I_VOLUME,2000);                                                    
add_prop(OBJ_I_WEIGHT,8000);                                                    
}                                                                               
                                                                                
                                                                                
string query_recover()                                                          
{                                                                               
    return MASTER + ":" + query_wep_recover();                                  
}                                                                               
                                                                                
                                                                                
void init_recover(string arg)                                                   
{                                                                               
    init_wep_recover(arg);                                                      
}                                                                               
                                                                                
