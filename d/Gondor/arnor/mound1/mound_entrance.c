/*
 * Coded by Tigerlily
 * March 2006
 * Tombs of Arnor
 */
#pragma strict_types

#include "arnor_defs.h"
inherit NEW_ARNOR_ROOM;

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/sys/tasks.h"
#include "/sys/ss_types.h"
#include "arnor_defs.h"

/*
static object *Orc = allocate(5);
*/
static object *Troll = allocate(1);

string inscription();

void
reset_room()
{
    int i;

    set_searched(0);
/*
    clone_npcs(Orc, NPC_DIR + "std_orc", -1.0);
*/
    clone_npcs(Troll, ARNOR_NPC + "medium_troll", -1.0);
/*
    if (sizeof(Orc))
    {
        for (i = 0; i < sizeof(Orc); i++)
        Orc[i]->clear_chat();
    }
*/
}

public void
create_arnor()
{
    set_short("A stone entryway");
    set_long("Behind the hedge a stone entryway cuts " +
        "into the hillside. An arched lintel over the doorway "+
        "bears an inscription, but it has been damaged beyond " +
        "recognition. The door swings on one hinge, as though it had " +
        "been hit with an enormous sledge hammer. Piles of rubble " +
        "and waste lie scattered on the ground.\n");
    add_item(({"lintel", "inscription", "arched lintel"}),
        "The lintel arches over the entryway and once contained an " +
        "inscription. You strain your eyes to read it. " 
        + VBFC("inscription") + "\n");
    add_item(({"doorway", "door", "hinge"}), "The great stone door " +
        "hangs from one hinge. It does not block the passage, so you " +
        "could enter here.\n");
    add_item(({"rubble", "piles of rubble", "piles", "waste"}),
        "Clearly the contents of the mound have been plundered. " +
        "Remnants of fine tapestries, shards of porcelain urns, and "+
        "other defiled objects lie in a heap on the ground.\n");
    add_item("hedge", "There is an exit out through the hedge.\n");

    add_exit(MOUND1 + "mound2", "up", 0, 0);
    add_exit(ND_OFFROAD + "offw1_8", "out", 0, 0);
    add_grass_room_items();
    reset_room();
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
    {
        sky_add_items();
        start_room_tells();
    }   
}

string
inscription()
{

    object tp = this_player();
    int success;

    success = tp->resolve_task(TASK_HARD, ({TS_WIS, TS_INT, SS_LANGUAGE}));


    if (success > 110)
        return "You read, Arado#, Chieftain of the D####dain, ####-2##0";

    if (success > 50)
        return "The inscription is somewhat blurred, but you " +
            "can make out A&&&#, #######, ####-####";
    if (success > 0)
        return "You can only make out a few letters that " +
            "look like ancient Numenorean."; 
    // else

    return "The inscription is too eroded by time for you to read.";
}
