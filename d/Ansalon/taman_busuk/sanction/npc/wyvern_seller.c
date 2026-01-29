#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include <language.h>
#include "/d/Ansalon/common/defs.h"


inherit AM_FILE
inherit "/d/Ansalon/common/cheater";

#define DA_WYVERN "/d/Ansalon/guild/dragonarmy/dragons/wyvern"
#define ONE_PLAT -1728

void
create_krynn_monster()
{
    seteuid(getuid());

    set_name("human");
    add_name(({"trainer","seller"}));
    set_race_name("human");
    set_adj("narrow-nosed");
    add_adj("squinty-eyed");
    set_gender(G_MALE);
    set_short("narrow-nosed squinty-eyed human");
    set_long("This human trains wyverns for transport.  "+
        "For a fee you can purchase one to take you all over the "+
        "realms.\n");
    set_stats(({80,70,75,55,55,60}));
    set_skill(SS_DEFENCE, 60);
    set_skill(SS_AWARENESS, 60);
    set_skill(SS_UNARM_COMBAT, 60);
    set_all_hitloc_unarmed(10);
    set_act_time(15);
    add_act("say Wyvern for sale, you need?");
    add_act("emote peers around suspiciously.");
    add_act("say Hey little boy, need a ride?");
    add_act("say Hey little girl, need a ride?");
    add_act("say Wyvern aren't so bad, once you get to know them.");
    add_act("say You ever got the business end of a wyvern tail?");

    add_ask(({"wyvern","steed","price","fee"}),
      "A small wyvern costs you 3 platinum, while a large one costs you 5 platinum.\n");

    add_prop(LIVE_I_NEVERKNOWN, 1);
}

void
init_living()
{
    ::init_living();
    ADA("buy");
}


buy(str)
{
    object wyvern,who;
    int price = ONE_PLAT * 3;
    string type = "small";

    if (!TP->query_dragonarmy_occ_member() &&
        !TP->query_wiz_level()) {
            NF("Only Dragonarmy members can purchase wyvern.\n");
            return 0;
    }


    if (!TP->query_dragonarmy_promotions() &&
        !TP->query_wiz_level()) {
        NF("Only Soldiers and above can purchase wyverns.\n");
        return 0;
}
    if (!strlen(str) || !str) {
        NF("What do you want, to buy a small wyvern or buy a large wyvern?\n");
        return 0;
    }

    if((str != "small wyvern") &&
       (str != "a small wyvern") &&
       (str != "large wyvern") &&
       (str != "a large wyvern") &&
       (str != "big wyvern") &&
       (str != "a big wyvern")) {
        NF("What do you want, to buy a small wyvern or buy a large wyvern?\n");
        return 0;
    }

    if (check_cheater(TP, TO))
    	return 1;

    if((str == "large wyvern") ||
       (str == "a large wyvern") ||
       (str == "big wyvern") ||
       (str == "a big wyvern")) {
           price = ONE_PLAT*5;
           type = "large";
    }
       

    if (!MONEY_ADD(TP, price)) {
        NF("You cannot pay the price.\n");
    	return 0;
    }

    write("The narrow-nosed human suddenly gives a sharp whistle, summoning "+
        "one of the wyvern circling overhead to your side!\n");
    say("The "+TO->short()+" suddenly gives a sharp whistle, signaling "+
        "one of the wyvern circling overhead to land!\n");

    wyvern = clone_object(DA_WYVERN);
    
    if (type == "large") {
        wyvern->set_wyvern_size("large");
    }

    wyvern->set_summoner(TP);
    tell_room(E(TO),capitalize(LANG_ADDART(wyvern->short()))+" arrives.\n", TO);
    wyvern->move(E(TO));
    return 1;
}
