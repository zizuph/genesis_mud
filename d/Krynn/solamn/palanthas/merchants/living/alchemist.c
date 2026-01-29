/*
 * 07 May 16 - added ability to buy identify scroll for 10 plat
 *             Arman Kharas
 *
 * 25 Aug 16 - commented out the ability to buy scroll. Decided to restrict
 *             the spell to the WoHS.
 */

#include "../../local.h"
#include <money.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Krynn/guilds/wohs/defs.h"

inherit CITIZEN;
inherit "/d/Ansalon/common/cheater";

#define SB_SCROLL     "/d/Krynn/common/scrolls/cyclonic_blast_scroll"
#define ICE_SCROLL    "/d/Krynn/common/scrolls/ice_shard_scroll"
#define STONE_POT     "/d/Krynn/common/potions/stone_potion"
#define STEEL_POT     "/d/Krynn/common/potions/steel_potion"
#define SPEED_POT     "/d/Krynn/common/potions/speed_potion"
#define SWIM_POT      "/d/Ansalon/goodlund/bloodsea/obj/swim_potion"
#define WATER_GEM     "/d/Krynn/common/warfare/rewards/magic_gems/triangular_sea_agate"
#define PURSE         "/d/Sparkle/area/faerie/obj/purse"

int alarm_id;

void
create_krynn_monster()
{
	 set_name("gringo");
	 set_title("the Amazing, Alchemist from Mount Nevermind");
	 add_name(({"shopkeeper","alchemist"}));
	 set_race_name("gnome");
	 set_gender(0);
	 set_adj("beady-eyed");
	 add_adj("white haired");
	 set_long("This strange looking gnome seems to be an alchemist of sorts. " +
            "Thick black eyebrows seem permanently narrowed as he carefully mixes " +
            "liquids and components in the most professional manner. However " +
            "you find it very difficult to take him too seriously due to his " +
            "shock of wild white hair that he has had little success in controlling, " +
            "obviously a result of a failed and rather explosive experiment.\n");

	 set_act_time(25);
	 add_act("emote studies a mirky potion closely.");
         add_act("emote chatters: HmmIfOnlyIHadMoreBells...");
	 add_act("emote starts cleaning out a vial with a dirty cloth.");
	 add_act("emote chatters: DoYouWantToBuyAPotion?YesYesYes?IHaveJustTheThing!");
	 add_act("emote chatters: GullyDwarvesMakeGreatTestSubjects! UnfortunatelyI"+
            "FindMostOfMyPotionsHaveANegativeAffect! TheyLimitTheirNumericalCapacity"+
            "ToTwo...");
	 add_act("emote puts a sprig of something into his mortar.");
	 add_act("emote carefully pours a smokey liquid into his mortar, and quickly mixes "+
            "it with the contents into a smelly paste.");

	 set_all_hitloc_unarmed(50);

	 set_stats(({70,70,70,70,70}));

	 set_skill(SS_UNARM_COMBAT,50);
	 set_skill(SS_BLIND_COMBAT,100);
	 set_skill(SS_PARRY,50);
	 set_skill(SS_DEFENCE,65);
	 set_skill(SS_AWARENESS,50);
	 set_skill(SS_WEP_SWORD,50);
	 set_skill(SS_WEP_POLEARM,50);
	 set_skill(SS_WEP_CLUB,50);
	 set_skill(SS_WEP_KNIFE,50);

	 add_prop(NPC_I_NO_RUN_AWAY,1);
         remove_prop(NPC_M_NO_ACCEPT_GIVE);

         add_ask(({"help","spell","teach magic","teach spell","magic",
             "scroll","scrolls","parchment","spells","task","help","quest"}), 
             VBFC_ME("spell_hint"));

         add_ask(({"gold quill","golden quill","golden-scaled sahuagin",
            "quill"}), VBFC_ME("quill_hint"));

         add_ask(({"sahuagin","sahuagins","territory","underwater territory"}),
            "say SahuaginAreTheSeaDevilsOfTheDeep!SailorsAvoidTheWatersNorth"+
            "OfTheGreatReefOutsideTheBayOfBranchallaAsThatIsWhereTheyLair!", 1);

	 set_alignment(0);
	 set_knight_prestige(-1);

         set_alarm(1.0, 0.0, "equip_me");
	 set_mm_in("arrives.");
}

