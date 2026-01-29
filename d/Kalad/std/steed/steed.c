/*
   steed.c
   
   A standard steed which you can mount and ride around with.
   
   Copyright by Wout de Zeeuw, Fysix@Genesis, March 1997
   Last modified:
      17 Jan 1998
   
 */
#pragma save_binary
#pragma strict_types
 
inherit "/std/creature.c";
inherit "/std/combat/unarmed.c";

#define STEED_PATH "/d/Kalad/std/steed/"
// Standard rider's shadow for riding around
#define STD_STEED_SHADOW STEED_PATH + "steed_sh"
// The feeding module
#define FEEDING STEED_PATH + "feeding"
// The leading shadow
#define LEAD_SHADOW STEED_PATH + "lead_sh"

inherit FEEDING; 

#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <cmdparse.h>
#include "/d/Kalad/std/steed/steed.h"
// Are we running on Genesis?
#include "default.h"

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

static object *Riders = ({ }),
              Leader;               // The living leading this steed
static int    Max_riders,           // Maximum number of riders
              Has_riders,           // Number of riders
              Last_moved_time,      // At what time was steed last moved?
              Mounted_combat,       // Is mounted combat allowed?
              No_trans,       // Is the steed moved when rider is transed?
              // Some rider skills and stats should be
              // redirected to the steed:
              *Redir_skills = ({ });
static string *Valid_dest = ({ }),     // Valid destination when mounted
              *Invalid_dest = ({ }),   // Invalid destiantion when mounted
              *Invalid_unmounted_dest = ({ }),
                              // Invalid dest when not mounted
              Shadow_file;    // The shadow that is loaded when mounting

// --- Prototypes ---------------------------------------------------

public int mounted_combat();
public int idle_time();
public varargs string composite_riders(object for_obj);
public varargs string short_old(object for_obj);

// --- Steed shadow set and query functions -------------------------

/* Function name: set_steed_shadow
 * Description:   Set the file name of the shadow that has
 *                to be loaded when a living mounts the steed.
 * Arguments:     string: the path to your shadow
 */
public void
set_steed_shadow(string s)
{
   Shadow_file = s;
}

/* Function name: query_steed_shadow
 * Description:   Query the file name of the shadow that has
 *                to be loaded when a living mounts the steed.
 * Returns:       string: the path to the shadow
 */
public string
query_steed_shadow(string s)
{
   return Shadow_file;
}

// --- Rider set and query functions --------------------------------

/* Function name: query_has_riders
 * Description:   How many riders does the steed have?
 * Returns:       int
 */
public nomask int
query_has_riders()
{
   return Has_riders;
}

/* Function name: query_driver
 * Description:   Who is driving the horse?
 * Returns:       object - the driver
 */
public nomask object
query_driver()
{
   return (Has_riders ? Riders[0] : 0);
}

/* Function name: query_riders
 * Description:   Who is/are riding the steed?
 * Returns:       object* - an array containing the rider object(s)
 */
public nomask object*
query_riders()
{
   return Riders;
}

/* Function name: add_riders
 * Description:   Add the rider object(s). Adds the prop LIVE_O_STEED
 *                to the rider, the rider shadow and the RIDER_SUBLOC.
 *                Handles notify_fail in case of errors.
 * Arguments:     mixed - the rider object(s)
 * Returns:       (int) 1 if successful, 0 some error occured
 *                (if the steed is full already, illegal rider or shadow).
 */
public nomask int
add_riders(mixed rider_ob)
{
   int i;
   object sh;

   // If steed is full, we can't have another rider
   if (Has_riders >= Max_riders)
      return 0;
   
   if (objectp(rider_ob))
      rider_ob = ({ rider_ob });
   if (!sizeof(rider_ob) || !pointerp(rider_ob))
      return 0;

   // Check if none of the objects is mounted already!
   i = sizeof(rider_ob);
   while (i--)
      if (rider_ob[i]->query_prop(LIVE_O_STEED))
         return 0;

   // Add a prop and a shadow in the rider
   setuid();
   seteuid(getuid());
   i = sizeof(rider_ob);
   while (i--)
   {
      sh = clone_object(Shadow_file);
      // Check if the shadow is a valid steed shadow
      if (!sh->is_steed_shadow())
      {
         sh->remove_object();
         rider_ob->catch_tell("Illegal steed shadow!\n");
      }
      sh->shadow_me(rider_ob[i]);
      sh->set_steed(this_object());

      rider_ob[i]->add_prop(LIVE_O_STEED, this_object());
      rider_ob[i]->add_subloc(RIDER_SUBLOC, this_object(), 0);
   }

   Riders += rider_ob;
   Has_riders = sizeof(Riders);

   return 1;
}

