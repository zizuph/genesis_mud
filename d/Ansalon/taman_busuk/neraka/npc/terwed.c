/* Ashlar, 30 Aug 97
   Terwed Ferin, master of joining ceremonies, trainer of certain skills.
   "Resides" in the Dark Abbey.
   Answers questions about the guild.
 */

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <cmdparse.h>
#include <money.h>
#include <filter_funs.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include "/d/Ansalon/taman_busuk/neraka/guild/guild.h"
#include "/d/Ansalon/taman_busuk/neraka/guild/spells.h"

inherit AM_FILE

#define ARM1 MEDALLION_OBJ

#undef DEBUG
#define DEBUG(x)    (find_player("ashlar")->catch_msg("PRIEST: " + x + "\n"))

void arm_me();

string
query_guild_title_race()
{
    return "Ferin";
}

int
query_guild_family_name()
{
    return 1;
}

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("terwed");
    set_introduce(1);
    add_name("priest");

    set_race_name("human");
    set_adj("shabby");
    add_adj("old");
    set_long("This crooked, shabby old human is despite the outward " +
    "appearance a powerful Priest of Takhisis. From behind the cowl " +
    "of his old dirty robe, he studies you with cunning. He is here " +
    "to help those that need guidance, and have questions to ask.\n");

    add_prop(CONT_I_HEIGHT, 170);
    add_prop(CONT_I_WEIGHT, 55000);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_stats(({ 90, 130, 110, 160, 160, 110 }));
    set_hp(query_max_hp());

    set_skill(SS_WEP_CLUB,          70);
    set_skill(SS_DEFENCE,           55);
    set_skill(SS_PARRY,             50);
    set_skill(SS_AWARENESS,         65);
    set_skill(SS_SPELLCRAFT,        65);
    set_skill(SS_ELEMENT_LIFE,      65);
    set_skill(SS_ELEMENT_AIR,       65);
    set_skill(SS_FORM_DIVINATION,   65);
    set_skill(SS_FORM_ENCHANTMENT,  60);
    set_skill(SS_FORM_ABJURATION,   60);

    set_skill(PS_GUILD_LEVEL, 125);
    set_skill(PS_SPELLS, -1);

    set_all_hitloc_unarmed(10);

    set_alignment(-950);
    set_knight_prestige(950);

    set_act_time(13);
    add_act("say Have you come to worship the Queen of Darkness?");
    add_act("emote mutters a short prayer to the Queen of Darkness.");
    add_act("say I may have answers you seek.");

    set_cact_time(5);
    add_cact("say I curse you!");
    add_cact("sneer");
    add_cact("say The hatred of the Queen of Darkness will follow you to your grave!");

    set_default_answer(QCTNAME(TO) + " mutters: I can not help you with " +
    "that.\n");

    add_ask(" [for] 'help' / 'answers' ", "say I can help you. " +
        "Perhaps you are interested in the priesthood?", 1);
    add_ask(" [about] [the] 'priests' / 'priesthood' / 'guild' ",
        VBFC_ME("answer_guild"));
    add_ask(" [about] [the] 'background' ", VBFC_ME("answer_background"));
    add_ask(" [about] 'joining' ", VBFC_ME("answer_joining"));
    add_ask(" [about] 'leaving' ", VBFC_ME("answer_leaving"));
    add_ask(" [about] [the] 'goals' ", VBFC_ME("answer_goals"));
    add_ask(" [about] [lord] 'devrail' ", "say Alas! Most grievous the " +
    "day when word arrived that Lord Devrail was slain. His mission " +
    "successful, yet the price was high. Now he shelters in the " +
    "embrace of our Queen.", 1);
    add_ask(" [about] 'pray' / 'praying' ", "say You may pray to the " +
    "Queen of Darkness here, to gain her favour.", 1);
    add_ask(" [about] 'scroll' ", "say I am not the one to help you with " +
    "that. Ask someone else.", 1);

    add_ask(" [for] 'task' ", VBFC_ME("answer_task"));
}

void
arm_me()
{
    setuid();
    seteuid(getuid());

    clone_object(POTSHADOW)->add_occ_shadow(TO);

    TO->init_occ_shadow();

    clone_object(NARM + "black_chain_shirt")->move(this_object(), 1);

    command("wear all");
}

