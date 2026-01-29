/*

   /d/Gondor/std/steed.c
   
   A standard steed which you can mount and ride around with.
   About the use of this steed, read tut.txt
   
   Copyright by Wout de Zeeuw, Fysix@Genesis, March 1997
   Last modified:
      7 Oct 1997
   
 */
#pragma save_binary
#pragma strict_types
 
inherit "/std/creature.c";
inherit "/std/combat/unarmed.c";

#define STEED_PATH "/d/Gondor/std/steed/"
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
#include "/d/Gondor/std/steed/steed.h"
// Are we running on Genesis?
#include "default.h"

// Some macros
#define FAIL(x) { notify_fail(x); return 0; }
#define NF(x) notify_fail(x)
#define TP this_player()
#define HE(x) (x)->query_pronoun()
#define PREV_LIGHT CAN_SEE_IN_ROOM(this_player()) 

// Rider's subloc for showing he's riding a steed
#define RIDER_SUBLOC "_steed"
// Steed's subloc for showing someone is riding it
#define STEED_SUBLOC "_riders"
 
// --- Global variables ---------------------------------------------

static object *Riders = ({ }),
              Leader;               // The living leading this steed
static int    Max_riders,           // Maximum number of riders
              Has_riders,           // Do I have riders? (used by move_living)
              Last_moved_time,      // At what time was steed last moved?
              Mounted_combat,       // Is mounted combat allowed?
              // Some rider skills and stats should be
              // redirected to the steed
              *Redir_skills = ({ });
//              *Redir_stats  = ({ });
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
 * Description:   Set the shadow that has to be loaded when a player
 *                mounts the steed.
 * Arguments:     string: the path to your shadow
 */
public void
set_steed_shadow(string s)
{
   Shadow_file = s;
}

/* Function name: query_steed_shadow
 * Description:   Query the shadow that has to be loaded when a player
 *                mounts the steed.
 * Returns:       string: the path to the shadow
 */
public string
query_steed_shadow(string s)
{
   return Shadow_file;
}

// --- Rider set and query functions --------------------------------

/* Function name: query_driver
 * Description:   Who is driving the horse?
 * Returns:       object - the driver
 */
public nomask object
query_driver()
{
   if (!sizeof(Riders))
      return 0;
   return Riders[0];
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
 * Returns:       (int) 1 if succesful, 0 some error occured
 *                (if the steed is full already, illegal rider or shadow).
 */
public nomask int
add_riders(mixed rider_ob)
{
   int i;
   object sh;

   // If steed is full, we can't have another rider
   if (sizeof(Riders) >= Max_riders)
      FAIL("The " + short() + " already has a rider.\n");
   
   if (objectp(rider_ob))
      rider_ob = ({ rider_ob });
   if (!sizeof(rider_ob) || !pointerp(rider_ob))
      return 0;

   // Check if none of the objects is mounted already!
   i = sizeof(rider_ob);
   while (i--)
      if (rider_ob[i]->query_prop(LIVE_O_STEED))
         FAIL("You are already mounted.\n");

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
         FAIL("Illegal steed shadow.\n");
      }
      sh->shadow_me(rider_ob[i]);
      sh->set_steed(this_object());

      rider_ob[i]->add_prop(LIVE_O_STEED, this_object());
      rider_ob[i]->add_subloc(RIDER_SUBLOC, this_object(), 0);
   }

   Riders += rider_ob;
   if (sizeof(Riders))
      Has_riders = 1;

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

   Riders -= ({ rider_ob });
   rider_ob->remove_prop(LIVE_O_STEED);
   rider_ob->remove_subloc(RIDER_SUBLOC);
   if (!sizeof(Riders))
      Has_riders = 0;

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

// --- mounting and dismounting ------------------------------------

/* Function name: can_mount
 * Description:   Is the player skilled enough to mount the steed?
 *                Called by do_mount. Replace with your own criteria
 *                if needed. notify_fail isn't used.
 * Arguments:     object - the player object
 * Returns:       int - true if succeeds
 */
public int
can_mount(object o)
{
   if (o->query_skill(SS_ANI_HANDL) < 20)
   {
      o->catch_tell("You are not skilled enough to handle this " + short(o) +
       ".\n");
      return 0;
   }
   
   return 1;
}

/* Function name: check_combat
 * Description:   Does this steed support mounted combat?
 *                If not, is the player or the steed not in combat?
 *                Called by do_mount. notify_fail isn't used.
 * Arguments:     object - the player object
 * Returns:       int - true if combat is no objection for mounting.
 */
