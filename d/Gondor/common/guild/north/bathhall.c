/*
 * /d/Gondor/common/guild/north/bathroom.c
 *
 * This is the Rangers of the North's bathroom.
 * Copied from:
 * This file is the hobbit's bathing area.
 * Dunstable, 3-21-95
 *
 * Modification history:
 *
 *	7-Jan-1998, Gnadnar:	remove LIVE_I_DIRTY prop when bathed,
 *				accept "me" as well as "myself"
 *	28-Feb-1998, Gnandar:	add a real fireplace, make room
 *				conform to domain.rules, general
 *				cleanup, add all the stuff from
 *				bathideas
 *	24-Mar-1998, Gnadnar:	use real soap object.
 */

#pragma save_binary

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/open/fireplace/fireplace";

#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include "northern_hq.h"
#include "/d/Gondor/open/fireplace/fireplace.h"

#define RON_I_HAVE_BATHED	"_RoN_i_have_bathed"
#define WET			"i_am_wet"
#define BATHING			"i_am_bathing"
#define DIRTY_SUBLOC		"how_dirty_subloc"
#define WET_SUBLOC		"wet_subloc"
#define	SOAP_ID			"_northern_baths_soap"
#define	TOWEL_ID		"_northern_baths_towel"

#ifndef LIVE_I_DIRTY
#define	LIVE_I_DIRTY		"_live_i_dirty"
#endif

#define BODY_PARTS ({ "face", "neck", "ears", "hair", "back", "arms", \
	    "hands", "toes", "feet", "legs", "chest", "shoulders", "ear", \
	    "arm", "hand", "toe", "foot", "leg", "shoulder" })

#define	ATTENDANT_FILE	(RANGER_NORTH_DIR+"npc/bath_attendant")

static object	Attendant;
static int	Soap_alarm;
static int	Towel_alarm;

public void	create_gondor();
public void	reset_room();
public void	init();
public int	check_exit();
public void	enter_inv(object ob, object from);
public void	leave_inv(object ob, object dest);
public string	exa_reflection();
public int	do_enter(string str);
public int	do_bathe(string str);
public int	do_rinse(string str);
public void	wash_body_part(string where, object pl);
public int	do_splash(string str);
public int	do_relax(string str);
public int	do_stand(string str);
public void	att_get_soap();
public void	att_get_towels();
public int	get_soap(string str);
public int	get_towel(string str);
public string	show_subloc(string subloc, object pl, object for_obj);
public string	expel_aggressive();
public string	fire_desc(string str);
static void	stop_the_fire();
public void	restart_fire();

/*
 * Function name:	create_gondor
 * Description	:	set up the room
 */
public void
create_gondor()
{
    set_short("in the Bath hall");
    set_long(fire_desc);
    set_parse_pattern("[the] [great] [stone] 'fireplace'");
    add_item( ({ "stone fireplace", "great fireplace", 
	"great stone fireplace", "fireplace" }), &fire_desc("fireplace"));
    add_item( ({ "fire", "flame", "flames" }), &fire_desc("fire"));
    add_item( ({ "wood", "firewood", "wood in fireplace",
	         "firewood in fireplace" }),
	&fire_desc("wood"));
    add_item( ({ "ash", "ashes", "ash in fireplace", "ashes in fireplace" }),
	&fire_desc("ashes"));


    add_item("walls", BSN(
	"The walls are solid grey stone, smooth and damp with "
      + "moisture from the tubs."));
    add_item(({"mats", "matting", "rushes", "rush matting", "floor"}),
	"The floor is covered with soft rush matting.\n");
    add_item(({"grey stone", "stone"}),
	"The stone is smooth, grey and slightly damp.\n");
    add_item("ceiling", BSN(
	"The ceiling is simply bare stone, lightly beaded "
      + "with moisture."));
    add_item("west wall", BSN(
	"A large sink and a rack of soaps stand along the "
      + "west wall. Above the sink hangs a long mirror."));
    add_item("south wall", &fire_desc("wall"));
    add_item(({"east wall", "towels", "towel hook", "towel hooks",
	"hook", "hooks"}), 
      "Plush towels hang on hooks along the east wall.\n");
    add_item(({"arch", "archway", "north wall"}),
	"An open archway leads north.\n");
    add_item("sink", BSN(
	"The sink, large and built of polished grey stone, "
      + "is filled with hot water."));
    add_item(({"soaps", "soap", "rack", "soap rack"}), 
	"The rack is filled with an assortment of soaps.\n");
    add_item("mirror", BSN(
	"The long mirror is made of polished metal. Your reflection "
      + "in it is fogged with moisture from the tubs."));
    add_item("reflection", exa_reflection);   
    add_item(({"row", "rows"}),
	"The wooden tubs are arranged in rows.\n");
    add_item(({"tub", "tubs", "wooden tub", "wooden tubs"}), BSN(
	"The heavy oak tubs are large enough to hold quite a lot "
      + "of hot water."));
    add_item(({"hot water", "water"}),
	"The sink and some of the tubs are filled with steaming hot "
      + "water.\n");

    add_cmd_item( "soap", ({ "pick", "get", "take" }), get_soap);
    add_cmd_item( "towel", ({ "pick", "get", "take" }), get_towel);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_HIDE,  -1);
    add_prop(ROOM_M_NO_ATTACK, expel_aggressive);
    add_prop(ROOM_M_NO_MAGIC_ATTACK, expel_aggressive);
      
    add_exit((RANGER_NORTH_DIR+"inn"), "north", check_exit);
    reset_room();  
} /* create_gondor */


