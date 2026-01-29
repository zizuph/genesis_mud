#include "defs.h"
inherit STD_ROOM;

#include <stdproperties.h>
#include <macros.h>

void
create_room()
{
    add_prop(ROOM_I_INSIDE,1); 
    ::create_room();
    set_short("The Bloody Skull Inn");
    set_long("You are the back area of the Bloody Skull Inn. Dark, shady "+
    "booths line the walls, where you see people talking and drinking. "+
    "A few tables are scattered about in the center. A public board is "+
    "here for travelers to leave messages to each other.\n");
    add_item("chairs",
	"They are made out of wood as is the rest of the place.\n"); 
    add_item("tables", "They are darkened with spilled beer.\n");
    add_item("booths","They are dark and shady, a place where you "+
    "would think dark deals are discussed.\n");
    clone_object(DRAKMERE_OBJ_DIR + "drakmere_board")->move(TO);
    add_exit(DRAKMERE_SHOP_DIR + "inn","west",0);
}

int *
query_coordinates()
{
    return ({68, 0, 0});
}
