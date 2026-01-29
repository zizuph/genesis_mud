/* Standard hobbits equipment coded by Anri */                                  
inherit "/std/weapon";                                                          
                                                                                
#include <wa_types.h>                                                           
#include <stdproperties.h>                                                      
#include "/sys/formulas.h"                                                      
#include <macros.h>                                                             
                                                                                
void                                                                            
create_weapon() {                                                               
set_name("spear");                                                              
set_short("light ash-tree spear");                                              
set_long("This is a small wooden spear with dull copper point. \n"              
   + "It is obviously crafted by a peaceful race like hobbits. \n"              
   + "It is made of an ash-tree. \n");                                          
set_adj(({"light","ash-tree","wooden","small"}));                               
set_hit(11);                                                                    
set_pen(16);                                                                    
set_wt(W_POLEARM);                                                              
set_dt(W_IMPALE);                                                               
set_hands(W_ANYH);                                                              
add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(11,16));                                    
add_prop(OBJ_I_VOLUME,110);                                                     
add_prop(OBJ_I_WEIGHT,1200);                                                    
}                                                                               
                                                                                
string query_recover()                                                          
{                                                                               
    return MASTER + ":" + query_wep_recover();                                  
}                                                                               
                                                                                
                                                                                
void init_recover(string arg)                                                   
{                                                                               
    init_wep_recover(arg);                                                      
}                                                                               
