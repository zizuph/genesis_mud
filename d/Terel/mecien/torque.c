inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <language.h>
#include <composite.h>
#include <filter_funs.h>

#define	TORQUE_SUBLOC	"_torque_subloc"
#define	MANA_COST	80
#define MIN_INTERVAL	120

int last_time;

void
create_object()
{
    set_name("torque");
    add_name("phase_torque");
    add_adj("crystal");
    set_long(break_string("This beautifully crafted torque is made entirely "+
       "of crystal that swirls with every colour in the spectrum.\n", 76));

   add_prop(OBJ_M_NO_DROP, "You can't drop that!\n");
    add_prop(OBJ_M_NO_STEAL, "That item is not stealable!");
    add_prop(OBJ_M_NO_SELL, "It is too priceless to sell!\n");
    add_prop(OBJ_M_NO_BUY, "It is not for sale!\n");
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(MAGIC_AM_MAGIC, ({ 10, "divination" }));
    add_prop(MAGIC_AM_ID_INFO, ({
	"The torque is enchanted with divine power.\n", 1,
	break_string("It can "+
		     "be used to look at the surroundings of other people "+
		     "anywhere in the world using the trigger 'scry "+
		     "<name>'.\n", 76), 15 }) );
}

string
query_auto_load()
{
    return MASTER;
}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    if (living(env))
	env->add_subloc(TORQUE_SUBLOC, this_object());
}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    if (living(env))
	env->remove_subloc(TORQUE_SUBLOC);
}

string
show_subloc(string subloc, object carrier, object for_obj)
{
    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";
    if (for_obj == carrier)
	return "You are wearing " + LANG_ADDART(short()) + " on your forehead.\n";
    return capitalize(carrier->query_pronoun()) + " is wearing "+
	   LANG_ADDART(short()) + " on " + carrier->query_possessive() + " forehead.\n";
}

void
init()
{
    ::init();
    add_action("scry", "scry");
}

int
scry(string arg)
{
    object who, *items;
    string who_str;
    int    success;

    notify_fail("Scry on whom?\n");
    if (!arg)
	return 0;
    if (this_player()->query_mana() < MANA_COST) {
	notify_fail("You are too exhausted to do that.\n");
	return 0;
    }
    who = find_living(arg);
    if (!who) {
	if (sscanf(arg, "on %s", who_str) == 1)
	    who = find_living(who_str);
	if (!who)
	    return 0;
    }
    if (!this_player()->query_met(who))
	return 0;
    if (who->query_wiz_level() > this_player()->query_wiz_level())
	return 0;
    if (!environment(who))
	return 0;
    success = this_player()->resolve_task(TASK_ROUTINE,
		({ TS_INT, SKILL_WEIGHT, 50, SS_SPELLCRAFT,
			   SKILL_WEIGHT, 25, SS_ELEMENT_LIFE,
			   SKILL_WEIGHT, 25, SS_FORM_DIVINATION }),
		who, ({ TS_INT, SS_ELEMENT_DEATH }));
    if (environment(who)->query_no_snoop() ||
	who->query_prop(OBJ_M_NO_MAGIC) ||
	environment(who)->query_prop(ROOM_M_NO_MAGIC))
	success = 0;
    if (who->query_prop(OBJ_I_INVIS) && !this_player()->query_prop(LIVE_I_SEE_INVIS))
	success = 0;
    if (time() - last_time < MIN_INTERVAL)
	success = 0;
  if(who->query_prop("protected"))
{
   write("A strange power seems to flood your mind and make you uneasy.\n");
  return 1;
   }
    if (success < 1) {
	write("For some reason, you were unable to do that.\n");
	this_player()->add_mana(-MANA_COST / 2);
	return 1;
    }
    who->catch_msg("You have a sense of being watched.\n");
    write("You can see the following:\n");
    if (environment(who)->query_prop(OBJ_I_LIGHT) < 1)
	write("A dark room.\n");
    else {
	write(environment(who)->long());
	items = FILTER_CAN_SEE(all_inventory(environment(who)), this_player());
	if (items) {
	    if (sizeof(FILTER_DEAD(items)))
		write(capitalize(COMPOSITE_DEAD(FILTER_DEAD(items))) + ".\n");
	    if (sizeof(FILTER_LIVE(items)))
		write(capitalize(COMPOSITE_LIVE(FILTER_LIVE(items))) + ".\n");
	}
    }
    this_player()->add_mana(-MANA_COST);
    last_time = time();
    return 1;
}
