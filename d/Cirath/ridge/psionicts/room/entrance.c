/* entrance.c: Entrance to gladiator guild. Serpine, 4-24-95. */
#pragma save_binary

inherit "/d/Cirath/std/room";
#include "defs.h"
#include <formulas.h>
 
create_room()
{

    set_short("entrance hall");
    set_long("You stand within a long, large hall, the walls of "+
             "which are filled with banners. A bitter "+
             "breeze pushes dust in from the open archway that leads "+
             "east and out of the building, and echoes of battle come "+
             "from the north. To the west is a small, dark chamber. "+
             "It is obvious that this is the home of the deadliest "+
             "warriors of the land: The Gladiators of Athas.\n");

    add_item(({"banners", "banner", "wall", "walls"}), "Collected in "+
             "countless battles they are the symbols of foes vanquished "+
             "by the warriors who reside here. Many are matted with "+
             "blood, no doubt of those who owned them.\n");
    add_item("dust", "It scatters around with no will of its own.\n");
    add_item(({"archway", "chamber", "dark chamber", "open archway"}),
             "It seems to beckon you with thoughts of violence.\n");

    add_exit(TYR+"market/rd_sw_03.c","east",0,1,0);
  add_exit(PSION_ROOM+"mainhall.c","north",0,1);
    add_exit(PSION_ROOM+"joinroom.c", "west", 0, 1);

    reset_room();
}
