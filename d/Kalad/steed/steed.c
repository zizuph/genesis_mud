/*
 * steed.c
 *
 * A standard steed which you can mount and ride around with.
 *
 * Copyright by Wout de Zeeuw, Fysix@Genesis, March 1997
 *
 * Revision History:
 *
 *    17 Jan 1998 - Unkown updates by Fysix.
 *    Unknown     - Modifications by Trofast for leading steeds.
 *    04.01.2000  - Lucius, Major rewrite.
 *    06.??.2000  - Lucius, compatibility updates, bugfixes, misc.
 *
 */
#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/d/Kalad/steed/hooks";
inherit "/d/Kalad/steed/feeding";

#define COMPAT /* This should allow to work with old code. */

#define STEED_PATH              "/d/Kalad/steed/"
#define STEED_RIDER_SHADOW      (STEED_PATH + "steed_sh")
#define STEED_LEAD_SHADOW       (STEED_PATH + "lead_sh")
#define STEED_MOUNT_SUBLOC      "_steed_mount_subloc"
#define STEED_RIDER_SUBLOC      "_steed_rider_subloc"
#define STEED_MAX_RIDERS        2
#define STEED_LEAD_MAX		3

#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

static object	leader;		/* Leader of this steed                    */
static object	*riders;	/* Riders on the steed                     */
static int	max_riders,	/* Max riders on this steed                */
		last_moved,	/* When did the steed move last            */
		mounted_combat,	/* Do we allow mounted combat?             */
		steed_skill,	/* What skill do we use for skill checks?  */
		no_trans;	/* Does the steed get transed with driver  */
static int	*redir_skills;	/* Skills to redirect                      */
static string	shadow_file;	/* Location of the rider shadow            */
static string	*valid_dest,	/* Valid steed destinations                */
		*invalid_dest,	/* Invalid steed destinations              */
		*invalid_unmounted_dest; /* Invalid unmounted destinations */

/*
 * Function name: query_valid_steed
 * Description:   Query for filter functions to show this is a
 *                genuine steed.
 * Returns:       int   1 - Always
 */
public nomask int
query_valid_steed()
{
    return 1;
}

/*
 * Function name: set_steed_max_riders
 * Description:   Set how many are allowed to mount this steed.
 * Arguments:     int: number of riders
 * Returns:       void
 * Note:          There is a mudlib defined hardcap on max riders
 *                that you cannot bypass.
 */
public nomask void
set_steed_max_riders(int i)
{
    if (i > STEED_MAX_RIDERS)
    {
	max_riders = STEED_MAX_RIDERS;
    }

    if (i < 0)
    {
	max_riders = 0;
    }

    max_riders = i;
}

/*
 * Function name: query_steed_max_riders
 * Description:   How many riders can we have
 * Returns:       int: number of riders.
 */
public nomask int
query_steed_max_riders()
{
    return max_riders;
}

/*
 * Function name: set_steed_shadow
 * Description:   Set the file name of the shadow that has
 *                to be loaded when a living mounts the steed.
 * Arguments:     string: the path to your shadow
 * Returns:       void
 */
static nomask void
set_steed_shadow(string s)
{
    shadow_file = s;
}

/*
 * Function name: query_steed_shadow
 * Description:   Query the file name of the shadow that has
 *                to be loaded when a living mounts the steed.
 * Returns:       string: the path to the shadow
 */
static nomask string
query_steed_shadow(string s)
{
    return shadow_file;
}

/*
 * Function name: query_steed_driver
 * Description:   Who is driving the horse?
 * Returns:       object - the driver
 */
public nomask object
query_steed_driver()
{
    if (!riders || !sizeof(riders))
    {
	return 0;
    }

    return riders[0];
}

/*
 * Function name: query_steed_leader
 * Description:   Who is leading this steed?
 * Returns:       object: leader of steed
 */
public nomask object
query_steed_leader()
{
    return leader;
}

/*
 * Function name: query_steed_riders
 * Description:   Who is/are riding the steed?
 * Returns:       object* - an array containing the rider object(s)
 */
public nomask object *
query_steed_riders()
{
    if (!riders)
    {
	return ({});
    }

    return ({}) + riders;
}

/*
 * Function name: set_steed_valid_dest
 * Description:   Props to determine if a steed may move to a location.
 * Arguments:     mixed: prop - the prop(s) to add.
 */
public nomask void
set_steed_valid_dest(mixed prop)
{
    if (!pointerp(prop))
    {
	prop = ({ prop });
    }

    valid_dest = prop;
}

/*
 * Function name: add_steed_valid_dest
 * Description:   Props to determine if a steed may move to a location.
 * Arguments:     mixed: prop - the prop(s) to add.
 */