/* Function name: remove_rider
 * Description:   Remove rider. Removes the LIVE_O_STEED property
 *                from the rider and the RIDER_SUBLOC subloc from the
 *                steed. It does not remove the rider shadow!
 * Arguments:     object - the rider object
 * Returns:       (int) 0 if there was no such rider on the steed
 */
public nomask int
remove_rider(object rider_ob)
{
   if (member_array(rider_ob, Riders) < 0)
      return 0;

   Riders -= ({ rider_ob, 0 });
   rider_ob->remove_prop(LIVE_O_STEED);
   rider_ob->remove_subloc(RIDER_SUBLOC);
   Has_riders = sizeof(Riders);

   return 1;
}

/* Function name: set_max_riders
 * Description:   Set the maximum number of people on the steed.
 * Arguments:     int
 */
public nomask void
set_max_riders(int i)
{
   Max_riders = i;
}

/* Function name: query_max_riders
 * Description:   What is the maximum number of people on the steed.
 * Returns:       int
 */
public nomask int
query_max_riders()
{
   return Max_riders;
}

// --- some redefinable message hooks ------------------------------

/* Function name: mount_hook
 * Description:   Give a message when a living mounts the steed.
 *                Called by do_mount when not in silent mode.
 * Arguments:     object the livings who mounts
 */
public void
mount_hook(object o)
{
   o->catch_tell("You mount the " + short_old(o) + ".\n");
   tell_room(environment(this_object()), QCTNAME(o) + " mounts the " +
      short_old() + ".\n", o);
}

/* Function name: dismount_hook
 * Description:   Give a message when a living dismounts the steed.
 *                Called by sh_do_dismount when not in silent mode.
 * Arguments:     object the living who dismounts
 * Returns:       
 */
public void
dismount_hook(object o)
{
   o->catch_tell("You dismount the " + short_old(o) + ".\n");
   tell_room(environment(this_object()), QCTNAME(o) +
      " dismounts the " + short_old() + ".\n", o);
}

/* Function name: is_not_driver_hook
 * Description:   Give a message when one of the riders tries
 *                to move, but he is not the driver of this steed.
 *                Called by query_cannot_move_to in this object.
 * Arguments:     object the living to give the message to
 */
public void
is_not_driver_hook(object o)
{
   o->catch_tell("You cannot go there since you " +
      "are not driving " + query_the_name(o) + ".\n");
}

/* Function name: invalid_dest_hook
 * Description:   Give a message when the steed cannot go somewhere
 *                because check_destination indicated it.
 *                Called by query_cannot_move_to in this object.
 * Arguments:     object the living to give the message to
 *                optional: string where_to, e.g. "board the ship",
 *                   "go north".
 */
public varargs void
invalid_dest_hook(object o, string where_to)
{
   o->catch_tell("Your " + short_old(o) +
      " refuses to " + (strlen(where_to) ? where_to : "go there") +
      ".\n");
}

/* Function name: steed_is_tired_hook
 * Description:   Give a message when the steed is too tired to move.
 *                Called by query_cannot_move_to in this object.
 * Arguments:     object the living to give the message to
 */
public void
steed_is_tired_hook(object o)
{
   o->catch_tell("Your " + short_old(o) +
      " is too tired to go there.\n");
}

/* Function name: lead_hook
 * Description:   Give a message when a player starts leading this steed.
 * Arguments:     object living
 */
public void
lead_hook(object o)
{
   o->catch_tell("You start leading the " + short() + ".\n");
   tell_room(environment(), QCTNAME(o) + " starts leading the " +
      short() + ".\n", o);
}

/* Function name: unlead_hook
 * Description:   Give a message when a player stops leading this steed.
 * Arguments:     object living
 */
public void
unlead_hook(object o)
{
   o->catch_tell("You stop leading the " + short() + ".\n");
   tell_room(environment(), QCTNAME(o) + " stops leading the " +
      short() + ".\n", o);
}

// --- mounting and dismounting ------------------------------------

