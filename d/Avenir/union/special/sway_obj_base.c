#pragma no_shadow
#pragma strict_types
/*
 * - /d/Avenir/union/obj/sway.c
 *
 * The Sway
 * Cirion 032506
 *
 * Revisions:
 *
 * Cirion, Dec 1997: Put in checks for the environment's
 *         function union_hook_sway_msg() - if it exists, then players
 *         will get that message instead of the defaults.
 *         
 * Cirion, Jun 1997: Added the cabability of generating
 *         visions when entering the sway. The visions work
 *         like this:
 *
 * Lilith, Sep 2003: end_sway() removed properties and skills 
 *         w/o a check to see if the amt removed = amt added. 
 *         This was resulting in removal of props and skills 
 *         modified by other objects such as spells.
 *
 * Lilith, May 2004: Updated sway messages, they've been the
 *         same for many years.
 *
 * Lucius, Dec 2004: Fixed bad interaction with other items setting
 *         extra skill/stat bonuses.
 * 
 * Lilith, Jan 2006: Upped darksight bonus so that it begins in the 
 *         first phase and increases to 4 levels instead of 3, also
 *         per req of Elders. Tax was increased from .50% to 1.0% 
 *
 * Lilith, Jan 2006: Removed Con bonus. It was deemed not worth
 *         the 1% tax paid and removed upon request of the Elders.
 *
 * Lucius, Apr 2008: Quickness prior to sway was being doubled,
 *                   noticed by AoB and corrected.
 *
 * Lucius, Jul 2011: Added <> to vision style format.
 * Lucius, Jul 2017: Cleanups. New vision system.
 *
 * Carnak, Apr 2021: Fixing the balance of the special
 *
 * Lilith, May 2021: Refactor the code to allow multiple forms of
 *                   the sway.  This is the base form, common
 *                   effects to all versions of the sway.
 *
 * Lilith, Aug 2021: Fixed bug that "visions" were causing with the 
 *                   Sway not ending, leaving members in limbo w/o 
 *                   ability to see. 
 */
inherit "/std/object";

#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>

#include "special.h"
#include "/d/Avenir/union/lib/filters.h"
#include "/d/Avenir/include/macros.h"

#define ERROR(x) \
    write_file(VISIONS + "ERRORS", ctime(time()) + ": "+ x +"\n")

/* Function prototypes */
private void phase_one(void);
private void phase_two(void);
private void phase_three(void);
private void phase_four(void);
private void phase_five(void);
private void end_sway(void);

private void start_vision(object *objs);
public int nothing(string str);

public object me;
public int in_sway, in_vision;
public int cant_see, skill, aware;
public int new_aware;

/* Commands allowed in a vision. */
public string *allowed_cmds = ({ "commune" });

/* The vision events, should they exist */
public string *events, vis_type;


private string phase_three_message;
private string phase_four_message;
private string phase_five_message;
private string end_sway_message;

/* These effects take place when the sway begins,
   and the Warrior closes their eyes. */
void apply_init_effects(void) {
    /* Stop me from fighting while I concentrate */
    me->add_prop(LIVE_I_CONCENTRATE, 1);

    aware = me->query_base_skill(SS_AWARENESS);

    cant_see = 1;
    ALTER_PROP(me, LIVE_I_BLIND, 5);

    me->add_prop(SWAY_PHASE_PROP, 0);
}

void apply_phase_one_effects(void) {
    /* The player can see again */
    cant_see = 0;
    ALTER_PROP(me, LIVE_I_BLIND, -5);
    me->remove_prop(LIVE_I_CONCENTRATE);

    me->add_prop(SWAY_PHASE_PROP, 1);
}

void apply_phase_two_effects(void) {
    /* Boost awareness by up to 10 points */
    new_aware = skill / 10;
    ALTER_SKILL(me, SS_AWARENESS, new_aware);

    me->add_prop(SWAY_PHASE_PROP, 2);
}

void apply_phase_three_effects(void) {
    /* Boost awareness by up to 20 points */
    ALTER_SKILL(me, SS_AWARENESS, -new_aware);
    new_aware = skill / 5;
    ALTER_SKILL(me, SS_AWARENESS, new_aware);

    me->add_prop(SWAY_PHASE_PROP, 3);
}

void apply_phase_four_effects(void) {
    me->add_prop(SWAY_PHASE_PROP, 4);
}

void apply_phase_five_effects(void) {
    me->add_prop(SWAY_PHASE_PROP, 5);
}