public nomask void
add_steed_valid_dest(mixed prop)
{
    if (!pointerp(prop))
    {
	prop = ({ prop });
    }

    valid_dest += prop;
}

/*
 * Function name: query_steed_valid_dest
 * Description:   Determine the valid props, or if a certain prop is valid.
 * Arguments:     str: (optional) The prop value to check.
 * Returns:       int:  1 - Prop is valid, 0 - Prop not in list
 *                string *: List of valid props
 */
public nomask varargs mixed
query_steed_valid_dest(string str)
{
    if (stringp(str))
    {
	return (member_array(str, valid_dest) != 1);
    }

    if (!pointerp(valid_dest))
    {
	valid_dest = ({});
    }

    return ({}) + valid_dest;
}

/*
 * Function name: set_steed_invalid_dest
 * Description:   Props to determine if a steed may move to a location.
 * Arguments:     mixed: prop - the prop(s) to add.
 */
public nomask void
set_steed_invalid_dest(mixed prop)
{
    if (!pointerp(prop))
    {
	prop = ({ prop });
    }

    invalid_dest = prop;
}

/*
 * Function name: add_steed_invalid_dest
 * Description:   Props to determine if a steed may move to a location.
 * Arguments:     mixed: prop - the prop(s) to add.
 */
public nomask void
add_steed_invalid_dest(mixed prop)
{
    if (!pointerp(prop))
    {
	prop = ({ prop });
    }

    invalid_dest += prop;
}

/*
 * Function name: query_steed_invalid_dest
 * Description:   Determine the invalid props, or if a certain prop is invalid.
 * Arguments:     str: (optional) The prop value to check.
 * Returns:       int:  1 - Prop is invalid, 0 - Prop not in list
 *                string *: List of invalid props
 */
public nomask varargs mixed
query_steed_invalid_dest(string str)
{
    if (!pointerp(invalid_dest))
    {
	invalid_dest = ({});
    }

    if (stringp(str))
    {
	return (member_array(str, invalid_dest) != 1);
    }

    return ({}) + invalid_dest;
}

/*
 * Function name: set_steed_invalid_unmounted_dest
 * Description:   Props to determine if a steed may move to a location.
 * Arguments:     mixed: prop - the prop(s) to add.
 */
public nomask void
set_steed_invalid_unmounted_dest(mixed prop)
{
    if (!pointerp(prop))
    {
	prop = ({ prop });
    }

    invalid_unmounted_dest = prop;
}

/*
 * Function name: add_steed_invalid_unmounted_dest
 * Description:   Props to determine if a steed may move to a location.
 * Arguments:     mixed: prop - the prop(s) to add.
 */
public nomask void
add_steed_invalid_unmounted_dest(mixed prop)
{
    if (!pointerp(prop))
    {
	prop = ({ prop });
    }

    invalid_unmounted_dest += prop;
}

/*
 * Function name: query_steed_invalid_unmounted_dest
 * Description:   Determine the invalid props, or if a certain prop is invalid.
 * Arguments:     str: (optional) The prop value to check.
 * Returns:       int:  1 - Prop is invalid, 0 - Prop not in list
 *                string *: List of invalid props
 */
public nomask varargs mixed
query_steed_invalid_unmounted_dest(string str)
{
    if (!pointerp(invalid_unmounted_dest))
    {
	invalid_dest = ({});
    }

    if (stringp(str))
    {
	return (member_array(str, invalid_unmounted_dest) != 1);
    }

    return ({}) + invalid_unmounted_dest;
}

/*
 * Function name: set_steed_skill
 * Description	: What skill number should we do skill checks against?
 * Arguments	: int - The skill number.
 * Returns	: void
 */
public nomask void
set_steed_skill(int arg)
{
    steed_skill = arg;
}

/*
 * Function name: query_steed_skill
 * Description	: What skill number are we checking against?
 * Arguments	: none
 * Returns	: int - The skill to check against.
 */
public nomask int
query_steed_skill()
{
    return steed_skill;
}

/*
 * Function name: set_steed_redir_skills
 * Description:   Set the skill numbers of the skills of the rider that
 *                are to be redirected to this steed. (e.g. climb skill).
 * Arguments:     mixed - a single skill number or an array of skill numbers
 */
public nomask void
set_steed_redir_skills(mixed arg)
{
    if (!pointerp(arg))
    {
	arg = ({ arg });
    }

    redir_skills = arg;
}

/*
 * Function name: add_steed_redir_skills
 * Description:   Set the skill numbers of the skills of the rider that
 *                are to be redirected to this steed. (e.g. climb skill).
 * Arguments:     mixed - a single skill number or an array of skill numbers
 */
