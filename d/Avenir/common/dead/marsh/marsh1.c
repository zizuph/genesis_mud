// file name: marsh1
// creator(s): Ilyian (21 August, 1995)
// last update:
// purpose:
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/dead/dead";
#include "../dead.h"

create_room()
{
set_short("Grey Marsh");
marsh_long("To the east you think you can make out a narrow, cobbled "
          +"path.");

AE(PATH+"path2","east",0,3);
am("2","west");
am("12","north");
AE(PATH+"shore1","south",0,3);
reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();

}
