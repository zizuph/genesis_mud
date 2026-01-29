/*  coded by Amelia, 5/14/97
*  pseudo poison, bad news for the undead,
*  if they drink the holy water, it begins
*  to make them happier, but reduces str and mana
*
* This is a modification of the holy poison
* to be used in the Manor's Garden. It will
* make any player feel drunk and happy if
* sniff the red rose. Could be used later as
* a quest item. Marisol Ramos (10/28/97)
*
* Modified in (07/09/98) to be used in the castle_garden
* in Emerald. If a player sniff it will feel really 
* romantic. 
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
    add_name("sca_rose_poison");


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
	ob->command("$sigh romantically");
	ob->catch_msg("The delicate perfume fills all your being.\n");
	break;

    case 1:
	ob->catch_msg("You feel love for every single creature.\n");
	break;

    case 2:
	ob->catch_msg("Your heart wants to explode with love.\n");
	ob->command("$say How I love to be in love with love!");
	break;

    case 3:
	ob->command("$say You are such a darling!");
	ob->command("kiss all romant");
	break;

    }

    return 1;

}
int
remove_it(object to, object player)
{
    player->catch_msg("The effect of the rose's perfume wears off.\n");
    to->remove_object();
    return 1;
}

int
enter_env(object env, object from)
{
    object to = this_object();

    X = env->query_stat(SS_STR) * 3 / 4 + random(10);
    ::enter_env(env, from);
    if (living(env))
    {
	env->add_tmp_stat(SS_STR, -X, 10);
	env->add_mana(-(env->query_max_mana()));
	set_alarm(3.0, 20.0, &tell_damage_player(env));
	set_alarm(300.0, -1.0, &remove_it(to, env));
	env->catch_msg("You feel in love now!\n");
	return 1;
    }
    return 1;
}