public nomask void
add_steed_redir_skills(mixed arg)
{
    if (!pointerp(arg))
    {
	arg = ({ arg });
    }

    redir_skills += arg;
}

/*
 * Function name: query_steed_redir_skills
 * Description:   Return the redirected skills, or check if a
 *                particular skills is being redirected.
 * Arguments:     int: (optional) Skill to check against.
 * Returns:       int: 1 - Yes, redirected, 0 - No, not redirected.
 *                int *: array of redirected skills.
 */
public nomask varargs mixed
query_steed_redir_skills(int i)
{
    if (!pointerp(redir_skills))
    {
	redir_skills = ({});
    }

    if (intp(i))
    {
	return (member_array(i, redir_skills) != -1);
    }

    return ({}) + redir_skills;
}

/*
 * Function name: set_steed_allow_combat
 * Description:   Do we allow mounted combat upon this steed?
 * Arguments:     int:  1 - Yes, 0 - No.
 */
public void
set_steed_allow_combat(int i)
{
    if (i > 0)
    {
	mounted_combat = 1;
    }
    else
    {
	mounted_combat = 0;
    }
}

/*
 * Function name: query_steed_allow_combat
 * Description:   Is mounted combat allowed on this steed?
 * Returns:       int:  1 - Yes, 0 - No.
 */
public int
query_steed_allow_combat()
{
    return mounted_combat;
}

/*
 * Function name: set_steed_no_trans
 * Description:   Is this steed allowed to be transed with the driver.
 * Arguments:     int:  1 - Yes, 0 - No.
 */
public nomask void
set_steed_no_trans(int i)
{
    if (i > 0)
    {
	no_trans = 1;
    }
    else
    {
	no_trans = 0;
    }
}

/*
 * Function name: query_steed_no_trans
 * Description:   Will the steed be transed along with it's rider?
 * Returns:       int:  1 - Yes, 0 - No.
 */
public nomask int
query_steed_no_trans()
{
    return no_trans;
}

/*
 * Function name: steed_check_dest
 * Description:   See if a steed may move into a location
 * Arguments:     mixed: 'dest' variable from move_living()
 *                object: the living
 *                string: 'how' variable from move_living()
 * Returns:       int: 0 - No, 1 - Yes.
 */
public nomask varargs int
steed_check_dest(mixed dest, object who, string how)
{
    int size, i;

    if (!dest)
    {
	return 0;
    }

    if (!query_fatigue())
    {
	st_hook_steed_tired(who, how);
	return 0;
    }

    if ((size = sizeof(riders)) && (riders[0] != who))
    {
	st_hook_not_driver(who, how);
	return 0;
    }

    if (stringp(dest))
    {
	if (LOAD_ERR(dest))
	{
	    return 0;
	}

	if (!objectp(dest = find_object(dest)))
	{
	    return 0;
	}
    }

    if (size)
    {
	i = sizeof(valid_dest);
	while (i--)
	{
	    if (dest->query_prop(valid_dest[i]))
	    {
		return 1;
	    }
	}

	i = sizeof(invalid_dest);
	while (i--)
	{
	    if (dest->query_prop(invalid_dest[i]))
	    {
		return 0;
	    }
	}
    }
    else
    {
	i = sizeof(invalid_unmounted_dest);
	while (i--)
	{
	    if (dest->query_prop(invalid_unmounted_dest[i]))
	    {
		return 0;
	    }
	}
    }

    return 1;
}

/*
 * Function name: add_steed_rider
 * Description:   Checks if rider can mount, and if so, mounts them.
 *                This involves adding them into the riders array
 *                and adding the shadow, subloc and properties needed.
 *                Does not handle messages, the calling function
 *                must handle messages based on return value.
 * Arguments:     object who: the mounter
 * Returns:       int:  0 - Rider added,
 *                      1 - No object to add,
 *                      2 - Bad path to shadow file
 *                      3 - Invalid steed-rider shadow
 *                      4 - Could not add shadow to rider
 */
static nomask int
add_steed_rider(object who)
{
    object sh;

    if (!objectp(who))
    {
	return 1;
    }

    if (!shadow_file)
    {
	shadow_file = STEED_RIDER_SHADOW;
    }

    if (file_size(shadow_file + ".c") < 1)
    {
	return 2;
    }

    sh = clone_object(shadow_file);

    if (!sh->query_valid_steed_shadow())
    {
	sh->remove_object();
	return 3;
    }

    if (!sh->shadow_me(who))
    {
	sh->remove_object();
	return 4;
    }

    sh->set_steed_object(this_object());
    who->add_prop(LIVE_O_STEED, this_object());
    who->add_subloc(STEED_RIDER_SUBLOC, this_object(), "steed");

    if (!riders)
    {
	riders  = ({ who });
    }
    else
    {
	riders += ({ who });

    }

    return 0;
}

