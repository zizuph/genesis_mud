/*
   lead_sh.c

   Shadow for leading steeds

   Copyright by Wout de Zeeuw, Fysix@Genesis, August 1997

 */
#pragma save_binary
#pragma strict_types

inherit "/std/shadow";

#include <stdproperties.h>

// --- Global variables ------------------------------------------------

static object* Steed = ({ });
// direction the leader is moving to (how from move_living)
static string In_move; 

// --- Prototypes ---
public void remove_lead_shadow();

// --- Functions -------------------------------------------------------
/* Function name: add_steed_follow
 * Description:   Has to be called to initialize this shadow.
 *                Adds a steed to the shadowee that follows him.
 * Arguments:     object - the steed object
 */
public void
add_steed_follow(object o)
{
   Steed -= ({ 0 });
   Steed += ({ o });
}

/* Function name: remove_steed_follow
 * Description:   Let a steed stop following
 * Arguments:     object - the following steed object
 */
public void
remove_steed_follow(object o)
{
   Steed -= ({ 0 });
   Steed -= ({ o });
   if (!sizeof(Steed))
      remove_lead_shadow();
}

/* Function name: query_steed_follow
 * Description:   Which are all steeds following the shadowee?
 * Returns:       object *
 */
public object*
query_steed_follow()
{
   return Steed;
}

/* Function name: query_leading_steed
 * Description:   Is shadow_who leading one or more steeds?
 * Returns:       int 1
 */
public int
query_leading_steed()
{
   return 1;
}

// --- Move functions ------------------------------------------------

/* Function name: st_check_followers
 * Description:   Check that the follower is where the rider is.
 * Arguments:     ob - The follower object to check.
 * Returns:       Result of check. 1/0.
 */
nomask int
st_check_followers(object ob)
{
   return (environment(ob) == environment(shadow_who) &&
      shadow_who->check_seen(ob));
}

/* Function name: st_move_followers
 * Description:   Move a the following steeds
 * Arguments:     ob - A follower to move.
 *                com - The command the leader gave
 * Returns:       Success of move.
 */
nomask int
st_move_followers(object ob, string com)
{
   if (!In_move)
      return 0;

   return (int) ob->command("$" + com);
}

/* Function name: move_living
 * Description:   Shadow the rider's move_living function in order to 
 *   co-move the following steeds.
 *   Functions moves the leader, then the steeds.
 *   When you want to call the original move_living 
 *   without bothering about the steed, call move_living_old in the player. 
 */
public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
int    r;
string vb, com;
object env, *followers;

   env = environment(shadow_who);
   vb = query_verb();

   if (Steed)
      followers = filter(Steed, st_check_followers);

   // Move the shadow_who
   r = shadow_who->move_living(how, to_dest, dont_follow, no_glance);

   // If shadow_who is moved OK, move the steeds as well
   if (!r && how != "X" && !dont_follow)
   {
      // Command for the followers if this is a leader
      if (!strlen(vb))
      {
         if (sizeof(explode(how, " ")) == 1)
            com = how;
         else
            com = "";
      }
      else if (com = env->query_dircmd())
         com = vb + " " + com;
      else
         com = vb;

      In_move = how;
      if (sizeof(followers))
         map(followers, &st_move_followers(, com));
   }

   In_move = 0;
   return r;
}

/* Function name: move_living_old
 * Description:   Calls original move_living function.
 * Arguments:     see move_living
 * Returns:       see move_living
 */
public varargs int
move_living_old(string how, mixed to_dest, int dont_follow, int no_glance)
{
   return shadow_who->move_living(how, to_dest, dont_follow, no_glance);
}

// Tell the steeds that their leader is not their leader anymore
// before the shadow is removed
// remove_shadow is private to prevent malicious buggy code from
// removing this shadow.
private void
remove_shadow()
{
   Steed->do_unlead(shadow_who);
   ::remove_shadow();  
}

/* Function name: remove_lead_shadow
 * Description:   Call this function to remove this shadow.
 */
public void
remove_lead_shadow()
{
   remove_shadow();
}