/* Function name: can_mount
 * Description:   Is the living skilled enough to mount the steed?
 *                Called by do_mount. Replace with your own criteria
 *                if needed. notify_fail isn't used.
 * Arguments:     object - the living object
 * Returns:       int - true if succeeds
 */
public int
can_mount(object o)
{
   if (o->query_skill(SS_ANI_HANDL) < 20)
   {
      o->catch_tell("You are not skilled enough to handle this " +
         short(o) + ".\n");
      return 0;
   }

   return 1;
}

/* Function name: check_combat
 * Description:   Does this steed support mounted combat?
 *                If not, is the living or the steed not in combat?
 *                Called by do_mount. notify_fail isn't used.
 * Arguments:     object - the living object
 * Returns:       int - true if combat is no objection for mounting.
 */
public int
check_combat(object o)
{
   if (mounted_combat())
      return 1;

   if (objectp(o->query_attack()))
   {
      o->catch_tell("You are too busy fighting to mount the " +
         short(o) + ".\n");
      return 0;
   }

   if (objectp(query_attack()))
   {
      o->catch_tell("The " + short(o) + " is occupied in combat and " +
         "it is too difficult too mount.\n");
      return 0;
   }

   return 1;
}

/* Function name: do_mount
 * Description:   Let a living mount, calls can_mount and check_combat
 *                to see if it is possible to mount.
 * Arguments:     object - the living object
 *                int - if true: silent mode, don't tell the environment
 *                   if the living mounts.
 *                               (0 default)
 * Returns:       0 - action failed and might be tried in another steed
 *                1 - syntax was ok but might not necessarily mount
 */
public varargs int
do_mount(object o, int silent = 0)
{
object sh;

   if (environment() != environment(o))
      return 0;

   if (objectp(Leader))
      FAIL("You cannot mount the " + short() +
      " while someone is leading it.\n");

   if (Has_riders >= Max_riders)
      FAIL("The " + short_old(o) + " already carries a rider.\n");

   if (member_array(o, Riders) >= 0)
   {
      o->catch_tell("You are already riding the " + short(o) + ".\n");
      return 1;
   }

   if (o->query_prop(LIVE_O_STEED))
   {
      o->catch_tell("You are already mounted.\n");
      return 1;
   }

   // Can the living mount?
   if (!can_mount(o))
      return 1;

   // Is either the living or the steed in combat?
   if (!check_combat(o))
      return 1;

   // Try to add the rider (should always succeed now)
   if (!add_riders(o))
      return 1;

   if (!silent)
      mount_hook(o);

   // Reveal the living when hidden, always tell him he's revealed
   o->reveal_me(1);

   return 1;
}

/* Function name: can_dismount
 * Description:   Can the living dismount? Might be useful to prevent
 *                dismount on certain locations (e.g. while flying).
 *                Called by sh_do_dismount. Replace with your own criteria
 *                if needed.
 * Arguments:     object - the living object
 * Returns:       int - true if succeeds
 */
public int
can_dismount(object o)
{
   return 1;
}

/* Function name: sh_do_dismount
 * Description:   Let a living dismount, but don't remove the shadow.
 *                This function usually lets a rider dismount, forced
 *                by the shadow itself (hence we don't want it removed).
 *                Called by do_dismount or the rider's shadow.
 *                Calls can_dismount to see if the rider can dismount.
 * Arguments:     object - the living object
 *                int - if true: silent mode, don't tell the environment.
 *                               (default 0)
 *                int - force dismount, ignoring can_dismount. (default 0)
 * Returns:       1 - if successful, 0 - fail
 */
public varargs int
sh_do_dismount(object o, int silent = 0, int force = 0)
{
   // Is the living a rider of this steed?
   if (member_array(o, Riders) < 0)
      return 0;

   // Can the rider dismount? If forced, living can always dismount
   if (!force && !can_dismount(o))
      return 0;

   remove_rider(o);

   if (!silent)
      dismount_hook(o);

   return 1;
}

/* Function name: do_dismount
 * Description:   Let a living dismount, and remove the shadow.
 * Arguments:     object - the living object
 *                int - if silent don't tell the environment (default 0)
 * Returns:       0 - failed to dismount, 1 - successful
 */
public varargs int
do_dismount(object rider_ob, int silent = 0, int force = 0)
{
   if (!sh_do_dismount(rider_ob, silent, force))
      return 0;

   rider_ob->remove_steed_shadow();
   return 1;
}

