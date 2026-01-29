/* Standard hobbits equipment coded by Anri */                                  
inherit "/std/weapon";                                                          
                                                                                
#include <wa_types.h>                                                           
#include <stdproperties.h>                                                      
#include "/sys/formulas.h"                                                      
#include <macros.h>                                                             
                                                                                
void                                                                            
create_weapon() {                                                               
set_name("mace");                                                              
set_short("hard steel mace");                                                    
set_long("This hard steel mace looks old and rusty.\n");
set_adj(({"rusty","hard","steel"}));                                        
set_hit(10);                                                                    
set_pen(9);                                                                     
set_wt(W_CLUB);                                                                 
set_dt(W_BLUDGEON);                                                             
set_hands(W_ANYH);                                                              
add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(10,9));                                     
add_prop(OBJ_I_VOLUME,130);                                                     
add_prop(OBJ_I_WEIGHT,1500);                                                    
}                                                                               
                                                                                
