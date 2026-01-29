#pragma strict_types
#pragma no_inherit
/*
 * - /d/Avenir/union/obj/sway.c
 *
 * The Sway
 * Cirion 032506
 *
 * Bug(s): cb_update_speed() in the combat object does not
 *         restart the heart_beat() alarm, so increasing speed
 *         while in combat is futile (stop_heart() & related
 *         functions are nomask, so cannot be accessed). And
 *         why else would you even increase speed?
 * Bug fixed
 *
 * Lucius, Jul 2011: Added <> to vision style format.
 * Lucius, Apr 2008: Quickness prior to sway was being doubled,
 *                   noticed by AoB and corrected.
 *
 * Lilith, Jan 2006: removed Con bonus. It was deemed not worth
 *         the 1% tax paid and removed upon request of the Elders.
 * 
 * Lilith, Jan 2006: upped darksight bonus so that it begins in the 
 *         first phase and increases to 4 levels instead of 3, also
 *         per req of Elders. Tax was increased from .50% to 1.0% 
 *
 * Lucius, Dec  2004: fixed bad interaction with other items setting
 *         extra skill/stat bonuses.
 *
 * Lilith, May  2004: updated sway messages, they've been the
 *         same for many years.
 *
 * Lilith, Sept 2003  end_sway() removed properties and skills 
 *         w/o a check to see if the amt removed = amt added. 
 *         This was resulting in removal of props and skills 
 *         modified by other objects such as spells.
 *         
 * Cirion, June 1997: Added the cabability of generating
 *         visions when entering the sway. The visions work
 *         like this:
 *         When a player first enters the sway, the object
 *         checks to see if the file SWAY_DIR + <player_name>
 *         or SWAY_DIR + <player's sphere> exists. If so,
 *         it parses that file (which needs to be in a certain
 *         format, see the README in the SWAY_DIR for more
 *         info). If that file exists, the player receives
 *         the vision and and the file is moved to an old
 *         file, coded by <old file> + "_<who>_<time>"
 *         The player must be alone to experience a vision.
 *
 * Cirion, December 1997: Put in checks for the environment's
 *         function union_hook_sway_msg() - if it exists, then players
 *         will get that message instead of the defaults. This is
 *         mainly for the Temple of Jazur, but can be used for other
 *         things as well.
 */
inherit "/std/object";
inherit "/d/Avenir/inherit/copy_file";

#include "../lib/misc.h"
#include "../defs.h"

#define ERROR(x) write_file(SWAY_DIR +"errors", ctime(time()) +": "+ x +"\n")

/* Function prototypes */
public void move_me_to(object who);
static void phase_one();
static void phase_two();
static void phase_three();
static void phase_four();
static void phase_five();
static void end_sway();
static void remove_me();
string check_vision_file(object who);
int parse_vision_file(string file);
void move_vision_file(object who, string file);
void start_vision(object who);
void vision(object who);
void end_vision(object who);
int do_nothing(string str);

static object me;
static int cant_see, skill, dex, aware;
static int new_dex, new_quick, new_aware, dark_increment;

/* The vision events, should they exist */
string *events, vis_type;
int event_counter, in_vision;

public void
create_object()
{
    if (!IS_CLONE)
	return;

    setuid();
    seteuid(getuid());

    set_name(SWAY_ID);
    add_name("ussway");
    set_long("Can you really see it?\n");

    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_M_NO_DROP, "Drop what?\n");
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY, 1);

    set_no_show();
}

public int
nosee(string str)
{
    if (!cant_see)
	return 0;

    write("You cannot see with your eyes shut.\n");
    return 1;
}

/*
 * These actions are for use when the player is closing
 * his eyes so he can go into the Sway.
 */
public void
init(void)
{
    ::init();

    add_action(nosee, "look");
    add_action(nosee, "examine");
    add_action(nosee, "exa");
    add_action(nosee, "appraise");

    if (in_vision)
	add_action(do_nothing, "", 1);
}

/*
 * This function called from the soul to enter the sway.
 */
