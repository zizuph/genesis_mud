// hp1
// grace aug 1994

inherit "/std/room";

#include "../local.h"

object guard;
int orb;

create_room()
{

   SHORT("Hidden storage room");
   LONG("This room is half again as large as the Chapel.\n"+
      "It is as clean and well-kept as the rest of the "+
      "fortress, despite its hidden location.  Numerous "+
      "crates line the bare stone walls, and a straw "+
      "pallet lies on the floor.\n");

   INSIDE;
   LIGHT;

   AE(ROOM + "alcove", "alcove", 0);
   AE(ROOM + "hp2", "east", 0);
   clone_object(SOBJ + "arm_a")->move(TO);   

   ACI(({"pallet","mattress"}), ({"lift","feel under", "search"}),
       "@@do_orb");

   reset_room();
}


     {                                                    
         write("Your eyes pick out something round " +
            "in the rubble.\n");
         ob->move(TO);                                        
       }                                                      
      else                                                    
         {                                                                 
         write("Your eyes notice an orb lying in the rubble.\n");                                              
         say(QCTNAME(TP) + " picks something up off of " +
            "the ground.\n");
       }                                                                   
      return 1;                                                            
   }                                                                       

   write("You see nothing but stones and soil.\n");
   return 1;
}
                           
{                                                                      
   orb = 0;
   if (!guard)                                                         
      (guard = clone_object(KNIGHT))->move_living(0,this_object());    
}                                                                      

