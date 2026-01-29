/*
 *  /d/Sparkle/guilds/mercs/npc/gnimpsh_new.c
 *
 *  Gnimpsh has given up on his Life Quest, and now sits and laments
 *  bitterly the fact that when Maligant's Mercenaries disbanded and
 *  reformed, he was left out in the cold. He'll help players who are
 *  still a member of the old guild leave, and he also has a quest
 *  for players who are not members of the new guild.
 *
 *  Created March 2010, by Cooper Sherry (Gorboth)  
 */
#include "/d/Sparkle/guilds/new_merc/merc_defs.h"

inherit "/d/Gondor/std/monster";

#include <macros.h>
#include <ss_types.h>
#include <time.h>       /* For logging the quest */
#include <stdproperties.h>      /* for OBJ_M_NO_ATTACK */
#include "/d/Sparkle/sys/quests.h"

/* Definitions */
#define        QUEST_OBJECT "/d/Sparkle/guilds/new_merc/obj/journal"
#define        QUEST_PROP "_on_gnimpsh_journal_quest"
#define        SPY_PROMPT_PROP "_gnimpsh_mentioned_spy_prop"

/* Global Variables */
string *gIntroduced = ({});

/* Prototypes */
public void        create_gondor_monster();
public void        intro_me(object name);
public void        add_introduced(string str);
public void        cannot_see_speaker();
public void        help_gnimpsh();
public void        recruit_spy();
public int         is_free_merc(object who);
public int         check_solved(object who);
public void        give_journal(object who);
public void        check_journal(object who, object journal);
public void        reward_player(object who);


/*
 * Function name:        create_gondor_monster
 * Description  :        set up the npc with domain presets
 */
