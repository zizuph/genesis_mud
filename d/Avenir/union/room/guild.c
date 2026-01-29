#pragma strict_types
/*
 * - /d/Avenir/union/room/guild.c
 *
 * Start room and guild chamber for the Union
 *    Cirion 032196
 *
 * Revisions:
 *   Lilith, May 2004: Changed force_sway time.
 *   Lilith, Jun 2004: Syntax update for getting list of Ceremonies.
 *   Lucius, Dec 2004: Updated the uscry not to use do_glance()
 *   Lucius, Sep 2005: Cleaned up file and modified anti-magic code.
 *	               Improved scry code to show room objects as well.
 *   Lucius, Feb 2009: More cleanup - Added logic to reduce the
 *	               Flame decay rate / levels when active members are
 *	               low or when not logged in.
 *   Lucius, Feb 2009: Modified logic to reduce decay rate slightly, fixed
 *  		       up burn() messages a bit. Add a limiter to prevent
 *  		       over-usage of Firestarter items.
 *   Lucius, Feb 2009: All new item valuation code, more distributed along
 *  		       a curve and capped. Should allow for less tedious flame
 *  		       fillups. Removed BLOCK_EXTINGUISH, can be handled through
 *  		       MIN_FLAME_STATE.  Modified FIRESTARTER value and limiter
 *  		       to encourage members to feed the flame more regularly.
 *   Zielia, Jun 2009: Warriors who come in to the start room will be cured
 *   		       of the Krynn plague.
 *   Lucius, Jul 2011: Modified loggings bits.
 *   Cotillion, Sep 2016: Add a mortal check in reduce_flame
 *   Lucius, Sep 2017: No slow members delay due to huge reduction
 *   		       in FLAME_DIFF. Slightly increase consumption rate.
 *   Lucius, Mar 2018: Add checks to alarm call_outs to prevent runtime errors.
 *   Lilith, May 2022: updated the flavor-text in the burn and feel functions.
 */
#include "../defs.h"

#include <files.h>
#include <macros.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>

inherit BASE;

#undef DEBUG
#define FIRE		(SAVINGS + "flame")
#define FCEREMONY	(CEREMONY + "ceremony_of_the_flame")
#define CPROMOTION	(CEREMONY + "ceremony_of_promotion")
#define FIRESTARTER	"union_is_a_firestarter"
/*
 * Must wait this many periods after using a
 * FIRESTARTER for it to have full effect again.
 * Lengthened to encourage Warriors to do their Duty.
 */
#define LIMITER_INC  (3 + random(6))
/*
 * How much a FIRESTARTER is worth in feed value.
 * This does not get reduced like other items.
 * Reduced to encourage Warriors to do their Duty.
 */
#define FSTARTER_VAL  (MAX_VALUE / 3)
/*
 * Reduce the Flame by this much each active interval.
 * Make sure it's a negative integer!
 */
#define FLAME_REDUCE -(100 + random(51))
/*
 * For every value over this, items are reduced
 * in effective value for feeding the Flame.
 */
#define NORMALIZE    500
/*
 * DIV_BASE - Initial % of value to use.
 * DIV_INC  - Reduce DIVE_BASE this much per normalization increment.
 * DIV_MIN  - Dividend should not fall below this, minimum % of value to use.
 */
#define DIV_BASE     20
#define DIV_INC      5
#define DIV_MIN      5
/*
 * Maximum value any single item will increase the flame by.
 */
#define MAX_VALUE    ((MAX_FLAME_STATE * 5) / 150)
/*
 * Minium 60 minutes (3600 secs) up to 2 hours (7201 secs) interval.
 */
#define ALARM_AMOUNT (3600 + random(3601))
/*
 * Mulitply reduce_flame interval by this much when we
 * are running in SLOW_MEMBERS mode.
 * MUST BE A FLOAT!
 */
#define ALARM_MULTP  5.0
/*
 * At or below this number of members logged in to trigger the
 * alarm multiplier in ALARM_MULTP. Set high to deactivate.
 * Set at 0 to only slow when no members. Uses <= comparison.
 */
#define SLOW_MEMBERS  1

public int alarm, state, last, limiter;

public void reduce_flame(void);
public varargs int change_state(int increment, int silent, string str);
public mixed check_valid(object who, object obj);

public int
go_up(void)
{
    write("You ascend the circular stair.\n");
    return 0;
}

