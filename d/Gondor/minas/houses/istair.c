inherit "/d/Gondor/common/room";
#include "/d/Gondor/defs.h"
#include <macros.h>
#include <stdproperties.h>

create_room()
{
    set_short("A large stairway in a house");
    set_long("not done yet.\n");
    
    add_prop(ROOM_I_INSIDE,1);


    add_exit(MINAS_DIR +"houses/ihall2","up",0);
    add_exit(MINAS_DIR +"houses/ihall","down",0);
}

