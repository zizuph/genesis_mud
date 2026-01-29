inherit "/std/room";

#include "/d/Roke/common/defs.h"

create_room()	{

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
             "blood, no doubt that of those who owned them.\n");
    add_item("dust", "It scatters around with no will of its own.\n");
    add_item(({"archway", "chamber", "dark chamber", "open archway"}),
             "It seems to beckon you with thoughts of violence.\n");

add_exit("/d/Roke/varl/atuan/mountains/m8","east");
	add_exit(GLAD_DIR+"ent1","north",0);
	add_exit(GLAD_DIR+"joinroom.c","west",0);

}

