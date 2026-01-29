/**********************************************************************
 * - riddler.c                                                      - *
 * - NPC tells riddles for entrance quest to the Pier that leads to - *
 * - Galaith Isle                                                   - *
 * - Created by Damaris@Genesis and Lucius 03/2001                  - *
 * - Damaris - Reopened quest, removed feature that prevented       - *
 * - 01/2006   retrying the quest until reboot. Now can retry as    - *
 * -           globe is given to npc.                               - *
 * - Tapakah - Refactored minorly.                                  - *
 * - 08/2021                                                        - *
 **********************************************************************/

#pragma strict_types

#include <const.h>   // for G_FEMALE
#include <macros.h>  // for OB_NAME
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "../defs.h"
#include "riddler.h"

//agreeable should be enough

#define GUILD_MIN_ALIGN  99
#define GARM "/d/Khalakhor/guilds/eilgalaith/arm/"

inherit "/d/Khalakhor/std/npc/elf";
inherit "/d/Khalakhor/se_speir/port/npc/help_me";
inherit "/d/Khalakhor/common/npc/quest-npc";

private void get_riddle (object who);
void react_wrong_answer ();

static object questor;
static mapping remembered = ([]), failed = ([]);
static string *riddles = ({
  "What can fill a room but takes up no space.",
  "The more thee take, the more thee leave behind.",
  "Forward I am heavy, backward I am not. What am I?",
  "Give it food and it will live, give it water and it will die.",
  "Yellow and white, hard outside, stolen from life. What am I? ",
  "They are dark, and always on the run, without the sun, there would "+
  "be none.",
  "The more there is the less thee see.",});
static string *answers = ({ "light", "footsteps", "ton", "fire", "egg", 
                            "shadows", "darkness" });

static int alarm, is_busy, tries, success, current = -1;

void
create_khalakhor_elf ()
{
  set_name("julia");
  set_living_name("julia");
  set_race_name("elf");
  add_name(({"julia", "riddler", "woman"}));
  set_adj("cheerful");
  add_adj("middle-aged");
  set_title("Jilio from the House of Eilaith");
  set_gender(G_FEMALE);
  set_size_descs("of normal length", "of normal width");
  set_long("She is known in these parts as 'The Riddler'.\n"+
           "She has peach coloured skin.\n"+
           "She has mysterious deep blue eyes.\n"+
           "Her hair is shoulder length, coal black and windswept.\n"+
           "She has the distinguished mark of the mystic vine of the "+
           "Eil-Galaith.\n"+
           "She wears the saffron and cerulean colours from the elven "+
           "House of Eilaith.\n");
  set_skill(SS_AWARENESS, 100);
  set_skill(SS_UNARM_COMBAT, 100);
  set_skill(SS_DEFENCE, 100);
  set_skill(SS_BLIND_COMBAT, 100);
  set_skill(SS_PARRY, 100);
  add_prop(NPC_I_NO_RUN_AWAY, 1);
  set_stats(({150 + random(10),
              150 + random(10),
              150 + random(10),
              150 + random(10),
              150 + random(10),
              150 + random(10)}));
  set_alignment(1000);
  clone_object(GARM + "jmantle")->move(TO);  
  clone_object(GARM + "cloak")->move(TO);
  clone_object(GARM + "mpants")->move(TO);
  clone_object(GARM + "mboots")->move(TO);
  command("wear all");

  set_act_time(15);
  add_act("ponder");
  add_act("smile secret");
  add_act("emote lips curl up in a mysterious smile.");
  add_act("emote hums an ancient elven melody.");
  add_act("emote adjusts her saffron and cerulean mantle.");
  add_act("rsay Riddle me this and riddle me that. "+
          "Life as an elf is where it's at.");
  add_act("rsay It's elaborately made can thee hear its call? "+
          "In the tower a silken thread falls.");
  add_act("rsay One plus two it equals three. "+
          "In the tower one will see.");
  add_act("rsay A spider I spied spinning a web. "+
          "Did not know who was to wed.");
  add_act("rsay Riddles I have within my mind. "+
          "Do thee wish to try this time?");
  add_ask(({"samorgan"}),
          "say Oh SaMorgan is closed at the moment. The storm made a mess "+
          "of the dock.", 1);
  add_ask(({"elves", "elf"}),
          "say Ahh yes, elves. We are a curious lot, I've been told.", 1);
  add_ask(({"eil-galaith"}),
          "say I know the way of course. Perhaps a small treasure "+
          "and a riddle or two and thee will as well.", 1);
  add_ask(({"galaith", "isle of galaith", "galaith isle"}),
          "say Oh yes, the isle of Galaith is ever so near. Sanctuary "+
          "tower rises there.", 1);
  add_ask(({"sanctuary", "sanctuary tower", "tower", "eil-galaith"}),
          "say Ahh, sanctuary is what we all seek, and it can be found "+
          "upon the isle of Galaith.", 1);
  add_ask(({"treasure", "globe"}),
          "say I once held within my hand the lands of Khalakhor. Now "+
          "that was a treasure indeed.",1);
  add_ask(({"riddle", "riddles"}),
          "say I have been called the riddler by some. Riddles I have "+
          "for those who wish to pass this way. If thee have a treasure "+
          "for me, then perhaps I'll give thee a riddle or two.", 1);
  add_ask(({"riddler"}),
          "say I've been called Riddler by a few.", 1);
  set_default_answer(react_wrong_answer);
  remove_prop(LIVE_M_NO_ACCEPT_GIVE);
}

