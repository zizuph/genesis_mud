/*
 * /d/Gondor/river/anduin/obj/toolchest.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * toolchest of the Beorning fishcamp's boat builder.
 * a red herring. it's permanently closed and locked.
 *
 * TBD: have builder intercept attempts to mess
 * with chest?
 *
 */

#pragma strict_types

inherit "/std/receptacle";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../carrock2lorien/fishcamp.h"

/* prototypes */
public void		create_receptacle();
public varargs int 	open(object ob);
public varargs int 	close(object ob);
public varargs int 	lock(object ob);
public varargs int 	unlock(object ob);
public varargs int 	pick(object ob);


/*
 * Function name:	create_receptacle
 * Description	:	set up the toolchest
 */
public void
create_receptacle()
{
    set_name( ({ "chest", "toolchest", CHEST_NAME }) );
    set_adj( ({ "large", "tool" }) );
    set_long(BSN(
        "The chest is quite large, and its surface is scarred "+
        "and pitted. It appears to have seen years of hard use."));
    set_no_show_composite(1);    /* is in room long */

    add_prop(OBJ_M_NO_GET, "The chest is too heavy.\n");

    /* thes values could be anything, since we won't 
     * let them get it and it's permanently locked
     */
    add_prop(CONT_I_WEIGHT,      10000);
    add_prop(CONT_I_MAX_WEIGHT,  10000);
    add_prop(CONT_I_VOLUME,      10000);
    add_prop(CONT_I_MAX_VOLUME,  10000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_LOCK, 1);
    set_key(CHEST_KEY);
    set_pick(99);

} /* create_receptacle */


/*
 * Functions name:	open, close, lock, unlock, pick
 * Description	:	respond to attempts to manipulate the chest
 * Arguments	:	object ob -- the chest
 * Returns	:	-1 -- fails, use default msg
 */
public varargs int	open(object ob)		{ return -1; }
public varargs int	close(object ob)	{ return -1; }
public varargs int	lock(object ob)		{ return -1; }
public varargs int	unlock(object ob)	{ return -1; }
public varargs int	pick(object ob)		{ return -1; }
