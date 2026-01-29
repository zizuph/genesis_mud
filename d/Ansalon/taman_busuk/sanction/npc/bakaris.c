/*
    Dargaard Keep, Bakaris Lieutenant of the Blue Dragonarmy.

    bakaris.c
    =========
    Coded by: Alustrial, with lots of help from Xarguul, Rastlin, 
    95/9/12   and Jeremiah. Based on Jeremiah's code nightbringer.c

    Updated : Lots so far, and probably lots more in the near future.

    Bakaris is the Lieutenant of the Blue Dragonarmy, and will be
    the biggest npc in Dargaard Keep, aside from Lord Soth. 

    Copied from Dargaard dirs to Sanction dirs. Modified by Arman.
    Optimized by Milan.
    Added ask support - Bakaris gives out all info about the Blue Dragonarmy
    Also made it shadowed by blue shadow and use blue soul + dattack so
    Bakaris is now true member of the blue dragonarmy.
    Also fixed that do_die delay.
    Milan.
*/

/*
Louie May 2005 - Added ability to ask for promotions, and to allow
new recruits to join without a voucher
*/
#pragma save_binary
#pragma strict_types

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include "/d/Ansalon/guild/dragonarmy/guild.h"
#include <ss_types.h>
#include <macros.h>
#include <composite.h>

inherit AM_FILE

int is_dying = 0;

void
create_krynn_monster()
{
    object sh;

    setuid();
    seteuid(getuid());

    set_race_name("human");
    set_living_name("bakaris");
    set_adj(({"handsome","blonde-haired"}));
    set_name(({"bakaris","lieutenant"}));
    set_gender(0);

    set_stats(({180,230,200,120,100,140}));
    set_base_stat(SS_OCCUP, 200);

    set_skill(SS_AWARENESS, 70);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 80);
    set_skill(SS_DRAGONARMY_ATTACK, 100);
    set_alignment(-3000);
    set_all_hitloc_unarmed(40);

    add_prop(CONT_I_HEIGHT, 185);

    add_prop(LIVE_I_QUICKNESS, 200);
    add_prop("_ranger_m_not_disarm",1);

    set_act_time(5);
    add_act("emote slams his mailed fist down upon the table.");
    add_act("emote growls in anger.");
    add_act("emote mumbles: Where is she...");
    add_act("emote paces impatiently about the room.");

    set_cact_time(4);
    add_cact("glare all");
    add_cact("emote grits his teeth, despite his injuries.");
    add_cact("laugh coldy");

    set_cchat_time(5);
    add_cchat("Fool! Now you will die.");
    add_cchat("Why do you even persist? You have no chance!");

    sh = clone_object(BLUE_SHADOW);
    if(sh->shadow_me(TO, "occupational", GUILD_STYLE, GUILD_NAME) != 1)
    {
	"secure/master"->do_debug("destroy",sh);
    }
    TO->set_promotion_level(3);
    add_cmdsoul(DRAGONARMY_BLUE_SOUL);
    load_command_souls();
}

void
arm_me()
{
    clone_object(DRAGONARMY_OCC_EMBLEM)->move(TO, 1);

    clone_object(SOBJ + "weapon/baksword")->move(TO, 1);
    clone_object("/d/Krynn/solamn/splains/obj/bdragonarm")->move(TO, 1);
    clone_object("/d/Krynn/solamn/splains/obj/bdragonhelm")->move(TO, 1);
    clone_object("/d/Krynn/solamn/splains/obj/bshinguard")->move(TO, 1);

    command("wear all");
    command("wield all");
}

