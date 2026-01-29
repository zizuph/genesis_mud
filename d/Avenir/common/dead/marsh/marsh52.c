// file name: marsh52
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
marsh_long(randmarsh[random(sizeof(randmarsh))]+" To the north you "
   +"can see a small, dry hillock.");

AI(({"hill","hillock"}),"It is a small hill that rises up to the "
   +"north. You cannot make out anything on it from here.\n");

am("_hill","north");
am("48","south");
am("51","west");
am("53","east");

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
