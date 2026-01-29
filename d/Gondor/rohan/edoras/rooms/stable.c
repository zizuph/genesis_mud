inherit "/d/Gondor/common/room";                                                      

#include <stdproperties.h>                                                            
#include "/d/Gondor/defs.h"

object *marh = allocate(3);

void
reset_room()
{
int i = sizeof(marh);

   while (i--)
      if (!objectp(marh[i]))
         (marh[i] = clone_object(EDORAS_DIR + "npc/marh1"))->move(this_object());
}
                                                                                      
void
create_room()
{
   set_short("The Stables");
   set_long(BSN("This is the main stable of Edoras, " +
      "where Rohirrim warriors keep their " +
      "Mearas, a special breed of horse. " +
      "In the corner there is a trough with straw and a cistern with water. " +
      "People are running by outside the door to the north."));
   add_exit(EDORAS_DIR + "field","north",0,1);                               
   add_prop(ROOM_I_INSIDE,1);                                                          

   add_item(({"trough", "trough with straw", "straw"}),
      "The trough is full of fresh straw coming from the plains of Rohan.\n");
   add_item(({"cistern", "cistern with water", "water"}),
      "The cistern is full of fresh water.\n");
   add_item(({"wall", "walls"}), 
      "The walls of the stable are made from roughly hewn black rock.\n");
   add_item(({"ceiling", "roof"}), 
      "The ceiling is made of wooden beams covered by stone tiles.\n");
   add_item(({"floor", "ground"}),
      "The ground is covered with straw.\n");
   add_item(({"stable"}),
      "Yes, you are in a stable! How observant of you!\n");

   reset_room();
}                                                                                     
