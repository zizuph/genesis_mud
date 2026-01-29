#pragma strict_types
// In water:	(/d/Avenir/inherit/water.c)
// creator(s):	Glinda May -95 (port/water.c; port/uw.c)
// 		Cirion Jan -96 (inherit/underwater.c)
// last update:
// 		Lucius, Jan 2009: Re-written, mostly new code.
// 		Lucius, Jan 2009: Changed drift code to reduce alarms.
//
// purpose:	Handle common water-movement tasks.
//
// note:
// bug(s):
// to-do:
//
inherit "/std/room";

#include "/d/Avenir/include/defs.h"
#include "/d/Avenir/include/paths.h"

#include <composite.h>
#include <files.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <terrain.h>

/* Logging */
//#undef LOG_EXT		"/d/Avenir/log/light_uw"
//#undef LOG_NOT_EXT	"/d/Avenir/log/light_uw"
//#define LOG_DROWN	"/d/Avenir/log/drown.log"

/* Max Breathe */
#define M_B		15

/* Breathe tracking prop */
#define BREATHE		"__ave_underwater_timer"

/* Shortcuts to check prop */
#define UNDERWATER	(query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)
#define UNDERWATERX(x)	((x)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)

public int swim_test(void);
public int swim_exit(void);
public string swim_where(void);
public int swim_func(string str);
public int calc_fat(object who);

public static string swim_dir = "";
public static object *drift_arr = ({ });
public static mapping cmd_sub, move_opp;
public static int alarm_id, drift_id, no_drift, must_swim, swim;


/*
 * Set this to disallow dropped item removal.
 */
public nomask void
set_no_drift(int i)	{ no_drift = i; }

public nomask int
query_no_drift(void)	{ return no_drift; }


/*
 * Set this to force usage of "swim"/"dive" commands
 * to move around, no standard movement.
 */
public nomask void
set_must_swim(int i)	{ must_swim = i; }


public nomask int
query_must_swim(void)	{ return must_swim; }


/*
 * Calculate initial lung capacity.
 */
public nomask int
set_timer(object player)
{
    int timer = (player->query_skill(SS_SWIM) /  5) +
		(player->query_stat(SS_CON)   / 25);

    player->add_prop(BREATHE, min(max(timer, 0), M_B));
}


/*
 * Masq this to customize swim from description.
 */
public string
hook_swim_from(void)	{ return ""; }


/*
 * Makes movement swimmingly fine.
 */
public nomask string
swim_desc(void)
{
    if (!swim)
	return "";

    string str = hook_swim_from();

    if (strlen(str))
	return str;

    if (!strlen(str = move_opp[swim_dir]))
	return "";
    else
	str += ".";

    if (swim_dir == "down")
	return "diving from "+ str;
    else
	return "swimming from "+ str;
}


>>(void)
{
    setuid();
    seteuid(getuid());
    /*
     * This can be turned off in rooms that want it.
     */
     
    set_noshow_obvious(1);
    /*
     * Being able to hide underwater would be the exception
     * and not the norm.
     */
     
    add_prop(ROOM_I_HIDE, -1);
    /*
     * Remove this prop inside rooms that have doors or
     * other long description changing objects.
     */
    add_prop(ROOM_I_NO_EXTRA_DESC, 1);
    
    /*
     * Make movement more swimming.
     */
    add_prop(ROOM_S_EXIT_FROM_DESC, swim_desc);
    
    /*
     * Just 'cause.
     */
    add_item("water",
	"Water, water everywhere. It is very wet.\n");
    
    /*
     * Allow for transparent swimming.
     * Only works in combination with the add_action's.
     */
    add_exit(swim_where, "swim", swim_exit, calc_fat, 1);
    add_exit(swim_where, "dive", swim_exit, calc_fat, 1);

    move_opp = SECURITY->query_move_opposites();
    
    cmd_sub  = ([
	 "n" : "north",
	 "s" : "south",
	 "w" : "west",
	 "e" : "east",
	 "u" : "up",
	 "d" : "down",
	"sw" : "southwest",
	"se" : "southeast",
	"nw" : "northwest",
	"ne" : "northeast",
    ]);
}


