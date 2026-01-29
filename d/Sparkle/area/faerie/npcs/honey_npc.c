/*
 * Honey quest NPC 
 * By Finwe, April 2005
 *
 * Fixed to destroy unneeded buckets to avoid getting overburdened
 * Lavellan 20100609
 *
 */

inherit "/std/monster";

#include "defs.h"
#include "../quests/qbits.h"
#include <composite.h>
#include <formulas.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#define QUEST_NAME_PROP "_honey_quest"

void
create_monster()
{
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);
    set_race_name("elf");

    set_name("saviro");
    set_adj("noble");
    set_adj("somber");
    set_short("happy busy elf");
    set_long("This is the honey collector of Green Oaks. She has smooth " +
    "skin and cheerful eyes. She looks like she loves sweet things, " +
    "especially honey.\n");

    set_skill(SS_DEFENCE,       100);
    set_skill(SS_UNARM_COMBAT,  100);
    set_skill(SS_AWARENESS,     100);
    set_skill(SS_PARRY,         100);
    add_prop(OBJ_M_NO_ATTACK, 1);   // non-killable

    set_chat_time(40+random(10));

    set_gender(G_FEMALE);

    set_chat_time(60+random(60));
    add_chat("If you are looking for something to do, ask me.");
    add_chat("I'm running low on honey.");
    add_chat("Honeybees are wonderful creatures.");
    add_chat("What can I help you with?");
    add_chat("Elves are marvelous creatures, I am sure you will agree.");
    add_chat("I love honey.");
    
    set_act_time(60+random(60));
    add_act("emote watches you.");
    add_act("emote paces the floor quietly.");
    add_act("emote smiles happily.");
    add_act("emote greets a visitor.");

    add_ask(({"honey", "honeycomb", "beehive", "bees", "quest", "help", "task"}), 
        VBFC_ME("ask_honey"));


}


void
add_introduced(string str)
{
    if (!interactive(TP) || TP->query_met(query_name()))
        return;

    command("introduce me to " + TP->query_real_name() + "");
    command("say to " + TP->query_real_name() + " Nice to meet ya!");
    command("shake " + TP->query_real_name() );
}

void
react_intro(object tp)
{
    if (!present(tp, ENV(TO)))
    {
        command("shrug");
        return;
    }
    /* we can be called in response to intro or out of init,
     * so check to be sure we don't intro twice
     */
    command("introduce me to "+tp->query_real_name());
    command("say Welcome to Faerie!");
    return;
}


string ask_honey()
{
    object bucket;

    if(TP->test_bit(DOMAIN, QUEST_GROUP, HONEY_QUEST_BIT))
    {
	    command("say Thank you for your offer, but you have helped me already.");
	    return "";
    }

    if (TP->query_prop(QUEST_NAME_PROP))
    {
	    command("say Have you found all the honey I need yet?");
	    command("say If you haven't, please try some more. I need fresh honey.");
	    return "";
    }


    command("say I am running low on honey, and haven't had time to go " +
        "get some.");
    command("say I know there are wild honeybees in the mountains, but I " +
        "can't climb up the trees and get the honeycomb.");
    command("say If you would, please fill this bucket on the ground with " +
        "honeycomb and bring it back to me. Thank you!");
    bucket = clone_object(OBJ_DIR+ "honeybucket");
    bucket->move(ENV(TO));
    TP->add_prop(QUEST_NAME_PROP,1);
    return "";

}

void
init_living()
{
    object  tp = TP;

    ::init_living();
}

void 
test_quest(object player, object obj)
{

    if(TP->test_bit(DOMAIN, QUEST_GROUP, HONEY_QUEST_BIT))
    {
	    command("say Thank you for your offer, but you have helped me already.");
       obj->remove_object();
	    return;
    }


// has prop?
    if (TP->query_prop(QUEST_NAME_PROP))
    {
// bucket full?
        if(!obj->query_bucket_full())
        {
            command("say You still need to get some more honeycomb for " +
                "me. The bucket isn't full yet.");
            command("say Bring it back when it's full!");
            command("emote places the bucket on the floor.");
            obj->move(environment(this_object()));
            return;
        }
    }
    
    
    command("grin broadly");
    command("say Ahh, I hope you didn't have too much trouble. Thank you so much!");
    command("say I shall process this honey right away and save it for some of my sweets.");
    player->remove_prop(QUEST_NAME_PROP);
    tell_object(player,"You feel more experienced!\n");
    say(QCTNAME(player) + " was rewarded.\n");
    TP->set_bit(QUEST_GROUP, HONEY_QUEST_BIT);
    TP->add_exp_quest(HONEY_QUEST_EXP);
    obj->remove_object();


}

void
return_object(object obj, object to)
{
    string  obname = OB_NAME(obj);

    if (obj->id("coin"))
        return;

    command("say I do not believe I need this. Thank-you though.");
    obj->move(environment(this_object()));}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    if (!living(from))
	    return;

    if (obj->id("_sparkle_honey_bucket")) 
	    set_alarmv(1.0,0.0,"test_quest",({from, obj}));
    else
    {
	    set_alarmv(1.0,0.0,"return_object",({from, obj}));
	    return;
    }
}
