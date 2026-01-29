#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include "/d/Ansalon/guild/dragonarmy/guild.h"
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit AM_FILE

/*
* 2005 May Louie - Added ability to ask for promotions and to
* allow recruits to join without a voucher.
*/
void
create_krynn_monster()
{
    object sh;

    if (!IS_CLONE)
	return;

    set_name("clerk");
    set_short("busy clerk");
    set_race_name("human");
    set_long("Before you stands a harried dragonarmy clerk, responsible " +
      "for the dispatching of various commands and messages to the " +
      "various dragonarmies. You would guess this man is quite knowledgeable "+
      "of the various dragonarmies.\n");
    set_stats(({65,55,45,35,35,45}));
    set_hp(10000);
    set_all_attack_unarmed(100, 100);
    set_all_hitloc_unarmed(90);

    set_skill(SS_WEP_CLUB, 50);
    set_skill(SS_DEFENCE, 30);
    set_skill(SS_PARRY, 30);

    set_alignment(-20);
    set_knight_prestige(1);

    set_act_time(45);
    add_act("emote searches frantically for a certain dispatch.");
    add_act("say Ariakas will have my hide if his General fails to get this " +
      "message!");
    add_act("emote wipes sweat from his forehead, inadvertantly " +
      "smudging ink across it.");
    add_act("say Ariakas is a brilliant tactician! The knights " +
      "won't know what hit them!");

    sh = clone_object(RED_SHADOW);
    if(sh->shadow_me(TO, "occupational", GUILD_STYLE, GUILD_NAME) != 1)
    {
	"secure/master"->do_debug("destroy",sh);
    }
    TO->set_promotion_level(2);
    add_cmdsoul(DRAGONARMY_RED_SOUL);
    load_command_souls();
}

void
do_promotion(object player, object me)
{
  object this_player_holder = player;
  string tp_real_name = player->query_real_name();
  
  me->command("say to "+OB_NAME(player)+
	      " It seems all the requirements are in order, I can "+
	      "approve this promotion request.");
  
  set_this_player(me);
  DRAGONARMY_BASE_SOUL->promote_soldier(tp_real_name);
  set_this_player(this_player_holder);
}


