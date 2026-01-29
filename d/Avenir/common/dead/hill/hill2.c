// file name: hill2
// creator(s): Ilyian (28 August, 1995)
// last update:
// purpose:
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/dead/dead";
#include "../dead.h"

create_room()
{
hill_long("The hillside continues to the north and the "
         +"south, and drops down into the marsh to the "
         +"west. East is a cobbled path.");

ahdown(HILL+"hill1","south");
AE(HILL+"hill3","north",0,1);
ahdown(MARSH+"marsh39","west");
AE(PATH+"path10","east",0,3);

reset_room();
}

reset_room()
 {
    hill_reset();
 }