/*
 * Function name: hook_return_intro
 * Description  : Called when someone introduces themselves
 *                to us.
 * Arguments    : str - Name of the player introducing.
 * Returns      : 1
 */
int
hook_return_intro (string str)
{
  if (!remembered[str])   {
    command("say Good day to thee, " + capitalize(str) +
            ", I'm " + query_name() + " " + query_title() +
            ". Might thee be of need of my riddles this day?");
    command("bow " + str);
    remembered[str] = "nice";
    present(str, environment(TO))->add_introduced("julia");
  }
  else if (remembered[str] == "bad") {
    command("growl sof");
    command("say I remember thee clearly, so be on thy way!");
  }
  else {
    command("giggle");
    command("say Ahh, yes, of course, "+
            "" + capitalize(str) + ", I remember thee quite well.");
    command("say Surely thou hath not forgotten that I am "+
            "" + query_name() + " " + query_title() + "?");
    command("say Or was it another riddle that thee "+
            "needed?");
    present(str, environment(TO))->add_introduced("julia");
  }
  return 1;
}

mixed
query_default_answer ()
{
  if (is_busy) {
    if (TP != questor) {
      command("sigh disgust");
      return("to "+ OB_NAME(TP) +" can't thee see "+
             "I'm busy here?");
    }
    if (current == -1) {
      command("rolleyes");
      return("to "+ OB_NAME(TP) +" Show some patience.");
    }
    
    switch(random(2)) {
    case 0:
      return("to "+ OB_NAME(TP) +" That doesn't "+
             "seem right.. try again.");
    case 1:
      command("hmm");
      return("to "+ OB_NAME(TP) +" Nooo.... I dont "+
             "think that is it, try something else.");
    default:
      command("scratch chin");
      return("to "+ OB_NAME(TP) +" That isn't right, "+
             "try again.");
    }
  }
  return ::query_default_answer();
}

void
react_wrong_answer ()
{
  if (current < 0)
    command("shrug");
  else
    command("say Unfortunately, thy answer is wrong.");
}


string
riddle_answer ()
{
  string whom = OB_NAME(TP);
  remove_ask(answers[current]);
  
  if (alarm) {
    remove_alarm(alarm);
    alarm = 0;
  }
  
  if (++success != 2) {
    command("ask "+ whom +" Oh my! I do believe that is "+
            "correct!");
    command("ask "+ whom +" I think I have another, let "+
            "me think...");
    set_alarm(3.0, 0.0, &get_riddle(TP));
    return "> ";
  }
  
  command("ask "+ whom +" Excellently done! Thou hath done great "+
          "and now I shall allow thee to proceed as promised.");
  command("ask "+ whom +" The entrance to the isle shall be open for "+
          "thee. The ship to it once sailed east from here, but now it is "+
          "moved to the mysterious land of Cadu. "+
          "Seek out Junil upon the isle and ask for a reward.");
  command("point east");
  
  TP->add_prop("__answered_galaith_riddles", 1);
  is_busy = questor = success = tries = 0; current = -1;
  return "> ";
}

