#include "/d/Gondor/defs.h"
inherit (COMMON_DIR + "room");

#include <macros.h>
#include <stdproperties.h>
#include "locals.h"

void
create_room()
{
    set_short("A small cosy house");
    set_long("The room is small, though it has space for a table "+
      "in the middle of the room, with chairs around it. "+
      "North there is a doorway leading out.\n");

    INSIDE;  /* This room is a inside room */

    add_item("table","It is a wooden table where folks can eat.\n");
    add_item("chairs","You see the wooden chairs all the way around "+
      "the table.\n");
    add_item("doorway","The doorway is leading out into the garden.\n");

    add_exit(THORN_DIR + "garden","north","@@enter_garden",1);

}

enter_garden()
{
    write("You walk through the doorway out into the light.\n");
    return 0;
}