/*
 * Function name: remove_steed_rider
 * Description:   Removes a rider from the steed.  Does not handle
 *                messages, those are left to the calling function.
 *                Removes subloc, shadow and properties as needed.
 * Arguments:     object who:  The dismounter
 * Returns:       int:  0 - No such rider,
 *                      1 - Rider removed.
 */
static nomask int
remove_steed_rider(object who, int keep_shadow)
{
    if (!who)
    {
	return 0;
    }

    if (!keep_shadow)
    {
	who->remove_steed_shadow();
    }

    who->remove_subloc(STEED_RIDER_SUBLOC);
    who->remove_prop(LIVE_O_STEED);
    riders -= ({ who });

    return 1;
}

/*
 * Function name: steed_do_mount
 * Description:   Checks to see if an object may mount this steed.
 * Arguments:     object who: object trying to mount.
 * Returns:       int   0 - Successfully mounted.
 *                      1 - Mount is being lead
 *                      2 - Too many riders
 *                      3 - Already mounted (this steed)
 *                      4 - Already mounted (another horse)
 *                      5 - Can't mount during combat conditions
 *                      6 - st_hook_try_mount returned 0
 *                      7 - add_steed_rider failed
 */
public nomask int
steed_do_mount(object who)
{
    mixed tmp;

    if (leader)
    {
	write("You may not mount the "+ ::short() +" while someone "+
	  "is leading it.\n");
	return 1;
    }

    if (sizeof(riders) >= max_riders)
    {
	write("There is not enough room to mount the "+ ::short() +".\n");
	return 2;
    }

    if (tmp = who->query_prop(LIVE_O_STEED))
    {
	if (objectp(tmp) && tmp->query_valid_steed())
	{
	    if (tmp == this_object())
	    {
		write("You are already riding the "+ ::short() +"!\n");
		return 3;
	    }

	    write("You are already riding a horse!\n");
	    return 4;
	}

	who->remove_prop(LIVE_O_STEED);
    }

    if (!st_hook_check_combat(who))
    {
	st_hook_fail_combat(who);
	return 5;
    }

    if (!st_hook_try_mount(who))
    {
	st_hook_fail_mount(who);
	return 6;
    }

    if (tmp = add_steed_rider(who))
    {
	write("Error attempting to mount, please make a bug report. "+
	  "Returned "+ tmp +"\n");
	return 7;
    }

    st_hook_did_mount(who);
    who->reveal_me(1);

    return 0;
}

/*
 * Function name: mount
 * Description:   Does syntax checking; calls the steed_do_mount
 *                function in whichever steed matches the input.
 * Arguments:     string str: The players input
 * Returns:       int   1 - mounting successfull
 *                      0 - didn't mount
 */
public nomask int
mount(string str)
{
    mixed tmp;
    int   size;

    if (!str)
    {
	notify_fail(capitalize(query_verb()) + " what, " +
	  "a steed or horse maybe?\n");
	return 0;
    }

    if (!CAN_SEE_IN_ROOM(this_player()))
    {
	if (stringp(tmp = environment()->query_prop(ROOM_S_DARK_MSG)))
	{
	    notify_fail(tmp);
	}
	else
	{
	    notify_fail("It is too dark to " + query_verb() +
	      " things.\n");
	}

	return 0;
    }

    if (!parse_command(str, all_inventory(environment()),
	"[the] %l", tmp))
    {
	notify_fail(capitalize(query_verb()) + " what?\n");
	return 0;
    }

    tmp  -= ({ tmp[0] });
    tmp   = filter(tmp, &->query_valid_steed());
    size  = sizeof(tmp);

    if (size < 1)
    {
	notify_fail("There is no " + str + " to " +
	  query_verb() + ".\n");
	return 0;
    }

    if (size > 1)
    {
	notify_fail("You may only " + query_verb() +
	  "one steed or horse at a time.\n");

	return 0;
    }

    if (tmp[0] == this_object())
    {
	steed_do_mount(this_player());
	return 1;
    }
    /*
	else
	{
	    tmp[0]->steed_do_mount(this_player());
	}
     */

    return 0;
}

