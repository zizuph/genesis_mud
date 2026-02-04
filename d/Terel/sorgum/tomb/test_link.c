inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"


create_room()
{
    set_short("test.");
    set_long(BSN(
       "This room test the link to the Sorgum area."
    ));

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(TOMBDIR + "meadow01", "north", "@@go_north");
}

go_north()
{
     write_file("/d/Terel/sorgum/log/visitors", capitalize(TP->query_name()) +
		" vistited (" + ctime(time()) + ")\n");
}
