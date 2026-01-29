/* room coded by Elizabeth Cook/Mouse, September 1996 */

inherit "std/room";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "../../mouse.h"

   void create_room() {
     add_prop(ROOM_I_LIGHT,1);
     add_prop(ROOM_I_INSIDE, 1);
     set_short("In the lodge");
     set_long("   The tunnel terminates in the south end of a chamber, "+
          "appearing only as a watery hole in the floor. The chamber "+
          "is as roughly hewn as the tunnel, with gnawed bits of "+
          "branches and other woody material protruding from the "+
          "walls and ceiling. This room is very dimly illuminated by "+
          "the light that manages to filter up through the tunnel and "+
          "down through the ceiling. In the northern end of the chamber "+
          "you notice a beaver nervously watching you while he eats his "+ 
          "dinner. He appears to be protecting the entrance to another "+
          "chamber to the north.\n");
     add_item("walls", "The walls are not much to look at, just mud "+
          "with nubs of wood sticking out.\n");
     add_item("branches","All you can see is chewed off nubs.\n"); 
     add_item("roots", "All you can see is chewed off nubs.\n");
     add_item("mud", "Slimy, brown, wet dirt.\n");
     add_item("hole", "You feel certain this is the only way back "+
          "out of the lodge, by swimming down through the tunnel "+
          "again.\n");
     add_item("floor", "The floor is hard-packed and smoothened from "+
          "years of use. From the fresh young twigs and leaves the "+
          "beaver has deposited on the floor, you believe this is his "+ 
          "dining area.\n");
     add_item("ceiling","The ceiling is made of tightly packed twigs "+ 
          "and branches  that are not cemented with mud to allow the "+
          "circulation of fresh air.\n");

     add_exit(ROOT+"pond/rooms/beaver_room3","swim","@@swim_func",5,1);
     add_exit(ROOT+"pond/rooms/beaver_room5","north","@@check_exit");  

     clone_object(ROOT+"pond/mons/beaver.c")->move(TO); 
}

void reset_room()
{
  if(!present("beaver"))
      clone_object(ROOT+"pond/mons/beaver.c")->move(TO);
}


int check_exit() {
   object beaver = present("beaver");
   if((beaver)&&(CAN_SEE(beaver,this_player())))
   {    
     write("You try to go north, but the beaver blocks your way.\n");
     return 1;
   }
   return 0;
}
int swim_func() {
   if(query_dircmd()!="down")
   {
      write("It is impossible to swim that direction.\n");
      return 1;
   }
   return 0;
}