void
catch_question(string str)
{
    string question, answ;
    mixed minfo;
    int new_stat;

    if(!TP->check_seen(TO) || !CAN_SEE_IN_ROOM(TO))
    {
	set_alarm(rnd()*3.0 + 1.0, 0.0, &command("emote peers around puzzled."));
	return;
    }

    if(!parse_command(str, ({}), "[about] [the] %s", question))
    {
	set_alarm(rnd()*3.0 + 1.0, 0.0, &command("say to "+
	    OB_NAME(TP)+" I do not understand your question."));
	return;
    }
    question = lower_case(question);

    if((minfo = MANAGER->query_member(question)))
    {
	if(!IS_MEMBER(TP) || MANAGER->query_punishment(TP->query_real_name(), PUN_NOWHO))
	{
	    set_alarm(2.5, 0.0, &command("say to "+OB_NAME(TP)+
		" Only soldiers of the Dragonarmy are entitled to the "+
		"information about other members."));
	    return;
	}
	set_alarm(0.5, 0.0, &command("emote looks in his recruitment list."));
	if(minfo[0] != "red")
	{
	    set_alarm(rnd()*3.0 + 1.0, 0.0, &command("dsay to "+
		OB_NAME(TP)+" "+C(question)+
		" is not a soldier of the Red Dragonarmy."));
	    return;
	}
	answ = " Yes, "+C(question)+" is "+C(PROMOTION_LEVELS[minfo[1]])+
	" of the Red Dragonarmy...";
	set_alarm(1.5, 0.0, &command("dsay to "+OB_NAME(TP)+answ));

	if(TP->query_dragonarmy_division() != "red")
	    return;

	answ = " ...and was ";
	if(minfo[3] && !minfo[1])
	{
	    answ += "just recruited";
	}
	else
	{
	    answ += (minfo[3] ? "promoted" : "demoted")+" to this level";
	}
	if(minfo[2])
	{
	    answ += " by "+C(minfo[2]);
	}
	answ += ".";
	set_alarm(2.0, 0.0, &command("dsay to "+OB_NAME(TP)+answ));

	if(TP->query_dragonarmy_promotions() < minfo[1])
	    return;

	minfo = MANAGER->query_member_activity(question);
	if(sizeof(minfo[0]))
	{
	    answ = " "+C(question)+" recruited "+COMPOSITE_WORDS(minfo[0])+".";
	    set_alarm(2.5, 0.0, &command("dsay to "+OB_NAME(TP)+answ));
	}
	if(sizeof(minfo[1]))
	{
	    answ = " "+C(question)+" promoted "+COMPOSITE_WORDS(minfo[1])+".";
	    set_alarm(3.0, 0.0, &command("dsay to "+OB_NAME(TP)+answ));
	}
	if(sizeof(minfo[2]))
	{
	    answ = " "+C(question)+" demoted "+COMPOSITE_WORDS(minfo[2])+".";
	    set_alarm(3.5, 0.0, &command("dsay to "+OB_NAME(TP)+answ));
	}
	return;
    }

    if (question == "list" || question == "member list")
    {
	if(!IS_MEMBER(TP) && !TP->query_wiz_level())
	{
       	    set_alarm(2.5, 0.0, &command("say to "+OB_NAME(TP)+
		" Only soldiers of the Dragonarmy are entitled to the "+
		"information about other members."));
	    return;
	}
        if(MANAGER->query_punishment(TP->query_real_name(), PUN_NOWHO))
        {
            set_alarm(2.5, 0.0, &command("say to "+OB_NAME(TP)+
                      " I am ordered not to reveal such information to punished soldiers."));
	    return;
        }  

	minfo = MANAGER->query_member_list("red");
	if(!minfo)
	{
	    set_alarm(2.5, 0.0, &command("emote searches frantically for his records."));
	    set_alarm(5.0, 0.0, &command("dsay to "+OB_NAME(TP)+
		" Sorry, I can't find my records now."));
	    return;
	}
	set_alarm(2.5, 0.0, &command("emote studies his records."));
	set_alarm(5.0, 0.0, &command("dsay to "+OB_NAME(TP)+
	    " You wanted list of Red Dragonarmy members..."));
	if(sizeof(minfo[0]))
	{
	    set_alarm(6.0, 0.0, &command("dsay to "+OB_NAME(TP)+
		" "+COMPOSITE_WORDS(minfo[0])+
		(sizeof(minfo[0])>1 ? " are Recruits." : " is Recruit.")));
	}
	else
	{
	    set_alarm(6.0, 0.0, &command("dsay to "+OB_NAME(TP)+
		" There are no fresh recruits now."));
	}
	if(sizeof(minfo[1]))
	{
	    set_alarm(6.5, 0.0, &command("dsay to "+OB_NAME(TP)+
		(sizeof(minfo[1])>1 ? " Soldiers are " : " Soldier is ")+
		COMPOSITE_WORDS(minfo[1])+"."));
	}
	else
	{
	    set_alarm(6.5, 0.0, &command("dsay to "+OB_NAME(TP)+
		" We desperately need soldiers."));
	}
	if(sizeof(minfo[2]))
	{
	    set_alarm(7.0, 0.0, &command("dsay to "+OB_NAME(TP)+
		" "+COMPOSITE_WORDS(minfo[2])+
		(sizeof(minfo[2])>1 ? " are Officers." : " is Officer.")));
	}
	else
	{
	    set_alarm(7.0, 0.0, &command("dsay to "+OB_NAME(TP)+
		" Noone has been promoted to the Officer rank."));
	}
	if(sizeof(minfo[3]))
	{
	    set_alarm(7.5, 0.0, &command("dsay to "+OB_NAME(TP)+
		" "+COMPOSITE_WORDS(minfo[3])+
		(sizeof(minfo[3])>1 ? " are High Officers." : " is High Officer.")));
	}
	else
	{
	    set_alarm(7.5, 0.0, &command("dsay to "+OB_NAME(TP)+
		" The High Officer rank is unassigned."));
	}
	if(sizeof(minfo[4]))
	{
	    set_alarm(8.0, 0.0, &command("dsay to "+OB_NAME(TP)+
		" "+COMPOSITE_WORDS(minfo[4])+
		(sizeof(minfo[4])>1 ? " are Generals," : " is General.")));
	}
	else
	{
	    set_alarm(8.0, 0.0, &command("dsay to "+OB_NAME(TP)+
		" The General position is open."));
	}
	return;
    }

    if (question == "dragonarmy" || question == "dragonarmies")
    {
	if(TP->query_alignment() > 0)
	{
	    command("eyebrow suspic");
	    command("say What are you interested in the dragonarmies for?");
	    command("say Begone before I call the guards!");
	    return;
	}

	command("scratch chin");
	command("say I know quite a bit about the dragonarmies...");
	set_alarm(1.0,0.0,&command("say From out of the nightmares and stories of "+
	    "the past came dragons, absent many years from the lands of Krynn."));
	set_alarm(2.0,0.0,&command("say Awoken by the call of the dark goddess Takhisis, "+
	    "these great serpentine beasts began to gather together great " +
	    "armies of ogres, evil men, goblins and other fell creatures in an " +
	    "effort to conquer the continent of Ansalon "+
	    "and subjugate all the free people to their dark will!"));
	set_alarm(3.0,0.0,&command("cackle"));
	set_alarm(4.0,0.0,&command("emote takes a deep breath."));
	set_alarm(5.0,0.0,&command("say I believe some books have been stored in the archive "+
	    "concerning various aspects of the dragonarmy if you are " +
	    "interested..."));
	set_alarm(5.5,0.0,&command("point east"));
	set_alarm(6.5,0.0,&command("say But you'll have to be a bit more specific if "+
	    "you want details from me, as there are five armies: the Red "+
	    "Dragonarmy, the Blue Dragonarmy, the Black Dragonarmy " +
	    "the Green Dragonarmy and the White Dragonarmy."));
	set_alarm(7.0,0.0,&command("smile knowing"));
	return;
    }

    if(question == "red dragonarmy" || question == "red")
    {
	if(TP->query_alignment() > 0)
	{
	    command("emote ignores the question.");
	    return;
	}
	command("say The Red Dragonarmy is the most powerful and successful " +
	  "army of the Dark Queen!");
	command("smile proud");
	set_alarm(1.0,0.0, &command("say The army is lead by the mighty Dragon Highlord "+
	    "Ariakas, whose victories and the favour of the Queen of Darkness "+
	    "has lead to him being proclaimed Emperor of Krynn!"));
	set_alarm(1.5,0.0, &command("cackle"));
	set_alarm(2.0,0.0,&command("You should have read the reports that "+
	    "came back from Nordmaar! Those savages fell like " +
	    "wheat to the disciplined soldiers in red, their spears " +
	    "dispersing their disorderly cavalry..."));
	set_alarm(2.5,0.0,&command("sigh wistful"));
	set_alarm(3.0,0.0,&command("say Anyhow, I digress. This "+
	    "army is highly skilled with polearms, and "+
	    "are the most highly trained in the defensive skills of " +
	    "all the armies."));
	set_alarm(4.0,0.0,&command("say They have been trained in some rather nasty "+
	    "impaling tactics that makes them warriors to be feared!"));
	set_alarm(4.5,0.0,&command("ponder"));
	set_alarm(5.0,0.0,&command("say A contingent of the Red Dragonarmy can be found "+
	    "to the north of Sanction, near the temple of Luerkhisis."));
	set_alarm(6.0,0.0,&command("say If you are further interested in this army, "+
	    "perhaps you should request an audience with Dragon Highlord " +
	    "Ariakas?"));
	set_alarm(6.5,0.0, &command("grin"));
	set_alarm(7.0,0.0, &command("say Go at your own peril though! He does not tolerate "+
	    "fools well!"));     
	return;
    }

    if(question == "blue dragonarmy" || question == "blue")
    {
	if(TP->query_alignment() > 0)
	{
	    command("snicker");
	    command("say Why should I answer you?");
	    return;
	}
	command("say The Blue Dragonarmy is one highly in the favour " +
	  "of the Queen of Darkness.");
	set_alarm(1.0,0.0,&command("say It is lead by the charismatic " +
	    "Dark Lady, Dragon Highlord "+
	    "Kitiara, a swordswoman of keen military ability " +
	    "and fiery temperament."));
	set_alarm(2.0,0.0,&command("say Her soldiers consist of some of the finest "+
	    "dragonriders, as their affinity with the loyal blue " +
	    "dragons is an unusually strong bond."));
	set_alarm(2.5,0.0,&command("ponder"));
	set_alarm(3.0,0.0,&command("say These warriors typically fight with one or two "+
	    "swords, their fierce fighting ability making them quite " +
	    "skilled shock legions."));
	set_alarm(4.0,0.0,&command("say At present there is a contingent of the Blue "+
	    "Dragonarmy stationed to the east of Sanction. Camp commander " +
	    "is lieutenant Bakaris. Go talk to him if you want more information."));

	return;
    }

    if(question == "green" || question == "green dragonarmy" ||
      question == "black" || question == "black dragonarmy" ||
      question == "white" || question == "white dragonarmy")
    {
	if(TP->query_alignment() > 0)
	{
	    command("eyebrow incred");
	    command("Can't you see I am a busy man? Begone!");
	    return;
	}
	command("scratch chin");
	command("say To be honest, I don't know much about that " +
	  "Dragonarmy. If you wish to find recruitment information about " +
	  "them, you have come to the wrong place.");
	command("smirk");
	return;
    }

    if(question == "quest" || question == "tour" || question == "task")
    {
	command("say Sorry, I cannot help you with that.");
	return;
    }

    if(question == "join" || question == "joining" || question == "recruiting" ||
      question == "join the dragonarmy" || question == "join the dragonarmies" ||
      question == "joining the dragonarmy" || question == "joining the dragonarmies")
    {
	if(TP->query_alignment() > 0)
	{
	    command("say Sorry, you really aren't the kind of person the "+
	      "dragonarmies are looking for.");
	    return;
	}
	command("say There are a few criteria that you must fall into " +
	  "if you want a chance to be able to join the Dragonarmies.");
	set_alarm(1.0,0.0,&command("say For starters, you can't be "+
	    "an elf. Ariakas hates them, and Lord Verminaard only likes "+
	    "them stuck on the end of a pike."));
	set_alarm(1.5,0.0,&command("say Mind you, if you have a little "+
	    "elven blood in you, its possible to get in, especially in the " +
	    "Blue Dragonarmy... rumours state that Lady Kitiara has " +
	    "a 'thing' for half-elves..."));
	set_alarm(2.0,0.0,&command("grin lewd"));
	set_alarm(2.5,0.0,&command("say The armies don't have any " +
	    "place for gnomes or dwarves... and certainly not kender."));
	set_alarm(3.0,0.0,&command("emote shudders at the thought."));
	set_alarm(3.5,0.0,&command("say So basically you have to be "+
	    "either human, half-elf, goblin, orc or minotaur to sign up here."));
	set_alarm(4.5,0.0,&command("say The dragonarmies also don't "+
	    "want any treehugging pansies. We don't want those who can't "+
	    "stomach sticking a spear into a womans back, or those " +
	    "who won't bash unruly slaves. Basically, you'll need a " +
	    "black heart."));
    /*
	set_alarm(5.5,0.0,&command("say Finally, you'll need to find "+
	    "an officer willing to 'vouch' you into his army. You get that, "+
	    "and you'll be able to sign up as a recruit."));
    */
   	set_alarm(5.5,0.0,&command("say Finally, you'll want to find "+
	    "a High Officer or higher willing to 'vouch' you into his army. "+
        "That way, you can join with full access.  If you do not, "+
        "you can still join but you'll be restricted from certain things "+
        "until someone lifts "+
        "your ban on various activities as a new recruit."));

    return;
    }

    if(question == "leaving" || question == "leaving the dragonarmy")
    {
	if(TP->query_alignment() > 0)
	{
	    command("say Bugger off goody two shoes!");
	    return;
	}
	command("say To leave any of the dragonarmies, you have to " +
	  "go to the place where you signed up, and 'discharge' "+
	  "yourself.");
	command("say But be warned! You lose a quarter of all your " +
	  "combat experience by doing so, so do not do it lightly!");
	return;
    }

    /*The clerk gives out promotions now*/
    if (question == "promotion" || question == "for promotion" ||
        question == "for a promotion" || question == "promote" ||
        question == "promote me" || question == "please promote me")
    {
        if (TP->query_dragonarmy_promotions() != 1) {
            set_alarm(2.0, 0.0, &command("say to "+OB_NAME(TP)+
                " Only Soldiers can request a promotion from me!"));
            return;
        }

        if (TP->query_dragonarmy_division() != "red") {
            set_alarm(2.0, 0.0, &command("say to "+OB_NAME(TP)+
                " You'll have to speak to someone in your own "+
                "army about a promotion, like Bakaris."));
            return;
        }

        set_alarm(2.0, 0.0, &command("say to "+OB_NAME(TP)+
            " A promotion, eh?  Well, let's have a look at "+
            "your records..."));
        
        if (!TP->test_bit("Ansalon",3,0) && TP->query_real_name() != "navarrejr")
        {
            set_alarm(3.0, 0.0, &command("say to "+OB_NAME(TP)+
                " No, this won't do at all.  You have to "+
                "prove your worth to get a promotion, "+
            "such as by mastering your weapon and then personally "+
            "conquering an area from the Knighthood!"));
            return;
        }

        if (TP->query_skill(SS_ANI_HANDL) < 70) {
            set_alarm(3.0, 0.0, &command("say to "+OB_NAME(TP)+
                " Officers of the Dragonarmy have to be "+
                "able to handle riding on the backs of dragons, "+
                "and your animal handling ability is too low for "+
                "that!"));
            return;
        }

        /*We require enough guild xp to almost be an HO before we*/
        /*promote to Officer automatically*/
        if (TP->query_dragonarmy_rank_stat() < 13) {
            set_alarm(3.0, 0.0, &command("say to "+OB_NAME(TP)+
                " You do not have enough experience on the "+
                "battlefield as a Dragonarmy Soldier to be "+
                "promoted to Officer yet!  Come back when "+
                "you are more blooded in the ways of the "+
                "Dragonarmy!"));
            return;
        }

        if(!MANAGER->query_promoted(TP))
        {
            set_alarm(3.0, 0.0, &command("say to "+OB_NAME(TP)+
                " What is this?  You have been demoted to your "+
                "current rank, and there is no way I'm going to "+
                "go against someone else's orders!"));
	        return;

        }

        set_alarm(3.0, 0.0, &command("say to "+OB_NAME(TP)+
            " Impressive work!  "+
            "Single handedly conquering an area from the "+
            "Knights, mastering the ways of beasts, and "+
            "a long history of serving well on the battlefield."));

	set_alarm(4.0, 0.0, &do_promotion(TP, this_object()));

        return;
    }

    set_alarm(2.0, 0.0, &command("say to "+OB_NAME(TP)+
	" I am too busy to worry about that. Go bother someone else!"));
}

