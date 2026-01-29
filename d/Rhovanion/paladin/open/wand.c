inherit "/std/object";                                                          
#include "/sys/stdproperties.h"                                                 
#include "/sys/macros.h"                                                        
#include "/d/Rhovanion/defs.h"                                                  
                                                                                
int charge;                                                                     
                                                                                
void create_object()                                                            
{                                                                               
   set_name("wand");                                                            
   set_pname("wands");                                                          
   set_short("wand of disintegration");                                         
   set_pshort("wands of disintegration");                                       
   set_long("This is very powerful wand of destruction !"+                      
            " Be careful !!\n");                                                
   add_prop(OBJ_I_WEIGHT,500);                                                  
   add_prop(OBJ_I_VOLUME,200);                                                  
   charge=10;                                                                   
                                                                                
}                                                                               
                                                                                
void init()                                                                     
{                                                                               
   add_action("do_disintegrate","disintegrate");                                
}                                                                               
                                                                                
int do_disintegrate(string target)                                              
{                                                                               
   if (target==0)                                                               
     {                                                                          
       notify_fail("Disintegrate what?\n");                                     
       return 0;                                                                
     }                                                                          
 if ((target=="door")&&(charge>0)&&(ENV(ENV(TO))->allow_dest_door()==1))        
     {                                                                          
       ENV(ENV(TO))->dest_door();                                               
       charge--;                                                                
       write("You point at door with your wand and powerful charge"+            
           " completely disintegrated it !\n");                                 
       say(QCTNAME(TP)+" points with "+TP->query_possessive()+                  
           " wand at the door and it's disintegrates with "+                    
           "a bright flash !\n");                                               
       return 1;                                                                
     }                                                                          
   if (charge==0)                                                               
     {                                                                          
       write("Your wand says: Poof!\n");                                        
       return 1;                                                                
     }                                                                          
   write("As you try to disintegrate "+target+", powerful charge "+             
         "rejected by your target hits you !!!\n");                             
   say(QCTNAME(TP)+" tries to disintegrate "+target+", but only "+              
       "got burned from blinding flash of fire !\n");                           
   TP->set_hp(TP->query_hp()-(TP->query_max_hp())/5);                           
   charge--;                                                                    
   return 1;                                                                    
}                                                                               
                                                                                
