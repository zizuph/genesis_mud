#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include <stdproperties.h>
inherit MITHAS_OUT;

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

    add_exit(MROOM + "square1","north",0);    
    add_exit(MROOM + "arena_entrance","west",0);
    add_exit(MROOM + "square8","east",0);             
    add_exit(MROOM + "tent2","tent","@@enter_tent");
}

string
long_descr()
{ 

   return tod_descr()+ "You are standing in the southeast corner "+
          "of a big marketplace in the city of Nethosak. "+
          "Even though there are a lot of people here, the street "+
          "is still very clean and orderly. All around you large "+
          "tents and wagons have been placed in long rows, offering "+
          "different merchantdises to travellers and citizens. The "+
          "marketplace continues to the north and east. To the west " +
          "lies the entrance to the Arena of Nethosak. This grand "+
          "structure rises high above the buildings in this arena, "+
          "loud cheers and screams can be heard from inside. "+
          season_descr()+ "\n";

}

int
enter_tent()
{
    write("You pull aside the cloth that coveres the entrance, and "+
          "step inside the tent.\n");
    return 0;
} 
