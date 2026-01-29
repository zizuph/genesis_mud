/*
 * /d/Gondor/anorien/osgiliath/ferry/ferryman.c
 *
 * Original version by Olorin
 *
 * Last modification: 24-Nov-1996 by Olorin
 *
 * This version:
 * Copyright (c) 1996 by Christian Markus
 */
#pragma strict_types

#include "/d/Gondor/defs.h"
inherit NPC_DIR + "npc_ranger";
inherit "/lib/trade";

#include <formulas.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#define KNOCKED_BY_FERRYMAN    "_knocked_by_ferryman"
#define LIVE_I_UNCONSCIOUS    "_live_i_unconscious"
#define	SAVE_FILE	ANO_DIR + "osgiliath/ferry/ferrysave"

static object  ship;
string	*AttackerList = ({ });

/* prototypes */
void	do_die(object killer);
void	set_ship(object s);
void	create_ranger();
void	arm_me();
void	init_living();
void	throw_into_river(object tp);
void	do_attack(object victim);
string *add_attacker(mixed att);
string *remove_attacker(mixed att);
int	did_attack(string name);
void	attacked_by(object ob);
public string *query_attackerlist();
void	remove_badge(object badge, object victim);
int	query_knight_prestige();
int	ranger_test(object tp);
int	badge_test(object tp);
int	enemy_test(object tp);
string	default_answer();
string	ask_road();
string	ask_damrod();
string	ithilien();
string	ask_anduin();

/*
 * Function name:	do_die
 * Description	:	do NOT die. try to throw enemies in river, too
 * Arguments	:	object killer -- our would-be killer
 */
void
do_die(object killer)
{
    object	env = ENV(TO),
		*enemies;
    string	name;
    int		s;

    if ( objectp(killer) && ENV(killer) == env )
    {
	if (!stringp(name = killer->query_name()))
	    name = file_name(killer);
	throw_into_river(killer);
    }
    else
    {
	enemies = query_enemy(-1);
	s = sizeof(enemies);
	while ( s-- > 0 )
	{
	    if ( ENV(enemies[s]) == env )
	    {
		if (!stringp(name = enemies[s]->query_name()))
		    name = file_name(enemies[s]);
		throw_into_river(enemies[s]);
	    }
	}
    }
    heal_hp(2000);
}

void
set_ship(object s)
{
    ship=s;
}

void
create_ranger()
{
  set_name("ferryman");
  set_race_name("human");
  add_adj("weather-beaten");
  add_adj("strong");
  set_company("Ithilien");
  set_long(BS(
    "This weather-beaten strong ranger ferries other rangers across " +
    "the Anduin. If you are no ranger, but have the Steward's leave to " +
    "go to Ithilien, he will help you too.\n"));
  set_stats(({ 100, 95, 90, 60, 60, 90 }));
  set_base_stat(SS_OCCUP,70);
  set_skill(SS_WEP_SWORD, 75);
  set_skill(SS_SWIM, 100);
  set_skill(SS_LOC_SENSE,100);
  set_skill(SS_AWARENESS,100);
  set_skill(SS_UNARM_COMBAT,90);
  set_skill(SS_DEFENCE,80);
  set_skill(SS_PARRY,60);
  set_skill(SS_BRAWLING,50+random(20));
  set_skill(SS_HEARING,50+random(20));

  set_alignment(1000);


  set_chat_time(5);
  add_chat("I wonder how long before the war breaks out.");
  add_chat("Damrod and Meneldil crossed the river here two days ago.");
  add_chat("Be always on guard in Ithilien! It's dangerous there!");
  add_chat("Haradrim troops are marching north on the road to the Morannon!");
  add_chat("The rangers of Ithilien are watching the road to the Morannon.");
  add_chat("We keep this ferry running for times of danger.");
  add_chat("I wonder why Damrod and Meneldil haven't been relieved yet.");
  add_chat("Don't use the road from the crossroads to the Morannon, "+
	"it's too dangerous!");
  set_cchat_time(11);
  add_cchat("Stop it, you pestering dog!");
  add_cchat("Give it to me, big-nose!");
  add_cchat("I'm gonna smack you so hard....");
  set_cact_time(5);
  add_cact("brawl");
  set_default_answer(VBFC_ME("default_answer"));
  add_ask(({"road","morannon"}), VBFC_ME("ask_road"));
  add_ask(({"damrod","meneldil"}), VBFC_ME("ask_damrod"));
  add_ask(({"ithilien"}), VBFC_ME("ithilien"));
  add_ask(({"anduin","river"}), VBFC_ME("ask_anduin"));


  seq_new("do_things");
  seq_addfirst("do_things","@@arm_me");

}

