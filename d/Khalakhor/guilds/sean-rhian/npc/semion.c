// Abbot of MacDunn Kirk - gives incense quest and rewards
//
//   Coder         Date                Action
// -------------- -------- ----------------------------------------------
// Zima           1/10/98  Created
// Zima           6/16/98  Second tour (honey/candles) added
// Zima           6/24/98  Third tour (oil) added
// Damaris        01/2001    Removed set_short
// Tapakah        08/2021  Refactored
//

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include "/d/Khalakhor/sys/paths.h"
#include "defs.h"

inherit "/d/Khalakhor/common/npc/quest-npc";
inherit SR_NPC+"monkbase";

string *
my_quests ()
{
  return ({"Incense Quest", "Honeycombs", "Blubber Oil" });
}

//
// DO_REWARD - give the player his reward
//
void
do_reward (int step, mapping quest)
{
  switch (step) {
  case 1:
    command("emote raises his hands and closes his eyes.");
    break;
  case 2:
    command("emote chants: Tuarasdal Ardaugh eh shoh "+ TPQN +
            " los seirbhis ayds!");
    do_reward_player(quest["real_bit"], quest["new_xp"],
                     ({SEMIONS_BLESSING, GEBANNS_BLESSING,
                       BRIARS_BLESSING, BALANS_BLESSING}));
    break;
  case 3:
    command("emote lowers his hands and opens his eyes.");
    command("say May Ardaugh grant you harmony, "+TPQN+"!");
    return;
  }
  set_alarm(3.0,0.0,&do_reward(step+1, quest));
}
 
//
// GIVE_INSTRUCTIONS - slowly give the blessing and instructions for quest
//
void
give_instructions (int step, mapping quest)
{
  // give initial blessing and final instructions for all tours
  if (step <= 3 || step >= 10)
    switch (step) {
      // steps for blessing before instructions
    case 1:
      command("emote raises his hands and closes his eyes.");
      break;
    case 2:
      command("emote chants: Bennaghey Ardaugh eh shoh "+ TPQN +
              " los seirbhis ayds!");
      TP->add_prop(SEMIONS_BLESSING, quest);
      log_quest(quest["real_bit"], TPQN, "quest started");
      break;
    case 3:
      command("emote lowers his hands and opens his eyes.");
      command("say Now listen carefully...");
      break;
      // steps for returning for reward after instructions
    case 10:
      command("say Receive his blessing of thanks, return here, "+
              "and ask me for your reward.");
      break;
    case 11:
      command("say May the Solsheyderi bless you on your quest.");
      return;
    }
 
  // give instructions for incense quest
  else if (quest["name"] == "Incense Quest")
    switch (step) {
    case 4: command("say You are to make a handful of incense from "+
                    "scratch.");
      break;
    case 5: command("say See brathair Finegas for the recipe.");
      break;
    case 6: command("say Take the incense to Gebann the prior of the "+
                    "kirk in the village of Tabor Sogh.");
      step=9; // skip steps 7-9 for incense quest
    }

  // give instructions for honey and candles tour
  else if (quest["name"] == "Honeycombs")
    switch (step)  {
    case 4: command("say My friend prior Briareus is having a "+
                    "birthday soon.");
      break;
    case 5: command("say I would like for you to make and deliver "+
                    "some gifts to him.");
      break;
    case 6: command("say You are to make three handmade beeswax "+
                    "candles. Just plain ones will do.");
      break;
    case 7: command("say While you are at it, get a pot of fresh "+
                    "honey. Briareus loves that!");
      break;
    case 8: command("say Give the candles and pot of honey to him. "+
                    "You'll find him in his kirk in Baile Ashalgh.");
      step=9; // skip step 9
      break;
    }
  else if (quest["name"] == "Blubber Oil")
    switch (step) {
    case 4:
      command("say Brathair Tinne, a novishagh, is feeling "+
              "rather ill.");
      break;
    case 5:
      command("say Brathair Balantrum is looking after him, "+
              "but he needs help.");
      break;
    case 6:
      command("say They should be in the kirk or abbey "+
              "somewhere, Balantrum won't let Tinne out of "+
              "his sight.");
      command("chuckle");
      break;
    case 7:
      command("say Go see if you can help brathair Balantrum.");
      step=9; 
      break;
    }
  else return; // invalid quest number
 
  set_alarm(3.0,0.0,&give_instructions(step+1, quest));
}
 
