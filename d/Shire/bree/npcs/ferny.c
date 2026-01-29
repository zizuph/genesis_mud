/*
* Palmer added lost horse quest Jan 2003
*
*/

inherit "/std/monster";
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/bree/rooms/town/stable/bree_stables.h"

#define QUEST_NAME "horse"

int alarm_id;
void after_attack();
void after_attack_msg();
string give_task();
int Begin_time = 0;

create_monster()
{
    if (!IS_CLONE)
        return;

    set_name("ferny");
    set_race_name("human");
    set_adj(({"squint-eyed","ill-favored"}));
    set_long("This is one of the visitors to the Prancing Pony. He looks like "
    	    +"he might not be all human, and he is listening intently to the talk in the room.\n");
    set_stats(({70,60,65,80,100,95}));
    MAKE_MONEY;
    set_alignment(-100);

    set_skill(SS_WEP_SWORD,50);
   set_skill(SS_PARRY,70);
    set_skill(SS_DEFENCE,60);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(CONT_I_WEIGHT, 60*1000);
    add_prop(CONT_I_HEIGHT, 120);
    set_gender(G_MALE);

    set_chat_time(5);
    add_act(({"emote takes out his tobacco.","emote stuffs his pipe with some tobacco.",
              "emote lights his pipe.","emote gets a big smile all over his face as he inhales some smoke from his fine pipe."}));

   add_chat("The fire could use some stoking, I think.");
   add_chat("They don't make tobacco like Old Toby anymore.");
   add_chat("There are going to be more and more people coming up the Greenway, I deem.");
   add_chat("Sharkey has put me in charge of keeping you in line!");

    set_act_time(5);
    add_act("yawn");
    add_act("smile mis");
    add_act("emote paces around the room nervously.");
    add_act("glare appledore");
    add_act("emote drinks a shot of prime liquor.");

    set_cact_time(5);
//  add_cact("shout Barliman, call the Shiriffe, "+QCTNAME(TP)+" is trying to kill me!!!");
    add_cact("knee all");
    add_cact("emote screams: STOP IT, or i will tell the Master!");

    set_cchat_time(3);
    add_cchat("You think you are tough attacking a man like me eh?");
    add_cchat("You stinking snob of an Shireling!!");
    add_cchat("Alas! I will have to kill you now.");
    add_ask(({"task", "help", "quest"}),VBFC_ME("give_task"));
    /*Triggers*/

    set_alarm(0.5,0.0,"arm_me");

}

arm_me()
{
    object knife,tunic,boots;

    FIXEUID;

    knife = clone_object(BREE_DIR + "wep/" + "rsword");
    tunic = clone_object(BREE_DIR + "arm/" + "ltunic");
/*    boots = clone_object(BREE_DIR + "arm/" + "boots");
    boots->move(TO);
*/
    knife->move(TO);
    tunic->move(TO);
    command("wear all");

}

void
attacked_by(object obj)
{
    ::attacked_by(obj);
    command("say You should not mess with me, I am stronger than I look.");
    command("emote grips the hilt of his longsword!");
    command("wield all");
    command("wear all");

    alarm_id = set_alarm(10.0, 20.0, "after_attack");
}

void
after_attack()
{
    if(TO->query_attack())
    {
        return;
    }

    else
    {
      after_attack_msg();
      return;
    }
}

void after_attack_msg()
{
  mixed *calls = get_all_alarms();
  int i;

  command("unwield all");
  command("say I am too good for them!!");
  command("say I hope Sharkey will come soon.");

  for (i = 0; i < sizeof(calls); i++)
  {
    alarm_id = calls[i][0];
    remove_alarm(alarm_id);
  }
}


void
add_introduced(string str)
{
    if (!interactive(TP) || TP->query_met(query_name()))
        return;

    command("introduce me to " + TP->query_real_name() + "");
}


string
give_task()
{
    int align;
    object uruk, orc1, orc2, horse;
    int now;

    align = TP->query_alignment();
    if (align > 0)
    {
        command("say I don't need any help from the likes of you.");
        return "";
    }

    if (Begin_time > 0)
    {
        now = time();
        if ((now - Begin_time) < 3600)
        {
            command("say Someone is helping me now. If you check back soon " +
                    "I may be able to use your help.");
            return "";
        }
    }
    if (!CHECK_QUEST(TP, QUEST_NAME))
    {
        if (TP->query_prop("_horse_quest"))
        {
            command("chuckle annoy" + TP->query_name());
            command("say Please go find my black horse!");
            return "";
        }

    command("say Well, someone tried to help me, but I think they have failed.");
    command("sigh miserably");
    command("say I sent someone to deliver a black horse to Minas Morgul. " +
    "If you can locate the black horse, take it to my contact near the gates of " +
    "Minas Morgul.");
    TP->add_prop("_horse_quest", 1);
    Begin_time = time();
    uruk = clone_object(BREE_STABLES_NPC_DIR + "uruk_leader");

    return "";
    }
    else
    {
        command("say You've already helped me.");
        return "";
    }
}

void
failed_give(object obj,object from)
{
    command("say No thank you.");
    write(TO->query_The_name(from)+" gives it back to you.\n");
    obj->move(from);
}

void
test_horse_quest(object player)
{
    if (!REWARD_QUEST(player, QUEST_NAME))
    {
        command("say You've already helped me.");
        return;
    }

    command("emote examines the scroll closely.");
    command("say Ah, yes, thank you for a job well done.");
    player->remove_prop("_horse_quest");
    player->remove_prop("_horse_trust_");
    tell_object(player,"You feel more experienced!\n");
    say(QCTNAME(player) + " looks more experienced.\n");
    return;
}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    if (!living(from))
        return;
    if (obj->id("_horse_quest_scroll_"))
    {
        obj->remove_object();
        set_alarm(2.0,0.0, &test_horse_quest(from));
    }
    else
        set_alarm(1.5,0.0, &failed_give(obj,from));
}
