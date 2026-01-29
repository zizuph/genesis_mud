/*
   steed_sh.c

   Rider's shadow for riding steed.c around.

   Copyright by Wout de Zeeuw, Fysix@Genesis, May 1997
   Last modified:
      15 Dec 1997

 */

#pragma save_binary
#pragma strict_types

inherit "/std/shadow";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "default.h"

// --- Global variables ---

static object Steed;
static string M_in, M_out, // New arrive and leave messages
              In_move;     // Direction we are moving to

// --- Prototypes ---
public void restore_rider();
public void remove_steed_shadow();

// --- Functions ------------------------------------------------------

/* Function name: set_steed
 * Description:   Has to be called to initialize this shadow.
 *                Notify the steed object to the steed shadow of the rider.
 *                Also sets the rider's in / out messages to
 *                the values query_rider_m_in() and query_rider_m_out()
 *                as given by the steed object.
 * Arguments:     object - the steed object
 */
public void
set_steed(object o)
{
   Steed = o;

   // Don't show the rider, the desc is incorporated in the steed
   shadow_who->set_no_show_composite(1);

   // Set the new messages
   M_in = Steed->query_rider_m_in(shadow_who);
   M_out = Steed->query_rider_m_out(shadow_who);
   
   // Need this for loading the log object
   setuid();
   seteuid(getuid());
}

// What is the steed object the shadowee is riding?
public object
query_steed()
{
   return Steed;
}

// Is this a genuine steed shadow? Used by the steed to discern
// valid steed shadows.
public nomask int
is_steed_shadow()
{
   return 1;
}

// Redefine the arrive message
public string
query_m_in()
{
   return M_in;
}

// Redefine the leave message
public string
query_m_out()
{
   return M_out;
}

// --- Move functions ------------------------------------------------

/* Function name: st_check_team
 * Description:   Check that the team to be moved is where the rider 
 *                is and doesn't contain any co-riders on any steed.
 *                (they are already moved by the steed).
 * Arguments:     ob - The team object to check.
 * Returns:       Result of check. 1/0.
 */
nomask int
st_check_team(object ob)
{
object tmp_steed;

   return (environment(ob) == environment(shadow_who) && 
      shadow_who->check_seen(ob) &&
      !(objectp(tmp_steed = ob->query_prop(LIVE_O_STEED)) &&
      tmp_steed->query_driver() != ob));
}

/* Function name: st_move_team
 * Description:   Move a member of a team in one direction.
 * Arguments:     ob - A teammember to move.
 *                com - The command the leader gave
 * Returns:       Success of move.
 */
nomask int
st_move_team(object ob, string com)
{
   if (!In_move)
      return 0;

   set_this_player(ob);
   // Can't use follow_leader because it has to be called
   // from the leader object in Genesis.
   ob->command("$" + com);
   return 1;
}

/* Function name: follow_leader
 * Description:   Follow the leader, except when I'm not driving the steed.
 * Arguments:     string how,
 *                (Not Genesis) object leader
 * Returns:       (Not Genesis)
 *                int 0 if not called by team leader or if I'm not driving.
 *                int 1 or 0 if the command succeeds
 */
#ifdef GENESIS
public void
follow_leader(string how)
{
   if (shadow_who != Steed->query_driver())
      return; // Can't follow, I'm not driving

   set_this_player(shadow_who);
   shadow_who->command("$" + how);
}
#else
public int
follow_leader(string how, object leader)
{
   if (shadow_who != Steed->query_driver())
      return 0; // Can't follow, I'm not driving

   return shadow_who->follow_leader(how, leader);
}
#endif

/* Function name: move_living
 * Description:   Shadow the rider's move_living function in order to 
 *   co-move the steed. Functions moves the rider, then the steed,
 *   then the co-riders, and last the rest of the team.
 *   When you want to call the original move_living 
 *   without bothering about the steed, call move_living_old in the player. 
 *   You should do sanity checks yourself then though!
 * Returns: 8 if the steed cannot go there
 *          9 if the rider is not the driver
 *          10 the steed is too tired to move
 */
