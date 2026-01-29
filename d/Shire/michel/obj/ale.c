inherit "/std/drink";                                                           
                                                                                
#include "/sys/macros.h"                                                        
#include "/sys/stdproperties.h"                                                 
                                                                                
create_drink()                                                                  
{                                                                               
   set_name("ale");                                                             
   set_pname("ales");                                                           
   set_short("jar of ale");                                                     
   set_pshort("jars of ale");                                                   
   set_adj("cold");                                                             
   set_long("This is jar of the finest hobbits ale. \n" +                       
     "It is cold as if it was kept in the cellar.\n");                          
   set_soft_amount(100);                                                        
   set_alco_amount(5);                                                          
   add_prop(OBJ_I_WEIGHT,100);                                                  
   add_prop(OBJ_I_VOLUME,100);                                                  
}                                                                               
