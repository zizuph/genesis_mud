inherit "/std/food";                                                            
                                                                                
#include "/sys/macros.h"                                                        
#include "/sys/stdproperties.h"                                                 
                                                                                
create_food()                                                                   
{                                                                               
   set_name("mushroom");                                                        
   set_pname("mushrooms");                                                      
   set_short("white mushroom");                                                 
   set_pshort("white mushrooms");                                               
   set_adj("white");                                                            
   set_long("This is a big white mushroom. It looks very weird \n"              
   + "and you doubt if it's edible. Sometimes people die after \n"              
   + "eating unknown mushrooms...\n");                                          
   set_amount(100);                                                             
   add_prop(OBJ_I_WEIGHT,50);                                                   
   add_prop(OBJ_I_VOLUME,100);                                                  
}                                                                               
