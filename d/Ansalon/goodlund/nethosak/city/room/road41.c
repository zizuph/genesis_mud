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
    set_short("Center road in Nethosak");
    set_long("@@long_descr"); 
 
    add_item(({"road", "crowded road"}), "The road has been made "+
          "out of small grey rocks that has been scattered all "+
          "over the place.\n");

    add_item(({"forest"}), "The forest doesn't look very big "+
          "it stretches itself towards to south and southeast.\n");

    add_item(({"tree", "oak tree"}), "The huge oak tree looks very "+
          "old, but it's a bit hard to get a good view of it from "+
          "here.\n"); 

    add_item(({"wagons", "tents"}), "The wagons and tents are very "+
          "small and made out of some wooden material. It's a bit "+
          "hard to get a good view of it from here.\n");
    add_exit(MROOM + "square8","north",0);
    add_exit(MROOM + "road40","south",0);    
    add_invis_exit(MROOM + "alley2","west","@@enter_alley");
    reset_mithas_room();
}

string
long_descr()
{  

     return tod_descr()+ "You stand on a crowded road that stretches itself "+ 
      "north towards the marketsquare. Far to the south you see one of the "+
      "two citygates that leads towards a small forest, south of the "+
      "city. A bit to the south a great oak tree rises above the houses "+
      "and stores. To the north you notice some wooden wagons and "+
      "small tents, that must make out the marketsquare of "+
      "Nethosak. " +season_descr()+ "\n";
}

int
enter_alley()
{
    write("You enter the small alley.\n");
    return 0;
}

