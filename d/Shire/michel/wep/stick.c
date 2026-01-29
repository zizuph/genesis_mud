inherit "/std/weapon";                                                          
#include <wa_types.h>                                                           
#include <macros.h>                                                             
#include <stdproperties.h>                                                      
#include "/sys/formulas.h"                                                      
                                                                                
void                                                                            
create_weapon() {                                                               
   set_name("stick");                                                           
   set_short("short oak stick");                                                
   set_long("This is a short wooden stick of solid oak. Seems that \n"          
   + "it was used as a walking stick by a small creature like a \n"         
   + " hobbit. You think it can be used as a weapon too. \n");                
   set_adj(({"short","wooden","oak","walking"}));                               
   set_hit(8);                                                                  
   set_pen(8);                                                                  
   set_wt(W_CLUB);                                                              
   set_dt(W_BLUDGEON);                                                          
   set_hands(W_ANYH);                                                           
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(8,8));                                   
   add_prop(OBJ_I_VOLUME,90);                                                   
   add_prop(OBJ_I_WEIGHT,190);                                                  
                                                                                
}                                                                               
   string query_recover()                                                       
{ return MASTER + ":" + query_wep_recover(); }                                  
                                                                                
   void                                                                         
   init_recover(string arg)                                                     
{ init_wep_recover(arg); }                                                      
                                                                                
