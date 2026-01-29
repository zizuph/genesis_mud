/*
 * /d/Gondor/common/doc/examples/room_dig.c
 *
 * a room to demonstrate the use of /d/Gondor/common/lib/dig
 *
 * Created by Gnadnar 8-July-1998
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/dig";

#include <macros.h>
#include "/d/Gondor/defs.h"

public void	create_gondor();
public void	reset_room();
public void	init();
public void	leave_inv(object ob, object dest);
public void	dig_results(object digger);

static int	Knife_here;	/* is there a knife buried here? */

/*
 * Function name:	create_gondor
 * Description	:	set up the room
 */
public void
create_gondor()
{
    set_short("a test field");
    set_long("A test field with nice soft soil.\n");

    set_dig_pattern("[in] [the] [nice] [soft] 'soil' / 'dirt' / 'here'");
    set_dig_message("in the soft soil");
    set_dig_tools( ({ "hands", "shovel", "stick", "sword",
	"knife", "dagger" }) );

    reset_room();
} /* create_gondor */


/*
 * Function name:	reset_room
 * Description	:	reset the knife
 */
public void
reset_room()
{
    Knife_here = 1;
}


/*
 * Function name:	init
 * Description	:	add the dig verb
 */
public void
init()
{
    ::init();
    add_action(dig_here, "dig");
} /* init */


/*
 * Function name:	leave_inv
 * Description	:	be sure digging alarm is cleared if digger
 *			manages to leave in spite of paralyze
 * Arguments	:	object ob -- the departing object
 *			object dest -- its destination
 */
public void
leave_inv(object ob, object dest)
{
    stop_digging(ob);
    ::leave_inv(ob, dest);
} /* leave_inv */


/*
 * Function name:	dig_results
 * Description	:	mask this routine to handle results of digging.
 * Arguments	:	object digger -- the person digging
 */
public void
dig_results(object digger)
{
    object	knife;
    if (!Knife_here)
    {
	tell_object(digger, "You find nothing buried in the soil\n");
	return;
    }
    Knife_here = 0;
    knife = clone_object(WEP_DIR+"knife");
    tell_object(digger, "You find "+knife->short()+" buried in the soil!\n");
    if (knife->move(digger))
    {
	write("Oops, you dropped it.\n");
	knife->move(TO);
    }
    tell_room(TO,
	QCTNAME(digger)+" finds something buried in the soil.\n", digger);
} /* dig_results */
