// file name: marsh26
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

am("31","north");
am("23","south");
am("25","west");
am("27","east");

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