/*
 * Function name: steed_do_dismount
 * Description:   Check to see if a rider may dismount the steed.
 * Arguments:     object who: the object trying to dismount,
 *                int  force: skip dismount checks or not
 *		  int  keep_shadow: don't remove the shadow
 * Returns:       int   0 - successfully dismounted,
 *                      1 - nobody to dismount,
 *                      2 - object isn't a rider of this mount,
 *                      3 - st_hook_try_dismount returned 0,
 *                      4 - remove_steed_rider returned 0.
 */
public nomask varargs int
steed_do_dismount(object who, int force = 0, int keep_shadow = 0)
{
    if (!who)
    {
	return 1;
    }

    if (member_array(who, riders) == -1)
    {
	return 2;
    }

    if (!force && !st_hook_try_dismount(who))
    {
	return 3;
    }

    if (!remove_steed_rider(who, keep_shadow))
    {
	st_hook_fail_dismount(who);
	return 4;
    }

    st_hook_did_dismount(who);
    return 0;
}

/*
 * Function name: steed_do_dismount_all
 * Description:   Dismount all riders.
 * Arguments:     int force: do we force them off or no?
 * Returns:       void
 */
public nomask varargs void
steed_do_dismount_all(int force = 0)
{
    int i;

    if (!riders)
    {
	return;
    }

    i = sizeof(riders);
    while (i--)
    {
	steed_do_dismount(riders[i], force);
    }
}

/*
 * Function name: dismount
 * Description:   Try to dismount from the steed
 * Arguments:     string str: (optional) if used, must match an
 *                            id that the mount uses.
 * Returns:       int:  1 - Yes, we dismounted.
 *                      0 - No, couldn't do it
 */
public nomask int
dismount(string str)
{
    object ob;

    if (!(ob = this_player()->query_prop(LIVE_O_STEED)))
    {
	notify_fail("You are not mounted upon anything!\n");
	return 1;
    }

    if (!objectp(ob))
    {
	notify_fail("You are not mounted upon anything!\n");
	return 1;
    }

    if (str && !ob->id(str))
    {
	notify_fail(capitalize(query_verb()) + " what?\n");
	return 0;
    }

    if (ob == this_object())
    {
	steed_do_dismount(this_player());
	return 1;
    }
    /*
	else
	{
	    ob->steed_do_dismount(this_player());
	}
     */

    return 0;
}

/*
 * Function name: steed_do_lead
 * Description:   Allow a player to lead this steed.
 * Arguments:     object: living attempting to lead
 * Returns:       int   8 - Success,
 *                      1 - No living,
 *                      2 - Steed already led,
 *                      3 - Steed has riders,
 *                      4 - st_hook_try_lead return 0,
 *                      5 - Bad shadow file for lead shadow,
 *                      6 - Could not add shadow,
 *                      7 - add_steed_follow failed (from shadow).
 */
public nomask int
steed_do_lead(object who)
{
    object ob;

    if (!who)
    {
	return 1;
    }

    if (leader)
    {
	if (objectp(leader))
	{
	    write("The " + ::short() + " is already being led " +
	      "by someone.\n");

	    return 2;
	}

	leader = 0;
    }

    if (sizeof(riders))
    {
	write("You may not lead a steed with riders upon it.\n");
	return 3;
    }

    if (!st_hook_try_lead(who))
    {
	st_hook_fail_lead(who);
	return 4;
    }

    if (!who->query_leading_steed())
    {
	if (file_size(STEED_LEAD_SHADOW + ".c") < 1)
	{
	    write("Unexpected error, please make a bug report.\n");
	    return 5;
	}

	ob = clone_object(STEED_LEAD_SHADOW);
	if (!ob->shadow_me(who))
	{
	    ob->remove_lead_shadow();
	    write("Unexpected error, please make a bug report.\n");
	    return 6;
	}
    }

    if (!who->add_steed_follow(this_object()))
    {
	ob->remove_lead_shadow();
	st_hook_add_follow_fail(who);
	return 7;
    }

    leader = who;
    st_hook_did_lead(who);
    return 8;
}

/*
 * Function name: lead
 * Description:   Attempt to lead a steed.
 * Arguments:     string: The steed to lead
 * Returns:       int:  1 - True, 0 - False
 */
