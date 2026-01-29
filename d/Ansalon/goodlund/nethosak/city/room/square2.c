#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include <stdproperties.h>
inherit MITHAS_OUT;

object citizen;
object citizen2;
object citizen3;

void 
reset_mithas_room()
{
    if(!objectp(citizen))
    {
      citizen = clone_object(MNPC + "citizen");
      citizen->move(this_object());
   }
   if(!objectp(citizen2))
   {
      citizen2 = clone_object(MNPC + "citizen");
      citizen2->move(this_object());
   }
   if(!objectp(citizen3))
   {
      citizen3 = clone_object(MNPC + "citizen");
      citizen3->move(this_object());
   }
}


void
create_mithas_room()
{
    set_short("Marketplace in Nethosak");
    set_long("@@long_descr"); 

    add_item(({"wagon","wagons"}), "The "+
          "wagons are made out of heavy oak wood, and "+
          "a trader is standing next to it. Offering you "+
          "some of him merchantdise.\n");

    add_item(({"tent","tents"}), "The "+
          "tents are made out of thick heavy cloth and colored "+
          "in different dark tones. There's a large opening in "+
          "the side.\n");

    add_exit(MROOM + "roadX","west",0);
    add_exit(MROOM + "square3","east",0);    
    add_exit(MROOM + "square1","south",0);        
    reset_mithas_room();
}

string
long_descr()
{ 

   return tod_descr()+ "You are standing on the northwest "+
          "corner of a big marketplace in the city of Nethosak. "+
          "Even though there are a lot of people here, the street "+
          "is still very clean and orderly. All around you large "+
          "tents and wagons have been placed in long rows, offering "+
          "different merchantdises to travellers and citizens. The "+
          "marketplace continues to the east and south, "+
          "going to the west will take you towards a large square "+
          "building." +season_descr()+ "\n";

}

