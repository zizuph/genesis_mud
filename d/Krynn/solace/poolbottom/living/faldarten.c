#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/solace/poolbottom/local.h"
#include "/d/Krynn/guilds/sohm/defs.h"

inherit "/d/Krynn/std/monster";

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("faldarten");
    set_living_name("faldarten");
    set_title("the Alchemist, Esteemed Transmuter");
    set_race_name("gnome");
    set_adj("green-bearded");
    add_adj("red-robed");
    set_gender("G_MALE");
    set_long("Before you stands a gnome dressed in the formal red robes of a " +
        "Wizard of High Sorcery. The effect is somewhat diminished by the chemical " +
        "stains and fire burns across it, however it is clear that this gnome is " +
        "the school's alchemist. You can purchase alchemical equipment from " +
        "him as well as trade potions.\n");

    set_stats(({79,100,100,136,136,89,89}));
    set_hp(query_max_hp());

    set_skill(SS_WEP_POLEARM, 50);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_FORM_ENCHANTMENT, 100);

    set_alignment(0);
    set_knight_prestige(0);
    set_act_time(20);
    add_act("emote squints at a large glass retort, watching intently the flow of " +
        "white vapour along the downward-pointing neck of the vessel.");
    add_act("say WhereDidIPutMyMortarAndPestle?"); 
    add_act("emote strokes his long green beard thoughtfully.");
    add_act("say MustBeCarefulWithThePhosphorus...");
    add_prop(OBJ_M_NO_ATTACK,"The gnome alchemist is protected " +
      "by powerful runes of magic, keeping him safe from harm.\n");
    add_prop(NPC_I_NO_RUN_AWAY,1);

    add_ask(({"alchemy","training"}),VBFC_ME("alchemy_hint"));
    add_ask(({"alchemist","transmuter"}),VBFC_ME("alchemist_hint"));
    add_ask(({"order of the red robes","red robes","order","test",
      "test of high sorcery"}),VBFC_ME("test_hint"));
    add_ask(({"potions","potion","buy potions","sell potions","trade potions"}),
      "say IWillBuyAndSellPotionsStudentsBringToMe!ListPotionsToSee" +
      "WhatIHave.", 1);
    add_ask(({"help","spell","teach magic","teach spell","magic","spells"}),VBFC_ME("spell_hint"));
    add_ask(({"mageware","mageware shops"}),VBFC_ME("mageware_hint"));
    add_ask(({"herbs","herbalist","herb"}),VBFC_ME("herbalist_hint"));

    set_default_answer("The gnomish alchemist is distracted by an experiment, and didn't " +
      "hear your question.\n");

    trig_new("%w 'introduces' %s","react_to_intro");

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    seteuid(getuid());
}

void
react_to_intro(string who,string garbage)
{
    set_alarm(2.0,0.0,"return_intro",who);
}

void
return_intro(string who)
{
    who = L(who);
    if (P(who,E(TO)))
    {
	command("introduce myself");
    }
}

string
herbalist_hint()
{
    command("think");
    command("say ThereIsNoHerbalistInTheSchool.");
    command("say RemingtonColtonUsedToSellHerbsInSolace...");
    command("say ButAfterAFallingOutWithTheobaldHeLeftTown...");
    command("say ButYouCanFindHimJustOutsideOfTown...");
    command("say OnTheWesternSideOfCrystalmirLake!");
    command("say YouCanBuyAndSellHerbsWithRemington.");
    command("smile supportive");
    command("say ForHerbalistSuppliesMaybeHeadDownTo...");
    command("say TheMagewareShopInHaven.");
    return "";
}

string
alchemy_hint()
{
    command("jump");
    command("say YouStartledMe!");
    command("emote looks worriedly at a bubbling retort.");
    command("say CouldHaveBlownTheRoofOffAgain!");
    command("say YesYesICanTrainYouInAlchemy!");
    command("say Just<improve>or<learn>!");
    command("say ThereIsAlsoAnAlchemy101BookYouShouldRead" +
            "InTheLibraryDownstairs!");
    command("smile supportive");
    return "";
}

string
mageware_hint()
{
    command("emote looks distractedly at a bubbling retort.");
    command("say ThereAreMagewareShopsInPlacesLikeHavenAndPalanthas..");
    command("say TheySellAllSortsOfMagicalStuffFromVialsToHerbsToPotionsToEvenSpellScrolls..");
    return "";
}

string
alchemist_hint()
{
    command("smile");
    command("say AfterPassingTheTestOfHighSorceryIBecameTheSchoolAlchemist!");
    command("say IJoinedTheOrderOfTheRedRobes.");
    command("twinkle proud");
    command("say MySpecialtyIsTransmutation.");
    command("say YouCanPickASpecialisationDownstairsInTheLibrary'sNorthWing.");
    command("smile supportive");
    return "";
}

string
test_hint()
{
    command("ponder");
    command("say ICan'tTalkMuchAboutTheTestOfHighSorcery..");
    command("say ThatIsASecretOfTheOrderButWhenISuccessfullyFinished...");
    command("say IJoinedTheNeutralOrderOfTheRedRobesThatFollowLunitari.");
    return "";
}

string
spell_hint()
{

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"riyitchikohk"))
    {
        command("say IHaveAlreadyTaughtYouACantripDidntI..");
        command("frown");
        command("say MaybeSpeakToTheobaldIfYouWantToLearnMoreMagic..");
        command("say OrTheQuestMasterTarshirInSolace...");
        command("say OrMaybeSeekOutTheMagewareShopsAroundTheRealmsForSpellScrolls..");
        command("say OrTheLairsOfMonsters!!!");
        command("think");
        command("say OrMaybeNot.");
        return "";
    }

    command("ponder");
    command("say IDoKnowAnEasyIllusionCantripICanTeachYou...");
    command("say InTradeForASpecialHerb...");
    command("say BringMeAVallenwoodBlossomAndI'llTeachItToYou.");
    return "";
}

void
give_it_back(object ob, object from)
{
    string what,
    who;
    what = L(ob->query_short());
    who = from->query_real_name();
    command("emote squints closely at the " + what + ".");
    command("say HmmCouldUseBellsAndWhistlesAndStuff.");
    command("say HereFriendTakeItBack.");
    command("give " + what + " to " + who);
}

void
return_give_blossom(object ob, object from)
{

    string who,
    what;
    who = from->query_real_name();
    what = ob->short();


    if(SOHM_MANAGER->query_scribed_spell(this_player(),"riyitchikohk"))
    {
        command("say AnotherVallenwoodBlossom!");
        command("emote carefully places " +what+ " in a retort of green " +
          "bubbling liquid, where it dissolves immediately.");
        ob->remove_object();
        command("eyebrow");
        return;
    }

	
    command("beam");
    command("say AVallenwoodBlossomJustAsIAsked!");
    command("emote carefully places " +what+ " in a retort of green " +
       "bubbling liquid, where it dissolves immediately.");
    ob->remove_object();
    command("say OkNowLetMeShowYouThatCantrip.");
    command("emote demonstrates how to cast a simple cantrip that fools " +
       "shopkeepers in to believing an item is cursed.");
    from->catch_msg("You quickly scribe down in your spellbook the cantrip.\n");
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"riyitchikohk");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if(ob->id("_sohm_vallenwood_blossom"))
    {
	set_alarm(1.0, 0.0, &return_give_blossom(ob, from));
	return;
    }

    set_alarm(1.0, 0.0, &give_it_back(ob, from));
    return;
}