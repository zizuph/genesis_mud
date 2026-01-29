
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/farlong.h"

void
create_room()
{
    set_short("Esgaroth pier");
    set_long(break_string("This is a large, sturdily-built wooden pier"
	+" at the south end of the city of Esgaroth.  It extends out into"
	+" the Long Lake, where a river ship docks regularly.  The wooden"
    +" way extends northward into the city, while a small sign "
    +"stands nearby."
	+"\n", 75));

    add_item("sign", "There is writing on it.\n");

    add_cmd_item("sign", "read", "The sign reads: The river ship southeast toward Rhun lands here.\n");

	AE(ESG_DIR+"es-6-13","north",0);
}

