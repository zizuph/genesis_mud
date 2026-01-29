#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_morgul_room()
{
    set_extraline("Here in the basement, it is completely dark. Moreover, " +
    "the dark stones that make the walls seem to swallow any light " +
    "that comes down here. There is a ladder leaning on one wall. Above " +
    "the ladder you can see a hole in the ceiling. A narrow passage leads " +
    "east.");
  add_item(({"ladder"}), BSN(
    "A rickety ladder is leaning on one wall. "));
  add_item(({"wall","walls","stones"}), BSN(
    "The walls of the basement are made from smooth black rock. It looks like " +
    "this cellar was built into the living rock of the Ephel Duath. The walls " +
    "are so black, it seems as if they are swallowing any light that might come " +
    "down here. Leaning on one wall is a ladder. "));
    set_road(5);
    set_side("northeast");

    add_exit(MORGUL_DIR + "city/tunnels/pass02","east","@@check_exit",1);
    add_prop(ROOM_I_LIGHT,-1);
    clone_object(MORGUL_DIR + "city/doors/b6trapdown")->move(TO);
}