//
// GIVE_QUEST - invoked in add_ask()
//
string
give_quest ()
{
  int i;
  mapping quest = TP->query_prop(SEMIONS_BLESSING);;
  // see if he's already been given a quest
  if (quest) {
    set_alarm(4.0, 0.0, &give_instructions(4, quest));
    command("say I have already given you a task, "+ TPQN +".");
    return "say But I shall repeat it for you.";
  }
 
  // see if there are any quests the player has not done
  quest = get_next_quest();
  if (! quest) {
    command("say You have completed all the tasks I have for you, "+ TPQN +".");
    return  "say But return in a few weeks and perhaps I can think "+
      "of something else.";
  }
 
  set_alarm(4.0,0.0,&give_instructions(1, quest));
  command("say Yes I do have something for you to do, "+ TPQN +".");
  return "say But you'll need my blessing first.";
}
 
//
// ASK_REWARD - invoked by vbfc in add_ask
//
string
ask_reward ()
{
  mapping quest = TP->query_prop(SEMIONS_BLESSING);
 
  // see if he's been given a task
  if (! quest)
    return "say But you do not have my blessing to do a task for me!";
 
  // see if he's already been rewarded for that task
  if (quest_done(quest))
    return "say I have already rewarded you for that task.";
 
  // see if he's completed the new task
  switch (lower_case(quest["name"])) {
  case "incense quest":
    if (!(TP->query_prop(GEBANNS_BLESSING)))
      return "say You do not have Prior Gebann's blessing. I "+
        "can not reward you.";
    break;
  case "honeycombs":
    if (!(TP->query_prop(BRIARS_BLESSING)))
      return "say You do not have Prior Briareus' blessing. I "+
        "can not reward you.";
    break;
  case "blubber oil":
    if (!(TP->query_prop(BALANS_BLESSING)))
      return "say You do not have Brathair Balantrum's blessing. "+
        "I can not reward you.";
    break;
  }
 
  set_alarm(4.0,0.0,&do_reward(1, quest));
  return "say You have done a good work! I shall reward you now!";
}

string
defans ()
{
  command("say I can not answer that. Perhaps you can learn more in our "+
          "library.");
  return "";
}
 
//
// ask_incense
//
string
ask_incense ()
{
  int done         = quest_done("Incense Quest");
  mapping sembless = TP->query_prop(SEMIONS_BLESSING);
 
  command("say It is a powder which emits white smoke and a powerful "+
          "scent when burned.");
  command("say We often use it in our rites.");
 
  if (done) {
    command("say You should know much about it by now.");
    return "smile";
  }
  if (TP->query_prop(GEBANNS_BLESSING)) {
    command("say Ah, I sense that you have completed your task!");
    return  "say Ask me for your reward and I shall bless you!";
  }
 
  if (sembless["name"] == "Incense Quest")
    return "say Brathair Finegas can help you with the recipe.";
 
  if (sembless)
    return "say When you finish the task I gave you, I have another "+
      "dealing with incense should you want it.";
 
  command("say In fact, I have a task for you dealing with incense.");
  command("say Just ask me for a task if you wish to try it.");
  command("say Or perhaps there is something else I should have you do.");
  return  "hmm";
}
 