void apply_end_sway_effects(void) {
    if (cant_see)
    {
        ALTER_PROP(me, LIVE_I_BLIND, -5);
        cant_see = 0;
        me->remove_prop(LIVE_I_CONCENTRATE);
    }

    if (new_aware) ALTER_SKILL(me, SS_AWARENESS, -new_aware);

    me->add_fatigue(-(SWAY_FATIGUE * (1 + random(me->query_prop(SWAY_PHASE_PROP)))));
    me->remove_prop(SWAY_PHASE_PROP);
}

public void set_phase_three_message(string message) {
  phase_three_message = message;
}

public void set_phase_four_message(string message) {
  phase_four_message = message;
}

public void set_phase_five_message(string message) {
  phase_five_message = message;
}

public void set_end_sway_message(string message) {
  end_sway_message = message;
}

public int has_sway_override(object player)
{
    if (U_IS_PUNISHED(player, U_PUNISHED_NOSTART))
    {
        return 0;
    }
    if (wildmatch("/d/Avenir/union/room/*", file_name(environment(player))))
    {
        return 1;
    }
    return 0;
}

/*
 * Automatically start up when we enter someone's inventory.
 */
public void
enter_env(object to, object from)
{
    mixed delay;
    object where;
    string special;

    ::enter_env(to, from);

    if (!living(to))
    {
	set_alarm(0.0, 0.0, remove_object);
	return;
    }

    me = to;
    where = environment(me);

    special = where->union_hook_sway_msg(0, me);
    if (strlen(special))
    {
	me->catch_msg(special + "\n");
    }
    else
    {
	me->catch_tell("You close your eyes and focus all your "+
	    "energies on entering the " + short() + ".\n");
    }

    special = where->union_hook_sway_msg_other(0, me);
    if (strlen(special))
    {
	tell_room(where, special + "\n", me, me);
    }
    else
    {
    ALLBB(me, QCTNAME(me) +" closes "+ HIS(me) +
	    " eyes and seems to be concentrating deeply.\n");
    }

    skill = me->query_skill(SS_SWAY);
    if (has_sway_override(me))
    {
        skill = max(skill, 50);
    }
#ifdef SKILLS_AFFECTED_BY_FLAME
    skill -= FLAME_DIFF(skill, PSTATE);
#endif

    if (skill < 1)
        skill = 1;

    apply_init_effects();

    delay = 12.0 - itof(skill / 10);
    in_sway = set_alarm(delay, 0.0, phase_one);
}

/*
 * Filter for seen things & people.
 */
private int
my_seen(object ob)
{
    if (ob == me)
	return 0;

    return ob->check_seen(me);
}

/*
 * Everything in the room we can see. This is used when awareness,
 * darksight, see_invis are changes, and will thereby give
 * messages if we can see something we previousley couldn't.
 */
private void
all_seen(object *old_seen)
{
    string item;
    object *ob_list, *obs;

    if (!CAN_SEE_IN_ROOM(me))
	return;

    ob_list = filter(all_inventory(ENV(me)), my_seen);

    if (sizeof(old_seen))
        ob_list -= old_seen;

    if (!sizeof(ob_list))
        return;

    item = COMPOSITE_LIVE(obs = FILTER_LIVE(ob_list));
    if (sizeof(obs))
    {
        me->catch_tell("From the mist and shadows, "+ item +" seem" +
	    (sizeof(obs) > 1 ? "" : "s") +" to emerge.");
    }

    item = COMPOSITE_DEAD(obs = FILTER_DEAD(ob_list));
    if (sizeof(obs))
    {
        me->catch_tell("Rising from obscurity, "+ item + " appear" +
	    (sizeof(obs) > 1 ? "" : "s") +" before you.");
    }
}

/*
 * Phase one of the sway.  See apply_phase_one_effects
 * for the combat effects that are being applied.
 * If sway > random(10) + 10, player can move on to phase_two
 */
private void
phase_one(void)
{
    string special;
    object *objs = all_inventory(ENV(me));

    in_sway = 0;

    /* Here we check to see if the player should
     * be affected by a vision */
    if (start_vision(objs))
        return;

    objs = filter(objs, my_seen);

    special = ENV(me)->union_hook_sway_msg(1, me);
    if (strlen(special))
    {
        me->catch_msg(special + "\n");
    }
    else if (CAN_SEE_IN_ROOM(me))
    {
        me->catch_tell("You snap your eyes open, and "+
	    "the area seems to fall into sharper focus.\n");
    }
    else
    {
        me->catch_tell("You snap your eyes open, and the "+
	    "darkness around you seems to breathe with life.\n");
    }

    special = ENV(me)->union_hook_sway_msg_other(1, me);
    if (strlen(special))
    {
        tell_room(ENV(me), special + "\n", me);
    }
    else
    {
        ALLBB(me, QCTNAME(me) +" snaps open "+
	    HIS(me) +" eyes and begins to sway with a graceful, "+
	    "flowing motion.\n");
    }

    apply_phase_one_effects();

    if (skill > (random(10) + 10))
        in_sway = set_alarm(10.0, 0.0, phase_two);
    else
        in_sway = set_alarm(10.0, 0.0, end_sway);

    all_seen(objs);
}

