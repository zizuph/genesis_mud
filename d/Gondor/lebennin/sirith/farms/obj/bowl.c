/*
 * /d/Gondor/common/guild/obj/firewood
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 * the liquid-handling initially was an important part of the quest
 * because we were going to make the pig drunk in order to kill her.
 * it's not important now that we use herbs instead, but retain it
 * as an interesting red herring.
 * 
 * code to strip container names from liquids swiped from
 * /d/Gondor/common/guild/obj/wineskin.c
 *
 * the bowl may hold liquids (something with query_soft_amount()) or
 * non-liquids, but not both (with the exception of scraps). this is
 * done so i don't have to deal with the interactions of liquids with 
 * various objects. if scraps and a liquid are put into the bowl, the
 * scraps absorb the liquid (which disappears).
 *
 * may not put mixtures of liquids in bowl. if this were a wineskin
 * or bottle or the like, it'd be worth doing it -- but not for a 
 * simple bowl.
 *
 * do_fill_put_pour() handles:
 *	fill bowl with liquid
 *	pour liquid in[to] bowl
 *	put object/liquid in[to] bowl
 *
 * do_empty_pour() handles:
 *	empty bowl
 *	empty liquid
 *	pour bowl
 *	pour liquid
 *	empty liquid from bowl
 *	pour liquid from bowl
 * plus all the above with "on[to] fire" appended
 *
 * do_drink() handles:
 *	drink [liquid] from bowl
 *
 * do_mix() handles:
 *	mix herb in[to]/with scraps
 *	stir herb in[to] scraps
 *
 * cannot 'get/take liquids from bowl', since holding liquid in your
 * bare hands is a trifle difficult. 
 *
 */

#pragma strict_types

inherit "/std/container";

#include <stdproperties.h>		/* for OBJ_I_WEIGHT, etc */
#include <macros.h>			/* for QCTNAME		 */
#include <herb.h>			/* for HERB_POISONING	 */
#include <poison_types.h>		/* for POISON_HP	 */
#include "../defs.h"
#include "/d/Gondor/open/fireplace/fireplace.h"	/* for FIRE_*	 */

#define MINUS \
    ({"bottle","mug","glass","pint","small","large","the","of","a","an"})

static object	Liquid;		/* liquid in the bowl	*/


/* prototypes */
public void	create_container();
public void	init();
public int	do_fill_put_pour(string arg);
static int	fill_with_liquid(object what, string cmd);
static int	fill_with_water();
public int	do_empty_pour(string arg);
public int	do_drink(string arg);
public int	feed_scraps(string arg);
public void	mix_with_scraps(string name, int soft_amt,
				int alco_amt, object scraps);
public void	enter_inv(object ob, object from);
public void	splash(object ob, object from);
public int	do_mix(string arg);
public void	enter_env(object dest, object from);
public void	break_bowl();


/*
 * Function name:	create_container
 * Description	:	set up the bowl
 */
public void
create_container() 
{
    set_name("bowl");
    set_adj( ({"chipped", "blue"}) );
    set_short("chipped blue bowl");
    set_long(BSN("The bowl's deep blue glaze has been chipped in "+
	"several places, but it still is a lovely colour."));

    /* let's say the bowl is about 8 inches tall, has a diameter
     * of 8 inches across the top and doesn't taper very much towards
     * its bottom -- simplify life and say it's an 8" cube ==
     * 512 cubic inches == 8390 cubic millilitres. let's say the
     * side and bottom of the bowl are 1/2 inch thick, so it can
     * actually hold 7.5**3 == 422 cubic inches == 6916 millilitres,
     * so the volume occupied by the bowl itself is 8390 - 6916
     */
    add_prop(CONT_I_WEIGHT,       454);	/* 1 lb */
    add_prop(CONT_I_MAX_WEIGHT,  2268);	/* 5 lbs */
    add_prop(CONT_I_VOLUME,      1474);
    add_prop(CONT_I_MAX_VOLUME,  6916);
    add_prop(CONT_I_TRANSP,         1);
    add_prop(CONT_I_RIGID,          1);
    add_prop(OBJ_I_VALUE,          50);
} /* create_container */


