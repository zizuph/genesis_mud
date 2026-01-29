inherit "/std/monster";
 
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/bits.h"

//   Prototypes
void return_introduce(string who);

int not_intro;
string give_task(object who);

 void
create_monster()
{
    if (!IS_CLONE) return;
    set_living_name("_baruk_");
    set_name("baruk");
    set_race_name("dwarf");
    set_long("This dwarf is fairly tall and very stout for his age.\n");
    set_adj(({"beady-eyed","shifty"}));
    set_stats(({40,40,60,20,20,20}));
    set_alignment(-250);
 
    set_skill(SS_WEP_KNIFE,60);
    set_skill(SS_PARRY,50);
 
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(CONT_I_WEIGHT, 90*1000);
    add_prop(CONT_I_HEIGHT, 140);
    set_gender(G_MALE);
  
   set_chat_time(5);
   add_chat("That accursed Mayor...");
   add_chat("Innkeeper, another beer, please!");
   add_chat("I'm thirsty.");
   add_chat("Go away, you bother me.");
   add_chat("If only I could teach that miserable Shiriffe a thing or two...");
 
   trig_new("%w 'introduces' %s","react_introduce");
   add_ask(({"task","job","quest","help"}),VBFC_ME("refuse"));
   add_ask(({"mayor","revenge","will"}),VBFC_ME("give_task"));
 
   set_alarm(1.0,0.0,"arm_me");
}

void arm_me()
{
    object tunic;
    object flail;
    FIXEUID;
 
    tunic = clone_object(MICH_DIR + "arm/h_mail");
    tunic->move(TO);
    command("wear all");
    flail = clone_object(MICH_DIR + "wep/h_dagger");
    flail->move(TO);
    command("wield all");
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
   if(not_intro) return;
    if (obj = present(who,environment()))
    {
            command("say Go away, fool.");
            command("introduce me");
            command("say I don't want your help.");
    }
   not_intro = 1;
   set_alarm(25.0,0.0,"clear_me");

}

void
clear_me()
{
   not_intro = 0;
}

string refuse()
{
 command("frown");
 command("say I don't need anyone's help!");
 command("say Or is it you who needs help?");
 command("smirk");
 return"";
}


void
reward_roster_quest(object obj, object from)
{
    int align;
   align = from->query_alignment();


    if(!from->query_prop("_i_need_evil_align_"))
    {
      command("say Heh, clever.  But you've already given me this.");
      command("say Thanks anyway!");
      command("thank "+from->query_real_name());
      return;
    }

   command("emote hides something away in his cloak.");
   obj->remove_object();
   command("thank "+from->query_real_name());
   from->set_alignment(align - 150);
   from->catch_msg("You feel more evil for that poisoning.\n");
   return;

}


void poison_pie(object obj, object from)
{

   command("emote takes the pie and turns around for a moment.");
   command("emote does something to the pie.");
   command("emote quickly turns back around.");
   command("say This will do nicely.");
   command("say Remember, I must have that roster!");
   obj->add_prop("_poisoned_bumbleberry_pie_",1);
   command("give pie to "+from->query_real_name());
   return;
}
 

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    if (!living(from))
        return;
    if (obj->query_prop("_i_am_bumbleberry_pie_"))
    {
     set_alarmv(1.5,0.0,"poison_pie",({obj, from}));
     return;
    }

    if (obj->query_prop("_i_am_mayor_roster_"))
    {
     set_alarmv(2.3,0.0,"reward_roster_quest",({obj, from}));
     return;
    }

      if(obj->query_alco_amount())
      {
        command("drink all");
        command("thank "+from->query_real_name());
        command("hiccup");
        set_alarm(1.0,0.0,&give_task(from));
        return;
      }
    else if (obj->id("coin"))
      {
        command("say Thanks! Money will always come in handy.");
        return;
      }
    else
      {
        command("say I don't want that!");
        command("drop " + obj->query_short());
        return;
      }
}

string give_task(object who)
{
    if (who->test_bit("Shire",WESTERN_GROUP,BUMBLEBERRY_BIT))
    {

      if(who->query_alignment() > -100)
      {
        command("say Go away.");
        return "";
       }

     command("grin "+ who->query_race());
     command("say You have already served me well!");
     command("say I wouldn't want to deal with slime such as yourself again!");
     return"";
    }

    command("say You can't do this, you're too spineless...");
    command("laugh evi");
    command("say But you can try, I guess...");
    set_alarm(5.0,0.0,"task");
    return"";
}

string task()
{
  command("say Here's my problem...");
  command("whisper "+TP->query_real_name()+" I need to find out some things.");
  command("whisper "+TP->query_real_name()+" Like who will be on patrol duty.");
  command("whisper "+TP->query_real_name()+" The Mayor keeps some kind of ");
  command("whisper "+TP->query_real_name()+" record, I know it!");
  command("whisper "+TP->query_real_name()+" I want that list!");
  TP->add_prop("_doing_poison_quest_",1);
  command("grin");
  
  return"";
}

 
