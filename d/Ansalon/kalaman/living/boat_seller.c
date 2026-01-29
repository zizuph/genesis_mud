#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include "/d/Ansalon/common/defs.h"


inherit AM_FILE
inherit "/d/Ansalon/common/cheater";

#define SHIP_DIR "/d/Ansalon/goodlund/bloodsea/obj/"


void
create_krynn_monster()
{
    set_name("merchant");
    set_race_name("gnome");
    set_adj("distraught");
    set_short("distraught gnome merchant");
    set_long("This short chubby gnome happens to be in charge of the " +
             "dry docks of Kalaman. Once he owned a range of ships for sale to " +
             "both experienced and would-be captains, but now with the war " +
             "on the steps of Kalaman his shipwrights have left him to safer " +
             "locations.\n");
    set_stats(({70,170,75,155,55,60}));
    set_skill(SS_DEFENCE, 60);
    set_skill(SS_AWARENESS, 60);
    set_skill(SS_UNARM_COMBAT, 60);
    set_all_hitloc_unarmed(10);
    set_act_time(9);

    add_act("say ThisWarWillRuinMe!");
    add_act("say AllMyShipwrightsGone!FledToPalanthas!");
    add_act("emote pulls his hair in frustration.");

/*
    add_act("shout ShipsOfAllSizesForSaleToBothRichAndPoor...");
    add_act("say I'veGotShipsOfVaryingSizeNamelyFishingBoatsForFewCrewToThe" +
            "MammothWarshipsForTheWouldBeConquerersWhoNeedToShipArmies...");
    add_act("say TheShipsAreOfHumanMakeSoOfQuiteSimpleDesignNoBellsOrWhistles..");
    add_act("say SailsAreSoPrimitiveButOnceTheGnomishSteamPoweredShipsAre" +
            "OperatingAsTheirSchematicsDetailIWillBeRich...");

    set_default_answer("The gnome looks at you as if you were and simpleton, " +
        "then smiles and says very slowly: I.. HAVE.. FOR.. SALE.. FISHING " +
        "BOATS... SAILING SHIPS.. CORSAIR SHIPS.. AND WARSHIPS... YouCanBuy" +
        "ThemIfYouWant..\n");

    add_ask(({"ship","ships","ships for sale","boat","warship",
              "corsair ship","fishing boat","sailing ship","corsair ship"}),
        VBFC_ME("ship_types"));
*/

    set_default_answer("The gnome is too distraught to answer any of your " +
        "questions.\n");

    add_prop(LIVE_I_NEVERKNOWN, 1);

    add_prop(OBJ_M_NO_ATTACK,"As you prepare to attack the weathly gnome merchant, " +
        "you notice a number of gnomish inventions hanging on his body... mini-" +
        "steam engines! Knowing how explosive those devices are, you reconsider " +
        "attacking this particular gnome.\n");
}

