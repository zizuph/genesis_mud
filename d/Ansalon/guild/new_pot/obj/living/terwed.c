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
#include <composite.h>
#include <files.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/new_pot/guild.h"
#include "/d/Ansalon/guild/new_pot/spells.h"
#include "npc.h"

inherit "/d/Ansalon/guild/new_pot/obj/living/npc";

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
create_pot_monster()
{
    if(!IS_CLONE)
	return;

    set_name("terwed");
    set_living_name("terwed");
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
    set_skill(PS_SPELLS, PTELL_ID);

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

    add_ask(" [for] 'quest' / 'task' ", VBFC_ME("answer_task"));
    add_ask(" 'about' %w ", "answer_member", 2);
}

void
arm_me()
{
    setuid();
    seteuid(getuid());

    clone_object(NARM + "black_chain_shirt")->move(this_object(), 1);

    command("wear all");

    ::arm_me();
}

void
do_reward(int quest, object questobj, object quester, int reward)
{
    string grade;
    
    switch (reward)
    {
        case 0..200:
            grade = " insignificantly";
            break;
        case 201..400:
            grade = " somewhat";
            break;
        case 401..600:
            grade = "";
            break;
        case 601..800:
            grade = " some";
            break;
        case 801..1000:
            grade = " greatly";
            break;
        case 1001..2000:
            grade = " immensly";
            break;
        default:
            grade = " fantastically";
            break;
    }

    switch(quest)
    {
    	case Q_VERMINAARD:
    	    command("say Excellent! I knew I could trust you to deliver this safely.");
    	    command("say I am sure you will find the Queen thankful as well.");
    	    quester->add_prop(POT_GOT_NEW_SPELL, ({"phammer", PHAMMER_ID}));
//    	    quester->set_skill(PS_SPELLS, quester->query_skill(PS_SPELLS) | PHAMMER_ID);
    	    quester->set_skill(PS_SKILL_POINTS,
    	        quester->query_skill(PS_SKILL_POINTS) + reward);
    	    questobj->remove_object();

            GUILD_ADMIN->add_priest_quest(quester->query_real_name(),
                Q_VERMINAARD);
    	    break;
    	case Q_KALAMAN:
    	    quester->add_prop(POT_GOT_NEW_SPELL, ({"palign", PALIGN_ID}));
//    	    quester->set_skill(PS_SPELLS, quester->query_skill(PS_SPELLS) | PALIGN_ID);
    	    quester->set_skill(PS_SKILL_POINTS,
    	        quester->query_skill(PS_SKILL_POINTS) + reward);
    	    quester->ks_remove_mission_shadow();

            GUILD_ADMIN->add_priest_quest(quester->query_real_name(),
                Q_KALAMAN);
    	    break;
        case Q_ANTECHAMBERS:
            quester->set_skill(PS_SKILL_POINTS,
                quester->query_skill(PS_SKILL_POINTS) + reward);
            quester->ts_remove_mission_shadow();
            
            GUILD_ADMIN->add_priest_quest(quester->query_real_name(),
                Q_ANTECHAMBERS);
            break;
    }

    write("You feel your standing within the guild improve" + grade + ".\n");
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
            set_alarm(2.0,0.0,&do_reward(Q_VERMINAARD, obj, from, 1000));
        else if(!obj->query_no_show())
            set_alarm(1.0,0.0,&give_back(obj,from));
}

