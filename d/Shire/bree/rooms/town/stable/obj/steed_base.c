/*
 * steed.c
 *
 * A standard steed which you can mount and ride around with.
 *
 * Copyright by Wout de Zeeuw, Fysix@Genesis, March 1997
 *
 * Date     wizard  Change
 * Sep 2002 fysix   - Incorporated a lot of Lucius' improvements.
 *                  - automount/autodismount,
 *                  - react slower on auto attack (for auto attacking npcs).
 *                  - introduce rider/leader objects for containing
 *                    rider/leader actions.
 *
 * Jan 2003 Palmer  - Changed dismount(string str) to use str so you can
 *                    "dismount horse instead of just "dismount"
 *
 * 08-04-23 Toby    - Fixed a bad use of environment() in do_mount(object o)
 *                    ( if (environment(this_object()) != environment(o)) ) 
 */
#pragma save_binary
#pragma strict_types

inherit "/std/creature.c";
inherit "/std/combat/unarmed.c";

#define STEED_PATH "/d/Genesis/steed/new/"

// Standard rider's shadow for riding around.
// #define STD_RIDER_SHADOW STEED_PATH + "rider_shadow"
#define STD_RIDER_SHADOW "/d/Shire/bree/rooms/town/stable/obj/rider_shadow"

// The feeding module.
#define FEEDING STEED_PATH + "feeding"
// The leading shadow.
#define LEADER_SHADOW STEED_PATH + "leader_shadow"
//#define LEADER_SHADOW "/d/Shire/bree/rooms/town/stable/obj/leader_shadow"
// Rider object with rider commands.
#define RIDER_OBJECT "/d/Shire/bree/rooms/town/stable/obj/rider_object"
// Leader object with leader commands.
#define LEADER_OBJECT STEED_PATH + "leader_object"

inherit FEEDING;
inherit STEED_PATH + "hooks";

#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <cmdparse.h>
// Are we running on Genesis?
#include "/d/Genesis/steed/new/default.h"
#include "/d/Genesis/steed/new/steed.h"

// Some macros
#define FAIL(x)   { notify_fail(x); return 0; }
#define NF(x)     notify_fail(x)
#define TP        this_player()
#define HE(x)     (x)->query_pronoun()

// Rider's subloc for showing he's riding a steed
#define RIDER_SUBLOC "_steed"
// Steed's subloc for showing someone is riding it
#define STEED_SUBLOC "_riders"

// --- Global variables ---------------------------------------------

static object *riders = ({ });
/* The living leading this steed. */
static object leader;
/* Maximum number of riders. */
static int max_riders;
/* Number of riders */
static int has_riders;
/* At what time was steed last moved? */
static int last_moved_time;
/* Is mounted combat allowed? */
static int mounted_combat_allowed;
/* Is the steed moved when rider is transed? */
static int no_trans;
/* Some rider skills and stats should be
 * redirected to the steed:
 */
static int *redir_skills = ({ });
/* Valid destination when mounted. */
static string *valid_dest = ({ });
/* Invalid destiantion when mounted. */
static string *invalid_dest = ({ });
/* Invalid dest when not mounted. */
static string *Invalid_unmounted_dest = ({ });
/* The rider shadow that is loaded when mounting. */
static string rider_shadow_file;
/* Automatic dismount flag for when horse cannot go somewhere mounted. */
static int auto_dismount = 0;
/* Automatic mount flag when horse can be mounted. */
static int auto_mount = 0;
/* Alarm that is used to delay the attacked_by reaction. */
static int attacked_by_alarm = 0;
/* The rider object file that is cloned when player mounts. */
static string rider_object_file = RIDER_OBJECT;
/* The rider object that the rider has.
 * The rider object contains rider commands.
 */
static object rider_object;
/* The leader object file that is cloned when player leads. */
static string leader_object_file = LEADER_OBJECT;
/* The leader object that the leader has.
 * The leader object contains leader commands.
 */
static object leader_object;

public int mounted_combat_allowed();
public int idle_time();
public varargs string composite_riders(object for_obj);
public varargs string steed_short(object for_obj);
public int do_lead(object new_leader);
public int do_unlead(object o, int notify_shadow = 0);
public varargs int do_dismount(object rider, int force = 0);

/* Function name: set_rider_object_file
 * Description:   Set the rider object file.
 *                The rider object file that is cloned when player mounts.
 *                The rider object contains rider commands.
 * Arguments:     string rider_object_file
 */
public void set_rider_object_file(string s)
{
    rider_object_file = s;
}

/* Function name: query_rider_object_file
 * Description:   Query the rider object file.
 * Returns:       string rider_object_file
 */
public string query_rider_object_file()
{
    return rider_object_file;
}

/* Function name: set_leader_object_file
 * Description:   Set the leader object file.
 *                The leader object file that is cloned when player leads.
 *                The leader object contains leader commands.
 * Arguments:     string leader_object_file
 */
public void set_leader_object_file(string s)
{
    leader_object_file = s;
}

/* Function name: query_leader_object_file
 * Description:   Query the leader object file.
 * Returns:       string leader_object_file
 */
public string query_leader_object_file()
{
    return leader_object_file;
}

/* Function name: set_auto_mount
 * Description:   set the auto mount flag.
 * Arguments:     int
 */
public void set_auto_mount(int setting)
{
    auto_mount = setting;
    if (objectp(leader))
    {
        leader->set_steed_with_auto_mount(auto_mount ? this_object() : 0);
    }
}

/* Function name: reset_auto_functions
 * Description:   resets the auto functions to off.
 */
public void reset_auto_functions()
{
    auto_dismount = 0;
    set_auto_mount(0);
}

/* Function name: set_rider_shadow_file
 * Description:   Set the file name of the shadow that has
 *                to be loaded when a living mounts the steed.
 * Arguments:     string: the path to the shadow file.
 */
public void
set_rider_shadow_file(string s)
{
    rider_shadow_file = s;
}

