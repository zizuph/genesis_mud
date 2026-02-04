inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

create_room()
{
    set_short("cottage library");
    set_long(
	"This room is filled with ceiling high bookshelves stocked " +
        "with books and neatly stacked scrolls.  Above the doorway " +
        "is a delightful Doric cpedimant " +
        "magnificently carved in an ornamental fashion with a scroll " +
        "and urn top.  Above the the crowded bookshelves at intervals " +
	"are portraits.\n"
    );

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(SORGUMDIR + "workroom", "workroom", 0);
}