public void
union_room(void)
{
    set_short("the Hall of Shadows");
    set_long("You are in a wide, oval chamber, mostly "
      +"obscured by thick white mist. Vague outlines, like "
      +"shadows dancing in the night, waver at the edge of "
      +"vision. In the east end of the chamber is "
      +"a massive crack@@fire_desc@@. A circular staircase "
      +"carved from granite rises up to the hallway above.\n");

    add_item(({"wall","walls","stone"}),"The stone of the wall "
      +"is pure white and smooth. It is powdery, almost like "
      +"limestone, and reflects what light it receives back into "
      +"the mist.\n");
    add_item(({"mist","fog"}),"It seems almost alive. Shapes "
      +"within it are constantly changing form.\n");
    add_item(({"floor","ground"}),"It is smooth, and pale. At the "
      +"eastern end of the chamber is a massive crack leading "
      +"down.\n");
    add_item(({"stair","staircase"}),"It is a wide, "
      +"circular staircase, made from unadorned white "
      +"stone.\n");
    add_item(({"crack","chasm","abyss"}),"The crack opens "
      +"wide, running along the eastern wall. It seems to "
      +"go down forever, vanishing into an indistinct reddish "
      +"haze far below.@@see_clist@@\n");
    add_item(({"fire","flame","blaze"}),"@@see_flame@@");

    add_cmd_item(({"crack","chasm","abyss",
	    "the crack","the chasm","the abyss",
	    "into the crack","into the chasm","into the abyss"}),
	({"jump","leap"}),"That would be suicide.\n");
    add_cmd_item(({"crack","chasm","abyss",
	    "the crack","the chasm","the abyss",
	    "into the crack","into the chasm","into the abyss"}),
	({"enter","climb"}),"The sides are too sheer to climb down.\n");

    remove_prop(ROOM_M_NO_TELEPORT_TO);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_prop("_union_flame_room", 1);

    add_exit("hall_low", "up", "@@go_up@@", 2);

    restore_object(FIRE);
    alarm = set_alarm(60.0, 0.0, reduce_flame);

    last = 1;
}

public int
has_sphere(object who)
{
    return (present(TOKEN_ID, who) ? 1 : 0);
}

public void
remove_blind(object who)
{
    if (!objectp(who))
	return;

    if (!CAN_SEE_IN_ROOM(who))
	who->catch_tell("The world slowly falls into focus again.\n");

    ALTER_PROP(who, LIVE_I_BLIND, -1);
}

public void
anti_magic_effect(object who)
{
    /* Don't bother with uncast spells. */
    if (!who->query_prop(LIVE_I_CONCENTRATE))
	return;

    /* Inform Warriors of the violation. */
    filter(users(), has_sphere)->catch_tell("Your sphere suddenly "+
	"starts to pulsate with an erratic, chaotic luminesence.\n");

    who->catch_tell("You feel that you are struggling against some "+
	"terrible force.\n");

    if (ENV(who) != TO)
    {
	tell_room(ENV(who),
	  "A dull roaring can be heard from a distance.\n" +
	  "The walls tremble and a faint dusting of black dust "+
	  "fills the air.\n");
    }

    tell_room(TO, "The flame starts to churn and twist wildly, as if "+
	"some great conflict were taking place within it.\n");

    /* Reduce the Flame a bit. */
    change_state(-30 - random(31));

    /* put the player in darkness for a while */
    ALTER_PROP(who, LIVE_I_BLIND, 1);
    set_alarm(60.0 + itof(random(300)), 0.0, &remove_blind(who));

    /* hurt him some too (but don't kill him) */
    who->heal_hp(-50 - random(1000));
    who->add_mana(-50 - random(500));

    /* break his spell */
    who->cmdhooks_break_spell("Your head explodes in agony and "+
	"everything around you goes dark.\n");
}

public void
checkme(object who)
{
    if (!objectp(who))
	return;

    if ((who->query_default_start_location() == HOME) && !IS_MEMBER(who))
	who->set_default_start_location(who->query_def_start());

    if (U_IS_PUNISHED(TP, U_PUNISHED_NOSTART) ||
	U_IS_PUNISHED(TP, U_PUNISHED_NOENTER))
    {
	who->catch_tell("You are no longer allowed to begin within "+
	    "these halls.\n");
	who->set_default_start_location(who->query_def_start());
    }

    int guru = VALID_GURU(who);

    if (guru == -1)
    {
	/* Already tornu */
	who->catch_tell("A thin tendril of fire brushes against you, "+
	    "welcoming you, sending a thrill down your spine.\n");
    }
    else if ((guru == 1) && present(who))
    {
	/* Can begin guru quest. */
	who->catch_tell("You feel a strong force drawing you towards the "+
	    "Flame.\n" + one_of_list(({
		    "You feel sightly dizzy.\n",
		    "Your blood races through your veins.\n",
		    "A thin tendril of fire brushes against you, "+
		        "sending a thrill down your spine.\n" })));
    }
}

/* First thing when waking up in the Halls */
public void
force_sway(object who)
{
    if (objectp(who))
    {
	who->command("$sway");
    }
}

public void
enter_inv(object who, object from)
{
    ::enter_inv(who, from);

    if (!interactive(who))
	return;

    if (!who->query_prop(LIVE_O_LAST_ROOM))
    {
	tell_room(TO, QCNAME(who) +" seems to materialize from the "+
	    "mist.\n", ({ who }) );
	set_alarm(5.0, 0.0, &checkme(who));
	set_alarm(60.0, 0.0, &force_sway(who));
    }
}

public void
leave_inv(object who, object from)
{
    ::leave_inv(who, from);

    if (!interactive(who) || !IS_MEMBER(who) || !who->query_hp() || from)
	return;

    tell_room(TO, QCTNAME(who) + " fades away into the mists.\n",
	({ who }) );
}

public nomask int
query_alarm(void)	{ return alarm; }

