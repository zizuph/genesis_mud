#include <filter_funs.h>
#include "/d/Shire/sys/defs.h"
#include "../local.h"
#include "/d/Shire/bits.h"

inherit GOBLIN_BASE;

// Prototypes
#ifndef QUESTS_CLOSED
void check_torch(object player, object ob);
#endif
void return_introduce(string player);

#define TORCHES   "_brought_torches"

string *list_introduced = ({ });
string *list_asked_help = ({ });

void create_goblin()
{
    set_base_gob(70);
    set_ran_gob(30);
    set_ran_wep(({ "club" }));
    set_ran_arm(({ "helm" }));
    set_def_arm(({ "mail", "shield" }));
    set_c_chats(({ "I hate intruders like you!",
	"I will have fresh flesh to feed on!",
	"Someone go and prepare big pot!",
	"I will sell loot from your corpse!" }));
    set_chats(({ "What do you want?",
	"I am hungry!!!",
	"You got anything nice to sell?",
	"You want to buy some nice equipment?",
	"You will not steal anything from me!",
	"You have enough money?",
	"I trade with anyone!",
	"Where can I get torches?" /* quest hint */
      }));
    set_name("grumphlin");
    set_title("Shopkeeper");
    set_long("This greedy goblin is willing to trade even with you as "+
      "long as he has some profit.\n");
    remove_prop(LIVE_I_NEVERKNOWN);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

#ifndef QUESTS_CLOSED
    add_ask(({"help","task","quest","torch","light","torches"}),
      VBFC_ME("answer_help"));
    add_ask(({"reward","about reward","for reward"}), VBFC_ME("answ_reward"));
    add_ask(({"final reward","for final reward"}), VBFC_ME("answ_final"));
#endif
}

void
add_introduced(string who)
{
    if (member_array(who, list_introduced) != -1)
	list_introduced += ({ who });
    set_alarm(1.2,0.0, &return_introduce(who));
}

void 
return_introduce(string who)
{
    if (member_array(who,list_introduced) == -1)
	list_introduced += ({who});
    if (present(who, ENV(TO))->query_race_name() == "goblin")
    { 
	command("introduce myself to "+who);
	command("bow "+ who);
    }
    return;
}

int 
query_introduced(object who)
{
    if(member_array(who->query_real_name(), list_introduced) == -1)
	return 0;
    return 1;
}

#ifndef QUESTS_CLOSED
string 
answer_help()
{
    string who_ask = TP->query_real_name();

    if (CHECK_QUEST(TP, "torch"))
    {
	command("whisper "+who_ask+" Let the others do the job now.");
	command("pat "+who_ask);
	return "";
    }
    if(member_array(who_ask, list_introduced) == -1)
    {
	command("say Introduce yourself first! I like to know who am I talking to.");
	command("peer "+who_ask);
	return "";
    }
    if(member_array(who_ask, list_asked_help) != -1)
    {
	command("say "+capitalize(who_ask)+", are you deaf??? I have already "+
	  "told you!!!");
	command("pat "+who_ask);
	return "";
    }
    list_asked_help += ({ who_ask }); /* now he has asked first time */
    command("whisper "+who_ask+" As you can see I need light for my work.");
    set_alarm(1.0,0.0,"command","whisper "+who_ask+
      " And I am always short of torches.");
    set_alarm(2.0,0.0,"command","whisper "+who_ask+
      " So your job is to bring me torches!");
    set_alarm(3.0,0.0,"command","whisper "+who_ask+
      " After you finish ask me for reward.");
    set_alarm(4.0,0.0,"command","whisper "+who_ask+
      " More you bring - the bigger reward of course.");
    return "";
}
#endif

void enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    if (!living(from)) 
	return;

    if (MASTER_OB(obj) == "/std/coins")
    {
	set_alarm(1.0, 0.0,"command", "say Money!!!");
	set_alarm(0.5,0.0,"get_rid_of",obj);
	return;
    }
#ifndef QUESTS_CLOSED
    if (member_array(from->query_real_name(), list_asked_help) == -1)
    {
	set_alarm(1.0, 0.0, "command", "say Why do you give me this?");
	set_alarm(2.0, 0.0, "command", "drop "+OB_NAME(obj));
	return;
    }
    if (member_array("/std/torch.c", inherit_list(obj)) != -1)
    {
	set_alarm(1.0, 0.0, &check_torch(from, obj));
	return;
    }
#endif

    set_alarm(1.0, 0.0, "command", "say This is not good.");
    set_alarm(2.0, 0.0, "command", "drop "+OB_NAME(obj));
}

#ifndef QUESTS_CLOSED
void check_torch(object tp, object obj)
{
    set_alarm(1.5, 0.0, "get_rid_of", obj);
    command("extinguish "+OB_NAME(obj));
    if (obj->query_time() < 200)
    {
	set_alarm(1.0, 0.0, "command", "say This "+obj->short()+
	  " will not last long enough!");
	set_alarm(1.1, 0.0, "command", "emote breaks "+obj->short()+
	  " and throws it away.");
	return;
    }
    set_alarm(2.0, 0.0, "command", "say Nice "+obj->short()+"!");
    set_alarm(3.0, 0.0, "command", "emote makes some note.");
    tp->add_prop(TORCHES, tp->query_prop(TORCHES) + 1);
}

string answ_reward()
{
    int t;

    if (member_array(TP->query_real_name(), list_asked_help) == -1)
    {
	command("say Have you done anything for me?");
	return "";
    }
    t = TP->query_prop(TORCHES);
    command("emote studies his notes.");
    if (t < 10)
    {
	set_alarm(2.0, 0.0, "command", "say You can do a lot better than that!");
    }
    else if (t < 20)
    {
	set_alarm(2.0, 0.0, "command", "say You can do better than that!");
    }
    else
    {
	set_alarm(2.0, 0.0, "command", "say You can still do better than that!");
    }
    set_alarm(3.0, 0.0, "command", "say But if you really want it now "+
      "just ask me for final reward.");
    return "";
}

string answ_final()
{
    int r, i;

    if (member_array(TP->query_real_name(), list_asked_help) == -1)
    {
	command("say Have you done anything for me?");
	return "";
    }
    i = TP->query_prop(TORCHES);
    r = MIN(TORCH_EXP, 4 * i);
    // Since the exp for this quest is variable we set it here
    if (!i)
    {
	command("say You have better bring me some torches first!");
	return "";
    }
    if (!VARIABLE_REWARD_QUEST(TP, "torch", r))
    {
	command("say I think I have already rewarded you!");
	return "";
    }
    list_asked_help -= ({ TP->query_real_name() });
    command("say Here is your reward.");
    TP->catch_msg("You feel a bit more experienced.\n");
    return "";
}
#endif

void get_rid_of(object obj){ obj->remove_object(); }

void init_attack(){}


