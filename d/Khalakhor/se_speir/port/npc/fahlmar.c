
/*
 * fahlmar.c
 *
 * Fahlmar Macdunn, Lord of Port MacDunn.
 * 
 * Khail - June 4/97
 * Quest management added by Tapakah, 07/2021
 * Refactored by Tapakah, 08/2021
 *
 */
#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include "/d/Khalakhor/se_speir/population.h"
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "npc.h"

inherit BASE_NPC;
inherit "/d/Khalakhor/common/npc/quest-npc";

mapping adjustment = ([]);

/*
 * Function name: arm_me
 * Description  : Clones in equipment
 *                and has him wear/wield it.
 * Arguments    : n/a
 * Returns      : n/a
 */
void
arm_me ()
{
  armours = ({ "/d/Khalakhor/common/arm/shirt_wool",
               "/d/Khalakhor/common/arm/belt",
               "/d/Khalakhor/common/kilts/kilt_macdunn" });

  ::arm_me();
}

string *
my_quests ()
{
  return ({ "Port Macdunn Introduction Tour",
            "Port Macdunn Inspection Tour" });
}

string
reply_news ()
{
  command("say We have sent a task force in the western direction to "+
          "explore the land route towards Sa Morgan. We haven't decided "+
          "whether they will set base there or "+
          "continue exploration westwards, though.");
}

varargs int
query_completed_intro_tour(object who, mapping census = 0)
{
  if (! census)
    census = who->query_prop(MACDUNN_INTRO_TOUR);
  string error = "";
  foreach (string name, int intro: census) {
    if (! who->query_met(lower_case(name)))
      error += (strlen(error) ? ", " : "") + name;
  }
  if (strlen(error))
    log_me(TPQN + " did not meet " + error + "\n", "notice", "intro-tour.log");
  return strlen(error) ? 0 : 1;
}

int
query_completed_inspect_tour(object who)
{
  object insp;

  if (!(insp = present("inspection_object", who)))
    return 0;

  return insp->query_finished_inspection();
}

void
reward_player(object who, mixed tour)
{
  if (!mappingp(tour))
    tour = get_quest_by_name(tour);

  if (! tour) {
    command("say Something strange happened. "+
            "You should alert the authorities.");
    log_quest(-1, TPQN, "reward out of turn", "error");
    return;
  }
  do_reward_player(tour["new_bit"], tour["new_xp"]);
}

string
reply_task_tour (mapping quest)
{
  mapping census = TP->query_prop(MACDUNN_INTRO_TOUR);
  if (census) {
    command("chuckle");
    command("say Forget who you're supposed to meet? " +
            COMPOSITE_WORDS(m_indices(census)) + ". Just " +
            "visit them then come back and ask me for a " +
            "reward.");
    return "";
  }
  command("say Before I can give you a real job, you'll " +
          "have to prove to me you're capable of finding " +
          "your way around the village.");
  command("hmm");
  mixed *people = query_random_population(SE_SP_LOCATION, "Port Macdunn", 6);
  string *names = get_population_column(people, SE_SP_NAME);

  command("say Nothing particularly challenging, just go " +
          "and introduce yourself to a few folks around the " +
          "village so the villagers won't be as suspicious " +
          "as they can be with outsiders. " +
          COMPOSITE_WORDS(names) + " should suffice. Come back " +
          "after you've visited them all and ask me for your " +
          "reward.");
  census = ([]);
  foreach (string name: names)
    census[name] = 0;
  TP->add_prop(MACDUNN_INTRO_TOUR, census);
  
  if (query_completed_intro_tour(TP)) {
    write("Chuckling, you explain to " + query_The_name(TO) +
          " that you've already met them all.\n");
    command("laugh");
    command("say Well, that was fast. One step ahead of " +
            "me, are you? Good, I like that.");
    command("smile");
    reward_player(TP, "Port Macdunn Introduction Tour");
    TP->remove_prop(MACDUNN_INTRO_TOUR);
  }
  return "";
}

string
reply_task_inspection ()
{
  if (TP->query_prop(MACDUNN_INSPECTION_TOUR)) {
      command("say It's really quite simple, just go " +
              "around the village inspecting the outside of " +
              "the embankment, and come back to ask for " +
              "your reward when done.");
      return "";
  }
  command("say Ok, this time I want to you do me a favour " +
          "and go inspect the outside of the embankment around " +
          "the village. Come back to me when you're done and " +
          "ask for your reward.");
  TP->add_prop(MACDUNN_INSPECTION_TOUR, 1);
  reset_euid();
  clone_object(OBJ + "inspection_object")->move(TP);
  return "";
}


string
reply_task ()
{
  command("say So it's a job you want is it? Let's see.");
  mapping quest = get_next_quest();

  if (! quest) {
    return "say Hmm, I don't seem to have any more tasks for " +
      "you yet. Maybe if you come back later. You can also check " +
      "with Abbot Semion in the Seanchan abbey, with the Postmaster "+
      "of Baile Ashlagh, or visit the elves in Sa Morgan.";
  }

  if (quest["name"] == my_quests()[0])
    return reply_task_tour(quest);

  if (quest["name"] == my_quests()[1])
    return reply_task_inspection();

  log_quest(quest["real_bit"], TPQN, "Strange error in quest", "error");
  return "say I will have to check with higher authorities on that.";
}