void
do_add_asks ()
{
  // general questions
  set_default_answer(defans);
  add_ask(({"order","manach","manachs","monk","monks","faith","sean-rhian",
            "way","the way","ardaugh","triad","oath","covenant",
            "the covenant","sagart","saggarts","history","angel",
            "archangel","maighal","scapular","tonsure","cincture","mitre",
            "habit","solsheyderi","statue","elves","goblins","chaos",
            "oath","covenant","harmony","Solsheyderi"
          }),
          "say You may learn of that in our library.",1);
  add_ask(({"seanchan tor","Seanchan Tor"}),
          "say He is one of the Solsheyderi, the one to whom this kirk "+
          "and abbey are dedicated.",1);
  add_ask(({"garden","herbs"}),
          "say We have a well-kept garden here, its bounty available to all."
          ,1);
  add_ask(({"blademaster","blademasters"}),
          "say Ah, they are a fine troop of brave souls.",1);
  add_ask(({"skills","alchemy","language","spellcraft","herbalism"}),
          "say We teach arcane skills here in the abbey to all who "+
          "can pay.",1);
  add_ask("cathair",
          "say The cathair is the chair where I sit when presiding over "+
          "official ceremonies.",1);
  add_ask(({"crozier","about crozier","what is crozier"}),
          "say A crozier is a staff carried by Abbots of the Order.",1);
  add_ask(({"Ardmaugh","ardmaugh"}),
          "say Ardmaugh is the holy city of Sean-Rhian, the cathair of the "+
          "Seirsanach, off a distant coast of Khalakhor.",1);
  add_ask(({"novice","novices","novishagh","novishaghs"}),
          "say The novishaghs are the novices of our order.",1);
  add_ask("kirk",
          "say It is the central place of worship for our order, built "+
          "long ago.",1);
  add_ask("abbey",
          "say It is the place where we live and work.",1);
  add_ask(({"join","guild","to join","how to join","joining","seeker",
            "seekers","disciple","disciples","note","future","member",
            "layman"
          }),
          "say Our order is not yet open to outsiders, though soon. "+
          "Contact Oracle Zima if you have questions.",1);
  add_ask(({"oracle","zima","oracle zima"}),
          "say Zima is the Oracle of Sean-Rhian. You may mail him if "+
          "you wish.",1);
  add_ask(({"bell","bells"}),
          "say The bells can be heard throughout the village.",1);
  add_ask("altar",
          "say The altar is the center of our worship.",1);
  add_ask(({"candle","candles"}),
          "say We make fine candles here. It is how we support our kirk.",1);
  add_ask(({"jonaugh","Jonaugh","jonaugh III","Jonaugh","seirsanach"}),
          "say The Seirsanach is the ruler of the Order of Sean-Rhian. "+
          "That office is held by Jonaugh III.",1);
  add_ask(({"abbot","bishop"}),
          "say I am the abbot, or head manach, of this kirk.",1);
  add_ask("help",
          "say How can I help you? Perhaps you can ask me something and "+
          "I can answer.",1);
  add_ask("monstrance",
          "say It is a very holy object. You should treat it with reverence "+
          "and not touch it.",1);
  add_ask("shamrock",
          "say It is an herb holy to our faith.",1);
  add_ask(({"emblem","circles","tricircum"}),
          "say The tricircum is the emblem of our order. It consists of "+
          "three circles interlocked, in the shape of a shamrock.",1);
  add_ask(({"martyr","martyrs","obelisk"}),
          "say An obelisk marks the mass grave of the martyrs of the "+
          "abbey. They were slaughtered in a goblin attack. May they rest "+
          "in harmony.",1);
  add_ask("library",
          "say It is in the abbey, further down the corridor.",1);
 
  // incense quest related asks
  add_ask(({"job","quest","quests","tour","for job","for quest","for tour",
            "task","for task"}), give_quest, 1);
  add_ask(({"incense","for incense","about incense","make incense",
            "how to make incense","recipe","incense recipe",
            "recipe for incense"}), ask_incense, 1);
  add_ask(({"reward","for reward","for my reward"}),
          "@@ask_reward",1);
  add_ask(({"blessing","for blessing","to bless me"}),
          "say If you wish my blessing, you must complete a task. If you "+
          "have completed the task, ask me for your reward.",1);
  add_ask(({"gebann","Gebann"}),
          "say Gebann is the Prior of the Kirk in the village of "+
          "Tabor Sogh.",1);
  add_ask(({"cimbaeth","Cimbaeth"}),
          "say Cimbaeth is one of the cooks of the abbey, and an expert "+
          "on making saltpeter.",1);
  add_ask(({"finegas","Finegas"}),
          "say Finegas is one of the instructors of the arcane arts. "+
          "He is usually in the library or in his class room.",1);
  add_ask(({"mabon","Mabon"}),
          "say Mabon is one of the gardeners of the abbey, and an "+
          "expert on herbs.",1);
  add_ask(({"tabor sogh","Tabor Sogh"}),
          "say Tabor Sogh is a small village on the coast, southeast of "+
          "Port MaDunn, across the plains.",1);
 
  // candles and honey quest related questions
  add_ask(({"baile ashlagh","Baile Ashlagh"}),
          "say Baile Ashlagh is a village in Khalakhor, a great distance from "+
          "here. You must sail to get there.",1);
  add_ask(({"handmade candle","handmade candles","wick","wicks","wax",
            "beeswax"}),
          "say See brathair Seandlar about that.",1);
  add_ask("honey",
          "say Well, it comes from bees. They store it in their hives.",1);
  add_ask("honey pot", "say Sorry, I don't have one.",1);
  add_ask(({"seandlar","Seandlar"}),
          "say Brathair Seandlar is a candle maker in the kirk. He's usually "+
          "in the candle shop down the corridor.",1);
  add_ask("bees", "say Ah, impatient little fellows, aren't they?",1);
  add_ask("hive","say You'd probably find one in the countryside.",1);
  add_ask(({"briareus","Briareus"}),
          "say He is the Prior of the kirk at Baile Ashlagh.",1);
  add_ask("prior",
          "say A prior is one of the Order in charge of a small kirk.",1);
  add_ask(({"mortar","pestle","key",}),
          "say I do not have one.",1);
  add_ask(({"water","holy water"}),
          "say I do not have any, but there should be some in the kirk.",1);
  add_ask(({"honeysuckle","lilac","bark","sap","amber","tree","cedar",
            "pine"}),"say See brathair Mabon about that.",1);
  add_ask("saltpeter","say See brathair Cimbaeth about that.",1);
  add_ask(({"bee","bees","honey","wax","comb","honeycomb","hive","beehive"}),
          "say I don't know of any around here, perhaps in the countryside?",1);
  add_ask("rites","say They are the rituals and ceremonies we do here.",1);

  // oil tour related asks
  add_ask(({"balantrum","Balantrum"}),
          "say Brathair Balantrum often takes care of the ill brathairs. "+
          "He's usually in the abbey or kirk here.",1);
  add_ask(({"tinne","Tinne"}),
          "say Brathair Tinne is a novishagh of the Order. He's been ill "+
          "lately and brathair Balantrum is looking after him.",1);
  add_ask(({"flask","for flask","about flask"}),
          "say Brathair Garlon tends to such things for us.",1);
  add_ask(({"garlon","Garlon"}),
          "say Brathair Garlon is the sacristan of the kirk. He tends to "+
          "the vestments and equipment used in our rites. He's usually "+
          "in the sacristy.",1);
  add_ask(({"sacristy","where is sacristy"}),
          "say The sacristy is at the end of the corridor to the east.",1);
  add_ask(({"blubber","whale blubber","oil"}),
          "say Ask brathair Cimbaeth about that.",1);
  add_ask("beatha","say Ask brathair Balantrum about that.",1);
}


