#include "/d/Ansalon/goodlund/nethosak/city/local.h"#include <stdproperties.h>
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
    add_exit(MROOM + "road15","north",0);
    add_exit(MROOM + "road19","south",0);    
    reset_mithas_room();
}

string
long_descr()
{ 

   return tod_descr()+ "You are standing on the southeast"+
          "road in the city of Nethosak. The road "+
          "here is paved with small rocks, and the buildings "+
          "are made out of grey stones. The road continues to north "+
          "toward an intersection and south further down the street. "+
          "To the southwest a tall building rises above the others, "+
          "and to the east, beyond the citywall you notice a small "+
          "forest." +season_descr()+ "\n";
}