public nomask int
lead(string str)
{
    mixed tmp;
    int   size;

    if (!str)
    {
	notify_fail(capitalize(query_verb()) + " what, " +
	  "a steed or horse maybe?\n");
	return 0;
    }

    if (!CAN_SEE_IN_ROOM(this_player()))
    {
	if (stringp(tmp = environment()->query_prop(ROOM_S_DARK_MSG)))
	{
	    notify_fail(tmp);
	}
	else
	{
	    notify_fail("It is too dark to " +
	      query_verb() + " things.\n");
	}

	return 0;
    }

    if (!parse_command(str, all_inventory(environment(this_player())),
	"[the] %l", tmp))
    {
	notify_fail(capitalize(query_verb()) + " what?\n");
	return 0;
    }

    tmp  -= ({ tmp[0] });
    tmp   = filter(tmp, &->query_valid_steed());
    size  = sizeof(tmp);

    if (size < 1)
    {
	notify_fail("There doesn't appear to be any " +
	  str + " to " + query_verb() + " here.\n");
	return 0;
    }

    if (size > STEED_LEAD_MAX)
    {
	notify_fail("You may only " + query_verb() + " " + 
	    LANG_WNUM(STEED_LEAD_MAX) + " steed or horse at a time.\n");
	return 0;
    }

    if (tmp[0] == this_object())
    {
	return steed_do_lead(this_player());
    }

    return 0;
}

/*
 * Function name: steed_do_unlead
 * Descrioption:  Stop leading a steed
 * Arguments:     object: the living
 *                int:    force them of or no?
 * Returns:       int:  0 - Success,
 *                      1 - No living,
 *                      2 - living isn't the leader,
 *                      3 - st_hook_try_lead returned 0,
 *                      4 - remove_steed_follow failed (from shadow).
 */
static nomask varargs int
steed_do_unlead(object who, int force = 0)
{
    if (!who)
    {
	return 1;
    }

    if (leader != who)
    {
	return 2;
    }

    if (!force && !st_hook_try_unlead(who))
    {
	st_hook_fail_unlead(who);
	return 3;
    }

    if (!who->remove_steed_follow(this_object()))
    {
	st_hook_rem_follow_fail(who);
	return 4;
    }

    st_hook_did_unlead(who);
    leader = 0;
    return 0;
}

/*
 * Function name: unlead
 * Description:   Stop leading a steed
 * Arguments:     string: steed to leave
 * Returns:       int: 1 / 0
 */
public nomask int
unlead(string str)
{
    object *tmp;
    int     size;

    if (!str)
    {
	notify_fail(capitalize(query_verb()) + " what?\n");
	return 0;
    }

    if (str == "all")
    {
	tmp = this_player()->query_steed_follow();
	if (!(size = sizeof(tmp)))
	{
	    write("You are leading no steeds.\n");
	    return 1;
	}

	while (size--)
	{
	    tmp[size]->steed_do_unlead(this_player());
	}

	return 1;
    }

    if (!sizeof(tmp = this_player()->query_steed_follow()))
    {
	write("You are leading no steeds.\n");
	return 1;
    }

    if (!(tmp = FIND_STR_IN_ARR(str, tmp)))
    {
	notify_fail(capitalize(query_verb()) + " what?\n");
	return 0;
    }

    size = sizeof(tmp);

    if (size < 1)
    {
	write("You do not have such a steed.\n");
	return 1;
    }

    if (size > 1)
    {
	write("Please be more specific as to which steed " +
	  "you wish to leave behind.\n");

	return 1;
    }

    if (tmp[0] == this_object())
    {
	return !steed_do_unlead(this_player());
    }

    return 0;
}

/*
 * Function name: query_steed_idle_time
 * Description:   How long since the horse last moved.
 * Returns:       int - time in seconds
 */
public nomask int
query_steed_idle_time()
{
    return (time() - last_moved);
}

/*
 * Function name: query_rider_m_in
 * Description:   Query the arrival message of the riders of this steed.
 * Arguments:     object: The rider's message to set.
 * Returns:       string: The message to set.
 */
public string
query_rider_m_in(object who)
{
    return "arrives riding on " + LANG_ADDART(::short());
}

/*
 * Function name: query_rider_m_out
 * Description:   Query the arrival message of the riders of this steed.
 * Arguments:     object: The rider's message to set.
 * Returns:       string: The message to set.
 */
public string
query_rider_m_out(object who)
{
    return "rides "+ LANG_ADDART(::short());
}

/*
 * Function name: query_rider_name
 * Description:   Returns the riders name based on looker.
 *                Used in composite_steed_riders() for steed short.
 * Arguments:     object: rider, onlooker
 * Returns:       string: riders name for onlooker.
 */
public nomask string
query_rider_name(object who, object for_obj)
{
    if (who == for_obj)
    {
	return "you";
    }

    return who->query_art_name(for_obj);
}

/*
 * Function name: composite_riders
 * Description:   Return a string of all the riders based on looker.
 *                Used for the steeds short description.
 * Arguments:     object: Who is looking.
 * Returns:       string: Composite string of riders.
 */
