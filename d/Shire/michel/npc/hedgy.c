inherit "/std/creature";                                                        
inherit "/std/act/action";                                                      
inherit "/std/combat/unarmed";                                                  
                                                                                
#include <ss_types.h>                                                           
#include <wa_types.h>                                                           
#include <macros.h>                                                             
#include <stdproperties.h>                                                      
#include "/d/Shire/common/defs.h"                                               
object target;                                                                  
string name;                                                                    
                                                                                
create_creature()                                                               
{                                                                               
   if (!IS_CLONE)                                                               
   return;                                                                      
   seteuid(getuid(this_object()));                                              
   set_name("cute");                                                            
   add_name("hedgehog");                                                        
   set_short("busy small hedgehog");                                            
   set_pshort("small hedgehogs");                                               
   set_pname("s");                                                              
   set_living_name("hedgehog");                                                 
   set_race_name("hedgehog");                                                   
   set_gender(G_NEUTER);                                                        
   set_long("This is a very busy cute hedgehog carrying something \n"           
    + "he had stolen from local hobbits. His eyes are twinkling \n"             
    + "with greed and happiness. \n");                                          
   add_prop(LIVE_I_NEVERKNOWN,1);                                               
   set_stats(({5,10,10,20,20,20}));                                             
   set_alignment(-30);                                                          
                                                                                
   set_attack_unarmed(0,5,5,W_IMPALE,100,"spikes");                             
   set_hitloc_unarmed(0,({5,5,5,5}),100,"body");                                
                                                                                
   add_prop(CONT_I_WEIGHT,1000);                                                
   add_prop(CONT_I_VOLUME,1500);                                                
                                                                                
   set_act_time(9);                                                             
   add_act(({"sniff","frown","twinkle"}));                                      
   set_cact_time(9);                                                            
   add_cact(({"frown","explode"}));                                             
                                                                                
   money_me();                                                                  
   feed_me();                                                                   
}                                                                               
money_me() {                                                                    
   object money;                                                                
   if(random(2)<2) {                                                            
   money = clone_object("/std/coins");                                          
   money->set_coin_type("copper");                                              
   money->set_heap_size(7);                                                     
   money->move(this_object());                                                  
} }                                                                             
feed_me()  {                                                                    
   object food;                                                                 
   if(random(2)<2) {                                                            
   food = clone_object(MICH_DIR + "obj/mushroom");                              
   food->move(this_object());                                                   
}}                                                                              
