/* A beer tent in Tantallon, coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit TANTALLON_INSIDE;
#include <macros.h>

reset_tantallon_room()
{
    if (!present("chef", TO))
	clone_object(MON + "chef")->move(TO);
}

create_tantallon_room()
{
    set_short("In kitchen");
    set_long(BS(
        "You are in the rear of the Draco Inn. Here is where the food is " +
	"being prepared and occasionally some beer is being brewed. There " +
	"is a stove in one corner." +
	"",SL));

    add_item("stove", "It is hot but you can't see anything on it.\n");

    add_cmd_item("stove", ({"touch", "smell"}), ({
	"Ooooaaach, you burned your fingers.\n",
	"It smells of old food.\n"}));

    add_exit(TDIR + "tent2", "west", 0);

    reset_room();

    INSIDE;
}