public nomask int
query_state(void)	{ return state; }

public string
see_clist(void)
{
    /* Non-members see nothing. */
    if (!IS_MEMBER(TP) && !IS_GMASTER(TP))
	return "";

    /* These Spheres see nothing. */
    switch(TP->query_union_sphere())
    {
    case SPH_DUTY:
    case SPH_TRAINING:
    case SPH_ISOLATION:
	return "";
    }

    return " The flickering shadows from the Flame highlight some "+
	"letters carved into lip of the chasm, they spell \"clist\".";
}

public string
see_flame(void)
{
    if (!state)
	return "There is no fire here anymore.\n";

    return "The flame rises up from the depths of the wide "+
	"crack in the floor. It is a very deep blue hue, almost "+
	"black, and wavers slightly as it rises up.\n";
}

public string
fire_desc(void)
{
    switch(state)
    {
    case 0:
	return ", bare and cold and empty, a wide hollow leading down "+
	    "to the center of the world";
    case 1 .. 50:
	return " opening into the floor, out of which a very faint "+
	    "black flame glows, on the verge of going out";
    case 51 .. 400:
	return " from which a very small flame rises, its black unearthly "+
	    "colour making the mist flicker with eerie shadows";
    case 401 .. 1000:
	return ", out of which a small black flame burns, twisting "+
	    "and casting strange shadows";
    case 1001 .. 2600:
	return " from which a small flame burns, its dark glow lighting "+
	    "the chamber and creating long and strange shadows in the mist";
    case 2601 .. 4000:
	return " in which a medium sized flame burns, its eerie black "+
	    "glow reaching halfway up the chamber. Its light creates "+
	    "strange and eerie shadows";
    case 4001 .. 6000:
	return " in which a large flame burns, casting a strong dark "+
	    "blue glow around the chamber and warming you against the "+
	    "cold mist";
    case 6001 .. 8000:
	return " in which a very large flame burns, so blue it is almost "+
	    "black, reaching nearly to the ceiling. The fire makes a low "+
	    "hissing noise as it burns, and seems to bring order to the "+
	    "swirling mist about";
    case 8001 .. MAX_FLAME_STATE:
	return " in which an inferno burns, touching the ceiling and "+
	    "spreading out across the room. The flame is twisting into "+
	    "itself in a terrifying spiral, fearsome and strong, and "+
	    "makes a dull roaring sound as it rises from the abyss below";
    default:
	return " that leads down into darkness. It is cold and empty";
    }
}

public void
reduce_flame(void)
{
    float ival = itof(ALARM_AMOUNT);
    object *list = FILTER_IS_MORTAL(users());

#if 0
#ifdef STATUE_WHEN_LINKDEAD
#ifdef OWN_STATUE
    list |= (object *)OWN_STATUE->query_linkdead_players();
#endif OWN_STATUE
#endif STATUE_WHEN_LINKDEAD
#endif

    int size = sizeof(filter(list,
	&operator(==)(, OCC_NAME) @ &->query_guild_name_occ()));

    /* If this cycle and last cycle had no members, don't reduce. */
    if (size || last)
	change_state(FLAME_REDUCE);

    /* If active / present members is low, slow down the timer. */
    if (size <= SLOW_MEMBERS)
	ival *= ALARM_MULTP;

    if (limiter > 0)
	limiter--;

    /* Chance of reduction, even if nobody awakes. */
    last = (size ?: !random(3));

    /* Re-launch the timer. */
    alarm = set_alarm(ival, 0.0, reduce_flame);
}

public int
enter(string str)
{
    if (!strlen(str) || STATE < 0)
	return notify_fail("Enter what?\n");

    if (!parse_command(str, ({}), "[the] 'flame' / 'fire'"))
	return notify_fail("Enter what?\n");

    say(QCTNAME(TP) + " approaches the fire.\n");

    if (ENEMY(TP))
    {
	write("The fire engulfs and burns you!\n");
	say("The dark fire engulfs and burns " + QTNAME(TP) + ".\n");
	TP->heal_hp(-500);
	return 1;
    }

    if (!IS_MEMBER(TP) && !IS_GMASTER(TP))
    {
	write("The flame resists you.\n");
	return 1;
    }

    int guru = VALID_GURU(TP);

    /* Already tornu. */
    if (guru == -1)
    {
	write("You enter the Flame, and immediately the shadows are "+
	    "drawn about you, brushing against you like ethereal fingers.\n");
	say(QCTNAME(TP) + " vanishes into the Fire.\n");

	if (!TP->move_living("M", ROOM + "altar_room", 1))
	{
	    tell_room(ROOM + "altar_room", QCTNAME(TP) +
	      " emerges from the Fire.\n", ({ TP }), TP);
	}
	return 1;
    }

    /* Not eligible. */
    if (guru == 0)
    {
	write("You pass through the Fire, as if it were not there.\n");
	say(QCTNAME(TP) + " passes through the fire, as if were not there.\n");
	return 1;
    }

    /* Allow to start guru quest. */
    write("You enter the Flame, and immediately the shadows are drawn "+
      "about you, brushing against you like ethereal fingers.\n");
    say(QCTNAME(TP) + " vanishes into the Fire.\n");
    TP->move_living("M", ROOM + "vision_room", 1);

#ifdef LOG_GURU
    write_file(GUILDLOG +"guru_quest",
	LOG_FMT(NM(TP) +" entered the Flame"));
#endif

    return 1;
}

