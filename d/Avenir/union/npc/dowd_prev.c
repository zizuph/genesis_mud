/* Npc trainer for the Union */
//-*-C++-*-
// file name:     /d/Avenir/union/npc/dowd.c
// creator(s):    Cirion (c) Marc Prud'hommeaux
// purpose:       Trainer and Avenger
// note:          Clones by /d/Avenir/union/room/white.c
// last update:   Lilith   09 Sept 2001
//                Added plantilsi_amon function and attacks
//                SUMMONING & USING HIM COSTS THE FLAME 
// bug(s):
// to-do:   make sure that the following works

#include "../defs.h"

inherit "/d/Avenir/inherit/defeat";
inherit NPC + "npc";
inherit "/d/Genesis/magic/resist";

#include <tasks.h>

int alarm_id,
amon;

string i_follow; /* 0(empty string) = following nobody, */

void 
create_monster()
{
    set_name("dowd");
    set_living_name("dowd");
    set_race_name("human");
    set_adj("shadowy");

    set_long("His face seems veiled by shadows, an ancient "
      +"enigma, unchanging.\n");

    /* This is Dowd, the ultimate warrior of shadow */
    set_stats(({ 200, 200, 255, 225, 226, 150 }));

    set_gender(G_MALE);
    set_appearance(75);
    set_alignment(0);
    set_union_npc();
    set_base_stat(SS_OCCUP, 400);

    set_skill(SS_LANGUAGE,      50);
    set_skill(SS_ACROBAT,       80);
    set_skill(SS_AWARENESS,     95);
    set_skill(SS_DEFENCE,       90);
    set_skill(SS_SWIM,          30);
    set_skill(SS_CLIMB,         61);
    set_skill(SS_LOC_SENSE,     80);
    set_skill(SS_PARRY,        100);
    set_skill(SS_WEP_MISSILE,  100);
    set_skill(SS_WEP_KNIFE,    150);
    set_skill(SS_WEP_SWORD,    150);
    set_skill(SS_SWAY,         150);
    set_skill(SS_FLING,        100);
    set_skill(SS_SLASH,        150);

    set_restrain_path(({"/d/Avenir/union/"}));
    set_monster_home("/d/Avenir/union/room/white");

    add_prop(LIVE_I_SEE_INVIS, 1 + random(4));
    add_prop(LIVE_I_SEE_DARK, 5);
    add_prop(LIVE_I_QUICKNESS, 80 + random(25));
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(LIVE_I_ATTACK_THIEF, 1);
    add_prop(NPC_I_NO_FEAR, 1);

    set_act_time(9);
    add_act("emote narrows his eyes.");
    add_act("emote draws the shadows close about him.");

    set_cact_time(3);
    add_cact("assist");
    add_cact("drop ogre items");
    add_cact("kill ogre");
    add_cact("emote glares about him with icy rage.");
    add_cact("emote is in a blood-rage the likes of which "+
      "you have never seen before.");
    add_cact("emote dances with incredible grace and "+
      "speed as he lays about him with his sword.");
    add_cact("emote shifts like a shadow, always just beyond reach.");
    add_cact("emote fades from sight for a long moment.");
    add_cact("say I am the flame-shadow which dances at the edges "+
      "of your sight.");

    add_ask(({ "help" }), "say When you require assistance, "+
      "you need only to say the words.", 1);
    add_ask(({ "hmm" }), "say Hmm indeed.", 1);
    add_ask(({ "key" }), 
      "say The keys are many. Keys are answers. "+
      "What is the question?", 1);
    add_ask(({ "task" }), "say I have none.", 1);
    add_ask(({ "amon", "Amon" }), 
      "say An innocuous word, of itself. It means: in strength.", 1);
    add_ask(({ "dowd", "Dowd" }), 
      "say It is the name by which I may be Called", 1);
    add_ask(({ "plantilsi", "Plantilsi" }),
      "say Such is a word of power. It is the equivalent of "+
      "Calling a Name three times, a summoning that cannot "+
      "be ignored.", 1);
    add_ask(({ "plantilsi amon", "plantilsi amon dowd"}),
      "say Utter that phrase in my presense only in direst "+
      "need. With it you may Call me fully from the Shadows, "+
      "and with me all the glory of the Flame shall fight at "+
      "your side.", 1);  
    add_ask(({ "return", "return home", "leave", "leave me" }), 
      VBFC_ME("do_leave"), 1);
    add_ask(({ "follow me", "join me", "follow", "join", "team"}),
      VBFC_ME("follow"));
    trig_new("%w 'leaves' %s", "follow_player");
    trig_new("%w 'limps' %s", "follow_player");

}

