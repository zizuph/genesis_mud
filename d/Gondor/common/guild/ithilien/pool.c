/*
 * /d/Gondor/common/guild/ithilien/pool
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 * Based on Elessar's pool (thanks, Elessar!!)
 *
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/area_room";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <stdproperties.h>
#include <composite.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <adverbs.h>

#include "/d/Gondor/defs.h"

#ifndef ROOM_I_NO_ALLOW_STEED
#include "/d/Gondor/std/steed/steed.h"
#endif /* ROOM_I_NO_ALLOW_STEED */

#define	RANGER_ITHILIEN_VISITOR	"ranger_ithilien_visitor"
#define	MIN_CLIMB_SKILL		25
#define	MIN_FATIGUE		50
#define	ITHILIEN_POOL_INTRUDER	"_ithilien_pool_intruder"

public void	create_area_room();
public void	init();
public int	do_swim(string str);
public int	do_dive(string arg);
public int	do_climb(string arg);
public int	do_enter(string arg);
public int	do_listen(string arg);
public int	do_splash(string arg);
public int	do_duck(string arg);
public int	do_float(string arg);
public void	enter_inv(object ob, object from);
public void	leave_inv(object ob, object to);
public string	query_swimmers();
public int	unq_no_move(string arg);
public void	wash_away(object pl);


/*
 * Function name:	create_area_room
 * Description	:	set up the room
 */
public void
create_area_room()
{
    set_areatype(999);	/* bad value so it doesn't do default config */
    set_areadesc("stone walled pool");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("cedar");
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);

    set_extraline(
	"The waters of the pool form a beautiful veil as they fall from "+
	"a large "+
        "rock to swirl and foam in the oval stone basin. The "+
        "steady splash of the waters masks the other sounds of "+
	"the forest. The walls of the basin are high and steep; the "+
	"only egress is a narrow cleft in the west wall, through "+
	"which the waters churn and flow away.");

    add_item( ({ "oval basin", "basin", "bowl", "pool" }), BSN(
	"The oval basin is filled with foaming waters that plunge "+
	"into the pool from the top of the rock. "+
	"The waters swirl around in the bowl before flowing away, "+
	"fuming and chattering, through a narrow cleft "+
	"into calmer and more level reaches to the west."));
    add_item( ({ "western wall", "west wall", "narrow cleft", "cleft" }),
	BSN(
	"The waters find their way out of the pool through a narrow "+
	"cleft to the west."));
    add_item( ({ "wall", "rocks", "rock wall", "rock walls", "walls",
	"cliff", "cliffs" }), BSN(
	"The walls of the basin are steep and featureless, "+
	"pierced only by a narrow cleft to the west end. " +
	"Over a flat even edge at the top of the north wall, "+
	"a waterfall plunges down into the pool."));
    add_item( ({ "edge", "flat edge", "even edge", "flat even edge",
	"northern wall", "north wall", "large rock", "rock", "veil",
	"fall", "falls", "waterfall", "waters", "water" }), BSN(
	"Water plunges from a flat even edge at the top of "+
	"the rock, shaping the fall into a sparkling veil "+
	"that pours into the pool."));
    add_item( ({ "tops", "tops of trees", "treetops", "tree tops",
	"forest", "tree", "trees" }), BSN(
	"Only the very tops of trees are visible above the walls "+
	"of the pool."));

    add_prop(OBJ_I_CONTAIN_WATER, -1);
    set_drink_from( ({ "pool", "basin", "bowl", "waterfall" }) );
} /* create_area_room */


/*
 * Function name:	init
 * Description	:	add player verbs
 */
public void
init()
{
    ::init();
    init_drink();
    add_action(do_swim, "swim");
    add_action(do_dive, "dive");
    add_action(do_climb, "climb");
    add_action(do_enter, "enter");
    add_action(do_listen, "listen");
    add_action(do_splash, "splash");
    add_action(do_duck, "duck");
    /* strictly speaking, "dunk" is something you do with a doughnut
     * and a cup of coffee, but many people seem to try this rather
     * than "duck", so what the heck ...
     */
    add_action(do_duck, "dunk");
    add_action(do_float, "float");
} /* init */