/* Function name: dismount_all
 * Description:   Dismount all riders.
 * Arguments:     int silent: 1 silent dismount (0 by default)
 *                int force: 1 force the riders, ignoring can_dismount
 *                 (0 by default).
 */
public varargs void
dismount_all(int silent = 0, int force = 0)
{
   map(Riders, &do_dismount(, silent, force));
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
   return Valid_dest;
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
      t = ({ t });
   if (pointerp(t))   
      Valid_dest = t;
}

// see set_valid_dest
public void
add_valid_dest(mixed t)
{
   if (stringp(t))
      t = ({ t });
   if (pointerp(t))
      Valid_dest += t;
}

/* Function name: query_invalid_dest
 * Description:   Returns an array of properties that indicate invalid
 *                destination rooms when the steed has riders.
 * Returns:       string *
 */
public string*
query_invalid_dest()
{
   return Invalid_dest;
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
      t = ({ t });
   if (pointerp(t))   
      Invalid_dest = t;
}

// see set_invalid_dest
public void
add_invalid_dest(mixed t)
{
   if (stringp(t))
      t = ({ t });
   if (pointerp(t))
      Invalid_dest += t;
}

/* Function name: query_invalid_unmounted_dest
 * Description:   Returns an array of properties that indicate invalid
 *                destination rooms when the steed has no riders.
 * Returns:       string *
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
      t = ({ t });
   if (pointerp(t))   
      Invalid_unmounted_dest = t;
}

// see set_invalid_unmounted_dest
public void
add_invalid_unmounted_dest(mixed t)
{
   if (stringp(t))
      t = ({ t });
   if (pointerp(t))
      Invalid_unmounted_dest += t;
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
 * Returns:       int - true if destination is OK
 */
public int
check_mounted_destination(object to_dest)
{
int i;

   // Check for valid destination first
   i = sizeof(Valid_dest);
   while (i--)
      if (to_dest->query_prop(Valid_dest[i]))
         return 1;

   // Check for invalid destination
   i = sizeof(Invalid_dest);
   while (i--)
      if (to_dest->query_prop(Invalid_dest[i]))
         return 0;
   
   return 1;
}

// Similar to check_mounted_destination,
// but now for the case when no livings are mounted
public int
check_unmounted_destination(object to_dest)
{
int i;

   // Check for invalid destination
   i = sizeof(Invalid_unmounted_dest);
   while (i--)
      if (to_dest->query_prop(Invalid_unmounted_dest[i]))
         return 0;
   
   return 1;
}

/* Function name: check_destination
 * Description:   Check the destination where the steed wants to move
 *                to. Usually called by the driver's shadow.
 *                Calls check_mounted_destination or 
 *                check_unmounted_destination depending on if
 *                the steed has riders.
 * Arguments:     mixed destination object/file name
 * Returns:       int 1 if the steed can go there
 */
