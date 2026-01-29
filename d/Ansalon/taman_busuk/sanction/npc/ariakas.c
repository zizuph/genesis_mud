/*
ariakas.c
=========

Coded by: Arman. Basic structure copied off Bakaris.c
*/
#pragma save_binary
#pragma strict_types

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include "/d/Ansalon/guild/dragonarmy/guild.h"
#include <ss_types.h>
#include <macros.h>
#include <poison_types.h>
#include <composite.h>

inherit AM_FILE

#define PLAINS "/d/Krynn/solamn/splains/obj/"
#define TPRIEST(p1)  (p1->query_guild_member("Priests of Takhisis"))

int is_dying = 0;

void
create_krynn_monster()
{
    setuid();
    seteuid(getuid());

    set_race_name("human");
    set_living_name("ariakas");
    set_adj(({"powerful","arrogant"}));
    set_name(({"ariakas","highlord"}));
    set_gender(0);
    set_title("the Emperor of Krynn, Highlord of the Red Dragonarmy");
    set_long("This huge human before you is Ariakas, the highest " +
      "of the Dragon Highlords, answering only to Takhisis herself. A " +
      "competent fighter and skilled magic-user, he radiates " +
      "immense power. You doubt you've met a more powerful " +
      "individual... ever.\n");
    set_knight_prestige(4000);

    set_stats(({240, 300, 300, 170, 170, 200}));
    set_base_stat(SS_OCCUP, 200);

    set_skill(SS_AWARENESS, 70);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_WEP_CLUB, 120);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 80);
    set_skill(SS_DRAGONARMY_ATTACK, 200);
    set_alignment(-3000);
    set_all_hitloc_unarmed(40);

    add_prop(CONT_I_HEIGHT, 185);

    add_prop(LIVE_I_QUICKNESS, 200);
    add_prop("_ranger_m_not_disarm",1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(OBJ_I_RES_POISON, 200);


}

void
attacked_by(object ob)
{
    command("say Fool! You shall die a horrible death for " +
      "your insolence!");
    command("shout Guards! To me!");
    E(TO)->summon_guards(ob);
    find_player("arman")->catch_msg("\n\n\nARIAKAS UNDER ATTACK!!!\n\n\n");

    ::attacked_by(ob);
}

void
arm_me()
{
    object arm1, arm2;

    clone_object(SOBJ + "ariakas_shield")->move(TO,1);
    clone_object(SOBJ + "weapon/mace")->move(TO,1);
    arm1 = clone_object(PLAINS + "bdragonarm");
    arm1->set_color("red");
    arm1->move(TO,1);
    clone_object(SOBJ + "armour/dragonmask")->move(TO,1);
    arm2 = clone_object(PLAINS + "bshinguard");
    arm2->set_color("red");
    arm2->move(TO,1);

    command("wear all");
    command("wield all");
}

int
special_attack(object ob)
{
    object poison;


    if((random(30) == 1) && (TO->query_hp() > 2000))
    {
	tell_room(E(TO), QCTNAME(TO)+ " points at " +QTNAME(ob)+
	  " and mutters a vile curse. "+QCTNAME(ob)+ " suddenly "+
	  "turns pale, and begins to choke.\n", ({TO, ob}));
	tell_object(ob, TO->query_The_name(ob)+ " points at you and mutters "+
	  "a vile curse of pure malevolence. You are poisoned!\n");

	poison = clone_object("/std/poison_effect");
	if(poison) {
	    poison->move(ob);
	    poison->set_time(600);
	    poison->set_short("magical poison");
	    poison->set_interval(13);
	    poison->set_strength(40);
	    poison->set_damage(({POISON_HP, 125}));
	    poison->start_poison();
	}
	return 1;
    }

    if((random(5) == 1) && (TO->query_hp() < 2000))
    {
	tell_room(E(TO), QCTNAME(TO) + " raises his hands into " +
	  "the air and calls out: Takhisis my Queen! Aid your servant!\n", TO);
	if(TO->query_mana() < 100)
	{
	    tell_room(E(TO), "Nothing seems to happen, and " +QTNAME(TO)+
	      " curses Takhisis vilely.\n", TO);
	    return 1;
	}
	else
	    tell_room(E(TO), "Suddenly, "+QTNAME(TO)+ " is surrounded " +
	      "by a black flame... He looks healed!\n", TO);
	TO->add_mana(-100);
	TO->heal_hp(10000);
	return 1;
    }
    return 0;
}