void
arm_me()
{
  seteuid(getuid(TO));
  clone_object(ITH_DIR + "obj/rlsword")->move(TO);
  command("wield sword");
  clone_object(ITH_DIR + "obj/rcloak")->move(TO);
  command("wear cloak");
  clone_object(ITH_DIR + "obj/rhood")->move(TO);
  command("wear hood");
  command("mask me");

  FIX_EUID
  restore_object(SAVE_FILE);
}

/* solemnian knights prestige */
int    query_knight_prestige() {return -15;}

void
throw_into_river(object tp)
{
    mixed   river_room;
    object  env = ENV(TO);


    if (!stringp(river_room = ENV(TO)->query_river_file()))
        return;


    FIX_EUID
    river_room->load_me();
    if (!objectp(river_room = find_object(river_room)))
        return;

    command("shout I'll remember this, you devil!");

    tp->add_fatigue(tp->query_max_fatigue() / -4);
    tp->add_prop(KNOCKED_BY_FERRYMAN, tp->query_prop(KNOCKED_BY_FERRYMAN) + 1);
    if (tp->query_prop(KNOCKED_BY_FERRYMAN) > 4)
    {
        tp->catch_msg(QCTNAME(TO)
	  + " knocks you on the side of the head with "
          + "the blade of his sword, and you fall unconscious "
          + "into the river!\n");
        tp->stop_fight(TO);
        stop_fight(tp);
        tp->add_prop(LIVE_I_UNCONSCIOUS, 1);
        tell_room(river_room, QCTNAME(tp)
	  + " falls limply from the platform "
          + "and into the river!\n");
        tp->move_living("M", river_room, 1, 0);
        tell_room(ENV(TO), QCTNAME(TO)
	  + " knocks " + QTNAME(tp) + " hard "
          + "in the head, and " + PRONOUN(tp)
	  + " falls limply into the river.\n");
    }
    else
    {
        tp->catch_msg(QCTNAME(TO)
	  + " knocks you on the side of the head with his "
          + "sword, and gives you a mighty shove!\n"
          + "You fall into the river with a great splash!\n");
        tp->stop_fight(TO);
        stop_fight(tp);
        tell_room(river_room, QCTNAME(tp)
	  + " is pushed into the river by somebody on the platform!\n");
        tp->move_living("M", river_room, 1, 0);
        tell_room(ENV(TO),QCTNAME(TO)+" shoves "
	  + QTNAME(tp)+" into the river!\n");
    }
}

void
do_attack(object victim)
{
    command("mask me");

    if (!present(victim, ENV(TO)) || !CAN_SEE(TO, victim) ||
    !CAN_SEE_IN_ROOM(TO))
        return;

    throw_into_river(victim);
}

void
attacked_by(object ob)
{
    ::attacked_by(ob);

    add_attacker(ob);
    throw_into_river(ob);
}

string *
add_attacker(mixed att)
{
    string name;

    if (objectp(att))
    {
	name = att->query_name();
    }
    else if (stringp(att))
    {
	name = CAP(att);
    }

    if (strlen(name) &&
        !did_attack(name))
    {
	AttackerList += ({ name });
	FIX_EUID
	save_object(SAVE_FILE);
    }
    return AttackerList;
}

string *
remove_attacker(mixed att)
{
    string name;

    if (objectp(att))
    {
	name = att->query_name();
    }
    else if (stringp(att))
    {
	name = CAP(att);
    }

    AttackerList -= ({ name });
    FIX_EUID
    save_object(SAVE_FILE);
    return AttackerList;
}

	

int
did_attack(string name)
{
    return (member_array(name, AttackerList) >= 0);
}

public string *query_attackerlist() { return AttackerList; }

void
remove_badge(object badge, object victim)
{
    string  owner = badge->query_prop("_ithilien_leave_name");

    command("mask me");
    command("say That badge doesn't belong to you!");

    if (owner == victim->query_real_name())
        owner = "your";
    else
        owner = CAP(owner) + "'s";

    victim->catch_msg(QCTNAME(TO) + " takes away "+owner+" badge from you.\n");
    tell_room(ENV(TO), QCTNAME(TO)+" takes away a badge from "
      + QCTNAME(victim)+".\n", victim);
    badge->move(TO);
    command("emote breaks the badge.");
    badge->remove_object();
}

int
ranger_test(object tp)
{
    if (!objectp(tp))
        return 0;

    if (!IS_RANGER(tp))
        return 0;

    if (interactive(tp))
        command("unmask me");
    return 1;
}

