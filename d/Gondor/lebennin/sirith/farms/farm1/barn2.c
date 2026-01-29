/*
 * /d/Gondor/lebennin/sirith/farms/farm1/barn2.c
 * barn of large farmstead in southern lebennin
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 */

#pragma strict_types

#include <stdproperties.h>		/* for ROOM_I_LIGHT	*/
#include "/d/Gondor/defs.h"
#include "../defs.h"			
#include "/d/Gondor/common/mordor/sys/clock.h"

inherit "/d/Gondor/lebennin/sirith/room";

#define	PASTURE_TEMPLATE	(SIRITH_FARMS_DIR+"fields/pasture%d")
#define	NCOWS	4
static object	*Cows = allocate(NCOWS);
static object	Bull;

public void	create_sirith();
public void	reset_room();
public void	init();
public void	sunrise();		/* move cattle to pasture*/
public void	sunset();		/* move cattle to barn	*/
public int	do_drink(string arg);	/* handle attempts to drink */


/*
 * Function name:	create_sirith
 * Description	:	set up the room
 */
public void
create_sirith()
{
    set_short("a large barn");
    set_long(BSN("A large barn. This end of the barn appears "+
	"to be a livestock pen. A water trough runs "+
	"along the north wall, and a long open rack "+
	"on the west wall is filled with hay."));

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(OBJ_I_CONTAIN_WATER, -1);	/* water trough */

    add_exit("barn1", "east", 0, 2);
    set_no_exit_msg( ({ "north", "northeast", "southeast",
	"south", "southwest", "west", "northwest", "up", "down" }), 
	BSN("You wander around the barn, but do not find "+
	    "anything of interest.") );

    add_item( ({ "barn", "pen" }), long);
    add_item( ({ "trough", "water trough", "water" }),
	BSN("The water looks reasonably clean."));
    add_item( ({ "rack", "hay", "hay rack", "manger" }),
	BSN("The rack is filled with hay."));

    add_item( ({ "floor", "ground", "dirt" }),
	BSN("The floor is just firmly packed dirt."));
    add_item( ({ "ceiling" }),
	BSN("The ceiling is high above your head."));
    add_item( ({ "north wall", "east wall",
		 "south wall", "plank", "planks" }),
	BSN("The walls are built of wide grey planks."));
    add_item( ({ "wall", "walls", "west wall" }),
	BSN("The walls are built of wide grey planks. "+
	    "A hay rack is fastened to the west wall."));

    add_cmd_item( ({ "hay", "hayrick", "hayricks", "mound", "mounds" }),
	({ "smell", "sniff" }),
	BSN("The hay tickles your nose, causing you to sneeze violently."));

    add_cmd_item( ({ "hay" }), ({ "get", "take" }),
	BSN("You reach to pull some hay from the rack, but the cloud "+
	    "of hay dust that falls into your face dissuades you "+
	    "from the attempt."));

/*
    if (!objectp(find_object(SIRITH_MASTER)))
	SIRITH_MASTER->create_object();
*/
    reset_room();
    CLOCK->notify_dawn(sunrise);
    CLOCK->notify_dusk(sunset);
} /* create_sirith */


/*
 * Function name:	reset_room
 * Description	:	replace cattle if necessary
 */
public void
reset_room()
{
    string timestr = tod();

    ::reset_room();
    if (timestr == "night" ||
	timestr == "evening" ||
	timestr == "dusk")
    {
	clone_npcs(Cows, SIRITH_FARMS_DIR+"npc/cow", 4.0, 
	    (SIRITH_FARMS_DIR+"farm1/barn2"));
	Bull = clone_npc(Bull, SIRITH_FARMS_DIR+"npc/bull",
	    (SIRITH_FARMS_DIR+"farm1/barn2"));
    }
    else
    {
	/* want them in the pasture, so call clone_npcs() from there */
	Bull = call_other((SIRITH_FARMS_DIR+"fields/pasture2"),
	    "make_cattle", Cows, Bull);
	Cows->set_random_move(120);
	Bull->set_random_move(120);
    }
} /* reset_room */


/*
 * Function name:	init
 * Description	:	add 'drink' action
 */
public void
init()
{
    ::init();
    add_action(do_drink, "drink");
} /* init */


/*
 * Function name:	sunrise
 * Description	:	move cattle to pasture when sun comes up
 */
public void
sunrise()
{
    int		i, n;
    object	env, *cattletomove;

    CLOCK->notify_dawn(sunrise);
    cattletomove = ({ });
    for (i = 0; i < NCOWS; ++i)
    {
	/* only move cattle that aren't fighting and aren't already
	 * in the pastures.
	 */
	if (objectp(Cows[i]) &&
	    !objectp(Cows[i]->query_attack()) &&
	    objectp(env = ENV(Cows[i])) &&
	    !sscanf(file_name(env), PASTURE_TEMPLATE, n))
	{
	    cattletomove += ({ Cows[i] });
	}
    }
    if (objectp(Bull) &&
	!objectp(Bull->query_attack()) &&
        objectp(env = ENV(Bull)) &&
        !sscanf(file_name(env), PASTURE_TEMPLATE, n))
    {
	cattletomove += ({ Bull });
    }

    /* to do this right, would walk the cattle from the barn to the
     * pasture (assuming they're in the barn, of course), but i don't
     * think it's worth the trouble.
     */
    cattletomove->move_living("away",
	(SIRITH_FARMS_DIR+"fields/pasture2"), 1, 1);
    cattletomove->set_restrain_path(LIVESTOCK_RESTRAIN);
    cattletomove->set_random_move(120);
} /* sunrise */


/*
 * Function name:	sunset
 * Description	:	move cattle to barn when sun goes down
 */
public void
sunset()
{
    int		i, n;
    object	env, *cattletomove;

    CLOCK->notify_dusk(sunset);
    cattletomove = ({ });
    for (i = 0; i < NCOWS; ++i)
    {
	/* only move cattle that aren't fighting and aren't already
	 * in the barn.
	 */
	if (objectp(Cows[i]) &&
	    !objectp(Cows[i]->query_attack()) &&
	    ENV(Cows[i]) != TO)
	{
	    cattletomove += ({ Cows[i] });
	}
    }
    if (objectp(Bull) &&
	!objectp(Bull->query_attack()) &&
	ENV(Bull) != TO)
    {
	cattletomove += ({ Bull });
    }
    /* again, this is the cheap way ... */
    cattletomove->move_living("away", TO, 1, 1);
} /* sunset */


/*
 * Function name:	do_drink
 * Description	:	handle attempts to drink from trough
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	0 on success, !0 on failure
 */
public int
do_drink(string arg)
{
    int amount;

    if (arg != "water from trough" &&
	arg != "from trough" &&
        arg != "water from the trough" &&
	arg != "from the trough")
    {
	NF0("Drink what?\n");
    }
    amount = TP->query_prop(LIVE_I_MAX_DRINK) / 20;
    if (TP->drink_soft(amount))
    {
	write("You drink a mouthful of warm water from the trough.\n");
    }
    else
    {
        write("You cannot drink more water just now.\n");
    }
    return 1;
} /* do_drink */
