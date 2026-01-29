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
    set_short("Main Street in Nethosak");
    set_long("@@long_descr"); 

    add_item(({"volcano","volcanos"}), "The "+
          "four great peeks are located far to the south, you "+
          "think you can see something flying near them.\n");

    add_exit(MROOM + "road12","west",0);
    add_exit(MROOM + "road14","east",0);
    add_exit(MROOM + "wep_smith","north",0);       
    reset_mithas_room();
}

string
long_descr()
{ 

   return tod_descr()+ "You are standing on the main "+
          "street in the city of Nethosak. The road "+
          "here is paved with small rocks, and the buildings "+
          "are made out of grey stones. The road continues to west "+
          "and east. To the north you see a stonebuilding with a "+
          "wooden sign above the door. The smell of hot metal fills "+
          "the air and a thick black smokes comes out of the "+
          "chimney. Far to the east you see the great plains and "+
          "forests that surround this city." +season_descr()+ "\n";

}