public void
create_gondor_monster()
{
    set_name("gnimpsh");
    set_title("the Former Record-Keeper of Maligant's Mercenaries");
    add_name("_merc_spy_quest_npc");
    set_race_name("gnome");
    set_long("A fretful little creature, this gnome looks "+
	"weary and hopeless. A pair of spectacles adorn his "+
	"aging face, and his hair is somewhat disheveled.\n");
    set_short("nervous little male gnome");
    set_adj(({"nervous", "little"}));
    set_stats(({ 50, 70, 60, 100, 60, 70}));
    set_skill(SS_AWARENESS,   65);
    set_skill(SS_HIDE,        25);
    set_skill(SS_DEFENCE,     50);
    set_alignment(350);

    add_prop(OBJ_M_NO_ATTACK, 
        "He would just run away and hide if you tried.\n");

    set_act_time(4);
    add_act("emote grumbles and mutters to himself.");
    add_act("say UpAndLeaveMeWithoutSoMuchAsAThankYou!TheyWon'tHave"
      + "TheLastLaugh,ThoseJerks!");
    add_act("emote groans and pulls at his already thinning hair.");
    add_act("emote exhales loudly, and folds his arms with a"
      + " \"Hmmph!\"");
    add_act("say ThatMorgan...AlwaysPlayingSoCoyAndNiceWhenMaligant"
      + "WasAround.SheShowedHerTrueColors,Didn'tShe!!");
    add_act("spit");

    set_cact_time(4);
    add_cact("shout What!?I'mJustAPoorOldGnome,YouLetMeBe!!");
    add_cact("shout ThisNeverWouldHaveHappenedWhenMaligantWas"
      + "Around.Oh,WhyDidIEverLeaveMt.Nevermind?!?");
    add_cact("shout GetAwayFromMe!You'reABiggerJerkThanAllThe"
      + "MercenariesPutTogether!");

    add_ask_item( ({ "guild" }),
        "say There'sNoGuildHere!GoFindThatWomanMorganIfYouWant"
      + "ToTalkAboutThat.NotMe!!");
    add_ask_item( ({ "mercenary", "mercenaries", }),
        "say Mercenaries?WhatMercenaries?!TheyAllLeftAndRefuseTo"
      + "InviteMeToTheirNewHeadQuarters!IDon'tEvenKnowWhatTheyAre"
      + "UpToTheseDays,ButIWantToFindOut.IJustWishICouldGetMore"
      + "PeopleToHelpMeOut.");
    add_ask_item( ({ "help", "help you", "help you out",
                     "help out" }), "@@help_gnimpsh@@");
    add_ask_item( ({ "spy", "journal" }), "@@recruit_spy@@");
    add_ask_item( ({"leave", "leave mercenaries", "leave guild",
                    "leaving", "leaving the mercenries",
                    "leaving the guild", "leaving mercenaries",
                    "leaving guild", "leave the guild",
                    "leave the mercenaries",}),
        "say OhSureWhyNot?Go,JoinTheNewGuildIfThatIsWhatYouReally"
      + "Want.EveryOneIsDoingIt.ItsAllTheRage!TheThingToDo!The"
      + "WayToBe!MarchRightAlongWithTheCrowd.<mercleave>IsWhat"
      + "YouNeedToDo.ThenYouAreFreeUnlikeGnimpsh!");
    add_ask_item( ({ "join", "join mercenaries", "jerk",
                     "jerks", "those jerks" }), "say Bah!The"
      + "GuildIsn'tHereAnymore,Can'tYouSeeThat?!GoFindThoseJerksIn"
      + "TheirFancyNewGuildhallIfYouAreSoInterested.");
    add_ask_item( ({ "life quest", "quest", "life's quest"}), "say Oh"
      + "Don'tRemindMe!!!BadEnoughThatMyLifeQuestIsTotallyRuined"
      + "WithoutYouBringingItUpOverAndOver...What'sThat?YouMean"
      + "YouDon'tKnowWhatItIs?Oh,Well,ISupposeThen...MyLifeQuest"
      + "IsToRecordTheNamesOfEveryLivingPerson.ButNowItCanNever"
      + "HappenThanksToThatWomanMorganAndHerFancyNewIdeas!");
    add_ask_item( ({ "background", "history", "past" }), "say WellI'mAGnome,"+
	"IWasBornInMountNevermind.IAmAnInventor,ButI'mCurrentlyOnBreak,"+
	"FulfillingMyLifeQuest.ButWhoCaresAnymore!ItsAllRuined!");
    add_ask_item( ({ "maligant" }), "say MaligantIs...Well...WasTheLeader"
      + "OfTheseMercenaries.HeLeft!!NowEverythingIsRuined!!");
    add_ask_item( ({ "dalizen" }), "say Gone!AndIDon'tCare.");
    add_ask_item("taryn", "say Don'tGetMeStartedOnThatOne!");
    add_ask_item("tarn", "say TarnWasOurBlackSmith.Gone!Jerk!!");
    add_ask_item("soren", "say Gone!Gone!Gone!");
    add_ask_item("morgan", "say Don'tTalkAboutHer!SheRuinedMyLife"
      + "QuestAndNowI'llDieWithNothingToShow!AllTheMercenariesWent"
      + "OffToJoinHerFancyNewOutfit!");
    add_ask_item( ({ "outfit", "fancy outfit", "fancy new outfit" }),
        "say MorganThinksShe'sTheNewMaligant.Well,She'sNot!ButThat"
      + "Didn'tStopAllTheMercenariesFromFollowingHerToHerFancyNew"
      + "Guildhall.");
    add_ask_item( ({ "guildhall", "new guildhall", "fancy guildhall",
                     "fancy new guildhally", "mercenary guildhall",
                     "mercenaries guildhall", "headquarters",
                     "new headquarters" }),
        "say Bah!IfSomeMorePeopleWouldHelpMeOutI'dFindOutWhat'sGoing"
      + "OnThere,IWould!");

    set_default_answer( ({ "say IDon'tKnow!", "say IDon'tCare!",
        "say GoBotherSomeoneElseWithSuchQuestions!",
        "emote rolls his eyes annoyedly.",
        "say DidIInSomeWayExpressInterestInAnythingYouHadToSay?",
        "say I'mSorry,DidIGiveYouTheImpressionThatIcared?MyMistake.",
        "say Don'tYouHaveAnythingBetterToDoThanPlagueMeWith"
      + "YourQuestions?" }) );
} /* create_gondor_monster */


/*
 * Function name:        intro_me
 * Description  :        allow the npc to react to introductions
 * Arguments    :        string name - the name of the player who
 *                                     intro'd.
 */
