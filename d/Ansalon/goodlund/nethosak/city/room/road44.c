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

    add_exit(MROOM + "road45","northwest",0);
    add_exit(MROOM + "road43","east",0);    
    reset_mithas_room();
}

string
long_descr()
{ 

   return tod_descr()+ "You are standing on the south"+
          "road in the city of Nethosak. The road "+
          "here is paved with small rocks, and the buildings "+
          "are made out of grey stones. The road continues to "+
          "the east towards one of the many intersections and "+
          "to the northwest, where the road continues. To the "+
          "north a great building rises, it's tall arches "+
          "stretches themselves high into the air, loud cheers "+
          "and screams can be heard from within. "+
          season_descr()+ "\n";
}

