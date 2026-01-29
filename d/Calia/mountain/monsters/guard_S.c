/*
 *	A guard for the southern section of the guild tunnels of Mount 
 *       Kyrus. 
 *
 *       Coded by Amelia, adapted by Maniac 7/3/96
 *       History:
 */
#pragma save_binary 

#include "guard.h" 

inherit CALIAN_GUARD; 

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <filter_funs.h>
#include "/std/combat/combat.h"
#include <composite.h>
#include <formulas.h>
#include <cmdparse.h>


void
arm_me()
{
	clone_object(TUNNELS_ARMS+"cr_bracers.c")->move(TO);
	clone_object(TUNNELS_ARMS+"cr_greaves.c")->move(TO);
	clone_object(TUNNELS_ARMS+"crystal_armour.c")->move(TO);
	clone_object(TUNNELS_WEAP+"crystal_sword.c")->move(TO);
	clone_object(GLYKRON_OBJECTS+"calian_medallion.c")->move(TO);
	command("wear all");
	command("wear medallion");
	command("wield all");
}


string
my_default_answer()
{
    command("say I don't know what you're talking about.");
    return "";
}


void
create_calian()
{
	if (!IS_CLONE)
		return;
        add_name("guard");
	set_adj("tall");
	set_race_name("human");
	set_long("This is a tall, fierce human, who seems very "+
		"determined in " + query_possessive() + " task of guarding " +
                "this tunnel.  Every "+
		"now and then, " + query_pronoun() + " looks out through " +
                "a peephole in the "+
		"door.  It looks like " + query_pronoun() + " has been at " +
                query_possessive() + " post for "+
		"a long time, since " + query_pronoun() + " looks a " +
                "little scruffy.\n");

	set_act_time(20);
	add_act("emote scratches " + query_possessive() + " chin and " +
                "mutters distractedly.", 0);
	add_act("eyebrow all", 0);
	add_act("emote stands with " + query_possessive() + " arms crossed " +
                "and stares straight ahead.", 0);

	set_chat_time(15);
	add_chat("I might tell you who is outside, if you ask me.");
	add_chat("You can ask me to open the door.");

	add_ask(OPEN_DOOR, VBFC_ME("open_door"),1);
	add_ask(QUESTIONS, VBFC_ME("peek_out"), 1);
        set_default_answer(VBFC_ME("my_default_answer"));
	set_base_stat(SS_STR, random(50)+100);
	set_base_stat(SS_DEX,random(50)+100);
	set_base_stat(SS_CON, 200);
	set_base_stat(SS_INT, random(50)+100);
	set_base_stat(SS_WIS, random(50)+100);
	set_base_stat(SS_DIS, random(50)+100);
        set_base_stat(SS_OCCUP, 130);

	set_skill(SS_WEP_SWORD, 100);
	set_skill(SS_DEFENCE, 100);
	set_skill(SS_UNARM_COMBAT, 100);
	set_skill(SS_BLIND_COMBAT, 100);
	set_skill(SS_AWARENESS, 100);
	set_all_hitloc_unarmed(query_average_stat() /5);

	set_alignment(1200);
	set_aggressive(0);
	add_prop(CONT_I_WEIGHT, random(25000)+50000);
	add_prop(CONT_I_VOLUME, random(25000)+50000);
	add_prop(LIVE_I_QUICKNESS, 100);
        add_prop(NPC_I_NO_RUN_AWAY, 1);
	enable_commands();
}


string
open_door()
{
        if (environment(TP) != environment(this_object()))
             return "";

        tell_room(environment(this_object()), QCTNAME(this_object()) +
              " opens the door and pushes " + QTNAME(TP) +
              " through.\n", TP);
        TP->catch_msg(QCTNAME(this_object())+" opens the door and " +
              "pushes you through.\n");
	set_alarmv(1.0, 0.0, "push_out", ({TP}));
	return "";
}

void
move_out(object player)
{
    tell_room(environment(this_object()), 
        QCTNAME(player)+" leaves out the door!\n", player);
    player->catch_msg("You leave out the door.\n");
    player->move_living("M", SOUTH_EXIT,1);
    tell_room(environment(player), QCTNAME(player)+" arrives.\n", player);
}


void
push_out(object tp)
{
    int i;
    object *team, *m_team;

    if (environment(tp) != environment(this_object()))
        return;

    team = tp->query_team();

    m_team = ({ });
    for (i = 0; i < sizeof(team); i++)
        if (environment(tp) == environment(team[i]))
            m_team += ({team[i]});

    move_out(tp);
    for (i = 0; i < sizeof(m_team); i++)
        move_out(m_team[i]);
}


string
peek_out()
{
        object next_room;
	object *people;
	object *lst;
	int n;

	people = ({});
	lst = ({});
	write("The guard peers suspiciously out the peephole.\n");
	say("The guard peers suspiciously out the peephole.\n");
	if((next_room = find_object(SOUTH_EXIT)) != 0)
		lst += all_inventory(next_room);
	if (lst && sizeof(lst) > 0)
		people = FILTER_LIVE(lst);
	if (!sizeof(people))
	{
		write("I see no one out there now.\n");
		say("The guard whispers something to "+QCTNAME(TP)+".\n");
		return "";
	}
/* else */
	write("I see "+COMPOSITE_LIVE(people)+" just outside the door!\n");
	say("The guard whispers something to "+QCTNAME(TP)+".\n");
	return "";
}
