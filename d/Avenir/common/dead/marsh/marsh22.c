// file name: marsh22
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
marsh_long(randmarsh[random(sizeof(randmarsh))]+" To the west "
          +"the fog seems to be a bit less dense.");

am("25","north");
am("19","south");
AE(PATH+"shore10","west",0,3);
am("23","east");

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
