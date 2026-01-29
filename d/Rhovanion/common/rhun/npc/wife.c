inherit "/std/monster";

#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

#define RHUN_TOUR       "_rhun_tour"
#define KILLED_WIFE     "_player_killed_wife"
#define DONE_WOOD       "_player_done_woodcutter"
#define TALKED_TO_WIFE  "_player_talked_to_wife"
#define CARVING         "_woodcutter_quest_carving" 


void create_monster()
{
  object ob;

  set_race_name("human");
  set_name(({"woman","wife"}));
  set_adj(({"woodcutter","distraught"}));
  set_short("distraught woman");

  set_alignment(50);
  set_gender(1);
  set_long("This distraught-looking woman lives here. She is"
          +" apparently the wife of the woodcutter who owns this"
          +" small house.\n");
  add_prop(CONT_I_WEIGHT, 70*1000);
  add_prop(CONT_I_VOLUME, 70*1000);
  add_prop(CONT_I_HEIGHT, 168);
  remove_prop(NPC_M_NO_ACCEPT_GIVE);
  set_stats(({20,25,20,25,25,20}));

  set_skill(SS_UNARM_COMBAT, 12);
  set_skill(SS_DEFENCE, 12);
  set_pick_up(43);

  set_chat_time(4);
  add_chat("Have you seen my husband?");
  add_chat("Where is he so long?");
  add_chat("Is it true that he has an affair?");

  set_act_time(4);
  add_act("sob");
  add_act("cry");
  add_act("sniff");
  add_act("emote blows her nose into a small handkerchief.");
  add_act("emote wrings out a small, very wet handkerchief.");

  reset_euid();
  ob=clone_object(RHUN_DIR+"npc/handkerchief");
  ob->move(TO, 1);

  add_ask(({"husband","woodcutter","about husband","about woodcutter"}),
                                           VBFC_ME("answ_func"));
  add_ask(({"easterling","about easterling",
            "easterlings","about easterlings"}), VBFC_ME("answ_easterling"));
  set_default_answer(VBFC_ME("def_answ_func"));
  set_dont_answer_unseen(1);
}

string def_answ_func()
{
  command("say I don't know about such things. I care only for my husband.");
  return "";
}

string answ_easterling()
{
  command("say Yes... I have heard that they are somewhere near.");
  set_alarm(1.0,0.0,"command","say Hope they don't harm my husband.");
  return "";
}

string answ_func()
{
  if(TP->query_prop(RHUN_TOUR) != 3)
  {
    command("say Why do you ask?");
    set_alarm(1.0,0.0,"command","peer at "+TP->query_real_name());
    set_alarm(2.0,0.0,"command","say Are you an Easterling spy?");
    return "";
  }
  if(TP->query_prop(TALKED_TO_WIFE))
  {
    command("say Please, can you do as I told you?");
    return "";
  }
  command("sniff");
  set_alarm(1.0,0.0,"command","say Could you find him? Could you?");
  set_alarm(2.0,0.0,"command","say I have heard that he has an affair and "+
                              "that he is building a house for that bitch! "+
                              "That is why he is away so long.");
  set_alarm(3.0,0.0,"command","say Please, ask him about it. "+
                              "I have to know the truth!");
  set_alarm(4.0,0.0,"command","emote blows her nose heavily into a small "+
                              "handkerchief.");
  set_alarm(4.0,0.0,"command","say They tell me that he's working for mayor. "+
                              "Preparing some wood they say. But I know it "+
                              "is a lie! It never took so long before.");
  set_alarm(6.0,0.0,"command","sob");
  TP->add_prop(TALKED_TO_WIFE,1);
  return "";
}

void enter_inv(object obj,object from)
{
  string ooo, *adjs;

  ::enter_inv(obj,from);
  if(!living(from)) return;

  if(member_array(CARVING,obj->query_names()) != -1)
  {
    set_alarm(1.0,0.0,"command","say Oh, thank you!");
    set_alarm(2.0,0.0,"command","say Now I know he still loves me!");
    set_alarm(4.0,0.0,"command","say I will not go to complain to mayor then.");
    set_alarm(6.0,0.0,"command","smile");
    TP->add_prop(DONE_WOOD, 1);
    return;
  }
  adjs = obj->query_adjs();
  if (!adjs) adjs = ({ });
  ooo = implode(adjs+({LOW(obj->query_name())}), " ");
  set_alarm(1.0,0.0,"command","say Why do you give me this?");
  set_alarm(2.0,0.0,"command","drop "+ooo);
}

void do_die(object killer)
{
  killer->add_prop(KILLED_WIFE, 1);
  ::do_die(killer);
}