public void
intro_me(object name)
{
    if (member_array(capitalize(name->query_real_name()), gIntroduced) == -1)
    {
	command("grumble impatiently");
        command("introduce me to " + OB_NAME(name));
        command("say to " + OB_NAME(name) + " WhatDoYouWant?");
        gIntroduced += ({ capitalize(name->query_real_name()) });
    }
} /* intro_me */


/*
 * Function name:        add_introduced
 * Description  :        add the introduced player to the array
 *                       of names this npc knows.
 * Arguments    :        string str - the name of the introduced
 *                                    player
 */
public void
add_introduced(string str)
{
    object who = find_living(str);
    string name = capitalize(who->query_real_name());

    if (member_array(name, gIntroduced) == -1)
        set_alarm(2.8, 0.0, &intro_me(who));
} /* add_introduced */


/*
 * Function name:        cannot_see_speaker
 * Description  :        If Gnimpsh can't see the speaker, he
 *                       isn't very happy about it.
 */
public void
cannot_see_speaker()
{
    command("say WhatThe...?WhoDidThat?!?ShowYourself!!");
    return;
}


/*
 * Function name:        help_gnimpsh
 * Description  :        when a player asks gnimpsh about help,
 *                       this routine gets called.
 */
public void
help_gnimpsh()
{
    if (!this_player()->query_prop(SPY_PROMPT_PROP))
    {
        command("say Don'tTeaseMe!Oh,AreYouSerious?Well,IfYouReally"
          + "WantToHelpI'dCertainlyGiveYouSomethingToDo.INeedASpy!");

        this_player()->add_prop(SPY_PROMPT_PROP, 1);
        return;
    }

    command("say LikeISaid,IfYouWantToHelpMe,ICouldUseASpy!YouKnow"
      + "WhatASpyIs,Don'tYou?");
    return;
} /* help_gnimpsh */



/*
 * Function name:        recruit_spy
 * Description  :        begin the quest for a particular player
 */
public void
recruit_spy()
{
    if (!CAN_SEE(this_object(), this_player()))
    {
        cannot_see_speaker();
        return;
    }

    if (check_solved(this_player()))
    {
        command("say YourAssistanceWasAlreadyMostHelpful.Thanks"
          + "Again!");
        return;
    }

    if (!this_player()->query_prop(SPY_PROMPT_PROP))
    {
        command("say WhatAreYouTalkingAbout?I'mNotASpy!WhoToldYouThat!?!"
          + "GetAwayFromMe!");
        return;
    }

    if (IS_MERC(this_player()))
    {
        command("say What!?You'veGotTheDrattedInsigniaOfThatNew"
          + "OutfitMorganIsRunning!");
        command("say IWouldn'tTrustAnythingYouDidForMeAnyMoreThanICould"
          + "LiftAnElephant!NowGetOutOfHere!GoPlayInYourFancyNewGuildhall!");

        return;
    }

    if (this_player()->query_prop(QUEST_PROP))
    {
        if (!present("_merc_spy_journal", this_player()))
        {
            command("say WhatAreYouWaitingFor?");
            command("say What!?YouLostTheJournal?!OhForHeaven'sSake!");
            give_journal(this_player());
            command("say ThisTimeDon'tLoseIt!");

            return;
        }

        command("say WhatAreYouWaitingFor?FindAWayToGetIntoThe"
          + "GuildHallOfTheMercenaryGuildAndWriteWhatYouFindOn"
          + "TheirGuildBoardInTheJournalIGaveYou!ThenComeBackAnd"
          + "ReturnItToMeSoICanSeeWhatTheyAreUpTo.");

        return;
    }

    command("say Really?You'llDoIt?Oh,I'veBeenWaitingForSomeoneLike"
      + "YouToComeAlong!");
    command("say Here'sWhatIWantYouToDo.TakeThis...");
    give_journal(this_player());
    command("say IWantYouToFindAWayToSneakIntoTheGuildhallOfThese"
      + "SoCalledFreeMercenariesAndFindTheirGuildBoard.WhenYouDo,"
      + "CopyDownTheMostRecentNoteOnTheirBoardAndGetTheHeckOutOf"
      + "ThereBeforeAnyoneSeesYou!ThenBringTheJournalBackToMeSoI"
      + "CanSeeWhatThoseJerksAreUpTo.");
    command("say WhatAreYouWaitingFor?!GetGoing!GoGoGoGoGo!");
      
    this_player()->add_prop(QUEST_PROP, 1);

    write_file(LOG_DIR + "merc_spy",
        TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
      + ctime(time())[11..18] + ") "
      + capitalize(this_player()->query_real_name()) 
      + " began the Merc Spy Quest.\n");

    return;
} /* recruit_spy */