/*
 * Function name:	init
 * Description	:	add player verbs
 */
public void
init()
{
    ::init();

    add_action(do_fill_put_pour,       "put");	/* fill the bowl          */
    add_action(do_fill_put_pour,      "fill");	/* fill the bowl          */
    add_action(do_fill_put_pour,      "pour");	/* fill or empty the bowl */
    add_action(do_empty_pour,        "empty");	/* empty the bowl         */
    add_action(do_drink,             "drink");	/* drink from the bowl    */
    add_action(do_mix,                 "mix");	/* mix herbs & scraps	  */
    add_action(do_mix,                "stir");	/* mix herbs & scraps	  */

    /* to allow "feed scraps to pig", etc while scraps are in bowl */
    add_action(feed_scraps, "give");
    add_action(feed_scraps, "feed");
    add_action(feed_scraps, "lure");
    add_action(feed_scraps, "show");

} /* init */


/*
 * Function name:	do_fill_put_pour
 * Description	:	fill the bowl with something
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if success, 0 if not
 *
 * handles the parsing and sanity checks for:
 *	put liquid/object in[to] bowl
 *	fill bowl with liquid
 *	pour liquid in[to] bowl
 * calls fill_with_liquid() or fill_with_water() to do the actual work
 * for liquids; falls thru to normal 'put' processing for "put object..."
 */
public int
do_fill_put_pour(string arg)
{
    object	what,	/* the liquid */
		where,	/* the container (presumably this bowl) */
		tp = TP,
		*inv = all_inventory(tp);
    string	whatstr,
		wherestr,
		vb = query_verb(),
		failstr; /* notify_fail msg, varies with verb */

    if (!strlen(arg))
    {
	NF0(capitalize(vb)+" what?\n");
    }

    if (vb == "fill")
    {
	failstr = "Fill what with which?\n";
	if (!parse_command(LOW(arg), ({ }), "%s 'with' %s",
	    wherestr, whatstr))
	{
	    NF0(failstr);
	}
    }
    else	/* vb == "pour" or "put" */
    {
	failstr = capitalize(vb)+" which in what?\n";
	if (!parse_command(LOW(arg), ({ }),
	    "%s 'in' / 'into' %s", whatstr, wherestr))
	{
	    if (vb == "put")
	    {
	    	return 0; /* no point in NF0 if we know it's "put" */
	    }
	    /* they might have done "pour milk from bowl" */
	    return do_empty_pour(arg);
	}
    }

    if (!parse_command(wherestr, inv, "%o", where) ||
	where != TO)
    {
	NF0(failstr);
    }

    if (!parse_command(whatstr, inv, "%o", what))
    {
	/* no such object 'whatstr' -- are they trying to get
	 * water from the room, perhaps ?
    	 * don't allow "pour water into bowl" when the water
	 * is a room property. typically the source is pool or watering 
	 * trough or ocean, and you cannot "pour" those.
	 */
	if (whatstr != "water" ||
	    vb == "pour")
	{
	    NF0(failstr);
	}

    }
    else if (!what->query_soft_amount())
    {
	/* the object is not a liquid */

	/* don't fill/pour non-liquids */
	if (vb != "put")
	{
	    NF0(failstr);
	}

	if (!objectp(Liquid))
	{
	    /* put non-liquid obj in bowl that is not holding a liquid
	     * now. nothing special -- let the normal 'put' processing
	     * handle it.
	     */
	    return 0;	
	}

	/* cannot put stuff in bowl if it already holds a liquid,
	 * except for scraps.
	 * do not return 0 here; if you do, 'put' will intercept it
	 * and quite possibly put the stuff in the bowl anyway.
	 */
	if (!what->id(SIRITH_SCRAPS))
	{
	    write(BSN("The bowl is full of "+Liquid->query_short()+"."));
	    return 1;
	}
	mix_with_scraps(0, 0, 0, what);
	return 1;
    }

    /* the object is a liquid or water from the room */
    if (query_prop(OBJ_I_WEIGHT) > query_prop(CONT_I_WEIGHT) &&
        !objectp(present(SIRITH_SCRAPS, TO)))
    {
	/* cannot put a liquid in the bowl if it already holds
	 * stuff and does not hold any scraps.
	 */
	write("The bowl is not empty.\n");
	return 1;
    }

    if (objectp(what))
    {
	return fill_with_liquid(what, vb+" "+arg);
    }
    return fill_with_water();
} /* do_fill_put_pour */