public int
touch(string str)
{
    notify_fail(CAP(query_verb()) + " what?");

    if (!strlen(str))
	return 0;

    if (!parse_command(str, ({}), "[the] [black] / [dark] 'flame' / 'fire'"))
	return 0;

    if (!state)
    {
	write("The flame is out.\n");
	return 1;
    }

    if (ENEMY(TP))
    {
	write("The flame burns you badly!\n");
	say(QCTNAME(TP) + " touches the dark flame, and then "+
	    "turns white with agony.\n");
	TP->hit_me(state * 3, MAGIC_DT, TO, -1);
	return 1;
    }

    say(QCTNAME(TP) + " passes " + HIS(TP) + " hand through the "+
	"dark flame.\n");

    if (IS_MEMBER(TP))
    {
    string heat;		
    switch(STATE)
    {
    case 9001..MAX_FLAME_STATE:	heat = "flushed with Jazur's Passion";  break;
    case 8001..9000: heat = "the Flame is nearly replete with offerings."; break; 
    case 7001..8000: heat = "the Passion of the Flame seems to be ebbing somewhat."; break;
    case 6001..7000: heat = "as though the Flame could use more fuel."; break;
	case 5001..6000: heat = "that the Flame should be fed soon.";    break;
	case 4001..5000: heat = "concerned that the Flame seems diminished.";  break;	
    case 3001..4000: heat = "a keen sense of Jazur's disappointment."; break;
    case 2601..3000: heat = "that the Flame has been neglected!";    break;	
    case 1501..2600: heat = "an alarming lack of warmth.";           break;
    case 501..1500:	 heat = "like the Flame is dying.";              break;
    case 1..500: heat = "that Jazur has withdrawn her Passion.";    break;
    default:	 heat = "bereft of Passion. The Flame is extinguished."; break;
    }
	write("Your hand passes into the dark flame.\nYou feel "+ heat +"\n");
    if (STATE > 6000)
    write("A warm and welcoming presence envelops you.\n");	
    if (STATE < 6000)
    write("An urgent need to tend to the Flame overwhelms you.\n");
	return 1;
    }

    if (FRIEND(TP))
    {
	write("The Flame feels warm and comforting to your touch.\n");
	return 1;
    }

    write("You pass your hand through the flame, as if it were not "+
	"there.\n");
    return 1;
}

public int
membership(object who)
{
    /* Don't show wizards. */
    if (who->query_wiz_level())
	return 0;

    return IS_MEMBER(who);
}

public int
who(string str)
{
    string faces;
    object *people;

    if (!strlen(str))
	return 0;

    if (!parse_command(str, ({}), "'in' / 'into' [the] 'fire' / 'flame'"))
    {
	write(CAP(query_verb())+" into what?\n");
	return 1;
    }

    if (!state)
    {
	write("The fire has gone out, the abyss is cold and empty.\n");
	say(QCTNAME(TP)+" stares down into the dark abyss.\n");
	return 1;
    }

    if (!IS_MEMBER(TP) && !IS_GMASTER(TP))
    {
	write("You see strange and indistinct shapes swirling in "+
	    "the flames.\n");
	say(QCTNAME(TP)+" looks into the fire.\n");
	return 1;
    }

    people = filter(users(), membership) - ({ TP });
    if (!sizeof(people))
    {
	write("You feel lonely and sad, there is nothing within "+
	    "the fire.\n");
	say(QCTNAME(TP)+" peers sadly into the flames.\n");
	return 1;
    }

    if (sizeof(people) == 1)
	faces = "face";
    else
	faces = "faces";

    TP->catch_tell("You peer within the flames, and can make out "+
	"the "+ faces +" of "+ COMPOSITE_LIVE(people) +".\nPerhaps, "+
	"by the grace of Jazur, you could scry/uscry one of them.\n");
    say(QCTNAME(TP)+" stares long and hard into the dark flame.\n");
    return 1;
}

public int
scry(string str)
{
    object ob, *live, *dead;

    if (!strlen(str))
	return 0;

    if (!state)
    {
	write("The fire has gone out, the abyss is cold and empty.\n");
	say(QCTNAME(TP)+" stares down into the dark abyss.\n");
	return 1;
    }

    mapping warriors = ([]);
    
    foreach (object shadow : object_clones(find_object(OCC_SHADOW)))
    {
        warriors[lower_case(shadow->query_real_name())] = 
            shadow->query_shadow_who();
    }

    ob = warriors[lower_case(str)];

    if (!objectp(ob) || ob->query_wiz_level())
    {
	notify_fail("You cannot do that.\n");
	return 0;
    }

    if (!objectp(ob = environment(ob)) ||
	    ob->query_prop(ROOM_M_NO_SCRY) ||
	    ob->query_prevent_snoop())
    {
	write("A dark room.\n");
	return 1;
    }

    write("\nThrough your link with Jazur, you are able to "+
      "catch a fleeting glimpse of one of your other selves.\n"); 

    TP->add_mana(-20);
    write(ob->long(0));

    dead = all_inventory(ob);
    live = filter(dead, living);
    dead = filter(dead - live, &not() @ &->query_no_show());

    if (sizeof(dead) && strlen(str = SILENT_COMPOSITE_DEAD(dead)))
	write(break_string((capitalize(str) + "."), 76) + "\n");

    if (sizeof(live) && strlen(str = SILENT_COMPOSITE_LIVE(live)))
	write(break_string((capitalize(str) + "."), 76) + "\n");

    return 1;
}