/*
 * Function name:        is_free_merc
 * Description  :        See if this player is a member of the Free
 *                       Mercenary Guild. Gnimpsh won't deal with
 *                       anyone who is.
 * Arguments    :        object who - the player
 * Returns      :        int 1 - is a member
 *                       int 0 - is not a member
 */
public int
is_free_merc(object who)
{
    if (IS_MERC(who))
    {
        command("say What!?You'veGotTheDrattedInsigniaOfThatNew"
          + "OutfitMorganIsRunning!LikeYou'dHelpMe!IWouldn'tTrust"
          + "AnythingYouDidForMeAnyMoreThanICouldLiftAnElephant!"
          + "NowGetOutOfHere!GoPlayInYourFancyNewGuildhall!");

        return 1;
    }

    return 0;
} /* is_free_merc */


/*
 * Function name:        check_solved
 * Description  :        See if the player already solved this
 *                       quest.
 * Arguments    :        object who - the player
 * Returns      :        int 1 - already solved
 *                       int 0 - not yet solved
 */
public int
check_solved(object who)
{
    return who->test_bit("Sparkle",
                         MERC_SPY_GROUP,
                         MERC_SPY_BIT);
} /* check_solved */


/*
 * Function name:        give_journal
 * Description  :        Give the quest object to the player so that
 *                       they can begin the quest.
 * Arguments    :        object who - the player
 */
public void
give_journal(object who)
{
    object  journal = clone_object(QUEST_OBJECT);

    if (journal->move(this_object()))
    {
        /* Gnimpsh shouldn't be carrying anything, so in the case
         * that he is too full it means some creative player has
         * loaded him up somehow.
         */
        command("drop all");
        journal->move(this_object());
    }

    command("give journal to " + OB_NAME(this_player()));
    return;
} /* give_journal */


/*
 * Function name:        check_journal
 * Description  :        Called when a player tries to <return> the
 *                       journal to Gnimpsh. If the journal has
 *                       had text copied into it, the player is
 *                       rewarded and the quest solved.
 * Arguments    :        object who - the player
 *                       object journal - the journal object
 */