/*
 * Function name:	fill_with_liquid
 * Description	:	fill the bowl with a liquid
 * Arguments	:	object what -- the liquid object
 *			string cmd -- the player's original cmd
 * Returns	:	1 on success, 0 on failure
 */
static int
fill_with_liquid(object what, string cmd)
{
    int		maxvol, maxwgt,
		percent_alco, soft_amt, alco_amt,
		spill;
    string	whatstr,
		*arr;
    object	scraps,
		tp = TP,
		env = ENV(tp);

    /* be sure liquid can leave player's inv. just move into
     * env, since it will be dested anyway.
     */
    if (what->move(env))
    {
       NF0("You cannot "+cmd+".\n");
    }

    /* duck the entire issue of potions; i don't want to handle
     * the effects on the pig if she eats potion-laced scraps
     */
    if (strlen(what->query_potion_name()))
    {
        whatstr = what->short();
        write(BSN("You start to pour the "+whatstr+
    	    " into the bowl."));
        what->remove_object();
        write("Oops! You spilled it.\n");
        SAY(" spills some "+whatstr+".");
        return 1;
    }

    whatstr = what->query_name();
    soft_amt = what->query_soft_amount();
    alco_amt = what->query_alco_amount();
    if (objectp(scraps = present(SIRITH_SCRAPS, TO)))
    {
	what->remove_object();
        mix_with_scraps(whatstr, soft_amt, alco_amt, scraps);
        return 1;
    }

    /* clone a new obj so we can be sure that the liquid in the 
     * bowl doesn't still id to stuff that doesn't make sense now
     * (e.g., "mug")
     */
    FIX_EUID;
    Liquid = clone_object("/std/drink");
    Liquid->set_name(whatstr);

    /* remove container words from liquid short
     * (e.g., "mug of apple cider" -> "apple cider")
     * bummer. this doesn't fix the entire problem. you still
     * get something like:
     *		The chipped blue bowl contains an apple cider.
     * and that string is constructed in /cmd/live/things.c,
     * so i'm not sure how to circumvent it. kludge it --
     * stick "quantity of" on the front. yeuch.
     */
    arr = explode(what->query_short()," ")-MINUS;
    if (!sizeof(arr))
    {
        arr = ({ whatstr });
    }
    Liquid->set_short("quantity of "+implode(arr, " "));

    /* a lame long desc, but not sure what else to do ...
     * since they can't get the liquid back out of the bowl
     * in any usable form, it probably doesn't matter
     */
    Liquid->set_long(BSN("This is some "+Liquid->query_short()+"."));

    /* if incoming liquid doesn't fit, make some spill over
     * we only care about the liquid's soft_amount. vol & weight
     * include the liquid's container, which we ignore.
     */
    maxvol = volume_left();
    maxwgt = query_prop(CONT_I_MAX_WEIGHT) - query_prop(CONT_I_WEIGHT);
    if (soft_amt > maxvol ||
	soft_amt > maxwgt)
    {
	spill = 1;
	soft_amt = (maxwgt < maxvol ? maxwgt : maxvol);
	/* remember that this is integer math -- don't try to 
	 * collapse the  ( * 100 ) ... ( / 100 ) out of the following.
	 */
	percent_alco = (alco_amt * 100 / soft_amt);
	alco_amt = (percent_alco * soft_amt / 100);
    }
    Liquid->add_prop(OBJ_I_VOLUME, soft_amt);
    Liquid->add_prop(OBJ_I_WEIGHT, soft_amt);
    Liquid->set_soft_amount(soft_amt);
    Liquid->set_alco_amount(alco_amt);

    Liquid->add_prop(OBJ_I_NO_GET,
        "You can carry "+whatstr+" in a container, but not pick "+
	"it up with your bare hands.\n");
    Liquid->add_prop(OBJ_I_NO_DROP,
        "If you dropped the "+whatstr+
        ", it would vanish into the ground immediately.\n");
    Liquid->add_prop(OBJ_I_NO_GIVE,
        "Nobody can keep so much "+whatstr+
        " in her bare hands, so you can't give it away.\n");

    if (!Liquid->move(TO))
    {
    	write("You fill the bowl with the "+whatstr+".\n");
        SAY(" fills a bowl with "+whatstr+".");
	if (spill)
	{
	    write(BSN("Some of the "+whatstr+" sloshes over the sides "+
		"of the bowl."));
	}
    }
    else
    {
        write("Oops! You spilled the "+whatstr+".\n");
        SAY(" spills some "+whatstr+".");
        Liquid->remove_object();
    }
    what->remove_object();
    return 1;
} /* fill_with_liquid */