/*
 * Function name:	do_swim
 * Description	:	handle movement around the pool
 * Arguments	:	string arg -- the direction to swim
 * Returns	:	1 if a good direction, 0 if not
 */
int
do_swim(string arg)
{
    object	tp = TP;

    if (tp->query_prop(ITHILIEN_POOL_INTRUDER))
    {
	NFN0("Swim where?");
    }

    if (arg == "w" ||
	arg == "west" ||
	arg == "through cleft" ||
	arg == "cleft")
    {
	write(BSN("You swim through the cleft in the west wall of the basin."));
	SAYBB(" swims through the cleft in the west wall.");
	write(BSN("The waters grow calmer and you climb out of the stream."));
	tp->move_living("M", (ITH_DIR+"nforest/sstream9"));
	if (TP != tp)
	{
	    set_this_player(tp);
	}
	tell_room(ENV(tp),
	    QCNAME(tp)+" climbs out of the stream.\n", tp);
    }
    else if (arg == "beneath waterfall" ||
	     arg == "beneath falls" ||
	     arg == "beneath fall" ||
	     arg == "beneath veil")
    {
	SAYBB(" disappears beneath the waterfall.");
	write(BSN("You swim beneath the plunging waterfall for "+
	    "a moment, then are swept out into the pool."));
	SAYBB(" emerges from the waterfall.");
    }
    else
    {
	write("You swim in the foaming waters.\n");
	SAYBB(" swims about the pool.");
    }

    return 1;
} /* do_swim */


/*
 * Function name:	do_dive
 * Description	:	respond to attempts to dive
 * Arguments	:	string arg -- whatever the player typed (unused)
 * Returns	:	1  (always succeeds)
 */
public int
do_dive(string arg)
{
    string tmpstr;
    if (strlen(arg) &&
	arg != "down" &&
        !parse_command(arg, ({ }),
		       "'into' / 'in' / 'beneath' / 'under' / 'below' "+
		       "%s 'water' / 'waters' / 'pool'", tmpstr))
    {
	NF0("Dive where?\n");
    }

    write(BSN( ({
	"You dive beneath the surface of the water for a moment, "+
	    "then return to the surface.",
	"You dive into the foaming waters, but emerge rather quickly when "+
	    "you run out of air.",
	"You dive towards the bottom of the pool"+
	    ", then bob to the surface again."
	})[random(3)]) );
    SAYBB(" dives under the water and then surfaces again.");
    return 1;
} /* do_dive */


/*
 * Function name:	do_climb
 * Description	:	respond to attempts to climb
 * Arguments	:	string arg -- whatever the player typed (unused)
 * Returns	:	1  (always succeeds)
 */
public int
do_climb(string arg)
{
    if (TP->query_prop(ITHILIEN_POOL_INTRUDER))
	NF0("Climb what?\n");
	
    if (arg == "waterfall" ||
	arg == "falls" ||
	arg == "fall" ||
	arg == "veil")
    {
	return do_enter("waterfall");
    }

    if (arg == "up")
    {
	arg = "wall";
    }

    /* singular arg */
    if (arg == "wall" ||
	arg == "cliff" ||
	arg == "rock" ||
	arg == "north wall" ||
	arg == "northern wall" ||
	arg == "west wall" ||
	arg == "western wall" ||
	arg == "south wall" ||
	arg == "southern wall" ||
	arg == "east wall" ||
	arg == "eastern wall")
    {
	write(BSN(
	    "You swim to the edge of the pool and try to climb the "+
	    arg+", but it is much too steep. You fall back into "+
	    "the water with a loud splash."));
	SAY(" tries to climb the wall of the basin, but falls back "+
	    "into the water with a loud splash.");
	return 1;
    }

    /* plural arg */
    if (arg == "walls" ||
	arg == "cliffs" ||
	arg == "rocks")
    {
	write(BSN(
	    "You swim to the edge of the pool and try to climb the "+
	    arg+", but they are much too steep. You fall back into "+
	    "the water with a loud splash."));
	SAY(" tries to climb the wall of the basin, but falls back "+
	    "into the water with a loud splash.");
	return 1;
    }

    NF0("Climb what?\n");

} /* do_climb */


