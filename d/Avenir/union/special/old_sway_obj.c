#pragma no_shadow
#pragma no_inherit
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
 */
inherit "/std/object";

#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>

#include "special.h"

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
public int cant_see, skill, dex, aware;
public int new_dex, new_quick, new_aware, darkness;

/* Commands allowed in a vision. */
public string *allowed_cmds = ({ "commune" });

/* The vision events, should they exist */
public string *events, vis_type;


public void
create_object(void)
{
    if (!IS_CLONE)
	return;

    setuid();
    seteuid(getuid());

    set_no_show();
    set_name(SWAY_ID);
    set_long("Can you really see it?\n");
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
	    "energies on entering the Sway.\n");
    }

    special = where->union_hook_sway_msg_other(0, me);
    if (strlen(special))
    {
	tell_room(where, special + "\n", me, me);
    }
    else
    {
	tell_room(where, QCTNAME(me) +" closes "+ HIS(me) +
	    " eyes and seems to be concentrating deeply.\n", me, me);
    }

    /* Stop me from fighting while I concentrate */
    me->add_prop(LIVE_I_CONCENTRATE, 1);

    skill = me->query_skill(SS_SWAY);
#ifdef SKILLS_AFFECTED_BY_FLAME
    skill -= FLAME_DIFF(skill, PSTATE);
#endif

    if (skill < 1)
        skill = 1;

    //dex   = me->query_base_stat(SS_DEX);
    aware = me->query_base_skill(SS_AWARENESS);

    cant_see = 1;
    ALTER_PROP(me, LIVE_I_BLIND, 5);

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
 * Phase one of the sway:
 *  set LIVE_I_SEE_DARK to 1
 *  set quickness to 25% of the sway skill
 *  increase dex by dex * (sway / 10) %
 *    eg. dex of 100, sway of 100 -> dex of 110, quick 25
 *        dex of 55, sway of 40 -> dex of 57, quick 10
 * If sway > random(10) + 10, player can move on to phase_two
 */
