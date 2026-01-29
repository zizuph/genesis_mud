inherit "/d/Genesis/ship/captain";
#include "local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/sys/filter_funs.h"
#include "/d/Krynn/common/defs.h"
#include <filter_funs.h>

#define ENV(xxx) environment(xxx)

int intro = 0;

void
create_monster()
{
    set_name("hans");
    add_name("captain");
    set_living_name("hans");
    set_race_name("elf");
    add_adj("thin");
    set_adj("bouncy");
    set_stats(({ 80, 80, 100, 60, 60, 90 }));
    set_skill(SS_SWIM, 100);
    set_skill(SS_LOC_SENSE,100);
    set_skill(SS_UNARM_COMBAT,80);
    set_skill(SS_DEFENCE,50);
    heal_hp(10000);
    set_chat_time(9);

    add_chat("My minotaurs work hard.");
    add_chat("How nice it is travelling by sea.");
    add_chat("I really like Palanthas. As soon as I have earned enough money I'll retire there.");
    add_chat("The proprietor of the Inn in Palanthas is a good friend of mine. He's always having problems though.");
    add_chat("Hmmph. I think we're behind schedule again.");
    add_chat("How nice it is travelling by sea.");
    add_chat("We better watch out for Ergothian Pirates.");
    add_chat("I wish my ship was as fine as those made by Cirdan the Shipwright.");

    add_ask(({"palanthas","inn","proprietor"}),"say I know Leiden since we both were kids! Just go and ask him for a job.",1);

    set_cchat_time(11);
    add_cchat("Stop it, you pestering dog!");
    add_cchat("Right, you'll pay for that!");
    add_cchat("Come on! I'll beat the living daylights out of you!");
    add_cchat("Right! I'm really gonna stump you this time!");
    add_cchat("Give it to me, big-nose!");
    add_cchat("I'm gonna smack you so hard....");

    trig_new("%w 'introduces' %s", "react_introduce");

    add_prop(OBJ_M_NO_ATTACK,
        "You feel this man is under strong protection.\n");

    set_ticket(TICKET);

    set_price(PRICE);

}

string
query_my_title()
{
    return "the Coast Skipper";
}

/*
 * Feature added by Mozart February 2000
 *
 * If the Free People hold Newports:
 *  All pay the standard price defined in local.h
 *
 * If a Dragonarmy hold Newports:
 *  Knights pay 100 times more in Palanthas and are not allowed to buy a ticket
 *  in Newports, other Dragonarmies and Free people pay 10 times more than the
 *  normal price
 *
 * If Knights hold Newports:
 *  Dragonarmy members pay 100 times more in Palanthas and cannot buy a ticket
 *  in Newports, Free People pay normal fare.
 */
int
buy(string str)
{

    object player, armymaster;
    string my_army, army_holding;
    int i;




    armymaster = find_object("/d/Krynn/common/warfare/armymaster");

    player = this_player();

    my_army = armymaster->army_of_player(player);

    army_holding = armymaster->army_in_area("Newports Area");

    // Free People are not holding Newports and not my army either
    if (army_holding == "Free People")
    {
        command("say Have a great day!");
    }
    else if (my_army != army_holding)
    {
        // Trying to buy a ticket at the Palanthas pier
        if ( find_object(PALANTHAS) == environment(player) )
        {
            if (my_army == "Knights")
            {
            command("say I have been ordered by the " + army_holding +
                " not to let Knights board here. I will let you " +
                "board anyway but it will cost you extra.");
            command("emote mumbles something about the risk of smuggling"
                    + " illegal passengers...");
            set_price(PRICE * 100);
            }
            else if(army_holding == "Knights")
            {
                if(my_army != "Free People")
                {
                command("say I have been ordered by the " + army_holding +
                    " not to let Dragonarmy members board here. I will "+
                    "let you board anyway but it will cost you extra.");
                command("emote mumbles something about the risk of smuggling"
                    + " illegal passengers...");
                set_price(PRICE * 100);
                }
            }
            else
            {
            command("say I have been ordered by the " + army_holding +
                " not to let others board here. I will "+
                "let you board anyway but it will cost you extra.");
            set_price(PRICE * 10);
            }
        }
        // Trying to buy a ticket at the Newports pier
        else if ( find_object(NEWPORTS) == environment(player) )
        {

            if (my_army == "Knights")
            {
            command("say I have orders from the " + army_holding +
                   " not to let Solamnian Knights board here.");
            return 1;
            }
            else if(army_holding == "Knights")
            {
            if(my_army != "Free People")
            {
                command("say I have orders from the " + army_holding +
                    " not to let any Dragonarmy member board here.");
                return 1;
            }
            }
            else
            {
            command("say I have been ordered by the " + army_holding +
                " not to let others board here. I will "+
                "let you board anyway but it will cost you extra.");
            command("emote mumbles something about the risk of smuggling"
                    + " illegal passengers...");
            set_price(PRICE * 10);
            }
        }
        // Trying to buy a ticket on the ship
        else
        {
            command("say I don't sell tickets on the ship.");
            return 1;
        }

    }
    else
        command("say Pleased to serve you!");

    if (player->query_average_stat() < 11)
    {
        notify_fail("You don't need to buy any ticket. " +
            "Young travel for free.\n");
        return 0;
    }

    return ::buy(str);
}

void
react_introduce(string person,string who)
{
    if (!intro)
      intro = set_alarm(4.0,0.0,"introduce_me");
}

void
introduce_me()
{
    tell_room(E(TO),QCTNAME(TO) + " introduces himself as:\n" +
          "Captain Hans " + query_my_title() + ", male elf.\n");
    FILTER_LIVE(all_inventory(E(TO)))->add_introduced("hans");
    intro = 0;
}