public void
move_me_to(object who)
{
    if (present(SWAY_ID, who))
    {
	set_alarm(0.0, 0.0, remove_object);
	return;
    }

    move(who, 1);
}

/*
 * Automatically start up when we enter someone's inventory.
 */
public void
enter_env(object to, object from)
{
    object   where;
    mixed    delay;
    string   special_msg, special_msg_other;

    ::enter_env(to, from);

    if(!living(to))
    {
	set_alarm(0.0, 0.0, remove_me);
	return;
    }

    me = to;
    where = environment(me);

    special_msg = ENV(me)->union_hook_sway_msg(0, me);
    if (strlen(special_msg))
	ME(special_msg);
    else
	ME("You close your eyes and focus all your energies "+
	    "on entering the Sway.");

    special_msg_other = ENV(me)->union_hook_sway_msg_other(0, me);
    if (strlen(special_msg_other))
	tell_room(where, special_msg_other + "\n", me);
    else
	tell_room(where, QCTNAME(me)+" closes "+ me->query_possessive() +
	    " eyes and seems to be concentrating deeply.\n", me);

    /* Stop me from fighting while I concentrate */
    me->add_prop(LIVE_I_CONCENTRATE, 1);

    skill = me->query_skill(SS_SWAY);
#ifdef SKILLS_AFFECTED_BY_FLAME
    if (environment()->query_wiz_level())
    {
	environment()->catch_tell("SKILLS_AFFECTED_BY_FLAME:\n"+
	    "\tSway Skill:  "+ skill +"\n\tFlame Diff:  -"+
	    FLAME_DIFF(skill, PSTATE) +"\n");
    }

    skill -= FLAME_DIFF(skill, PSTATE);
#endif
    if(skill < 1)   skill = 1;

    dex   = me->query_base_stat(SS_DEX);
    aware = me->query_base_skill(SS_AWARENESS);

    cant_see = 1;
    ALTER_PROP(me, LIVE_I_BLIND, 5);

    delay = 11.0 - (itof(skill) / 10.0);
    set_alarm(delay, 0.0, phase_one);
}

/*
 * Filter for seen things & people.
 */
int
my_seen(object ob)
{
    if (CAN_SEE(me, ob) && CAN_SEE_IN_ROOM(me) &&
	me->query_prop(LIVE_I_SEE_INVIS) >= 0)
	return 1;
    else
	return 0;
}

/*
 * Everything in the room we can see. This is used when awareness,
 * darksight, see_invis are changes, and will thereby give
 * messages if we can see something we previousley couldn't.
 */
void
all_seen(object *old_seen)
{
    object *ob_list, *obs;
    string  item;

    ob_list = filter(all_inventory(ENV(me)) - ({ me }), my_seen);

    if (sizeof(old_seen))
	ob_list -= old_seen;

    ob_list -= ({ 0 });

    if(!sizeof(ob_list))
	return;

    item = COMPOSITE_LIVE(obs = FILTER_LIVE(ob_list));
    if (sizeof(obs))
	ME("From the mist and shadows, "
	  + item + " seem" + (sizeof(obs) > 1 ? "" : "s")
	  + " to emerge.");

    item = COMPOSITE_DEAD(obs = FILTER_DEAD(ob_list));
    if (sizeof(obs))
	ME("Rising from obscurity, "
	  + item + " appear" + (sizeof(obs) > 1 ? "" : "s")
	  + " before you.");
}

/*
 * Phase one of the sway:
 *  set LIVE_I_SEE_DARK to 1
 *  set quickness to 25% of the sway skill
 *  increase dex by dex * (sway / 10) %
 *    eg. dex of 100, sway of 100 -> dex of 110, quick 25
 *        dex of 55, sway of 40 -> dex of 57, quick 10
 * If sway > random(10) + 10, player can move on to phase_two
 */
