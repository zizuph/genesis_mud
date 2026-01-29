/* created by Aridor, 06/15/94 */
/* the quest npc for the 3rd small adventure of the questmaster.*/

/* Modified by Dajala, 20.03.95
 * Masked do_die() to enable Brimsch to haunt players who made it impossible 
 * for him to solve his life quest.
 */

#include "brimsch.h"
inherit M_FILE
#include <macros.h>

int no_intro = 0;
object *muffin_list = ({ });

void
create_krynn_monster()
{
    set_name("brimsch");
    add_name("brimsch_gnome");
    set_adj("talkative");
    add_adj("sad");
    set_race_name("gnome");
    set_long("@@my_long");
    default_config_npc(40);
    set_alignment(50);
    set_knight_prestige(-1);
    add_ask(({"muffin","raisin","raisins","sad","quest","lifequest",
	      "life quest","problem",
	      "help","difficulties","difficulty"}),
	    VBFC_ME("ask_for_help"));
    trig_new("%s 'introduces' %s","my_intro");
    set_act_time(3);
    add_act("say IJustCannotFigureThisOut!");
    add_act("say ByTheDeadRatOfAGullyDwarf!ThisReallyBugsMe.");
    add_act("say ICouldAsWellAskAGullyDwarf.TheyCanCountToTwoAtMost.");
    add_act("think something");
    add_act("ponder");
    add_act("emote curses loudly.");
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    seteuid(getuid(TO));
    (QUEST_MASTER)->load_me();
}

string
my_long()
{
      return "This is a sad gnome. He is holding a muffin in his hand " +
	"but still he is crying.\n";
}

string
ask_for_help()
{
    int prp = TP->query_prop(PLAYER_I_BRIMSCH_LIFE_QUEST);
    (QUEST_MASTER)->load_me();
    if ((QUEST_MASTER)->query_quest_number(SMALLADV, TP) != 2)
      {
	  command("say IDon'tThinkYouCanHelpMeWithThis...");
	  command("sigh");
	  return "";
      }
    command("say I'mSoGladYouAsked.YesIDoNeedHelpWithaProblemIHaveBeen" +
	    "ThinkingAboutForAllMyLifeNow.");
    command("say ItIsMyLifeQuestYouKnowAndIAmSupposedToSolveIt.OnlyThen" +
	    "WillIBeAcceptedAsATrueGnomeAndIWillHaveTheChanceToLiveA" +
	    "PeacefulLifeAsIHaveAlsoSavedTheSoulsOfAllMyPredecessors" +
	    "WhoHaveFailedOnThisQuest.");
    command("Well,TheQuestYouAsk?ItSoundsFairlySimple,WhichIsEvenMore" +
	    "AstonishingAsTheSolutionAppearsToBeSoMuchMoreComplex.");
    command("hmm");
    command("say AhYes,Well,Actually,IHaveToDetermineTheAverageNumber" +
	    "OfRaisinsInAMuffin.");
    if (member_array(TP,muffin_list) != -1)
      command("say OhIAlreadyGaveYouAMuffin.Good.");
    else
      {
	  command("say Here'sAMuffinForYou.ICan'tAffordAnymore,ButMaybeYou" +
		  "CanHelpMe?");
	  clone_object(MUFFIN)->move(TO);
	  command("give muffin to " + TP->query_real_name());
	  muffin_list += ({ TP });
	  TP->add_prop(PLAYER_I_BRIMSCH_LIFE_QUEST, prp | 1);
	  set_alarm(1800.0,0.0,"remove_someone_from_muffin_list",TP);
      }
    command("say IfYouFindOutSomethingAboutItJustGiveMeTheSolution.");
    return "";
}

void
remove_someone_from_muffin_list(object who)
{
    muffin_list -= ({ who });
    muffin_list -= ({ 0 });
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob,from);
    if (ob->id("muffin_solution"))
      set_alarm(1.0,0.0,"remove_solution_reward_who",ob,from);
    else
      set_alarm(1.0,0.0,"command","drop all");
}

void
remove_solution_reward_who(object ob, object who)
{
    object note;
    string the_name;
    if (!ob)
      return;
    ob->remove_object();
    if (!who)
      return;
    the_name = who->query_real_name();
    note = clone_object(MY_NOTE);
    note->move(TO);
    command("say OH!MY!GOD!");
    command("cheer");
    command("say IDon'tBelieveThis.ThisIsIncredible!HowDidYouFindOut??");
    command("say Well,-Ohmygosh-...");
    command("thank " + the_name);
    command("say Here,TakeThisNoteOfGratitude.IAmSureItWillBeValuable.");
    command("emote writes something on a small sheet of paper.");
    command("give note to " + the_name);
    command("smile");
    command("bounce");
   command("say IWillBeFamous!IWillBeRich!IWillHurryToPresentThisUnbelievable" +
	    "SolutionToTheCommiteeOfFoodAndDrinkimprovementsAndAnalysis.");
    command("emote runs out of the room and down the corridor.");
    set_alarm(1.0,0.0,"remove_object");
}

erase_no_intro() { no_intro = 0; }

int
my_intro(string s1, string s2)
{
  if (!no_intro)
    {
      set_alarm(1.0, -1.0, "command","introduce me");
      no_intro = 1;
      set_alarm(6.0, -1.0, "erase_no_intro");
      return 1;
    }
  return 1;
}

/* Mask do_die to get the haunting */
void 
do_die(object killer)
{
  object ghost;

  seteuid(getuid());
  ghost = clone_object("/d/Krynn/gnome/monster/ghost"); 
  ghost->set_ghost_des(this_object()->query_nonmet_name());
  ghost->set_duration(800);
  ghost->move(killer);
  ghost->start_haunt();
  ghost->set_inform_msg("YouDeprivedMeOfThePossibilityTo"
	+ "FulfillMyLifeQuest.\nYouWillSurelyPay.\n");
  ::do_die(killer);
}

