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
    set_short("Southwest road in Nethosak");
    set_long("@@long_descr"); 

    add_item(({"volcano","volcanos"}), "The "+
          "four great peeks are located far to the south, you "+
          "think you can see something flying near them.\n");
 
    add_item(({"arena","cirkus", "great building"}),
          "You observe that the great building, is "+
          "the imperial arena of the minotaurs, also "+
          "knows as the Great Circus, it is within this "+
          "building that minotaurs and other beasts "+
          "battle to show the strength that they possess "+
          "This is also the place were the Emperor and "+
          "the current Arena Champion battle to the death.\n");

    add_exit(MROOM + "road46","southeast",0);  
    add_exit(MROOM + "road48","north",0);
    reset_mithas_room();
}

string
long_descr()
{ 
    return tod_descr()+ "You are standing on the southwest "+
          "road in the city of Nethosak. The road "+
          "here is paved with small rocks, and the buildings "+
          "are made out of grey stones. The road continues to "+
          "the north and southeast further down the street. " +
          "To the northeast a great building rises, it's tall "+
          "arches stretches themselves high into the air, loud "+
          "cheers and screams can be heard from within. "+
          "To the west, beyond the citywall you notice a small "+
          "forest and the wooden pier of Nethosak. A bit to the "+
          "north you see a crowded intersection. "+
          season_descr()+ "\n";
}

