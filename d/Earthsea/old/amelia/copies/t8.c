inherit "/d/Roke/common/roke/rokeroom";

#include "/d/Roke/common/defs.h"
#include "/d/Roke/common/roke/defs.h"  /*Wizardschool special defs*/

#pragma strict_types

object *sheep = allocate(3);
object shepherd;

void reset_room();

void
create_room()
{
   set_short("Street");
   set_long("From this high vantage point you have a good "+
      "view of the city below you. Three streets comming from "+
      "south, southwest and east meet here "+
      "at the crest of the hill you stand on. "+
      "To the south of here, beyond the city, you see a big, solid "+
      "stone building radiating strength and power. Northwards there "+
      "is a paddock with lush meadows. " +
      "The air is cold and damp. \n");
   
   
   add_exit(THVIL + "t5" , "southwest" , 0);
   add_exit(THVIL + "t6" , "south" , 0);
   add_exit(THVIL + "t9" , "east" , 0);
   add_exit(THVIL + "p1" , "north", "@@pasing");
   
   OUTSIDE;
   reset_room();
}

int
pasing()
{
   TP->catch_msg("You open the gate to the paddock and easily slip "+
      "through. \n");
   return 0;
}


void
reset_room()
{
   int i = sizeof(sheep);
   
   while (i--)
   {
      if (!objectp(sheep[i]))
         {
         sheep[i] = clone_object(THWIL + "monster/sheep");
            sheep[i]->move_living("flying", this_object(), 1, 1);
          }
   }
   if (!objectp(shepherd))
      {
      shepherd = clone_object(THWIL + "monster/shepherd");
            shepherd->move_living("jumping", this_object(), 1, 1);
   }
}     