/* Function name: query_rider_shadow_file
 * Description:   Query the file name of the shadow that has
 *                to be loaded when a living mounts the steed.
 * Returns:       string: the path to the shadow file.
 */
public string
query_rider_shadow_file()
{
    return rider_shadow_file;
}

/* Function name: query_has_riders
 * Description:   How many riders does the steed have?
 * Returns:       int
 */
public nomask int
query_has_riders()
{
    return has_riders;
}

/* Function name: query_driver
 * Description:   Who is driving the horse?
 * Returns:       object - the driver
 */
public nomask object
query_driver()
{
    return (has_riders ? riders[0] : 0);
}

/* Function name: query_riders
 * Description:   Who is/are riding the steed?
 * Returns:       object* - an array containing the rider object(s)
 */
public nomask object*
query_riders()
{
    return riders;
}

/* Function name: add_rider
 * Description:   Add the rider object(s). Adds the prop LIVE_O_STEED
 *                to the rider, the rider shadow and the RIDER_SUBLOC.
 * Arguments:     object - the rider.
 * Returns:       (int)
 *                STEED_STS_OK
 *                STEED_STS_TOO_MANY_RIDERS
 *                STEED_STS_RIDER_ALREADY_MOUNTED
 *                STEED_STS_ILLEGAL_SHADOW
 *                STEED_STS_ILL_RIDER_OBJ
 */
public nomask int
add_rider(object rider)
{
    int i;
    int sts;
    object sh;

    // If steed is full, we can't have another rider
    if (has_riders >= max_riders)
    {
        return STEED_STS_TOO_MANY_RIDERS;
    }

    // Check if rider is mounted already!
    if (rider->query_prop(LIVE_O_STEED))
    {
        return STEED_STS_RIDER_ALREADY_MOUNTED;
    }

    // Add a prop and a shadow in the rider
    setuid();
    seteuid(getuid());
    sh = clone_object(query_rider_shadow_file());
    // Check if the shadow is a valid steed shadow
    if (!sh->is_rider_shadow())
    {
        sh->remove_object();
        return STEED_STS_ILLEGAL_SHADOW;
    }
    sh->shadow_me(rider);
    sh->set_steed(this_object());
    rider_object = clone_object(query_rider_object_file());
    if (!objectp(rider_object))
    {
        sh->remove_object();
        return STEED_STS_ILL_RIDER_OBJ;
    }
    rider_object->move(rider, 1);
    rider_object->set_steed(this_object());
    rider_object->set_rider(rider);

    rider->add_prop(LIVE_O_STEED, this_object());
    rider->add_subloc(RIDER_SUBLOC, this_object(), 0);

    riders += ({rider});
    has_riders = sizeof(riders);

    return STEED_STS_OK;
}

/* Function name: remove_rider
 * Description:   Remove rider. Removes the LIVE_O_STEED property
 *                from the rider and the RIDER_SUBLOC subloc from the
 *                steed. It does not remove the rider shadow!
 * Arguments:     object - the rider object
 * Returns:       (int)
 *                STEED_STS_OK
 *                STEED_STS_LIVING_NO_RIDER
 */
public nomask int
remove_rider(object rider)
{
    if (member_array(rider, riders) < 0)
    {
        return STEED_STS_LIVING_NO_RIDER;
    }

    riders -= ({ rider, 0 });
    rider->remove_prop(LIVE_O_STEED);
    rider->remove_subloc(RIDER_SUBLOC);
    rider_object->remove_object();
    rider_object = 0;
    has_riders = sizeof(riders);

    return STEED_STS_OK;
}

/* Function name: set_max_riders
 * Description:   Set the maximum number of people on the steed.
 * Arguments:     int
 */
public nomask void
set_max_riders(int i)
{
    max_riders = i;
}

/* Function name: query_max_riders
 * Description:   What is the maximum number of people on the steed.
 * Returns:       int
 */
public nomask int
query_max_riders()
{
    return max_riders;
}

// --- Functions to handle statuses ----------------------------------------

/* Function name: handle_mount_status
 * Description:   handle mount status in order to give appropriate messages.
 * Arguments:     int status - see steed.h
 *                object living
 * Returns:       void
 */
public void handle_mount_status(int sts, object living)
{
    if (STEED_STS_SUCCESS(sts))
    {
        mount_hook(living);
    }
    else
    {
        switch (sts) {
          case STEED_STS_ILLEGAL_SHADOW:
            living->catch_tell("Illegal steed shadow.\n");
            break;
          case STEED_STS_SKILL_TOO_LOW:
            fail_mount_hook(living);
            break;
          case STEED_STS_LIVING_IN_COMBAT:
          case STEED_STS_STEED_IN_COMBAT:
            fail_mount_in_combat_hook(living);
            break;
          case STEED_STS_ILL_MOUNT_WHILE_LEAD:
            living->catch_tell("You cannot mount the " + short() +
                " while someone is leading it.\n");
            break;
          case STEED_STS_TOO_MANY_RIDERS:
            living->catch_tell("The " + steed_short(living) +
                " cannot carry more riders.\n");
            break;
          case STEED_STS_RIDER_ALREADY:
            living->catch_tell("You are already riding the " +
                short(living) + ".\n");
            break;
          case STEED_STS_RIDER_ALREADY:
            living->catch_tell("You are already mounted.\n");
            break;
          case STEED_STS_ILL_RIDER_OBJ:
            living->catch_tell("Illegal rider object.\n");
            break;
          default :
            living->catch_tell("Failed to mount the " + short(living) + ".\n");
        }
    }
}

/* Function name: handle_dismount_status
 * Description:   handle dismount status in order to give appropriate messages.
 * Arguments:     int status - see steed.h
 *                object living
 * Returns:       void
 */
public void handle_dismount_status(int sts, object living)
{
    if (STEED_STS_SUCCESS(sts))
    {
        dismount_hook(living);
    }
    else
    {
        switch (sts) {
          default :
            living->catch_tell("Unknown dismount fail status.\n");
        }
    }
}

