/* chapel/obj/bouget.c is cloned by chapel/store.c */
inherit "/std/object";
 
#include <stdproperties.h>
#include <macros.h>
#include <const.h>
#include "../chapel.h"
#include <cmdparse.h>
 
#define BOUQUET_SUBLOC "_wedding_bouquet_subloc"
 
int have_been_thrown;

/* Prototypes */
int do_throw(string arg);
int do_smell(string arg);
 
/*
 * Function name:   create_object
 * Description:     Set up the object
 */
void
create_object()
{
    set_name("bouquet");
    add_name("flowers");
    set_adj("wedding");
    set_long("It's a glowing, crystal wedding bouquet. You could probably " +
             "smell them, or even throw them after the cermony.");
 
    add_prop(OBJ_I_WEIGHT, 300);  /* It weighs 300 grams */
    add_prop(OBJ_I_VOLUME, 200);  /* It measures 200 ml. */
    add_prop(OBJ_I_VALUE, 432);
}
 
/*
 * Function name:   init
 * Description:     This function is called each time this object comes
 *		    near a living.
 */
void
init()
{
    ::init();
    add_action(do_throw, "throw");
    add_action(do_smell, "smell");
}
 
void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    if (env && living(env))
      env->add_subloc(BOUQUET_SUBLOC, this_object());
}
 
void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    if (env && living(env))
      env->remove_subloc(BOUQUET_SUBLOC);
}
 
/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *                who     - The player to whom we added the subloc
 *                for_obj - The looker
 * Returns:       The string the looker shall see
 */
string
show_subloc(string subloc, object who, object for_obj)
{
   string str;
 
   /* Is this our call? */
   if (subloc != BOUQUET_SUBLOC)
      return "";
 
   if (who->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return "";
 
   if (for_obj == who)
      str = "You are ";
   else
      str = capitalize(who->query_pronoun()) + " is ";
 
   str += "carrying a " + query_short() + ".\n";
   return str;
}
 
int
wedding_stuff()
{
    return 1;
}
 
/*
 * Function name:   do_throw
 * Decription:      Allow the player to throw this bouquet.
 * Arguments:       str: Whatever the player typed behind "throw"
 * Returns:         1 if successfull, 0 if not.
 */
/*
 * Idea: let the bouquet only be caught be other females in the same room.
 */
int
do_throw(string arg)
{
    object *obs;
    int    i;
 
    notify_fail("Throw what?\n");
    if (!arg || !id(arg))
      return 0;
 
    if (this_player()->query_prop(IS_BRIDE)) {
    write("But you are not married yet!\n");
    return 1;
    }
 
    if (have_been_thrown) {
    write("It is a bit late for that; it has already been done.\n");
    return 1;
    }
    have_been_thrown = 1;
 
    write("You throw the wedding bouquet into the air.\n");
    say(QCTNAME(TP) + " throws the wedding bouquet into the air.\n");
 
    obs = filter(all_inventory(environment(this_player())),
           "filter_catch", this_object());
    if (sizeof(obs)) {
    i = random(sizeof(obs));
    if (!move(obs[i])) {
     obs[i]->catch_msg("You catch the wedding bouquet!\n");
     tell_room(environment(this_player()), QCTNAME(obs[i]) +
           " catches the wedding bouquet.\n");
     return 1;
       }
    }
 
    tell_room(environment(TP), "The the wedding bouquet falls to the floor " +
              "and shatters.\n");
    remove_object();
    return 1;
}
 
int
filter_catch(object ob)
{
    if (!living(ob))
       return 0;
    if (!ob->query_gender() == G_FEMALE)
       return 0;
    if (ob == this_player())
       return 0;
    if (!CAN_SEE(this_player(), ob))
       return 0;
    if (sizeof(FIND_STR_IN_OBJECT("marriage ring", ob)))
       return 0;
    return 1;
}
 
int
do_smell(string arg)
{
    notify_fail("Smell what?\n");
    if (!arg)
        return 0;
    NF("Smell flowers?\n");
    if (!id(arg))
    return 0;
    write("You inhale the exquisit flagrance of the flowers.\n");
    tell_room(environment(TO), QCTNAME(TP) + " smells the flowers.\n", TP);
    return 1;
}
 
int
for_bride()
{
    return 1;
}
