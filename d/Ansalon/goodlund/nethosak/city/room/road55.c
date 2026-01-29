#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include <stdproperties.h>
inherit MITHAS_OUT;

object dwarf;

void 
reset_mithas_room()
{
    if(!objectp(dwarf))
    {
      dwarf = clone_object(MNPC + "female_g_dwarf");
      dwarf->move(this_object());
   }
}

void
create_mithas_room()
{
    set_short("Northern road in Nethosak");
    set_long("@@long_descr"); 
   
    add_exit(MROOM + "road54","west",0);
    add_exit(MROOM + "road56","southeast",0);     
    reset_mithas_room();
}

string
long_descr()
{ 
   return tod_descr()+
   "The road here is paved with small rocks, and the buildings "+
   "are made out of grey stones. Heavy stone statues dominate "+
   "these roads, they have been placed alongside the road with "+
   "some trees and a few bushes. To the northeast a huge building "+
   "has been build, and you realize that it must be where the "+
   "minotaur Emperor lives. "+
   "The road continues to the west towards the main gate of the "+
   "palace and southwest."+
   season_descr()+ "\n";

}