static void
phase_one()
{
    object *objs;
    string vision, special_msg, special_msg_other;

    /* The player can see again */
    cant_see = 0;
    ALTER_PROP(me, LIVE_I_BLIND, -5);
    me->remove_prop(LIVE_I_CONCENTRATE);

    /* Here we check to see if the player should
     * be affected by a vision */
    if (!sizeof(FILTER_OTHER_LIVE(all_inventory(ENV(me)))) &&
	!objectp(me->query_attack()) &&
	(vision = check_vision_file(me)) && parse_vision_file(vision))
    {
	move_vision_file(me, vision);
	start_vision(me); 
	return;
    }

    objs = filter(all_inventory(ENV(me)) - ({ me }), my_seen);

    if (strlen(special_msg = ENV(me)->union_hook_sway_msg(1, me)))
	ME(special_msg);
    else if(CAN_SEE_IN_ROOM(me))
	ME("You snap your eyes open, and "
	  +"the area seems to fall into sharper focus.");
    else
	ME("You snap your eyes open, and the darkness around seems "
	  +"to breathe with life.");

    if (strlen(special_msg_other = ENV(me)->union_hook_sway_msg_other(1, me)))
	tell_room(ENV(me), special_msg_other + "\n", me);
    else
	tell_room(environment(me),
	    QCTNAME(me)+" snaps "+(me->query_possessive()) +
	    " eyes open and begins to sway with a strange, flowing "+
	    "motion.\n", me);

    new_quick = skill / 4;
    new_dex   = skill / 10;

    ALTER_PROP(me, LIVE_I_QUICKNESS, new_quick);
    ALTER_STAT(me, SS_DEX, new_dex);

    dark_increment++;
    ALTER_PROP(me, LIVE_I_SEE_DARK, 1);

    me->query_combat_object()->cb_update_speed();

    all_seen(objs);

    if (skill > (random(10) + 10))
	set_alarm(10.0, 0.0, phase_two);
    else
	set_alarm(10.0, 0.0, end_sway);
}

/*
 * Phase two of the sway:
 *  set LIVE_I_SEE_DARK to 2
 *  set quickness to 45% of the sway skill
 *  increase dex by dex * (sway / 5) %
 *  increase awareness by awareness * (sway / 10) %
 *  eg. dex of 100, awareness of 80, sway of 100->
 *        quick 45, dex 120, awareness 88
 *      dex of 55, awareness of 45, sway of 40->
 *        quick 18, dex 59, aware 47
 * If sway > random(20) + 20, player can move on to phase_three
 */
static void
phase_two()
{
    object *objs = filter(all_inventory(ENV(me)) - ({ me }), my_seen);
    string special_msg, special_msg_other;

    /* Only these two were set in Phase One. */
    ALTER_PROP(me, LIVE_I_QUICKNESS, -new_quick);
    ALTER_STAT(me, SS_DEX, -new_dex);

    new_dex   = skill / 5;
    new_aware = skill / 10;
    new_quick = skill * 9 / 20;

    if (strlen(special_msg = ENV(me)->union_hook_sway_msg(2, me)))
	ME(special_msg);
    else if (CAN_SEE_IN_ROOM(me))
	ME("You feel the blood in your veins "
	  +"start to rush frantically, flooding you with "
	  +"a power that makes your muscles tingle. "
	  +"Everything seems to move very slowly.");
    else
	ME("You feel the blood in your veins "
	  +"start to rush frantically, flooding you with "
	  +"a power that makes your muscles tingle. The "
	  +"darkness around you seems to pulsate like a heart.");

    if (strlen(special_msg_other = ENV(me)->union_hook_sway_msg_other(2, me)))
	tell_room(ENV(me), special_msg_other + "\n", me);

    ALTER_PROP(me, LIVE_I_QUICKNESS, new_quick);
    ALTER_SKILL(me, SS_AWARENESS, new_aware);
    ALTER_STAT(me, SS_DEX, new_dex);

    dark_increment++;
    ALTER_PROP(me, LIVE_I_SEE_DARK, 1);

    me->query_combat_object()->cb_update_speed();

    all_seen(objs);

    if(skill > (random(20) + 20))
	set_alarm(15.0, 0.0, phase_three);
    else
	set_alarm(15.0, 0.0, end_sway);
}

