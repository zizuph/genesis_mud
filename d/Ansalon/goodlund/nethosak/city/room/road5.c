#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include <stdproperties.h>
inherit MITHAS_OUT;

object citizen;

void 
reset_mithas_room()
{
    if(!objectp(citizen))
    {
      citizen = clone_object(MNPC + "citizen");
      citizen->move(this_object());
   }
}

void
create_mithas_room()
{
    set_short("Northern road in Nethosak");
    set_long("@@long_descr"); 
   
    add_exit(MROOM + "road38","northeast",0);
    add_exit(MROOM + "road4","south",0);     
    reset_mithas_room();
}

string
long_descr()
{ 

    return tod_descr()+ "You are standing on "+
         "a road in the city of Nethosak. To "+
         "the northeast and south the road continues. "+
         "Far to the south tall trees and a few "+
         "mountain peaks can be seen. " +season_descr()+
         "\n";
}

