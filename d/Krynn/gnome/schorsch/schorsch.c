/* This poor gnome is in charge of the boards of Genesis.
 * He has to run around and secure all the notes that have
 * come loose. He is permanently tired and seeks friendly players
 * to help him.
 * Created by Dajala
 */

/* Still to do:
 *	163: More boards to add
 */
/* Navarre November 30th, 2005: Replaced lower_case(helper->query_name()) with OB_NAME(helper)
 * As it didn't work for all players, and we received complaints about it.
 * It is now fixed.
 */
/* 2017-10-24 Malus: Prevent multiple calls to found_helper(), check if player
 * has already completed the quest. */ 
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/gnome/local.h"
#include "/d/Krynn/gnome/schorsch/schorsch.h"
#include <macros.h> 

inherit M_FILE


/* Global variables */

int     help_imminent, *board_list = allocate(BOARD_NUMBER);
object  helper, securetool;

void
outout(int flag)
{
    command("emote finishes his milk and stands up.");
    if(flag)
    {    
	command("thank " + helper->query_name());
	command("say But there is still work for me to do.");
    }
    else
	command("say I have to go again.");
    command("bow tika");
    command("emote leaves.");
    remove_object();
}

void
get_list()
{
    int i, j, a;

    board_list[0] = 0; /* Visit the guild in any case. */
    for(i=1;i<BOARD_NUMBER;i++)
    {
        a = board_list[i] = random(sizeof(BOARD_NAMES) - 1) + 1;
        for(j=1;j<i;j++)
            if(board_list[j] == a)
                i--;
    }
}	

void    
found_helper()
{    
    int i;

    command("cheer");
    command("hug " + helper->query_name());
    command("say IAmGladThatThereAreStillFriendlyPeopleInTheWorld"
	+ "WhoCareToHelpAnOldGnome.");
    command("emote smiles gnomishly");
    command("give securetool to " + lower_case(helper->query_name()));
    get_list();
    securetool->set_owner(board_list);
    tell_room(E(TO), "The gnome's voice fades.\n");
    command("whisper " + OB_NAME(helper) + " I'dAskYouToVisitFive"
	+ "DifferentBulletinBoards,Namely:");
    for(i=0;i<BOARD_NUMBER;i++){
	command("whisper " + OB_NAME(helper) + " " 
		+ BOARD_STRINGS[board_list[i]]);
        }
    tell_room(E(TO), "Stronger, he continues.\n");
    command("say PleaseRememberAllOfThem.");
    command("smile " + helper->query_name());
    outout(1);
}

string
answer_help_nod(object actor, string adverb)
{
    if(!get_alarm(help_imminent) || actor != helper)
	    return "";
    find_player("malus")->catch_msg("answer_help_nod");
    set_alarm(2.0, 0.0, &found_helper());
    remove_alarm(help_imminent);
    
    return "";
}

void
create_krynn_monster()
{
    set_name("schorsch");
    add_name("schorsch_gnome");
    set_adj("tired");
    add_adj("old");
    set_long("The old gnome seems very tired. He sits at a table, drinking "
	+ "a glass of milk. He looks at you pitifully.\n");
    set_race_name("gnome");
    set_title("the Keeper of the Boards");
    default_config_npc(40);
    set_alignment(80);
    set_knight_prestige(-1);
    add_ask(({"help","reason","problem","tired","pitiful","quest",
	      "life quest","difficulties","difficulty","work","care"}),
	      "ask_for_help", 2);

    add_emote_hook("nod", 0.0, answer_help_nod); /* Added by Rastlin */

    set_introduce(1); /* introduce back to people */
    set_act_time(8);

    add_act("@@brain");
    set_alarm(1500.0, -1.0, &outout(0));

    seteuid(getuid());
    securetool = clone_object("/d/Krynn/gnome/schorsch/secureto");
    securetool->move(TO);
}

string
brain()
{
    int i;
    
    i = random(4);
    if (!i)
    {
        command("say AllThisWorkToDo...");
        command("sigh pitif");
    }
    else if (i == 1)
	    command("say ...AndIAmAllAloneToDoIt...");
    else if (i == 2)
    {
        command("sigh");
        command("say IfOnlySomebodyWouldCareForMe...");
    }
    else
    {
        tell_room(environment(), QCTNAME(TO) + " drinks "
            + "some milk.\n"); 
        command("sniff");
    }
    return "";
}

string
ask_for_help()
{
    if (get_alarm(help_imminent))
    {
        if (helper != TP)
            command("say JustAMoment,IMayHaveFoundSomeoneToHelpMe!");
        return "";
    }
    if (TP->test_bit("Krynn", SCHORSCH_GROUP, SCHORSCH_BIT))
    {
        command("say Oh,HelloAgain!");
        command("smile fondly");
        command("say YouAlreadyKnowOfMyResponsibilities!YouHaveHelped"+
                "MeBefore.Don'tYouRemember?");
        command("say ICannotLetYouDoAnyMore,OrTheyMightMakeYouMyReplacement!");
        command("chuckle gnomishly");
        return "";
    }
    helper = TP;
    command("say DoYouReallyCare?");
    command("smile hopefully");
    command("say IAmInChargeOfMaintainingTheBulletinBoardsHereInGenesis.");
    command("say IHaveToSecureTheNotesThatHaveComeLooseBeforeTheyMight" 
	+ "FallOffAndBeLost.");
    command("say ButNowIHaveBecomeOldAndMyFeetWon'tCarryMeAsFastAsTheyDid"
	+ "WhenIWasYoungAndHealthy.");
    command("cough");
    command("say WouldYouReallyLikeToHelpMe?");
    command("eyebrow " + helper->query_name());
    help_imminent = set_alarm(18.0, -1.0, "no_help_shrug");
    return "";
}

void
no_help_shrug()
{
    command("sigh");
    command("emote looks down onto the table.");
    command("say IFearedSo." + C(PRONOUN(helper)) + "Won'tHelpMe.");
}

public void
speech_hook(string verb, object actor, string adverb, object *objlist,
        string text, int target)
{
    int i;
    string str;
    string *confirmations;

    if (!get_alarm(help_imminent) || actor != helper)
        return;

    str = lower_case(text);

    // Remove single trailing period or multiple exclamation points
    for (i = strlen(str)-1; i>0; i--)
    {
        if (str[i] == '.' && i == strlen(str)-1)
        {
            i--;
            break;
        }
        if (str[i] != '!')
            break;
    }
    str = extract(str, 0, i);
    
    confirmations = ({"yes", "of course", "sure", "why not", "ok", "okay",
            "yea", "yeah", "yep", "aye", "certainly", "gladly", "naturally"});
    if (member_array(str, confirmations) > -1)
    {
        set_alarm(1.0, 0.0, &found_helper()); 
        remove_alarm(help_imminent);
    }
}

/* Mask do_die to get the haunting */
void 
do_die(object killer)
{
  object ghost;

  seteuid(getuid());
  ghost = clone_object(TDIR + "monster/ghost"); 
  ghost->set_ghost_des(this_object()->query_nonmet_name());
  ghost->set_duration(800);
  ghost->move(killer);
  ghost->start_haunt();
  ghost->set_inform_msg("YouDeprivedMeOfThePossibilityTo"
	+ "CarryOnWithMyWork.\nYouWillSurelyPay.\n");
  ::do_die(killer);

}

/* This define will handle the emotes, it looks silly. I know ;-) */
EMOTE_HOOK