/*
 * Function name:	fill_with_water
 * Description	:	fill the bowl with water from the room
 * Returns	:	1 on success, 0 on failure
 */
static int
fill_with_water()
{
    int		wgt_left,
		soft_amt,
       		vol = volume_left();
    object	scraps,
		tp = TP,
		env = ENV(tp);

    if (!env->query_prop(OBJ_I_CONTAIN_WATER) &&
        !env->query_prop(ROOM_BEACH) &&
        !env->query_prop(ROOM_IN_WATER) &&
        !env->query_prop(ROOM_UNDER_WATER))
    {
	NF0("There is no water here.\n");
    }

    if (objectp(scraps = present(SIRITH_SCRAPS, TO)))
    {
	mix_with_scraps("water", vol, 0, scraps);
	return 1;
    }

    wgt_left = query_prop(CONT_I_MAX_WEIGHT) - query_prop(OBJ_I_WEIGHT);
    soft_amt = (wgt_left < vol ? wgt_left : vol);

    FIX_EUID;
    Liquid = clone_object(OBJ_DIR + "water");
    Liquid->set_short("quantity of water");
    Liquid->set_long("The water is quite clear.\n");
    Liquid->change_prop(HEAP_S_UNIQUE_ID, "The water is quite clear.\n");
    Liquid->set_soft_amount(soft_amt);
    Liquid->add_prop(OBJ_I_VOLUME, soft_amt);
    Liquid->add_prop(OBJ_I_WEIGHT, soft_amt);
    if (Liquid->move(TO))
    {
	ERR_LOG(file_name(Liquid)+"->move(this_object()) failed\n");
	write("Oops! You spilled the water.\n");
	Liquid->remove_object();
	return 1;
    }
    TO->add_prop(OBJ_I_CONTAIN_WATER,1);
    write("You fill the bowl with water.\n");
    say(QCTNAME(tp) + " fills a bowl with water.\n");
    return 1;
} /* fill_with_water */


/*
 * Function name:	do_empty_pour
 * Description	:	empty liquid out of bowl
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if success, 0 otherwise
 *
 * handles:
 *	empty/pour bowl/liquid [on/onto fire]
 *	empty/pour liquid from bowl [on/onto fire]
 *
 */
