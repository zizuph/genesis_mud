inherit "/d/Shire/room";                                                        
                                                                                
#include <macros.h>                                                             
#include <stdproperties.h>                                                      
#include "/d/Shire/common/defs.h"                                               
create_room()                                                                   
{                                                                               
  set_short("In the cellar");                                                   
  set_long("You are staying in the dark cellar deep inside " +                  
     "the hobbits hole. This is a place where hobbits store their \n" +         
     "food. You see many huge circles of cheese and sausages and \n"+           
     "packs with crops here. There are some barrels with ale, \n" +             
     "red wine and brandy stored in the corner. \n" +                           
     "The air is cold and wet here. \n");                                       
  add_item("cheese","These are big pieces of famous Michel " +                  
     "Delving cheese. \n");                                                     
  add_item("sausages","There are many sausages hanging on the wall.\n");        
  add_item("barrels","The barrels are made of wood and filled " +               
     "with beverages. \n");                                                     
  add_prop(ROOM_I_LIGHT,0);                                                     
  add_prop(ROOM_I_INSIDE,1);                                                    
  add_exit(MICH_DIR +"hole4","up",0);                                           
  reset_room();                                                                 
}                                                                               
                                                                                
reset_room() {                                                                  
   object ob;                                                                   
   object goods;                                                                
   ob = clone_object(MICH_DIR +"npc/gnat");                                     
   ob->move(this_object());                                                     
   goods = clone_object("/std/food");                                           
   goods->move(this_object());                                                  
   goods->set_name("sausage");                                                  
   goods->set_pname("sausages");                                                
   goods->set_short("smoked sausage");                                          
   goods->set_pshort("smoked sausages");                                        
   goods->set_adj("smoked");                                                    
   goods->set_long("This is a piece of tasty smoked sausage. \n"                
   + "It smells with garlic, pepper and spices. You suppose \n"                 
   + "that only hobbits are able to cook such delicious things!.\n");           
   goods->set_amount(100);                                                      
   goods->add_prop(OBJ_I_WEIGHT,50);                                            
   goods->add_prop(OBJ_I_VOLUME,90);                                            
   goods->move(this_object());                                                  
}                                                                               