/*
 * Phase two of the sway.  See apply_phase_two_effects for the
 * combat effects that are being applied.
 * If sway > random(20) + 20, player can move on to phase_three
 */
private void
phase_two(void)
{
    string special;
    object *objs = filter(all_inventory(ENV(me)), my_seen);

    in_sway = 0;

    apply_phase_two_effects();

    special = ENV(me)->union_hook_sway_msg(2, me);
    if (strlen(special))
    {
        me->catch_msg(special + "\n");
    }
    else if (CAN_SEE_IN_ROOM(me))
    {
        me->catch_tell("You feel the blood in your veins "+
	    "start to rush frantically, flooding you with "+
	    "a power that makes your muscles tingle. "+
	    "Everything seems to move very slowly.\n");
    }
    else
    {
        me->catch_tell("You feel the blood in your veins "+
	    "start to rush frantically, flooding you with "+
	    "a power that makes your muscles tingle. The "+
	    "darkness around you seems to pulsate like a heart.\n");
    }

    special = ENV(me)->union_hook_sway_msg_other(2, me);
    if (strlen(special)) tell_room(ENV(me), special + "\n", me, me);

    if (skill > (random(20) + 20))
        in_sway = set_alarm(15.0, 0.0, phase_three);
    else
        in_sway = set_alarm(15.0, 0.0, end_sway);

    all_seen(objs);
}

/*
 * Phase three of the sway.  See apply_phase_three_effects
 * for the combat effects being applied.
 * If sway > random(40) + 50, player can move on to phase_four
 */
private void
phase_three(void)
{
    string special;
    int o_can_see = CAN_SEE_IN_ROOM(me);
    object *objs = filter(all_inventory(ENV(me)), my_seen);

    apply_phase_three_effects();

    special = ENV(me)->union_hook_sway_msg(3, me);
    if (strlen(special))
    {
        me->catch_msg(special + "\n");
    }
    else
    {
        me->catch_tell(phase_three_message);
        if (!o_can_see && CAN_SEE_IN_ROOM(me))
        {
            me->catch_tell("The darkness seems to fade back "+
	        "into a dull grey fog.\n");
        }
    }

    special = ENV(me)->union_hook_sway_msg_other(3, me);
    if (strlen(special)) tell_room(ENV(me), special + "\n", me, me);

    if (skill > (random(30) + 50))
        in_sway = set_alarm(20.0, 0.0, phase_four);
    else
        in_sway = set_alarm(20.0, 0.0, end_sway);

    all_seen(objs);
}

/*
 * Phase four of the sway.  See apply_phase_four_effects
 * for the combat effects being applied.
 * If sway > random(10) + 93, player can move on to phase_five
 */
private void
phase_four(void)
{
    string special;
    int o_can_see = CAN_SEE_IN_ROOM(me);
    object *objs = filter(all_inventory(ENV(me)), my_seen);

    apply_phase_four_effects();

    special = ENV(me)->union_hook_sway_msg(4, me);
    if (strlen(special))
    {
        me->catch_tell(special + "\n");
    }
    else {
        me->catch_tell(phase_four_message);
        if (!o_can_see && CAN_SEE_IN_ROOM(me))
        {
            me->catch_tell("The darkness seems to fade back "+
	        "into a dull grey fog.\n");
        }
    }

    special = ENV(me)->union_hook_sway_msg_other(4, me);
    if (strlen(special)) tell_room(ENV(me), special + "\n", me, me);

    if (skill > (random(10) + 85))
        in_sway = set_alarm(30.0, 0.0, phase_five);
    else
        in_sway = set_alarm(30.0, 0.0, end_sway);

    all_seen(objs);
}

/*
 * Phase five of the sway.  See apply_phase_five_effects
 * for the combat effects being applied.
 * Last phase, end of sway is next
 */