/*
 * Function name:	reset_room
 * Description	:	be sure attendant, hamper and stand are present
 */
public void  
reset_room()
{ 
    object	hamper,
		*towels;

    Attendant = clone_npc(Attendant, ATTENDANT_FILE);

    set_wood(20);
    if (query_fire_state() != FIRE_BURNING)
    {
	Attendant->command("light fire");
    }
   
    if (!objectp(hamper = present("hamper", TO)))
    {
	clone_object(RANGER_NORTH_DIR+"obj/hamper")->move(TO);
    }
    else
    {
	towels = filter(all_inventory(hamper), &->id("towel"));
	if (sizeof(towels))
	{
    	    Attendant->command("emote gathers some towels from "
			     + "the hamper and takes them for "
			     + "cleaning.");
	    towels->remove_object();
	}
    }

    if (!objectp(present("stand", TO)))
    {
	clone_object(RANGER_NORTH_DIR+"obj/clothes_stand")->move(TO);
    }

} /* reset_room */


/*
 * Function name:	init
 * Description	:	add player verbs
 */
public void
init()
{
    ::init();
    init_fire();

    add_action(do_bathe, "wash");
    add_action(do_bathe, "clean");
    add_action(do_bathe, "bathe");
    add_action(do_rinse, "rinse");
    add_action(do_enter, "enter");
    add_action(do_stand, "stand");  
    add_action(do_stand, "leave");  
    add_action(do_stand, "out");  
    add_action(do_splash, "splash");
    add_action(do_relax, "relax");

} /* init */


/*
 * Function name:	check_exit
 * Description	:	don't allow exit til have finished bathing
 * Returns	:	0 if may exit, 1 if not
 */
public int
check_exit()
{
    object	tp = TP,
		*inv,
		*soaps,
		*towels,
		towel;

    if (objectp(Attendant))
    {
	if (tp->query_prop(BATHING))
	{
	    tp->catch_msg(QCTNAME(Attendant) 
		+ " says: You must leave the tub and dry off first.\n");
	    return 1;
	}
	if (tp->query_prop(WET))
	{
	    tp->catch_msg(QCTNAME(Attendant) 
	    	+ " says: You must dry yourself before leaving.\n");
	    if (!objectp(towel = present("towel",tp)) ||
	        towel->query_wet())
	    {
		Attendant->give_towel(tp);
	    }
	    return 1;
	}

	inv = deep_inventory(tp);
	soaps = filter(inv, &->id(SOAP_ID));
	towels = filter(inv, &->id(TOWEL_ID));
	if (sizeof(soaps))
	{
	    tp->catch_msg(QCTNAME(Attendant) + " blocks the exit.\n"
		+ QCTNAME(Attendant)
	        + " says: Please give your soap to me.\n"
		+ QCTNAME(Attendant)
	        + " says: You should not take guild property.\n");
	    return 1;
	}
   
	if (sizeof(towels))
	{
	    tp->catch_msg(QCTNAME(Attendant) + " blocks the exit.\n"
		+ QCTNAME(Attendant)
	        + " says: Please leave your towel in the hamper.\n"
		+ QCTNAME(Attendant)
	        + " says: You should not take guild property.\n");
	    return 1;
	}

	Attendant->command("shout Make sure you have all of your belongings!");
	return 0;
    }

    /* no attendant -- fake it */
    if (tp->query_prop(BATHING))
    {
	tp->command("$stand up");
	tp->remove_prop(BATHING);
    }
    if (tp->query_prop(WET))
    {
	tp->remove_prop(WET);
	tell_object(tp, "You take a clean towel from one of the hooks.\n"+
	     "You dry yourself off.\n"+
	     "You put the towel in the hamper.\n");
	say(QCTNAME(tp)+" takes a clean towel from one of the hooks.\n"+
	     QCTNAME(tp)+" dries "+OBJECTIVE(tp)+"self off.\n"+
	     QCTNAME(tp)+" puts a towel in the hamper.\n", tp);
    }
    inv = deep_inventory(tp);
    soaps = filter(inv, &->id(SOAP_ID));
    towels = filter(inv, &->id(TOWEL_ID));
    if (sizeof(soaps))
    {
	
	tell_object(tp, "You return your soap to the rack.\n");
	say(QCTNAME(tp)+" returns some soap to the rack.\n");
	soaps->remove_object();
    }
    if (sizeof(towels))
    {
	
	tell_object(tp, "You put your towels in the hamper.\n");
	say(QCTNAME(tp)+" puts some towels in the hamper.\n");
	towels->remove_object();
    }
    return 0;   
} /* check_exit */


