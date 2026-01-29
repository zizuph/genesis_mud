inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

void
create_room()
{
    ::create_room();

    set_short("Lounge");
    set_long(BS("\nThis is a large room which looks like it's used for "
       +"relaxing in.  In the centre there is a table with some cards "
       +"lying on it.  The north wall houses a large hearth  A windows "
       +"in the far wall provides plenty of light.\n\n"));

    add_exit(FARM(ghouse/hall1), "east", 0, 0, 0);

    add_prop(ROOM_I_INSIDE, 1);

    add_item("table", BS("\nThe table stands a couple of feet high.  It is "
       +"crafted from dark wood with ornately carved legs.\n\n"));

    add_item(({"card","cards"}), BS("\nA closer looks at the cards show them "
       +"to dipict scenes of torture.  What kind of people would use these "
       +"as a form of entertainment?\n\n"));

    add_item("windows", BS("The window looks out over the sea.\n\n"));
}

