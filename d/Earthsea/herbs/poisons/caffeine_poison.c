/*  coded by Amelia, 5/14/97
*  pseudo poison, no real damage
*  too much caffeine gives you the jitters
*/
#pragma save_binary

inherit "/std/object";
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>

void
create_object()
{

    set_name("_caffeine_poison_");


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
	ob->command("bounce");
	ob->catch_msg("You feel a little jittery.\n");
	break;

    case 1:
	ob->command("tremble");
	break;

    case 2:
	ob->catch_msg("You feel a bit nervous.\n");
	ob->command("smile nervously");
	ob->command("blink");
	break;

    case 3:
	ob->command("emote bounces off the walls.");
	break;

    }

    return 1;

}
int
remove_it(object to, object player)
{
    player->catch_msg("The effects are wearing off.\n");
    to->remove_object();
    return 1;
}

int
enter_env(object env, object from)
{
    object to = this_object();

    ::enter_env(env, from);
    if (living(env))
    {
	set_alarm(3.0, 20.0, &tell_damage_player(env));
	set_alarm(300.0, -1.0, &remove_it(to, env));
	env->catch_msg("Your stomach feels a bit queasy.\n");
	return 1;
    }
    return 1;
}
