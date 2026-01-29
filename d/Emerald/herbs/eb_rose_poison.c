/*  coded by Amelia, 5/14/97
*  pseudo poison, for skunk berries
*  Earthsea herbs
*  has healing effect, with undesirable social side-effects
*
* This is a modification of this poison
* to be used for the black rose in the
* Manor's Garden. It will makes sick
* anyone that sniff it, provoking
* vomit. Could be use later for
* a quest.
* Marisol Ramos (10/28/97)
*
* Modified again for the ebony_rose.c for the castle_garden in 
* Emerald. This pseudo-poison will create a temporary madness.
* (07/08/98)
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

    set_name("_skunk_poison_");
    add_name("_rose_poison_");


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
    object tp = this_player();

    int j;

    j=random(4);

    switch(j)
    {
    case 0:
	ob->command("drool absent");
    tell_room(environment(tp), QCTNAME(tp) +  "drools absentmindedly "+
    "dropping saliva all over the ground.\n",({tp}));
	ob->heal_hp(-5);
	break;

    case 1:
	ob->command("twitch craz");
	break;

    case 2:
	ob->catch_msg("You feel that somebody is watching you.\n");
	ob->heal_hp(-5);
	break;

    case 3:
	ob->command("laugh maniac");
	ob->heal_hp(20);
	ob->catch_msg("You can't control yourself. Madness is creeping "+
	  "slowly in your mind.\n");
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
	env->catch_msg("You feel that you are loosing your mind.\n");
	return 1;
    }
    return 1;
}
