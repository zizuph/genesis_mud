/* Ashlar, 4 Oct 97
 */

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <cmdparse.h>
#include <money.h>
#include <filter_funs.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/new_pot/guild.h"
#include "npc.h"

inherit "/d/Ansalon/guild/new_pot/obj/living/npc";
#ifdef COMMERCE
inherit "/d/Genesis/lib/commerce";
#endif

void arm_me();

void
create_pot_monster()
{
    if(!IS_CLONE)
	return;

    set_name("erdin");
    set_living_name("erdin");
    set_introduce(1);
    add_name("priest");

    set_race_name("gnome");
    set_adj("short");
    add_adj("dark-cloaked");
    set_long("Not much can be seen about this gnome as he hides himself " +
    "behind a dark cloak.\n");

    add_prop(CONT_I_HEIGHT, 135);
    add_prop(CONT_I_WEIGHT, 35000);

    set_stats(({ 100, 110, 100, 130, 130, 110 }));
    set_hp(query_max_hp());

    set_skill(SS_WEP_CLUB,          70);
    set_skill(SS_DEFENCE,           55);
    set_skill(SS_PARRY,             50);
    set_skill(SS_AWARENESS,         65);
    set_skill(SS_SPELLCRAFT,        65);
    set_skill(SS_ELEMENT_LIFE,      65);
    set_skill(SS_ELEMENT_AIR,       65);
    set_skill(SS_FORM_DIVINATION,   65);
    set_skill(SS_FORM_ENCHANTMENT,  60);
    set_skill(SS_FORM_ABJURATION,   60);

    set_skill(PS_GUILD_LEVEL, 70);
    set_skill(PS_SPELLS, PTELL_ID);

    set_all_hitloc_unarmed(10);

    set_alignment(-800);
    set_knight_prestige(800);

    set_act_time(17);
    add_act("say BeCarefulWithThatBeaker!");
//    add_act("say ManyOfMyStudiesTakeMeToTheRealmOfRituals.");
#ifdef COMMERCE
    add_act("say ResearchingNewIngredientsIsDangerousAndTimeConsumingBut" +
        "EvenSoVeryIntruiging.");
#endif
    add_act("emote studies some device.");

    set_cact_time(5);
    add_cact("say I curse you!");
    add_cact("sneer");
    add_cact("say The hatred of the Dark Queen will follow you to your grave!");

    set_default_answer(QCTNAME(TO) + " looks at you askance.\n");

#ifdef COMMERCE
    add_ask("[new] 'ingredients'",
        "say IKnowALotAboutIngredientsAndMyStudiesAllowsMeToResearchFor" +
        "More.IfYouHaveSomethingYouThinkCouldMakeAnIngredientsPleaseShow" +
        "ItToMeAndIWillSeeWhatICanDo.");
#endif
    add_ask("[dragon] 'scale' / 'scales'",
        "say IKnowSomeThingsAboutDragonScales.DoYouNeedThemForIngredients?ShowMeWhatYouNeedThemFor",
        1);
    add_ask("[for] 'help' / 'hint'",
        "say IfYouNeedHelpWithSomething,ShowItToMe,AndIWillGiveYouWhatAdviceICan.",
        1);
    add_ask("[about] 'rituals' / 'ceremonies'", VBFC_ME("answer_rituals"));
    add_ask("[about] 'ritual' [of] %w", "answer_rituals", 2);

#ifdef COMMERCE
    // Theiwar sells "silver bar"
    add_demanded_commodity("silver", 60, 20, 0.0);
    add_demanded_commodity("diamond", 90, 30, 0.0);
    add_demanded_commodity("elf heart", 10, 10, 0.0);
//    add_demanded_commodity

    add_supplied_commodity("pot_silver_powder", 2, 15, 0.0);
    add_supplied_commodity("pot_diamond_dust", 2, 17, 0.0);
    add_supplied_commodity("pot_elven_blood", 2, 10, 0.0);
    
    add_supply_requirement("pot_silver_powder", ({ "silver", 1 }));
    add_supply_requirement("pot_diamond_dust", ({ "diamond", 1 }));
    add_supply_requirement("pot_elven_blood", ({ "elf heart", 5 }));

    set_commerce_savefile(MASTER);
#endif
}

void
arm_me()
{
    setuid();
    seteuid(getuid());
    
    clone_object(NARM + "black_chain_shirt")->move(this_object(), 1);
    
    command("wear all");
    
    ::arm_me();
}

