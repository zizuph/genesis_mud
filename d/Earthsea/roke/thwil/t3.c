#include "defs.h"
inherit THWIL_BASE_ROOM;


object *sheep = allocate(4);

void reset_room();

void
create_thwil_room()
{
   set_short("Street");
   set_long("You stand in an intersection in the western parts of Thwil. "+
      "To the south you see the top of the hill and on that "+ 
      "there is a large wall surrounding some sort of building. "+
      "The street slopes downwards " +
      "to the west.\n");
   add_item("building", "It is dominating the surrounding, " +
      "strangely enough not only with its size.\n");
   add_item("wall", "The walls seems to be more of artistic use " +
      "than defensive. \n");
   
   add_exit(THWIL + "t4" , "west" , 0, 1);
   add_exit(THWIL + "t2" , "east" , 0, 1);
   add_exit(THWIL + "a4" , "south" , 0, 1);
   
   STREET;
   reset_room();
}




void
reset_room()
{
   int i;
   
   for(i=0;i<sizeof(sheep);i++)
   if (!objectp(sheep[i]))
      {
      sheep[i] = clone_object(THWIL + "monster/sheep");
      sheep[i]->move_living("flying", this_object(), 1, 1);
   }
   
   for(i=1;i<sizeof(sheep);i++)
   sheep[0]->team_join(sheep[i]);
}



