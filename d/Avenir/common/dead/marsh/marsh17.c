// file name: marsh17
// creator(s): Ilyian (24 August, 1995)
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
marsh_long(randmarsh[random(sizeof(randmarsh))]+" To the "
          +"north and the east you can just make out "
          +"a cobbled path.");

AE(PATH+"path5","north",0,3);
am("12","south");
am("16","west");
AE(PATH+"path4","east",0,3);

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