public int
start(string str)
{
    if (str != "here")
    {
	notify_fail("Start where, here perhaps?\n");
	return 0;
    }

    if (U_IS_PUNISHED(TP, U_PUNISHED_NOSTART) ||
	U_IS_PUNISHED(TP, U_PUNISHED_NOENTER))
    {
	write("You are forbidden from starting here.\n");
	return 1;
    }

    write("You will now enter the lands from this dark place.\n");
    say("The mist seems to caress "+QTNAME(TP)+".\n");

    TP->set_default_start_location(file_name(TO));
    return 1;
}

public varargs int
change_state(int increment, int silent, string str)
{
    int newstate;

    if (!state)
	return 0;

    newstate = state + increment;

    if (!silent)
    {
	string mess = "";

	if (newstate == state)
	{
	    mess = "The dark flame seems unaffected.";
	}
	else if (newstate < 1 && state > 0)
	{
	    mess = "The weakened flame flickers slightly and "+
		"finally vanishes in the abyss.";
	}
	else if (increment < 0)
	{
	    mess = "The dark flame seems to dim slightly.";
	}
	else if (newstate >= MAX_FLAME_STATE && state < MAX_FLAME_STATE)
	{
	    if (strlen(str))
		mess = "The flame "+ str +" before growing ";
	    else
		mess = "The flame grows ";

	    mess += "into a massive inferno, its tendrils licking "+
		"the ceiling and filling you with an unearthly power.";
	}
	else if (increment > 0)
	{
	    if (strlen(str))
	    {
		mess = "The flame "+ str +", casting long and "+
		    "strange shadows as it does that seem to "+
		    "have a life of their own.";
	    }
	    else
	    {
		mess = "The flame grows and burns brighter, "+
		    "casting long and strange shadows that seem "+
		    "to have a life of their own.";
	    }
	}

	if (strlen(mess))
	    tell_room(TO, mess + "\n");
    }

    state += increment;

    if (state > MAX_FLAME_STATE)
	state = MAX_FLAME_STATE;

    if (state < MIN_FLAME_STATE)
	state = MIN_FLAME_STATE;

    save_object(FIRE);
    return state;
}

public mixed
check_valid(object who, object obj)
{
    mixed msg;

    if (msg = obj->query_prop(OBJ_M_NO_DROP))
    {
	if (stringp(msg))
	    return msg;
	else
	    return "That object may not be dropped.\n";
    }

    if (!CAN_SEE(who, obj) || !CAN_SEE_IN_ROOM(who) || obj->query_no_show())
	return "You cannot see that.\n";

    if (obj->query_auto_load())
	return "You cannot do that.\n";

    if (obj->query_worn())
	return "You should remove it first.\n";

    if (obj->query_wielded() || obj->query_held())
	return "You should unwield or release it first.\n";

    return 0;
}

private void
burn_it_up(object what)
{
    if (what->query_prop(HEAP_I_IS))
	what->reduce_heap_size();
    else
	what->remove_object();
}