/* Function name: handle_lead_status
 * Description:   handle lead status in order to give appropriate messages.
 * Arguments:     int status - see steed.h
 *                object living
 * Returns:       void
 */
public void handle_lead_status(int sts, object living)
{
    if (STEED_STS_SUCCESS(sts))
    {
        lead_hook(living);
    }
    else
    {
        switch (sts) {
          case STEED_STS_ILL_LEADER_OBJ:
            living->catch_tell("Illegal leader object.\n");
            break;
          default :
            living->catch_tell("Failed to lead.\n");
        }
    }
}

/* Function name: handle_unlead_status
 * Description:   handle unlead status in order to give appropriate messages.
 * Arguments:     int status - see steed.h
 *                object living
 * Returns:       void
 */
public void handle_unlead_status(int sts, object living)
{
    if (STEED_STS_SUCCESS(sts))
    {
        unlead_hook(living);
    }
    else
    {
        switch (sts) {
          case STEED_STS_LIVING_NO_LEADER:
            living->catch_tell("You are not leading the " + steed_short() +
                ".\n");
            break;
          default :
            living->catch_tell("Failed to unlead.\n");
        }
    }
}

// --- mounting and dismounting ------------------------------------

/* Function name: query_auto_mount
 * Description:   Is automatic mount set?
 * Returns:       int
 */
public nomask int
query_auto_mount()
{
    return auto_mount;
}

/* Function name: query_auto_dismount
 * Description:   Is automatic dismount set?
 * Returns:       int
 */
public nomask int
query_auto_dismount()
{
    return auto_dismount;
}

/* Function name: can_mount
 * Description:   Can the living mount the steed?
 *                Called by do_mount. Replace with your own criteria
 *                if needed.
 * Arguments:     object - the living object
 * Returns:       int status - see steed.h
 */
public int
can_mount(object o)
{
    if (o->query_skill(SS_ANI_HANDL) < 20)
    {
        return STEED_STS_SKILL_TOO_LOW;
    }

    return STEED_STS_OK;
}

/* Function name: check_combat
 * Description:   Does this steed support mounted combat?
 *                If not, is the living or the steed not in combat?
 *                Called by do_mount. notify_fail isn't used.
 * Arguments:     object - the living object
 * Returns:       int status - see steed.h
 *                STEED_STS_OK
 *                STEED_STS_LIVING_IN_COMBAT
 *                STEED_STS_STEED_IN_COMBAT
 */
public int
check_combat(object o)
{
    if (mounted_combat_allowed())
    {
        return STEED_STS_OK;
    }

    if (objectp(o->query_attack()))
    {
        return STEED_STS_LIVING_IN_COMBAT;
    }

    if (objectp(query_attack()))
    {
        return STEED_STS_STEED_IN_COMBAT;
    }

    return STEED_STS_OK;
}

/* Function name: do_mount
 * Description:   Let a living mount, calls can_mount and check_combat
 *                to see if it is possible to mount.
 * Arguments:     object - the living object
 * Returns:       int status, see steed.h
 */
public varargs int
do_mount(object o)
{
    object sh, bad_rider;
    int sts;

    if (environment(this_object()) != environment(o))
    {
        return STEED_STS_LIVING_IN_OTHER_LOC;
    }

    if (objectp(leader) && (leader != o))
    {
        return STEED_STS_ILL_MOUNT_WHILE_LEAD;
    }

    if (has_riders >= max_riders)
    {
        return STEED_STS_TOO_MANY_RIDERS;
    }

    if (member_array(o, riders) >= 0)
    {
        return STEED_STS_RIDER_ALREADY;
    }

    if (o->query_prop(LIVE_O_STEED))
    {
        return STEED_STS_RIDER_ALREADY_MOUNTED;
    }

    // Can the living mount?
    sts = can_mount(o);
    if (STEED_STS_FAIL(sts))
    {
        return sts;
    }

    // Is either the living or the steed in combat?
    sts = check_combat(o);
    if (STEED_STS_FAIL(sts))
    {
        return sts;
    }

    // Added by Palmer to prevent multiple rider objects accumulating
    bad_rider = present("__rider_object", o);
    if (objectp(bad_rider))
    {
        //DEBUG tell_room(environment(bad_rider), "Destructing...\n");
        bad_rider->remove_object();
    }


    // unlead first if living was leader.
    if (objectp(leader))
    {
        sts = do_unlead(o, 1);
        handle_unlead_status(sts, o);
        if (STEED_STS_FAIL(sts))
        {
            return sts;
        }
    }

    // Try to add the rider (should always succeed now)
    sts = add_rider(o);
    if (STEED_STS_FAIL(sts))
    {
        return sts;
    }

    // Reveal the living when hidden, always tell him he's revealed
    o->reveal_me(1);

    return STEED_STS_OK;
}

/* Function name: unlead_and_mount
 * Description:   unlead and mount, called for auto mounting by the
 *                leader_shadow.
 * Arguments:     int move_result - this value will be returned.
 * Returns:       int move_result
 */
public int unlead_and_mount(int move_result)
{
    object o;
    int sts;
    o = leader;
    sts = do_mount(o);
    handle_mount_status(sts, o);
    return move_result;
}

/* Function name: dismount_and_lead
 * Description:   dismount and lead, called for dismounting by
 *                rider_shadow.
 *                Only driver should lead.
 * Returns:       int status, see steed.h
 */
public int dismount_and_lead(object o)
{
    object driver = query_driver();
    int sts;

    sts = do_dismount(o);
    handle_dismount_status(sts, o);
    if (STEED_STS_FAIL(sts))
    {
        return sts;
    }
    if (o == driver)
    {
        sts = do_lead(o);
        handle_lead_status(sts, o);
    }
    return sts;
}