/*
 * Function name:	enter_inv
 * Description	:	after parent, check for dropped towels
 * Arguments	:	object ob -- the entering object
 *			object from -- where it came from
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (objectp(Attendant))
    {
	if (!Soap_alarm &&
	    ob->id("soap"))
	{
	    Soap_alarm = set_alarm(6.0, 0.0, att_get_soap);
	}
	if (!Towel_alarm &&
	    ob->id("towel"))
	{
	    Towel_alarm = set_alarm(6.0, 0.0, att_get_towels);
	}
    }
} /* enter_inv */


/*
 * Function name:	leave_inv
 * Description	:	mask parent to remove any tmp properties
 *			when player leaves the room
 * Arguments	:	object ob -- the departing object
 *			object dest -- where it's going
 */
public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    ob->remove_prop(WET);
    ob->remove_prop(BATHING);
    ob->remove_prop(LIVE_S_EXTRA_SHORT);
    ob->remove_subloc(WET_SUBLOC);
} /* leave_inv */



/*
 * Function name:	exa_reflection
 * Description	:	look at oneself in the mirror
 * Returns	:	string -- the reflection desc
 */
public string
exa_reflection()
{
    string	txt;
    int		day = CLOCK->query_day();

    txt = "The lightly fogged reflection is that of yourself. " +
	  "You are a " +
	   (TP->query_gender() == G_MALE ? "handsome man" :
      					   "lovely woman") + ", ";
    if (strlen(TP->desc_scar()))
    {
	txt += "even with scars on your " + TP->desc_scar() + ". ";
    }
    else
    {
	txt += "without a single scar of combat to blemish your body. ";
    }
    if (present("dirty", TP))
    {
	txt += "Right now, " +
		lower_case(TP->show_subloc(DIRTY_SUBLOC, TP, TP)) + ". ";
    }
    if (TP->query_dirty_shadow() == 666)
    {
	txt += "You are still very dirty after having fallen in that puddle. ";
    }
    if (TP->query_prop(RON_I_HAVE_BATHED) < (day - 1))
    {
	txt += "You could definitely use a bath.";
    }
    SAY(" gazes at "+OBJECTIVE(TP)+"self in the mirror.");
    return BSN(txt);
} /* exa_reflection */


