/* Standard hobbits equipment coded by Anri */                                  
inherit "/std/weapon";                                                          
                                                                                
#include <wa_types.h>                                                           
#include <stdproperties.h>                                                      
#include "/sys/formulas.h"                                                      
#include <macros.h>                                                             
                                                                                
void                                                                            
create_weapon() {                                                               
set_name("flail");                                                              
set_short("ash-tree flail");                                                    
set_long("This is a nice wooden flail used often in field labour. \n"           
       + "It consists of two ash-tree sticks joined by short chain. \n"        
       + "The flail looks like a peasant's weapon. \n");                         
set_adj(({"ash-tree","wooden","nice"}));                                        
set_hit(13);                                                                    
set_pen(9);                                                                     
set_wt(W_CLUB);                                                                 
set_dt(W_BLUDGEON);                                                             
set_hands(W_ANYH);                                                              
add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(13,9));                                     
add_prop(OBJ_I_VOLUME,130);                                                     
add_prop(OBJ_I_WEIGHT,1500);                                                    
}                                                                               
                                                                                
string query_recover()                                                          
{                                                                               
    return MASTER + ":" + query_wep_recover();                                  
}                                                                               
                                                                                
                                                                                
void init_recover(string arg)                                                   
{                                                                               
    init_wep_recover(arg);                                                      
}                                                                               
