/*
 * /d/Gondor/common/doc/examples/room_noise.c
 *
 * a room to demonstrate the use of /d/Gondor/common/lib/random_noise
 *
 * Created by Gnadnar 7-July-1998
 *
 */

#pragma strict_types

/* inherit the noise file as well as the standard room */
inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/random_noise";

#include "/d/Gondor/defs.h"

public void	create_gondor();
public void	init();
public int	random_noise();

/*
 * Function name:	create_gondor
 * Description	:	set up the room
 */
public void
create_gondor()
{
    set_short("a test room");
    set_long("A test room with occasional noises.\n");
} /* create_gondor */


/*
 * Function name:	init
 * Description	:	init the random noises
 */
public void
init()
{
    ::init();
    init_random_noise();
} /* init */


/*
 * Function name:	random_noise
 * Description	:	write a random noise
 * Returns	:	int -- non-zero if noises should continue,
 *				zero if they should stop
 */
public int
random_noise()
{
    tell_room(TO, BSN(	({
	"Boo!",
	"The floor creaks, although you see no one here.",
	"You hear faint silvery laughter in the distance.",
	"There is a faint tapping noise, as of fingernails on glass.",
	"You have the feeling you are not alone.",
	})[random(5)] ) );
    return 1;
} /* random_noise */
