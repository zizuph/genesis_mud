#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include <stdproperties.h>
inherit MITHAS_OUT;

object citizen;
object citizen2;

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

    add_exit(MROOM + "square5","north",0);    
    add_exit(MROOM + "square7","west",0);
    add_exit(MROOM + "square9","east",0);
    add_exit(MROOM + "road41","south",0); 
    add_exit(MROOM + "tent1","tent","@@enter_tent"); 
    reset_mithas_room();
} 

string
long_descr()
{ 

   return tod_descr()+ "You are standing in the southern part "+
          "of a big marketplace in the city of Nethosak. "+
          "Even though there are a lot of people here, the street "+
          "is still very clean and orderly. All around you large "+
          "tents and wagons have been placed in long rows, offering "+
          "different merchantdises to travellers and citizens. The "+
          "marketplace continues to the north, east and west. To the "+
          "south a road continues towards the south gate of the "+
          "city. " +season_descr()+ "\n";
}

int
enter_tent()
{
    write("You pull aside the cloth that coveres the entrance, and "+
          "step inside the tent.\n");
    return 0;
} 

