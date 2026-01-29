// kn2.c wood storage room, Knights' Spur
// Grace,  Dec 30 1994

#include "../local.h"
#include <stdproperties.h>

inherit SPURRM;

object wood;
int log;


void
reset_spur_room()
{                                                                       
    log = 0;
    if (!wood)
      (wood = clone_object(SOBJ + "wood"))->move(TO);
}  

void  
create_spur_room()
{
   SHORT("Storage room");
   LONG("A small room much like all the others here in the "+
      "Knights' Spur.  The room lacks its own illumination, "+
      "the only light being that which filters in from the "+
      "hallway to the east. There is a large stack of firewoo"+
      "d piled neatly on the floor. ");
                                                                            
   INSIDE;
   LIGHT;
   add_exit(ROOM + "pass3l3", "east", 0);
   AE(ROOM + "kn1", "south", 0);
    clone_object(SOBJ + "closet_a")->move(TO); 
   AI(({"stack","pile"}), "@@pile_of_wood");
   AI(({"floor","stone floor"}),                                                 
      "It is covered with wood chips and wood dust.\n");                                                          

   reset_spur_room();

}      

void                                                                                 
init()                                                                           
{                                                                                
    ::init();                                                                    
                                         
    ADA("get");                                                                  
    ADD("get","take"); 
}                                                                                
                                                                                 
string
pile_of_wood()
{                                                                                                                
   if (log == 11)
      {           
           write("The pieces of wood remaining in this stack are quite "+
                   "large and have yet to be split. They are much too "+
                   "heavy to be carried.\n");

           return "";
      }
   write("There are pieces of wood in all shapes and sizes in this pile. "+
           "Some of them are small enough to be carried by one person, "+
           "while others weigh more than you do.\n");
   SAY(" looks toward the stack of firewood.\n");
   return "";
}



int 
get(string str)
{
   NF("Get what?\n");
   if ((str == "wood") || (str == "firewood") || (str == "piece of wood") ||
        (str == "wood from stack") || (str == "piece of wood from stack"))
      {
          if (log == 11)
             {
                 write("You cannot carry that piece of wood, it is MUCH "+
                          "too heavy!\n");
                  SAY(" tries get a piece of wood from the stack, but fails.\n");
                  return 1;
              }
      clone_object(SOBJ + "wood")->move(TP);
      write("You get a piece of firewood from the stack.\n");
      SAY(" gets a piece of firewood from the stack.\n");
      log++;
      return 1;
   }
   return 0;
}                                                                      
                                                                        