public int
do_empty_pour(string arg)
{
    int		onfire;
    object	fire,
		what,	/* the liquid */
		where,	/* the container (presumably this bowl) */
		tp = TP,
		env = ENV(tp),
		*inv = all_inventory(tp);
    string	whatstr,
		vb = query_verb();

    if (!strlen(arg))
    {
	NF0(capitalize(vb)+" what?\n");
     }

    if (parse_command(LOW(arg),
	 ({ }), "%s 'on' / 'onto' [the] 'fire'", whatstr))
    {
	fire = present("fire", env);
	if (!objectp(fire = present("fire", env)) &&
	    env->query_fire_state() != FIRE_BURNING)
	{
	    NF0("There is no fire here.\n");
	}
	onfire = 1;
	arg = whatstr;
    }

    /* usually pass all_inventory(tp) to parse_command, because i want it to
     * consider only objects in player's hands, not in closed packs etc.
     * however, for this one, add the bowl's inv too.
     */
    if (parse_command(LOW(arg), inv + all_inventory(TO), "%o", where))	
    {
	if (where == TO  ||
	    where == Liquid)
	{
	    where = TO;
	    what = Liquid;
	    whatstr = Liquid->query_name();
	}
	else
	{
	    NF0(capitalize(vb)+" what?\n");
	}
	/* handle this error case here so we can do a better msg */
	if (!objectp(Liquid))
	{
	    NF0("You cannot "+vb+" an empty bowl.\n");
	}
    }
    else if (parse_command(LOW(arg), inv, "%s 'from' %o", whatstr, where))
    {
	if (where != TO)
	{
	    NF0(capitalize(vb)+" what?\n");
	}
	/* handle this error case here so we can do a better msg */
	if (!objectp(Liquid))
	{
	    NF0("You cannot "+vb+" "+whatstr+" from an empty bowl.\n");
	}
    }
    else 
    {
	whatstr = arg;
    }
    
    if (!objectp(Liquid) ||
	(strlen(whatstr) &&
	 !Liquid->id(whatstr)))
    {
	/* this msg has to be very general because it will also be
	 * the error msg for "pour" failures from do_fill_put_pour()
	 */
	NF0(capitalize(vb)+" what?\n");
    }

    /* ok, they meant this bowl, it contains a liquid, and either 
     * they didn't specify which liquid or their spec matched.
     */
    whatstr = Liquid->query_name();
    Liquid->remove_object();
    TO->remove_prop(OBJ_I_CONTAIN_WATER);
    if (!onfire)
    {
	write(BSN("You pour the "+whatstr+" from the bowl on the "+
	    (env->query_prop(ROOM_I_INSIDE) ? "floor." : "ground.")));
	SAY(" pours "+whatstr+" from a bowl.");
	tell_room(env, "The "+whatstr+" vanishes immediately.\n");
    }
    else	/* pour/empty onto fire */
    {
	write("You pour "+whatstr+" on the fire.\n");
	SAY(" pours "+whatstr+" on the fire.");

	/* we firmly ignore the possibility of inflammable liquids */
	if (objectp(fire))
	{
	    fire->extinguish("fire");
	}
	else
	{
	    env->set_fire_state(FIRE_ASHES);
	}
    }
    return 1;
} /* do_empty_pour */


/*
 * Function name:	do_drink
 * Description	:	handles attempts to drink from bowl
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if success, 0 otherwise
 *
 * handles
 *	drink [liquid] from bowl
 * except that we don't really drink it. it got too complex,
 * so we just spill the liquid.
 */
