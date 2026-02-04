inherit "/d/Terel/sorgum/tomb/gpath_room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

create_room()
{
    ::create_room();
    add_exit(TOMBDIR + "gpath05", "south", 0);
}

