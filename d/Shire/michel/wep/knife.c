/* Standard hobbits equipment coded by Anri */                                  
inherit "/std/weapon";                                                          
                                                                                
#include <wa_types.h>                                                           
#include <stdproperties.h>                                                      
#include "/sys/formulas.h"                                                      
#include <macros.h>                                                             
                                                                                
void                                                                            
create_weapon() {                                                               
set_name("dagger");                                                             
set_short("heavy copper dagger");                                               
set_long("This is a heavy dagger made of fine copper. This weapon \n"           
   + "looks very simple - a long blade and a hilt covered with \n"              
   + "soft leather. It looks old and much used. \n");                           
set_adj(({"heavy","copper"}));                                                  
set_hit(10);                                                                    
set_pen(10);                                                                    
set_wt(W_KNIFE);                                                                
set_dt(W_IMPALE|W_SLASH);                                                       
set_hands(W_ANYH);                                                              
add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(10,10));                                    
add_prop(OBJ_I_VOLUME,60);                                                      
add_prop(OBJ_I_WEIGHT,900);                                                     
}                                                                               
                                                                                