private void
phase_five(void)
{
    string special;
    int o_can_see = CAN_SEE_IN_ROOM(me);
    object *objs = filter(all_inventory(ENV(me)), my_seen);

    in_sway = 0;

    apply_phase_five_effects();

    special = ENV(me)->union_hook_sway_msg(5, me);
    if (strlen(special))
    {
        me->catch_msg(special + "\n");
    }
    else
    {
        me->catch_tell(phase_five_message);
        if (!o_can_see && CAN_SEE_IN_ROOM(me))
        {
            me->catch_tell("The darkness rolls back, as if pushed by "+
	        "an invisible hand.\n");
        }
    }
    special = ENV(me)->union_hook_sway_msg_other(5, me);
    if (strlen(special)) tell_room(ENV(me), special + "\n", me, me);

    in_sway = set_alarm(25.0, 0.0, end_sway);
    all_seen(objs);
}

/*
 * End the sway, set all the skills, stats, and props
 * to their old values.
 */
private void
end_sway(void)
{
    string special;

    in_sway = 0;

    apply_end_sway_effects();

    special = ENV(me)->union_hook_sway_msg(-1, me);
    if (strlen(special))
    {
        me->catch_msg(special + "\n");
    }
    else
    {
        me->catch_tell(end_sway_message);
    }

    special = ENV(me)->union_hook_sway_msg_other(-1, me);
    if (strlen(special)) tell_room(ENV(me), special + "\n", me, me);

    set_alarm(0.0, 0.0, remove_object);
}

/*
 * Return a no-space version
 * of ctime(time()) for use in file names
 */
private string
time_desc(void)
{   /* Parse out the double spaces that sometimes occur
     * in ctime(time()) (when the date is a single char,
     * rather than two chars).
     */
    string *tdesc = filter(explode(ctime(time()), " "), strlen);
    /*
     * Set the desc to the format: <month>-<day>-<year>
     */
    return tdesc[1]+"-"+tdesc[2]+"-"+tdesc[4];
}

private int
parse_vision_file(void)
{
    string read, vision = LIST->query_union_vision(me);

    if (!strlen(vision))
	return 0;

    /* Make sure the vision file exists. */
    read = VISIONS + vision;

    if (file_size(read) < 1)
    {
	ERROR("Could not find file: " + vision);
	return 0;
    }

    /* Try to read in the vision file. */
    read = read_file(read);

    if (!strlen(read))
    {
	ERROR("Could not read file: " + vision);
	return 0;
    }

    /* Index on incidents of the "#" string. */
    events = explode(read, "#");

    if (!sizeof(events))
    {
	ERROR("Found "+ vision +", but no events were parsed!");
	return 0;
    }

    LOG_EVENT(me->query_cap_name() +" received vision: "+ vision);
    return 1;
}

private void
end_vision(void)
{
    in_vision = 0;
    me->catch_tell("You open your eyes once more.\n");
    apply_end_sway_effects();
    set_alarm(0.0, 0.0, remove_object);
}

private void
vision(int counter)
{
    int next;
    string ev, *split;

    if (counter >= sizeof(events))
    {
	ERROR("Event counter: " + counter + " greater than size "+
	    "of events: " + sizeof(events));
	end_vision();
	return;
    }

    ev = events[counter];
    split = explode(ev, "&&");

    if (sizeof(split) != 2)
    {
	ERROR("Error in parsing out string: " + ev);
	end_vision();
	return;
    }

    if (split[0] == "<>")
    {
	next = 0;
	me->catch_tell("\n");
    }
    else
    {
	me->catch_tell(split[0] + "\n");
	next = atoi(split[1]);
	if (!next)
	{
	    end_vision();
	    return;
	}
    }

    in_vision = set_alarm(itof(next), 0.0, &vision(++counter));
}

private int
start_vision(object *objs)
{
    if (objectp(me->query_attack()))
	return 0;

    if (sizeof(FILTER_OTHER_LIVE(objs)))
	return 0;

    if (!parse_vision_file())
	return 0;

    add_action(nothing, "", 1);
    vision(0);
    return 1;
}

/*
 * Paralyze a player if he is experiencing a vision
 */
public int
nothing(string str)
{
    /*
     * Something has gone horriby wrong.
     * Allow a cry for help.
     */
    if (member_array(query_verb(), allowed_cmds) != -1)
	return 0;

    write("In the throes of a powerful vision, you cannot "+
      "seem to move at all.\n");

    if (TP->query_wiz_level())
    {
	write("....except, since you are a wizard, you can.\n");
	return 0;
    }

    return 1;
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
 * their eyes so they can enter into the Sway.
 */
public void
init(void)
{
    ::init();

    add_action(nosee, "look");
    add_action(nosee, "examine");
    add_action(nosee, "exa");
    add_action(nosee, "appraise");
}

/*
 * Some wizard dested me. Bad Wizard. Baaaaad Wizard.
 */
public void
remove_object(void)
{
    if (in_sway)
	end_sway();
    else if (in_vision)
	end_vision();
    else
	::remove_object();
}
