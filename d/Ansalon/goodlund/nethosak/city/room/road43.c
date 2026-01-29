#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include <stdproperties.h>
inherit MITHAS_OUT;

void
create_mithas_room()
{
    set_short("South road in Nethosak");
    set_long("@@long_descr"); 

    add_exit(MROOM + "road42","east",0);
    add_exit(MROOM + "road44","west",0);    
   
}

string
long_descr()
{ 

   return tod_descr()+ "You are standing on the south"+
          "road in the city of Nethosak. The road "+
          "here is paved with small rocks, and the buildings "+
          "are made out of grey stones. The road continues to "+
          "the east towards on of the many intersections and "+
          "to the west, where the road continues. Above the "+
          "city wall to the south, you notice a small forest "+
          "and beyond that four small mountain peeks reach "+
          "high above the trees. To the northeast a great  "+          "building rises, it's tall arches stretches "+
          "themselves high into the air, loud cheers and "+
          "screams can be heard from within. "+
          season_descr()+ "\n";
}