private void
phase_one(void)
{
    string special;
    object *objs = all_inventory(ENV(me));

    in_sway = 0;

    /* The player can see again */
    cant_see = 0;
    ALTER_PROP(me, LIVE_I_BLIND, -5);
    me->remove_prop(LIVE_I_CONCENTRATE);

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
        tell_room(environment(me), QCTNAME(me) +" snaps open "+
	    HIS(me) +" eyes and begins to sway with a strange, "+
	    "flowing motion.\n", me, me);
    }

    //new_dex   = skill / 10;
    //ALTER_STAT(me, SS_DEX, new_dex);
    new_quick = skill / 4;
    ALTER_PROP(me, LIVE_I_QUICKNESS, new_quick);

    darkness++;
    ALTER_PROP(me, LIVE_I_SEE_DARK, 1);

    me->query_combat_object()->cb_update_speed();

    if (skill > (random(10) + 10))
        in_sway = set_alarm(10.0, 0.0, phase_two);
    else
        in_sway = set_alarm(10.0, 0.0, end_sway);

    all_seen(objs);
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
private void
phase_two(void)
{
    string special;
    object *objs = filter(all_inventory(ENV(me)), my_seen);

    in_sway = 0;

    /* Only these two were set in Phase One. */
    ALTER_PROP(me, LIVE_I_QUICKNESS, -new_quick);
    //ALTER_STAT(me, SS_DEX, -new_dex);

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

    //new_dex   = skill / 5;
    new_aware = skill / 10;
    new_quick = skill * 5 / 20;

    //ALTER_STAT(me,  SS_DEX, new_dex);
    ALTER_SKILL(me, SS_AWARENESS, new_aware);
    ALTER_PROP(me,  LIVE_I_QUICKNESS, new_quick);

    darkness++;
    ALTER_PROP(me, LIVE_I_SEE_DARK, 1);

    me->query_combat_object()->cb_update_speed();

    if (skill > (random(20) + 20))
        in_sway = set_alarm(15.0, 0.0, phase_three);
    else
        in_sway = set_alarm(15.0, 0.0, end_sway);

    all_seen(objs);
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
private void
phase_three(void)
{
    string special;
    object *objs = filter(all_inventory(ENV(me)), my_seen);

    //ALTER_STAT(me,  SS_DEX, -new_dex);
    ALTER_SKILL(me, SS_AWARENESS, -new_aware);
    ALTER_PROP(me,  LIVE_I_QUICKNESS, -new_quick);

    //new_dex   = skill / 2;
    new_aware = skill / 5;
    new_quick = skill * 6 / 20;

    //ALTER_STAT(me,  SS_DEX, new_dex);
    ALTER_SKILL(me, SS_AWARENESS, new_aware);
    ALTER_PROP(me,  LIVE_I_QUICKNESS, new_quick);

    me->query_combat_object()->cb_update_speed();

    special = ENV(me)->union_hook_sway_msg(3, me);
    if (strlen(special))
    {
        me->catch_msg(special + "\n");
    }
    else if (!CAN_SEE_IN_ROOM(me))
    {
        me->catch_tell("You feel dizzy, almost drunken. "+
	    "Shadows seem to dance before your eyes, and "+
	    "your skin tingles with an icy sensation.\n");
    }
    else
    {
        me->catch_tell("You feel dizzy, almost drunken on "+
	    "the rush of power pulsing through you. In your "+
	    "heightened state, everything around you seems to "+
	    "be moving excruciatingly slowly, as if your "+
	    "relationship to time has changed.\n");
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
 * Phase four of the sway:
 *  set quickness to 95% of the sway skill
 *  set LIVE_I_SEE_DARK to 3
 * Other stats and skills remain the same.
 * If sway > random(10) + 93, player can move on to phase_five
 */
private void
phase_four(void)
{
    string special;
    int o_can_see = CAN_SEE_IN_ROOM(me);
    object *objs = filter(all_inventory(ENV(me)), my_seen);

    ALTER_PROP(me, LIVE_I_QUICKNESS, -new_quick);

    new_quick = skill * 6 / 20;  
    ALTER_PROP(me, LIVE_I_QUICKNESS, new_quick);

    darkness++;
    ALTER_PROP(me, LIVE_I_SEE_DARK, 1);

    me->query_combat_object()->cb_update_speed();

    special = ENV(me)->union_hook_sway_msg(4, me);
    if (strlen(special))
    {
        me->catch_tell(special + "\n");
    }
    else if (!o_can_see && CAN_SEE_IN_ROOM(me))
    {
        me->catch_tell("The blood in your veins pound in a "+
	    "furious crescendo, carrying to your ears the echo "+
	    "of beloved voices. The darkness seems to fade back "+
	    "into a dull grey fog.\n");
    }
    else if (!CAN_SEE_IN_ROOM(me))
    {
        me->catch_tell("The blood in your veins pound in a "+
	    "furious crescendo, carrying to your ears the echo "+
	    "of beloved voices. The darkness seems to glisten "+
	    "all around you.\n");
    }
    else
    {
        me->catch_tell("The blood in your veins pounds in a furious "+
	    "crescendo, carrying to your ears the echo of beloved "+
	    "voices. Colors seem to be emerging and brightening as "+
	    "the Sway lends deeper sight.\n");
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
 * Phase five of the sway:
 *  set LIVE_I_SEE_DARK to 4
 *  set LIVE_I_SEE_INVIS to 1
 * Other stats and skills remain the same.
 * Last phase, end of sway is next
 */
private void
phase_five(void)
{
    string special;
    int o_can_see = CAN_SEE_IN_ROOM(me);
    object *objs = filter(all_inventory(ENV(me)), my_seen);

    in_sway = 0;

    darkness++;
    ALTER_PROP(me, LIVE_I_SEE_DARK, 1);
    ALTER_PROP(me, LIVE_I_SEE_INVIS, 1);

    special = ENV(me)->union_hook_sway_msg(5, me);
    if (strlen(special))
    {
        me->catch_msg(special + "\n");
    }
    else if (!o_can_see && CAN_SEE_IN_ROOM(me))
    {
        me->catch_tell("Your heart pushes liquid fire through your "+
	    "veins, each beat pounding with passion, the essence of "+
	    "your other selves enhancing every sense. The darkness "+
	    "rolls back, as if pushed by an invisible hand.\n");
    }
    else
    {
        me->catch_tell("Your heart pushes liquid fire through your "+
	    "veins, each beat pounding with passion, the essence of "+
	    "your other selves enhancing every sense until the very "+
	    "ground seems to be vibrating with life.\n");
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

    if (new_quick) ALTER_PROP(me,  LIVE_I_QUICKNESS, -new_quick);
    if (new_aware) ALTER_SKILL(me, SS_AWARENESS, -new_aware);
    //if (new_dex)   ALTER_STAT(me,  SS_DEX, -new_dex);

    if (darkness)
    {
        ALTER_PROP(me, LIVE_I_SEE_DARK, -darkness);
        if (darkness == 4) ALTER_PROP(me, LIVE_I_SEE_INVIS, -1);
    }

    special = ENV(me)->union_hook_sway_msg(-1, me);
    if (strlen(special))
    {
        me->catch_msg(special + "\n");
    }
    else
    {
        me->catch_tell("Suddenly the energy that uplifted you ebbs "+
	    "away. The world around you becomes unfocused and hazy, "+
	    "and a feeling of great weariness falls upon you.\n");
    }

    special = ENV(me)->union_hook_sway_msg_other(-1, me);
    if (strlen(special)) tell_room(ENV(me), special + "\n", me, me);

    me->add_fatigue(-(SWAY_FATIGUE * (1 + random(darkness))));
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
