/*
 * /d/Shire/rivendell/room/river/riverbottom.c
 *
 * master room for underwater rooms for the bruinen below the ford.
 * just forces them back to the surface, where all the interesting
 * stuff happens.
 */

#pragma strict_types

inherit "/d/Gondor/std/water/underwater";

#include <stdproperties.h>
#include "local.h"

#define	NO_GONDOR_DEFS
#include "/d/Gondor/std/water/underwater.h"

#define	ROCK_DENSITY	ROCKY

/* prototypes */
public void	create_riverbottom();
nomask void	create_underwater();
public int	block_exit();
public void	enter_inv(object ob, object from);
public void	move_to_surface(object ob);
public void	float_downstream(object ob);


/*
 * Function name:	create_riverbottom
 * Description	:	configure your riverbottom room here
 */
public void
create_riverbottom()
{
}


/*
 * Function name:	create_underwater
 * Description	:	set up the riverbottom
 */
nomask void
create_underwater()
{
    /* XXX these descs should be overridden by something more
     * interesting in create_riverbottom()
     */
    set_short("Underwater");
    set_long("In the depths the River Bruinen. The water is "+
	"dark and turbulent.\n");

    /* defaults */
    set_depth(MAX_WADE_DEPTH * 4);
    set_currentstr(MAX_CURRENT - 1);
    set_rock_density(ROCK_DENSITY);
    set_watertype("river");
    set_waterrefs( ({ "water", "waters", "river",
	"bruinen", "river bruinen", "bruinen river", "loudwater",
	"river loudwater", "loudwater river",  }) );

    create_riverbottom();

} /* create_underwater */


/*
 * Function name:	block_exit
 * Description	:	prevent taking exits -- we want to
 *			roll 'em about ourselves
 * Returns	:	1 -- always
 */
public int
block_exit()
{
    /* XXX more/better msgs */
    write(BSN(
	({ "The current is too strong -- you cannot control "+
		"your movement.",
	   "You splash desperately in the racing waters, "+
		"but are unable to make any progress.",
	   "The river tosses you about like a straw -- "+
		"you are helpless in the torrents.",
	})[random(3)]));
    return 1;
} /* block_exit */


/*
 * Function name:	enter_inv
 * Description	:	force 'em back up.
 * Arguments	:	object ob -- the entering object
 *			object from -- its source
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (living(ob)) {
	set_alarm(1.0, 0.0, &move_to_surface(ob));
    }
} /* enter_inv */


/*
 * Function name:	move_to_surface
 * Description	:	force player back to surface
 * Arguments	:	object ob --- the person to move
 */
public void
move_to_surface(object ob)
{
    if (objectp(ob) &&
	ENV(ob) == TO)
    {
	/* XXX more/better msgs ? */
	write("The violently churning water flings you upwards.\n");
	ob->move_living("up", query_above());
	if (ENV(ob) == TO)
	{
	    ob->move(query_above(), 1);
	}
    }
} /* move_to_surface */


/*
 * Function name:	float_downstream
 * Description	:	mask parent so we don't move 'em downstream
 * Arguments	:	object ob -- the entering person
 */
public void
float_downstream(object ob)
{
}
