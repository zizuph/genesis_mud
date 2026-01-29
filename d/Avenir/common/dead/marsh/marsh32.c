// file name: marsh32
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
marsh_long(randmarsh[random(sizeof(randmarsh))]+" The ground "
          +"begins to rise steeply to the north.");

AE(HILL+"hill1","north",0,5);
am("27","south");
am("31","west");
am("33","east");

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