void
return_intro(object ob)
{
    int promos;
    string who;

    if(!present(ob, E(TO)))
    {
	return;
    }

    promos = ob->query_dragonarmy_promotions();
    who = ob->query_real_name();

    if(TPRIEST(TP))
    {
	command("say to " +who+ " Ah! A cleric of our Dark Queen "+
	  "to pay me a visit...");
	set_alarm(0.5, 0.0, &command("smile arrogant"));
    }
    else
	switch(promos)
    {
    case 4:
	command("smile slight");
	set_alarm(1.0,0.0, &command("say to "+who+ " It seems one "+
	    "of my Generals has come to pay me a visit. Greetings to " +
	    "you, "+capitalize(who)+ "."));
	break;
    case 3:
	command("nod respect " +who);
	break;
    case 2:
	command("say to "+who+ " Well met officer " +capitalize(who)+
	  ". What brings you to my chambers?");
	break;
    case 1:
	command("say to "+who+ " What is it soldier? I am a busy man.");
	set_alarm(1.5, 0.0, &command("eyebrow " +who));
	break;
    default:
	command("glare coldly " + who);
	set_alarm(1.0, 0.0, &command("say Who allowed this person into " +
	    "my presence?"));
	set_alarm(1.5,0.0, &command("say You had best not be wasting my " +
	    "time, for I am a man not to be trifled with."));
	set_alarm(2.0,0.0, &command("laugh arrogant"));
	break;
    }
    set_alarm(2.5, 0.0, &command("introduce me to "+who));
}

void
add_introduced(string str)
{
    object ob = find_player(lower_case(str));
    if(ob && !ob->query_met(TO))
    {
	set_alarm(1.0, 0.0, &return_intro(ob));
    }
}

void
emote_hook(string emote, object actor, string adverb)
{
    switch(emote)
    {
    case "kick":
	if(!TO->query_attack())
	{
	    command("shout You will never do this again!");
	    command("kill "+actor->query_real_name());
	    E(TO)->summon_guards(actor);
	}
	break;
    }
}

private void
real_do_die( object killer )
{
    if(!is_dying)
	return;
    heal_hp(-10000);
    ::do_die(killer);
}

void
do_die( object killer )
{
    if (is_dying || query_hp() > 0)
	return;

    is_dying = 1;
    set_alarm(0.0, 0.0, &command("glare angrily "+ killer->query_real_name()));
    set_alarm(1.0, 0.0, &command("say You think you can so easily defeat me? " +
	"The most powerful servant of the Dark Queen?"));
    set_alarm(1.5, 0.0, &command("laugh coldly "+ killer->query_real_name()));
    set_alarm(2.5, 0.0, &command("emote slumps to the floor and stiffens."));
    set_alarm(3.0, 0.0, &command("emote curses violently."));
    set_alarm(4.0, 0.0, &command("say Bah! Betrayed in the end..."));
    set_alarm(5.0, 0.0, &command("sigh ."));

    set_alarm(5.5, 0.0, &real_do_die(killer));
}

void
catch_question(string str)
{
    string question, answ;
    mixed minfo;

    if(!TP->check_seen(TO) || !CAN_SEE_IN_ROOM(TO))
    {
	set_alarm(rnd()*3.0 + 1.0, 0.0, &command("emote peers around puzzled."));
	return;
    }

    if(TP->query_dragonarmy_division() != "red" && !TP->query_met(TO))
    {
	set_alarm(rnd()*3.0 + 1.0, 0.0, &command("say to "+
	    TP->query_real_name()+" Who are you stranger?"));
	return;
    }

    if(!parse_command(str, ({}), "[about] [the] %s", question))
    {
	set_alarm(rnd()*3.0 + 1.0, 0.0, &command("say to "+
	    TP->query_real_name()+" I do not understand your question."));
	return;
    }
    question = lower_case(question);
    if(question == "ariakas")
    {
	set_alarm(rnd()*3.0 + 1.0, 0.0, &command("say to "+
	    TP->query_real_name()+" He is the most powerful man " +
	    "on the face of this planet, and you now speak to him. Be " +
	    "honoured!"));
	return;
    }

    if (question == "dragonarmy" || question == "blue dragonarmy" ||
      question == "army" || question == "blue army" ||
      question == "info" || question == "information" || question == "informations" ||
      question == "join" || question == "leave" ||
      question == "join dragonarmy" || question == "join blue dragonarmy" ||
      question == "join army" || question == "join blue army" ||
      question == "leave dragonarmy" || question == "leave blue dragonarmy" ||
      question == "leave army" || question == "leave blue army" ||
      question == "join red dragonarmy" || question == "join red army" ||
      question == "red dragonarmy" || question == "red army")
    {
	set_alarm(2.0, 0.0, &command("say to "+TP->query_real_name()+
	    " Do not bother me with your inane questions! If you " +
	    "want to learn of my armies, go speak to my clerk in " +
	    "the city."));
	return;
    }

    /*The clerk gives out promotions now*/
    if (question == "promotion" || question == "for promotion" ||
        question == "for a promotion" || question == "promote" ||
        question == "promote me" || question == "please promote me")
    {
        if (TP->query_dragonarmy_promotions() != 1) {
            set_alarm(2.0, 0.0, &command("say to "+OB_NAME(TP)+
                " Only Soldiers can request a promotion, imbecile!"));
            return;
        }

        set_alarm(2.0, 0.0, &command("say to "+OB_NAME(TP)+
            " I can't be bothered with such mundane issues.  "+
            "Talk to my clerk in the city about such things."));
        return;
    }


    set_alarm(2.0, 0.0, &command("say to "+TP->query_real_name()+
	" I am too busy to bother with such things."));
}
