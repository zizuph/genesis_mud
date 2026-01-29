inherit "/std/monster";

#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

#define THIS_ONE_GOT_IT "_this_one_got_it_"
#define TALKED_TO_WIFE  "_player_talked_to_wife"
#define CARVING         "_woodcutter_quest_carving"

static int armed;

void arm_me()
{
  if(armed) return;
  armed = 1;
  reset_euid();
  clone_object(RHUN_DIR+"npc/hatchet")->move(TO, 1);
  command("wield all");
}

void create_monster()
{
  set_alarm(0.0, 0.0, "arm_me");

  set_race_name("human");
  set_name("woodcutter");
  set_adj("handsome");
  set_short("handsome woodcutter");

  set_alignment(100);
  set_gender(0);
  set_long("This handsome woodcutter seems to be a hard-working man"
	+" who has spent most of his time in the outdoors. He"
	+" appears quite friendly.\n");
  add_prop(CONT_I_WEIGHT, 72*1000);
  add_prop(CONT_I_VOLUME, 74*1000);
  add_prop(CONT_I_HEIGHT, 174);
  set_stats(({82, 74, 85, 70, 70, 82}));

  set_skill(SS_UNARM_COMBAT, 34);
  set_skill(SS_WEP_AXE, 90);
  set_skill(SS_DEFENCE, 78);
  set_pick_up(43);

  set_chat_time(6);
  add_chat("I love working in the forest.");

  set_act_time(4);
  add_act("flex");
  add_act("smile knowingly");
  add_act("emote takes a deep breath of fresh air.");

  add_ask(({"affair","house","about affair","about house"}),
                                     VBFC_ME("answ_affair"));
  add_ask(({"bitch","about bitch"}), VBFC_ME("answ_bitch"));
  add_ask(({"wife","about wife"}), VBFC_ME("answ_wife"));
}

string answ_affair()
{
  if(TP->query_prop(THIS_ONE_GOT_IT))
  {
    command("say Why do you ask me about it again? I have already "+
            "told you how is it.");
    return "";
  }
  if(!TP->query_prop(TALKED_TO_WIFE))
  {
    command("say Now I have other things on my mind than houses and affairs.");
    return "";
  }
  TP->remove_prop(TALKED_TO_WIFE);
  command("say So now she thinks that I am building a house for my fiance.");
  set_alarm(1.0,0.0,"command","say As you can see I am really preparing "+
                              "wood for town wall as mayor asked me.");
  set_alarm(2.0,0.0,"command","say Why it takes so long she asks? I will "+
                              "tell you the truth.");
  set_alarm(3.0,0.0,"command","whisper "+TP->query_real_name()+
                              " I enjoy the time I am away from her.");
  set_alarm(4.0,0.0,"command","whisper "+TP->query_real_name()+
                            " I am starting to hate her for all her nagging.");
  set_alarm(5.0,0.0,"command","whisper "+TP->query_real_name()+
         " I will have an affair sooner or later if she goes on like this.");
  set_alarm(6.0,0.0,"command","say But please don't tell her this. Instead "+
         "tell her that I must work very slowly because otherwise I could "+
       "attract attention of Easterlings. And that would make her a widow.");
  set_alarm(7.0,0.0,"command","say Please give her this and tell her that "+
                              "I have to stay here for another month!");
  reset_euid();
  clone_object(RHUN_DIR+"npc/carving")->move(TO,1);
  set_alarm(8.0,0.0,"command","give "+CARVING+" to "+TP->query_real_name());
  set_alarm(9.0,0.0,"command","smile");
  TP->add_prop(THIS_ONE_GOT_IT, 1);
  return "";
}

string answ_bitch()
{
  command("say Yes, I know what a bitch is...");
  set_alarm(1.0,0.0,"command","say Sometimes I'd say that my wife is a bitch.");
  set_alarm(2.0,0.0,"command","say She always nags me for nothing.");
  set_alarm(3.0,0.0,"command","sigh");
  return "";  
}

string answ_wife()
{
  command("say Have you brought me some news from her?");
  set_alarm(1.0,0.0,"command","peer at "+TP->query_real_name());
  return "";
}
