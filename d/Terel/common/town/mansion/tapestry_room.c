inherit "/std/room.c";
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <macros.h>

#define BS(message)    break_string(message, 70)
#define TP             this_player
#define TO             this_object

void
create_room()
{
    object  ob;
    
    set_short("The Room of Tapestries");
    set_long(BS("The red carpet in this room may once have been plush; "
    + "now it is decayed and motheaten. The room is unremarkable except "
    + "for the still-exquisite decoration.\n"));
    
    add_exit(MANSION +"wing_w5","south",0,1);

    add_item("carpet","The carpet is worn-down and decayed, hardly worth looking at.\n");
    
    ob = clone_object(MANSION+"tapestry3");
    ob->move(TO());
    ob = clone_object(MANSION+"tapestry2");
    ob->move(TO());
    ob = clone_object(MANSION+"tapestry1");
    ob->move(TO());
}