/*
 * Function name:	do_enter
 * Description	:	handle attempts to enter tub
 * Arguments	:	string str -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_enter(string str)
{
    int		day = CLOCK->query_day(),
		s;
    object	tp = TP,
		ob;

    if (!strlen(str) ||
	(!parse_command(str, ({}), "[the] / [a] [wooden] [bath] 'tub'") &&
	 !parse_command(str, ({}), "[the] / [a] 'bath'")))
    {
	notify_fail("Enter what?\n");
	return 0;
    }

    if (tp->query_prop(BATHING))
    {
	notify_fail("You are already sitting in a tub.\n");
	return 0;
    }
   
    tp->add_prop(WET, 1);
    tp->add_prop(BATHING, 1);
    tp->add_prop(LIVE_S_EXTRA_SHORT, " sitting in a tub");
    tp->add_subloc(WET_SUBLOC, TO);
   
    write("You walk over to the nearest tub and get ready to splash.\n");

    if ( sizeof(tp->query_armour(-1)) )
    {
	s = sizeof(all_inventory(tp));
	tp->command("$remove all");
	tp->command("$put armours in stand");
	write("You quickly remove the rest of your clothing.\n");
	SAY(" quickly removes the rest of " + POSSESSIVE(tp)
	  + " clothing, and stands there naked for a brief moment.");
    }
    else
    {
	write("You quickly remove your clothing.\n");
	SAY(" quickly removes " + POSSESSIVE(tp)
	  + " clothing, and stands there naked for a brief moment.");
    }

    if (objectp(Attendant) &&
	tp->query_gender() != Attendant->query_gender())
    {
	Attendant->command("blush");
    }

    SAY(" climbs into one of the wooden tubs.");
    write("You climb into one of the wooden tubs.\n");

    if (objectp(Attendant))
    {
	write("The attendant fills your tub with hot water.\n");
	say("The attendant fills "+QTNAME(tp)+"'s tub with hot water.\n");
	write("It's a little too warm at first, but soon you relax and enjoy "
	    + "it.\nAhh!\n");
	SAY(" jumps a bit at the temperature of the water, but "
          + "soon relaxes and appears to enjoy it.");
	if (!objectp(present("soap", tp)))
	{
	    write("The attendant hands you a bar of soap.\n");
	    say("The attendant hands "+QTNAME(tp)+" a bar of soap.\n");
	    FIX_EUID;
	    ob = clone_object(RANGER_NORTH_DIR+"obj/soap");
	    if (ob->move(tp))
	    {
		write("Oops! The soap slips through your fingers.\n");
		SAY(" drops the soap.");
		if (ob->move(TO))
		{
		    ob->move(TO, 1);
		}
	    }
	}
    }

    return 1;  
} /* do_enter */


/* 
 * Function name:	do_bathe
 * Description	:	respond to attempts to bathe
 * Arguments	:	string str -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_bathe(string str)
{
    object	dirtyob,
		*who,
		tp = TP;
    int		day = CLOCK->query_day();
   
    if (!str ||
	str == "me" ||
	str == "myself" ||
	LOW(str) == tp->query_real_name())
    {
	if (!tp->query_prop(BATHING))
	{
	    write(BSN(
		"You walk over to the sink and splash some water "
	      + "on your face. It would probably be more effective "
	      + "to enter a tub and have a proper bath."));
	    SAY(" walks over to the sink and splashes some water "
	      + "on " + POSSESSIVE(TP) + " face. " + CAP(PRONOUN(TP))
	      +	" doesn't look much cleaner, though.");
	    return 1;
	}

	if (!objectp(present("soap", tp)))
	{
	    NF0("You cannot "+QVB+" without soap.\n");
	}

	if (objectp(dirtyob = present("dirty", tp)))
	{
	    dirtyob->remove_object();
	}

	if (tp->query_dirty_shadow() == 666)
	{
	    tp->remove_shire_filthy_shadow();
	}
	tp->remove_prop(LIVE_I_DIRTY);
   
	write("You bathe yourself with soap and hot water.\n");
	SAY(" washes "+OBJECTIVE(tp)+"self in the tub.");
	tp->add_prop(RON_I_HAVE_BATHED, day);
	return 1;

    }

    str = LOW(str);
    if (member_array(str, BODY_PARTS) >= 0)
    {
	if (tp->query_prop("i_am_bathing"))
	{
	    if (!objectp(present("soap", tp)))
	    {
		NF0("You cannot "+QVB+" without soap.\n");
	    }
	    wash_body_part(str, tp);
	    return 1;
	}
	NF0("You should enter a tub first.\n");
    }

    if (parse_command(str, all_inventory(TO), "%l", who) &&
	sizeof(who = NORMAL_ACCESS(who, 0, 0)))
    {
	if (!who[0]->query_prop(BATHING))
	{
	    NF0(CAP(PRONOUN(who[0])) + " isn't bathing.\n");
	}
	if (!objectp(present("soap", tp)))
	{
	    NF0("You cannot "+QVB+" "+QTNAME(who[0])+" without soap.\n");
	}
	tp->catch_msg("You wash " + QTNAME(who[0])
	      + "'s back.\n");
	who[0]->catch_msg(QCTNAME(tp) + " washes your back.\n");
	say(QCTNAME(tp)+" washes " + QTNAME(who[0]) + "'s back.\n",
	    ({ who[0], tp }));
	return 1;
    }
    NF0(CAP(str) + " isn't here.\n");

} /* do_bathe */