string
reply_reward_tour (mapping quest)
{
  command("say So you've met everyone have you?");
  if (!query_completed_intro_tour(TP)) {
    write("You sheepishly admit that you missed someone.\n");
    command("say Well then, I guess you'd better get back " +
            "to looking.");
  }
  else {    
    write("You effortlessly describe " +
          COMPOSITE_WORDS(m_indices(quest)) +
          " as proof you've met them.\n");
    command("smile");
    command("say Well done!");
    reward_player(TP,  "Port Macdunn Introduction Tour");
    TP->remove_prop(MACDUNN_INTRO_TOUR);
  }
  return "";  
}

string
reply_reward_inspection ()
{
  command("say So you've looked over all the embankments?");
  if (!query_completed_inspect_tour(TP)) {
    write("You describe the embankments you inspected to " +
          "Fahlmar, but he shakes his head.\n");
    command("say I think you missed some, go check again. " +
            "Remember it's the outside we need inspected, not " +
            "the inside.");
  }
  else {
    write("You describe the embankments you inspected " +
          "to Fahlmar, who nods in satisfaction.\n");
    command("say That sounds like all of 'em, well done!");
    reward_player(TP, "Port Macdunn Inspection Tour");
    TP->remove_prop(MACDUNN_INSPECTION_TOUR);
    present("inspection_object", TP)->remove_object();
  }
  return "";
}

string
reply_reward ()
{
  mixed quest;

  quest = TP->query_prop(MACDUNN_INTRO_TOUR);
  if (quest)
    return reply_reward_tour(quest);

  quest = TP->query_prop(MACDUNN_INSPECTION_TOUR);
  if (quest)
    return reply_reward_inspection();
  
  command("say Reward for what? You aren't doing anything " +
          "for me at the moment.");
  return "";
}

void
create_khalakhor_human ()
{
  ::create_khalakhor_human();
  add_name("lord");
  add_name("man");
  set_adj("stately");
  add_adj("middle-aged");
  set_long("This man carries himself with a grace that " +
           "indicates nobility, but a confidence that indicates " +
           "that nobility was probably earned on the battlefield, " +
           "and not politically. He appears very preoccupied, " +
           "however, and possibly has a number of duties that " +
           "he could use some help with. Maybe you can ask him about "+
           "some news in the area as well.\n");

  default_config_npc(75);
  set_skill(SS_AWARENESS, 50);
  set_skill(SS_UNARM_COMBAT, 50);
  set_skill(SS_DEFENCE, 80);
  set_skill(SS_WEP_SWORD, 90);

  set_alignment(800);

  set_act_time(15);
  add_act("ponder");
  add_act("emote glances through a handful of papers on " +
          "his desk.");
  add_act("emote rubs his eyes with his hands.");
  add_act("say What do you want? I'm rather busy.");
  add_act("say Blazes, I don't like these rumours of goblins " +
          "in the village, the northern clans have been quiet " +
          "for far too long.");
  add_act("say If you're looking for a job, just ask me for " +
          "one.");
  add_ask(({"task", "quest", "tour", "job", "work", "help"}),
          reply_task, 1);
  add_ask(({"reward", "for reward"}), reply_reward, 1);
  add_ask(({"news", "tidings", "about news", "about tidings"}), reply_news, 1);
  
  set_size_descs("of normal length", "of normal width");
}


void
hook_return_intro_new (string str)
{
  command("say Good day to you, " + capitalize(str) +
          ", I'm " + query_name() + " " + query_title() + 
          ". What can I do for you?");
  command("bow " + str);
}

void
hook_return_intro_bad (string str)
{
  command("smirk");
  command("say I remember you, bugger off!");
}

void
hook_return_intro_good (string str)
{
  command("chuckle");
  command("say Ahh, yes, of course, I remember you from " +
          "your last visit, " + capitalize(str) + ", what " +
          "can I do for you this time?");
}

int
hook_return_intro (string str)
{
  str = lower_case(str);
  if (adjustment[str])
    adjust_quests(adjustment, str);
  else
    ::hook_return_intro(str);
  return 1;
}

void
adjust_quests (mapping adjustment, string tpqn)
{
  command("say Hello, my dear " + capitalize(tpqn) + "!");
  command("say Let's see...");
  command("emote looks through a bunch of folders.");
  ::adjust_quests(adjustment, tpqn);

  command("say We apologize for the delay in handling this.");
  command("say I heard the mayor of Cadu will be taking care "+
          "of Nyreese quests soon.");
  command("say Maybe I should visit him and establish a trade route.");  
}

void
init_living ()
{
  ::init_living();
  mapping *tp_adjustment;

  string tpqn = lower_case(TPQN);
  if (tp_adjustment = get_quest_adjustments(TP)) {
    adjustment[tpqn] = tp_adjustment;
    if (! TP->query_met()) 
      command("say Hello, " + TP->query_nonmet_name() + ". " +
              "We are conducting a revision of quests in the domain. " +
              "Would you mind introducing yourself, so that we could "+
              "check your file as well?");
    else
      adjust_quests(adjustment, tpqn);
  }  
}
