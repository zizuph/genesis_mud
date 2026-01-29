/*
 * Shirriffe of Bree, the Old Ferumbras of Old Bree, Updated for Bree
 * Sanford was named after a Sharpie that was on ny desk
 * -- Finwe, April 2002
 */

inherit "/std/monster";

//#include "/d/Shire/common/defs.h"
#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/bits.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define QUEST_NAME "locket"

/* Function prototypes */
void reward_locket_quest(object player);
void locket_quest();
void return_introduce(string who);

int alarm_id;

create_monster()
{
    if (!IS_CLONE)
        return;

    set_living_name("sanford");
    set_name("sanford");
    set_title("the hermit of Bree");
    set_race_name("human");
    set_long("This is the hermit of Bree. People of Bree talk about how " +
        "strange and loopy he is. he lives alone up here in the shack. " +
        "However, there's no denying, he's a good lookout and watches the " +
        "road up here.\n");
    set_adj(({"babbling","distracted"}));
    set_stats(({65,65,60,80,100,30}));
    MAKE_MONEY;
    set_alignment(350);
    
    set_skill(SS_WEP_KNIFE,50);
    set_skill(SS_DEFENCE,50);
    
    remove_prop(NPC_M_NO_ACCEPT_GIVE,0);
    add_prop(CONT_I_WEIGHT, 70*1000);
    add_prop(CONT_I_HEIGHT, 110);
    set_gender(G_MALE);

    set_chat_time(2);
    add_chat("I wonder who is behind the orcs near here.");
    add_chat("Boy, those Staddle hobbits are really funny.");
    add_chat("Ever seen a rabbit hop by chased by a goose? I have, funniest thing ever!");
    add_chat("Boy, the Hobbits of Archet are a strange lot.");
    add_chat("Be careful of those Southrons. They're not trustworthy.");
    add_chat("It gets cold up here when the wind blows.");
    trig_new("%w 'introduces' %s","react_introduce");
    add_ask(({"task","help","quest","job","orc"}),VBFC_ME("give_task"));

    set_alarm(1.0,0.0,"arm_me");    
}

arm_me()
{
    object tunic;
    
    FIXEUID;

    tunic = clone_object(ARM_DIR + "ltunic");
    tunic->move(TO);
    command("wear all");
   
}

int
react_introduce(string who, string dummy)
{
    if (who)
    {
        who = lower_case(who);
        set_alarm(3.0,0.0,&return_introduce(who));
        return 1;
    }
}

void
return_introduce(string who)
{
    object obj;
    int    ran;
    
    if (obj = present(who,environment()))
    {
        ran = random(3);
        if (ran == 0)
        {
            command("say Good day " + obj->query_cap_name() +
                ", are you looking for a task here?");
            command("introduce me");
            command("smile " + who);
            command("shake " + who);
        }
        if (ran == 1)
        {
            command("bow to " + who);
            command("introduce me");
            command("say Welcome " + CAP(who) +
                ", can I help you with something?");
            command("smile serious " + who);
        }
        if (ran == 2)
        {
            command("introduce me");
            command("say Greetings " + CAP(who) + ".");
            command("bow deeply to " + who);
        }
    }
}


void test_locket_quest(object player)
{
int ix;
    ix = player->test_bit("Shire",EASTERN_GROUP,BREE_LOCKET_BIT);
    if(player->test_bit("Shire",EASTERN_GROUP,BREE_LOCKET_BIT))
    {
      command("say I appreciate your efforts, but you already helped me.");
      return;
    }
    command("gasp");
    command("say I know just who this is! Just wait till...");
    command("blush");
    command("Oh, sorry, didn't mean to have an outburst.");
    command("say Thank you so much for aiding me.");
    command("shake " + player->query_name());
    reward_locket_quest(player);

}


string give_task()
  {
    if (!TP->test_bit("Shire",EASTERN_GROUP,BREE_LOCKET_BIT))
    {
        locket_quest();
        return "";
    }
    else 
    {
        command("say Forgive me, but I have no need of your "+
        "services at this time. It looks like you either helped me " +
        "or my friend Ferumbras in the past.");
        command("emote smiles thankfully.");
        return "";
    }
}


void locket_quest()
{
    if(TP->query_prop("_bree_locket_quest"))
    {
        command("peer " + TP->query_name());
        command("say I've told you all I that I know about this.");
        command("say Please, go and find out what you can!");
        return;
    }
    command("say I need to know who is behind the orcs that are moving");
    command("say in around Bree. They could not avoid the Bounders");
    command("say without some sort of aid. I fear this is the beginning");
    command("say of the end for the Shire, if we cannot unite against");
    command("say such nasty creatures. Please bring me some identification");
    command("say of the spy, hobbit or human, and I will reward you well!");
    TP->add_prop("_bree_locket_quest",1);
}

void
reward_locket_quest(object player)
{
    player->remove_prop("_bree_locket_quest");
    player->set_bit(EASTERN_GROUP,BREE_LOCKET_BIT);
    player->add_exp(BREE_LOCKET_EXP,0);
    seteuid(getuid(TO));
    log_file(QUEST_NAME, extract(ctime(time()),4,15) + " " +
        CAP(player->query_real_name()) + " rewarded with "+BREE_LOCKET_EXP+" exp, "+
        "<"+player->query_average_stat()+"> avg stats.\n");
        tell_object(player,"You feel much more experienced!\n");
    say(QCTNAME(player) + " got a nice reward.\n");
}

public void
enter_inv(object obj, object from)
  { 
    ::enter_inv(obj, from);
    /*command("say DEBUG: enter_inv entered with from = " + (objectp(from) ? from->query_name() : " no object ") +
    " and obj = " + (objectp(obj) ? obj->query_name() : " no object "));*/
    if (!living(from))
        return;

    if (obj->id("_orc_locket_")) test_locket_quest(from);
    else
    {
        command("say I have no need for such things.");
        write("The hobbit gives it back to you.\n");
        obj->move(from);
        return;
    }
  }
