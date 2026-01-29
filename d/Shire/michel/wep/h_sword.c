/* Standard hobbits equipment coded by Anri */                                  
inherit "/std/weapon";                                                          
                                                                                
#include <wa_types.h>                                                           
#include <stdproperties.h>                                                      
#include "/sys/formulas.h"                                                      
#include <macros.h>                                                             
                                                                                
void                                                                            
create_weapon() {                                                               
   set_name("sword");                                                           
   set_short("short hobbits sword");                                            
   set_long("This is a small and short iron sword of hobbits make. \n"          
         + "The sword looks more like a big dagger. It is suitable \n"          
         + "for small creatures like hobbits or gnomes. \n");                   
   set_adj(({"short","hobbits","small","iron"}));                               
   set_hit(16);                                                                 
   set_pen(17);                                                                 
   set_wt(W_SWORD);                                                             
   set_dt(W_SLASH|W_IMPALE);                                                    
   set_hands(W_ANYH);                                                           
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(16,17));                                 
   add_prop(OBJ_I_VOLUME,95);                                                   
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