public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
int      r;
object   *team, env;
string   vb, com;

   // See if the steed could go to the destination
   r = Steed->query_cannot_move_to(shadow_who, to_dest);

   // Check if teleported
   if (how == "X")
   {
      // If steed won't be transed or has multiple riders, dismount
      if (Steed->query_no_trans() ||
         sizeof(Steed->query_riders()) > 1 || r)
      {
         Steed->sh_do_dismount(shadow_who, 0, 1);
         r = shadow_who->move_living(how, to_dest, dont_follow, no_glance);
         remove_steed_shadow();

         return r;   // This point won't be reached
      }
      else  // else move horsie along, but not the team
      {
         dont_follow = 1;
      }
   }
   // Player is not teleported, look if steed can move to destination
   else if (r)
      return r;

   // find the team before anything is moved
   team = shadow_who->query_team();
   if (team && !dont_follow)
   {
      env = environment(shadow_who);
      vb = query_verb();
      team = filter(team, st_check_team);
   }

   // Move the shadow_who, don't let team follow yet
   r = shadow_who->move_living(how, to_dest, 1, no_glance);

   // If shadow_who is moved OK, move the steed (and team) as well
   if (!r)
   {
      Steed->add_prop(ROOM_S_DIR, ({how, "horse"}));
      Steed->drive_steed(how, to_dest, 1, 1);

      if (!dont_follow && sizeof(team))
      {
         // Command for the followers if this is the leader
         if (!strlen(vb))
         {
            com = (sizeof(explode(how, " ")) == 1 ? how : "");
         }
         else  // check for "board ship", "enter portal" etc.
         {
            com = env->query_dircmd();
            com = (com ? vb + " " + com : vb);
         }
         
         In_move = how;
         map(team, &st_move_team(, com));
      }
   }
   
   In_move = 0;

   // Check if shadow_who and steed ended up in the same room
   if (environment(shadow_who) != environment(Steed))
   {
      Steed->sh_do_dismount(shadow_who, 0, 1);
      remove_steed_shadow();  // No code will be executed after this statement
   }

   return r;
}

/* Function name: move_living_old
 * Description:   Calls original move_living function, is called by
 *                the steed to make its riders follow it. Might give
 *                unexpected results when not used correctly. Should probably
 *                never be called by any other object than the steed.
 * Arguments:     see move_living
 * Returns:       see move_living
 */
public varargs int
move_living_old(string how, mixed to_dest, int dont_follow, int no_glance)
{
   return shadow_who->move_living(how, to_dest, dont_follow, no_glance);
}

// --- Redirection functions ---------------------------------------

/* Function name: dont_redirect
 * Description:   Call function in the rider, or in the steed?
 *                used for bypassing redirecting skills
 *                when the player skills himself when on the steed.
 * Arguments:     object - the calling object
 * Returns:       (int) 1 - do not redirect the function
 */
public int
dont_redirect(object caller)
{
   // if case of a "skillstat" or "skills" command
   // redirection of skills is not allowed!
   // No need to take (adventurer) guilds into account since they
   // use query_base_skill which is unshadowable.
   return (query_verb() == "skills" || query_verb() == "skillstat");
}

// Movement skills should be redirected to the steed when mounted only
// during movement.
// Makes use of the query_redir_skills function in the steed.
// Use query_base_skill to find out the real player skills.
public int
query_skill(int skill_nr)
{
object o;

   if (member_array(skill_nr, Steed->query_redir_skills()) >= 0 && 
    !dont_redirect(calling_object()))
      o = Steed;
   else
      o = shadow_who;
   return o->query_skill(skill_nr);
}

// Rider doesn't get tired for 25%, horse for 75% when riding.
// Redirect fatigue to the steed only when the room does the call,
// so spells and poisons will still have effect *grin*
public void
add_fatigue(int f)
{
   // The random 4 indicates the 25% mentioned above
   if (calling_object()->query_prop(ROOM_I_IS) && random(4))
      Steed->add_fatigue(f);
   else
      shadow_who->add_fatigue(f);
}

// --- Functions related to combat -------------------------------------

// When rider is attacked, dismount him if Steed->mounted_combat()
// returns false. Otherwise just start normal combat.
public void
attacked_by(object o)
{
   if (!Steed->mounted_combat())
   {
      Steed->sh_do_dismount(shadow_who);
      shadow_who->attacked_by(o);
      remove_steed_shadow();
   }
   else
   {
      shadow_who->attacked_by(o);
   }
}

// When rider attacks somebody, dismount him if Steed->mounted_combat()
// returns false. Otherwise just start normal combat.
public void
attack_object(object o)
{
   if (!Steed->mounted_combat())
   {
      Steed->sh_do_dismount(shadow_who);
      shadow_who->attack_object(o);
      remove_steed_shadow();
   }
   else
   {
      shadow_who->attack_object(o);
   }
}

