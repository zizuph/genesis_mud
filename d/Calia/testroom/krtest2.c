
/* Kroug room test room */

#include "testroom.h"
inherit "/d/Calia/std/kr_room";


void
create_room()
{
    set_short("Kroug test room 1");
    set_long("This is kroug test room 2.\n");

    add_exit(TR+"krtest1", "west");
}
