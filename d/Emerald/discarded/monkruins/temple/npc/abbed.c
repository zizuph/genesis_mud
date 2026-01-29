/* temple/npc/abbed.c is cloned by temple/court_e.c"  */
inherit "/std/monster";
 
#include "/d/Emerald/defs.h"
#include "/d/Emerald/lib/prestige.h"
#include "/d/Emerald/lib/make_money.h"
#include "/d/Emerald/lib/quests.h"
 
#define QUEST_NAME "ring"
#define RING_QUEST_GROUP 0
#define RING_QUEST_BIT 0
#define RING_QUEST_EXP 1000
 
/* Function prototypes */
void givebag( object from );
void help_friend(object friend);
void return_introduce(string who);
void drop_th(object obj);
void rew_talk(object player);
void talk_hl();
void reward_ring_quest(object player);
void ring_quest();

object keyob;
 
create_monster()
{
    if (!IS_CLONE) return;
    set_name("abbot");
    set_race_name("human");
    set_short("abbot");
set_long("He looks like he is quite dedicated to his work. He appears "+
             "to be looking for something.\n");
    set_stats(({40,60,50,50,80,90}));
 
    set_skill(SS_HERBALISM,20);
    set_skill(SS_DEFENCE,30);
    set_skill(SS_FORM_DIVINATION,25);
    set_skill(SS_ELEMENT_LIFE,40);
    set_skill(SS_APPR_MON,70);
    set_skill(SS_AWARENESS,45);
 
    remove_prop(NPC_M_NO_ACCEPT_GIVE,0);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(CONT_I_WEIGHT, 70*1000);
    add_prop(CONT_I_HEIGHT, 110);
    set_gender(G_MALE);
    set_alignment(150-random(200));
 
   set_chat_time(5);
   add_chat("Why am I so forgetful?");
   add_chat("It's hard to serve the God of Doomed, you know.");
   add_chat("My ring is lost! My beautiful ring!");
   add_chat("Our dungeon cells are empty! Do not break our rules, or... ");
   add_chat("The thief was nasty! I'm glad to see him imprisoned!");
 
   trig_new("%w 'introduces' %s","react_introduce");
   add_ask(({"task","help","quest","ring"}),VBFC_ME("give_task"));
   add_ask(({"thief"}),VBFC_ME("info"));
   add_ask(({"key","cell","cells"}),VBFC_ME("info2"));
}
 
void
attacked_by(object ob)
{
 object *arr;
 int i;
 
 ::attacked_by(ob);
 arr=(object *)query_team_others();
 for (i = 0; i<sizeof(arr);i++)
    arr[i]->notify_ob_attacked_me(this_object(), ob);
}
 
void
notify_ob_attacked_me(object friend,object attacker)
{
  if (query_attack()) return;
  if (random(10))
      set_alarm(1.0,0.0,"help_friend",attacker);
  return;
}
 
void
help_friend(object ob)
{
  if (ob && !query_attack() &&  present(ob,environment()))
   {
    command("say You didn't really think it would be easy, " +
                "did you?");
    command("kill" +  lower_case(ob->query_real_name()));
   }
}
 
void arm_me()
{
    clone_object(TEMPLE_DIR + "arm/m_robe")->move(TO,1);
    clone_object(TEMPLE_DIR + "obj/h_book")->move(TO,1);
    command("wear all");
    MAKE_MONEY;
}
 
int
react_introduce(string who, string dummy)
{
    if (who)
    {
        who = lower_case(who);
        set_alarm(3.0,0.0,"return_introduce",who);
        return 1;
    }
}
 
void
return_introduce(string who)
{
    object obj;
 
    if (obj = present(who,environment()))
    {
            command("eyebrow" + who);
            command("hmm");
            command("say Nice to meet you, " + capitalize(who) + ".");
            command("say We do not introduce ourselves here.");
            command("emote mumbles something about rules.");
            command("say So you don't expect I'll introduce, do you?");
    }
}
 
void test_ring_quest(object player)
{
    if(player->test_bit("Emerald",RING_QUEST_GROUP,RING_QUEST_BIT))
    {
      command("say I do not recognize this ring!");
      command("say But thanks, I like it anyway.");
      return;
    }
    if(!player->query_prop("_me_found_ring_"))
     {
       command("emote mumbles a prayer.");
       command("hmm");
       command("say God doesn't want to reward you!.");
       command("say Go away, if you broke his rules!");
       return;
     }
       set_alarm(2.0,0.0,"rew_talk",player);
       return;
}
 
void rew_talk(object player)
{
     command("say Thank you very much!");
     command("say I'm very glad to get your help!");
     command("say Let God reward you!");
            reward_ring_quest(player);
}
 
string give_task()
{
 if (!TP->test_bit("Emerald",RING_QUEST_GROUP,RING_QUEST_BIT))
    {
        ring_quest();
        return "";
    }
      command("say It's nice to see that you are so helpful!");
      command("say But I don't want to bother you anymore.");
      return "";
}