void 
arm_me()
{
    object arm;

    seteuid(getuid(TO));

    arm = clone_object(OBJ+"combat_veil");
    arm->move(TO);
    arm = clone_object(OBJ+"shirt");
    arm->move(TO);
    arm = clone_object(OBJ+"pants");
    arm->move(TO);
    arm = clone_object(OBJ+"boots");
    arm->move(TO);
    arm = clone_object(OBJ+"cape");
    arm->move(TO);
    arm = clone_object(OBJ+"gloves");
    arm->move(TO);
    arm = clone_object(OBJ+"knife");
    arm->move(TO);
    arm = clone_object("/d/Avenir/common/dead/obj/falcata");
    arm->move(TO);

    command("wear all");
    command("veil me");
    command("wield all");

    update_hooks();
    TO->set_union_sphere("flame");
}


void 
leave()
{
    object rom;

    seteuid(getuid());
    rom = clone_object("/std/room");
    command("emote closes his eyes in the Sway and "+
      "becomes one with the shadows.");
    move(rom);
}

/* Called when a union member asks him to leave or return */
string
do_leave()
{
    if (!IS_MEMBER(TP))
    {
	command("say Alas, I can only take your meaning to be "+
	  "that you wish me to help you die.");
	command("kill "+ TP->query_real_name());
	return "";

    }
    else
    {
	command("ectios");
	command("say May your passion feed the Flame, my other self");
	set_alarm(5.0, 0.0, leave);
	return "";
    }
    return "";    
}


/* I have been summoned for war */
void 
plantilsi_amon()
{
    command("sway");
    set_aggressive(1);
    set_alarm(2000.0, 0.0, leave);
}


void 
add_introduced(string str)
{
    // Don't return intro
}

/* 
 *  I'll attack if I'm not busy killing
 * someone else right now.
 */
void
do_slay(object victim)
{
    if(query_attack())
    { 
	return; 
    }  // always concentrate on fighting

    command("kill "+ victim->query_real_name());
    command("us Abrud charus amon Jazur!");
}

/* Should I attack this person? */
int
do_this_check()
{
    /* Reset. (See init_living) */
    alarm_id = 0;

    if (TP->query_prop("_i_summoned_dowd"))
    {
	TP->remove_prop("_i_summoned_dowd");

	if (IS_MEMBER(TP) || FRIEND(TP))
	{
	    command("bow "+ TP->query_name());
	    command("say I am here, amon. ");
	    command("say There is a price to be "+
	      "paid for Calling me. That price is blood and "+
	      "Fire.");
	    command("say You have but to ask me to follow, "+
	      "and you may lead me to those who must die.");
	}
	else
	{
	    command("say I am here, amon. There is a price to be "+
	      "paid for Calling me. That price is your blood.");
	    command("kill "+ TP->query_name());      
	}
    }    

    if(query_attack())
    { 
	return 0; 
    }   // always concentrate on fighting

    if (IS_MEMBER(TP) || FRIEND(TP))
    {
	return 0;
    }   // do not kill my own

    if(ENEMY(TP) || IS_INFIDEL(TP))
    {
	return 1;
    }   // attack enemies of the guild and sybarus

    if (TP->query_race() == "ogre" || 
      TP->query_race() == "dark elf")
    {
	return 1;
    }   // attack our historical enemies    

}


/*
 * Function name: init_attack
 * Description:   Called from init_living() in monster.c
 */
public void
init_attack()
{
    int i = check_call(monster_aggressive);
    if (!i) 
	return;
    if (alarm_id)
	return;
    if (do_this_check()) 
	alarm_id = set_alarm(itof(random(4) + 1), 0.0, 
	  &do_slay(this_player()));
}

