// file name: marsh28
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
marsh_long(randmarsh[random(sizeof(randmarsh))]);

am("33","north");
AE(PATH+"path7","east",0,3);
am("27","west");
AE(PATH+"path6","south",0,3);

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