/* Function name: can_dismount
 * Description:   Can the living dismount? Might be useful to prevent
 *                dismount on certain locations (e.g. while flying).
 *                Called by sh_do_dismount. Replace with your own criteria
 *                if needed.
 * Arguments:     object - the living object
 * Returns:       int status, see steed.h
 */
public int
can_dismount(object o)
{
    return STEED_STS_OK;
}

/* Function name: sh_do_dismount
 * Description:   Let a living dismount, but don't remove the rider shadow.
 *                This function usually lets a rider dismount, forced
 *                by the shadow itself (hence we don't want it removed).
 *                Called by do_dismount or the rider's shadow.
 *                Calls can_dismount to see if the rider can dismount.
 * Arguments:     object - the living object
 *                int - force dismount, ignoring can_dismount. (default 0)
 * Returns:       int status, see steed.h
 */
public varargs int
sh_do_dismount(object rider, int force = 0)
{
    // Is the living a rider of this steed?
    if (member_array(rider, riders) < 0)
    {
        return STEED_STS_LIVING_NO_RIDER;
    }

    // Can the rider dismount? If forced, living can always dismount
    if (!force)
    {
        int sts = can_dismount(rider);
        if (STEED_STS_FAIL(sts))
        {
            return sts;
        }
    }

   return remove_rider(rider);
}

/* Function name: do_dismount
 * Description:   Let a living dismount, and remove the rider shadow.
 * Arguments:     object - the living object
 * Returns:       int status, see steed.h
 */
public varargs int
do_dismount(object rider, int force = 0)
{
    int sts = sh_do_dismount(rider, force);
    if (STEED_STS_FAIL(sts))
    {
        return sts;
    }

    rider->remove_rider_shadow();
    return STEED_STS_OK;
}

/* Function name: dismount_all
 * Description:   Dismount all riders.
 * Arguments:     int silent: 1 silent dismount (0 by default)
 *                int force: 1 force the riders, ignoring can_dismount
 *                 (0 by default).
 */
public varargs void
dismount_all(int force = 0)
{
    int i = sizeof(riders);
    while (i--)
    {
        object o = riders[i];
        int sts = do_dismount(o, force);
        handle_dismount_status(sts, o);
    }
}

// --- Functions for destination checks of the steed -----------------

/* Function name: query_valid_dest
 * Description:   Returns an array of properties that indicate always valid
 *                destination rooms (no matter the invalid properties)
 *                when the steed has riders.
 * Returns:       string *
 */
public string*
query_valid_dest()
{
    return valid_dest;
}

/* Function name: set_valid_dest
 * Description:   Set the properties that indicate always valid
 *                destination rooms (no matter the invalid properties)
 *                when the steed has riders.
 * Arguments:     mixed - a single property or an array of properties.
 */
public void
set_valid_dest(mixed t)
{
    if (stringp(t))
    {
        t = ({ t });
    }
    if (pointerp(t))
    {
        valid_dest = t;
    }
}

// see set_valid_dest
public void
add_valid_dest(mixed t)
{
    if (stringp(t))
    {
        t = ({ t });
    }
    if (pointerp(t))
    {
        valid_dest += t;
    }
}

/* Function name: query_invalid_dest
 * Description:   Returns an array of properties that indicate invalid
 *                destination rooms when the steed has riders.
 * Returns:       string *
 */
public string*
query_invalid_dest()
{
    return invalid_dest;
}

/* Function name: set_invalid_dest
 * Description:   Set the properties that indicate invalid
 *                destination rooms when the steed has riders.
 * Arguments:     mixed - a single property or an array of properties.
 */
public void
set_invalid_dest(mixed t)
{
    if (stringp(t))
    {
        t = ({ t });
    }
    if (pointerp(t))
    {
        invalid_dest = t;
    }
}

// see set_invalid_dest
public void
add_invalid_dest(mixed t)
{
    if (stringp(t))
    {
        t = ({ t });
    }
    if (pointerp(t))
    {
        invalid_dest += t;
    }
}

/* Function name: query_invalid_unmounted_dest
 * Description:   Returns an array of properties that indicate invalid
 *                destination rooms when the steed has no riders.
 * Returns:       string *
 * TODO: add arg for property to check in stead of returning all
 *  invalid unmounted dest properties.
 */
public string*
query_invalid_unmounted_dest()
{
    return Invalid_unmounted_dest;
}

/* Function name: set_invalid_unmounted_dest
 * Description:   Set the properties that indicate invalid
 *                destination rooms when the steed has no riders.
 * Arguments:     mixed - a single property or an array of properties.
 */
public void
set_invalid_unmounted_dest(mixed t)
{
    if (stringp(t))
    {
        t = ({ t });
    }
    if (pointerp(t))
    {
        Invalid_unmounted_dest = t;
    }
}

// see set_invalid_unmounted_dest
public void
add_invalid_unmounted_dest(mixed t)
{
    if (stringp(t))
    {
        t = ({ t });
    }
    if (pointerp(t))
    {
        Invalid_unmounted_dest += t;
    }
}

/* Function name: check_mounted_destination
 * Description:   Checks if the destination is a valid one for the steed.
 *                (e.g. don't enter small houses etc.)
 *                Is used only when the steed has riders.
 *                Properties as given by query_valid_dest() are
 *                seen as valid destinations.
 *                Properties as given by query_invalid_dest() are
 *                seen as invalid destinations. Valid destinations have
 *                a higher priority.
 * Arguments:     object - the destination object
 * Returns:       int status - see steed.h
 *                STEED_STS_OK
 *                STEED_STS_ILL_MOUNTED_DEST
 */
public int
check_mounted_destination(object to_dest)
{
    int i;

    // Check for valid destination first
    i = sizeof(valid_dest);
    while (i--)
    {
        if (to_dest->query_prop(valid_dest[i]))
        {
            return STEED_STS_OK;
        }
    }

    // Check for invalid destination
    i = sizeof(invalid_dest);
    while (i--)
    {
        if (to_dest->query_prop(invalid_dest[i]))
        {
            return STEED_STS_ILL_MOUNTED_DEST;
        }
    }

    return STEED_STS_OK;
}

