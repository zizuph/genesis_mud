// file name: marsh36
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
          +"east rises a steep hill.");

add_hill();

AE(HILL+"hill1","east",0,5);
am("39","north");
am("31","south");
am("35","west");

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
