/*
 *	/d/Gondor/lebennin/wolfcave/gilraen.c
 *
 */
#pragma strict_types

inherit "/d/Gondor/common/dunedain/npc/npc_dunadan.c";
inherit "/d/Gondor/common/lib/logkill.c";
#include "/d/Gondor/common/lib/make_money.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"

public void
create_dunadan()
{
    set_living_name("gilraen");
    set_name("gilraen");
    add_name(({"lady","woman","dunadan"}));
    set_race_name("human");
    set_adj(({"slender","auburn-maned"}));
    set_title("Proud Lady of Gondor");
    set_dunedain_house("Belecthor");
    set_long("A beautiful and stately lady, she obviously comes from a "+
	     "wealthy family.\n");
    default_config_npc(75);
    set_base_stat(SS_CON,85);
    set_base_stat(SS_INT,85);
    set_base_stat(SS_DEX,95);
    refresh_mobile();
    set_skill(SS_WEP_SWORD, random(11)+90);
    set_skill(SS_WEP_KNIFE, random(6)+85);
    set_skill(SS_2H_COMBAT, random(6)+80);
    set_skill(SS_DEFENCE, random(21)+90);
    set_skill(SS_PARRY, random(11)+90);
    set_alignment(300+random(301));
    set_gender(G_FEMALE);
    set_chat_time(5);
    add_chat("I hope someone arrives soon to help us.");
    add_chat("I still wonder what happened to Father's servant.");
    add_chat("They say he was lost somewhere off the road between here "+
	"and Pelargir.");
    add_chat("It would be so nice to regain the lost family heirlooms.");
    add_chat("He disappeared so long ago, there must be nothing but dust "+
	"left by now.");
    set_cchat_time(8);
    add_cchat("How dare you attack me in my own house! Get out now!");
    add_cchat("Guards! Guards!");
    add_cchat("I shall not be as easy to kill as you think I am.");
    add_cchat("For Gondor! ");
    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"task","quest","job","servant","servants","tasks",
	"quests","jobs"}),
	    VBFC_ME("give_task"));
    add_ask("name", VBFC_ME("introduce"));
    add_ask(({"pelargir", "lebennin", }), VBFC_ME("reply_pelargir"));

    add_prop(NPC_M_NO_ACCEPT_GIVE,0);
    add_prop(LIVE_I_QUICKNESS, 25);
    GONDOR_MASTER->npcsize(TO, "tall", "normal");

    set_equipment( ({ WEP_DIR+"dlongsword",
		      WEP_DIR+"dagger",
		      MINAS_DIR+"obj/ltunic", }) );
}

public varargs void 
arm_me(int mt_equip = 0)
{
    ::arm_me(0);

    get_money();
    MONEY_MAKE_GC(5)->move(TO);
}


string 
introduce(string str)
{
    command("say Pleased to meet you, I am the Lady Gilraen.");
    command("curtsey");
    if (strlen(str))
	command("introduce me to "+str);
    else
	command("introduce me");
    return "";
}

void 
minas_tirith_wolfcave()
{
    if (TP->query_prop("_gilraen_wolfcave_quest"))
    {
	command("peer "+TP->query_name());
	command("say I've told you all I that I can about this.");
	command("say Please, go and find what remains of my father's servant!");
	return;
    }
    command("say I need to know what has happened to my father's servant!");
    command("say Long ago, when I was yet unborn, my family moved here "+
	"from Pelargir.");
    command("say Father was as yet a child himself, and he was attended "+
	"by a loyal servant.");
    command("say My grandfather, father, and some household members set "+
	"out one day for Minas Tirith.");                  
    command("say But on the way, they were ambushed by some filthy bandits.");
    command("say In an attempt to draw off some of the attackers, my "+
	"father's servant");
    command("say grabbed some of the baggage and made off towards the "+
	"mountains");
    command("say shouting all the way that he would hide the gold and "+
	"then go for reinforcements.");
    command("say His ploy worked, and most of the bandits left the battle "+
	"to follow him.");
    command("say Unfortunately, it seems his ploy worked too well, for he was");
    command("say never heard from again.");
    command("say My father searched but was never able to find him.");
    command("say All we know is that he headed northwest towards the "+
	"White Mountains");
    command("say from the road running between Minas Tirith and Pelargir.");
    command("say Please, find him or his remains, and bring back whatever "+
	"you can.");
    TP->add_prop("_gilraen_wolfcave_quest",1);
}

string 
give_task()
{
    if (!TP->test_bit("Gondor",TOUR_GROUP,GILRAEN_WOLFCAVE_BIT))
	minas_tirith_wolfcave();
    else 
	command("say Forgive me, but I have no need of your services "+
	    "at this time.");
    return "";
}

void 
reward_wolfcave_quest(object player)
{
    if (present(player,ENV(TO)))
    {
        player->remove_prop("_gilraen_wolfcave_quest");
        player->remove_prop("_gilraen_wolfcave_quest_goblet");
        player->remove_prop("_gilraen_wolfcave_quest_plates");
        player->remove_prop("_gilraen_wolfcave_quest_forks");
        player->remove_prop("_gilraen_wolfcave_quest_note");
	MONEY_MAKE_GC(5)->move(TO);
        command("give gold coins to "+TP->query_real_name());
        player->set_bit(TOUR_GROUP,GILRAEN_WOLFCAVE_BIT);
        player->add_exp_quest(GILRAEN_WOLFCAVE_QUEST_EXP);
	player->adjust_alignment(200);
        LOG_QUEST(player, GILRAEN_WOLFCAVE_QUEST_EXP, "GILRAEN WOLFCAVE");
        tell_object(player,"You feel much more experienced!\n");
    }
}