/*
 * Phase three of the sway:
 *  set quickness to 85% of the sway skill
 *  increase dex by dex * (sway / 2) %
 *  increase awareness by awareness * (sway / 5) %
 *  eg. dex of 100, awareness of 80, sway of 100->
 *         quick 85, dex 150, aware 96
 *      dex of 55, awareness of 45, sway of 40->
 *        quick 34, dex 66, aware of 49
 * If sway > random(40) + 50, player can move on to phase_four
 */
static void
phase_three()
{
    int    o_can_see = CAN_SEE_IN_ROOM(me);
    object *objs = filter(all_inventory(ENV(me)) - ({ me }), my_seen);
    string special_msg, special_msg_other;

    ALTER_PROP(me, LIVE_I_QUICKNESS, -new_quick);
    ALTER_SKILL(me, SS_AWARENESS, -new_aware);
    ALTER_STAT(me, SS_DEX, -new_dex);

    new_dex   = skill / 2;
    new_aware = skill / 5;
    new_quick = skill * 11 / 20;

    ALTER_PROP(me, LIVE_I_QUICKNESS, new_quick);
    ALTER_SKILL(me, SS_AWARENESS, new_aware);
    ALTER_STAT(me, SS_DEX, new_dex);

    me->query_combat_object()->cb_update_speed();

    if (strlen(special_msg = ENV(me)->union_hook_sway_msg(3, me)))
	ME(special_msg);
    else if (!o_can_see && CAN_SEE_IN_ROOM(me))
	ME("Your feel dizzy, almost drunken. The "
	  +"darkness in the area seems to roll back to "
	  +"a haze, and everything seems to glow luminous and "
	  +"bright.");
    else if (!CAN_SEE_IN_ROOM(me))
	ME("You feel dizzy, almost drunken. "
	  +"Shadows seem to dance before your "
	  +"eyes, and your skin tingles with an "
	  +"icy sensation.");
    else
	ME("You feel dizzy, almost drunken on the rush of power "
	  +"pulsing through you. In your heightened state, everything "
	  +"around you seems to be moving excruciatingly slowly, "
	  +"as if your relationship to time has changed.");

    if (strlen(special_msg_other = ENV(me)->union_hook_sway_msg_other(3, me)))
	tell_room(ENV(me), special_msg_other + "\n", me);

    all_seen(objs);

    if (skill > (random(30) + 50))
	set_alarm(20.0, 0.0, phase_four);
    else
	set_alarm(20.0, 0.0, end_sway);
}

/*
 * Phase four of the sway:
 *  set quickness to 95% of the sway skill
 *  set LIVE_I_SEE_DARK to 3
 * Other stats and skills remain the same.
 * If sway > random(10) + 93, player can move on to phase_five
 */
static void
phase_four()
{
    int   o_can_see = CAN_SEE_IN_ROOM(me);
    object *objs = filter(all_inventory(ENV(me)) - ({ me }), my_seen);
    string special_msg, special_msg_other;

    ALTER_PROP(me, LIVE_I_QUICKNESS, -new_quick);
    new_quick = skill * 19 / 20;  
    ALTER_PROP(me, LIVE_I_QUICKNESS, new_quick);

    dark_increment++;
    ALTER_PROP(me, LIVE_I_SEE_DARK, 1);

    me->query_combat_object()->cb_update_speed();

    if (strlen(special_msg = ENV(me)->union_hook_sway_msg(4, me)))
	ME(special_msg);
    else if (!o_can_see && CAN_SEE_IN_ROOM(me))
	ME("The blood in your veins starts to "
	  +"pound in a furious crescendo, carrying to "
	  +"your ears the echo "
	  +"of beloved voices. The darkness "
	  +"seems to fade back into a dull grey fog.");
    else
	ME("The blood in your veins pounds in a furious "
	  +"crescendo, carrying to your ears the echo "
	  +"of beloved voices. Colors seem "
	  +"to be emerging and brightening "
	  +"as the Sway lends deeper sight.");

    if (strlen(special_msg_other = ENV(me)->union_hook_sway_msg_other(4, me)))
	tell_room(ENV(me), special_msg_other + "\n", me);

    all_seen(objs);

    if (skill > (random(10) + 85))
	set_alarm(30.0, 0.0, phase_five);
    else
	set_alarm(30.0, 0.0, end_sway);
}

