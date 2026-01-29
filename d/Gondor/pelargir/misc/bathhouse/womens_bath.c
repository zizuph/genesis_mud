/*
 * /d/Gondor/pelargir/misc/bathhouse/womens_bath.c
 *
 * Copyright (C) 1999 by Nancy L. Mintz (Gnadnar)
 *
 */


#pragma strict_types

inherit "/d/Gondor/pelargir/misc/bathhouse/bath";

#include <const.h>
#include "/d/Gondor/defs.h"
#include "bath.h"

public void	create_bath();
public void	enter_inv(object ob, object from);


/*
 * Function name:	create_bath
 * Description	:	set up the room
 */
public void
create_bath()
{
    set_short("large room");
    set_long(BSN("Wooden tubs fill this large room, " +
	"leaving very little space to walk around. A rush basket " +
	"and a small copper pot sit on the floor near the doorway."));
    
    add_item( ({ "large room", "room", "women's bath", "bath", }), long);
    add_item( ({ "open door", "open doorway", "door", "doorway", }),
	"A low open doorway, gently arched, leads west.\n");

    add_exit(ENTRY, "west", check_sitting);
    Room_dir = "east";
    Attendant_gender = G_FEMALE;
} /* create_bath */


/*
 * Function name:	enter_inv
 * Description	:	mask parent to eject wrong gender
 * Arguments	:	object ob -- the entering object
 *			object from -- its source
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob) &&
	ob->query_gender() == G_MALE)
    {
	set_alarm(1.0, 0.0, &wrong_gender(ob));
    }
} /* enter_inv */
