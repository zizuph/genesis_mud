inherit "/std/creature";                                                        
inherit "/std/act/attack";                                                      
inherit "/std/combat/unarmed";                                                  
                                                                                
#include "/sys/ss_types.h"                                                      
#include "/sys/wa_types.h"                                                      
#include "/sys/macros.h"                                                        
#include "/sys/stdproperties.h"                                                 
                                                                                
                                                                                
create_creature()                                                               
{                                                                               
   if (!IS_CLONE)                                                               
   return;                                                                      
   set_name("gnat");                                                            
   add_name("mosquito");                                                        
   set_short("huge cruel gnat");                                                
   set_pshort("huge cruel gnats");                                              
   set_pname("s");                                                              
   set_living_name("gnat");                                                     
   set_race_name("insect");                                                     
   set_gender(G_NEUTER);                                                        
   set_long("This mosquito makes you tremble from horror. \n"                   
    + "It is as big as a bird and cruel as an orc. \n"                          
    + "You feel that it is going to suck your blood off! \n");                  
   add_prop(LIVE_I_NEVERKNOWN,1);                                               
   set_stats(({5,7,4,3,3,15}));                                                 
   set_alignment(-10);                                                          
   set_aggressive(1);                                                           
                                                                                
   set_attack_unarmed(0,5,5,W_IMPALE,100,"bite");                               
   set_hitloc_unarmed(0,({5,5,5,5}),100,"body");                                
                                                                                
   add_prop(CONT_I_WEIGHT,10);                                                  
   add_prop(CONT_I_VOLUME,15);                                                  
                                                                                
}                                                                               
query_knight_prestige() { return(1); }                                          