int
read_answer (string str)
{
  if (current < 0)
    return 0;
  
  if (!str)
    NF0("Answer what?");

  if (str == answers[current])
    riddle_answer();
  else 
    react_wrong_answer();
  return 1;
}

varargs void
timeout (object who)
{
  if (alarm) {
    remove_alarm(alarm);
    alarm = 0;
  }
  remove_ask(answers[current]);
  questor = is_busy = 0; current = -1;
  
  if (objectp(who) && present(who, environment())) {
    string whom = OB_NAME(who);
    command("ask "+ whom +" Sorry, but thy time is up.");
    command("think");
    
    if (tries < 3) {
      command("ask "+ whom +" I'm feeling generous, "+
              "so let me give thee another chance...");
      get_riddle(who);
      return;
    }
    command("ask "+ whom +" I can't think of anymore riddles "+
            "for thee to try to help me with.");
    command("ask "+ whom +" Try me again another day and "+
            "perhaps we'll be able to help each other.");
    failed[who->query_real_name()] = 1;
  }
  questor = success = tries = is_busy = 0; current = -1;
}

private void
get_riddle (object who)
{
  int last;
  string whom;
  
  if (!present(who, environment())) {
      // Reset all the variables
    is_busy = questor = success = tries = 0;
    return;
  }
  
  whom = OB_NAME(who);
  last = current; tries++;
  
  while(last == current)
    current = random(sizeof(riddles));
  
  command("ask "+ whom +" Here is a riddle I need help with. "+
          "Give me the answer within a couple of minutes to proceed...");
  command("clear throat");
  command("ask "+ whom +" "+ riddles[current]);
  
  add_ask(answers[current], riddle_answer);
  alarm = set_alarm(300.0, 0.0, &timeout(who));
}

private void
receive_globe (object ob, object from)
{
  string whom, what;
  if (!present(from, environment())) {
    is_busy = questor = success = tries = 0;
    command("scratch");
    command("shrug");
    ob->remove_object();
    return;
  }
  
  what = OB_NAME(ob);
  whom = OB_NAME(from);
  ob->remove_object();
  
  if (from->query_prop("__answered_galaith_riddles")) {
    command("ask "+ whom +" Thou hath helped me, "+
            "if thee need something more, seek out Junil as I said.");
    return;
  }
  
  if (from->query_race() == "goblin" ||
      from->query_alignment() <= GUILD_MIN_ALIGN) {
    command("peer suspic at "+ whom);
    command("ask "+ whom +" Thank thee kindly for "+
            "returning this to me.");
    command("ponder"); command("smile warily at "+ whom);
    command("ask "+ whom +" Perhaps its best thee leave "+
            "the area... Thy kind aren't altogether welcome here...");
    return;
  }
  
  command("smile brightly "+ whom);
  command("lift globe"); command("focus globe");
  command("ask "+ whom +" A most precious treasure thou hath given "+
          "me.");
  command("ask "+ whom +" Perhaps thou hath time to solve a couple "+
          "riddles for me, if thee can be of help, then perhaps I shall "+
          "let thee pass.");
  command("smile enigmatic");
  
  is_busy++; questor = from;
  set_alarm(3.0, 0.0, &get_riddle(from));
}

private void
return_item (object ob, object from)
{
  string whom = OB_NAME(from), what = OB_NAME(ob);
  
  if (present(from, environment()) && from->check_seen(this_object())) {
    if (is_busy)
      command("ask "+ whom +" I am a bit busy, try me later.");
    else
      command("ask "+ whom +" I don't need this.");
    if (command("give "+ what +" to "+ whom) == 0)
      command("drop "+ what);
  }
  else {
    command("say What am I supposed to do with this?");
    command("drop "+ what);
  }
}

void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
  
  if (!objectp(ob) || !objectp(from))
    return;

  if  (!is_busy && ob->id("_eil-galaith_globe_"))
    set_alarm(1.0, 0.0, &receive_globe(ob, from));
  else
    set_alarm(1.0, 0.0, &return_item(ob, from));
}

void
init_living ()
{
  ::init_living();
  add_action(read_answer, "answer");  
}
