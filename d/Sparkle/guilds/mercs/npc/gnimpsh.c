/*
 * Mercenary guild recruiter, by Morrigan 11/2001
 *
 * Adapted from code by Auberon and Gwyneth
 * Updated for Sparkle by Lunatari 2006
 */
#include "../merc.h"

inherit MERC_GONDOR_NPC

#include "attackers.h"

string *gIntroduced = ({});

void
create_gondor_monster()
{
    set_name("gnimpsh");
    set_title("the Record-Keeper of Maligant's Mercenaries");
    add_name("recruiter");
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

    add_ask_item(({"mercenary", "mercenaries"}),
        "say TheMercenariesAreForIndividualsWhoDon'tWantTheirDestinies"+
	"DeterminedForThem. AtLeastThatIsWhatMaligantSays,GoAskHim! Unless"+
	"YouWantToHireOne,ThenYouMustTalkToMe!");
    add_ask_item(({"statue", "statues"}),
        "say ThereAreStatuesOfOurMightiestWarriorsInTheGreatHallForHistorical"+
        "Purposes. "+
        "SomeOfOurCurrentMembersHavePosedForStatuesThere,Too,IThink.");
    add_ask_item(({"hire", "mercenaries for hire", "available mercenaries"}),
	"say YouCan<list mercenaries>HereToSeeWhoIsAvailable,You'llHaveTo"+
	"ContactThemAndMakeTheMonetaryArrangementsYourself.");
    add_ask_item(({"leave", "leave mercenaries", "leave guild"}),
        "say ItIsPossibleToLeaveTheMercenariesHere,ButYouShouldn'tDoThat.");
    add_ask_item(({"join", "join mercenaries"}), "say EveryoneShouldBeA"+
	"Mercenary,Because-Well,BecauseISaidSo.");
    add_ask_item(({"holster", "guild item", "scabbard"}), "say IfYouLose"+
	"Yours,YouCanRequestANewOne.\n");
    add_ask_item(({ "rules", "rule" }), "say WellThereIsAPosterHere,Or"+
	"YouCanAskMaligant...WaitNoYouCan't...He'sGone! CanYouRead?");
    add_ask_item(({ "life quest", "quest", "life's quest"}), "say MyLifeQuest"+
	"IsToRecordTheNameOfEveryLivingPerson. MaligantWasNiceEnoughToLetMeBe"+
	"HisRecordKeeper,IThinkThisMightTakeAWhile,Though.");
    add_ask_item(({"background", "history", "past" }), "say WellI'mAGnome,"+
	"IWasBornInMountNevermind.IAmAnInventor,ButI'mCurrentlyOnBreak,"+
	"FulfillingMyLifeQuest.SpeakingOfMyLifeQuest,WhyDon'tYouFindSome "+
	"PeopleToJoinTheMercenariesForMe,SoICanGetBackToInventingAgain"+
	"SomeDay?" );

    add_ask_item(({ "maligant" }), "say MaligantIs...Well...WasTheLeader"
      + "OfTheseMercenaries. HeLeft!! HaveYouSeenHim??!");
    add_ask_item( ({ "dalizen", "taryn", "tarn", "corwin", "bryce",
                     "raddick" }),
        "say They'veAllLeftUs! Ohhh! WhatHasBecomeOfMyLifeQuest?!");
    add_ask_item("morgan", "say She'sRuinedEverything! SheShouldn'tHaveTried"
        + "ToMakeThingsBetter - SheOnlyMadeItWorse!");

    set_default_answer( ({ "say IDon'tKnow.", "say IDon'tCare.",
        "say AskSomeoneElse,LikeMaligant.", "emote rolls his eyes impatiently.",
        "say DidIInSomeWayExpressInterestInAnythingYouHadToSay?", "say I'mSorry, "+
	"DidIGiveYouTheImpressionThatIcared? MyMistake.", "say Don'tYouHave"+
	"AnythingBetterToDoThanPlagueMeWithYourQuestions?" }) );
}

void
intro_me(object name)
{
    if (member_array(capitalize(name->query_real_name()), gIntroduced) == -1)
    {
	command("grumble impatiently");
        command("introduce me to " + OB_NAME(name));
        command("say to " + OB_NAME(name) + " Yes,Yes,WhatDoYouWant?");
        gIntroduced += ({ capitalize(name->query_real_name()) });
    }
}

void
add_introduced(string str)
{
    object who = find_living(str);
    string name = capitalize(who->query_real_name());

    if (member_array(name, gIntroduced) == -1)
        set_alarm(2.8, 0.0, &intro_me(who));
}