public int
check_destination(mixed to_dest)
{
   // Check if destination loads, and if it loads, check
   // if the steed can enter... if not, abort
   if (!stringp(LOAD_ERR(to_dest)))
      if (!objectp(to_dest))
         to_dest = find_object(to_dest);

   return (Has_riders ?
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
   return Redir_skills;
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
      t = ({ t });
   if (pointerp(t))   
      Redir_skills = t;
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
   Mounted_combat = t;
}

/* Function name: mounted_combat
 * Description:   Is mounted combat allowed on this steed object?
 * Returns:       int 0 - false, 1 - true
 */
public int
mounted_combat()
{
   return Mounted_combat;
}

// Checks mounted_combat(), if no mounted combat allowed,
// when steed is attacked, dismount all riders.
public void
attacked_by(object o)
{
   if (!mounted_combat())  // dismount if mounted combat is not allowed
      dismount_all();
   else if (member_array(o, Riders) >= 0) // dismount if rider attacks me
      do_dismount(o);
   
   ::attacked_by(o);
}

// dismount all when horse dies
public void
do_die(object killer)
{
   if (query_hp() > 0)
      return;

   dismount_all(0, 1);
   ::do_die(killer);
}

// --- Move functions ------------------------------------------------

// give message, called by query_cannot_move_to below
public void
give_msg(function msg_function, string where_to)
{
   if (where_to == "M")
      return;
   msg_function();
}

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
   if (Riders[0] != living)
   {
      give_msg(&is_not_driver_hook(living), where_to);
      return 9;
   }

   // Check if the steed is tired
   if (!query_fatigue())
   {
      give_msg(&steed_is_tired_hook(living), where_to);
      return 10;
   }

   // Check if the steed can go there
   if (!check_destination(destination))
   {
      give_msg(&invalid_dest_hook(living, strlen(where_to) ?
         where_to : "go there"), where_to);
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
   steed_how = Has_riders ? "M" : how;

   // Check the destination
   if (!check_destination(to_dest))
      return 8;

   r = ::move_living(steed_how, to_dest, dont_follow, no_glance);

   if (!r)
      Last_moved_time = time();

   // Steed has run off by itself (e.g. panic) or 
   // is led somewhere by the lead shadow.
   // Let all riders follow automatically by calling the old move_living
   // function (saves some overhead that's in the shadowed move_living fun).
   Riders->move_living_old(how, to_dest, 1, 0);

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
      Last_moved_time = time();

   // Let the co-riders move too, call original move_living function
   // in the riders (saves some overhead that's in the
   // shadowed move_living)
   Riders[1..]->move_living_old(how, to_dest, 1, 0);
   return r;
}

// Make the original move_living function accessible
public varargs int
move_living_old(string how, mixed to_dest, int dont_follow, int no_glance)
{
   return ::move_living(how, to_dest, dont_follow, no_glance);
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
   No_trans = (i ? 1 : 0);
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
   return No_trans;
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
    
    // Give the steed proper hitlocs and attacks
    configure_steed();
   
    // Set some standard values
    set_valid_dest(({ ROOM_I_ALLOW_STEED }));
    set_invalid_dest(({ ROOM_I_NO_ALLOW_STEED, ROOM_I_INSIDE }));
    set_invalid_unmounted_dest(({ ROOM_I_NO_ALLOW_STEED }));
    set_redir_skills(({ SS_CLIMB, SS_SWIM, SS_SNEAK, SS_HIDE }));
    Last_moved_time = time();
    
    // Add a subloc to this steed to show riders if present
    add_subloc(STEED_SUBLOC, this_object(), 0);
   
    set_steed_shadow(STD_STEED_SHADOW); // set the standard steed shadow
    set_max_riders(1);        // 1 rider maximum
    allow_mounted_combat(0);  // don't allow mounted combat
    set_no_trans(1);          // dismount when rider is transed
    
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
         "You are riding a " + short_old(for_obj) + ".\n" :
         capitalize(HE(on)) + " is riding a " + short_old(for_obj) + ".\n");
   }
   else if (subloc == STEED_SUBLOC)  // Extra description for steed
   {
      if (!Has_riders)
         return ""; // Sanity check, no description to give

      verb = (Has_riders == 1 && for_obj != Riders[0] ? "is" : "are");
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
   return Has_riders ?
      COMPOSITE_WORDS(map(Riders, &rider_name(, for_obj))) :
      "nobody";
}

// Still make the old short function available
public varargs string
short_old(object for_obj)
{
   return ::short(for_obj);
}

// adjusted short desc showing everybody on the steed
public varargs string
short(object for_obj)
{
   // If no riders return the original short desc
   if (!Has_riders)
      return short_old(for_obj);

   if (!objectp(for_obj))
      for_obj = this_player();

   return short_old(for_obj) + " with " + composite_riders(for_obj) +
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
   return "arrives riding on " + LANG_ADDART(short_old()) + ".";
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
   return "rides " + rider->query_possessive() +
      " " + short_old();
}

// --- leading functions ---------------------------------------------------

/* Function name: query_leader
 * Description:   Who leads this steed?
 * Returns:       object
 */
public object
query_leader()
{
   return Leader;
}

/* Function name: can_lead
 * Description:   Hook to see if the living can lead this steed.
 *                notify_fail is not used.
 * Arguments:     object living
 * Returns:       int 1 if the living is allowed to lead this steed
 */
public int
can_lead(object living)
{
   living->catch_tell("What?\n");
   return 0;
}

/* Function name: do_lead
 * Description:   Let a living lead this steed.
 * Arguments:     object: the leader to be
 * Returns:       int success
 */
