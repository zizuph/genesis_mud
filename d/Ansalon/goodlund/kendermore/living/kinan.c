/* Kinanserofin, the gnome of Kendermore, Gwyneth, June 1999 */

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit "/std/act/action.c";
inherit AM_FILE

public void
create_krynn_monster()
{
    if (!IS_CLONE)
        return;

    set_name("kinanserofin");
    add_name("kinan");
    set_living_name("kinan");
    set_race_name("gnome");
    set_title("of Mt. Nevermind");
    set_long("He busily runs about, looking in books, checking the contents " + 
        "of jars, and marking things off. He looks very much at home in " + 
        "cluttered little house, but you wonder what he's doing in " + 
        "Kendermore.\n");
    set_adj("short");
    add_adj("talkative");
    set_gender(G_MALE);
    set_introduce(1);
    set_stats(({70,75,75,80,80,60}));
    set_skill(SS_AWARENESS, 50);
    set_alignment(400);
    set_knight_prestige(-40);

    set_act_time(15);
    add_act("emote studies a book closely.");
    add_act("emote makes a mark on a piece of paper.");
    add_act("emote plants a seed in a pot full of soil, and pours some " + 
        "water on it.");
    add_act("say ILikeItHereInKendermore!AllTheKenderComeBackWithTheMost" + 
        "InterestingPlantsFromTheirTravels!");
    add_act("say KendermoreIsSuchAPleasantPlace.");
    add_act("say Oh,ThisIsAnInterestingSeed!");

    set_default_answer("I'mSorry,IDon'tKnowAboutThat!\n");
    add_ask(({"kendermore", "kender", "krynn", "travels"}), "say ICameTo" + 
        "KendermoreBecauseOfMyLifeQuest.IHateTravelling,SoIHaveTheKenderDo" + 
        "ItForMe!TheyBringBackTheMostWonderfulPlants!", 1);
    add_ask(({"quest","life quest"}), "say EveryGnomeHasALifeQuest.MineIs" + 
        "ToCollectOneOfEverySinglePlantAndHerbInAllOfKrynn!", 1);
    add_ask(({"plant", "plants", "herb", "herbs", "seed", "seeds"}), 
        "say Unfortunately,YouCan'tJustStickThemInAPotAndExpectThemToGrow." +
        "YouHaveToHaveJustTheRightConditions.", 1);
    add_ask(({"conditions", "right conditions"}), "say SomePlantsGrowBestIn" + 
        "ADryDesert,WhileOthersOnlyGrowInSwamps!IHadTheHelpOfAMage.You'll" + 
        "SeeHowIfYouGoBeyondThatDoor.", 1);
    add_ask(({"door", "swamps", "swamp", "desert"}), "say It'sReallyAmazing" + 
        "BeyondThatDoor!", 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    set_alarm(1.0,0.0,"arm_me");
}

/* Function name : Arm me
 * Description : Clones, wears and wields armours and weapons.
 * Returns : Null
*/

void
arm_me()
{
    seteuid(getuid(TO));
    clone_object(KOBJ + "shirt")->move(TO);
    clone_object(KOBJ + "leggings")->move(TO);
    clone_object(KOBJ + "boots")->move(TO);

    command("wear all");
}

