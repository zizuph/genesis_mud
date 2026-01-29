/*
 * /d/Gondor/rohan/horn/burg/tow_enter.c
 *
 * Modification history:
 *
 * 21-Dec-97, Gnadnar: general cleanup
 */

inherit "/d/Gondor/std/room.c";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

#define OTHER_ROOM ROH_DIR + "horn/gorge/ofield6"
#define	NGUARDS	3

static object	*Guards = allocate(NGUARDS);
static object	Erkenbrand;

/* Prototypes */
public object	query_erkenbrand();
public object	*query_guards();
public void	move_guards();

public object query_erkenbrand()	{ return Erkenbrand; }
public object * query_guards()		{ return Guards; }

public void
create_gondor()
{
    object door;

    set_short("Tower entrance");
    set_long(BSN("A round room in the tower. On the east "+
    "side of the room is a highbacked chair behind a large table. "+
    "Above the chair hangs a banner. Around the room, on the wall, some "+
    "tapestries hang. The wall is limewashed white. "+
    "Beside the door stands an armsrack. On the other side of the door "+
    "there is an opening to a spiral staircase, turning "+
    "counter-clockwise, leading up and down."));

    add_item("banner",BS("The banner of Rohan displays a white horse running "+
    "on a green field.\n"));
    add_item("tapestries",BS("On the tapestries depict some of the heroes "+
    "of Rohan. Most conspicuous is the one of Helm Hammerhand, the long "+
    "dead hero-king, who died defending the Hornburg.\n"));
    add_item("armsrack","The armsrack is empty.\n");
    add_item(({"chair","table"}),"The chair and table are made of oak; they "+
    "have seen much use.\n");

    add_prop(ROOM_I_INSIDE, 1);

    door = clone_object(ROH_DIR+"horn/doors/tower_door_out"); 
    door->move(TO);

    reset_room();
}


public void
reset_room()
{
    ::reset_room();
    Erkenbrand = clone_npc(Erkenbrand, (ROH_DIR+"horn/npc/erkenbrand"));
    /* do these individually so we have 3 guards ready to hang the orc.
     * if we clone 'em with clone_npcs() and a delay, erkenbrand
     * may only get 1 guard to go with him.
     */
    Guards[0] = clone_npc(Guards[0], (ROH_DIR+"horn/npc/g_guard"));
    Guards[1] = clone_npc(Guards[1], (ROH_DIR+"horn/npc/g_guard"));
    Guards[2] = clone_npc(Guards[2], (ROH_DIR+"horn/npc/g_guard"));
}


public void
move_guards()
{
    object room;

    if ( !objectp(room = find_object(OTHER_ROOM)) )
	return;
    if ( objectp(Erkenbrand) )
    {
	Erkenbrand->move_living("with some guards who came to fetch him",
    	    OTHER_ROOM);
	Guards->move_living("following Erkenbrand", OTHER_ROOM);
    }
    else
	Guards->move_living("away", OTHER_ROOM);
}
