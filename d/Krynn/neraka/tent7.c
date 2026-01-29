/* A beer tent in Tantallon, coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>

inherit TANTALLON_INSIDE;


reset_tantallon_room()
{
    object ob;
    if (!present("mary"))
    {
        ob = clone_object(MON + "mary");
        ob->move(TO);
    }
}

create_tantallon_room()
{
    set_short("Inside a tent");
    set_long(BS(
        "You stand inside one of the tents of Tantallon. You can see that " +
	"someone lives here since there is a bed in one corner and a small " +
	"fire in the middle. But that's about what's in here. The " +
	"citizens of Tantallon can't be very rich you notice." +
	"",SL));

    add_item("bed",
        "It's made out of some blankets.\n");
    add_item("fire",
        "It is responsible for the light and the heat in this tent.\n");

    add_exit(TDIR + "city6", "west", 0);
    reset_room();

    INSIDE;
}