public int
check_combat(object o)
{
   if (mounted_combat())
      return 1;

   if (objectp(o->query_attack()))
   {
      o->catch_tell("You are too busy fighting to mount the " + short(o) +
       ".\n");
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
 * Description:   Let a player mount, calls can_mount and check_combat
 *                to see if it is possible to mount.
 * Arguments:     object - the player object
 *                int - if true: silent mode, don't tell the environment
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

   if (sizeof(Riders) >= Max_riders)
      FAIL("The " + short() + " already carries a rider.\n");

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

   // Can the player mount?
   if (!can_mount(o))
      return 1;

   // Is either the player or the steed in combat?
   if (!check_combat(o))
      return 1;

   // Try to add the rider (should always succeed now)
   if (!add_riders(o))
      return 1;

   if (!silent)
   {
      o->catch_msg("You mount the " + short_old(o) + ".\n");
      tell_room(environment(this_object()), QCTNAME(o) + " mounts the " +
       short_old() + ".\n", o);
   }

   // Reveal the player when hidden, always tell him he's revealed
   o->reveal_me(1);

   return 1;
}

/* Function name: can_dismount
 * Description:   Can the player dismount? Might be useful to prevent
 *                dismount on certain locations (e.g. while flying).
 *                Called by sh_do_dismount. Replace with your own criteria
 *                if needed.
 * Arguments:     object - the player object
 * Returns:       int - true if succeeds
 */
public int
can_dismount(object o)
{
   return 1;
}

/* Function name: sh_do_dismount
 * Description:   Let a player dismount, but don't remove the shadow.
 *                This function usually lets a rider dismount, forced
 *                by the shadow itself (hence we don't want it removed).
 *                Called by do_dismount or the rider's shadow.
 *                Calls can_dismount to see if the rider can dismount.
 * Arguments:     object - the player object
 *                int - if true: silent mode, don't tell the environment.
 *                               (default 0)
 *                int - force dismount, ignoring can_dismount. (default 0)
 * Returns:       1 - if successful, 0 - fail
 */
public varargs int
sh_do_dismount(object o, int silent = 0, int force = 0)
{
   // Is the player a rider of this steed?
   if (member_array(o, Riders) < 0)
      return 0;

   // Can the rider dismount? If forced, player can always dismount
   if (!force && !can_dismount(o))
      return 0;

   remove_rider(o);

   if (!silent)
   {
      o->catch_msg("You dismount the " + short_old(o) + ".\n");
      tell_room(environment(this_object()), QCTNAME(o) +
       " dismounts the " + short_old() + ".\n", o);
   }
   return 1;
}

/* Function name: do_dismount
 * Description:   Let a player dismount, and remove the shadow.
 * Arguments:     object - the player object
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

/* Function name: check_destination
 * Description:   Checks if the destination is a valid one for the steed.
 *                (e.g. don't enter small houses etc.) is used only when
 *                riding the steed.
 *                Properties as given by query_valid_dest() are
 *                seen as valid destinations.
 *                Properties as given by query_invalid_dest() are
 *                seen as invalid destinations. Valid destinations have
 *                a higher priority.
 * Arguments:     mixed - the destination object / file
 * Returns:       int - true if destination is OK
 */
public int
check_destination(mixed to_dest)
{
int i;

   // Check if destination loads, and if it loads, check
   // if the steed can enter... if not, abort
   if (!stringp(LOAD_ERR(to_dest)))
      if (!objectp(to_dest))
         to_dest = find_object(to_dest);

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

// Similar to check_destination, but then for the case when no players
// are mounted
public int
check_unmounted_destination(mixed to_dest)
{
int i;

   // Check if destination loads, and if it loads, check
   // if the steed can enter... if not, abort
   if (!stringp(LOAD_ERR(to_dest)))
      if (!objectp(to_dest))
         to_dest = find_object(to_dest);

   // Check for invalid destination
   i = sizeof(Invalid_unmounted_dest);
   while (i--)
      if (to_dest->query_prop(Invalid_unmounted_dest[i]))
         return 0;
   
   return 1;
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
int i;

   if (!mounted_combat())  // dismount if mounted combat is not allowed
   {
      dismount_all();
      ::attacked_by(o);
      return;
   }
   
   if (member_array(o, Riders) >= 0)   // dismount if rider attacks me
   {
      do_dismount(o);
      ::attacked_by(o);
      return;
   }
}

// dismount all when horse dies
public void
do_die(object killer)
{
   if (query_hp() > 0 || query_wiz_level() || query_ghost())
      return;

   dismount_all();
   ::do_die(killer);
}

// --- Move functions ------------------------------------------------

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

   // If has riders don't show move
   steed_how = Has_riders ? "M" : how;

   // Check the destination
   if (Has_riders)
   {
      if (!check_destination(to_dest))
         return 8;
   }
   else
      if (!check_unmounted_destination(to_dest))
         return 8;

   r = ::move_living(steed_how, to_dest, dont_follow, no_glance);

   if (!r)
      Last_moved_time = time();

   // Steed has run off by itself (e.g. panic),
   // Let all riders follow automatically by calling the old move_living
   // function (saves some overhead that's in the shadowed move_living fun).
   if (sizeof(Riders))
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
    set_race_name("horse");

    // Some standard properties of the steed
    set_gender(0);
#ifdef GENESIS
    add_prop(LIVE_I_NO_FOOTPRINTS, 1);
#endif
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_HEIGHT, 200);
    
    // Give the steed proper hitlocs and attacks
    configure_steed();
   
    // Set some standard values for global variables
    set_valid_dest(({ ROOM_I_ALLOW_STEED }));
    set_invalid_dest(({ ROOM_I_NO_ALLOW_STEED, ROOM_I_INSIDE }));
    set_invalid_unmounted_dest(({ ROOM_I_NO_ALLOW_STEED }));
    set_redir_skills(({ SS_CLIMB, SS_SWIM, SS_SNEAK, SS_HIDE }));
    Last_moved_time = time();
    
    // Add subloc to this steed to show riders if present
    add_subloc(STEED_SUBLOC, this_object(), 0);
   
    set_steed_shadow(STD_STEED_SHADOW); // set the standard steed shadow
    set_max_riders(1);         // 1 rider maximum
    allow_mounted_combat(0);   // don't allow mounted combat
    
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
// * RIDER_SUBLOC: the extra description of the rider object
// * STEED_SUBLOC: the extra description of this steed object
public string
show_subloc(string subloc, object on, object for_obj)
{
   int s;
   string objective, verb;

   if (subloc == RIDER_SUBLOC)  // Extra description for rider
   {
      if (on == for_obj)
         return "You are riding a " + short_old(for_obj) + ".\n";
      return capitalize(HE(on)) + " is riding a " + short_old(for_obj) + ".\n";
   }
   else if (subloc == STEED_SUBLOC)  // Extra description for steed
   {
      s = sizeof(Riders);
      if (!s)
         return ""; // Sanity check, no description to give

      if (s == 1)
      {
         if (for_obj == Riders[0])
            verb = "are";
         else
           verb = "is";
      }
      else
         verb = "are";

      if (on == for_obj)
         objective = "you"; // very unlikely
      else
         objective = query_objective();

      return capitalize(composite_riders(for_obj)) + " " +
         verb + " riding on " + objective + ".\n";
   }

   return "";
}

// Function to return name of a rider
public string
rider_name(object o, object for_obj)
{
   if (for_obj == o)
      return "you";
   return o->query_art_name(for_obj);
}

// Function to describe all riders
public varargs string
composite_riders(object for_obj)
{
   string r = "";
   int  i, s = sizeof(Riders);

   if (!s)
      return "nobody";

   for (i = 0; i < s - 1; i++)
      r += rider_name(Riders[i], for_obj) + ", ";
   if (s > 1)
      r += "and ";
   r += rider_name(Riders[s - 1], for_obj);
   return r;
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
   int s = sizeof(Riders);

   // If no riders return the original short desc
   if (!s)
      return short_old(for_obj);

   if (!objectp(for_obj))
      for_obj = this_player();

   // write description for one of the riders, or one of the others?
   if (s && member_array(for_obj, Riders) >= 0)
      return short_old(for_obj) + " with " + composite_riders(for_obj) +
       " riding on " + query_objective();

   // description for a non-rider
   return short_old(for_obj) + " with " + composite_riders(for_obj) +
      " riding on " + query_objective();
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
 * Description:   Hook to see if the player can lead this steed. Don't
 *                use notify_fail here, but give your error messages directly
 *                when redefining this function.
 * Arguments:     object player
 * Returns:       int 1 if the player is allowed to lead this steed
 */
public int
can_lead(object player)
{
   player->catch_tell("What?\n");
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
   // See if the player is already leading another horse
   if (!Leader->query_leading_steed())
   {
      shadow = clone_object(LEAD_SHADOW);
      shadow->shadow_me(Leader);
   }
   Leader->add_steed_follow(this_object());
   Leader->catch_tell("You start leading the " + short() + ".\n");
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
   Leader->catch_tell("You stop leading the " + short() + ".\n");
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

   // Don't allow leading when player is riding a steed
   if (objectp(this_player()->query_prop(LIVE_O_STEED)))
      FAIL("You cannot lead a " + steed->query_race() +
      " while riding.\n");

   // Don't allow to lead steeds with player on them
   if (sizeof(steed->query_riders()))
      FAIL("You cannot lead a " + steed->query_race() +
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

   if (PREV_LIGHT <= 0)
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
      for (i = 1; i < sizeof(o_list); i++)
      {
         if (!o_list[i]->is_steed())
            return 0;
         if (o_list[i]->do_mount(this_player()))
            return 1;
      }
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
 * Arguments:     string: the object description the player wants to leave.
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
      Leader->remove_steed_follow(this_object());
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