/* Similar to check_mounted_destination,
 * but now for the case when no livings are mounted
 * Returns:       int status - see steed.h
 *                STEED_STS_OK
 *                STEED_STS_ILL_MOUNTED_DEST
 */
public int
check_unmounted_destination(object to_dest)
{
    int i;

    // Check for invalid destination
    i = sizeof(Invalid_unmounted_dest);
    while (i--)
    {
        if (to_dest->query_prop(Invalid_unmounted_dest[i]))
        {
            return STEED_STS_ILL_UNMOUNTED_DEST;
        }
    }

    return STEED_STS_OK;
}

/* Function name: check_destination
 * Description:   Check the destination where the steed wants to move
 *                to. Usually called by the driver's shadow.
 *                Calls check_mounted_destination or
 *                check_unmounted_destination depending on if
 *                the steed has riders.
 * Arguments:     mixed destination object/file name
 * Returns:       int status - see steed.h
 */
public int
check_destination(mixed to_dest)
{
    // Check if destination loads, and if it loads, check
    // if the steed can enter... if not, abort
    if (!stringp(LOAD_ERR(to_dest)))
    {
        if (!objectp(to_dest))
        {
            to_dest = find_object(to_dest);
            if (!objectp(to_dest))
            {
                return STEED_STS_ILL_DEST;
            }
        }
    }

    return (has_riders ?
        check_mounted_destination(to_dest) :
        check_unmounted_destination(to_dest));
}

// --- set & query functions for redirection of rider's ------------------
//     abilities to the steed

/* Function name: query_redir_skills
 * Description:   Return the skill numbers of the living skills that are
 *                redirected by the rider's shadow to this steed.
 * Returns:       int * an array of skill numbers
 */
public int*
query_redir_skills()
{
    return redir_skills;
}

/* Function name: set_redir_skills
 * Description:   Set the skill numbers of the skills of the rider that
 *                are to be redirected to this steed. (e.g. climb skill).
 * Arguments:     mixed - a single skill number or an array of skill numbers
 */
public void
set_redir_skills(mixed t)
{
    if (intp(t))
    {
        t = ({ t });
    }
    if (pointerp(t))
    {
        redir_skills = t;
    }
}

// --- Functions related to combat ---------------------------------

// Uses tools
public string
query_combat_file()
{
    return "/std/combat/ctool";
}

/* Function name: allow_mounted_combat
 * Description:   Allow or disallow mounted combat on this steed object.
 * Arguments:     int 0 - false, 1 - true
 */
public void
allow_mounted_combat(int t)
{
    mounted_combat_allowed = t;
}

/* Function name: mounted_combat
 * Description:   Is mounted combat allowed on this steed object?
 * Returns:       int 0 - false, 1 - true
 */
public int
mounted_combat_allowed()
{
    return mounted_combat_allowed;
}

// Delayed call from attacked_by.
public void
delayed_attacked_by(object o)
{
    object attacker;

    attacked_by_alarm = 0;
    attacker = query_attack();
    if (objectp(attacker) && (environment(attacker) == environment()))
    {
        object driver;
        if (sizeof(riders))
        {
            driver = riders[0];
        }
        dismount_all();
        if (objectp(driver))
        {
            int sts = do_lead(driver);
            handle_lead_status(sts, driver);
        }
    }
}

// Checks mounted_combat_allowed(), if no mounted combat allowed,
// when steed is attacked, dismount all riders with a delay.
public void
attacked_by(object o)
{
    if (!mounted_combat_allowed())  // dismount if mounted combat is not allowed
    {
        // Dismount after 3 seconds if still needed.
        if (attacked_by_alarm)
        {
            remove_alarm(attacked_by_alarm);
        }
        attacked_by_alarm = set_alarm(3.0, 0.0, &delayed_attacked_by(o));
    }
    else if (member_array(o, riders) >= 0) // dismount if rider attacks me
    {
        do_dismount(o);
    }

    ::attacked_by(o);
}

// dismount all when horse dies
public void
do_die(object killer)
{
    if (query_hp() > 0)
    {
        return;
    }

    dismount_all(1);
    ::do_die(killer);
}

// --- Move functions ------------------------------------------------

/* Function name: query_cannot_move_to
 * Description:   Check if the steed can't move.
 *                Called by move_living in the steed shadow of a rider.
 * Arguments:     object the rider that wants to move
 *                mixed the destination where the rider wants to go
 *                optional:
 *                string where_to: e.g. "enter the portal", "go north",
 *                   "board the ship".
 *                   If "M" is passed no fail messages will be given.
 *                   If omitted "go there" will will be substituted.
 * Returns:       int 0 if it is ok to move
 *                    8 invalid destination
 *                    9 living is not the driver
 *                   10 steed is too tired
 */
public varargs int
query_cannot_move_to(object living, mixed destination, string where_to)
{
    // If this rider is not the driving rider, don't execute the move
    if (riders[0] != living)
    {
        return 9;
    }

    // Check if the steed is tired
    if (!query_fatigue())
    {
        return 10;
    }

    // Check if the steed can go there
    if (STEED_STS_FAIL(check_destination(destination)))
    {
        return 8;
    }

    return 0;
}

/* Function name: move_living
 * Description:   Records the time in which the steed last moved.
 *                Further: if horse moves by itself (e.g. panic) move
 *                the riders as well. Also does a check
 *                for the destination when the steed has riders.
 * Arguments:     see original move_living function.
 * Returns:       see original move_living function.
 *                int 8 if the destination was not valid
 */