int
special_attack(object ob)
{
    if(!query_prop("_dragonarmy_dattack_prop"))
	command("slash");
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

    switch(promos)
    {
    case 4:
	command("emote swiftly straightens to attention.");
	set_alarm(1.0, 0.0, &command("dsay to "+who+" Greetings " +
	    "General "+capitalize(who)+ "! How may I be of assistance?"));
	break;
    case 3:
	command("dsay to "+who+" Ah "+capitalize(who)+ "... I should "+
	  "have recognized you.");
	command("nod respect " +who);
	break;
    case 2:
	command("dsay to "+who+ " Well met officer " +capitalize(who)+
	  ". What can I do for you?");
	break;
    case 1:
	command("dsay to "+who+ " What is it soldier? I am a busy man.");
	set_alarm(1.5, 0.0, &command("eyebrow " +who));
	break;
    default:
	command("glare coldly " + who);
	set_alarm(1.0, 0.0, &command("say I care nothing for your identity!"));
	set_alarm(1.5, 0.0, &command("say But you would do well to remember "+
	    "mine..."));
	set_alarm(2.0, 0.0, &command("emote draws himself to his full "+
	    "height, and throws his cape over his shoulder."));
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
    case "spit":
	if (!query_attack())
	{
	    command("say to "+OB_NAME(actor)+" Run while you can!");
	    command("slash "+OB_NAME(actor));
	}
	else if (query_prop(BAKARIS_BLOCKS))
	{
	    actor->add_prop(KICKED_BAKARIS, 1);
	    command("say to "+OB_NAME(actor)+" I will finish this one first.");
	    command("say to "+OB_NAME(actor)+" Then we shall see if you are brave to do it again!");
	}
	else if (!actor->query_prop(KICKED_BAKARIS))
	{
	    actor->add_prop(KICKED_BAKARIS, 1);
	    command("say to "+OB_NAME(actor)+" One more time and I will not let you out alive!");
	}
	else
	{
	    add_prop(BAKARIS_BLOCKS, 1);
	    command("say to "+OB_NAME(actor)+" You are dead now!");
	    command("emote moves to block exit with his body.");
	    command("kill "+OB_NAME(actor));
	}
	break;
    }
}

void
stop_block()
{
    remove_prop(BAKARIS_BLOCKS);
    command("say Another one bites the dust!");
    command("emote moves out of exit.");
    if (query_attack())
	command("say You can now run like rats!");
}

void
notify_you_killed_me(object ob)
{
    set_alarm(1.0, 0.0, stop_block);
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
    set_alarm(0.0, 0.0, &command("glare angrily "+ OB_NAME(killer)));
    set_alarm(1.0, 0.0, &command("say You think you can so easily defeat a "+
	"servant of the Dark Queen?"));
    set_alarm(1.5, 0.0, &command("laugh coldly "+ OB_NAME(killer)));
    set_alarm(2.5, 0.0, &command("emote slumps to the floor and stiffens."));
    set_alarm(3.0, 0.0, &command("emote curses violently."));
    set_alarm(4.0, 0.0, &command("say Bah! Betrayed in the end..."));
    set_alarm(5.0, 0.0, &command("sigh ."));

    set_alarm(5.5, 0.0, &real_do_die(killer));
}

