/* This is file /d/Gondor/morgul/obj/hook.c       */                                      
/* A hook for the entrance quest to Minas Morgul  */                                      
/* Olorin, December 1993                          */                                      
                                                                                          
inherit "/std/weapon";                                                                    
                                                                                          
#include <stdproperties.h>                                                                
#include <wa_types.h>                                                                     
#include <formulas.h>                                                                     
#include <macros.h>                                                                       
                                                                                          
#define BSN(xxx)        break_string(xxx + "\n", 78)                                      
                                                                                          
create_weapon()                                                                           
{                                                                                         
  set_name(({"hook","axe","weapon"}));                                                    
  set_short("iron hook");                                                                 
                                                                                          
  set_long(BSN("This is an iron rod, a little more than a foot long. " +                  
    "One half of the rod has been bent, shaping the rod into a hook. " +   
    "The tip at the bent end has been sharpened, so that one can use the " +             
    "hook also as some kind of axe, but it is probably not an effective weapon."));       
  set_adj("iron");                                                                        
  set_default_weapon(4,7,W_AXE,W_IMPALE,W_ANYH,0);                                        
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(4,7)+random(100)+50);                               
  add_prop(OBJ_I_WEIGHT,
	(F_WEIGHT_DEFAULT_WEAPON(4, W_AXE) + random(40) + 700));                     
}                                                                                         
                                                                                          
query_recover()  { return MASTER + ":" + query_wep_recover(); }                           
init_recover(arg) { init_wep_recover(arg); }                                              