void
do_reward(string quest, object questobj, object quester, int reward)
{
    switch(quest)
    {
    	case "verminaard":
    	    command("say Excellent! I knew I could trust you to deliver this safely.");
    	    command("say I am sure you will find the Queen thankful as well.");
    	    quester->add_prop(POT_GOT_NEW_SPELL,"pslow");
    	    quester->set_skill(PS_SPELLS, quester->query_skill(PS_SPELLS) | PSLOW_ID);
    	    quester->set_skill(PS_SKILL_POINTS,
    	        quester->query_skill(PS_SKILL_POINTS) + reward);
    	    questobj->remove_object();
    	    break;
    	case "kalaman":
    	    quester->add_prop(POT_GOT_NEW_SPELL,"peyes");
    	    quester->set_skill(PS_SPELLS, quester->query_skill(PS_SPELLS) | PEYES_ID);
    	    quester->set_skill(PS_SKILL_POINTS,
    	        quester->query_skill(PS_SKILL_POINTS) + reward);
    	    quester->ks_remove_mission_shadow();
    	    break;
    }
}

void
give_back(object obj, object from)
{
    command("say That does not interest me.");
    command("drop " + obj->query_name());
}

void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    if (living(from))
        if(obj->id("verminaard_artifact"))
            set_alarm(2.0,0.0,&do_reward("verminaard", obj, from, 600));
        else if(!obj->query_no_show())
            set_alarm(1.0,0.0,&give_back(obj,from));
}

int
do_report(string str)
{
    int reward;
    
    if (!MEMBER(TP) || !TP->ks_query_has_mission())
        return 0;

    if (!TP->ks_query_mission_success())
    {
	write("You report your partial findings.\n");
    	command("sneer");
    	command("say I expect a full report, now go back and make sure " +
    	"you study everything I need to know.");
    	command("emote waves his hand in dismissal.");
    	return 1;
    }

    write("You report your findings.\n");
    if(TP->ks_query_kills() == 0)
    {
    	command("say Excellent! All details I needed, and you did not " +
    	"attract any attention.");
    	command("say That's full marks on this mission.");
    	reward = 300;
    }
    else if(TP->ks_query_kills() < 3)
    {
    	command("say Looks like you ran into some trouble, but still, " +
    	"you got what I needed.");
    	command("say You will be rewarded for this.");
    	reward = 200;
    }
    else
    {
    	command("say Is this what you call going unnoticed?");
    	command("fume");
    	command("say " + TP->ks_query_kills() + " dead! This will put the " +
    	"guard on full alert!");
    	command("say Your incompetence may have ruined our easy victory.");
    	command("say Still, your information seems accurate enough.");
    	command("say You will recieve one reward, but if you fail me like this again..");
    	command("say Suffice to say you will not like the consequences.");
    	command("emote mutters something about reckless incompetence.");
    	reward = 0;
    }
    do_reward("kalaman",TP,TP,reward);
    return 1;
}

void
init_living()
{
    ::init_living();
    add_action(do_report, "report");
}

string
answer_task()
{
    int spells;
    if (!TP || E(TP) != E(TO))
        return "";
        
    if (MEMBER(TP))
    {
    	spells = TP->query_skill(PS_SPELLS);

    	if ((spells & PSLOW_ID) == 0 &&
    	(TP->query_priest_level() > 0 || TP->query_priest_sublevel() >= 3))
    	{
    	    command("say I do have a thing for you. Verminaard, the " +
    	    "Highlord of the Red Dragonarmy, has reported that he " +
    	    "has managed to unearth a strange artifact.");
    	    command("say He thinks it is an item of great power.");
    	    command("say However, the treacherous elves of Qualinost " +
    	    "are waylaying his troops, so he dare not send the " +
    	    "artifact by the usual way. Instead, he requests that " +
    	    "a Priest of Takhisis come to fetch the artifact.");
    	    command("say I will give you a token to show to the " +
    	    "Highlord, and he will give you the artifact in return.");
    	    command("say Return and give it to me, and you will be rewarded.");
            if (!present("verminaard_token", TP))
            {
        	    clone_object(NERAKA + "guild/obj/verminaard_token")->move(TP, 1);
        	    TP->catch_msg(QCTNAME(TO) + " gives you a black metal token.\n");
            }
            else
            {
                command("say But I've told you all this before. Now go do it.");
            }
    	}
    	else if ((spells & PEYES_ID) == 0 &&
    	(TP->query_priest_level() > 0 || TP->query_priest_sublevel() >= 1))
    	{
    	    command("say We have recieved information that the Solamnian " +
    	    "Knights have, or are planning to, reinforce the guards of Kalaman.");
    	    command("say As you can understand, this disturbs our plans of the " +
    	    "imminent assault on that city.");
    	    command("say You will travel to Kalaman, and raising as little " +
    	    "suspicion as possible, you will study their defences.");
    	    command("say I will need information on how many men they have " +
    	    "guarding the palace, and how many they have in reserve in the " +
    	    "barracks.");
    	    command("say When you have visited all those places, return here " +
    	    "and report.");
    	    command("say And remember, stay unnoticed! Do not engage in combat " +
    	    "unless absolutely necessary.");
    	    if (!TP->ks_query_has_mission())
    	    {
    	        clone_object(NERAKA + "guild/obj/kalaman_shadow")->shadow_me(TP);
    	    }
    	}
    	else
    	{
            command("say I have no tasks for you at the moment.");
    	}
    }
    else
    {
    	command("say Only Priests of Takhisis are worthy of performing " +
    	"my tasks.");
    }
    	
    return "";
}