void
do_promotion(object player, object me)
{
  object this_player_holder = player;
  string tp_real_name = player->query_real_name();
  
  me->command("say to "+OB_NAME(TP)+
              " Very well, you are fit to lead our troops astride "+
              "the back of one of our dragons.");
  
  set_this_player(me);
  if (!DRAGONARMY_BASE_SOUL->promote_soldier(tp_real_name))
  {
        set_alarm(4.0,0.0,&command("say to "+OB_NAME(TP)+
            " Well, that's messed up, I can't seem to "+
            "promote you.  You should probably talk to "+
            "a Krynn wizard about that."));
  }
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

    if(TP->query_dragonarmy_division() != "blue" && !TP->query_met(TO))
    {
	set_alarm(rnd()*3.0 + 1.0, 0.0, &command("say to "+
	    OB_NAME(TP)+" Who are you stranger?"));
	return;
    }

    if(!parse_command(str, ({}), "[about] [the] %s", question))
    {
	set_alarm(rnd()*3.0 + 1.0, 0.0, &command("say to "+
	    OB_NAME(TP)+" I do not understand your question."));
	return;
    }
    question = lower_case(question);
    if(question == "bakaris")
    {
	set_alarm(rnd()*3.0 + 1.0, 0.0, &command("say to "+
	    OB_NAME(TP)+" I am Bakaris!"));
	return;
    }

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
	if(minfo[0] != "blue")
	{
	    set_alarm(rnd()*3.0 + 1.0, 0.0, &command("dsay to "+
		OB_NAME(TP)+" "+C(question)+
		" is not a soldier of the Blue Dragonarmy."));
	    return;
	}
	answ = " Yes, "+C(question)+" is "+C(PROMOTION_LEVELS[minfo[1]])+
	" of the Blue Dragonarmy...";
	set_alarm(1.5, 0.0, &command("dsay to "+OB_NAME(TP)+answ));

	if(TP->query_dragonarmy_division() != "blue")
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
	if(!IS_MEMBER(TP) || MANAGER->query_punishment(TP->query_real_name(), PUN_NOWHO))
	{
	    set_alarm(2.5, 0.0, &command("say to "+OB_NAME(TP)+
		" Only soldiers of the Dragonarmy are entitled to the "+
		"information about other members."));
	    return;
	}
	minfo = MANAGER->query_member_list("blue");
	if(!minfo)
	{
	    set_alarm(5.0, 0.0, &command("dsay to "+OB_NAME(TP)+
		" I am too busy now. Come back later."));
	    return;
	}
	set_alarm(2.5, 0.0, &command("emote studies his records."));
	set_alarm(5.0, 0.0, &command("dsay to "+OB_NAME(TP)+
	    " List of Blue Dragonarmy members..."));
	if(sizeof(minfo[0]))
	{
	    set_alarm(6.0, 0.0, &command("dsay to "+OB_NAME(TP)+
		" "+COMPOSITE_WORDS(minfo[0])+
		(sizeof(minfo[0])>1 ? " are Recruits." : " is Recruit.")));
	}
	else
	{
	    set_alarm(6.0, 0.0, &command("dsay to "+OB_NAME(TP)+
		" We need some fresh recruits."));
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

    if (question == "dragonarmy" || question == "blue dragonarmy" ||
      question == "army" || question == "blue army" ||
      question == "info" || question == "information" || question == "informations" ||
      question == "join" || question == "leave" ||
      question == "join dragonarmy" || question == "join blue dragonarmy" ||
      question == "join army" || question == "join blue army" ||
      question == "leave dragonarmy" || question == "leave blue dragonarmy" ||
      question == "leave army" || question == "leave blue army")
    {
	set_alarm(2.0, 0.0, &command("say to "+OB_NAME(TP)+
	    " This is the right place to join the Blue Dragonarmy and "+
	    "I am the responsible Recruitment Officer."));
	set_alarm(3.0, 0.0, &command("say to "+OB_NAME(TP)+
	    " New recruits can sign up here."));
    /*
    set_alarm(4.0, 0.0, &command("say to "+OB_NAME(TP)+
	    " An officer has to vouch for them before I accept them."));
    */
    set_alarm(4.0, 0.0, &command("say to "+OB_NAME(TP)+
        " You'll probably want to find "+
	    "a High Officer or higher willing to 'vouch' you into the army. "+
        "That way, you can join with full access.  If you do not, "+
        "you can still join but you'll be restricted from certain things "+
        "until someone lifts "+
        "your ban on various activities as a new recruit."));
	set_alarm(5.0, 0.0, &command("hmm"));
	set_alarm(6.0, 0.0, &command("say to "+OB_NAME(TP)+
	    " Soldiers can also discharge themselves from the Dragonarmy here."));
	set_alarm(7.0, 0.0, &command("say to "+OB_NAME(TP)+
	    " But I would not suggest that!"));
	set_alarm(7.5, 0.0, &command("emote slams his mailed fist down upon the table."));
	return;
    }

    /*Bakaris gives out promotions now*/
    if (question == "promotion" || question == "for promotion" ||
        question == "for a promotion" || question == "promote" ||
        question == "promote me" || question == "please promote me")
    {
        if (TP->query_dragonarmy_promotions() != 1) {
            set_alarm(2.0, 0.0, &command("say to "+OB_NAME(TP)+
                " Only Soldiers can request a promotion from me!"));
            return;
        }
        
        if (TP->query_dragonarmy_division() != "blue") {
            set_alarm(2.0, 0.0, &command("say to "+OB_NAME(TP)+
                " You fool, you're not even under my command!"));
            return;
        }

        set_alarm(2.0, 0.0, &command("say to "+OB_NAME(TP)+
            " You want a promotion?  Hmm, let me think..."));
        
        if (!TP->test_bit("Ansalon",3,0)) {
            set_alarm(3.0, 0.0, &command("say to "+OB_NAME(TP)+
                " I don't think I've heard of you.  You have to "+
                "prove your worth to get a promotion from me, "+
            "such as by mastering your weapon and then "+
            "personally conquering an area from the Knighthood!"));
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
                "current station, don't come crying to me to "+
                "get you promoted, work it out with your commanding "+
                "officer or general!"));
	        return;

        }

        set_alarm(3.0, 0.0, &command("say to "+OB_NAME(TP)+
            " Ah yes, your exploits are well known - "+
            "single handedly conquering an area from the "+
            "Knights, mastering the ways of beasts, and "+
            "a long history of serving well on the battlefield "+
            "in Her army."));
        
        set_alarm(4.0, 0.0, &do_promotion(TP, this_object()));

        return;
    }

    set_alarm(2.0, 0.0, &command("say to "+OB_NAME(TP)+
	" I am too busy to bother with such thing."));
}

