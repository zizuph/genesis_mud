/*  coded by Amelia, 5/14/97
*  pseudo poison, bad news for the undead,
*  if they drink the holy water, it begins
*  to make them happier, but reduces str and mana
*/
#pragma save_binary

inherit "/std/object";
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>

int X;

void
create_object()
{

    set_name("_holy_poison_");


    add_prop(OBJ_I_INVIS, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_NO_DROP,1);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VALUE, 0);
    set_no_show();

}


int
tell_damage_player(object ob)
{
    int j;

    j=random(4);

    switch(j)
    {
    case 0:
	ob->command("choke");
	ob->catch_msg("The holy water clarifies your soul.\n");
	break;

    case 1:
	ob->catch_msg("You feel weak as a kitten.\n");
	break;

    case 2:
	ob->catch_msg("The world looks so much brighter now.\n");
	ob->command("emote smiles happily at the world.");
	break;

    case 3:
	ob->command("emote whistles a happy tune.");
	ob->command("hug all");
	break;

    }

    return 1;

}
int
remove_it(object to, object player)
{
    player->catch_msg("The effect of the holy water wears off.\n");
    to->remove_object();
    return 1;
}

int
enter_env(object env, object from)
{
    object to = this_object();

    X = env->query_stat(SS_STR) * 3 / 4 + random(30);
    ::enter_env(env, from);
    if (living(env))
    {
	env->add_tmp_stat(SS_STR, -X, 10);
	env->add_mana(-(env->query_max_mana()));
	set_alarm(3.0, 20.0, &tell_damage_player(env));
	set_alarm(300.0, -1.0, &remove_it(to, env));
	env->catch_msg("You have been poisoned!\n");
	return 1;
    }
    return 1;
}
