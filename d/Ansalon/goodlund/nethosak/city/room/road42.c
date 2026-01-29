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
    set_short("South road in Nethosak");
    set_long("@@long_descr"); 

    add_exit(MROOM + "road23","east",0);
    add_exit(MROOM + "road43","west",0);    
    reset_mithas_room();
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
          "high above the trees. " +season_descr()+ "\n";
}