string
answer_guild()
{
    command("say The Priests of Takhisis, or more formally, the " +
    "Dedicated Priesthood of Takhisis, the Queen of Darkness, are " +
    "based within this temple. You may ask me further about " +
    "background, joining, leaving or goals.");
    return "";
}

varargs string
answer_background(int round = 0)
{
    switch(round)
    {
    	case 0:
        command("say The Priesthood was founded some 70 years ago to " +
        "enable the forces of the Dark Queen to use the old clerical " +
        "magic to aid her battles.");
        break;

        case 1:
        command("say After the Cataclysm, the old priesthood had " +
        "disappeared, and this new priesthood is based on the few " +
        "documents that survived the Cataclysm, as well as the " +
        "wishes the Queen of Darkness has let us know about.");
        break;

        case 2:
        command("say We have now grown into a powerful organisation, " +
        "and the time has come to emerge fully into the open, for now " +
        "is the battle of Krynn coming to a head.");
        break;
    }

    if (round < 2)
        set_alarm(3.0,0.0,&answer_background(round+1));
    return "";
}

varargs string
answer_joining(int round = 0)
{
    switch(round)
    {
    	case 0:
    	command("say To join you must find a priest willing to initiate " +
    	"you into the priesthood. As an initiate you will be paying " +
    	"a tax of " + ATAX + " percent of your experience.");
        break;

        case 1:
        command("say As you grow within the guild, you will become " +
        "more and more powerful, until one day the Queen of Darkness " +
        "will judge you fit to become a Priest. Your tax will then " +
        "rise to " + MTAX + " percent and you will gain new abilities.");
        break;

        case 2:
        command("say A word of warning! The way of the priest is not " +
        "for the weak. The Queen does not approve of weaklings and " +
        "losers, and she has ways to quickly dispose of them.");
        break;

        case 3:
        command("say With the recent death of Lord Devrail, we " +
        "are waiting for a new leader to emerge. Until such a time " +
        "only a select few may join us.");
    }

    if (round < 3)
        set_alarm(3.0,0.0,&answer_joining(round+1));
    return "";
}

varargs string
answer_leaving()
{
    command("say If you decide to leave the Priesthood, the Dark Queen " +
    "will remove her hand from you, and you will walk unprotected into " +
    "the world. Her blessings removed, you will lose all knowledge of " +
    "this temple, and with that knowledge, a substantial part of your " +
    "experience, close to that which Death himself exacts as payment!");
    return "";
}

varargs string
answer_goals(int round = 0)
{
    switch(round)
    {
    	case 0:
    	command("say The goals of the Priesthood have always been to " +
    	"aid the Queen of Darkness in her conquest of Krynn.");
        break;

        case 1:
        command("cough .");
        break;

        case 2:
        command("say To this end, we do battle with the forces of good " +
        "that opposes us.");
        break;

        case 3:
        command("say No one and no thing must stand in the way of the " +
        "Dark Queen of Krynn!");
    }

    if (round < 3)
        set_alarm(3.0,0.0,&answer_goals(round+1));
    return "";
}

int
second_life(object killer)
{
    setuid();
    seteuid(getuid());
    A_KILL_LOG("pot/npckills","Terwed",killer);
    return 0;
}