/* 
 * Function name:	do_rinse
 * Description	:	respond to attempts to rinse
 * Arguments	:	string str -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_rinse(string str)
{
    object	*who,
		tp = TP;
   
    if (!str ||
	str == "me" ||
	str == "myself" ||
	LOW(str) == tp->query_real_name())
    {
	if (!tp->query_prop(BATHING))
	{
	    write(BSN(
		"You walk over to the sink and splash some water "
	      + "on your face. It would probably be more effective "
	      + "to enter a tub and have a proper bath."));
	    SAY(" walks over to the sink and splashes some water "
	      + "on " + POSSESSIVE(TP) + " face. " + CAP(PRONOUN(TP))
	      +	" doesn't look much cleaner, though.");
	    return 1;
	}
	write("You rinse yourself with hot water.\n");
	SAY(" rinses "+OBJECTIVE(tp)+"self with hot water.");
	return 1;
    }
    if (parse_command(str, all_inventory(TO), "%l", who) &&
	sizeof(who = NORMAL_ACCESS(who, 0, 0)))
    {
	if (!who[0]->query_prop(BATHING))
	{
	    NF0(CAP(PRONOUN(who[0])) + " isn't bathing.\n");
	}
	tp->catch_msg("You rinse " + QTNAME(who[0])
	      + "'s back.\n");
	who[0]->catch_msg(QCTNAME(tp) + " rinses your back.\n");
	say(QCTNAME(tp)+" rinses " + QTNAME(who[0]) + "'s back.\n",
	    ({ who[0], tp }));
	return 1;
    }
    NF0(CAP(str) + " isn't here.\n");
} /* do_rinse */



/*
 * Function name:	wash_body_part
 * Description	:	handle attempts to wash specific part
 * Arguments	:	string where -- which part
 *			object pl -- the player
 */
public void
wash_body_part(string where, object pl)
{
    string	t1,
		t2,
		poss= POSSESSIVE(pl);

    switch(where)
    {
	case "face":
	    t1 = "You cup your hands in the warm water and scoop "
	       + "some up to wash your face.";
	    t2 = " scoops some water up with " + poss
	       + " cupped hands, and washes " + poss + " face.";
	    break;
	case "neck":
	case "shoulders":
	case "shoulder":
	    t1 = "You use some soap and water to gently wash "
	       + "your neck and shoulders.";
	    t2 = " uses some soap and water to gently wash " + poss
	       + " neck and shoulders.";
	    break;
	case "ears":
	case "ear":
	    t1 = "You tilt your head while using a finger "
	       + "to get the dirt out of your ears.";
	    t2 = " tilts " + poss + " head, using a finger "
	       + "to clean " + poss + " ears.";
	    break;
	case "hair":
	    t1 = "You bow your head down towards the water and soak "
	       + "your hair, washing it thoroughly with soap.";
	    t2 = " soaks " + poss + " hair in the bath water, rinsing "
	       + "it and washing it with soap.";
	    break;
	case "back":
	    t1 = "You stretch an arm behind you, and try to wash your back "
	       + "with soap and water.";
	    t2 = " stretches an arm over " + poss + " shoulder, trying "
	       + "to wash " + poss + " back with soap and water.";
	    break;
	case "arms":
	case "arm":
	case "armpits":
	case "armpit":
	    t1 = "You scrub the soap up and down along your arms, "
	       + "washing them in the pleasantly warm water. Then you lift "
	       + "them to wash the sweat from your armpits.";
	    t2 = " scrubs the soap up and down along both " + poss + " arms, "
	       + "washing them with water from the tub. Then " + PRONOUN(pl)
	       + " raises " + poss + " arms to wash " + poss + " armpits.";
	    break;
	case "hands":
	case "hand":
	    t1 = "You wash your hands in the warm water in the tub.";
	    t2 = " washes " + poss + " hands in the warm water in " + poss
	       + " tub.";
	    break;
	case "toes":
	case "toe":
	    t1 = "You use the soap and your fingers to rinse the dirt "
	       + "from between your toes.";
	    t2 = " reaches down " + poss + " leg to clean " + poss + " toes.";
	    break;
	case "feet":
	case "foot":
	    t1 = "You bend your knees so you can reach over to wash "
	       + "your feet.";
	    t2 = " bends " + poss + " knees to reach over and wash " + poss
	       + " feet with soap.";
	    break;
	case "leg":
	case "legs":
	    t1 = "You lift one leg in the air, lathering it with soap before "
	       + "washing it in the pleasantly warm water.";
	    if (pl->query_gender() == G_FEMALE)
	    {
	        t2 = " stretches one shapely leg out of the water to "
		   + "lather it slowly with soap before washing it.";
	    }
	    else
	    {
	        t2 = " stretches one muscular leg out of the water to "
		   + "lather it slowly with soap before washing it.";
	    }
	    break;
	case "chest":
	    t1 = "You lather your chest with soap, then scrub yourself "
	       + "well with your hands, splashing some water on to "
	       + "rinse off the soap.";
	    t2 = " lathers " + poss + " chest with soap, scrubbing "
	       + OBJECTIVE(pl) + "self with " + poss 
	       + " hands, and washing off the soap with water.";
	    break;
	default:
	    t1 = "You wash yourself with soap and hot water.";
	    t2 = " washes " + OBJECTIVE(pl) + "self with soap and hot water.";
	    break;
    }         
    pl->catch_msg(BSN(t1));
    SAY(t2);
    return;
} /* wash_body_part */