public int
burn(string str)
{
    int value;
    string msg;
    object what, *stuff;

    if (!strlen(str)) 
	return 0;

    if (!parse_command(str, ({ }),
	"[the] %s 'in' / 'into' / 'unto' / 'to' [the] 'flame' / 'abyss' / 'jazur'",
	msg))
    {
	return notify_fail(CAP(query_verb())+" what where?\n");
    }

    stuff = FIND_STR_IN_OBJECT(msg, TP);
    msg = "";

    string verb1 = " "+ query_verb() +" ";
    string verb2 = " "+ query_verb() +"s ";

    if (!sizeof(stuff))
	return notify_fail(CAP(query_verb()) +" what into the Flame?\n");

    if (sizeof(stuff) > 1)
	return notify_fail("You can only"+ verb1 +"in one thing at a time.\n");

    what = stuff[0];

    if (stringp(msg = check_valid(TP, what)))
	return notify_fail(msg);

    if (what->query_magic_res(MAGIC_I_RES_FIRE)  ||
	what->query_magic_res(MAGIC_I_RES_MAGIC) ||
	what->query_magic_res(MAGIC_I_RES_EARTH))
    {
	notify_fail("The abyss seems to resist "+LANG_THESHORT(what)+".\n");
	return 0;
    }

    TP->catch_tell("You"+ verb1 + LANG_THESHORT(what)+" unto the Flame.\n");
    say(QCTNAME(TP) + verb2 + LANG_ASHORT(what)+" unto the Flame.\n");

    if (!query_state())
    {
	/* If the flame is out, only something special can start it again. */
	if (!what->id(FIRESTARTER) && !present(FIRESTARTER, what))
	{
	    tell_room(TO, "The abyss remains lifeless and cold.\n");
	    return 1;
	}

	LOG_EVENT(NM(TP)+" re-started the flame.");

	tell_room(TO, "A deep rumbling can be heard from the depths of "+
	    "the abyss.\nA single tiny flame rises from the crack and "+
	    "starts the burn weakly.\n");
	write("You experience a tremendous feeling of accomplishment "+
	    "and overwhelming relief.\nYou feel more experienced in "+
	    "general.\n");

	limiter += LIMITER_INC;
	TP->add_exp_general(500);
	change_state(100, 1);
	return 1;
    }

    if (what->query_prop(OBJ_I_CONTAIN_WATER))
    {
	tell_room(TO, "A loud hissing sound arises from the flame.\n");
#ifdef VERBOSE
	LOG_EVENT(NM(TP)+" threw "+file_name(what) +
	    " into the flame, containing water.");
#endif
	change_state(-85 - random(150));
	burn_it_up(what);
	return 1;
    }

    if (IS_DRINK_OBJECT(what))
    {
	value = what->query_soft_amount() * what->num_heap();
	tell_room(TO, "The flame hisses angrily.\n");
	change_state(-(value * 10));
#ifdef VERBOSE
	LOG_EVENT(NM(TP)+" threw "+file_name(what) +
	  " into the fire (soft: "+value+")");
#endif
	burn_it_up(what);
	return 1;
    }

    if (what->query_prop(HEAP_I_IS))
	value = what->query_prop(HEAP_I_UNIT_VALUE);
    else
	value = what->query_prop(OBJ_I_VALUE);

#if 0
    if (what->id(FIRESTARTER) || present(FIRESTARTER, what))
    {
	if (!limiter)
	{
	    value = FSTARTER_VAL;
	    msg = "flashes with flurries of bright blue";

	    limiter += LIMITER_INC;

	    if (state < MAX_FLAME_STATE)
		TP->add_exp_general(100);
	}
	else
	{
	    value = 1;
	    msg = "briefly glows a midnight blue";
	}
    }
    else
#endif
    {
	int mult = value / NORMALIZE;

	/* Guard against 0 */
	mult = (mult ?: 1);
	mult *= DIV_INC;

	/* Determine % of value to use. */
	int pct = DIV_BASE - mult;

	/* Minimum % to use. */
	if (pct < DIV_MIN)
	    pct = DIV_MIN;

	/* Adjust effective value. */
	value = ((value * pct) / 100);

	/* Cap effective value. */
	if (value > MAX_VALUE)
	    value = MAX_VALUE;
	else if (value < 0)
	    value = 0;
    }

    if (!strlen(msg)) switch(value)
    {
    case 0 .. 15:
	msg = "consumes it quickly";
	break;
    case 16 .. 50:
	msg = "burns it up in a moment";
	break;
    case 51 .. 100:
	msg = "incinerates it quickly";
	break;
    case 101 .. 150:
	msg = "consumes it greedily";
	break;
    case 151 .. 200:
	msg = "immoliates it, glimmering joyfully";
	break;
    case 201 .. 300:
	msg = "wraps some tendrils of fire about it, "+
	    "slowly consuming it";
	break;
    default:
	msg = "slowly burns it away, seeming to savour it";
	break;
    }

#ifdef VERBOSE
    LOG_EVENT(NM(TP) +" burnt "+what->query_short() +
	" in the fire (value "+value+")");
#endif

    if (value > 0)
    {
	if (state < MAX_FLAME_STATE && random(2))
	    TP->adjust_union_virtue(US_GRACE, 5);
    }

    burn_it_up(what);
    change_state(value, 0, msg);
    return 1;
}

public int
pour(string str)
{
    int value;
    object what;

    if (!strlen(str))
	return 0;

    if (!query_state())
	return notify_fail("The abyss is already extinguished.\n");

    if (!parse_command(str, TP, 
	"[the] %o 'on' / 'onto' / 'into' [the] 'fire' / 'flame'", what))
    {
	return notify_fail(CAP(query_verb())+" what on the fire?\n");
    }

    string verb1 = " "+ query_verb() +" ";
    string verb2 = " "+ query_verb() +"s ";

    if (what->query_prop(OBJ_I_CONTAIN_WATER))
    {
	TP->catch_tell("You"+ verb1 +"the "+ what->short() +" into the "+
	    "flame, and hear a loud hissing sound.\n");
	say(QCTNAME(TP) + verb2 + LANG_ASHORT(what) +"into "+
	    "the flame, and you hear a loud hissing sound.\n");
#ifdef VERBOSE
	LOG_EVENT(NM(TP)+" poured "+ file_name(what) +
	  " into the flame, containing water.");
#endif
	change_state(-85 - random(150));
	what->remove_object();
	filter(users(), has_sphere)->catch_tell("Your sphere "+
	    "suddenly grows noticably colder.\n");
	return 1;
    }

    if (IS_DRINK_OBJECT(what))
    {
	value = what->query_soft_amount() * what->num_heap();
	TP->catch_tell("You"+ verb1 + LANG_THESHORT(what) +
	    " into the flame.\n");
	say(QCTNAME(TP) + verb2 + LANG_ASHORT(what) +
	    " into the flame.\n");
	tell_room(TO, "The flame hisses angrily.\n");
	change_state(-(value * 10));
#ifdef VERBOSE
	LOG_EVENT(NM(TP)+" threw "+file_name(what) +
	    " into the fire (soft: "+value+")");
#endif
	filter(users(), has_sphere)->catch_tell("Your sphere "+
	    "suddenly grows noticably colder.\n");
	what->remove_object();
	return 1;
    }

    return 0;
}