/*
 * Function name:	do_enter
 * Description	:	respond to attempts to enter waterfall
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we understand the arg, 0 if not
 */
public int
do_enter(string arg)
{
    object	tp = TP;

    if (tp->query_prop(ITHILIEN_POOL_INTRUDER) ||
        (arg != "waterfall" &&
	 arg != "falls" &&
	 arg != "fall" &&
         arg != "veil"))
    {
	NF0(capitalize(query_verb())+" what?\n");
    }

    write(BSN(
	"You swim beneath the waterfall and attempt to climb "+
	"the wet, slippery rocks."));
    SAYBB(" disappears beneath the waterfall.");

    if (tp->query_skill(SS_CLIMB) >= MIN_CLIMB_SKILL &&
        tp->query_fatigue() >= MIN_FATIGUE && 
        tp->query_encumberance_weight() <= 80)
    {
	write(BSN("With some difficulty, you scramble up the rocks "+
	    "beneath the plunging water and emerge on solid ground."));
	tp->move_living("M", (RANGER_ITH_DIR+"window"));
	if (TP != tp)
	{
	    set_this_player(tp);
	}
	tell_room(ENV(tp),
	    QCNAME(tp)+" emerges from the waterfall.\n", tp);
    }
    else
    {
	write(BSN(
	    "You fall from the rocks and are swept out "+
	    "into the pool."));
	SAYBB(" emerges from the waterfall.");
    }
    return 1;
} /* do_enter */


/*
 * Function name:	do_listen
 * Description	:	respond to attempts to listen
 * Arguments	:	string arg -- whatever the player typed (unused)
 * Returns	:	1 (always)
 *
 * All you can hear in the pool is the water.
 */
public int
do_listen(string arg)
{
    write(BSN("The rhythmic plash of falling waters "+
	"masks all other sounds."));
    return 1;
} /* do_listen */


/*
 * Function name:	do_splash
 * Description	:	respond to attempts to splash people
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_splash(string arg)
{
    object	*target,
		*inv, 
		tp;
    int		s;

    if (!strlen(arg) ||
	arg == "water")
    {
	WRITE("You splash water high into the air -- wheee!");
	SAY(" splashes water high into the air.");
	return 1;
    }

    arg = LOW(arg);
    tp = TP;
    if (arg != "me" &&
	arg != "myself" &&
	arg != tp->query_real_name())
    {
	inv = all_inventory(TO);
	if (!parse_command(arg, inv, "[water] [on] / [at] %l", target))
	{
	    NF0("Splash whom?\n");
	}

	target = NORMAL_ACCESS(target, 0, 0);
    }
    else
    {
	target = ({ tp }); 
    }

    if (!(s = sizeof(target)))
    {
	NF0("Splash whom?\n");
    }

    while (s-- > 0)
    {
	if (target[s] != tp)
	{
	    tp->catch_msg("You splash water at "+QTNAME(target[s])+".\n");
	    target[s]->catch_msg(QCTNAME(tp)+" splashes water at you.\n");
	    say(QCTNAME(tp)+" splashes water at "+QTNAME(target[s])+".\n", 
		({ tp, target[s] }) );
	}
	else
	{
	    write("You splash water on your face. Ahhh, that's refreshing.\n");
	    SAY(" splashes water on "+tp->query_possessive()+" face.");
	}
    }

    return 1;
} /* do_splash */