public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    int    r;
    string steed_how;

    // If steed has riders don't show move
    steed_how = has_riders ? "M" : how;

    // Check the destination
    if (STEED_STS_FAIL(check_destination(to_dest)))
    {
        return 8;
    }

    r = ::move_living(steed_how, to_dest, dont_follow, no_glance);

    if (!r)
    {
        last_moved_time = time();
    }

    // Steed has run off by itself (e.g. panic) or
    // is led somewhere by the lead shadow.
    // Let all riders follow automatically by calling the old move_living
    // function (saves some overhead that's in the shadowed move_living fun).
    riders->move_living_old(how, to_dest, 1, 0);

    return r;
}

/* Function name: drive_steed
 * Description:   Let the driver drive the steed, let the other riders
 *                follow the steed. Is different than move_living
 *                since it passes the "how" correctly to the other riders.
 *                Also it doesn't do a destination check.
 *                Records the time in which the steed last moved.
 * Arguments:     see original move_living function.
 * Returns:       int 8 if illegal steed destination.
 */
public varargs int
drive_steed(string how, mixed to_dest, int dont_follow, int no_glance)
{
    int r;

    r = ::move_living("M", to_dest, dont_follow, no_glance);

    if (!r)
    {
        last_moved_time = time();
    }

    // Let the co-riders move too, call original move_living function
    // in the riders (saves some overhead that's in the
    // shadowed move_living)
    riders[1..]->move_living_old(how, to_dest, 1, 0);
    return r;
}

// Make the original move_living function accessible
public varargs int
move_living_old(string how, mixed to_dest, int dont_follow, int no_glance)
{
    return ::move_living(how, to_dest, dont_follow, no_glance);
}


/* Function name: dismount_lead_move
 * Description:   Dismount, lead horse, and move to given destination.
 *                Used for auto-dismount functionality.
 * Arguments:     see original move_living function.
 * Returns:       see original move_living function.
 */
public varargs int dismount_lead_move(
    object living,
    string how,
    mixed to_dest,
    int dont_follow,
    int no_glance)
{
    int sts;

    if (living != riders[0])
    {
        return 9;
    }

    sts = do_dismount(living);
    handle_dismount_status(sts, living);
    if (STEED_STS_FAIL(sts))
    {
        return 11;
    }

    // Dismount went ok, now let's lead.
    sts = do_lead(living);
    handle_lead_status(sts, living);
    if (STEED_STS_FAIL(sts))
    {
        return 12;
    }

    // Lead went ok, now let's move.
    return living->move_living(how, to_dest, dont_follow, no_glance);
}

/* Function name: set_no_trans
 * Description:   Will the steed be moved along when the rider is
 *                transed? (With "X" as the first arg in move_living).
 * Arguments:     int 1 dismount player when transed
 *                    0 move steed with player when he is alone on the steed.
 */
public void
set_no_trans(int i)
{
    no_trans = (i ? 1 : 0);
}

/* Function name: query_no_trans
 * Description:   Will the steed be moved along when the rider is
 *                transed? (With "X" as the first arg in move_living).
 * Returns:       int 1 dismount player when transed
 *                    0 move steed with player when he is alone on the steed.
 */
public int
query_no_trans()
{
    return no_trans;
}

// --- Creation stuff ----------------------------------------------

/* Function name: create_steed
 * Description:   Creation function of the steed
 */
public void
create_steed()
{
}

/* Function name: configure_steed
 * Description:   Give the steed some standard hitlocs and attacks, called
 *                from create_creature. Redefine when you need other
 *                hitlocs or attacks.
 */
public void
configure_steed()
{
    set_race_name("horse");
    set_gender(0);

    set_attack_unarmed(0, 10, 10, W_IMPALE | W_SLASH, 10, "teeth");
    set_attack_unarmed(1, 15, 20, W_BLUDGEON, 30, "right fore hoof");
    set_attack_unarmed(2, 15, 20, W_BLUDGEON, 30, "left fore hoof");
    set_attack_unarmed(3, 20, 25, W_BLUDGEON, 30, "hind hoofs");

    set_hitloc_unarmed(0, 10, 15, "head");
    set_hitloc_unarmed(1, 10, 40, "body");
    set_hitloc_unarmed(2, 15, 20, "foreleg");
    set_hitloc_unarmed(3, 10, 20, "hindleg");
    set_hitloc_unarmed(4, 10, 5, "tail");
}

nomask void
create_creature()
{
    // Some standard properties of the steed
#ifdef GENESIS
    add_prop(LIVE_I_NO_FOOTPRINTS, 1);
#endif
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_HEIGHT, 200);

    configure_steed();

    set_valid_dest(({ ROOM_I_ALLOW_STEED }));
    set_invalid_dest(({ ROOM_I_NO_ALLOW_STEED, ROOM_I_INSIDE }));
    set_invalid_unmounted_dest(({ ROOM_I_NO_ALLOW_STEED }));
    set_redir_skills(({ SS_CLIMB, SS_SWIM, SS_SNEAK, SS_HIDE }));
    last_moved_time = time();

    // Add a subloc to this steed to show riders if present
    add_subloc(STEED_SUBLOC, this_object(), 0);

    set_rider_shadow_file(STD_RIDER_SHADOW);
    set_max_riders(1);
    allow_mounted_combat(0);
    set_no_trans(1);

    create_steed();
}

/* Function name: is_steed
 * Description:   Is this object a steed?
 * Returns:       int 1
 */
public nomask int
is_steed()
{
    return 1;
}

// --- Description functions -------------------------------------

// Shows the following sublocs:
//    RIDER_SUBLOC: the extra description of the rider object
//    STEED_SUBLOC: the extra description of this steed object
public string
show_subloc(string subloc, object on, object for_obj)
{
    string objective, verb;

    if (subloc == RIDER_SUBLOC)  // Extra description for rider
    {
        return (on == for_obj ?
            "You are riding a " + steed_short(for_obj) + ".\n" :
            capitalize(HE(on)) + " is riding a " +
            steed_short(for_obj) + ".\n");
    }
    else if (subloc == STEED_SUBLOC)  // Extra description for steed
    {
        if (!has_riders)
        {
            return ""; // Sanity check, no description to give
        }

        verb = (has_riders == 1 && for_obj != riders[0] ? "is" : "are");
        objective = (on == for_obj ? "you" : query_objective());

        return capitalize(composite_riders(for_obj)) + " " +
            verb + " riding on " + objective + ".\n";
    }

    return "";
}

