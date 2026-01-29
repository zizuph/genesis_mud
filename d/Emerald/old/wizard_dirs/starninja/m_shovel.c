inherit "/std/object";                                                          
                                                                                
#include "/d/Emerald/defs.h"                                                    
                                                                                
int do_dig(string str);                                                         
int do_bury(string str);                                                        
                                                                                
void                                                                            
create_object()                                                                 
{                                                                               
 set_name("shovel");                                                            
 set_short("magic shovel");                                                     
 set_adj("magic");                                                              
 set_long("This is a magic shovel. Its magic felt easily; " +                   
         "every time you touch shovel or even linger your hand " +              
         "near it strange feeling overcomes you.\n");                           
}                                                                               
                                                                                
init()                                                                          
{                                                                               
 ::init();                                                                      
 add_action(do_dig,"dig");                                                      
 add_action(do_bury,"bury");                                                    
}                                                                               
                                                                                
int                                                                             
do_dig(string str)                                                              
{                                                                               
 object ms;                                                                     
 int ran;                                                                       
                                                                                
 NF("Dig what with what?\n");                                                   
 if (!str) return 0;                                                            
 if (!parse_command(str,"'ground'/'here' 'with' %o",ms)) return 0;              
 if (ms!=TO) return 0;                                                          
 if (ENV(TP)->query_prop(ROOM_I_INSIDE))                                        
       {                                                                        
        ran=random(10000);                                                      
        if (ran)                                                                
           {                                                                    
             write("Shovel resists!\n");                                        
             return 1;                                                          
           }                                                                    
        write("Shovel breaks!\n");                                              
        set_alarm(0.1,0.0,remove_object());                                     
        return 1;                                                               
       }                                                                        
 write("With an amazing speed you dig out HUGE hole in the ground.\n");         
 say(QCTNAME(TP) + " digs out huge hold in the ground.\n");                     
 ENV(TP)->add_my_desc("Someone digged out here huge hole.\n");                  
 return 1;                                                                      
}                                                                               
                                                                                
int                                                                             
do_bury(string str)                                                             
{                                                                               
 object wh,ms;                                                                  
 int ran;                                                                       
                                                                                
 NF("Bury what with what?\n");                                                  
 if (!str) return 0;                                                            
 if (!parse_command(str,all_inventory(ENV(TP)) + all_inventory(TP),             
         "%o 'with' %o",wh,ms)) return 0;                                       
 if (ms!=TO) return 0;                                                          
 if (ENV(TP)->query_prop(ROOM_I_INSIDE))                                        
       {                                                                        
        ran=random(10000);                                                      
        if (ran)                                                                
           {                                                                    
             write("Shovel resists!\n");                                        
             return 1;                                                          
           }                                                                    
        write("Shovel breaks!\n");                                              
        set_alarm(0.1,0.0,remove_object());                                     
        return 1;                                                               
       }                                                                        
 if (wh->query_prop(OBJ_M_NO_GET) || wh->query_prop(OBJ_M_NO_DROP))             
      {                                                                         
        write("You cannot bury this!\n");                                       
        return 1;                                                               
      }                                                                         
 write("You bury " + wh->query_short() + ".\n");                                
 say(QCTNAME(TP) + " buries " + wh->query_short() + ".\n");                     
 wh->remove_object();                                                           
 return 1;                                                                      
}                                                                               