/*
 * Function name:	do_duck
 * Description	:	respond to attempts to duck people
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_duck(string arg)
{
    object	*target,
		*inv, 
		tp;
    int		s;

    if (!strlen(arg))
    {
	WRITE("You duck beneath the water for a moment.");
	SAY(" ducks beneath the water for a moment.");
	return 1;
    }

    inv = all_inventory(TO);
    arg = LOW(arg);
    if (!parse_command(arg, inv,
		       "%l [under] / [beneath] / [in] [the] [pool] "+
		       "/ [water]", target))
    {
	NF0("Duck whom?\n");
    }

    target = NORMAL_ACCESS(target, 0, 0);
    if (!(s = sizeof(target)))
    {
	NF0("Duck whom?\n");
    }
    if (s > 1)
    {
	NF0("You can't duck that many people at once!\n");
    }

    tp = TP;
    if (target[0] == tp)
    {
	/* XXX cannot happen -- NORMAL_ACCESS removes TP */
	write(BSN("You duck beneath the water for a moment."));
	SAY(" ducks beneath the water for a moment.");
	return 1;
    }

    say(QCTNAME(tp)+" dives into the water.\n", tp);
    tp->catch_msg("You dive towards the bottom of the pool and, grabbing "+
	QTNAME(target[0])+"'s ankles, pull "+target[0]->query_objective()+
	" beneath the water!\n");
    tell_object(target[0],
	"Something grabs your ankles and pulls you beneath the water!\n");
    say("Suddenly, "+QTNAME(target[0])+" is pulled beneath the water!\n", 
	({ tp, target[0] }) );
    tp->catch_msg("You release your grip on "+QTNAME(target[0])+".\n");
    tell_object(target[0],
	"You bob back to the surface as the grip on your ankles "+
	"is released.\n");
    say(QCTNAME(target[0])+" bobs to the surface.\n", ({ tp, target[0] }) );
    write("You return to the surface.\n");
    say(QCTNAME(tp)+" rises to the surface.\n", tp );
    return 1;
} /* do_duck */


/*
 * Function name:	do_float
 * Description	:	respond to attempts to float
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_float(string arg)
{
    string	adv, poss = TP->query_possessive();

    if (!strlen(arg))
    {
	arg = "here";
    }
    else if (strlen(adv = FULL_ADVERB(arg)))
    {
	arg = adv;
    }

    switch (arg)
    {
    case "here": case "lazily": case "in pool": case "in water":
	write(BSN("You float lazily in the pool, eyes closed and "+
	    "mind deliciously empty."));
	SAY(" floats lazily in the pool. "+capitalize(poss)+
	    " eyes are closed and there's a blissful smile on "+poss+" face.");
	break;
    case "happily":
	write(BSN("You float happily in the pool, making little "+
	    "splashes with your toes."));
	SAY(" floats happily in the pool, making little "+
	    "splashes with "+poss+" toes.");
	break;
    case "idly": case "n": case "s": case "e": case "w": case "ne": case "nw":
    case "se": case "sw": case "north": case "south": case "east": case "west":
    case "northeast": case "northwest": case "southeast": case "southwest":
	write(BSN("You float idly in the pool, unable to control "+
	    "your direction of movement."));
	SAY(" floats idly in the pool.");
	break;
    default:
	NF0("Float how?\n");
    }
    return 1;
} /* do_float */



/*
 * Function name:	enter_inv
 * Description	:	check if ob is allowed to enter
 * Arguments	:	object ob -- the entering object
 *			object from -- where they came from
 *
 * XXX was using LIVE_S_EXTRA_SHORT, but gorboth said it
 * gave weird results with some of the Morgul Mages souls.
 */