/*
 * Phase five of the sway:
 *  set LIVE_I_SEE_DARK to 4
 *  set LIVE_I_SEE_INVIS to 1
 * Other stats and skills remain the same.
 * Last phase, end of sway is next
 */
static void
phase_five()
{
    int     i, o_can_see = CAN_SEE_IN_ROOM(me);
    object *objs = filter(all_inventory(ENV(me)) - ({ me }), my_seen);
    string special_msg, special_msg_other;

    dark_increment++;
    ALTER_PROP(me, LIVE_I_SEE_DARK, 1);
    ALTER_PROP(me, LIVE_I_SEE_INVIS, 1);

    if (strlen(special_msg = ENV(me)->union_hook_sway_msg(5, me)))
	ME(special_msg);
    else if (!o_can_see && CAN_SEE_IN_ROOM(me))
	ME("Your heart pushes liquid fire through your veins, each "
	  +"beat pounding with passion, the essence of your other "
	  +"selves enhancing every sense. The darkness rolls back, "
	  +"as if pushed by an invisible hand.");
    else
	ME("Your heart pushes liquid fire through your veins, each "
	  +"beat pounding with passion, the essence of your other "
	  +"selves enhancing every sense until the very ground "
	  +"seems to be vibrating with life.");

    if (strlen(special_msg_other = ENV(me)->union_hook_sway_msg_other(5, me)))
	tell_room(ENV(me), special_msg_other + "\n", me);

    all_seen(objs);

    set_alarm(25.0, 0.0, end_sway);
}

/*
 * End the sway, set all the skills, stats, and props
 * to their old values.
 */
static void
end_sway()
{
    string special_msg, special_msg_other;

    if (new_quick)
	ALTER_PROP(me, LIVE_I_QUICKNESS, -new_quick);
    if (new_aware)
	ALTER_SKILL(me, SS_AWARENESS, -new_aware);
    if (new_dex)
	ALTER_STAT(me, SS_DEX, -new_dex);

    if (dark_increment)
    {
	ALTER_PROP(me, LIVE_I_SEE_DARK, -dark_increment);

	if (dark_increment == 4)
	    ALTER_PROP(me, LIVE_I_SEE_INVIS, -1);
    }

    if (strlen(special_msg = ENV(me)->union_hook_sway_msg(-1, me)))
	ME(special_msg);
    else
	ME("Suddenly the energy that uplifted you ebbs away. "
	  +"The world around you becomes unfocused and hazy, "
	  +"and a feeling of great weariness falls upon you.");

    if (strlen(special_msg_other = ENV(me)->union_hook_sway_msg_other(-1, me)))
	tell_room(ENV(me), special_msg_other + "\n", me);

    me->add_fatigue(-(SWAY_FATIGUE * (1 + random(3))));

    set_alarm(0.0, 0.0, remove_me);
}

/*
 * Some wizard dested me. Bad Wizard. Baaaaad Wizard.
 */
public void
remove_object()
{
    if (IS_CLONE)
	end_sway();

    ::remove_object();
}

static void
remove_me()
{
    ::remove_object();
}

/*
 * time_desc(): return a no-space version
 * of ctime(time()) for use in file names
 */
string
time_desc()
{
    string *t, tt, tdesc = ctime(time());

    /* Parse out the double spaces that sometimes occur
     * in ctime(time()) (when the date is a single char,
     * rather than two chars).
     */
    tdesc = implode(explode(tdesc, "  "), " ");

    /*
     * Index it out
     */
    t = explode(tdesc, " ");

    /*
     * Set the desc to the format: <month>-<day>-<year>
     */
    tt = t[1]+"-"+t[2]+"-"+t[4];

    return tt;
}