int
do_report(string str)
{
    int reward;
    
    if (!MEMBER(TP))
        return 0;

    if (TP->ks_query_has_mission())
    {
        if (!TP->ks_query_mission_success())
        {
            write("You report your partial findings.\n");
            command("sneer");
            command("say I expect a full report, now go back and make " +
    	        "sure you study everything I need to know.");
            command("emote waves his hand in dismissal.");
            return 1;
        }

        write("You report your findings.\n");
        if(TP->ks_query_kills() == 0)
        {
   	        command("say Excellent! All details I needed, and you did " +
   	            "not attract any attention.");
            command("say That's full marks on this mission.");
            reward = 800;
        }
        else if(TP->ks_query_kills() < 3)
        {
            command("say Looks like you ran into some trouble, but " +
                "still, you got what I needed.");
            command("say You will be rewarded for this.");
            reward = 500;
        }
        else
        {
            command("say Is this what you call going unnoticed?");
            command("fume");
            command("say " + TP->ks_query_kills() + " dead! This will " +
                "put the guard on full alert!");
            command("say Your incompetence may have ruined our easy victory.");
            command("say Still, your information seems accurate enough.");
            command("say You will recieve one reward, but if you fail me like this again..");
            command("say Suffice to say you will not like the consequences.");
            command("emote mutters something about reckless incompetence.");
            reward = 100;
        }

        do_reward(Q_KALAMAN, TP, TP, reward);
    }
    else if (TP->ts_query_has_mission())
    {
        if (!TP->ts_query_mission_success())
        {
            write("You report your partial findings.\n");
            command("sneer");
            command("say I expect a full report, now go back and make " +
    	        "sure you study everything I need to know.");
            command("emote waves his hand in dismissal.");
            return 1;
        }
        
        write("You report your findings.\n");
        if (TP->ts_query_mission_time() < 300)
        {
            command("say Is this what you call thoroughly?");
            command("say Still it is accurate.");
            reward = 300;
        }
        else
        {
            command("say Excellent! This is all the detail I expected.");
            command("say I have a feeling you will be turning out to " +
                "be a fine addition to our priesthood.");
            command("smile .");
            reward = 600;
        }

        do_reward(Q_ANTECHAMBERS, TP, TP, reward);
    }
    else
        return 0;

    return 1;
}

void
init_living()
{
    ::init_living();
    add_action(do_report, "report");
}

varargs string
answer_member(object asker, string member)
{
    string s, he, his, him;
    int lev, days;
    object pl;

    if (!MEMBER(TP) && member_array(TP->query_real_name(),
        SECURITY->query_guild_masters("pot")) < 0)
    {
        answer_question(({ query_default_answer() }), 0);
        return "";
    }

    /* There is a three second delay from which the npc is loaded til
     * he has the necessary soul to use the command psay.
     */
    if (member_array(GUILD_CMDSOUL, query_cmdsoul_list()) < 0)
    {
        command("say to " + OB_NAME(TP) + " You have caught me in a " +
            "bad moment. Please allow me just a blink of an eye to " +
            "compose myself.");
        return "";
    }

    if (member == "members")
    {
        command("psay Ahh yes our members. By the records I keep these " +
            "are our members: " + COMPOSITE_WORDS(map(filter(
            GUILD_ADMIN->query_guild_list(), &not() @ &wildmatch("*jr")),
            capitalize)) + ".");
        command("psay I can tell you more about those if you ask me.");
        return "";
    }

    if (member == "pilgrims")
    {
        if (!sizeof(GUILD_ADMIN->query_pilgrims()))
        {
            command("psay Ahh yes our pilgrims. Unfortunately I have " +
                "none in my records listed as pilgrim.");
            return "";
        }
        command("psay Ahh yes our pilgrims. By the records I keep these " +
            "are our pilgrims: " +
            COMPOSITE_WORDS(map(GUILD_ADMIN->query_pilgrims(), capitalize)) +
            ".");
        command("psay I can tell you more about those if you ask me.");
        return "";
    }

    if (member == "council")
    {
        command("psay The positions in our council consists of the " +
            "Nightlord or lady, the Herbmanager, the Inquisitor, the " +
            "Librarian and the Headmentor.");
        command("psay I can tell you more about those positions if " +
            "you ask me.");
        return "";
    }
    
    if (member_array(member, ({ "nightlord", "nightlady", "chancellor",
        "inquisitor", "librarian", "headmentor" })) >= 0)
    {
        switch (member)
        {
            case "nightlord":
            case "nightlady":
                member = GUILD_ADMIN->query_council_seat("leader");
                break;
            case "herbmanager":
                member = GUILD_ADMIN->query_council_seat("chancellor");
                break;
            case "inquisitor":
                member = GUILD_ADMIN->query_council_seat("inquisitor");
                break;
            case "librarian":
                member = GUILD_ADMIN->query_council_seat("librarian");
                break;
            case "headmentor":
                member = GUILD_ADMIN->query_council_seat("mentor");
                break;
        }
        
        command("psay That position is currently held by " +
            (member ? capitalize(member) : "noone") + ".");
        return "";
    }

    if (member_array(member, GUILD_ADMIN->query_pilgrims()) >= 0)
    {
        days = max(-1, (GUILD_ADMIN->query_pilgrimage(member) - time()) / 86400);

        switch (days)
        {
            case -1:
                command("psay The pilgrimage of " + capitalize(member) +
                    " has just run out.");
                break;
            case 0:
                command("psay The pilgrimage of " + capitalize(member) +
                    " ends today.");
                break;
            default:
                command("psay " + capitalize(member) + " has been " +
                    "granted pilgrimage for another " + LANG_NUM2WORD(days) +
                    " day" + (days > 1 ? "s" : "") + ".");
                break;
        }
        
        return "";
    }

    if (member_array(member, GUILD_ADMIN->query_guild_list()) < 0)
    {
        command("psay I have no record of any such member.");
        return "";
    }

    if ((pl = find_player(member)))
    {
        lev = pl->query_skill(PS_GUILD_LEVEL);
        he = pl->query_pronoun();
        his = pl->query_possessive();
        him = pl->query_objective();
    }
    else
    {
        pl = SECURITY->finger_player(member);

        lev = GUILD_ADMIN->query_guild_level(member);
        he = pl->query_pronoun();
        his = pl->query_possessive();
        him = pl->query_objective();
        pl->remove_object();
    }
    
    if (member_array(member, GUILDMASTERS) >= 0)
    {
        command("psay " + capitalize(member) + " holds the honourary " +
            "title Guildmaster. While " + he + " takes no active part " +
            "in the guild's internal affairs, " + he + " works " +
            "closely with Takhisis Herself to allow Her priests " +
            "to be Her instrument of power in new and interesting ways " +
            "and wage constant battles with the Avatars of Balance " +
            "that would take away Her powers.");
        return "";
    }
    
    s = capitalize(member) + " holds the title " +
        GUILD_TITLES[lev / 50][(lev % 50 / 10) * 2 + (he == "she" ? 1 : 0)] + ". ";
    if (member_array(member, GUILD_ADMIN->query_guild_council()) >= 0)
    {
        s += capitalize(he) + " sits on the council of High Priests";
        if (GUILD_ADMIN->query_guild_leader() == member)
            s += " and is the Leader of our Priesthood. ";
        else
            s += ". ";
    }
    
    if (strlen(GUILD_ADMIN->query_priest_sponsor(member)))
    {
        s += capitalize(he) + " was mentored by " +
            capitalize(GUILD_ADMIN->query_priest_sponsor(member)) + ". ";
    }
    
    s += capitalize(he) + " has now actively served Takhisis for ";
    
    switch (GUILD_ADMIN->query_days_in_guild(member))
    {
        case 1:
            s += "less than a day";
            break;
        case 2..3:
            s += "a few days";
            break;
        case 4..6:
            s += "nearly a week";
            break;
        case 7..13:
            s += "nearly two weeks";
            break;
        case 14..20:
            s += "nearly three weeks";
            break;
        case 21..30:
            s += "nearly a month";
            break;
        case 31..60:
            s += "nearly two months";
            break;
        case 61..90:
            s += "nearly three months";
            break;
        case 91..120:
            s += "nearly four months";
            break;
        case 121..180:
            s += "nearly half a year";
            break;
        case 181..360:
            s += "nearly a year";
            break;
        case 361..720:
            s += "nearly two years";
            break;
        case 721..1080:
            s += "nearly three years";
            break;
        /* In 10-15 RL years maybe they will reach here */
        default:
            s += "more than three years";
    }

    command("psay " + s + ".");
    return "";
}