varargs string
answer_rituals(object asker, string arg, int round = 0)
{
    /* ritual of water */
/*    ({ "soul", "water", "fire", }))*/

    if (!arg)
    {
        switch (round)
        {
            case 0:
                set_busy(B_SPEAKING);
                command("say ManyOfMyStudiesTakeMeToTheRealmOfRituals.");
                break;
            case 1:
                command("say ThePowerOfTheWordIsOneOfTheGreatestInThe" +
                    "WholeWorld.");
                break;
            case 2:
                command("say ThereIsNooneWhoKnowsOfALimitToThatPower,Much" +
                    "LessIfThereIsOneInTheFirstPlace.");
                break;
            case 3:
                unset_busy(B_SPEAKING);
                command("say YouCanAskMeMoreByAskingMeRitualOfWater,Ritual" +
                    "ofFire,RitualOfRefiningAndSoOn.");
        }

        if (round < 3)
            set_alarm(3.0, 0.0, &answer_rituals(asker, arg, round + 1));
        return "";
    }

    switch (arg)
    {
        case "water":
            switch (round)
            {
                case 0:
                    set_busy(B_SPEAKING);
                    command("say TheMostSimpleRequiresAContainerOf" +
                        "WaterAndAPhialToFillItWith.");
                    break;
                case 1:
                    command("say PlaceThoseComponentsOnAnAltarAnd" +
                        "BeginAChantToOurGodessWhereinSheWillHearYou.");
                    break;
                case 2:
                    unset_busy(B_SPEAKING);
                    command("say AFaithfulHeartAndAFavourableStanding" +
                        "WillHaveAPhialOfHolyWaterStandingOnTheAltar.");
                    break;
            }

            if (round < 2)
                set_alarm(3.0, 0.0, &answer_rituals(asker, arg, round + 1));
            break;
        case "fire":
            switch (round)
            {
                case 0:
                    set_busy(B_SPEAKING);
                    command("say TheRitualOfFireIsAMostPowerfulOne.");
                    break;
                case 1:
                    command("say ItRequiresAClub,Fireweed,AFreshHeart" +
                        "AndADiamond.");
                    break;
                case 2:
                    command("say TheClubNotHavingAnyMagicalProperties" +
                        "ItWillGetMostPowerful");
                    command("say OnesThroughThisRitual.");
                    break;
                case 3:
                    command("say MerelyPlaceThoseOnAnAltarAndBeginA" +
                        "ChantToOurGodessAlong");
                    command("say WithAnotherPriestWhereinSheWillHearYou.");
                    break;
                case 4:
                    unset_busy(B_SPEAKING);
                    command("say AFaithfulHeartAndAFavourableStanding" +
                        "WillHaveAMagicalClub");
                    command("say SittingOnTheAltar.");
                    break;
            }

            if (round < 4)
                set_alarm(3.0, 0.0, &answer_rituals(asker, arg, round + 1));
            break;

       case "refining":
            switch (round)
            {
                case 0:
                    set_busy(B_SPEAKING);
                    command("say TheRitualOfRefiningIsTheMostBasicRitual.");
                    break;
                case 1:
                    command("say ItRequiresAnySortOfLeftoverCutWithYourSacrificial"
                        + "Knife.");
                    break;
                case 2:
                    command("say PlaceTheLeftoverOnTheAltarAndBeginAChantToOur"
                        +"GoddessWhereSheWillHearYou.");
                    break;
                case 3:
                    unset_busy(B_SPEAKING);
                    command("say AFaithfulHeartAndAFavourableStandingWill"
                        + "LeaveSomeRefinedPowderLayingOnTheAltar.");
                    break;
            }

            if (round < 3)
                set_alarm(3.0, 0.0, &answer_rituals(asker, arg, round + 1));
            break;

        default:
            command("say UnfortunatelyIKnowNotOfAnySuchRitualButIWill" +
                "ResearchThat.");
            break;
    }

    return "";
}
    
    

#ifdef COMMERCE
public void
hook_commerce_amount_update(string commod, int amount)
{
    object *oblist;

    DEBUG("Erdin produced " + amount + " of " + commod);
    
    if (!exist_supplied_commodity(commod))
        return;

    amount = query_commodity_amount(commod);
    add_commodity_amount(commod, -amount);
    
    if (E(TO) && amount)
    {
        switch (commod)
        {
            case "pot_silver_powder":
                pot_silver_powder(commod, amount);
                break;
            case "pot_diamond_dust":
                pot_diamond_dust(commod, amount);
                break;
            case "pot_elven_blood":
                pot_elven_blood(commod, amount);
                break;
        }
    }
}

