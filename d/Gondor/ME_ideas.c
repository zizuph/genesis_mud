#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_gondor()
{
    set_short("this is the idearoom of the Middle Earth domains");
    set_long("The Middle Earth Idearoom.\n"+
        BSN("This is where members of the Middle Earth domains "
	    + "discuss topics that are important to Middle Earth "
	    + "as a whole. This includes but is not restricted to "
	    + "ideas for quests common to several domains, and "
	    + "the borders and connections between Middle Earth "
	    + "domains. There is a bulletin board here for this "
	    + "use. Exits lead to the workrooms of the Middle "
	    + "Earth domains."));

    add_prop(ROOM_I_INSIDE,1);

    add_exit("/d/Shire/workroom",     "northwest", 0, 0);
    /* Rhovanion is closed -- gnadnar
     * add_exit("/d/Rhovanion/workroom", "northeast", 0, 0);
     */
    add_exit("/d/Mordor/workroom",    "southeast", 
	     &RING_QUEST_MASTER->domain_closed());
    add_exit("/d/Gondor/workroom",    "south",     0, 0);

    clone_object(BOARD_DIR + "me_ideaboard")->move(TO);
}

public int query_prevent_snoop() { return 1; }
