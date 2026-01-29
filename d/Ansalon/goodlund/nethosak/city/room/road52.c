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
    set_short("South of the Imperial Castle");
    set_long("@@long_descr"); 
   
    add_exit(MROOM + "road68","east",0);
    add_exit(MROOM + "road51","west",0);
    add_exit(MROOM + "road59","south",0);      
    reset_mithas_room();   
}

string
long_descr()
{ 

   return tod_descr()+
   "The road here is paved with small rocks, and the buildings "+
   "are made out of grey stones. Heavy stone statues dominate "+
   "these roads, they have been placed alongside the road with "+
   "some trees and a few bushes. A bit to the east, a large "+
   "iron gate prevents passage to the castle. The road stretches "+
   "itself to the east towards the gate, to the west and to the "+
   "south towards the center of Nethosak. "+
   season_descr()+ "\n";

}
