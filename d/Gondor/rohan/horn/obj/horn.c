/*
 * /d/Gondor/rohan/horn/obj/horn.c
 *
 * 10 Aug 98, Gnadnar:	make parsing more robust, conform to domain.rules
 */

#pragma strict_types

inherit "/std/object";

#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

public void	create_object();
public void	init();
public int	blow_horn(string str);
public void	honk(object tp);


/*
 * Function name:	create_object
 * Description	:	set up the horn
 */
public void
create_object()
{
    set_name("horn");
    set_adj("brass");
    set_short("brass horn");
    set_long("A horn with simple brass fittings.\n");

    add_prop(OBJ_I_WEIGHT,1000);
    add_prop(OBJ_I_VOLUME,1000);
    add_prop(OBJ_I_VALUE, 0);
} /* create_object */


/*
 * Function name:	init
 * Description	:	add 'blow'
 */
public void
init()
{
    ::init();
    add_action("blow_horn", "blow");
} /* init */



/*
 * Function name:	blow_horn
 * Description	:	let 'em blow the horn
 * Arguments	:	string str -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
blow_horn(string str)
{
    int		s;
    object	tp = TP,
	   	*targets;

    if ((!strlen(str)) ||
	(!parse_command(LOW(str), all_inventory(tp), "%i", targets)) ||
	!(s = sizeof(targets = NORMAL_ACCESS(targets, 0, 0))))
    {
        NF0("Blow what?\n");
    }
    if (s > 1)
    {
	NF0("You can only blow one thing at a time.\n");
    }
    if (targets[0] != TO)
    {
	return 0;
    }
    TP->reveal_me(1);
    write("You blow the horn.\n");
    SAY(" blows a horn.");
    tell_room(ENV(TP), "The deep-throated call of the horn fills the air.\n");
    set_alarm(1.0, 0.0, &honk(TP));
    return 1;
} /* blow_horn */


/*
 * Function name:	honk
 * Description	:	player blew horn -- summon the guard
 * Arguments	:	object tp -- the player
 */
public void
honk(object tp)
{
     ENV(tp)->call_helmsdeep_guard(tp);
} /* honk */

/* This object is not recoverable on purpose. */
