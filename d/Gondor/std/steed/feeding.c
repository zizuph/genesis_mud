/*
   feeding.c

   Inheritable module for feeding livings.

   Fysix@Genesis, May 1997

 */

#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <composite.h>
#include <cmdparse.h>
#include <stdproperties.h>
#include "default.h"

// --- Global variables -------------------------------------------------

string* Allowed_food = ({ });

// --- Functions --------------------------------------------------------

/* Function name: light_fail
 * Description:   We fail to do something because it is dark?
 * Arguments:     string - the object string
 * Returns:       int 0 if failed
 */
varargs int
light_fail(string str)
{
string s;

    if (!strlen(str))
	str = query_verb() + " things";
#ifdef GENESIS
    if (!stringp(s = environment(this_player())->query_prop(ROOM_S_DARK_MSG)))
#endif
	notify_fail("It is too dark to " + str + ".\n");
#ifdef GENESIS
    else
	notify_fail(s + " " + str + ".\n");
#endif
    return 0;
}

/* Function name: can_feed
 * Description:   Is this object something that is accepted by food by this
 *                living?
 * Arguments:     object, the food object
 * Returns:       int 0 - false, 1 - true
 */
public int
can_feed(object o)
{
   if (member_array(o->query_name(), Allowed_food) < 0)
   {
      notify_fail(capitalize(o->short()) + 
         " is not accepted as food.\n");
      return 0;
   }
   return 1;
}

/* Function name: query_allowed_food
 * Description:   What kinds of food are allowed for this living for feeding?
 * Returns:       string* - an array of food names
 */
public string*
query_allowed_food()
{
   return Allowed_food;
}

/* Function name: set_allowed_food
 * Description:   Set the kinds of food that this living is allowed to
 *                be fed with.
 * Arguments:     mixed - a string or array of strings describing the food
 */
public void
set_allowed_food(mixed t)
{
   if (stringp(t))
      t = ({ t });
   if (pointerp(t))
      Allowed_food = t;
}

/* Function name: do_feed
 * Description:   Try to feed this living.
 * Arguments:     mixed - the food object(s)
 *                object - feeder, defaults to this_player()
 * Returns:       int 0 - failed feeding, 1 - success
 */
public varargs int
do_feed(mixed o, object feeder)
{
int    i, eaten, ate_something;
object tp = this_player();

   if (objectp(o))
      o = ({ o });

   // Check all food
   i = sizeof(o);
   while (i--)
      if (!can_feed(o[i]))
         return 0;

   if (!objectp(feeder))
      feeder = this_player();

   // Transfer food and let living eat the stuff
   // add check later if food was really moved
   
   o->move(this_object());

   feeder->catch_msg("You feed the " + this_object()->short(feeder) + ".\n");
   tell_room(environment(this_object()),
    QCTNAME(feeder) + " feeds the " +
    QCTNAME(this_object()) + ".\n", feeder);

   this_object()->command("eat all");

/*
   // Try to eat now, check if something is eaten
   ate_something = 0;
   i = sizeof(o);
   set_this_player(this_object());
   while (i--)
   {
      eaten = o[i]->eat_it("all");
      ate_something = ate_something || eaten;
      if (!eaten)
         break;
   }
   set_this_player(tp);

   // Tell everybody if we ate something
   if (ate_something)
   {
      feeder->catch_msg("You feed the " + this_object()->short(feeder) + ".\n");
      tell_room(environment(this_object()),
       QCTNAME(feeder) + " feeds the " +
       QCTNAME(this_object()) + ".\n", feeder);
   }
   
   // Tell everybody if we were full
   if (!eaten)
      feeder->catch_tell("The " + this_object()->short(feeder) + 
       " cannot eat " +
       o[i]->short() + " anymore.\n");

   // move the food back that wasn't eaten
   o[0..i]->move(feeder);
 */
   return 1;
}

/* Function name: feed
 * Description:   Action for feeding animals. Makes a call to do_feed(mixed)
 *                in the object, as define in feeding.c. do_feed should
 *                handle the actual feeding.
 * Arguments:     string - the arguments after the feed command
 * Returns:       int 1 - succesful, 0 - failed
 */
public nomask int
feed(string s)
{
object *living_list, living, *food_list, food;
string s1, s2;

   notify_fail("Feed whom with what?\n");
   if (!stringp(s))
      return 0;

   if (!parse_command(s, all_inventory(environment(this_player())),
    "%s 'with' %s", s1, s2))
      return 0;

   living_list = FIND_STR_IN_ARR(s1, all_inventory(environment(this_player())));
   if (sizeof(living_list) != 1)
      return 0;

   living = living_list[0];

   food_list = FIND_STR_IN_ARR(s2, all_inventory(this_player()));
   if (sizeof(food_list) == 0)
      return 0;

   notify_fail("Try to feed the " + living->short() + " with one thing " +
    "at a time.\n");
   if (sizeof(food_list) > 1)
      return 0;

   food = food_list[0];
   return living->do_feed(food, this_player());
}