public void
cer_flicker(void)
{
    tell_room(TO, "The flame starts to flicker with sinuous motions.\n");
}

/*
 * Prepare a player for the Ceremony of the Flame
 * specific to Flame sphere, put here so Elders can
 * access it too.
 */
public int
cflame(string str)
{
    object *oblist, who, cer_obj;
    object tp = this_player();

    if (!strlen(str) || !FCEREMONY->valid_master(TP))
	return 0;

    if (!parse_command(str, ({}), "[on] %s", str))
	return notify_fail("cflame on whom?\n");

    oblist = FILTER_LIVE(FIND_STR_IN_OBJECT(str, ENV(TP)));

    if (!sizeof(oblist))
	return 0;

    if (sizeof(oblist) > 1)
    {
	write("You may use only one person at a time.\n");
	return 1;
    }

    who = oblist[0];

    if (!FCEREMONY->valid_target(who, TP))
	return 0;

    cer_obj = clone_object(FCEREMONY);
    cer_obj->set_ceremony_master(TP);
    cer_obj->set_ceremony_target(who);
    cer_obj->move(ENV(TP));

    tp->catch_msg("You cup the head of " + QTNAME(who) +" in your hands, "+
      "and in a voice that carries to all corners of the chamber, "+ 
      "you chant the ancient words: Alus kri sarudas Jazur!\n");
    who->catch_msg(QCTNAME(tp) + " cups your head in " + HIS(tp) +
      " hands, and in a voice that carries to all corners of the chamber, "+
      "chants the ancient words: Alus kri sarudas Jazur!\n");
    say(QCTNAME(tp) + " places " + HIS(tp) + " hands upon the head of "+
      QTNAME(who) +", and in a voice that carries to all corners "+
      "of the chamber, chants the ancient words: "+
      "Alus kri sarudas Jazur!\n", ({ who, tp }));

    return 1;
}

/*
 * Prepare a player for the Ceremony of Promotion
 * Specific to the Mentor sphere, put here so Elders can
 * access it too.
 */
public int
cname(string str)
{
    object *things, who, promot;

    if (!strlen(str) || !CPROMOTION->valid_master(TP))
	return 0;

    if (!parse_command(str, ({}), "[on] %s", str))
	return notify_fail("cname on whom?\n");

    things = FILTER_LIVE(FIND_STR_IN_OBJECT(str, ENV(TP)));

    if (!sizeof(things))
	return 0;

    if (sizeof(things) > 1)
    {
	notify_fail("You may use only one person at a time.\n");
	return 0;
    }    

    who = things[0];

    if (!CPROMOTION->valid_target(who, TP))
	return 0;

    promot = clone_object(CPROMOTION);
    promot->set_ceremony_master(TP);
    promot->set_ceremony_target(who);
    promot->move(ENV(TP));

    TP->catch_msg("You place your hands upon the head of " +
	QTNAME(who) +" and mumble the aged words: Alus kri akus "+
	"amestio!\n");
    who->catch_msg(QCTNAME(TP) + " places " + HIS(TP) + " hands "+
	"upon your head and mumbles the aged words: Alus kri akus "+
	"amestio!\n");
    say(QCTNAME(TP) + " places " + HIS(TP) + " hands upon the head of "+
	QTNAME(who) + " and mumbles the aged words: Alus kri akus "+
	"amestio!\n", ({ who, TP }));

    // summon guild NPC's to come to the ceremony
    LIST->query_present_members()->summon_for_union_ceremony(TO);
    tell_room(TO, "The flame starts to flicker with sinuous motions.\n");
    return 1;
}

/* Ceremonies available here */
public mixed
clist(string str)
{
    if (str == "flame")
    {
	if (!FCEREMONY->valid_master(TP))
	{
	    notify_fail("You are not presently permitted to perform this "+
	      "ceremony.\n");
	    return 0;
	}

	write("To initiate this ceremony use <cflame on person>\n"+
	  "You must be in the presence of the Flame to "+
	  "conduct this ceremony.  You must also have a "+
	  "Union member other than yourself present to "+
	  "offer to the Flame. This ceremony will enhance "+
	  "strength of the Flame, but it will not light it "+
	  "if it has been extinguished. Once you have initiated "+
	  "the ceremony, you can get further help using "+
	  "<help ceremony>.\n"); 
    }
    else if (str == "promotion")
    {
	if (!CPROMOTION->valid_master(TP))
	{
	    notify_fail("You are not presently permitted to perform this "+
	      "ceremony.\n");
	    return 0;
	}

	write("To initiate this ceremony use <cname on person>.\n"+
	  "You must be in the presence of the Flame to "+
	  "conduct this ceremony, which names a Novice to "+
	  "the sphere of Duty and promotes him or her to "+
	  "warrior status. Once you have initiated "+
	  "the ceremony, you can get further help using "+
	  "<help ceremony>.\n"); 
    }
    else
    {
	(CEREMONY + "cerobj")->list_ceremonies("ceremonies");
	return 1;
    }
    return 1;
}