void
unsummon_guards(object guard1, object guard2, object guard3)
{
  if (sizeof(guard1->query_attack()) > 0 ||
      sizeof(guard2->query_attack()) > 0 ||
      sizeof(guard3->query_attack()) > 0)
  {
    set_alarm(600.0, 0.0, &unsummon_guards(guard1, guard2, guard3));
  }
  else
  {
    if(objectp(guard1))
    {
        tell_room(environment(guard1), QCTNAME(guard1)+" leaves.\n");
        guard1->remove_object();
    }

    if(objectp(guard2))
    {
        tell_room(environment(guard2), QCTNAME(guard2)+" leaves.\n");
        guard2->remove_object();
    }

    if(objectp(guard3))
    {
        tell_room(environment(guard3), QCTNAME(guard3)+" leaves.\n");
        guard3->remove_object();
    }
  }
}

void get_guards(object ob)
{
   object guard1;
   object guard2;
   object guard3;

   string yell_str;

   if (ob->query_dragonarmy_division() == "blue")
   {
	   yell_str = "shout Traitor! Traitor in our midst! Guards!";
   }
   else if (ob->query_dragonarmy_division() == "red")
   {
       yell_str = "shout It is one of those pesky Red Army folks! Guards!";
   }
   else if (ob->query_guild_name_lay() == "Templars of Takhisis")
   {
       yell_str = "shout One of the Templars are rebelling against the Queen! Guards!";
   }
   else if (ob->query_guild_name_occ() == "Priests of Takhisis")
   {
	   yell_str = "shout One of the Priests has lost their way! Guards!";
   }

   if (yell_str)
   {
     this_object()->command(yell_str);
     
     if(!objectp(guard1))
     {
       guard1 = clone_object("/d/Ansalon/taman_busuk/sanction/npc/da_member");
       guard1->set_color("blue");
       guard1->set_dragonarmy_rank(random(4) ? 1 : 2);
       guard1->arm_me();
       guard1->move(environment(this_object()), 1);
       guard1->command("kill " + OB_NAME(ob));
     }
     else if(present(guard1, environment(this_object())))
     {
       guard1->command("kill " + OB_NAME(ob));
     }

     if(!objectp(guard2))
     {
       guard2 = clone_object("/d/Ansalon/taman_busuk/sanction/npc/da_member");
       guard2->set_color("blue");
       guard2->set_dragonarmy_rank(random(4) ? 1 : 2);
       guard2->arm_me();
       guard2->move(environment(this_object()), 1);
       guard2->command("kill " + OB_NAME(ob));
     }
     else if(present(guard1, environment(this_object())))
     {
       guard2->command("kill " + OB_NAME(ob));
     }

     if(!objectp(guard3))
     {
       guard3 = clone_object("/d/Ansalon/taman_busuk/sanction/npc/da_member");
       guard3->set_color("blue");
       guard3->set_dragonarmy_rank(random(4) ? 1 : 2);
       guard3->arm_me();
       guard3->move(environment(this_object()), 1);
       guard3->command("kill " + OB_NAME(ob));
     }
     else if(present(guard1, environment(this_object())))
     {
       guard3->command("kill " + OB_NAME(ob));
     }
   }
   set_alarm(600.0, 0.0, &unsummon_guards(guard1, guard2, guard3));
}

public void attacked_by(object ob)
{
   
   ::attacked_by(ob);
   get_guards(ob);
}

public void
attack_object(object ob)
{
   ::attack_object(ob);   
   get_guards(ob);
}
