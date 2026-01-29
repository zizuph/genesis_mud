// file name: marsh58
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
marsh_long(randmarsh[random(sizeof(randmarsh))]+" You can "
    +"make out a narrow road to the west and the south.");

am("61","north");
AE(PATH+"path4","south",0,3);
am("59","east");
AE(PATH+"path5","west",0,3);

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
