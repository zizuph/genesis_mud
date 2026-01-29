/*
 * /d/Gondor/lebennin/sirith/farms/farm2/barn.c
 * barn of small farmstead in southern lebennin
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 */

#pragma strict_types

#include <stdproperties.h>	/* for ROOM_I_LIGHT	*/
#include "/d/Gondor/defs.h"
#include "../defs.h"			
#include "/d/Gondor/common/mordor/sys/clock.h"

inherit "/d/Gondor/lebennin/sirith/room";

#define	PASTURE_TEMPLATE	(SIRITH_FARMS_DIR + "fields/pasture%d")
#define	NSHEEP	4
static object	*Sheep = allocate(NSHEEP);
static object	Ram;

public void	create_sirith();
public void	reset_room();
public void	init();
public void	sunrise();		/* move sheep to pasture*/
public void	sunset();		/* move sheep to barn	*/
public int	do_drink(string arg);	/* handle attempts to drink */


/*
 * Function name:	create_sirith
 * Description	:	set up room
 */
public void
create_sirith()
{
    set_short("a small barn");
    set_long(BSN("A small barn. A low trough runs along the back wall, "+
	"and an overhead rack on the east wall is filled with hay."));

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);	/* barn has no door. not realistic, 
				 * perhaps, but westyard looked too
				 * cluttered with all those doors
				 */
    add_prop(OBJ_I_CONTAIN_WATER, -1);	/* water trough */

    add_exit("westyard", "south", 0, 2);
    set_no_exit_msg( ({ "north", "northeast", "east", "southeast",
	"southwest", "west", "northwest", "up", "down" }),
	BSN("You wander around the barn.") );

    add_item( ({ "barn" }), long);
    add_item( ({ "ground", "floor", "straw", "traces", "dung" }),
	BSN("The floor is firmly packed earth, scattered with straw "+
	    "and unmistakable traces of some kind of livestock."));
    add_item( ({ "trough", "water", "back wall", "north wall" }),
	BSN("The trough is filled with reasonably clean water."));
    add_item( ({ "wall", "walls", "ceiling", "plank", "planks" }),
	BSN("The walls and ceiling are built of wide grey planks."));
    add_item( ({ "rack", "east wall", "hay" }),
	BSN("The hay rack hangs just above head height on the east wall."));

    add_cmd_item( ({ "hay" }), ({ "get", "take" }),
	BSN("You reach to pull some hay from the rack, but the cloud "+
	    "of hay dust that falls into your face dissuades you "+
	    "from the attempt."));

/*
    if (!objectp(find_object(SIRITH_MASTER)))
    {
	SIRITH_MASTER->create_object();
    }
*/

    reset_room();
    CLOCK->notify_dawn(sunrise);
    CLOCK->notify_dawn(sunset);
} /* create_sirith */


/*
 * Function name:	reset_room
 * Description	:	replenish sheep
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
	clone_npcs(Sheep, (SIRITH_FARMS_DIR+"npc/sheep"), 4.0, 
	           (SIRITH_FARMS_DIR+"farm2/barn"));
	Ram = clone_npc(Ram, (SIRITH_FARMS_DIR+"npc/ram"),
		        (SIRITH_FARMS_DIR+"farm2/barn"));
    }
    else
    {
	/* want them in the pasture, so all clone_npcs from there */
	Ram = call_other((SIRITH_FARMS_DIR+"fields/pasture6"), "make_sheep",
		         Sheep, Ram);
	Sheep->set_random_move(120);
	Ram->set_random_move(120);
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
 * Description	:	move sheep to pasture when sun comes up
 */
public void
sunrise()
{
    int		i, n;
    object	env, *sheeptomove;

    CLOCK->notify_dawn(sunrise);
    sheeptomove = ({ });
    for (i = 0; i < NSHEEP; ++i)
    {
	/* only move sheep that aren't fighting and aren't already
	 * in the pastures.
	 */
	if (objectp(Sheep[i]) &&
	    !objectp(Sheep[i]->query_attack()) &&
	    objectp(env = ENV(Sheep[i])) &&
	    !sscanf(file_name(env), PASTURE_TEMPLATE, n))
	{
	    sheeptomove += ({ Sheep[i] });
	}
    }
    if (objectp(Ram) &&
	!objectp(Ram->query_attack()) &&
        objectp(env = ENV(Ram)) &&
        !sscanf(file_name(env), PASTURE_TEMPLATE, n))
    {
	sheeptomove += ({ Ram });
    }

    /* to do this right, would walk the sheep from the barn to the
     * pasture (assuming they're in the barn, of course), but i don't
     * think it's worth the trouble.
     */
    sheeptomove->move_living("away",
	(SIRITH_FARMS_DIR + "fields/pasture6"), 1, 1);
    sheeptomove->set_restrain_path(LIVESTOCK_RESTRAIN);
    sheeptomove->set_random_move(120);
} /* sunrise */


/*
 * Function name:	sunset
 * Description	:	move sheep to barn when sun goes down
 */
public void
sunset()
{
    int		i, n;
    object	env, *sheeptomove;

    CLOCK->notify_dusk(sunset);
    sheeptomove = ({ });
    for (i = 0; i < NSHEEP; ++i)
    {
	/* only move sheep that aren't fighting and aren't already
	 * in the barn.
	 */
	if (objectp(Sheep[i]) &&
	    !objectp(Sheep[i]->query_attack()) &&
	    ENV(Sheep[i]) != TO)
	{
	    sheeptomove += ({ Sheep[i] });
	}
    }
    if (objectp(Ram) &&
	!objectp(Ram->query_attack()) &&
        ENV(Ram) != TO)
    {
	sheeptomove += ({ Ram });
    }

    /* again, this is the cheap way ... */
    sheeptomove->move_living("away", TO, 1, 1);
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
	write(BSN("You drink a mouthful of warm water from the trough."));
    }
    else
    {
        write("You cannot drink more water just now.\n");
    }
    return 1;
} /* do_drink */
