inherit "/d/Genesis/ship/captain";
inherit "/d/Krynn/std/act/actions";
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
    set_title("the Coast Skipper");
    set_race_name("elf");
    add_adj("thin");
    set_adj("bouncy");
    set_stats(({ 80, 80, 100, 60, 60, 90 }));
    set_skill(SS_SWIM, 100);
    set_skill(SS_LOC_SENSE,100);
    set_skill(SS_UNARM_COMBAT,80);
    set_skill(SS_DEFENCE,50);
    set_skill(SS_AWARENESS, 40);
    
    set_chat_time(9);

    add_chat("My minotaurs work hard.");
    add_chat("How nice it is travelling by sea.");
    add_chat("I really like Palanthas. As soon as I have earned enough " +
        "money I'll retire there.");
    add_chat("The proprietor of the Inn in Palanthas is a good friend of " +
        "mine. He's always having problems though.");
    add_chat("Hmmph. I think we're behind schedule again.");
    add_chat("How nice it is travelling by sea.");
    add_chat("We better watch out for Ergothian Pirates.");
    add_chat("I wish my ship was as fine as those made by Cirdan the Shipwright.");

    add_ask(({"palanthas","inn","proprietor"}),
        "say I know Leiden since we both were kids! Just go and ask him for " +
        "a job.",1);
    
    set_cchat_time(11);
    add_cchat("Stop it, you pestering dog!");
    add_cchat("Right, you'll pay for that!");
    add_cchat("Come on! I'll beat the living daylights out of you!");
    add_cchat("Right! I'm really gonna stump you this time!");
    add_cchat("Give it to me, big-nose!");
    add_cchat("I'm gonna smack you so hard....");

    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(OBJ_M_NO_ATTACK,
        "You feel this man is under strong protection.\n");

    set_ticket(TICKET);
    set_price(PRICE);
}

string
query_presentation()
{
    return "Captain " + ::query_presentation();
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
 *
 * Cotillion fixed this
 */
int
buy(string str)
{

    object player;
    string my_army, army_holding;

    player = this_player();

    my_army = ARMYMASTER->army_of_player(player);
    army_holding = ARMYMASTER->army_in_area(WAR_AREA_NEWPORT);

    if (find_object(DECK) == environment(player) )
    {
        notify_fail("You are already underway. " +
            "You don't need another ticket.\n");
        return 0;
    }
     
     
    if (player->query_average_stat() < 11)
    {
        notify_fail("You don't need to buy any ticket. " +
            "Young travel for free.\n");
        return 0;
    }

    if (ARMYMASTER->query_peace())
    {
        set_price(PRICE);
        return ::buy(str);
    }

    if (army_holding == KNIGHT_ARMY)
    {
        if (my_army == KNIGHT_ARMY)
        {
            command("say A Pleasure to Serve you Sir Knight");
            set_price(PRICE / 3);
            return ::buy(str);
        }
        
        if (wildmatch("*Dragon Army", my_army))
        {
            if (find_object(PALANTHAS) == environment(player) )
            {
                
                command("say I have been ordered by the " + army_holding +
                    " not to let Dragonarmy members board here. I will "+
                    "let you board anyway but it will cost you extra.");
                command("emote mumbles something about the risk of smuggling"
                    + " illegal passengers...");
                set_price(PRICE * 100);
                return ::buy(str);
            }

            if (find_object(NEWPORTS) == environment(player))
            {
                command("say I have strict orders from the " + army_holding +
                    " not to let any Dragonarmy member board here.");
                return 1;
            }
        }
    }

    /* One of the Dragonarmies hold Newports
     *
     * Knights need to pay * 100 in Palanthas, and can't board in Newports
     * All others pay * 10 
     */
    if (wildmatch("*Dragon Army", army_holding))
    {
        if (my_army == army_holding)
        {
            set_price(PRICE / 5);
            return ::buy(str);
        }
        
        if (my_army != KNIGHT_ARMY)
        {
            set_price(PRICE * 10);
            return ::buy(str);
        }
        
        if (find_object(PALANTHAS) == environment(player) )
        {
            command("say I have been ordered by the " + army_holding +
                " not to let Knights board here. I will let you " +
                "board anyway but it will cost you extra.");
            command("emote mumbles something about the risk of smuggling"
                + " illegal passengers...");
            set_price(PRICE * 100);
            return ::buy(str);
        }
        
        
        if (find_object(NEWPORTS) == environment(player))
        {
            command("say I have strict orders from the " + army_holding +
                " not to let Solamnian Knights board here.");
            return 1;
        }
    }

    set_price(PRICE);
    return ::buy(str);
}

/*
 * Function name: react_introduce
 * Description:   React to an introduction. The default is to introduce
 *                back at the person who introduced/was introduced.
 *                Redefine this function if you want your own introduction.
 * Arguments:     who introduced to me. Can be 0 if there was no one specific.
 */
public varargs void
react_introduce(mixed who = 0)
{
    object ob;                                                                 
    who = lower_case(who);
    
    if (!(ob = find_player(who)))
        return;
    
    this_object()->action_introduce(ob);
}

/*
 * Function name: add_introduced
 * Description:   Called when someone introduced to the npc.
 * Arguments:     who was introduced. this_player() did the
 *                introduction. not necessarily the same as
 *                who.
 */
public void
add_introduced(string who)
{
    if (!query_attack())
        set_alarm(rnd() * 2.0, 0.0, &react_introduce(who));
}

