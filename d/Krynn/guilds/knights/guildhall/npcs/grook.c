/* The gnome who sells doves in VKeep
* updated by Teth, Feb.1/96
*
* Navarre Sep 1st 2006, removed wrong spaces in add_ask functions.
*                       Gnomes dont speak with spaces. 
*                       Fixed in response to typo report.
*/

#include "../../local.h"
#include <macros.h>

inherit M_FILE

#include "./std/killer.h"

void
create_krynn_monster()
{
    set_name("grook");
    set_title("TheKeeperOfDoves");
    set_introduce(1);
    ALWAYSKNOWN;
    add_name("pig_gnome");
    set_extra_long("A dove sits on his right shoulder.\n");
    set_race_name("gnome");
    set_adj("small");
    default_config_mobile(50);
    set_all_attack_unarmed(50, 50);
    set_all_hitloc_unarmed(50);
    set_gender(0);
    set_alignment(300);
    set_knight_prestige(-6);
    add_prop(NPC_I_NO_LOOKS,1);
    
    add_item("dove", "The stormcloud grey dove coos softly " +
        "in Grook's ear. It seems to love its keeper quite a " +
        "bit, but that is probably because Grook is a gentlegnome." + 
        " Occasionally, it flaps its muscular wings.\n");
    set_act_time(3);
    add_act("emote says: SomethingKeepsScaringMyDoves!TheyGetSo" + 
        "FrightenedThatTheyShiverInTheirFeathers!");
    add_act("emote says: ILoveDovesIThinkTheyAreTheMostBeautiful" +
        "CreaturesInTheWorld WouldYouLikeOne?TheyAreSoHelpful!");
    add_act("emote lightly strokes the feathers of the nearest dove.");
    add_act("emote tickles a dove underneath the beak and coos: " +
        "KootchieKootchieKoo MyLittleOne!");
    add_act("emote sighs as he thinks about his lifequest.");
    set_default_answer("Grook says: IDon'tKnowWhatYouAreTalkingAbout.\n");
    add_ask(" [about] 'lifequest'", "Grook says: MyLifeQuestIs"+
        "VeryExcitingIAmSoGladYouWantToHearAboutItIWantToSeeIfICan" +
        "MakeAnUnderwaterCommunicatingServiceWithSwimmingDoves" +
        "ButSoFarMyPreciousDovesKeepDrowningItIsVerySadButNowI" +
        "AmOutfittingThemWithMyPUBATheDoveUnderwaterBreathing" +
        "ApparatusIThinkItWillRevolutionizeTheIndustry!\n");
    add_ask(" [about] 'dove' / 'doves'", "Grook says: DovesAreProud" +
        "MembersOfTheClassAvesAndTheyAreVerySmart BecauseTheyAlways" +
        "SeemToKnowWhereHomeIsAndWhereOtherPeopleAreSoThatTheyCanBe" +
        "UsedAsAMethodOfLongDistanceCommunication!\n");
}