void 
init_living()
{
    ::init_living();

    if (alarm_id)
	return;

    if (do_this_check()) 
	alarm_id = set_alarm(itof(random(4) + 1), 0.0,
	  &do_slay(this_player()));

}


/*
 * Flame burn
 */
void 
flame_burn(object victim)
{
    int resistance;

    /* Check the target's magic resistance */
    resistance = spell_resist_basic(this_object(), victim, 
      SS_ELEMENT_FIRE, TASK_ROUTINE);

    /* Do the extra damage, taking the magic resistance into account */
    victim->hit_me(300 * (100 - resistance) / 100, MAGIC_DT,
      this_object(), -1);

    victim->catch_msg(QCTNAME(TO)+"'s sword courses with a black "+
      "flame that singes your very soul as it slices through your "+
      "flesh.\n");
    tell_room(ENV(TO), QCTNAME(TO)+"'s sword courses with black "+
      "flame as he dances under "+ QTNAME(victim) +"'s guard and "+
      "deals "+victim->query_objective() +" a soul-shattering "+
      "blow!\n", victim);

    /* Kill the target, if appropriate */
    if (victim->query_hp() <= 0)
	victim->do_die(this_object());

    /* This maneuver costs the Flame some of its strength */
    //    HOME->change_state(-50, 1);

}

/*
 * Heal, but not until down 50% hp
 */
void 
heal_me()
{
    int hp;

    hp = query_max_hp() / 2;
    if (query_hp() > hp)
	return;

    heal_hp(hp);
    command("emote cries out: Turas amon Jazur");
    command("emote seems greatly strengthened.");

    /* This maneuver costs the Flame some of its strength */  
    ("/d/Avenir/union/room/guild")->change_state(-200, 1);
}

/* 
 *  Deadly attacks.
 */
int
special_attack(object victim)
{
    if (ENV(victim) != ENV(TO) || victim->query_ghost())
    {
	TO->stop_fight(victim);
	return 1;
    }

    switch (random(45))
    {
    case 0: 
	{ 
	    flame_burn(victim);
	    command("slash"); 
	}                          
	return 0;        
    case 1: 
	{
	    command("sway");
	    command("slash");
	}
	return 0;
    case 2: heal_me();
	return 0;
    default: 
	command("slash");
    }
    return 0;
}


/* These functions ensure that he will follow */
string 
remove_nl_endpunc(string parm) 
{
    /* removes a new line and ending punctuation from the end of a string */
    /* borrowed from slave.c .. Zima                                      */

    string lastlet;
    int    lastpos;

    lastpos=strlen(parm)-1;
    lastlet=extract(parm,lastpos,lastpos);
    if (lastlet="\n")
	parm=extract(parm,0,(lastpos-1));

    lastpos=strlen(parm)-1;
    lastlet=extract(parm,lastpos,lastpos);
    if ((lastlet="!")||(lastlet=".")||(lastlet="?"))
	parm=extract(parm,0,(lastpos-1));

    return parm;
}


void
do_follow(string where)
{
    command(where);
}


int
follow_player(string who, string where)
{
    who = lower_case(who);

    if (!i_follow)
	return 1;

    where = remove_nl_endpunc(where);

    if (who == i_follow)
	set_alarm(1.0, 0.0, &do_follow(where));

    return 1;
}

string
follow()
{
    string who;
    string mout;

    if (i_follow)
	return "";

    if (!present(this_player(), environment(this_object())))
	return "";

    if (!IS_MEMBER(TP))
    {
	command("say Surely you jest?");
	return "";  
    }

    who = lower_case(TP->query_name());
    mout = TP->query_m_out();

    i_follow = who;

    command("dignity");
    command("say I am ready to do that which I have been "+
      "Summoned for. Lead on.");
    command("whisper to "+ who +" I rarely leave this place. "+
      "To prevent confusion as I try to follow you, make "+
      "sure that I can clearly see you leaving a room. "+
      "No limping, hip swaying, or other distractions.");
    return "";
}

public string
query_i_follow()
{
    return i_follow;
}


