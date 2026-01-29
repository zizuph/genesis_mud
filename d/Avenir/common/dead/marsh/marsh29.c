// file name: marsh29
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
marsh_long(randmarsh[random(sizeof(randmarsh))]+" To the west and "
          +"south, the fog thins out a bit, revealing a path "
          +"that runs along the shore.");

am("34","north");
AE(PATH+"shore11","south",0,3);
AE(PATH+"shore12","west",0,3);
am("30","east");

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