// Death, dismount first
public void
do_die(object killer)
{
   if (shadow_who->query_hp() > 0 || shadow_who->query_wiz_level() ||
      shadow_who->query_ghost())
      return;

   if (objectp(Steed))
      Steed->sh_do_dismount(shadow_who);
   restore_rider();
   shadow_who->do_die(killer);
   ::remove_shadow();
}

// --- Destruction of this shadow --------------------------------------

/* Function name: restore_rider
 * Description:   Restores the rider's no_show_composite.
 */
public void
restore_rider()
{
   if (!objectp(shadow_who))
      return;

   shadow_who->set_no_show_composite(0);
}

// Restore the rider before the shadow is removed
// note that remove_shadow is always called by remove_object.
// remove_shadow is private to prevent malicious buggy code from
// removing this shadow.
private void
remove_shadow()
{
   restore_rider();
   ::remove_shadow();
}

// Make sure the player dismounts before he is destructed
public void
remove_object()
{
   // dismount without removing the shadow, check if there really is
   // a steed object, otherwise the player might not be able to quit even.
   if (objectp(Steed))
      Steed->sh_do_dismount(shadow_who, 0, 1);  

   restore_rider();
   shadow_who->remove_object();  // remove the player

   ::remove_object();   // which calls remove_shadow
}

/* Function name: remove_steed_shadow
 * Description:   removes this steed shadow.
 */
public void
remove_steed_shadow()
{
   remove_shadow();
}

/* Function name: linkdeath_hook
 * Description:   dismount player when linkdieing.
 * Arguments:     int 1 for linkdeath, 0 for revive
 */
public void
linkdeath_hook(int i)
{
   if (i == 1)
   {
      if (objectp(Steed))
         Steed->sh_do_dismount(shadow_who, 0, 1);

      restore_rider();
      Steed->move_living("M", Steed->query_prop(LIVE_O_LAST_ROOM), 0, 1);
      shadow_who->linkdeath_hook(i);

      ::remove_shadow();
   }
   else // Reviving while mounted is not very likely, but it might happen
      shadow_who->linkdeath_hook(i);
}

// --- Code involving boarding and disembarking ships ---------------

/* Function name: query_cannot_move_to
 * Description:   Check if the player cannot go somewhere. This function
 *                has to handle message itself when the player cannot go
 *                to the specified destination.
 * Arguments:     mixed destination
 *                [string where_to]: e.g. "go north", "board the ship".
 *                   If "M" is passed give no fail messages.
 *                   If omitted "go there" will be substituted.
 * Returns:       int 0 if it's ok to move
 *                otherwise error code according to the 
 *                query_cannot_move_to code in the steed.
 */
public varargs int
query_cannot_move_to(mixed destination, string where_to)
{
int r;

   if (r = Steed->query_cannot_move_to(shadow_who,
      destination, where_to))
      return r;

   return shadow_who->query_cannot_move_to(destination, where_to);
}

/* Function name: query_cannot_board_ship
 * Description:   Can a player not board? Called by the ship object.
 * Arguments:     mixed destination room
 * Returns:       int 1 if unable to board
 */
public int
query_cannot_board_ship(mixed destination)
{
   if (query_cannot_move_to(destination, "board"))
      return 1;
    
   return shadow_who->query_cannot_board_ship(destination);
}

/* Function name: query_cannot_disembark_ship
 * Description:   Can a player not disembark? Called by the deck object.
 * Arguments:     mixed destination room
 * Returns:       int 1 if unable to disembark
 */
public int
query_cannot_disembark_ship(mixed destination)
{
   if (query_cannot_move_to(destination, "disembark"))
      return 1;

   return shadow_who->query_cannot_disembark_ship(destination);
}

// Intercepting set_m_in and set_m_out
// we don't want /std/combat/cbase.c to set
// the in/out messages to "X arrives riding on a horse".
// It used to do this when a player wimped, see cb_run_away()

// Logging this to check this really ANNOYING leave/arrive message bug!
// Not my bug, but other people's bug ofcourse.
public void
set_m_in(string s)
{
// Don't call the original set_m_in while player is mounted!!!
//   shadow_who->set_m_in(s);
}

public void
set_m_out(string s)
{
// Don't call the original set_m_out while player is mounted!!!
//   shadow_who->set_m_out(s);
}