public void
cure_plague(object carrier, int inc)
{
    if (!objectp(carrier))
	return;

    if (ENV(carrier) != TO) {
#ifdef DEBUG
	if (carrier->query_wiz_level()) {
	    write("!! PLAGUE: No longer present!\n");
	}
#endif
	return;
    }

    float wait = 2.0 + (3.0 * rnd());

    switch(inc)
    {
    case 0:
	{
	    int flag;
	    object ob;

	    while(ob = present("nasty_sickness", carrier)) 
	    {
		ob->cure_poison( ({"all"}), 999 );   
		// And just in case...
		ob->timeout();
		// Did we cure it?
		flag++;
	    }

	    if (flag)
	    {
		wait = (8.0 * rnd());
#ifdef DEBUG
		if (carrier->query_wiz_level()) {
		    write("\n>> PLAGUE: Removed "+ flag +" occurance(s)\n");
		}
#endif
		break;
	    }
	} /* Deliberate Fallthru */
    default:
	wait = 0.0;
	break;

    case 1:
	carrier->catch_tell("Suddenly you feel very hot, almost feverish.\n");
	break;

    case 2:
	carrier->catch_tell("Blue-black flames errupt from your skin. "+
	  "You are engulfed in fire!\n");

	tell_room(ENV(carrier), "Blue-black flames suddenly errupt from "+ 
	  QPNAME(carrier) +" skin! "+ HE(carrier) +" is engulfed in fire!"+
	  "\n", carrier, carrier);
	break;

    case 3:
	carrier->catch_tell("Seconds of agony feel like hours as the "+
	  "flames rage over and through you. Your mind rings with the "+
	  "sound of a familar voice: What Outland impurity have you "+
	  "brought into these Halls?\n");

	tell_room(ENV(carrier), "The flames continue to burn over "+ 
	  QTNAME(carrier) +", completely enveloping "+ HIM(carrier)+
	  ".\n", carrier, carrier);
	break;

    case 4:
	carrier->catch_tell("The pain intensifies and now you recognize "+
	  "it as both a blessing and a penance.\n");
	carrier->command("$ucry");
	break;

    case 5:
	wait = 0.0;
	carrier->catch_tell("Finally, the flames die, receding back into "+
	  "your skin. They leave you with a pleasant warmth and a sense "+
	  "that you have somehow been cleansed.\n");

	tell_room(ENV(carrier), "As suddenly as they appeared, the flames "+
	  "enveloping "+ QTNAME(carrier) +", die, appearing to be absorbed "+
	  "into "+ HIS(carrier)+" very skin.\n", carrier, carrier);
	break;
    }

    if (wait) {
	set_alarm(wait, 0.0, &cure_plague(carrier, ++inc));
#ifdef DEBUG
	if (carrier->query_wiz_level()) {
	    write(sprintf("** PLAGUE: Alarm delay >> %f\n", wait));
	}
#endif
    }
#ifdef DEBUG
    else if (carrier->query_wiz_level()) {
	write(sprintf("!! PLAGUE: Fini!\n"));
    }
#endif
}

public void
init(void)
{
    ::init();

    add_action( burn, "throw" );
    add_action( burn, "feed"  );
    add_action( burn, "burn"  );
    add_action( burn, "toss"  );	
    add_action( burn, "offer" );
    add_action( burn, "render");
	
	
    add_action( pour, "pour"  );

    add_action( touch, "touch" );
    add_action( touch, "feel"  );

    add_action( enter, "enter" );

    add_action( who, "stare" );
    add_action( who, "peer"  );
    add_action( who, "look"  );

    /* Members and Guildmaster only commands follow. */
    if (!IS_MEMBER(TP) && !IS_GMASTER(TP))
	return;

    cure_plague(TP, 0);

    add_action(   scry, "scry"   );
    add_action(   scry, "uscry"  );
    add_action(  start, "start"  );
    add_action(  cname, "cname"  );
    add_action( cflame, "cflame" );
    add_action(  clist, "clist"  );
}

/*
 * Function name: query_jazur_flame_present
 * Description:   Check to see if the jazur flame is present
 *                in the room. Used for objects that need to
 *                see if they are in a room with the Jazur
 *                flame.
 * Arguments:     none
 * Returns:       1 if Jazur Flame is present, 0 otherwise,
 *                string for a specific fail message.
 */
public mixed
query_jazur_flame_present(void)
{
    return (state > 0);
}