public void
enter_inv(object ob, object from)
{
    object	gnad;	/* XXX temporary */

    ::enter_inv(ob, from);

    if (living(ob))
    {
        if (present("_kalad_dirty_object", ob))
	{
            present("_kalad_dirty_object", ob)->remove_object();
	}
	if (ob->query_dirty_shadow() == 666)
	{
	    ob->remove_shire_filthy_shadow();
	}

	if (ob->query_guild_name_occ() != "Gondorian Rangers Guild" &&
        ob->query_guild_name_occ() != "Rangers of the North" &&
    	    !ob->query_prop(RANGER_ITHILIEN_VISITOR) &&
	    !ob->query_wiz_level() &&
	    MASTER_OB(ob) != (RANGER_DIR + "obj/pigeon"))
	{
	    set_alarm(0.1, 0.0, &wash_away(ob));
	    ob->add_prop(ITHILIEN_POOL_INTRUDER, 1);
	}
    }
    else
    {
	set_alarm(1.0, 0.0, &wash_away(ob));
    }
} /* enter_inv */


/*
 * Function name:	leave_inv
 * Description	:	remove props from objects when they leave
 * Arguments	:	object ob -- the entering object
 *			object to -- where they're going
 */
public void
leave_inv(object ob, object to)
{
    if (living(ob))
    {
	ob->remove_prop(ITHILIEN_POOL_INTRUDER);
    }
    ::leave_inv(ob, to);
} /* leave_inv */


/*
 * Function name:	query_swimmers
 * Description	:	describe who's in the pool
 * Returns	:	string -- the description
 */
public string
query_swimmers() 
{
    object	*swimmers;
    int		s;

    swimmers = FILTER_LIVE(all_inventory(TO));
    if (!(s = sizeof(swimmers)))
    {
	return "";
    }
    if (s == 1)
    {
	return swimmers[0]->query_Art_name(TP)+
	    " is swimming in the foaming waters of the pool. ";
    }
    return capitalize(
	COMPOSITE_WORDS(
	FILTER_LIVE(all_inventory(TO))->query_art_name(TP)))+
	" are swimming in the foaming waters of the pool. ";
} /* query_swimmers */


/*
 * Function name:	unq_no_move
 * Description	:	mask parent so players can swim around the pool
 *			in all directions, even tho no exits have
 *			been added
 * Arguments	:	string arg - the command line argument.
 * Returns	:	1 (always)
 */
public int
unq_no_move(string arg)
{
    string	vb = query_verb();

    if (vb == "up")
    {
	return do_climb("walls");
    }
    if (vb == "down")
    {
	return do_dive("");
    }
    return do_swim(query_verb());
} /* unq_no_move */


/*
 * Function name:	wash_away
 * Description	:	float intruders and nonlivings downstream
 * Arguments	:	object ob -- the intruding object
 */
public void
wash_away(object ob)
{
    string desc1, desc2, vb;
    if (!objectp(ob))
	return;
    if (living(ob))
    {
	tell_object(ob,
	    BSN("The foaming waters sweep you downstream."));
	tell_room(TO,
	    QCNAME(ob)+" is swept downstream by the foaming waters.\n", ob);
	tell_object(ob,
	    BSN("The waters grow calmer and you climb out of the stream."));
	ob->move_living("M", (ITH_DIR+"nforest/sstream9"));
	tell_room(ENV(ob),
	    QCNAME(ob)+" climbs out of the stream.\n", ob);
    }
    else
    {
	/* using "the "+ short() in this msg looks silly for heaps:
	 *	The a piece of ham washes downstream.
	 */
	desc1 = ob->short();
	switch( ob->num_heap() )
	{
	case 0:
	    desc2 = CAP(LANG_ADDART(desc1));
	    desc1 = "The "+desc1;
	    vb = "washes";
	    break;
	case 1:
	    desc1 = desc2 = CAP(desc1);
	    vb = "washes";
	    break;
	default:
	    desc1 = desc2 = CAP(desc1);
	    vb = "wash";
	    break;
	}
	tell_room(TO,
	    desc1+" "+vb+" downstream.\n");
	ob->move((ITH_DIR+"nforest/sstream9"), 1);
	tell_room(ENV(ob),
	    desc2+" "+vb+" ashore from the stream.\n");
    }
} /* wash_away */