/*
 * Standard settings for an underwater room.
 *
 * public void
 * create_room(void)
 * {
 *    underwater_room();
 *    <....>
 * }
 *
 * |==[ OR ]==|
 *
 * public void
 * underwater_room(void)
 * {
 *    ::underwater_room();
 *    <....>
 * }
 */
public void
underwater_room(void)
{
    set_short("underwater");
    set_long("You are underwater.\n");
    set_terrain(TERRAIN_UNDERWATER);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT,  0);
    add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
    add_prop(ROOM_S_DARK_LONG,
	"The dark water around you covers your sight.\n");
    
    add_prop(ROOM_S_DARK_MSG,
	"The water is too dark to");
}


/*
 * Standard settings for an in/above water room.
 * (See usage example above.)
 */
public void
water_room(void)
{
    set_short("water");
    set_long("Surrounded by water.\n");
    set_terrain(TERRAIN_ONWATER);
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}


/*
 * Dropped items get moved to a temp room.
 * Some rooms are protected from drifting.
 */
private nomask void
drift_away(void)
{
    drift_id   = 0;
    drift_arr -= accept_here;

    if (!sizeof(drift_arr))
	return;

    /* Done this way so as to avoid privilige errors. */
    tell_room(TO, CAP(COMPOSITE_DEAD(drift_arr)) +
	" drifts away with the currents.\n");

    drift_arr->move((COM + "void")->get_this_object());
    drift_arr = ({ });
}


/*
 * Extinguish all /std/torch based items.
 * This includes most lamps, we will recurse through
 * open packs that are emitting light as well.
 *
 * We don't deliberately make the items unusable, so they
 * can re-light torches and such after leaving the water.
 *
 * Further objects can be added if made aware of them.
 */
public nomask void
extinguish_light(object what = this_player())
{
    if (!objectp(what))
	return;

    object *packs = ({ }), *torches = ({ });

    foreach(object obj : all_inventory(what))
    {
	if (!obj->query_prop(OBJ_I_LIGHT))
	    continue;

	if (IS_TORCH_OBJECT(obj))
	{
	    torches += ({ obj });
#ifdef LOG_EXT
	    write_file(LOG_EXT, ctime(time()) +": "+
		"Torch-based object marked for extinguishing --"+
		"\n >>> "+ file_name(obj) +"\n");
#endif
	}
	else if (IS_CONTAINER_OBJECT(obj))
	{
	    if (obj->query_prop(CONT_I_CLOSED))
		continue;

	    packs += ({ obj });
	}
	else
	{
#ifdef LOG_NOT_EXT
	    write_file(LOG_NOT_EXT, ctime(time()) +": "+
		"Light emitting object found, not extinguished --"+
		"\n >>> "+ file_name(obj) +"\n");
#endif
	}
    }

    int size = sizeof(torches);
    if (size)
    {
	string mess = " " +
	    (size > 1 ? "go" : "goes") +" out with a loud hiss as "+
	    (size > 1 ? "they come " : "it comes ") +
	    "into contact with water.\n";

	write(CAP(COMPOSITE_DEAD(torches)) + mess);
	say(CAP(QCOMPDEAD) + mess);
	/*
	 * This will work for all properly coded objects
	 * which are based on /std/torch.c
	 */
	torches->extinguish_me();
    }

    if (sizeof(packs))
    {
	write("Water begins seeping into "+
	    COMPOSITE_DEAD(packs) +"....\n");

	foreach(object item : packs)
	    extinguish_light(item);
    }
    /*
     * Make sure all light levels are sync'd up.
     */
    update_light(1);
}


/*
 * This prevents hiding torches inside a pack and then opening
 * it after entering the water, this detects the change in
 * light levels and attempts to extinguish known items.
 */
