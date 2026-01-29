inherit "/d/Avenir/inherit/monster.c";
#include "/d/Avenir/common/bazaar/bazaar.h"
#include <language.h>
#define L(str) lower_case(str)
#define SUBLOC "holdin_baby_subloc"

void
create_monster()
{
  
  set_name("baby");
	set_race_name("baby");
	set_short("small baby");
        set_adj("small");
        set_gender(1);
        add_name("infant");
	set_long("A small baby who needs some T.L.C.\n");
        default_config_npc(5);

    set_act_time(10);
	add_act("giggle");
	add_act("moan soft");
	add_act("twinkle");
	add_act("cry soft");
	add_act("emote coos softly");
	add_act("laugh softly");
	add_act("snuggle all");
	add_act("emote gurgles happily");
	add_act("emote smiles at you");
	add_act("emote grasps your finger and coos happily");
    set_tell_active(1);
    add_prop(OBJ_M_NO_GET, 0);
	add_prop(OBJ_I_WEIGHT, 0.5);
	add_prop(OBJ_I_VOLUME, 0.5);
}

void
init_living()
{
    add_action("react_hug", "hug");
    add_action("react_tickle", "tickle");
	add_action("react_kiss", "kiss");
}
void
slow_enter_env(object player)
{
    tell_room(environment(player), QCTNAME(player) + " holds the baby in " +
	player->query_possessive() + " arms\n", ({ player }) );
}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    if(!living(env)) return;
    set_alarm(0.1, 0.0, &slow_enter_env(env));
    env->add_subloc(SUBLOC, this_object());
}

void
leave_env(object env, object to)
{
    if(!living(env)) return;
    env->catch_msg("You stop holding the baby in your arms.\n");
    tell_room(environment(env),QCTNAME(env)+" takes the baby from "+
       env->query_possessive()+" arms.\n", env);
    env->remove_subloc(SUBLOC);
	::leave_env(env, to);
}

string
show_subloc(string subloc, object carrier, object for_obj)
{
    if (for_obj == carrier)
    {
	return "You are holding a baby in your arms.\n";
    }
    return capitalize(carrier->query_pronoun()) + " is holding a baby in " +
	carrier->query_possessive() + " arms.\n";
}

int
react_hug(string str)
{
    if (str == "baby")
      {
	set_alarm(2.0,0.0,"command","emote snuggles close to you");
	  return 0;
      }
}


int
react_tickle(string str)
{
	if (str == "baby")
	{
	set_alarm(2.0,0.0,"command", "emote laughs merrily");
            return 0;
        }
}

int
react_kiss(string str)
{
	if (str == "baby")
	{
	set_alarm(2.0,0.0,"command","emote smiles and kisses you, leaving slobber behind");
	return 0;
}
}