public nomask string
composite_riders(object for_obj)
{
    if (!sizeof(riders))
    {
	return "nobody";
    }

    return COMPOSITE_WORDS(map(riders, &query_rider_name(, for_obj)));
}

/*
 * Function name: short_old
 * Description:   Gives the old short() desc without the rider info.
 * Arguments:     object: Who is looking?
 * Returns:       string: The old short desc.
 */
public nomask varargs string
short_old(object for_obj)
{
    return ::short(for_obj);
}

/*
 * Masked to show current riders (if any)
 */
public nomask varargs string
short(object for_obj)
{
    if (!sizeof(riders))
    {
	return ::short(for_obj);
    }

    if (calling_function(0) == "composite")
    {
	return ::short(for_obj);
    }

    if (!for_obj)
    {
	for_obj = this_player();
    }

    return (::short(for_obj) + " with " +
      composite_riders(for_obj) +
      " riding on " + query_objective());
}

/*
 * Subloc descriptions for riders and mounts.
 */
public string
show_subloc(string subloc, object on, object for_obj)
{
    int size;

    if (subloc == STEED_RIDER_SUBLOC)
    {
	return (on == for_obj ? "You are " :
	  capitalize(on->query_pronoun()) + " is ") +
	"riding " + LANG_ADDART(::short(for_obj)) + ".\n";
    }
    else if (subloc == STEED_MOUNT_SUBLOC)
    {
	if (!(size = sizeof(riders)))
	{
	    return "";
	}

	if (size == 1)
	{
	    return capitalize(composite_riders(for_obj)) + " " +
	    (for_obj == query_steed_driver() ? "are " : "is ") +
	    "riding on " + (on == for_obj ? "you" : 
	      query_objective()) + ".\n";
	}

	return capitalize(composite_riders(for_obj)) + " are " +
	"riding on " + (on == for_obj ? "you" : 
	  query_objective()) + ".\n";
    }
}

/*
 * Allow steeds to use weapons and armours
 */
public string
query_combat_file()
{
    return "/std/combat/ctool";
}

/*
 * Dismount riders if we aren't combat trained.
 * Dismount riders if one of them attacks us.
 *
 * Prevent riders from attacking their mounts.
 */
public void
attacked_by(object who)
{
    if (member_array(who, riders) != -1)
    {
	steed_do_dismount_all(1);
    }
    else if (!mounted_combat)
    {
	steed_do_dismount_all(1);
    }

    ::attacked_by(who);
}

/*
 * Rut roh, kick off the riders and remove leaders
 * if we are destroyed.
 */
public void
remove_object()
{
    if (objectp(leader))
    {
	steed_do_unlead(leader, 1);
    }

    steed_do_dismount_all(1);
    ::remove_object();
}

/*
 * We died, not a good thing, kick off the riders and say
 * goodbye to the leader.
 */
public void
do_die(object who)
{
    if (query_hp() > 0)
    {
	return;
    }

    if (objectp(leader))
    {
	steed_do_unlead(leader, 1);
    }

    steed_do_dismount_all(1);
    ::do_die(who);
}

/*
 * Masked to allow in for correct sneakage.
 */
public mixed
query_prop(string prop)
{
    object tmp;

    if ((prop == OBJ_I_HIDE) || (prop == LIVE_I_SNEAK))
    {
	if (objectp(tmp = query_steed_driver()))
	{
	    return tmp->query_prop(prop);
	}
    }

    return ::query_prop(prop);
}

/*
 * Provide a method to call the normal move_living code in the steed
 */
public nomask varargs int
move_living_old(string how, mixed dest, int dont_follow, int no_glance)
{
    return ::move_living(how, dest, dont_follow, no_glance);
}

/*
 * The masked move_living allows us to recored the time the steed moved
 * and to move along riders if the steed has moved of it's own accord,
 * or been forced (panic, spells, etc).
 */
public nomask varargs int
move_living(string how, mixed dest, int dont_follow, int no_glance)
{
    int    res, size;
    string myhow;
    object driver;

    if (size = sizeof(riders))
    {
	myhow  = "M";
	driver = riders[0];
    }
    else
    {
	myhow = how;
    }

    if (!steed_check_dest(dest, driver, how))
    {
	st_hook_invalid_dest(driver, how);
	return 8;
    }

    res = ::move_living(myhow, dest, dont_follow, no_glance);

    if (res == 0)
    {
	last_moved = time();
    }
    else
    {
	st_hook_invalid_dest(driver, how);
	return res;
    }

    if (size > 1)
    {
	riders[1..]->move_living_old(how, dest, 1, 0);
    }

    st_hook_steed_moved();
    return res;
}

