/* A gleamable boomerang */
inherit "/std/object";

#include <stdproperties.h>
#include <cmdparse.h>
#include <tasks.h>
#include <ss_types.h>
#include <macros.h>

#define GLEAMTIME_PER_THROW 120
#define FATIGUE 10 /* The costs of fatigue-points for throwing the boomerang */

/*
 * Function name: create_object
 * Description:   The standard create routine
 * Arguments:     none
 * Returns:       nothing
 */

void create_object()
{
   set_name("boomerang");
   set_pname("boomerangs");
   set_short("@@boomerang_short");
   set_pshort("@@boomerang_pshort");
   set_adj("strange looking");
   set_long("@@boomerang_long");
   add_prop(OBJ_I_LIGHT,0);
   add_prop(OBJ_I_WEIGHT,200);
   add_prop(OBJ_I_VOLUME,150);
   add_prop(OBJ_I_VALUE,100);
}

/*****************************************************************************/

/*
 * Function name: boomerang_short, boomerang_pshort, boomerang_long
 * Description:   I change the short, plural short and long description
                  of the boomerang if it's gleaming.
 * Arguments:     none
 * Returns:       The description
 */

string boomerang_short()
{
   return   "strange looking boomerang"
            + ((find_call_out("extinguished") != -1) ? " (gleaming)" : "");
}

/*---------------------------------------------------------------------------*/

string boomerang_pshort()
{
   return   "strange looking boomerangs"
            + ((find_call_out("extinguished") != -1) ? " (gleaming)" : "");
}

/*---------------------------------------------------------------------------*/

string boomerang_long()
{
   if (find_call_out("extinguished") != -1)
      return   "The boomerang gleams in a shining yellow light. " +
               "It looks marvelous.\n";
   else
      return (break_string(
         "Somehow the boomerang looks as if it has seen better times. " +
         "It's no weapon at all, it's just here to have fun. " +
         "Maybe you should try to throw it.\n",70));
}

/*****************************************************************************/

/*
 * Function name: init
 * Description:   Adds commands to the player
 * Arguments:     none
 * Returns:       nothing
 */

void init()
{
   add_action("boomerang_throw","throw");
}

/*****************************************************************************/

/*
 * Function name: boomerang_throw
 * Description:   The player tries to throw the boomerang.
 * Arguments:     str - the string describing what he wants to throw.
 * Returns:       1/0
 */

int boomerang_throw(string str)
{
   int      time_left;  /* The gleamtime left*/
   object   *obj;       /* Objects of name "str" the player's holding */
   
   /* Is it this boomerang he's trying to throw or something else? */
   notify_fail("Throw what?\n");
   if (!sizeof(obj = FIND_STR_IN_OBJECT(str, this_player())) ||
      (obj[0] != this_object()))
      return 0; /* Didn't try to throw this boomerang or doesn't hold it */

   /* Is the player too tired to throw the boomerang? */
   if ((this_player()->query_fatigue()) < FATIGUE) {
      write("You're too tired to throw that boomerang.\n");
      say(QCTNAME(this_player()) + " tries to throw a boomerang but fails.\n");
      log_file("boomerang",this_player()->query_name() + 
         " tried to throw a boomerang.\n");
      return 1;
   }

   if (this_player()->resolve_task(TASK_ROUTINE,
      ({TS_INT,SS_WEP_MISSILE})) < 0){
      write(break_string("Somehow you feel that you wouldn't manage to " +
         "throw the boomerang right and you don't want the other players " +
         "laughing at you when you don't succeed.\n",70));
      log_file("boomerang",this_player()->query_name() + 
         " didn't dare to throw a boomerang.\n");
      return 1;
   }


   /* The player can throw the boomerang */
   write(break_string(
      "You throw the boomerang as hard as you can. " +
      "It makes a very large curve, returns to you and you catch it.\n",70));
   say(break_string(QCTNAME(this_player()) + 
      " throws a boomerang and catches it easily. " +
      "You wish you could do that too.\n", 70));
   log_file("boomerang",this_player()->query_name() + 
      " threw a boomerang.\n");

   this_player()->add_fatigue(-FATIGUE); /* decrease fatigue */

   /* Is the boomerang gleaming already? */
   if (find_call_out("extinguished") == -1) {
      call_out("extinguished", GLEAMTIME_PER_THROW);
      change_prop(OBJ_I_LIGHT, 1);
      write("Suddenly the boomerang starts gleaming.\n");
   }
   
   /* The boomerang gleams already. -> Increase gleam-time */
   else { 
      this_player()->add_fatigue(-FATIGUE); /* decrease fatigue */
      time_left = remove_call_out("extinguished"); /* gleam-time left */
      call_out("extinguished", time_left + GLEAMTIME_PER_THROW);
      write("You wonder if it's gleaming for a longer time now.\n");
   }
   return 1;
}

/*****************************************************************************/

/*
 * Function name: extinguished
 * Description:   When this function's called the boomerang no longer gleams.
 * Arguments:     none
 * Returns:       nothing
 */

void
extinguished()
{
   object obj; /* Location of the boomerang */
   
   obj = environment();
   if (living(obj)){ /* Tell player and room that boomerang stops gleaming */
      tell_object(obj,"Your boomerang stops gleaming.\n");
      tell_room(environment(obj),"The boomerang " +
         QTNAME(obj) + " is holding stops gleaming.\n",obj);
   }
   else /* Tell room that the boomerang stops gleaming */
      tell_room(obj,"The boomerang stops gleaming.\n");
   change_prop(OBJ_I_LIGHT, 0);
}