string
answer_task()
{
    int spells;
    if (!TP || E(TP) != E(TO))
        return "";
        
    if (MEMBER(TP))
    {
        if (!GUILD_ADMIN->query_priest_has_quest(TP->query_real_name(),
            Q_ANTECHAMBERS) && TP->query_skill(PS_GUILD_LEVEL) >= 0)
        {
            command("say In case of an attack on our temple it is " +
                "essential to quickly get a good overview of our " +
                "defences.");
            command("say To that end you should have a good knowledge " +
                "of moving about our temple.");
            command("say You will learn where the respective dragonarmy " +
                "antechambers are located.");
            command("say Once you have found all of them and studied " +
                "them thoroughly, report back to me.");
    	    if (!TP->ts_query_has_mission())
    	    {
    	        clone_object(GUILDDIR + "obj/quest/temple_shadow")->shadow_me(TP);
    	    }
        }
        else if (!GUILD_ADMIN->query_priest_has_quest(TP->query_real_name(),
            Q_KALAMAN) && TP->query_skill(PS_GUILD_LEVEL) >= 10)
        {
#ifdef 0
    	else if ((spells & PEYES_ID) == 0 &&
    	(TP->query_priest_level() > 0 || TP->query_priest_sublevel() >= 1))
    	{
#endif
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
    	        clone_object(GUILDDIR + "obj/quest/kalaman_shadow")->shadow_me(TP);
    	    }
    	}
        else if (!GUILD_ADMIN->query_priest_has_quest(TP->query_real_name(),
            Q_VERMINAARD) && TP->query_skill(PS_GUILD_LEVEL) >= 30)
        {
#ifdef 0
    	spells = TP->query_skill(PS_SPELLS);

    	if ((spells & PSLOW_ID) == 0 &&
    	(TP->query_priest_level() > 0 || TP->query_priest_sublevel() >= 3))
    	{
#endif
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
        	    clone_object(GUILDDIR + "obj/quest/verminaard_token")->move(TP, 1);
        	    TP->catch_msg(QCTNAME(TO) + " gives you a black metal token.\n");
            }
            else
            {
                command("say But I've told you all this before. Now go do it.");
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
            set_busy(B_SPEAKING);
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
            unset_busy(B_SPEAKING);
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
    string *arr;

    switch(round)
    {
    	case 0:
            set_busy(B_SPEAKING);
    	command("say To join you must find a priest willing to initiate " +
    	"you into the priesthood. As an initiate you will be expected " +
    	"to learn our ways, something which requires utter dedication.");
        break;

        case 1:
        command("say As you grow within the guild, you will become " +
        "more and more powerful, until one day the Queen of Darkness " +
        "will judge you fit to become a Priest. Such a feat will be " +
        "rewarded with higher skills and new abilities.");
        break;

        case 2:
        command("say A word of warning! The way of the priest is not " +
        "for the weak. The Queen does not approve of weaklings and " +
        "losers, and She has ways to quickly dispose of them.");
        break;

        case 3:
            unset_busy(B_SPEAKING);
#ifdef CLOSED_FOR_NEW_MEMBERS
            command("say Unfortunately at this time we cannot accept " +
                "any more members into our guild. Pray that the day " +
                "will come when this policy changes.");
#else
            arr = map(({ GUILD_ADMIN->query_council_seat("leader"),
                GUILD_ADMIN->query_council_seat("mentor") }), capitalize);
            
            if (arr[0] == arr[1])
                arr = ({ arr[0] });
            
            arr -= ({ "" });

            if (!sizeof(arr))
                command("say Unfortunately at this time none holds a " +
                    "position as to allow you into the guild. Rest " +
                    "assured this will be dealt with shortly.");
            else
                command("say If your intentions are true in heart and " +
                    "mind, then send an application to the Council. " +
#ifdef 0
                    "mind, then send an application to " +
                    COMPOSITE_WORDS(arr) + ". Include what you think " +
#else
                    "Include what you think " +
#endif

                    "is necessary.");
#endif
            break;
    }

    if (round < 3)
        set_alarm(3.0,0.0,&answer_joining(round+1));
    return "";
}

varargs string
answer_leaving(int round = 0)
{
    switch (round)
    {
        case 0:
            set_busy(B_SPEAKING);
            command("say Leaving is not something you do. Should you " +
                "decide to betray the Priesthood, eternal suffering in " +
                "the Abyss awaits you!");
            break;
        case 1:
            command("say Long and faithful service with a body gone " +
                "frail and fragile, Takhisis might spare you from " +
                "such a fate.");
            break;
        case 2:
            unset_busy(B_SPEAKING);
            command("say Know though that the price for leaving is " +
                "still a great one to pay for separation from the " +
                "Dark Queen's tender whispering has been known to " +
                "create madmen and raving lunatics.");
            break;
    }
    
    if (round < 2)
        set_alarm(3.0, 0.0, &answer_leaving(round + 1));

    return "";
}

varargs string
answer_goals(int round = 0)
{
    switch(round)
    {
    	case 0:
            set_busy(B_SPEAKING);
    	command("say The goals of the Priesthood have always been to " +
    	"aid the Queen of Darkness in her conquest of Krynn.");
        break;

        case 1:
        command("cough .");
        break;

        case 2:
        command("say To this end, we have been forced to defend " +
            "ourselves against the misled children of Paladine " +
            "and their allies, believing the twisted words and " +
            "dark lies of their masters that tells them to do anything " +
            "in their power to stop us.");
        break;

        case 3:
            unset_busy(B_SPEAKING);
        command("say No one and no thing must stand in the way of the " +
        "Dark Queen of Krynn!");
    }

    if (round < 3)
        set_alarm(3.0,0.0,&answer_goals(round+1));
    return "";
}
