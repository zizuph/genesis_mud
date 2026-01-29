/*
 * /d/Gondor/common/quest/enchant_seed/normseed.c
 *
 * coded by ???
 *
 * Modification history:
 * 02-Sep-1998, Gnadnar: tidy up
 * 25-Apr-2020, Made the seed worthless to sell
 */

#pragma strict_types

inherit "/std/object";

#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"


public void	create_object();
public void	init();
public int	plant_me(string arg);


/*
 * Function name:	create_object
 * Description	:	set up the seed
 */
public void
create_object()
{
    set_name("seed");
    set_adj( ({ "small", "green" }) );
    set_long("The small green seed appears quite ordinary.\n");
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_I_VALUE, 0);

} /* create_object */


/* 
 * Function name:	init
 * Description	:	add verbs
 */
public void
init()
{
    add_action(plant_me, "plant");
    add_action(plant_me, "sow");
} /* init */


/*
 * Function name:	plant_me
 * Description	:	handle planting the seed
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
plant_me(string arg)
{
    int		s;
    object	env;
    mixed	*targets;
    string	tmpstr;

    if (!strlen(arg))
    {
	NF0(CAP(QVB)+" what?\n");
    }

    arg = LOW(arg);
    if (!parse_command(arg, all_inventory(TP), "[the] %i %s", targets, tmpstr))
    {
	NF0(CAP(QVB)+" what?\n");
    }
    targets = NORMAL_ACCESS(targets, 0, 0);
    if (!(s = sizeof(targets)))
    {
	NF0(CAP(QVB)+" what?\n");
    }
    if (s > 1)
    {
	NF0("You can only "+QVB+" one thing at a time.\n");
    }
    if (targets[0] != TO)
    {
	return 0;	/* matched some seed, but not this one */
    }
    if (strlen(tmpstr) &&
	!parse_command(tmpstr, ({}), "[in] [the] 'ground'"))
    {
	NF0("Plant the seed where? In the ground, perhaps?\n");
    }

    env = ENV(TP);
    if (env->query_prop(ROOM_I_INSIDE))
    {
	NF0("You cannot "+QVB+" a seed indoors.\n");
    }

    write("You carefully plant the seed in the ground.\n");
    SAY(" plants a small green seed in the ground.");

    remove_object();
    return 1;
} /* plant_me */
