// file name: marsh18
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
marsh_long(randmarsh[random(sizeof(randmarsh))]+" You can "
          +"make out the faint sounds of waves.");

AE(PATH+"shore10","north",0,3);
am("13","south");
AE(PATH+"shore9","west",0,3);
am("19","east");

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