void
arm_me ()
{
  vest_me(({"robe","cincture","scapular","cope","mitre"}));
  (clone_object(SR_WEAPON+"crozier"))->move(TO);
  command("wield all");
}

void
create_khalakhor_elf ()
{
  ::create_khalakhor_human();
  set_race_name("elf");
  add_name(({"abbot","manach","monk",SR_NPC_ID}));
  add_adj(({"wizened","white-haired"}));
  set_long("He is a wizened white-haired elf, impressively dressed in "+
           "the habit of an abbot of Sean-Rhian. He seems preoccupied.\n");
  set_manach_stats(100);
  set_act_time(30);
  add_act("emote mumbles a silent prayer.");
  add_act("emote puts his hands together prayerfully.");
  add_act("emote bows his head prayerfully.");
  add_act("emote raises his hands and sings a quiet chant.");
  add_act("emote folds his arms into the sleeves of his robe.");
  add_act("emote nods at you hospitably.");
  add_act("emote chants in an ancient tongue.");
  add_act("emote traces three circles before his face.");
  add_act("emote genuflects on one knee and prays.");
  add_act("emote folds his arms beneath his scapular.");
  add_act("emote looks worriedly at the note on his desk.");
  do_add_asks();
  
  set_log_ask();
}

void
create_khalakhor_human () {
  create_khalakhor_elf();
}
