/*
 * /d/Gondor/rohan/isengard/isen_gate.c
 *
 * Original version by unknown.
 *
 * Rewritten by Olorin on 8-Dec-1996.
 *
 * Copyright (c) 1996 by Christian Markus
 *
 * Modification log:
 *
 */
#pragma strict_types

#include "defs.h"

inherit ISEN_ROOM;

#include <macros.h>
#include <stdproperties.h>

#define DID_VISIT_ISENGARD "_ranger_visited_isengard"

static object  Guard1, 
               Guard2;

public void
reset_room()
{
    int     isen_stage = Master->query_isen_stage();

    if ((isen_stage <  ROHAN_STAGE_BATTLE_END) || 
	(isen_stage == ROHAN_STAGE_VICTORY))
    {
	if (!objectp(Guard1))
	{
	    Guard1 = clone_object(ISEN_DIR + "npc/dunlend");
	    Guard1->arm_me();
	    Guard1->move_living("down", TO);
	    if (objectp(Guard2)) 
		Guard1->team_join(Guard2);
	}
	if (!objectp(Guard2))
	{
	    Guard2=clone_object(ISEN_DIR+"npc/dunlend");
	    Guard2->arm_me();
	    Guard2->move_living("down", TO);
	    if (objectp(Guard1)) 
		Guard1->team_join(Guard2);
	}
    }
    else
    {
	// No guards while the Ents rule in Isengard:
	if (objectp(Guard1))
	{
	    Guard1->move_living("north", VOID);
	    Guard1->remove_object();
	}
	if (objectp(Guard2))
	{
	    Guard2->move_living("north", VOID);
	    Guard2->remove_object();
	}
    }
}	

public int
message()
{
    if (TP->query_wiz_level()) 
    {
        write("This exit is still closed for mortals, wizard.\n");
        return 0;
    }
    if (objectp(Guard1) || present(Guard2))
    {
	write("The guards stop you from approaching the Gates.\n");
	return 1;
    }
    else
    {
	write("The gates are closed and silent; you won't get in yet.\n");
	return 1;
	/*
	   write("You pass into the tunnel, peering fearfully at the murderholes.\n");
	   return 0;
	 */
    }
}

public int query_is_gate() { return 1; }

public void
create_isengard()
{
    set_short("the gates of Isengard");
    add_item(({"gates","gate"}),
    "The great gates of the fortress of Isengard are made of solid black\n"+
    "iron. Sturdily wrought hinges of a stronger metal support the gates\n"+
    "and strengthen the already solid doors. Twenty feet tall, and equally\n"+
    "wide, the gates of Isengard lead through the volcanic ring of Isengard.\n");
    add_item(({"fortress", "isengard", "orthanc", "castle"}),
      BSN("The fortress is ancient, but still seems to be maintained "
    + "and guarded. Carved out of a volcano long dead, the outer "
    + "wall is more than a hundred feet high. Beyond the wall you see "
    + "a tall dark tower: The Castle Orthanc, where Saruman lives."));
    add_exit(ISEN_DIR + "tunnel1",    "north",message);
    add_exit(ISEN_DIR + "isenroad/isenroad4", "south", 0);
/*
   (ISEN_DIR + "arrowroom1")->load_me();
   (ISEN_DIR + "arrowroom2")->load_me();
   (ISEN_DIR + "arrowroom3")->load_me();
 */
    reset_room();
}

/*
 * Function name: query_isen_desc
 * Description:   Give a stage dependent description of the room. 
 *                Has to be defined in the rooms. This is just a dummy
 *                function.
 * Argument:      stage - The the Isen_Stage variable.
 * Returns:       The room description for this stage.
 */
public string
query_isen_desc(int stage)
{
    string  desc =
	"Before you is a great fortress, commonly known as Isengard, "+
	"or Angrenost. Carved out of an extinct volcano, its outer ring-"+
	"wall is more than a hundred feet high.";

    switch (stage)
    {
    case ROHAN_STAGE_PEACE..ROHAN_STAGE_BATTLE_END:
    case ROHAN_STAGE_DEFEAT:
	desc += " The exterior gates are protected by two huge " +
	    "watch towers hewn out of the rock of the ring-wall, " +
	    "in addition to the guard outside the gates.";
	break;
    case ROHAN_STAGE_VICTORY:
	desc += " The gates have been destroyed by tremendous " +
	    "force. Only ruins remain of the watch towers and " +
	    "the tunnel leading through the ring-wall has " +
	    "collapsed, making entry impossible.";
	break;
    }
    return desc;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (IS_RANGER(ob))
        ob->add_prop(DID_VISIT_ISENGARD, 1);
}

