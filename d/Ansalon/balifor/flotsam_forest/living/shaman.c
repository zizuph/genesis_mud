#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE
inherit AUTO_TEAM

#define ARM1 ARMOUR + "shield"
#define ARM2 ARMOUR + "l_gauntlets"
#define WEP  WEAPON + "spear"
#define PLAYER_I_FOUND_TAIL "_player_i_found_tail"

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_pick_up_team(({"centaur"}));
    set_max_team_size_auto_join(4);

    set_name("centaur");
    add_name("shaman");
    set_race_name("centaur");
    set_gender(G_MALE);
    set_short("centaur shaman");
    set_long("Before you sits an ancient centaur shaman. " +
      "He is the keeper of all the knowledge of this tribe, and " +
      "is held in awe and reverence by all his brethren.\n");

    set_stats(({115,100,125,89,89,96}));
    set_hp(10000);
    add_prop(OBJ_M_NO_ATTACK,"An aura of peace fills the " +
      "tent. You don't feel like attacking the centaur.\n");
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);

    set_alignment(500);
    set_knight_prestige(-200);
    set_skill(SS_WEP_POLEARM, 60);
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_PARRY, 50);
    set_skill(SS_AWARENESS,100);

    remove_attack(W_FOOTR);
    remove_attack(W_FOOTL);

    set_act_time(10);
    add_act("emote strokes his whispy beard thoughtfully.");
    add_act("say Greetings stranger.");


    add_ask(({"map","about map"}),"say A map? Well, " +
      "I cannot tell you about a map unless I know which " +
      "map you are talking about. Perhaps you could " +
      "give it to me?",1);
    add_ask(({"quest","about quest"}),"say Nay, I have " +
      "no epic quest or task that you would be interested " +
      "in, as I have no reward for someone like yourself.",1);
    add_ask(({"auld centaurish","Auld Centaurish"}),
      "say Auld Centaurish is the ancient language of the " +
      "centaurs of old. I am proud to say that I can still " +
      "read texts written in it.",1);
    add_ask(({"favour","favor"}),"say If you destroy the beast known " +
      "as a wyvern that plagues this land, and bring back " +
      "its tail as proof of your deed, I will be in your debt. " +
      "But be warned! This wyvern is one of the greater wyverns! " +
      "Its poison is deadly even to the great! If I were you " +
      "I would seek out a talisman that will protect you from " +
      "its deadly venom.",1);
    add_ask("talisman","say I made a talisman for a swordsman " +
      "from the North. He was going to hunt down the beast " +
      "for us.",1);
    add_ask("bogga","say I know not what you are talking " +
      "about.",1);
    add_ask("swordsman",
      "say The warrior was old, yet skilled with the blade. " +
      "Apart from that I can tell you little, as humans all " +
      "look alike to me.",1);
}

void
arm_me()
{
    seteuid(getuid(TO));
    clone_object(WEP)->move(TO,1);
    command("wield all");
    clone_object(ARM1)->move(TO,1);
    clone_object(ARM2)->move(TO,1);
    command("wear all");
}

int
special_attack(object enemy)
{
    int attacktype,
    pen,
    att,
    wloc;

    mixed hitres;

    string *hitloc,
    *attack,
    how;

    attacktype = random(5);

    if (attacktype == 1)
    {
	pen = 25 + random(25);
	hitres = enemy->hit_me(pen, 20,TO,-1);

	enemy->catch_msg(QCTNAME(TO) + 
	  " strikes you savagely with his front hooves!\n");
	tell_room(E(TO),QCTNAME(TO) + " strikes out at " +
	  OBJECTIVE(enemy) + " savagely with his hooves!\n",
	  ({enemy, TO }));

	if (enemy->query_hp() <= 0)
	{
	    enemy->do_die(TO);
	}
	return 1;
    }
    return 0;
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}

void
return_give_stinger(object from)
{
    command("gasp");
    command("say The tail of the wyvern! The centaur tribes " +
      "of the Goodlund Peninsula owe you a favour indeed! " +
      "I will translate the map for you now if you wish. All " +
      "you need to do is hand it over to me.");
    TP->add_prop(PLAYER_I_FOUND_TAIL,1);
}

void
return_give_map(object ob, object from)
{
    if(!from->query_prop(PLAYER_I_FOUND_TAIL))
    {
	string what, who;
	what = L(ob->query_short());
	who = from->query_real_name();
	command("say Hmm... yes, this map is written in " +
	  "Auld Centaurish. It is the directions that will take " +
	  "you through the magical mists to the fabled Hall of " +
	  "Heroes.");
	command("emote strokes his grey whispy beard.");
	command("say I will translate it for you, but in " +
	  "return you must do a favour for the tribe.");
	command("give " + what + " to " + who);
	command("give map to " + who);
    }
    if(from->query_prop(PLAYER_I_FOUND_TAIL))
    {
	command("emote pulls out a piece of parchment and " +
	  "starts copying the tattered map.");
	command("say Done!");
	write("The centaur shaman gives you a scroll.\n");
	say("The centaur shaman gives " + QTNAME(TP) +
	  "a scroll.\n");
	clone_object(FOBJ + "map2")->move(TP);
	command("say Good fortune!");
    }
}

void
give_it_back(object ob, object from)
{
    command("hmm");
    command("say What is this? Thank ye, but i do not need it.");
    command("give " + OB_NAME(ob) + " to " + OB_NAME(from));
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(ob->id("stinger"))
    {
	set_alarm(1.0,0.0, &return_give_stinger(from));
	return;
    }

    if(ob->id("_armour_quest_map"))
    {
	set_alarm(1.0,0.0, &return_give_map(ob, from));
	return;
    }

    set_alarm(1.0,0.0, &give_it_back(ob, from));
    return;
}
