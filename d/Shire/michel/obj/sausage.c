inherit "/std/food";                                                            
                                                                                
#include "/sys/macros.h"                                                        
#include "/sys/stdproperties.h"                                                 
                                                                                
create_food()                                                                   
{                                                                               
   set_name("sausage");                                                         
   add_name("_shire_sausage_");
   set_pname("sausages");                                                       
   set_short("smoked sausage");                                                 
   set_pshort("smoked sausages");                                               
   set_adj("smoked");                                                           
   set_long("This is a piece of tasty smoked sausage. \n"                       
   + "It smells with garlic, pepper and spices. You suppose \n"                 
   + "that only hobbits are able to cook such delicious things!.\n");           
   set_amount(100);                                                             
   add_prop(OBJ_I_WEIGHT,50);                                                   
   add_prop(OBJ_I_VOLUME,90);                                                   
}                                                                               