string
quill_hint()
{
    command("say TheGoldQuillIsSoRare!CanOnlyBeFoundOnASahuagin" +
        "PriestessAndOnlyAGolden-ScaledOne!YouWillFindThemInThe" +
        "DeepestWatersOfTheirUnderwaterTerritories!");
    return "";
}

string
spell_hint()
{
    if(!WOHS_MANAGER->query_scribed_spell(this_player(),"suacodrevab") &&
        (TP->query_advanced_spells_max() > 0))
    {
        command("say GreatWizard!IHaveAScrollOfAdvancedMagic!!");
        command("say APowerfulDamagingWindSpell!");
        command("say BringMeAGoldQuillFromAGolden-ScaledSahuagin" +
            "PriestessAndItIsYours!");
        command("bounce");
        return "";

    }

    if(WOHS_MANAGER->query_scribed_spell(this_player(),"suacodrevab") &&
        !WOHS_MANAGER->query_scribed_spell(this_player(), "xarzithinloilfrey"))
    {
        command("say GreatWizard!IHaveAnotherScrollYouMayBeInterestedIn?");
        command("say AMinorSpellButOneYouAreUnlikelyToHave!");
        command("say BringMeAnotherGoldQuillFromAGolden-ScaledSahuagin" +
            "PriestessAndItIsYours!");
        command("bounce");
        return "";
    }

    if(!WOHS_MANAGER->query_scribed_spell(this_player(),
        "xarzithinloilfrey") && (TP->query_minor_spells_max() > 0))
    {
        command("say AspiringWizard!IHaveAScrollOfMagicYouMayWant!!");
        command("say AMinorSpellButOneYouAreUnlikelyToHave!");
        command("say BringMeAGoldQuillFromAGolden-ScaledSahuagin" +
            "PriestessAndItIsYours!");
        command("bounce");
        return "";
    }

    command("say UnfortunatelyIAmAllOutOfMagicScrollsAtTheMoment!");
    command("sigh");
    command("say IHaveAnOrderOutstandingWithTheTowerOfWayrethFor" +
       "More..");
    command("say ButTheyAreInSuchDemand!");
    command("say StillIHaveOtherTreasuresThatICouldTradeYou!");
    command("say BringMeAGoldQuillFromAGolden-ScaledSahuagin" +
        "PriestessAndIWillTradeYouForIt!");
    return "";
}

void
equip_me()
{
    object cloak;
    cloak = clone_object("/d/Krynn/gnome/obj/cloak");
    cloak->add_name("_alchemist_item");
    cloak->move(TO);
    command("wear all");

}

void
give_it_back(object ob, object from)
{
    string what,
    who;
    what = L(ob->query_short());
    who = from->query_real_name();
    command("emote looks closely at the " + what + ".");
    command("say ThankYouButIHaveNoUseForThat.");
    command("say HereTakeItBackFriend.");
    command("give " + what + " to " + who);
    command("drop " +what);
}