/*
 * Function name: init_steed_feed
 * Description	: Add the feeding commands into the steed.
 * Arguments	: none
 * Returns	: void
 */
private void
init_steed_feed()
{
    add_action(feed, "feed");
}

/*
 * Function name: init_steed_lead
 * Description	: Add the leading commands into the steed.
 * Arguments	: none
 * Returns	: void
 */
public void
init_steed_lead()
{
    add_action(unlead, "unlead");
    //    add_action(unlead, "leave" );
    add_action(  lead, "lead"  );
}

/*
 * Function name: init_steed
 * Description	: Add the basic commands into the steed.
 * Arguments	: none
 * Returns	: void
 */
private void
init_steed()
{
    init_steed_lead();
    init_steed_feed();

    add_action(dismount, "dismount");
    add_action(   mount, "ride"    );
    add_action(   mount, "mount"   );
}

/*
 * Add in the commands to the players as we encounter them.
 * Need to find a better way, this is inefficient.
 */
public void
init_living()
{
    ::init_living();
    init_steed();
}

/*
 * Function name: attack_steed
 * Description	: This checks to see if riders may attack their mounts.
 * Arguments	: None
 * Returns	: string - empty, fail attack, print hook message
 *		  int	 - 0, we are allowed to attack.
 * Notes	: This is not included in the query_prop mask
 *		  as someone may wish to add a real no_atack prop.
 */
public mixed
attack_steed()
{
    if (member_array(this_player(), riders) > -1)
    {
	if (!st_hook_try_attack_mount(this_player()))
	{
	    st_hook_fail_attack_mount(this_player());
	    return "";
	}
    }
    return 0;
}

/*
 * Function name: create_steed
 * Description:   Creation function of the steed
 * Returns:       void
 */
public void
create_steed()
{
}

/*
 * create_creature mask to setup our steeds with default
 * values and make people use the create_steed function.
 */
public nomask void
create_creature()
{
    /* Set some standard items */
    set_name("steed");
    set_race_name("steed");
    set_short("steed");
    set_long("A boring, undescribed standard type steed.\n");
    set_gender(G_NEUTER);

    /* Set some standard properties */
    add_prop(LIVE_I_NO_FOOTPRINTS, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(CONT_I_HEIGHT, 200);

    /* Add these props to check for certain values. */
    add_prop(OBJ_M_NO_ATTACK, &attack_steed());

    /* Give the steed proper hitlocs and attacks. */
    set_attack_unarmed(0, 10, 10, W_IMPALE | W_SLASH, 10, "teeth");
    set_attack_unarmed(1, 15, 20, W_BLUDGEON, 30, "right fore hoof");
    set_attack_unarmed(2, 15, 20, W_BLUDGEON, 30, "left fore hoof");
    set_attack_unarmed(3, 20, 25, W_BLUDGEON, 30, "hind hoofs");

    set_hitloc_unarmed(0, 10, 15, "head");
    set_hitloc_unarmed(1, 10, 40, "body");
    set_hitloc_unarmed(2, 15, 20, "foreleg");
    set_hitloc_unarmed(3, 10, 20, "hindleg");
    set_hitloc_unarmed(4, 10,  5, "tail");

    /* Set some standard steed values */
    set_steed_no_trans(1);
    set_steed_max_riders(1);
    set_steed_allow_combat(0);
    set_steed_skill(SS_RIDING);
    set_steed_shadow(STEED_RIDER_SHADOW);
    set_steed_valid_dest( ({ ROOM_I_ALLOW_STEED }) );
    set_steed_invalid_dest( ({ ROOM_I_NO_ALLOW_STEED, ROOM_I_INSIDE }) );
    set_steed_invalid_unmounted_dest( ({ ROOM_I_NO_ALLOW_STEED }) );
    set_steed_redir_skills( ({ SS_CLIMB, SS_SWIM, SS_SNEAK, SS_HIDE }) );

    /* Now we customize... */
    create_steed();

    /* Add the subloc onto the steed. */
    add_subloc(STEED_MOUNT_SUBLOC, this_object(), "riders");

    last_moved = time();
}

public void
reset_steed()           { ::reset_creature(); }

public nomask void
reset_creature()        { reset_steed(); }

/*
 * Here follows a few compability functions for use with
 * the olde steeds code.
 */
#ifdef COMPAT

public nomask object
query_driver()		{ return query_steed_driver(); }

public nomask int
query_has_riders()	{ return sizeof(riders); }

public nomask object *
query_riders()		{ return query_steed_riders(); }

public nomask int
is_steed()		{ return query_valid_steed(); }

public object
query_leader()		{ return query_steed_leader(); }

#endif COMPAT