public int
do_lead(object o)
{
   object shadow;

   if (!can_lead(o))
      return 1;

   Leader = o;
   // See if the living is already leading another horse
   if (!Leader->query_leading_steed())
   {
      shadow = clone_object(LEAD_SHADOW);
      shadow->shadow_me(Leader);
   }

   Leader->add_steed_follow(this_object());

   // Give message that living starts leading the steed
   lead_hook(Leader);
   return 1;
}

/* Function name: do_unlead
 * Description:   Let the leader of this steed not lead it anymore.
 * Arguments:     object the supposed to be leader, if not the right
 *                       leader is passed, the function fails.
 *                int - optional: notify the leader's shadow that the leader
 *                   is no longer leading the steed.
 * Returns:       int success
 */
public varargs int
do_unlead(object o, int notify_shadow = 0)
{
   if (Leader != o)
      return 0;
   if (notify_shadow)
      Leader->remove_steed_follow(this_object());
      
   // Give message that living stops leading the steed.
   unlead_hook(Leader);
   Leader = 0;
   return 1;
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

   if (stringp(str))
      return 0;

   if (!(steed = this_player()->query_prop(LIVE_O_STEED)))
      FAIL("But you are not mounted on anything.\n");

   return steed->do_dismount(this_player());
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

   if (!s || !sizeof(o_list = 
      FIND_STR_IN_ARR(s, all_inventory(environment(this_player())))))
      return 0;
   if (sizeof(o_list) > 1)
      return 0;
   steed = o_list[0];

   // check if it's a steed
   if (!steed->is_steed())
      return 0;

   // check if we have a leader already
   if (objectp(steed->query_leader()))
      FAIL("The " + steed->short() + " is already lead by someone.\n");

   // Don't allow leading when living is riding a steed
   if (objectp(this_player()->query_prop(LIVE_O_STEED)))
      FAIL("You cannot lead a " + steed->query_race_name() +
      " while riding.\n");

   // Don't allow to lead steeds with riders on them
   if (steed->query_has_riders())
      FAIL("You cannot lead a " + steed->query_race_name() +
      " with riders on " + steed->query_objective() + ".\n");
   
   return steed->do_lead(this_player());
}

/* Function name: mount
 * Description:   Try to mount a steed, does a syntax check and a check
 *                if the object is a steed (using the is_steed() function)
 *                and then calls do_mount in the steed object
 * Arguments:     string - the object description
 * Returns:       1 - if successful
 */
public nomask int
mount(string s)
{
   mixed  *o_list;
   int    i, index;

   if (CAN_SEE_IN_ROOM(this_player()) <= 0)
       return light_fail("mount");

   if (this_player()->query_prop(LIVE_O_STEED))
      FAIL("You are already mounted.\n");

   if (!s || !parse_command(s, all_inventory(environment(this_player())),
      "%l", o_list))
      return 0;

   index = o_list[0];

   if (index == 0)   // don't allow "mount all horses" or "mount horses"
      return 0;
   if (index > 0)    // allow "mount horse"
   {
      if (index > 1) // don't allow "mount two horses"
         return 0;

      // Try mounting the first horse, then the second etc
      o_list = filter(o_list[1..], &->is_steed());
      for (i = 0; i < sizeof(o_list); i++)
         if (o_list[i]->do_mount(this_player()))
            return 1;
      return 0;
   }
   else              // allow "mount second horse"
   {
      if (!o_list[-index]->is_steed())
         return 0;
      return o_list[-index]->do_mount(this_player());
   }
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

   if (!s || !sizeof(o_list = 
      FIND_STR_IN_ARR(s, all_inventory(environment(this_player())))))
      return 0;
   if (sizeof(o_list) > 1)
      return 0;
   steed = o_list[0];

   // check if it's a steed
   if (!steed->is_steed())
      return 0;

   return steed->do_unlead(this_player(), 1);
}

void
init_living()
{
   ::init_living();
   add_action(dismount, "dismount");
   add_action(feed, "feed");
   add_action(lead, "lead");
   add_action(unlead, "leave");  // put this in a lead object later
   add_action(mount, "mount");
}

// --- The rest --------------------------------------------------

// When this horse is destructed, everybody should dismount first
// and the leader should be notified.
public void
remove_object()
{
   dismount_all(0, 1);
   if (objectp(Leader))
      do_unlead(Leader, 1);
   ::remove_object();
}

/* Function name: idle_time
 * Description:   How long has the horse been not moved?
 * Returns:       int - time in seconds
 */
public int
idle_time()
{
   return time() - Last_moved_time;
}