public int
do_drink(string arg)	/* appears to work */
{
    int		rval;
    string	whatstr, wherestr;
    object	tp = TP,
		*inv = all_inventory(tp),
		what, 
		where;

    if (!arg)
    {
	NF0("Drink what?\n");
    }
    
    if ((!parse_command(LOW(arg), inv, "%s 'from' %o", whatstr, where) &&
         !parse_command(LOW(arg), inv, "'from' %o", where)) ||
	where != TO)
    {
	NF0("Drink what from where?\n");
    }

    if (!objectp(Liquid))
    {
	NF0("The bowl is empty.\n");
    }
    
    if (strlen(whatstr))
    {
	if (!Liquid->id(whatstr) &&
	    whatstr != Liquid->query_short())
	{
	    NF0("There is no "+whatstr+" in the bowl.\n");
	}
    }
    else
    {
	whatstr = Liquid->query_name();
    }

    /* well, hmm, let's bail out. i don't feel like managing all
     * the drink intricacies myself, and /std/drink.c's drink_it()
     * is going to fail unless i move the liquid into the player,
     * but that is problematical because not all of the liquid
     * might be drunk, and if there's some left i should put it 
     * back in the bowl, but the removal of that which was drunk
     * is done via set_alarm(), so i can't just check the object
     * as soon as drink_it() returns ... ick. this is just a bowl
     * for scraps, not a wineskin. it's hard to drink from a big bowl
     * without spilling, anyway. 
     */
    write(BSN("You tip the bowl up to drink, but spill the "+whatstr+
	" down your chin and onto the "+
	(ENV(tp)->query_prop(ROOM_I_INSIDE) ? "floor." : "ground.") ));
    SAY(" tries to drink "+whatstr+" from a bowl, but spills it.");
    Liquid->remove_object();
    TO->remove_prop(OBJ_I_CONTAIN_WATER);
    return 1;
} /* do_drink */


/*
 * Function name:	feed_scraps
 * Description	:	allow feed/give/show scraps while they're in bowl
 * Arguments	:	string arg -- whatever the player typed
 * Return	:	1 if we recognize the arg, 0 otherwise
 */
public int
feed_scraps(string arg)
{
    object scraps;

    if (objectp(scraps = present(SIRITH_SCRAPS, TO)))
    {
	return scraps->feed_scraps(arg);
    }
    return 0;
} /* feed_scraps */


/*
 * Function name:	mix_with_scraps
 * Description	:	mix a liquid with the scraps in the bowl
 * Argumennts	:	string name -- the name of the liquid
 *			int soft_amount -- how much of it
 *			int alco_amount -- how much alcohol
 *			object scraps -- the scraps
 */
