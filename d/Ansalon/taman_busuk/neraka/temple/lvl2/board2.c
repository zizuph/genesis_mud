/* This room is supposed to contain the commonboard in the PoT
 */

#pragma strict_types

#include "../defs.h"
#include <macros.h>

inherit TEMPLE + "std_temple.c";

void
create_temple_room()
{
    object ob;

    ::create_temple_room();

     set_short("The common board room");
    set_long("This room is very bare and empty except for one large board " +
        "on the opposite side of the room from the entrance.\n");

    setuid();
    seteuid(getuid());
    
    if (!LOAD_ERR("/d/Genesis/obj/board"))
    {
        ob = clone_object("/d/Genesis/obj/board");
        ob->set_no_show_composite(1);
        ob->move(this_object());
    }
    
    add_exit( LVLTWO + "library.c", "northwest" );
}