// Function to return name of a rider
public string
rider_name(object o, object for_obj)
{
    return (for_obj == o ? "you" : o->query_art_name(for_obj));
}

// Function to describe all riders
public string
composite_riders(object for_obj)
{
    return has_riders ?
        COMPOSITE_WORDS(map(riders, &rider_name(, for_obj))) :
        "nobody";
}

// Still make the old short function available.
public varargs string
steed_short(object for_obj)
{
    return ::short(for_obj);
}

// adjusted short desc showing everybody on the steed
public varargs string
short(object for_obj)
{
    // If no riders return the original short desc
    if (!has_riders)
    {
        return steed_short(for_obj);
    }

    if (!objectp(for_obj))
    {
        for_obj = this_player();
    }

    return steed_short(for_obj) + " with " + composite_riders(for_obj) +
      " riding on " + query_objective();
}

// --- leave and arrive messages of the riders ----------------------------

/* Function name: query_rider_m_in
 * Description:   Query the arrival message of the riders of this steed.
 *                Called by set_steed in the steed shadow.
 * Arguments:     object rider
 * Returns:       string
 */
public string
query_rider_m_in(object rider)
{
    return "arrives riding on " + LANG_ADDART(steed_short());
}

/* Function name: query_rider_m_out
 * Description:   Query the leave message of the riders of this steed.
 *                Called by set_steed in the steed shadow.
 * Arguments:     object rider
 * Returns:       string
 */
public string
query_rider_m_out(object rider)
{
    return "rides " + rider->query_possessive() + " " + steed_short();
}

// --- leading functions ---------------------------------------------------

/* Function name: query_leader
 * Description:   Who leads this steed?
 * Returns:       object
 */
public object
query_leader()
{
    return leader;
}

/* Function name: can_lead
 * Description:   Hook to see if the living can lead this steed.
 * Arguments:     object living
 * Returns:       int status - see steed.h
 */
public int
can_lead(object living)
{
    return STEED_STS_OK;
}

/* Function name: do_lead
 * Description:   Let a living lead this steed.
 * Arguments:     object: the leader to be
 * Returns:       int status - see steed.h
 */
public int
do_lead(object new_leader)
{
    object shadow, bad_leader;
    int sts;

    sts = can_lead(new_leader);
    if (STEED_STS_FAIL(sts))
    {
        return sts;
    }

    // Added by Palmer to prevent multiple leader object accumulating
    bad_leader = present("__leader_object", new_leader);
    if (objectp(bad_leader))
    {
        //tell_room(environment(bad_leader), "Destructing...\n");
        bad_leader->remove_object();
    }

    leader = new_leader;
    // See if the living is already leading another horse
    if (!leader->query_leading_steed())
    {
        shadow = clone_object(LEADER_SHADOW);
        shadow->shadow_me(leader);
    }
    leader_object = clone_object(query_leader_object_file());
    if (!objectp(leader_object))
    {
        shadow->remove_object();
        return STEED_STS_ILL_LEADER_OBJ;
    }
    leader_object->move(leader, 1);
    leader_object->set_steed(this_object());
    leader_object->set_leader(leader);

    // Update the auto mount flag in the lead shadow.
    // Palmer:
    // This is where the Mercenariess with dogs following get bugged
    set_auto_mount(auto_mount);
    leader->add_following_steed(this_object());

    return STEED_STS_OK;
}

/* Function name: do_unlead
 * Description:   Let the leader of this steed not lead it anymore.
 * Arguments:     object the supposed to be leader, if not the right
 *                       leader is passed, the function fails.
 *                int - optional: notify the leader's shadow that the leader
 *                   is no longer leading the steed.
 * Returns:       int status - see steed.h
 *                STEED_STS_OK
 *                STEED_STS_LIVING_NO_LEADER
 */
public varargs int
do_unlead(object o, int notify_shadow = 0)
{
    if (leader != o)
    {
        return STEED_STS_LIVING_NO_LEADER;
    }
    if (notify_shadow)
    {
        leader->remove_following_steed(this_object());
    }
    leader_object->remove_object();
    leader_object = 0;

    leader = 0;
    return STEED_STS_OK;
}

// --- Functions for the actions -------------------------------------------

/* Function name: dismount
 * Description:   try to dismount, if syntax is OK, make a call
 *                to do_dismount in the steed object.
 * Arguments:     string - not used
 * Returns:       true if successful
 */
public nomask int
dismount(string str)
{
    object steed;
    int sts;

    dismount_all(1);
    return(1);
    /* Removed so you can "dismount steed"
    if (stringp(str))
    {
        return 0;
    }
*/
    /*
    if (!(steed = this_player()->query_prop(LIVE_O_STEED)))
    {
        FAIL("But you are not mounted on anything.\n");
    }

    sts = steed->do_dismount(this_player());
    steed->handle_dismount_status(sts, this_player());
    if (STEED_STS_FAIL(sts))
    {
        notify_fail("");
    }
    reset_auto_functions();
    return STEED_STS_SUCCESS(sts);
    */
}

/* Function name: lead
 * Description:   lead this steed somewhere
 * Arguments:     string - the steed to lead
 * Returns:       int 1 if successful
 */
