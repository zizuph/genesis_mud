/*
 * /d/Gondor/river/anduin/lorien2rauros/eyot_bushes.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * bushes on the eyot -- only the smaller races can get in here
 */

#pragma strict_types

inherit "/d/Gondor/std/room";

#include <composite.h>		/* for COMPOSITE_LIVE */
#include <stdproperties.h>	/* for FILTER_LIVE */
#include <filter_funs.h>	/* for FILTER_LIVE */
#include "/d/Gondor/defs.h"	/* always */
#include "../anduin.h"		/* always */

#define	EYOT		(LORIEN_TO_RAUROS_DIR+"eyot")

#ifdef XYZZY
#define	RACE(tp) \
    ((tp)->query_real_name()[0..6] == "gnadnar" ? \
	"gnome" : (tp)->query_race())
#else
#define	RACE(tp)	((tp)->query_race())
#endif


/* prototypes */
public void	create_gondor();
public void	enter_inv(object ob, object from);
public string	look_eyot();

static object	Eyot;	/* the room */


/*
 * Function name:	create_shore_room
 * Description	:	set up the bushes
 */
public void
create_gondor()
{
    FIX_EUID;	/* because we might load EYOT */

    set_short("beneath some bushes");
    set_long(BSN("Thorny bushes press close on all sides, leaving "+
	"very little room to move about. The bushes thin towards "+
	"the south."));
    add_exit("eyot", "south", 0, 2, 1);
    set_no_exit_msg( ({ "north", "northeast", "northwest", "east",
	"west", "southwest", "southeast" }),
	BSN("You try to make your way further into the bushes, but they "+
	    "are too tangled and their thorns too sharp."));

    add_prop(ROOM_I_NO_ALLOW_STEED, 1);

    add_item( ({ "south", "south bushes", "thin bushes", "island",
	"small eyot", "eyot" }), look_eyot);
    add_item( ({ "thorn bushes", "tangled bushes", "bush", "bushes" }),
	BSN("The tangled bushes are thick with thorns."));
    add_item( ({ "thorn", "thorns" }),
	BSN("The long, sharp thorns are mere inches from your face."));
    add_item( ({ "ground", "gravel" }),
	BSN("The ground is hard, and scattered with gravel."));
    add_item( ({ "sun", "sky", "moon", "stars" }),
	BSN("All you can see from here is thorn bushes."));
} /* create_gondor */


/*
 * Function name:	enter_inv
 * Description	:	mask parent to keep too-big races out
 * Arguments	:	object ob  - the object entering our inventory.
 *			object from - wherever 'ob' came from. This can be 0.
 */
public void
enter_inv(object ob, object from)
{
    string	race;

    ::enter_inv(ob, from);

    if (living(ob))
    {
	race = RACE(ob);
	if (race != "hobbit" &&
	    race != "gnome" &&
	    race != "dwarf")
	{
	    if (ob->query_wiz_level())
	    {
		write(BSN("It's a tight fit, but you exert your "+
		      "wizardly powers to force a space in the bushes."));
		return;
	    }
	    if (!objectp(Eyot))
	    {
		EYOT->short();
		Eyot = find_object(EYOT);
	    }
	    if (objectp(Eyot))
	    {
		from = Eyot;
	    }
	    else if (!objectp(from))
	    {
		return;	/* sigh */
	    }
	    write(BSN("Yikes! Ouch! Thorns rip your flesh as you "+
		"try to force your way into the bushes. Bleeding, "+
		"you stagger out."));
	    ob->heal_hp(-30);
	    ob->move_living("south", from);
	    if (ENV(ob) == TO)
	    {
		ob->move(from, 1);
	    }
	}
    }
} /* enter_inv */


/*
 * Function name:	look_eyot
 * Description	:	see who is standing on the eyot
 * Returns	:	string -- the desc
 */
public string
look_eyot()
{
    object	*on_eyot;

    if (!objectp(Eyot))
    {
    	EYOT->short();
	Eyot = find_object(EYOT);
    }
    on_eyot = FILTER_LIVE(all_inventory(Eyot));
    if (!TP->query_wiz_level())
    {
	/* assume cannot see hidden or invis */
	on_eyot = filter(filter(on_eyot,
	    &not() @ &->query_prop(OBJ_I_HIDE)),
	    &not() @ &->query_invis());
    }
    switch (sizeof(on_eyot))
    {
    case 0:
	return BSN("The bushes somewhat obscure your view, but the eyot "+
		"appears to be empty.");
    case 1:
	return BSN("The bushes somewhat obscure your view, but "+
	    "you think you see "+on_eyot[0]->query_art_name(TP)+
	    " standing on the eyot.");
    default:
	return BSN("The bushes somewhat obscure your view, but "+
	    "you think you see "+COMPOSITE_LIVE(on_eyot)+
	    " standing on the eyot.");
    }
} /* look_eyot */
