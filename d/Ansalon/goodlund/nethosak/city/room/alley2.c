#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include <stdproperties.h>
inherit MITHAS_OUT;

void
create_mithas_room()
{
    set_short("Dark alley");
    set_long("@@long_descr"); 

    add_invis_exit(MROOM + "road41","east","@@enter_street");
    add_invis_exit(MROOM + "alley","south","@@enter_alley");  
   
}

string
long_descr()
{ 
     return tod_descr()+ "You are standing in a very dark "+
           "alley in the city of Nethosak. Unlike the rest "+
           "of the city dirt and garbage fill the street. "+
           "The dark alley continues to the south, and to "+
           "the east the street leads back to the main "+
           "road. " +season_descr()+ "\n";
}

int
enter_street()
{
    write("You enter the crowded street of Nethosak.\n");
    return 0;
} 

int
enter_alley()
{
    write("You continue walking in the small alley.\n");
    return 0;
}

