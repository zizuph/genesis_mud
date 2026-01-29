#include "/d/Ansalon/goodlund/nethosak/city/local.h"#include <stdproperties.h>
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
    set_short("South road in Nethosak");
    set_long("@@long_descr"); 

    add_exit(MROOM + "temple_entrance","east",0);
    add_exit(MROOM + "road23","west",0);    
    reset_mithas_room();
}

string
long_descr()
{ 

   return tod_descr()+ "You are standing on the south"+
          "road in the city of Nethosak. The road "+
          "here is paved with small rocks, and the buildings "+
          "are made out of grey stones. The road continues to "+
          "the east towards the Temple of the Stars and "+
          "to the west, to a intersection. "+
          random_descr()+ " " +season_descr()+ "\n";
}