public void
update_internal(int l, int w, int v)
{
    ::update_internal(l, w, v);

    if ((l > 0) && UNDERWATER)
    {
	object source = calling_object(0);
	/*
	 * Some magic light-source cast into the room?
	 */
	if (source == this_object())
	    return;

	/* When a light-emitting container is opened, try
	 * to extinguish items. Must include delay as the
	 * object isn't actually opened yet. */
	set_alarm(0.0, 0.0, &extinguish_light(source));
    }
}


public void
death_scene(object player)
{
    tell_object(player,
	"A sudden peace fills you.\nYou draw your final breath, and " +
	"the feeling of the water\nfilling your lungs is wonderful.\n" +
	"Pictures of fields filled with flowers flow through your mind.\n");
}


public void
feel_worse(object player)
{
    string str;

    switch(random(4))
    {
    case 0:
	str = "You are struggling! Your lungs fill with water!\n";
	break;
    case 1:
	str = "Panic makes you gasp for air. You inhale water instead!\n";
	break;
    case 2:
	str = "Your eyes feel as if they are poping out of your head. " +
	    "The pressure is killing you!\n";
	break;
    case 3:
	str = "You are dying! Get out!!!\n";
	break;
    }
    tell_object(player, str);
}


public void
give_msg(object player, int num)
{
    string str;

    switch(num)
    {
    case 15:
	str = "You are enjoying the easy feeling of diving.\n";
	break;
    case 14:
	str = "You start wondering how long you can keep diving like this.\n";
	break;
    case 13:
	str = "You feel a weak pressure from inside.\nYou let out some air.\n";
	break;
    case 12:
	str = "Some air bubbles flow out your mouth, floating upwards.\n" +
	    "You can't help wishing you were going the same way.\n";
	break;
    case 11:
	str = "You start longing for solid earth under your feet.\n";
	break;
    case 10:
	str = "If only you could fill your lungs with air again!\n";
	break;
    case 9:
	str = "You are having problems concentrating on what you are doing.\n" +
	    "All you can think about is air.\n";
	break;
    case 8:
	str = "A sudden feeling of weakness overwhelms you.\n";
	break;
    case 7:
	str = "Your vision fades for a second.\n";
	break;
    case 6:
	str = "Your arms are starting to feel numb.\n";
	break;
    case 5:
	str = "You feel extremely claustrophobic.\n";
	break;
    case 4:
	str = "Panic strikes you with a cold grasp around your heart.\n";
	break;
    case 3:
	str = "OUT!! You have to get out!!\n";
	break;
    case 2:
	str = "You briefly lose your senses.\n";
	break;
    case 1:
	str = "A scream builds up within you and forces itself out your " +
	    "lips.\nYou swallow water.\n";
	break;
    }

    if (strlen(str))
	tell_object(player, str);
}


/*
 * Just a basic breathe test, as long as the MAGIC_I_BREATH_WATER
 * prop is present, player(s) can breathe indefinately. Else, there
 * is a simple timer formulae (set_timer) that is tracked in another
 * prop. It runs from 15 -> 0. Players get status messages, holding
 * still lasts longer than active swimming.
 */
private nomask int
check_things(void)
{
    foreach(object player : filter(all_inventory(), query_interactive))
    {
	/* Wizards and ghosts are soul-less and don't need air. */
	if (player->query_wiz_level() || player->query_ghost())
	    continue;

	/* Magic breathe turns water into air. */
	int magic = player->query_prop(MAGIC_I_BREATH_WATER);

	if (magic)
	{
	    player->add_prop(BREATHE, M_B);
	    player->catch_tell("You breathe the water easily.\n");
	    continue;
	}

	/* Check lung capacity. */
	int timer = player->query_prop(BREATHE);

	if (--timer < 0)
	    timer = 0;

	player->add_prop(BREATHE, timer);

	/* Oxygen levels? */
	if (!timer && !magic)
	{
	    player->heal_hp(-(player->query_stat(SS_CON) * 6));
	    if (!player->query_hp())
	    {
		/* Dead! */
		death_scene(player);
		player->do_die(TO);
#ifdef LOG_DROWN
		write_file(LOG_DROWN, player->query_name() +
		    " drowned, " + ctime(time()) + ".\n");
#endif
		continue;
	    }

	    /* Dying! */
	    feel_worse(player);
	    continue;
	}

	/* Running out of breathe. */
	give_msg(player, min(M_B, timer));
    }
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!no_drift && !living(ob) && objectp(from))
    {
	if (!drift_id)
	    drift_id = set_alarm(1.5, 0.0, drift_away);
	drift_arr += ({ ob });
    }

    /* Only underwater players at this point. */
    if (!UNDERWATER || !query_interactive(ob))
	return;

    /* Only start alarm for non-wizards. */
    if (!alarm_id && !ob->query_wiz_level())
	alarm_id = set_alarm(2.0, 10.0, check_things);

    if (!UNDERWATERX(from))
    {
	/* We just dove. */
	extinguish_light(ob);
	if (!ob->query_prop_setting(BREATHE))
	    set_timer(ob);
    }
}


