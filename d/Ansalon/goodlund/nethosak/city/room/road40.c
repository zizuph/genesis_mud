#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include <stdproperties.h>
inherit MITHAS_OUT;

void
create_mithas_room()
{
    set_short("Center road in Nethosak");
    set_long("@@long_descr"); 

    add_exit(MROOM + "road41","north",0);
    add_exit(MROOM + "road39","south",0);
    add_invis_exit(MROOM + "alley","west","@@enter_alley");  
   
}

string
long_descr()
{ 
     return tod_descr()+ "You stand on a crowded road that stretches itself "+ 
      "towards the marketsquare. Far to the south you see one of the two "+
      "citygates that leads towards the small forest, south of the "+
      "city. A bit to the south a great oak tree rises above the houses "+
      "and stores. To the north you notice some wooden wagons and "+
      "small tents, that must make out the marketsquare of "+
      "Nethosak." +season_descr()+ "\n";
}

int
enter_alley()
{
    write("You enter the small alley.\n");
    return 0;
}