public void
mix_with_scraps(string name, int soft_amt, int alco_amt, object scraps)
{
    object	env = ENV(TP);
    int		orig_weight, orig_vol,
		max_weight, max_vol,
		new_amt, percent_alco, new_alco,
		spill;

    if (!soft_amt)
    {
	if (!objectp(Liquid))
	{
	    /* "cannot" happen */
	    DEBUG_LOG("mix_with_scraps: no soft_amt and no "+
		"Liquid; breaking bowl\n");
	    write(BSN("Oops! You drop the bowl, and it shatters."));
	    scraps->remove_object();
	    TO->remove_object();
	    return;
	}
	/* adding scraps to liquid already in bowl */
	soft_amt = Liquid->query_soft_amount();
	alco_amt = Liquid->query_alco_amount();
	name = Liquid->query_name();
    }

    /*
     * bowl contains either scraps or liquid, and we're about
     * to add the other. will this fit?
     * the scraps should grow by all the the liquid's weight
     * and half its volume.
     */

    /* empty out bowl so we have a fresh start */
    if (objectp(Liquid))
    {
	Liquid->move(env);
    }
    else
    {
	scraps->move(env);
    }

    orig_weight = scraps->query_prop(OBJ_I_WEIGHT);
    orig_vol = scraps->query_prop(OBJ_I_VOLUME);
    max_weight = query_prop(CONT_I_MAX_WEIGHT) - query_prop(OBJ_I_WEIGHT);
    max_vol = volume_left();
    if (!max_weight ||
	!max_vol)
    {
	write("The bowl cannot hold the "+name+".\n");
	DEBUG_LOG("mix_with_scraps: empty bowl can't hold more?\n");
	if (objectp(Liquid))
	{
	    Liquid->move(TO);
	}
	else
	{
	    scraps->move(TO);
	}
	return;
    }
    if ((orig_weight + soft_amt) > max_weight ||
        (orig_vol + (soft_amt/2)) > max_vol)
    {
	/* oops. can't all fit */
	spill = 1;
	new_amt = (max_weight < (max_vol * 2) ? max_weight : (max_vol * 2));
    	scraps->add_prop(OBJ_I_WEIGHT, new_amt);
    	scraps->add_prop(OBJ_I_VOLUME, new_amt/2);
	/* not absorbing all the liquid, so need to adjust alco_amt.
	 * remember that this is integer math -- don't try to 
	 * collapse the  ( * 100 ) ... ( / 100 ) out of the following.
	 */
	percent_alco = (alco_amt * 100 / soft_amt);
	new_alco = (percent_alco * new_amt / 100);
    }
    else
    {
	/* it fits */
	new_amt = soft_amt;
	new_alco = alco_amt;
	scraps->add_prop(OBJ_I_WEIGHT, (orig_weight + soft_amt));
	scraps->add_prop(OBJ_I_VOLUME, (orig_vol + (soft_amt/2)));
    }

    if (scraps->move(TO))
    {
	/* "cannot" happen, but reset scraps and put back */
	scraps->add_prop(OBJ_I_WEIGHT, orig_weight);
	scraps->add_prop(OBJ_I_VOLUME, orig_vol);
	if (scraps->move(TO))
	{
	    /* really cannot happen */
	    DEBUG_LOG("mix_with_scraps: breaking bowl\n");
	    write(BSN("Oops! You drop the bowl, and it shatters."));
	    if (objectp(Liquid))
	    {
		Liquid->remove_object();
	    }
	    else
	    {
		scraps->remove_object();
	    }
	    TO->remove_object();
	    return;
        }
    }

    scraps->add_alcohol(new_amt, new_alco);

    if (!objectp(Liquid))	/* liquid entering bowl w/ scraps */
    {
	write(BSN("You fill the bowl with "+name+
	    ", which soaks into the kitchen scraps."));
	if (spill)
	{
	    write(BSN("Some of the "+name+
		" sloshes over the sides of the bowl."));
	}
	SAY(" fills a bowl with "+name+".");
    }
    else	/* scraps entering bowl w/ liquid */
    {
	write(BSN("You put the scraps in the bowl, where they "+
	    "absorb the "+name+"."));
	if (spill)
	{
	    write(BSN("Some of the "+name+
		" sloshes over the sides of the bowl."));
	}
	SAY(" puts some kitchen scraps into a bowl.");
	Liquid->remove_object();
    }
    scraps->move(TO);
} /* mix_with_scraps */


/*
 * Function name:	enter_inv
 * Description	:	called when something enters the bowl
 * Arguments	:	object ob -- the entering object
 *			object from -- its previous env
 * 
 * this protects against a failure of my fill/put/pour parsing,
 * and splashes any liquid from the bowl if another object enters.
 * pure paranoia and probably never will be needed
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (objectp(Liquid) &&
	Liquid != ob)
    {
	/* use TP here -- newly cloned liquid has no 'from' */
	set_alarm(1.0, 0.0, &splash(ob, TP));
    }
} /* enter_inv */


/*
 * Function name:	splash
 * Description	:	called from enter_inv to splash liquid out
 * Arguments	:	object ob -- the entering object
 *			object from -- this_player() when enter_inv()
 *					was called
 * 
 * this protects against a failure of my fill/put/pour parsing,
 * and splashes any liquid from the bowl if another object enters.
 * pure paranoia and probably never will be needed
 */
public void
splash(object ob, object from)
{
    if (!objectp(Liquid) ||
	!objectp(ob) ||
	ENV(ob) != TO)
    {
	return;
    }

    if (ENV() == from)
    {
	tell_object(from,
	    BSN("The "+ob->query_name()+" displaces the "+
	    Liquid->query_name()+", which sloshes out of the bowl."));
    }
    Liquid->remove_object();
    TO->remove_prop(OBJ_I_CONTAIN_WATER);
} /* splash */


/*
 * Function name:	do_mix
 * Description	:	handle mixing herbs into scraps
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if success, 0 if not
 *
 * handles:
 *	mix herb with/in/into scraps
 *	stir herb in/into scraps
 * if herb is poison, calls add_poison() in scraps
 */