public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (drift_id)
	drift_arr -= ({ ob });

    if (alarm_id)
    {
        /* Stop alarm if empty of players. */
        if (!sizeof(filter(all_inventory(), query_interactive)))
        {
            remove_alarm(alarm_id);
            alarm_id = 0;
        }
    }

    if (UNDERWATER && !UNDERWATERX(to))
    {
        /* We are surfacing. */
        ob->remove_prop(BREATHE);
        ob->catch_tell("You break the water's surface, "+
            "returning to the air.\n");
    }
}


/*
 * Use up oxygen trying to speak.
 */
public nomask int
no_talk(string str)
{
    if (!strlen(str))
	return 0;

    /* Don't check, negative values will be caught later. */
    TP->add_prop(BREATHE, TP->query_prop(BREATHE) - 1);

    write("Some bubbles flow out of your mouth.\n");
    say(QCTNAME(TP) + " opens " + TP->query_possessive() +
	" mouth letting out some bubbles.\n");

    return !TP->query_wiz_level();
}


/*
 * Filter what you are allowed to do in/under water.
 */
public int
catch_all(string str)
{
    switch(query_verb())
    {
#if 0
    case "dive":
    case "swim":
	return swim_func(str);
#endif

    case "light":
	write("You cannot light anything under water!\n");
	break;

#if 0
     case "eat":
     case "drink":
 	/* Only allow eating / drinking if magic breathe'd */
 	if (TP->query_prop(MAGIC_I_BREATH_WATER))
 	    return 0;

     	write("Being surrounded by water precludes that idea.\n");
 	break;
#endif

  /* Regular talk-type commands. */
    case "say":
    case "asay":
    case "ask":
    case "laugh":
    case "rsay":
    case "scream":
    case "shout":
    case "whisper":
    case "whistle":
  /* Guild talk-type commands. */
    case "aasay":
    case "grsay":
    case "ks":
    case "ksay":
    case "ms":
    case "mhiss":
    case "rasp":
    case "us":
    case "usay":
    case "usto":
	return no_talk(str);

    case "ponder":
    case "wonder":
    case "think":
	write("The vastness of the water is too pressing for that.\n");
	break;

    default:
	return 0;
    }
    return 1;
}


public void
init(void)
{
    ::init();
    /*
     * Must be first or above water swimming breaks.
     */
    add_action( swim_func, "swim" );
    add_action( swim_func, "dive" );

    if (!UNDERWATER)
	return;

    add_action( catch_all, "",   1 );
    add_action(   no_talk, "'",  2 );
    add_action(   no_talk, "a'", 2 );
}


/*
 * Standardized fatigue calculator for swimming pleasure.
 */
public nomask varargs int
calc_fat(object who = this_player())
{
    int skills = 10 * (who->query_skill(SS_SWIM) +
		       who->query_skill(SS_ACROBAT));

    int stats  = (6 * who->query_stat(SS_CON)) +
		 (3 * who->query_stat(SS_STR)) +
		 (2 * who->query_stat(SS_DEX));
		 
    int result = who->query_prop(OBJ_I_WEIGHT);
        result /= (skills + stats);
	result /= 7;

    return result = min(max(result, 3), 20);
#if 0
    if (who->query_wiz_level())
	who->catch_tell(">> Calculated fatigue cost: "+ result +"\n");

    return result;
#endif
}