/*
 * Function name:	do_splash
 * Description	:	handle attempts to splash
 * Arguments	:	string str -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_splash(string str)
{
    object	*target,
		tp = TP;
    string	who;

    if (!tp->query_prop(BATHING))
    {
	write("You dip your hand in one of the tubs filled "
	  + "with water, and splash a bit. Mmmm, how nice it "
	  + "would be to immerse your entire body in that warm water.\n");
	SAY(" dips " + POSSESSIVE(tp) + " hand in the water "
	  + "in one of the tubs, splashing it a little about.");
	return 1;
    }

    if (!str)
    {
	write("You splash around in the warm water.\nWhee!\n");
	SAY(" splashes around in the tub.");
	return 1;
    }
   
    str = LOW(str);
    if (str == "wildly")
    {
	write("You splash wildly in the tub, drenching your surroundings!\n");
	SAY(" splashes wildly in "+POSSESSIVE(tp)+ " tub, drenching "
	  + "everything in the room, including you!");
	target = FILTER_PRESENT_LIVE(all_inventory(TO));
	target->add_prop(WET, 1);
	target->add_subloc(WET_SUBLOC, TO);
	return 1;
    }

    if (parse_command(str, all_inventory(TO),
		      "[water] [at] / [on] %l", target) &&
	sizeof(target = NORMAL_ACCESS(target, 0, 0)))
    {
	/* just splash first target -- otherwise msgs get too complex */
	tp->catch_msg("You splash some water at " + QTNAME(target[0])
		    + "!\n");
	tell_room(TO,
	    QCTNAME(tp)+" splashes some water at "+QTNAME(target[0])+"!\n",
	    ({ tp,  target[0] }) );
	target[0]->catch_msg(QCTNAME(tp) + " splashes some water at you!\n");
		target[0]->add_prop(WET, 1);
	return 1;
    }

    NFN0("Splash how? Please don't splash wildly, it will soak the room!");
} /* do_splash */

/*
 * Function name:	do_relax
 * Description	:	handle attempts to relac
 * Arguments	:	string str -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_relax(string str)
{
    object	tp = TP;
    if (strlen(str) &&
	!parse_command(LOW(str), ({}), "'in' [the] [wooden] [bath] 'tub'") &&
	!parse_command(LOW(str), ({}), "'in' [the] [hot] [bath] 'water'"))
    {
	NF0("Relax how? Relax in the tub, perhaps?\n");
    }
    if (!tp->query_prop(BATHING))
    {
	write("You dip your hand in one of the tubs filled "
	  + "with water, and splash a bit. Mmmm, how nice it "
	  + "would be to relax in that warm water.\n");
	SAY(" dips " + POSSESSIVE(tp) + " hand in the water "
	  + "of one of the tubs.");
	return 1;
    }
    write(BSN("You lean back to relax, and sink slowly up to your neck "
	+ "in the hot water. Ahhhhh!"));
    SAY(" leans back to relax, and sinks slowly up to "
	+ POSSESSIVE(tp) + " neck in the hot water.");
    return 1;
} /* do_relax */


