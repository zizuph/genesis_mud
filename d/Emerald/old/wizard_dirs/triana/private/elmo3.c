inherit "/d/Avenir/inherit/monster.c";
#include "/d/Avenir/common/bazaar/bazaar.h"
#include <language.h>
#define L(str) lower_case(str)
#define SUBLOC "holdin_elmo_subloc"

void
create_monster()
{
	set_name("tickle-me-elmo");
	add_name("elmo");
	set_race_name("elmo");
	set_short("tickle-me-elmo");
        set_adj("red");
	add_adj("fuzzy");
	set_long("   A small tickle me elmo you can hold and cuddle.\n\n");
        default_config_npc(5);

    set_act_time(10);
	add_act("giggle merrily");
	add_act("twinkle merrily");
	add_act("laugh softly");
	add_act("snuggle all");
    set_tell_active(1);

	add_prop(OBJ_M_NO_GET, 0);
	add_prop(OBJ_I_WEIGHT, 2);
	add_prop(OBJ_I_VOLUME, 2);
}

void
init_living()
{
    add_action("react_hug", "hug");
    add_action("react_tickle", "tickle");
}
void
slow_enter_env(object player)
{
    tell_room(environment(player), QCTNAME(player) + " holds elmo in " +
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
    env->catch_msg("You stop holding elmo in your arms.\n");
    tell_room(environment(env),QCTNAME(env)+" takes elmo from "+
       env->query_possessive()+" arms.\n", env);
    env->remove_subloc(SUBLOC);
	::leave_env(env, to);
}

string
show_subloc(string subloc, object carrier, object for_obj)
{
    if (for_obj == carrier)
    {
	return "You are holding elmo in your arms.\n";
    }
    return capitalize(carrier->query_pronoun()) + " is holding elmo in " +
	carrier->query_possessive() + " arms.\n";
}

int
react_hug(string str)
{
    if (str == "elmo")
      {
	set_alarm(2.0,0.0,"command","emote looks content.");
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


