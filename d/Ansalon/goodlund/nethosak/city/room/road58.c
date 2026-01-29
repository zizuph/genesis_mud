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
    set_short("Northern road in Nethosak");
    set_long("@@long_descr"); 
   
    add_exit(MROOM + "road57","northwest",0);
    add_exit(MROOM + "road69","south",0);     
    reset_mithas_room();
}

string
long_descr()
{ 

    return tod_descr()+ "You are standing on "+
         "a eastern road in the city of Nethosak. To "+
         "the northwest and south the road continues. "+
         "Far to the south, beyond the city, tall "+
         "trees and thick bushes cover the ground colouring "+
         "everything in a green light. Four great " +
         "mountain peaks can be seen, over the trees tops "+
         "and a few shadows seems to move slightly around "+
         "then. " +season_descr()+ "\n";
}