/*
 * Function name:	do_stand
 * Description	:	handle attempts to stand up
 * Arguments	:	string str -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
int
do_stand(string str)
{
    object	ob,
		tp = TP;
    string	vb = QVB;
   
    if (vb == "leave")
    {
	if (!strlen(str) ||
	    (!parse_command(str, ({}), "[the] [wooden] [bath] 'tub'") &&
	     !parse_command(str, ({}), "[the] 'bath'")))
	{
	    NF0("Leave what?\n");
	}
    }
    else if (vb == "stand" &&
	     strlen(str) &&
	     str != "up")
    {
	NF0("Stand "+str+"? Why not stand up?\n");
    }

    if (!tp->query_prop(BATHING))
    {
	NF0("You are not in a tub.\n");
    }
   
    tp->remove_prop(BATHING);
    tp->remove_prop(LIVE_S_EXTRA_SHORT);
    write("You stand up, dripping water.\n"); 
    SAY(" stands up, " + POSSESSIVE(tp) + " naked body dripping.");

    if (objectp(Attendant))
    {
	if (tp->query_gender() != Attendant->query_gender())
	{
	    Attendant->command("blush");
	}
	if (objectp(ob = present("soap", tp)))
	{
	    write("You give your soap to the bath attendant.\n");
	    SAY(" gives "+POSSESSIVE(tp)+" soap to the bath attendant.");
	    while (objectp(ob))
	    {
		ob->remove_object();
		ob = present("soap", tp);
	    }
	}
	if (!objectp(present("towel", tp)))
	{
	    Attendant->give_towel(tp);
	}
    }
    return 1;   

} /* do_stand */


/*
 * Function name:	att_get_soap
 * Description	:	have attendant pick up soap
 */
public void
att_get_soap()
{
    Soap_alarm = 0;
    if (objectp(Attendant) &&
	present("soap", TO))
    {
	Attendant->command("sigh");
	Attendant->command("get soaps");
	Attendant->command("say I wish people wouldn't drop "+
	   "their soap.");
	Attendant->command("say It makes the floor so slippery.");
    }
} /* att_get_soap */


/*
 * Function name:	att_get_towels
 * Description	:	have attendant pick up towels
 */
public void
att_get_towels()
{
    Towel_alarm = 0;
    if (objectp(Attendant) &&
	present("towel", TO))
    {
	Attendant->command("sigh");
	Attendant->command("say I wish people would use the hamper.");
	Attendant->command("get towels");
	Attendant->command("put towels in hamper");
    }
} /* att_get_towels */


	/*
	 * Function name:	get_soap
	 * Description	:	respond to attempts to get soap
	 * Arguments	:	string str -- whatever the player typed
 *				after "soap"
 * Returns	:	1 on success, 0 on failure
 */
public int
get_soap(string str)
{
    object	tp = TP,
		ob;

    if (objectp(present("soap", tp)))
    {
	write("But you already have some soap.\n");
	return 1;
    }
    if (!strlen(str))
    {
	if(objectp(present("soap", TO)))
	{
	    return 0;	/* get soap from room */
	}
    }
    else if (str != " from rack" &&
	     str != " from soap rack" &&
             str != " from racks" &&
	     str != " from soap racks")
    {
	write("Get soap from where?\n");
	return 1;
    }
    FIX_EUID;
    ob = clone_object(RANGER_NORTH_DIR+"obj/soap");
    write("You get a bar of soap from the soap rack.\n");
    SAY(" gets a bar of soap from the soap rack.");
    if (ob->move(tp))
    {
	write("Oops! The bar of soap slips through your fingers.\n");
	SAY(" drops the soap.");
	if (ob->move(TO))
	{
	    ob->move(TO, 1);
	}
    }
    return 1;
} /* get_soap */


/*
 * Function name:	get_towel
 * Description	:	respond to attempts to get towel
 * Arguments	:	string str -- whatever the player typed
 *				after "towel"
 * Returns	:	1 on success, 0 on failure
 */
public int
get_towel(string str)
{
    object	tp = TP,
		ob;

    if (objectp(present("towel", tp)))
    {
	write("But you already have a towel.\n");
	return 1;
    }

    if (!strlen(str))
    {
	if(objectp(present("towel", TO)))
	{
	    return 0;	/* get towel from room */
	}
    }
    else if (str != " from hook" &&
	     str != " from towel hook" &&
             str != " from hooks" &&
	     str != " from towel hooks")
    {
	write("Get towel from where?\n");
	return 1;
    }
    FIX_EUID;
    ob = clone_object(RANGER_NORTH_DIR+"obj/towel");
    write("You get a towel from one of the hooks.\n");
    SAY(" gets a towel from one of the hooks.");
    if (ob->move(tp))
    {
	write("Oops! The towel slips through your fingers.\n");
	SAY(" drops the towel.");
	if (ob->move(TO))
	{
	    ob->move(TO, 1);
	}
    }
    return 1;
} /* get_towel */


/*
 * Function name:	show_subloc
 * Description	:	generate "foo is dripping wet" msg
 *			for living's desc.
 * Arguments	:	string subloc -- the subloc
 *			object pl -- the player
 *			object for_obj -- who's doing the looking
 * Returns	:	string -- the "is sitting" msg
 */