/*
 * Is there a file corresponding to a vision which the
 * player should see?
 * Check for:
 *   1. The player's name
 *   2. The player's sphere
 *   3. A file called "anyone"
 */
string
check_vision_file(object who)
{
    string name;

    reset_euid();

    name = who->query_real_name();
    if (file_size(SWAY_DIR + name) > 1)
	return name;

    name = who->query_name();
    if (file_size(SWAY_DIR + name) > 1)
	return name;

    name = who->query_union_sphere();
    if (file_size(SWAY_DIR + name) > 1)
	return name;

    name = "anyone";
    if (file_size(SWAY_DIR + name) > 1)
	return name;

    return 0;
}

int
parse_vision_file(string file)
{
    string read;

    reset_euid();

    if (!strlen(read = read_file(SWAY_DIR + file)))
    {
	ERROR("Could not read file: " + file);
	return 0;
    }

    events = explode(read, "\n");

    /* Get the vision type. */
    if (sscanf(events[0], "ID: %s", vis_type))
	read = implode(events[1..], "");
    else
	read = implode(events, "");

    /* Index on incidents of the "#" string */
    events = explode(read, "#");

    return 1;
}

void
move_vision_file(object who, string file)
{
    string new;

    reset_euid();

    mkdir(SWAY_DIR + "done");

    file = SWAY_DIR + file;
    new  = SWAY_DIR + "done/" +
	who->query_real_name() +"_"+ time_desc() +
	(strlen(vis_type) ? "_"+ vis_type : "");

    if (strlen(new) > 100)
    {
	ERROR("Tried to move vision file: " + file + " to: " + new +
	    ", but the resulting filename was too long");
	rename(file, file + "_move_err");
    }
    else if (wildmatch(new, "* *"))
    {
	ERROR("Tried to move vision file: " + file + " to: " + new + ", but "
	  + "the resulting filename had a space");
	rename(file, file + "_move_err");
    }
    else if (!rename(file, new))
    {
	ERROR("Failed to move vision file: " + file + " to: " + new);
	rename(file, file + "_move_err");
    }
}

void
start_vision(object who)
{
    reset_euid();

    if (!sizeof(events))
    {
	ERROR("Vision started, but no vision events were specified");
	end_vision(who);
	return;
    }

    event_counter = 0;
    in_vision = 1;
    set_this_player(who);

    init();
    vision(who);
}

void
vision(object who)
{
    string *split;
    string ev;
    int next;
    float alarm;

    if (event_counter >= sizeof(events))
    {
	ERROR("Event counter: " + event_counter + " greater than size "
	  + "of events: " + sizeof(events));
	end_vision(who);
	return;
    }

    ev = events[event_counter];
    split = explode(ev, "&&");

    if (sizeof(split) != 2)
    {
	ERROR("Error in parsing out string: " + ev);
	end_vision(who);
	return;
    }

    if (split[0] == "<>")
    {
	alarm = 0.0;
	who->catch_tell("\n");
    }
    else
    {
	who->catch_tell(split[0] + "\n");
	next = atoi(split[1]);
	if (!next)
	{
	    end_vision(who);
	    return;
	}
	alarm = itof(next);
    }

    event_counter++;
    set_alarm(alarm, 0.0, &vision(who));
}

void
end_vision(object who)
{
    remove_me();
}

/*
 * Paralyze a player if he is experiencing a vision
 */
int
do_nothing(string str)
{
    /*
     * Something has gone horribly, horriby wrong.
     * Allow a cry for help.
     */
    if (query_verb() == "commune")
	return 0;

    write("In the throes of a powerful vision, you cannot "+
	"seem to move at all.\n");

    if (TP->query_wiz_level())
    {
	write("...except, since you are a wizard, you can.\n");
	return 0;
    }

    return 1;
}