public int
lead(string s)
{
    object *o_list;
    object steed;
    int sts;

    if (
        (!s) ||
        (!sizeof(
            o_list =
            FIND_STR_IN_ARR(s, all_inventory(environment(this_player()))))
            )
        )
    {
        return 0;
    }
    if (sizeof(o_list) > 1)
    {
        return 0;
    }
    steed = o_list[0];

    // check if it's a steed
    if (!steed->is_steed())
    {
        return 0;
    }

    // check if we have a leader already

    if (objectp(steed->query_leader()))
    {
        // Palmer Jan 2003 added check to show that YOU are already leading,
        // not just "someone"
        if ((steed->query_leader()) == this_player())
        {
            FAIL("You're already leading the " + steed->short() + ".\n");
        }
        else
        {
            FAIL("The " + steed->short() + " is already lead by someone.\n");
        }
    }

    //Commented by Trofast Dec 1999
    // Don't allow leading when living is riding a steed
    //   if (objectp(this_player()->query_prop(LIVE_O_STEED)))
    //      FAIL("You cannot lead a " + steed->query_race_name() +
    //      " while riding.\n");

    // Don't allow to lead steeds with riders on them
    if (steed->query_has_riders())
    {
        FAIL("You cannot lead a " + steed->query_race_name() +
        " with riders on " + steed->query_objective() + ".\n");
    }

    sts = steed->do_lead(this_player());
    steed->handle_lead_status(sts, this_player());
    if (STEED_STS_FAIL(sts))
    {
        notify_fail("");
    }
    return STEED_STS_SUCCESS(sts);
}

/* Function name: mount
 * Description:   Try to mount a steed, does a syntax check and a check
 *                if the object is a steed (using the is_steed() function)
 *                and then calls do_mount in the steed object
                  Palmer removed "nomask"
 * Arguments:     string - the object description
 * Returns:       1 - if successful
 */
public int
mount(string s)
{
    mixed *o_list;
    int i, index;
    int sts;
    object steed_to_mount = 0;

    if (CAN_SEE_IN_ROOM(this_player()) <= 0)
    {
        return light_fail("mount");
    }

    if (this_player()->query_prop(LIVE_O_STEED))
    {
        FAIL("You are already mounted.\n");
    }

    notify_fail("Mount what? The " + short(this_player()) + "?\n");
    if (
        (!s) ||
        (!parse_command(s, all_inventory(environment(this_player())),
            "%l", o_list))
        )
    {
        return 0;
    }

    index = o_list[0];

    notify_fail("You don't seem to be able to mount that.\n");
    if (index == 0)   // don't allow "mount all horses" or "mount horses"
    {
        return 0;
    }
    if (index > 0)    // allow "mount horse"
    {
        if (index > 1) // don't allow "mount two horses"
        {
            return 0;
        }

        // Try mounting the first horse, then the second etc
        o_list = filter(o_list[1..], &->is_steed());
        for (i = 0; i < sizeof(o_list); i++)
        {
            steed_to_mount = o_list[i];
            break;
        }
        if (!steed_to_mount)
        {
            return 0;
        }
    }
    else              // allow "mount second horse"
    {
        if (!o_list[-index]->is_steed())
        {
            return 0;
        }
        steed_to_mount = o_list[-index];
    }
    sts = steed_to_mount->do_mount(this_player());
    steed_to_mount->handle_mount_status(sts, this_player());
    if (STEED_STS_FAIL(sts))
    {
        notify_fail("");
    }
    return STEED_STS_SUCCESS(sts);
}

/* Function name: unlead
 * Description:   Leave the steed.
 * Arguments:     string: the object description the living wants to leave.
 * Returns:       int success
 */
public int
unlead(string s)
{
    object *o_list;
    object steed;
    int sts;

    if (
        (!s) ||
        (!sizeof(
            o_list =
                FIND_STR_IN_ARR(s, all_inventory(environment(this_player())))))
        )
    {
        return 0;
    }
    if (sizeof(o_list) > 1)
    {
        return 0;
    }
    steed = o_list[0];

    // check if it's a steed
    if (!steed->is_steed())
    {
        return 0;
    }

    sts = steed->do_unlead(this_player(), 1);
    steed->handle_unlead_status(sts, this_player());
    reset_auto_functions();
    if (STEED_STS_FAIL(sts))
    {
        notify_fail("");
    }
    return STEED_STS_SUCCESS(sts);
}

/* Function name: auto_mount
 * Description:   Toggle automatic mount.
 * Returns:       int success
 */
public int
do_auto_mount(string str)
{
    object steed;

    if (stringp(str))
    {
        return 0;
    }

    if (!(steed = this_player()->query_prop(LIVE_O_STEED)))
    {
        return 0;
    }

    set_auto_mount(1 - auto_mount);
    this_player()->catch_tell("Automatic mount is now " +
        (auto_mount ? "on" : "off") + ".\n");
    return 1;
}

/* Function name: auto_dismount
 * Description:   Toggle automatic dismount.
 * Returns:       int success
 */
public int
do_auto_dismount(string str)
{
    object steed;

    if (stringp(str))
    {
        return 0;
    }

    if (!(steed = this_player()->query_prop(LIVE_O_STEED)))
    {
        return 0;
    }

    if (STEED_STS_FAIL(can_lead(this_player())))
    {
        FAIL("You must have the ability to lead this " + short() +
            " to enable automatic dismount.\n");
    }

    auto_dismount = 1 - auto_dismount;
    this_player()->catch_tell("Automatic dismount is now " +
        (auto_dismount ? "on" : "off") + ".\n");
    return 1;
}

void
init_living()
{
    ::init_living();

    if (!IS_LIVING_OBJECT(this_player()))
        return;

    add_action(feed, "feed");
    add_action(lead, "lead");
    add_action(mount, "mount");
}

// --- The rest --------------------------------------------------

// When this horse is destructed, everybody should dismount first
// and the leader should be notified.
public void
remove_object()
{
    dismount_all(1);
    if (objectp(leader))
    {
        do_unlead(leader, 1);
    }
    ::remove_object();
}

/* Function name: idle_time
 * Description:   How long has the horse been not moved?
 * Returns:       int - time in seconds
 */
public int
idle_time()
{
    return time() - last_moved_time;
}

/* Function name:
 * Description:
 * Arguments:
 * Returns:
 */
