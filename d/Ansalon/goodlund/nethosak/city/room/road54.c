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
   
    add_exit(MROOM + "road55","east",0);
    add_exit(MROOM + "road53","west",0);      
    reset_mithas_room();
}

string
long_descr()
{ 

   return tod_descr()+
   "The road here is paved with small rocks, and the buildings "+
   "are made out of grey stones. A large stone statue decorate "+
   "the center of the street here. It's covered with moss and "+
   "partly eroded. To the northeast a huge building "+
   "has been build, and you realize that it must be where the "+
   "minotaur Emperor lives. Far to the south the forest of Mithas "+
   "flows gently over the green landscape, almost like a river. "+
   "The road continues to the west towards the main gate of the "+
   "palace and to the west."+
   season_descr()+ "\n";

}


