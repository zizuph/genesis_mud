#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Corridor end in the stronghold");
 set_long("You are in the end of the dark corridor leading south. "+
   "Smaller corridors continue southwest and southeast , while to "+
   "northwest and northeast you see some kind of lookout towers. "+
   "Arch leads back to corridor to south.\n");

 add_item("arch","It leads south , where the corridor seem to start.\n");
 add_item("flag","Flag of Karg Empire flows slightly in gusts of "+
   "wind.\n");

 add_exit(STRHOLD_LVL1+"cor7","south");
 add_exit(STRHOLD_LVL1+"cor9","southwest");
 add_exit(STRHOLD_LVL1+"cor28","southeast");
 add_exit(STRHOLD_LVL1+"tower1","northwest");
 add_exit(STRHOLD_LVL1+"tower2","northeast");
}