/*

void
ship_two()
{
    command("say IAlsoHaveThePopularSailingShips...");
    command("say ...ThatAreRoomierAllowingForLargerGroupsToSetSail...");
    command("say ...AndCanBeSailedByALaySailor...");
    command("say ...SellingForTheBargainOf50Gold...");
    command("emote boggles at the very concept.\n");
}

void
ship_three()
{
    command("say ...ThenThereIsTheImpressiveCorsairShip...");
    command("say ...BuiltOnTheIsleOfSaifhumItIsBiggerAnd..");
    command("say ...BuiltForThoseWhoCanTrulySailAShip...");
    command("say ...GoingForAStealAt100GoldCoinsOnly...");
    command("emote puffs with exhaustion.\n");
}

void
ship_four()
{
    command("say AndFinallyThereIsTheWarship...");
    command("wink know");
    command("say TheySayBiggerIsBetterAndTheyWereNotWrongHere...");
    command("say TheseBeautiesCanCarryAnArmyAcrossTheSevenSeas...");
    command("say ..HoweverOnlyAMasterMarinerCanHandleSuchAShip...");
    command("say ..ButItsPriceIsAlmostPiracyGoingFor400Gold...");
    command("emote mutters something about bells and whistles.\n");
}

string
ship_types()
{
    command("say IHaveInStockFourTypesOfShips...");
    command("say ...AtTheBottomOfTheRangeIsTheBasicFishingBoat...");
    command("say ...WhichIsGoodForTheIndividualOrSmallParty...");
    command("say ...OnlyRequiringBasicSailingSkills...");
    command("say ...AndCostsAPaultry30GoldCoins...");
    command("emote takes a deep breath of air.\n");

    set_alarm(3.0, 0.0, "ship_two");
    set_alarm(7.0, 0.0, "ship_three");
    set_alarm(11.0, 0.0, "ship_four");

    return "";

}



void
init_living()
{
    ::init_living();
    ADA("buy");
}


buy(str)
{
    object ship, boat_in, who;

    if (check_cheater(TP, TO))
        return 1;

    if (str == "fishing boat")
    {
        NF("The gnome says: You cannot afford a fishing boat.\n");
        if(!MONEY_ADD(TP, -4320))
	    return 0;

        write("You pay the gnome, who tucks the money into a big pouch. He then gestures towards " +
              "the dry docks to the southeast...\n");
        say(QCTNAME(TP) + " pays the gnome some money. The gnome gestures frantically towards " +
              "the dry docks to the southeast...\n");

        who = TP;
        ship = clone_object(SHIP_DIR + "fishing_boat");
        ship->move(environment(who));
        ship->config_boat_inside();
        boat_in = ship->query_boat_in();
        boat_in->set_owner(who);

        return 1;
     }

    if (str == "sailing ship")
    {
        NF("The gnome says: You cannot afford a sailing ship.\n");
        if(!MONEY_ADD(TP, -7200))
	    return 0;

        write("You pay the gnome, who tucks the money into a big pouch. He then gestures towards " +
              "the dry dock to the southeast...\n");
        say(QCTNAME(TP) + " pays the gnome some money. The gnome gestures frantically towards " +
              "the dry dock to the southeast...\n");

        who = TP;
        ship = clone_object(SHIP_DIR + "ship2");
        ship->move(environment(who));
        ship->config_boat_inside();
        boat_in = ship->query_boat_in();
        boat_in->set_owner(who);

        return 1;
     }

    if (str == "corsair ship")
    {
        NF("The gnome says: You cannot afford a corsair sloop-of-war.\n");
        if(!MONEY_ADD(TP, -14400))
	    return 0;

        write("You pay the gnome, who tucks the money into a big pouch. He then gestures towards " +
              "the dry dock to the southeast...\n");
        say(QCTNAME(TP) + " pays the gnome some money. The gnome gestures frantically towards " +
              "the dry dock to the southeast...\n");

        who = TP;
        ship = clone_object(SHIP_DIR + "corsair2");
        ship->move(environment(who));
        ship->config_boat_inside();
        boat_in = ship->query_boat_in();
        boat_in->set_owner(who);

        return 1;
     }

    if (str == "warship")
    {
        NF("The gnome says: You cannot afford a warship.\n");
        if(!MONEY_ADD(TP, -57600))
	    return 0;

        write("You pay the gnome, who tucks the money into a big pouch. He then gestures towards " +
              "the dry docks to the southeast...\n");
        say(QCTNAME(TP) + " pays the gnome some money. The gnome gestures frantically towards " +
              "the dry dock to the southeast...\n");

        who = TP;
        ship = clone_object(SHIP_DIR + "warship2");
        ship->move(environment(who));
        ship->config_boat_inside();
        boat_in = ship->query_boat_in();
        boat_in->set_owner(who);

        return 1;
     }


    NF("What did you say you wanted to buy? A fishing boat? Sailing ship? Corsair ship? " +
       "Or warship? For information on them you may want to ask the gnome about them.\n");
	return 0; 


}

*/