int
badge_test(object tp)
{
    int     i,
            good_badge = -1;
    object *badge,
            cap;

    if (!sizeof(badge = filter(all_inventory(tp), &->id("_ithilien_badge"))))
        return 0;

    // the player has at least one badge, now check validity
    for (i = 0; i < sizeof(badge); i++)
    {
        if (badge[i]->query_prop("_ithilien_leave_name") ==
	tp->query_real_name())
            good_badge = i;
    }

    // remove non-valid badges
    if (good_badge >= 0)
        badge -= ({ badge[good_badge] });
    for (i = 0; i < sizeof(badge); i++)
        remove_badge(badge[i], tp);

    // no valid badge
    if (good_badge == -1)
    {
        do_attack(tp);
        command("say Dirty thief!");
        tp->add_prop("_no_pass_to_ithilien", 1);
        return 0;
    }

    if (tp->query_prop("_no_pass_to_ithilien"))
    {
        command("peer " + tp->query_real_name());
        return 1;
    }

    return 1;
}

int
enemy_test(object tp)
{
    if (IS_EVIL(tp))
        return 1;
    return 0;
}

string
default_answer()
{
  if (ranger_test(TP) || badge_test(TP))
  {
    command("say I'm not here to answer questions!");
    command("say If you want to cross the Anduin, just board the ferry.");
    command("say I will ferry you across - but only if it is dark.");
  }
  else if (enemy_test(TP))
    do_attack(TP);
  else if (query_attack() != TP)
  {
    command("say You don't have any business in Ithilien!");
    command("say You'd better leave!");
    command("suspicious " + TP->query_real_name());
  }
  return "";
}

string
ask_road()
{
  command("sigh");
  command("say I guess you mean the road to the Morannon?");
  command("say At the foot of the Ephel Duath, there is an ancient road");
  command("say running north towards the Black Gate of Mordor, the Morannon!");
  command("say On this road, these days armies from Harad are marching north");
  command("say to swell the forces of Mordor, alas!");
  command("sigh");
  command("say We rangers sometimes ambush them, but we are not enough in ");
  command("say numbers to stop them!");
  command("say So, most of the time, there are only a few of us, "+
	"watching the ");
  command("say road, and reporting how many of the Haradrim march north.");
  command("say Right now, Damrod and Meneldil should be on that post.");
  return "";
}

string
ask_damrod()
{
  command("smile");
  command("say Damrod and Meneldil are good friends of mine!");
  command("say I ferried them across the river only two days ago!");
  command("say They came from Minas Tirith, and were on their way to the ");
  command("say post guarding the road to the Morannon.");
  command("say Actually, I'm expecting them back as soon as they "+
	"are relieved.");
  command("think");
  command("say They should report back to Minas Tirith, but since we are so ");
  command("say few only, they might have to wait several days until "+
	"they are relieved!");
  command("say Poor guys! So long on duty, without the chance to get "+
	"anything warm to eat!");
  command("say If you are looking for them, look on top of the ridge "+
	"west of the road");
  command("say to the Morannon. It's close to the small lake in "+
	"Northern Ithilien!");
  return "";
}

string
ithilien()
{
  command("sigh");
  command("say Ithilien! Once it was called the Garden of Gondor!");
  command("say Now it lies under the shadow of Mordor!");
  command("say Orcs and Haradrim live there now instead of Gondorians!");
  command("say Be careful if you travel there!");
  command("say If you want to go north, use the river road "+
	"along the Anduin, ");
  command("say but don't use the road to the Morannon! ");
  command("say If you follow the road east from the crossroads, ");
  command("say you will come to Minas Morgul, the city of the nazgul.");
  command("emote shivers with terror.");
  return "";
}

string
ask_anduin()
{
  command("say The river Anduin is the mightiest river in Middle Earth!");
  command("say Its sources are far north in the Ered Mithrin.");
  command("say From there, the Anduin flows south more than 1500 miles");
  command("say to its mouths in the Bay of Belfalas.");
  command("say From where the Limlight flows into the Anduin, the Anduin is ");
  command("say the eastern border of Rohan until it reaches "+
	"the falls of Rauros!");
  command("say From there it runs between Anorien and Ithilien.");
  command("say But, alas, since Ithilien has fallen to Mordor, the Anduin ");
  command("say is Gondor's line of defence!");
  command("say If the enemy manages to cross the river in force, ");
  command("say then, I fear, Minas Tirith will fall, too!");
  command("sigh");
  command("say But only over my dead body will this happen!");
  return "";
}

void
init_living()
{
    ::init_living();

    if (member_array(TO, TP->query_enemy(-1)) >= 0)
        set_alarm(1.0, 0.0, &throw_into_river(TP));
}