varargs void
pot_silver_powder(string commod, int amount, int round = 0)
{
    object *oblist;

    set_busy(B_SPEAKING);
    
    switch (round)
    {
        case 0:
            command("emote places a piece of silver in a " +
                "small steel bowl upon the workbench.");
            command("emote reaches for a small phial and unplugs it.");
            break;
        case 1:
            tell_room(environment(TO), "Leaning as far from the " +
                "bowl as possible, " + QTNAME(TO) + " tips the " +
                "phial over the bowl and thick black liquid drips " +
                "down while " + HE(TO) + " mumbles a prayer to the " +
                "Dark Queen.\n");
            break;
        case 2:
            tell_room(environment(TO), "There is a slow cracking " +
                "noise and then a large bang. A cloud of black " +
                "smoke rises from the bowl.\n");
            break;
        case 3:
            tell_room(environment(TO), QCTNAME(TO) + " waves away " +
                "the smoke and then empties the bowl into one of " +
                HIS(TO) + "pouches.\n");

            
            oblist = clone_commodity(MASTER_OB(find_commodity(commod)),
                amount);
            map(oblist, &->move(TO, 1));
            
            unset_busy(B_SPEAKING);
                
            break;
    }

    if (round < 3)
        set_alarm(5.0, 0.0, &pot_silver_powder(commod, amount, round + 1));
}

void
show_ingredient(object pl, object ob, int round)
{
    if (environment(pl) != environment(this_object()))
    {
        unset_busy(B_SPEAKING);

        if (environment(ob) == TO)
        {
            command("emote shrugs.");
            command("drop " + OB_NAME(ob));
        }
        
        return;
    }
    
    switch(round)
    {
        case 0:
            set_busy(B_SPEAKING);
            say(" eyes the " + ob->short() + ".\n");
            break;
        case 1:
            command("say MayI?");
            if (environment(ob) != pl)
            {
                command("say NowWhereDidThat" + capitalize(ob->query_name()) +
                    "Go?");
                return;
            }

            command("emote takes the " + ob->short() + ".");
            command("emote studies the " + ob->short() + " intently.");
            break;
        case 2:
            if (is_ingredient(ob))
            {
#endif
                

void
ded_hint(object pl, int round)
{
    if (environment(pl) != environment(this_object()))
    {
        unset_busy(B_SPEAKING);
        return;
    }

    switch(round)
    {
        case 0:
            set_busy(B_SPEAKING);
            say(" peers the scroll.\n");
            break;

        case 1:
            command("say AhYes,It'sThatOne.TheIngredientsCanBeVery" +
            "HardToFind.EspeciallyTheScalesTheDragonsAreReluctantTo" +
            "GiveUsScalesEvenWhenWeTellThemIt'sForResearch.TheyAre" +
            "VeryTouchy.");
            command("pout");
            break;

        case 2:
            command("say LuckilyThereIsAnotherWay.AllThisOldLoreIs" +
            "WellAndGood,ButManyThingsAreRedundantAndUnnecessary." +
            "ForExampleDoYouKnowThatTheHealingSpellOriginally" +
            "RequiredAPinchOfBlackSand,ABucketOfWaterAndTwoCatpaws?");
            break;

        case 3:
            command("say No,NotManyKnowThat.Still,WeSimplifiedThat" +
            "One,AndOthersAswell.TheWorkWeDoHereIsOftenUnderestimated." +
            "FewRealiseThatWithoutOurResearchHereTheyWouldHaveTo" +
            "CarryAroundSeveralPackmulesWithIngredientsForTheirSpells.");
            break;

        case 4:
            command("say ButToTheCaseInHand.ThisRitualWorksJustAsWell" +
            "WithJustAMugOfTheDrinkCalled'BlackDragonbrew'WhichIsSold" +
            "AtAnInnHereInNeraka.ThatDrinkContainsAllTheActive" +
            "ComponentsRequiredForTheRitual.");
            break;

        case 5:
            command("smile . " + pl->query_real_name());
            unset_busy(B_SPEAKING);
            break;
    }

    if (round < 5)
        set_alarm(10.0,0.0, &ded_hint(pl, round+1));
}


/*
 * This function is called when the npc is shown something.
 */
void
show_hook(object ob)
{
    if (ob->id("scroll_of_dedication") && !query_busy(B_SPEAKING))
    {
        ded_hint(this_player(), 0);
        return;
    }

#ifdef 0
    if (objectp(ob) && !query_busy(B_SPEAKING))
    {
        show_ingredient(this_player(), ob, 0);
        return;
    }
#endif
}