public int
do_mix(string arg)
{
    string	herbstr,
		scrapstr,
		vb = query_verb();
    object	herb,
		scraps,
		thisob,
		*inv;
    mixed	*herb_effects;
    int		i, n;

    if (!strlen(arg))
    {
	NF0(capitalize(vb)+" what?\n");
    }

    if (vb == "mix")
    {
	if (!parse_command(LOW(arg), ({ }), "%s 'in' / 'into' / 'with' %s",
		  	   herbstr, scrapstr))
	{
	    NF0("Mix what?\n");
	}
    }
    else
    {
    	/* "stir herbs with scraps" sounds odd; you can't use
	 * scraps as a spoon.
	 */
	if (!parse_command(LOW(arg), ({ }), "%s 'in' / 'into' %s",
			   herbstr, scrapstr))
	{
	    NF0("Stir what?\n");
	}
    }

    thisob = TO;
    inv = all_inventory(TP) + all_inventory(thisob);

    if (!parse_command(scrapstr, inv, "%o", scraps) ||
        !scraps->id(SIRITH_SCRAPS) ||
        !parse_command(herbstr, inv, "%o", herb))
    {
	NF0(capitalize(vb)+" what?\n");
    }

    if (!herb->id("herb"))
    {
	NFN0("You can't seem to "+vb+" the "+herbstr+" and the scraps.");
    }

    if (ENV(herb) != thisob ||
	ENV(scraps) != thisob)
    {
	NFN0("It would be easier to "+vb+" the "+herbstr+" into the scraps "+
	    "if they both were in the bowl.");
    }

    write("You "+vb+" the "+herbstr+" into the scraps.\n");
    if (pointerp(herb_effects = herb->query_effect()))
    {
    	for (i = 2, n = sizeof(herb_effects); i < n; i += 3)
	{
    	    if (herb_effects[i-2] == HERB_POISONING)
	    {
		/* might as well pass the poison strength to the scraps,
		 * since we know its index.
		 */
		scraps->add_poison(herb, herb_effects[i]);
		break; /* for */
	    }
	}
    }
    herb->remove_object();
    return 1;
} /* do_mix */


/*
 * Function name:	enter_env
 * Description	:	mask parent so bowl breaks if dropped
 * Arguments	:	object dest -- the new env
 *			object from -- the old env
 */
public void
enter_env(object dest, object from)
{
    ::enter_env(dest, from);
    if (objectp(dest) &&
	dest->query_prop(ROOM_I_IS))
    {
	set_alarm(0.2, 0.0, break_bowl);
    }
} /* enter_env */


/*
 * Function name:	break_bowl
 * Description	:	break the bowl and scatter any scraps if dropped
 *
 * Need to do this because players are leaving the bowl of scraps sitting in
 * the sty, which makes it just a little too easy for the next person.
 */
public void
break_bowl()
{
    object	ob, *inv = all_inventory(TO), env = ENV();
    string	breakstr, floor;
    int		s = sizeof(inv);

    floor = (env->query_prop(ROOM_I_INSIDE) ? "floor" : "ground");
    breakstr = "The blue chipped bowl shatters as it hits the "+floor+".\n";
    if (objectp(Liquid))
    {
	breakstr += "Some "+Liquid->query_name()+
		    " spills from the shattered bowl.\n";
	Liquid->remove_object();
    }
    while (s-- > 0)
    {
	if (inv[s]->id(SIRITH_SCRAPS))
	{
	    breakstr += BSN("Some kitchen scraps spill from the shattered bowl "
		      + "and crumble to bits when they hit the "+floor+".");
	    inv[s]->remove_object();
	}
	else
	{
	    breakstr += capitalize(LANG_ASHORT(inv[s]))
		      + " falls from the shattered bowl.\n";
	    if (inv[s]->move(env))
	    {
		inv[s]->move(env, 1);
	    }
	}
    }
    tell_room(env, breakstr);
    remove_object();
} /* break_bowl */
