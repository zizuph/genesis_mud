// file name: marsh54
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
marsh_long(randmarsh[random(sizeof(randmarsh))]+" To the west "
   +"you can make out a narrow cobbled road, and from the east "
   +"and south, the noise from the sea can be heard.");

am("55","north");
AE(PATH+"shore27","east",0,3);
AE(PATH+"path2","west",0,3);
AE(PATH+"shore26","south",0,3);

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