void
given_gold_quill(object ob, object from)
{
    string what, who;
    what = L(ob->query_short());
    who = from->query_real_name();

    object scroll, herb1, herb2, money;

    command("emote looks closely at the " + what + ".");
    command("beam excited");
    command("say YouDidIt!ARareGoldQuill!ThankyouThankyou!");
    command("emote tucks the " + what + " away on a shelf.");
    ob->remove_object();

    if(!WOHS_MANAGER->query_scribed_spell(this_player(),"suacodrevab") &&
        (TP->query_advanced_spells_max() > 0))
    {
        command("emote takes a dusty scroll down from one of the shelves.");
        command("say AsPromisedHereIsTheScrollOfAPowerfulDamagingWindSpell!");

        scroll = clone_object(SB_SCROLL);
        scroll->add_name("_alchemist_item");
        scroll->move(TO, 1);
        what = L(scroll->query_short());
        command("give " + what + " to " + who);
        command("drop " +what);

        command("say IfYouEverFindMoreGoldQuillsBringThemToMe!");
        command("say IWillRewardYouHandsomely!");
        return;
    }
    else if(WOHS_MANAGER->query_scribed_spell(this_player(),"suacodrevab") &&
        !WOHS_MANAGER->query_scribed_spell(this_player(),"xarzithinloilfrey"))
    {
        command("say IHaveAlreadyGivenYouTheScrollOfAPowerfulDamagingWindSpell!");
        command("ponder");
        command("emote takes a dusty scroll down from one of the shelves.");
        command("ponder");
        command("say PerhapsYouWouldFindThisOfValue?");
        command("say IGotItFromASailorWhoFoundItInAChestCaughtInANetNearIcewall.");
        command("say Here!UseItInGoodDays!");

        scroll = clone_object(ICE_SCROLL);
        scroll->add_name("_alchemist_item");
        scroll->move(TO, 1);
        what = L(scroll->query_short());
        command("give " + what + " to " + who);
        command("drop " +what);


        command("beam");
        command("say IfYouEverFindMoreGoldQuillsBringThemToMe!");
        command("say IWillRewardYouHandsomely!");
        return;

    }
    else if(!WOHS_MANAGER->query_scribed_spell(this_player(),"xarzithinloilfrey") &&
        (TP->query_minor_spells_max() > 0))
    {
        command("emote takes a dusty scroll down from one of the shelves.");
        command("ponder");
        command("say AsAnAspiringSpellcasterIThinkYouWouldFindThisOfValue.");
        command("say IGotItFromASailorWhoFoundItInAChestCaughtInANetNearIcewall.");
        command("say Here!UseItInGoodDays!");

        scroll = clone_object(ICE_SCROLL);
        scroll->add_name("_alchemist_item");
        scroll->move(TO, 1);
        what = L(scroll->query_short());
        command("give " + what + " to " + who);
        command("drop " +what);

        command("beam");
        command("say IfYouEverFindMoreGoldQuillsBringThemToMe!");
        command("say IWillRewardYouHandsomely!");
        return;
    }

    command("emote rummages around through his shelves.");
    command("say Here!AWorthyTrade!UseItInGoodDays!");

    // Gnome gives a random reward to the individual.
    switch(random(10))
    {
        case 0:
            scroll = clone_object(STONE_POT);
            scroll->add_name("_alchemist_item");
            scroll->move(TO, 1);
            what = L(scroll->query_short());
            command("give " + what + " to " + who);
            command("drop " +what);
        break;
        case 1:
            scroll = clone_object(STEEL_POT);
            scroll->add_name("_alchemist_item");
            scroll->move(TO, 1);
            what = L(scroll->query_short());
            command("give " + what + " to " + who);
            command("drop " +what);
        break;
        case 2:
            scroll = clone_object(SPEED_POT);
            scroll->add_name("_alchemist_item");
            scroll->move(TO, 1);
            what = L(scroll->query_short());
            command("give " + what + " to " + who);
            command("drop " +what);
        break;
        case 3:
            scroll = clone_object(SWIM_POT);
            scroll->add_name("_alchemist_item");
            scroll->set_heap_size(6);
            scroll->move(TO, 1);
            what = L(scroll->query_short());
            command("give sea-green potions to " + who);
            command("drop " +what);
        break;
        case 4:
            scroll = clone_object(WATER_GEM);
            scroll->add_name("_alchemist_item");
            scroll->move(TO, 1);
            what = L(scroll->query_short());
            command("give gems to " + who);
            command("drop " +what);
        break;
        case 5..7:
            scroll = clone_object(PURSE);
            scroll->add_name("_alchemist_item");
            scroll->move(TO, 1);
            money = MONEY_MAKE_GC(120);
            money->move(scroll, 1);
            command("$give purse to " + who);
            command("$drop purse");
        break;
        default:
            scroll = clone_object("/d/Gondor/common/obj/herbpouch");
            scroll->add_name("_alchemist_item");
            scroll->move(TO, 1);
            herb1 = clone_object("/d/Krynn/common/herbs/salt_wort");
            herb1->set_heap_size(200);
            herb1->move(scroll, 1);
            herb2 = clone_object("/d/Krynn/common/herbs/bur_reed");
            herb2->set_heap_size(200);
            herb2->move(scroll, 1);
            command("$give pouch to " + who);
            command("$drop pouch");
        break;
    }

    command("beam");
    command("say IfYouEverFindMoreGoldQuillsBringThemToMe!");
    command("say IWillRewardYouHandsomely!");
    return;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(ob->id("_alchemist_item"))
    {
	return;
    }

    if(ob->id("_gold_sahuagin_priestess_quill"))
    {
        set_alarm(1.0, 0.0, &given_gold_quill(ob, from));
	return;
    }

    set_alarm(1.0, 0.0, &give_it_back(ob, from));
    return;
}

