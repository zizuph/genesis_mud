inherit "/std/object";                                                          
#include <stdproperties.h>                                                      
#include <macros.h>                                                             
                                                                                
void                                                                            
create_object() {                                                               
  set_name("hay");                                                              
   add_name(({"_pony_hay_","heap of hay","heap"}));
  add_adj(({"fragrant","dried"}));                                              
  set_short("heap of hay");                                                     
  set_pshort("heaps of hay");                                                   
  set_long("This is a large heap of fragrant hay. The dryed grass \n" +         
    "smells with herbs and looks like a perfect food for your \n"+              
    "best horses. \n");                                                         
  add_prop(OBJ_I_VALUE,0);                                                      
  add_prop(OBJ_I_VOLUME,10000);                                                 
  add_prop(OBJ_I_WEIGHT,1000);                                                  
}                                                                               
