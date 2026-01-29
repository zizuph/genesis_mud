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
    set_short("Southeast road in Nethosak");
    set_long("@@long_descr"); 

    add_item(({"tall building","building"}), "The "+
       "great building, has a circular shape, it might "+
       "be the Temple of the Stars.\n");

    add_exit(MROOM + "road20","northeast",0);
    add_exit(MROOM + "temple_entrance2","southwest",0);    
    reset_mithas_room();
}

string
long_descr()
{ 

   return tod_descr()+ "You are standing on the southeast"+
          "road in the city of Nethosak. The road "+
          "here is paved with small rocks, and the buildings "+
          "are made out of grey stones. The road continues to "+
          "the northeast toward the eastside of the city and "+
          "to the southwest, where three large statues has "+
          "been placed infront of the entrance to a temple. "+
          random_descr()+ " " +season_descr()+ "\n";
}