void
losekey()
{
  keyob->remove_object();
} 

void
thankkey()
{
  command("say Oh, thank you very much! But it's not that "+
          "important comparing to loss of my ring...");
  set_alarm(1000.0,0.0,losekey); 
}

 
void ring_quest()
{
    if(TP->query_prop("_ring_quest_"))
    {
      command("sigh");
      command("say I already gave you a task!");
      command("say Please go and find my ring.");
      return;
    }
    command("smile");
    command("say You know, I am a very forgetful man.");
    command("say And clumsy too...");
    command("say I lost my ring of Abbot.");
    command("say It was blessed by our God, God of Doomed.");
    command("say So if you find it and bring to me, I'll ask my God " +
            "to reward you.");
    command("say Go, and let God help you in your quest.");
    TP->add_prop("_ring_quest_",1);
}
 
void
reward_ring_quest(object player)
{
          player->set_bit(RING_QUEST_GROUP,RING_QUEST_BIT);
          player->add_exp(RING_QUEST_EXP,0);
          tell_object(player,"You feel more experienced!\n");
          ENV(TO)->questdone();
}
 
 
public void
enter_inv(object obj, object from)
{
 
  ::enter_inv(obj, from);
  if (!living(from))
      return;
  if (obj->id("_abbot_quest_ring_")) {test_ring_quest(from);}
  else
   if (obj->id("_ring_quest_bag_"))
    {
      set_alarm(2.0,0.0,"givebag",from);
      return;
    }
  else
   if (obj->id("_ring_quest_key_"))
    {
      keyob=obj;
      set_alarm(1.0,0.0,thankkey);
      return;
    }
    else
    {
      set_alarm(2.0,0.0,"drop_th",obj);
      return;
    }
}
 
string info()
{
    command("say Yes, there was a monk who stole many items " +
            "from fellow-monks.");
    command("say When we found out who it is, we threw him into our " +
            "dungeon!");
    command("grin");
    command("say When the mayor of Telberin learned about him, he " +
            "sent some Paladins to us, and we never heard about " +
            "that thief again.");
    command("sigh sadly");
    command("say But we didn't find the things he stole!");
    return"";
}
 
string info2()
{
  command("say A key? The key from the prison cell you mean? Yes, I " + 
            "have it, a big gold key.");
  command("emote searches in his pockets.");
  if (!keyob)
   {
      command("say Hmm... I lost it somewhere... So nobody can " +
            "get into the cell now.");
      command("sigh");
      command("say I have to order a new key somewhere...");
      command("think it.");
   }
  else
   {
     command("emote finds a key in the deepest one.");
     command("say Here it is! I don't need it now, so you can take " +
               "it...");
     command("emote tries to hand a key, but...");
     command("drop key");
     command("say Ooops! How clumsy I am! Could you please take it " +
               "by yourself? My back aches when i try to stoop...");  
    }  
  return"";
}

void givebag( object from )
{
  object shovel;
 
      command("emote opens the bag.");
      command("emote gets some jewels from the bag.");
      command("say I know who owns these jewels!");
      command("emote puts some jewels in the bag.");
      command("emote gets a silver crucifix from the bag.");
      command("gasp");
      command("say The crucifix from our temple!");
      command("emote puts crucifix in the bag.");
      command("emote gets a small shovel from the bag.");
      command("hmm");
      command("say I don't recognize this shovel...");
      command("emote closes the bag.");
      command("thank " + from->query_real_name());
      command("say I'm very glad that you found these stolen items.");
      command("say But I still hope that you'll find my ring.");
      command("say Here, you keep this shovel...");
      shovel=clone_object(TEMPLE_DIR + "obj/shovel");
      shovel->move(TO);
      command("give shovel to " + from->query_real_name());
      command("say I don't need this item... so you may " +
                "as well take it.");
}
 
void drop_th(object obj)
{
      command("say I don't need that.");
      command("drop " + obj->query_short());
}
 
int
special_attack(object enemy)
{
  int heal;
 
  if(random(6) != 3) return 0;
  if(TO->query_hp() > TO->query_max_hp() - 50) return 0;
  if(TO->query_mana() < 50)
  {   tell_room(ENV(TO),QCTNAME(TO) + " closes his eyes, but fails " +
          "to concentrate enough.\n");
      return 1;
  }
  tell_room(ENV(TO),QCTNAME(TO) + " closes his eyes and " +
             "looks concentrated.\n");
  set_alarm(2.0,0.0,talk_hl);
  heal = random(40) + 10;
  TO->heal_hp(heal);
  TO->add_mana(-heal);
  return 1;
}
 
void talk_hl()
{
  tell_room(ENV(TO),QCTNAME(TO) + " mumbles a prayer and " +
                "heals himself.\n");
  return;
}