public string
show_subloc(string subloc, object pl, object for_obj)
{
    string	name;

    if (this_player()->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
        return "";
    }

    if (subloc != WET_SUBLOC)
    {
	return pl->show_subloc(subloc, pl, for_obj);
    }

    if (pl->query_prop(BATHING))
    {
	if (for_obj != pl)
	{
	    return capitalize(pl->query_pronoun()) +
		" is sitting in a tub.\n";
		
	}
	return "You are sitting in a tub.\n";
    }
    if (pl->query_prop(WET))
    {
	if (for_obj != pl)
	{
	    return capitalize(pl->query_pronoun()) + " is dripping wet.\n";
		
	}
	return "You are dripping wet.\n";
    }
    return "";
} /* show_subloc */


/* 
 * Function name:	expel_aggressive
 * Description	:	evict people who start fights
 * Returns	:	"" (msgs are written here)
 */
public string
expel_aggressive()
{
    object	tp;

    if (!objectp(Attendant))
    {
	return "Violence is not permitted here.\n";
    }
    tp = TP;
    Attendant->command("glare "+tp->query_real_name());
    Attendant->command("say Hey! No fighting in the baths!");
    tp->catch_msg(QCTNAME(Attendant)+" hustles you out of the room.\n");
    say(QCTNAME(Attendant)+" hustles "+QTNAME(tp)+" out of the room.\n");
    tp->move_living("M", (RANGER_NORTH_DIR+"inn"));
    SAY(" is propelled into the room.");
    return "";
} /* expel_aggressive */


/*
 * Function name:	fire_desc
 * Description	:	VBFC for fire and related items
 * Arguments	:	string str -- the item
 * Returns	:	string -- the description
 */
public string
fire_desc(string str)
{
    int		fire_state = query_fire_state();

    switch ( str )
    {

    case "wall":
    case "fireplace":
	switch ( fire_state )
	{
	case FIRE_BURNING:
	    return BSN("A great stone fireplace fills the south wall. "+
		"A large fire burns brightly in the fireplace, "+
		"warming the entire room.");
	case FIRE_UNLIT_WOOD:
	    return BSN("A great stone fireplace fills the south wall. "+
		"Firewood is stacked in the fireplace.");
	default:	/* FIRE_ASHES */
	    return "A great fireplace fills the south wall.\n";
	}

    case "fire":
	if ( fire_state == FIRE_BURNING )
	    return BSN("The fire is large and quite hot. Its heat "+
		"fills the room.");
	return BSN("You find no fire.");

    case "wood":
	switch ( fire_state )
	{
	case FIRE_BURNING:
	    return BSN("The wood in the fireplace burns brightly.");
	case FIRE_UNLIT_WOOD:
	   return BSN("Unlit wood is piled in the fireplace.");
	default:	/* FIRE_ASHES */
	    return BSN("You find no firewood.");
	}

    case "ashes":
	switch ( fire_state )
	{
	case FIRE_BURNING:
	    return BSN("Beneath the brightly burning fire, "+
		"ashes cover the bottom of the fireplace.");
	case FIRE_UNLIT_WOOD:
	    return BSN("Beneath the wood, "+
		"ashes cover the bottom of the fireplace.");
	default:	/* FIRE_ASHES */
	    return BSN("Ashes cover the bottom of the fireplace.");
	}

    default:	/* room long description */
	if ( fire_state == FIRE_BURNING )
	    return BSN(
		"Large wooden tubs are arrayed in rows side by side, and from "
	      + "a great fireplace set in the far south wall, a very large "
	      + "fire warms the room. "
	      + "Hooks along the east wall hold plush towels, and below a "
	      + "long mirror mounted on the west wall are a sink and a rack "
	      + "of soaps.");
	return BSN(
		"Large wooden tubs are arrayed in rows side by side, and "
	      + "a great fireplace is set in the far south wall. "
	      + "Hooks along the east wall hold plush towels, and below a "
	      + "long mirror mounted on the west wall are a sink and a rack "
	      + "of soaps.");
    }
    return "";	/* "cannot" happen */
} /* fire_desc */


/*
 * Function name:	stop_the_fire
 * Description	:	mask parent so that bath attendant will restart fire
 */
static void
stop_the_fire()
{
    ::stop_the_fire();
    if (objectp(Attendant))
    {
	set_alarm(3.0, 0.0, restart_fire);
    }
} /* stop_the_fire */


/*
 * Function name:	restart_fire
 * Description	:	have the attendant restart the fire
 */
public void
restart_fire()
{
    set_wood(20);
    if (objectp(Attendant))
    {
	Attendant->command("light fire");
    }
} /* restart_fire */