/*
 * Mask add_exit() to default use of the calc_fat() function.
 * We prefer the global non_obvious flag to save memory/performance.
 */
public nomask varargs int
add_exit(string place, string cmd, mixed efunc, mixed fat, mixed non_obv)
{
    if (intp(fat) && (fat < 1))
	fat = calc_fat;

    if (intp(efunc) && !efunc)
	efunc = swim_test;

    return ::add_exit(place, cmd, efunc, fat, non_obv);
}


/*
 * Masq this for unified custom movement failures.
 */
public string
hook_no_swim(string str)
{
    return "";
}


/*
 * More thematic movement failures.
 */
public nomask int
unq_no_move(string str = query_verb())
{
    string hook = hook_no_swim(str);

    if (!strlen(hook))
	hook = "You are unable to swim "+ str +".\n";

    notify_fail(hook);
    return 0;
}


/*
 * Return differences from exit vs. command.
 */
public nomask int
swim_no_move(string str)
{
    string hook = hook_no_swim(str);

    if (!strlen(hook))
	hook = "You are unable to "+ query_verb() +" "+ str +".\n";

    write(hook);
    return 1;
}


/*
 * Convert swim/dive command into movement.
 */
public nomask int
swim_func(string str)
{
    string verb = query_verb();

    if (!strlen(str))
    {
        if (verb != "dive")
        {
            switch(random(2))
            {
            case 0:
            write("You swim around in circles.\n");
            say(QCTNAME(TP) +" swims around in circles.\n");
            break;
            case 1:
            write("You float about aimlesslely.\n");
            say(QCTNAME(TP) +" floats about aimlesslely.\n");
            break;
            }
            return 1;
        }
        str = "down";
    }
    else if (cmd_sub[str])
	str = cmd_sub[str];

    if ((verb == "dive") && (str != "down"))
    {
        write("Diving is limited to a downards direction.\n");
        return 1;
    }

    /* Get valid exits. */
    string *exits = query_exit_cmds() - ({ "swim", "dive" });

    /* See if the exit exists. */
    if (!IN_ARRAY(str, exits))
	return swim_no_move(str);

    swim = 1;
    swim_dir = str;

    /* Try to move. */
    return unq_move(str);
}


/*
 * Return the real exit path from the psuedo swim exit.
 */
public nomask string
swim_where(void)
{
    int idx = member_array(swim_dir, room_exits);

    /* This should never occur... */
    if (idx < 1)
	return "/road/to/nowhere";

    return room_exits[idx - 1];
}


/*
 * Masq this to print extra movement / swim messages.
 */
public int
swim_exit(void)
{
    return 0;
}


/*
 * Force an exit to be a non-swim exit with this.
 */
public nomask int
no_swim(void)
{
    swim = 0;
    swim_dir = "";

    return 0;
}


/*
 * Block non swim/dive exits if must_swim is enabled.
 */
public nomask int
swim_test(void)
{
    string verb = query_verb();

    if (!strlen(swim_dir))
    {
	if (cmd_sub[verb])
	    swim_dir = cmd_sub[verb];
	else
	    swim_dir = verb;
    }

    swim = 1;

    if (!must_swim)
	return swim_exit();

    if (swim_dir == "down")
	verb = "diving";
    else
	verb = "swimming";

    write("You should try "+ verb +" there instead.\n");

    swim = 0;
    return 1;
}


/*
 * Intercept to return a proper exit_cmd when
 * using pseudo-swimming.
 */
public nomask int
exit_move(string exit_cmd, object dest_room)
{
    if (swim)
    {
	if (swim_dir == "down")
	    exit_cmd = "diving "+ swim_dir;
	else
	    exit_cmd = "swimming "+ swim_dir;
    }

    int move =  ::exit_move(exit_cmd, dest_room);

    swim_dir = "";
    swim = 0;

    return move;
}