public void
check_journal(object who, object journal)
{
    mixed   note_txt;
    string *note_contents;
    string  first_line;
    int     length_found = 0;
    int     name_found = 0;
    int     i = 1;
    int     j = 0;
    int     length;
    string  name;

    if (!CAN_SEE(this_object(), this_player()))
    {
        cannot_see_speaker();
        command("emote gives the journal back.");
        return;
    }

    if (!who->query_prop(QUEST_PROP))
    {
        command("say WhatThe...!??WhereDidYouStealThatFrom?I"
          + "Don'tRememberGivingYouMyJournal!StayAwayFromMy"
          + "Stuff!");
        command("emote takes the journal and whisks it out of"
          + " sight.");
        journal->remove_object();

        return;
    }

    if (is_free_merc(who))
    {
        command("emote takes the journal and whisks it out of"
          + " sight.");
        journal->remove_object();

        return;
    }

    command("say ThatWasFast!Quick,LetMeSeeThat!");
    command("emote quickly reads through the journal.");

    note_txt = journal->query_note_txt();

    if (!note_txt)
    {
        command("blink");
        command("say SomeSortOfJokeYouHaveGoingHere?ThereisNothing"
          + "WrittenInThisJournal!!OhHaHaHaFunnyJokeOnTheGnome!Now"
          + "GetGoingYouIdiot!BringMeSomethingToReadFromTheirGuild"
          + "Board!");
        command("emote gruffly returns the journal and snorts in"
          + " frustration.");

        return;
    }

    /* So, here we have one of those Gorboth moments, where I am
     * doing all sorts of noodling to get the exact effect I want.
     * I have no doubt this will be utterly unfathomable to future
     * readers of the code if I don't explain myself, so here is
     * the idea. I want the npc to be able to mention the title
     * of the note that got copied into the journal, and the
     * name of the author. So, what I've done is used arrays and
     * lots of text searching via explode() to find the things I
     * want. First, we are going after the title of the note, so I've
     * used the array variable note_contents, which by using a pad
     * of three empty spaces "   " is likely to capture the title
     * of the note as it was posted on the board. Thus,
     * note_contents[0] is assumed to be the note title below.
     * Then, to get the author of the note, I have to do a great
     * deal more work. For this, we assume a typical note title
     * might look like this:
     *
     * New Trainer                           Gorboth      16 Mar
     *
     * With this one, I am using the array variable first_line, to
     * capture only the first line of the note. Then, I start
     * searching backwards through the line to first skip the
     * month name "Mar", then look for the first word that is 
     * found that is greater than 2 characters long. This will
     * ignore the date and any spaces between the date and the name
     * of the author. It seems to work. However, if in the future,
     * some eager Archwizard decides to change the format for how
     * notes are posted on boards, this will all go kablooey. In
     * that case, a wizard will need to go in and either change
     * the method of finding the author name or (more realistically)
     * simply remove the command() line below where Gnimpsh tries
     * to speak the title of the note and mention the author.
     *
     * A lot of work for small effect, but I live for this stuff!
     */
    note_contents = explode(note_txt, "   ");
    first_line = explode(note_txt, "\n")[0];

    while (!name_found)
    {
        while (!length_found)
        {
            name = first_line[-i..];

            if (explode(name, "")[0] == " ")
            {
                length_found = 1;
                name = name[1..];
            }
            else
            {
                i++;
            }
        }

        if (j && strlen(name) > 2)
        {
            name_found = 1;
        }        

        j++;
        length_found = 0;
        first_line = first_line[..-(i + 1)];
        i = 0;
    }

    command("gasp");
    command("cackle");
    command("say OhLookAtThis!SomeoneHasRecentlyPostedANoteOn"
      + "TheMercenaryBoard!");
    command("say \"" + note_contents[0] + "\"...Written"
      + "BySomeoneNamed..." + capitalize(name) + "!");
    command("Let'sSeeWhatIt'sAllAbout...");
    command("emote reads the journal entry carefully.");
    command("say Oh,ThisIsFascinating!");
    command("grin malic");
    command("say GoodGood,ICan'tThankYouEnough!IDon'tHaveAnyReward"
      + "ForYouMyselfButYouProbablyGotSomeValuableExperienceFromAll"
      + "TheSneakingAroundYouHadToDo.");
    command("hug " + OB_NAME(who));

    journal->remove_object();
    reward_player(who);

    return;
} /* check_journal */


/*
 * Function name:        reward_player
 * Description  :        Here we give out the actual quest reward and
 *                       set the bits.
 * Arguments    :        object who - the player
 */
public void
reward_player(object who)
{
    int    reward = who->query_exp();

    if (check_solved(who))
    {
        write("You do not feel more experienced this time.\n");

        write_file(LOG_DIR + "merc_spy",
            TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
          + ctime(time())[11..18] + ") "
          + capitalize(this_player()->query_real_name()) 
          + " solved the quest another time for zero exp.\n");

        return;
    }

    /* Players may not be rewarded more experience than they have
     * already accumulated.
     */
    if (reward > MERC_SPY_EXP)
    {
        reward = MERC_SPY_EXP;
    }

    who->set_bit(MERC_SPY_GROUP, MERC_SPY_BIT);
    who->add_exp_quest(reward);
    who->catch_tell("You feel more experienced!\n");

    write_file(LOG_DIR + "merc_spy",
        TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
      + ctime(time())[11..18] + ") "
      + capitalize(this_player()->query_real_name()) 
      + " (" + who->query_average_stat() + ") is awarded "
      + reward + " experience.\n");

    return;
} /* reward_player */


/*
 * Function name: catch_question
 * Description:   This function is called in each living being someone asks a
 *                question to.
 * Arguments:     question - The question as put
 */
public void
catch_question(string question)
{
    if (!CAN_SEE(this_object(), this_player()))
    {
        cannot_see_speaker();
        return;
    }

    ::catch_question(question);
} /* catch_question */