void 
test_wolfcave_quest(object player)
{
  if(TP->test_bit("Gondor",TOUR_GROUP,GILRAEN_WOLFCAVE_BIT))
  {
    command("say I appreciate your efforts, but I can't reward you "+
	"twice for the same job.");
    return;
  }

  if(player->query_prop("_gilraen_wolfcave_quest_plates"))
  {
    if(player->query_prop("_gilraen_wolfcave_quest_forks"))
    {
      if(player->query_prop("_gilraen_wolfcave_quest_goblet"))
      {
        if(player->query_prop("_gilraen_wolfcave_quest_note"))
        {
          command("say Thank you so much for aiding me.");
          command("kiss "+player->query_name());
          reward_wolfcave_quest(player);
        }
        else
        {
          command("hmm");
          command("say You've been very helpful, but did you find "+
	      "anything else?");
        }
      }
      else
      {
        command("curtsey ");
        command("say This is excellent, but have you found anything else?");
        command("say If so, please give it to me.");
        command("smile");
      }
    }
    else
    {
      command("hmm");
      command("say Are you sure you found nothing else?");
      command("peer "+player->query_name());
    }
  }
}

void 
check_item(object *arr)
{
  object ob = arr[0],
         from = arr[1];

  if(ob->query_prop("_gilraen_wolfcave_quest_plates") &&
  from->query_prop("_gilraen_wolfcave_quest"))
  {
    command("emote examines "+LANG_ADDART(ob->query_short())+" intently.");
    command("smile");
    command("say Grandfather had "+LANG_ADDART(ob->query_short())+
	" just like these.");
    from->add_prop("_gilraen_wolfcave_quest_plates",1);
    ob->remove_object();
    test_wolfcave_quest(from);
  }
  else if(ob->query_prop("_gilraen_wolfcave_quest_forks") &&
  from->query_prop("_gilraen_wolfcave_quest"))
  {
    command("emote polishes "+LANG_ADDART(ob->query_short())+".");
    command("hmm");
    command("say Oh yes, he had "+LANG_ADDART(ob->query_short())+
	". Grandfather was fond of fine dining wares.");
    from->add_prop("_gilraen_wolfcave_quest_forks",1);
    ob->remove_object();
    test_wolfcave_quest(from);
  }
  else if(ob->query_prop("_gilraen_wolfcave_quest_goblet") &&
  from->query_prop("_gilraen_wolfcave_quest"))
  {
    command("emote holds "+LANG_ADDART(ob->query_short())+
	" in her hand for a "+
      "moment.");
    command("say This was my grandfather's favorite piece, "+
	"he missed it greatly.");
    command("emote chuckles fondly.");
    from->add_prop("_gilraen_wolfcave_quest_goblet",1);
    ob->remove_object();
    test_wolfcave_quest(from);
  } 
  else if(ob->query_prop("_gilraen_wolfcave_quest_note") &&
  from->query_prop("_gilraen_wolfcave_quest"))
  { 
    command("emote reads "+LANG_ADDART(ob->query_short())+".");
    command("sob");
    command("say May he rest in peace. My search is over, "+
	"my promise fulfilled.");
    command("say Now at least we know what happened to my father's servant.");
    from->add_prop("_gilraen_wolfcave_quest_note",1);
    ob->remove_object();
    test_wolfcave_quest(from);
  }
  else if(ob->id("coin"))
  {
    command("glare "+TP->query_real_name());
    command("say We are not as rich as we used to be, but we still "+
	"don't need alms!");
    command("stand up");
    command("point door");
    command("say Begone!");
    set_alarm(10.0, 0.0, &command("sit in chair"));
  }
  else if(TP->query_prop("_gilraen_wolfcave_quest"))
  {
    command("sigh");
    command("say I don't believe this belonged to my father's servant.");
    command("give "+ob->query_name()+" to "+from->query_real_name());
    command("smile sadly");
    if ( present(ob, TO) )
    	command("drop "+ob->query_name());
  }
  else
  {
    command("say Why have you given this to me?");
    command("smile "+TP->query_name());
    command("give "+ob->query_name()+" to "+from->query_real_name());
    command("say If you really want to do something for me, why don't "+
	"you ask for a job?");
  }
}

void 
enter_inv(object ob, object from)
{
  ::enter_inv(ob,from);
  if(!from) 
    return;
  set_alarm(0.0, 0.0, &check_item(({ob, from})));
}

/* Solemnian knight prestige */
int query_knight_prestige() {return (-10);}

void
add_introduced(string str)
{
    set_alarm(2.0, 0.0, &introduce(str));
}

string
default_answer()
{
    command("say I'm not sure I understand what you are asking.");
    command("say I am looking for someone to find the remains of a "+
	"long lost servant");
    command("say and retrieve any items found with his remains.");
    return "";
}

string
reply_pelargir()
{
    command("say My family is from Pelargir in Lebennin.");
    command("say Pelargir lies at the mouths of the Anduin");
    command("say and is Gondor's largest harbour.");
    return "";
}
