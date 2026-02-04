/*
inside fireplace
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)    break_string(message, 70)
#define TP             this_player()

void
create_room()
{
    set_short("inside fireplace");
    set_long(BS("You find yourself inside a narrow, dirty fireplace south " +
	"of the dining room. There's still a lot of ashes lying around " +
	"as if a fire would have burnt here recently.\n"));
   
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT,  0);	
   
    add_exit(MANSION + "rooms/dining", "north", 0);

    add_item("cobwebs", "The lack of cobwebs makes you feel very uneasy.\n");
    add_item("dust", "There is no dust to be seen anywhere.\n");
}

