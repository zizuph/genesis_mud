/*
   steed_sh.c

   Rider's shadow for riding steed.c around.

   Copyright by Wout de Zeeuw, Fysix@Genesis, May 1997

 */

#pragma save_binary
#pragma strict_types

inherit "/std/shadow";

#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "default.h"

#define DEBUG(x) find_player("fysix")->catch_msg(x)

// --- Global variables ------------------------------------------------

static object Steed;
static string M_in, M_out, // New arrive and leave messages
              In_move;     // Direction we are moving to

// --- Prototypes ---
public void restore_rider();

// --- Functions ------------------------------------------------------

/* Function name: set_steed
 * Description:   Has to be called to initialize this shadow.
 *                Notify the steed object to the steed shadow of the rider.
 *                Also resets the rider's in / out messages.
 * Arguments:     object - the steed object
 */
public void
set_steed(object o)
{
   Steed = o;

   // Don't show the rider, the desc is incorporated in the steed
   shadow_who->set_no_show_composite(1);

   // Set the new messages
   M_in = "arrives riding on " + 
       LANG_ADDART(o->short_old());
   M_out = "rides " + shadow_who->query_possessive() +
      " " + o->short_old();
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
 */
public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
int      r;
object   *team, env;
string   vb, com;

   // When teleported, dismount, move and later remove the shadow
   if (how == "X")
   {
      Steed->sh_do_dismount(shadow_who, 0, 1);
      r = shadow_who->move_living(how, to_dest, dont_follow, no_glance);
      remove_shadow();
      return r;   // This point won't be reached
   }
   
   // If this rider is not the driving rider, don't execute the move
   if (Steed->query_driver() != shadow_who)
   {
      shadow_who->catch_tell("You cannot go there since you " +
       "are not driving " + Steed->query_the_name(shadow_who) + ".\n");
      return 9;
   }

   // Check if the steed can go there
   if (!Steed->check_destination(to_dest))
   {
      shadow_who->catch_tell("Your " + Steed->short_old(shadow_who) +
       " refuses to go there.\n");
      return 8;
   }

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

   // If shadow_who is moved OK, move the steed and team as well
   if (!r && how != "X")
   {
      Steed->add_prop(ROOM_S_DIR, ({how, "horse"}));
      Steed->drive_steed(how, to_dest, 1, 1);

      if (!dont_follow && sizeof(team))
      {
         // Command for the followers if this is a leader
         if (!strlen(vb))
         {
            if (sizeof(explode(how, " ")) == 1)
               com = how;
            else
               com = "";
         }
         else if (com = env->query_dircmd()) // check for "board ship" etc.
            com = vb + " " + com;
         else
            com = vb;

         In_move = how;
         map(team, &st_move_team(, com));
      }
   }
   
   // Check if shadow_who and steed ended up in the same room
   if (environment(shadow_who) != environment(Steed))
   {
      Steed->sh_do_dismount(shadow_who, 0, 1);
      remove_shadow();  // No code will be executed after this statement
   }

   In_move = 0;

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

// When moving around, the most tired of the rider and steed reflects
// the riding total fatigue.
public int
query_fatigue()
{
int steed_fatigue, rider_fatigue;

   if (calling_object()->query_prop(ROOM_I_IS))
   {
      steed_fatigue = Steed->query_fatigue();
      rider_fatigue = shadow_who->query_fatigue();
      return (rider_fatigue < steed_fatigue ? rider_fatigue : steed_fatigue);
   }
   else
      return shadow_who->query_fatigue();
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
      remove_shadow();
   }
   else
   {
      shadow_who->attacked_by(o);
//      Steed->attacked_by(o); // is this allowed by balance?
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
      remove_shadow();
   }
   else
   {
      shadow_who->attack_object(o);
      Steed->attacked_by(o);
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
// note that remove_shadow is always called by remove_object
public void
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
 * Description:   Removes this steed shadow.
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
 *                [string where_to]: e.g. "board the ship", "go north",
 *                "enter the portal".
 *                If omitted, "there" will be substituted.
 *                If no messages are wanted, pass "S" as argument
 *                for silent mode.
 * Returns:       int 1 if player cannot move to destination.
 */
public varargs int
query_cannot_move_to(mixed destination, string where_to)
{
   // Are we driving the steed?
   if (shadow_who != Steed->query_driver())
   {
      if (where_to != "S")
         shadow_who->catch_tell("But you are not driving the " +
          Steed->query_race() + ".\n");
      return 1;
   }

   // Does the steed want to go there?
   if (!Steed->check_destination(destination))
   {
      if (where_to != "S")
      {
         if (!strlen(where_to))
            where_to = "there";
         shadow_who->catch_tell("Your " + Steed->query_race() +
          " refuses to " + where_to + ".\n");
      }
      return 1;
   }

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
