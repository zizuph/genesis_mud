//
// postmaster - in village post office. operates mail delivery tour
//
// Zima  - June 10/98
//
// Refactored
// Tapakah, 08/2021


#pragma strict_types
 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

#include "defs.h"
#include "postman.h"

inherit BASE_ASHLAGH;
inherit "/d/Khalakhor/common/npc/quest-npc";

#define SACK "_ashlagh_mailsack"

string *
my_quests ()
{
  return ({ "Post Office Tour" });
}

void
arm_me ()
{
  armours = ({ COM_ARM+"shirt_wool",
               COM_ARM+"apron",
               COM_ARM+"breeches" });
  ::arm_me();
}

void
reward (mapping quest)
{
  command("say Good job " + laddie(TP) +"!");
  command("say The people of Baile Ashlagh thank you.");
  command("emote smiles mysteriously.");
  do_reward_player(quest["real_bit"], quest["new_xp"], B_A_POSTMAN_QUEST);
}
 
string
ask_reward ()
{
  mapping quest = get_next_quest();
  if (! quest)
    return "say I've already rewarded ye, "+(TP->query_name())+"!";

  if (! TP->query_prop(B_A_POSTMAN_QUEST))
    return "say Reward for what, " + laddie(TP) + "?";
      
  object sack = present("_ashlagh_mailsack",TP);
  int l = sack->get_letters();
  if (l) {
    return "say You haven't delivered all of them. You have " +
      LANG_NUM2WORD(l) + " left!";
  }

  reward(quest);
  return "";
}

string
ask_instruct ()
{
  mapping quest = get_next_quest();
  if (! quest)
    return "say I do no' have instructions fer ye, ye've done the job.";
  else if (present(SACK,TP)) {
    command("say Take the sack of mail I gave ye.");
    command("say Deliver the letters in it, the addresses are on 'em.");
    command("say Deliver 'em to the right person now, ye won't get "+
            "rewarded for a bad job!");
    command("say Don't drop that sack, and return it to me when "+
            "you're done.");
    return  "say Do a good job and I'll reward ye.";
  }
  command("say I do no' have any instructions fer ye.");
  return "say But if ye want a job, ask me for one.";
}
 
string
ask_hire ()
{
  mapping quest = get_next_quest();
 
  if (! quest)
    return "Thank you " + laddie(TP) + ", but I already used your service!";
  else if (TP->query_prop(B_A_POSTMAN_QUEST))
    return "say Ye already accepted a job from me, now get to work!";

  mapping *addresses = query_random_population(0, 0, B_A_NUM_LETTERS);
  seteuid(getuid());
  object sack=clone_object(OBJ+"mailsack");
  sack->make_letters(addresses);
  sack->move(TO);
  string s = sack->query_name();
  command("emote gets a "+s+" from a shelf.");
  command("say Now take this "+s+".");
  command("give "+s+" to "+ lower_case(TP->query_name()));
  command("drop "+s);
  command("say Deliver all the mail in it to the right people.");
  command("say Don't ever let that " + s + " out of yer hands!");
  command("say When you're done, bring it back to me and ask for reward.");
  TP->add_prop(B_A_POSTMAN_QUEST, sack->get_letters());
  return "emote manages to smile satisfactorily.";
}
 
string
ask_job ()
{
  mapping quest = get_next_quest();
  if (! quest) {
    command("say You have already delivered mail for me "+
            (TP->query_name())+".");
    return "say I'm not allowed to hire ye again.";
  }
  if (TP->query_prop(B_A_POSTMAN_QUEST))
    return ("say I already gave you a sack of mail, why don't you "+
            "deliver it?");

  command("say Aye, I have a job fer ye.");
  command("say I need someone to deliver the mail for me.");
  command("say Some is out of the village, you'll have to sail.");
  return  "say If you want the job, ask me to hire you.";
}
 
//
// defans - default reponse for asks
//
string
defans ()
{
  string title = laddie(TP);
  command("say Don't bother me now " + title + ", I've got worries galore!");
  return "";
}

void
create_khalakhor_human ()
{
  explicit_name = "litreach";
  ::create_khalakhor_human();
  add_name(({"postman","postmaster"}));
  set_adj(({"grumpy","gray-haired","agitated"}));
  set_long("He's a grumpy gray-haired human who seems to work in the "+
           "post office. He appears rather agitated at the moment.\n");
 
  default_config_npc(40);
  set_skill(SS_AWARENESS, 75);
  set_skill(SS_UNARM_COMBAT, 30);
  set_skill(SS_DEFENCE, 30);
  set_skill(SS_WEP_SWORD, 35);
  
  set_alignment(400);

  add_prop(ATTACK_TEAM,ATEAM);
 
  set_act_time(15);
  add_act("emote grumbles quietly himself.");
  add_act("say That darn boy don't deserve a job in this village!");
  add_act("say Who'm I gonna get to deliver all this mail?");
  add_act("say The gobbo's scairt off all me mailboys.");
  add_act("emote places some letters in a box.");
  add_act("emote moves a package on a shelf.");
  add_act("emote searches through a box on the shelf grumbling.");
  add_act("say You know anybody needs a job? Tell 'em to ask me!");
  add_act("sigh");
  
  add_cact("say Oh, so it's a fight you want, is it?");
  add_cact("say Ye'll not get a penny of me money, varmit!");
  add_cact("say The guards'll rip yer head off!");
  add_cact("emote growls.");
  
  set_default_answer(defans);
  add_ask(({ "instructions","for instructions" }), ask_instruct, 1);
  add_ask(({ "tour","job","quest","task","for tour","for job",
             "for task","for quest" }),
          ask_job, 1);
  add_ask(({ "mail","packages" }),
          "say Aye, I've got dozens to deliver and no one to do it for me!",1);
  add_ask(({ "problem","agitated","troubled","trouble","why agitated",
             "why troubled","why","mailboys","worries","about worries" }),
          "say Me mailboys have all quit and I have no one to deliver the "+
          "mail. You need a job?",1);
  add_ask(({ "reward","for reward"}), ask_reward, 1);
  add_ask(({ "hire", "hire me", "to hire me", "to hire" }), ask_hire, 1);
 
  remembered = ([]);
  set_size_descs("short", "lean");
}
 
void
hook_return_intro_new (string str)
{
  command("say Hello thar  " + capitalize(str) + "!");
  command("say I'm "+ query_name() + " " + query_title());

  command("bow");
  command("say Pardon me but I'm a bit troubled at the moment "+
          "and a bit agitated.");
}
void
hook_return_intro_good (string str)
{
  command("say Aye, we met earlier " + capitalize(str) + ".");
  command("say Litreach may be old, but he's still got his mind!");
  command("wink");
}
