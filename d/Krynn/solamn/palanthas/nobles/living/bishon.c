#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <language.h>
#include <money.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit M_FILE

/*
    Krynn bits 4:2 through to 4:5 are used for the
    four quests given out by Bison. See 
    /d/Krynn/open/BITS for details.
 */

#define QUEST_ONE        2
#define QUEST_TWO        3
#define QUEST_THREE      4
#define QUEST_FOUR       5

#define QUEST_ONE_REWARD        3500
#define QUEST_TWO_REWARD        3000
#define QUEST_THREE_REWARD      5000
#define QUEST_FOUR_REWARD       10000

#define QUEST_PROP_ONE          "_player_received_quest_one"
#define QUEST_PROP_TWO          "_player_received_quest_two"
#define QUEST_PROP_THREE        "_player_received_quest_three"
#define QUEST_PROP_FOUR         "_player_received_quest_four"
#define QUEST_RETURNED_RECIPE   "_player_received_quest_four_retrieved_recipe"
#define QUEST_TASKED_POTION     "_player_received_quest_four_make_potion"

#define CHECK_QUEST(player, quest_num)  player->test_bit("krynn", 4, quest_num)
#define QUEST_GIVEN(player, quest_prop) player->query_prop(quest_prop)

#define FISHING_MANAGER      ("/d/Krynn/clubs/fishing/fishing_manager")

#define SHARK_FIN_NUM           "_bison_shark_fins"
#define PLATTER "/d/Krynn/solamn/palanthas/nobles/obj/bishon_platter"
#define NOODLE  "/d/Krynn/solamn/palanthas/nobles/obj/bishon_noodles"
#define SOUP    "/d/Krynn/solamn/palanthas/nobles/obj/bishon_soup"

void
create_krynn_monster()
{
    if (!IS_CLONE)
       return;
   
    set_name("bishon");
    set_title("Grilmer, the Seafood Culinarian");
    set_short("burly moustachioed human");
    set_race_name("human");
    set_long("This is the owner of Bishon's Crabber, one of the " +
       "busiest seafood restaurants in the land. A big burly man " +
       "with a grand walrus moustache, he seems a bit preoccupied " +
       "harrassing his kitchen chef about low ingredient stocks.\n");

    add_prop(OBJ_M_NO_ATTACK,"You try and approach him to attack, " +
        "but there always seems to be clientele between you, blocking " +
        "your way!\n");
   
    set_act_time(20);
    add_act("emote shouts into the kitchen: Have no orders of Balifor " +
       "bonito come in yet?");
    add_act("emote serves a bowl of steaming shark fin soup to " +
       "a hungry-looking sailor.");
    add_act("emote gruffly acknowledges the call for service from " +
       "a rotund merchant.");
    add_act("emote takes payment from an elderly noble.");
    add_act("emote serves a plate of raw fish fillets to a young " +
       "dock worker.");
    add_act("emote shouts into the kitchen: Why is it so hard to " +
       "find a fisherman who can bring me giant ink sacs?");

    add_ask(({"quest","task","help"}), VBFC_ME("quest_hint"));
    add_ask(({"stocks","ingredient stocks","low stocks",
       "low ingredient stocks"}),
       "say Aye! My stocks of fresh seafood are running very " +
       "low! Think you can <help> me?", 1);
    add_ask(({"bonito","balifor bonito","Balifor bonito"}),
       "say The Balifor bonito is a unique fish! You'll only " +
       "be able to catch it in the Bay of Balifor!", 1);
    add_ask(({"freshly caught","fresh","fishing","catch"}),
       "say My seafood needs to be freshly caught, so you may " +
       "need to learn how to fish! There is an old salty dog of " +
       "a fisherman on the docks who could probably give you some " +
       "fishing tips and sell you some fishing equipment.", 1);
    add_ask(({"balifor","bay of balifor"}), "say The Bay of Balifor " +
       "is on the other side of the continent of Ansalon, far " +
       "to the southeast. Travelling overland with the current " +
       "war on may be too dangerous... you'd probably be best to " +
       "charter a ship and sail around to Port Balifor.", 1);
    add_ask(({"great white shark", "shark fin", "fin", "white shark",
       "shark" }),
       "say I need fins from the great white shark for my shark fin " +
       "soup. Great whites are too big to catch with a rod... you'll " +
       "need to hunt it down and catch it with a net most likely.", 1);
    add_ask(({"squid","collosal squid","ink sac","sac"}),
       "say The ink from the collosal squid makes an amazing black noodle! " +
       "The collosal squid though is hard to find... and hard to kill. " +
       "A good many South Courrain fisherman have had their ship dragged " +
       "to the bottom by these squids, so don't take them lightly!", 1);
    add_ask(({"south courrain", "south courrain ocean", 
       "south corrain fisherman", "southern courrain ocean"}),
       "say The Southern Courrain Ocean is south of the Bloodsea of Istar " +
       "isles Mithas and Kothas, on " +
       "the other side of the Goodlund Peninsula. Serious deep sea anglers " +
       "fish there... along with the bigger types of sea creatures and " +
       "monsters.", 1);
    add_ask(({"northern wastes", "beach"}),
       "say If you follow the coastline east from Palanthas, you'll pass " +
"the peninsula of the Northern Wastes on your way to Kalaman.", 1);
    add_ask(({"acquaintance"}),
       "say A bit of an adventurer and ruins explorer. He'd stop here " +
       "for a meal when passing through Palanthas. I wouldn't call him " +
       "a close friend, more an infrequent customer.", 1);
    add_ask(({"net", "fishing rod", "bait"}),
       "say Sorry, I can't help you with that. Perhaps seek out a fisherman " +
       "at the Palanthas docks?", 1);
    add_ask(({"wreck"}),
       "say All I have heard is reports of the wreck of my acquaintance's " +
       "ship being sighted on a beach near the Northern Wastes, east of " +
       "Palanthas. It is a remote beach... so you will either need to " +
       "charter a ship or sail there yourself.", 1);
    add_ask(({"sea lion","heart","heart of a sea lion"}),
       "say Sea lions are incredibly rare predatory creatures of the high seas. " +
       "I have heard they like the cold southern waters of the South Courrain " +
       "Ocean.", 1);
    add_ask(({"potion of swimming", "swimming potion", "potion"}),
       "@@ask_potion");
    add_ask(({"recipe", "swimming potion recipe", "recipe for a potion of swimming"}),
       "@@ask_potion");

    set_default_answer("say Sorry, I can't help you with that.", 1);

    trig_new("%w 'introduces' %s","react_to_intro");
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    seteuid(getuid());

    set_stats(({100,100,100,100,100,100}));
    set_hp(10000);
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
quest_hint()
{
    if (!CHECK_QUEST(TP, QUEST_ONE))
    {
        if(QUEST_GIVEN(TP, QUEST_PROP_ONE))
        {
            command("say Like i said, I need a freshly caught " +
                "Balifor bonito. FRESHLY CAUGHT. Think you " +
                "can go fish one up for me? I'll reward you for it.");
            return "";
        }
	command("emote pulls on his walrus moustache thoughtfully.");
        command("say You know you may be able to help me.");
	command("say I was expecting a shipment of a specific fish " +
            "today, but it hasn't come in yet.");
	command("grumble");
        command("say I need a freshly caught Balifor bonito. " +
            "Think you can go fish one up for me?");

        TP->add_prop(QUEST_PROP_ONE, 1);
	return "";
    }
    else if (!CHECK_QUEST(TP, QUEST_TWO))
    {
        if(QUEST_GIVEN(TP, QUEST_PROP_TWO))
        {
            command("say Like i said, I need five fins from " +
                "great white sharks. Bring them to me and i'll " +
                "reward you for it.");
            return "";
        }
	command("emote pulls on his walrus moustache thoughtfully.");
        command("say Well, you've demonstrated to me you can fish.");
	command("say But what I need now is no bonito... it is the " +
            "fins from great white sharks for my shark fin soup!");
        command("say Bring me five great white shark fins, and " +
            "i'll reward you.");

        TP->add_prop(QUEST_PROP_TWO, 1);
	return "";
    }
    else if (!CHECK_QUEST(TP, QUEST_THREE))
    {
        if(QUEST_GIVEN(TP, QUEST_PROP_THREE))
        {
            command("say Like i said, bring me the ink sac of " +
                "a collosal squid, and i'll reward you handsomely!");
            return "";
        }
	command("emote pulls on his walrus moustache with frustration.");
        command("say I've run out of squid ink for my black noodles!");
	command("say And it is no ordinary squid ink I need, but the " +
            "ink of a collosal squid, that you will only find in the " +
            "Southern Courrian Ocean.");
        command("say Bring me the ink sac of such a squid, and " +
            "i'll reward you handsomely!");

        TP->add_prop(QUEST_PROP_THREE, 1);
	return "";
    }
    else if (!CHECK_QUEST(TP, QUEST_FOUR))
    {
	command("ponder");
        command("say A few years ago an adventurous acquaintance of mine " +
            "was bringing me a recipe for a potion of swimming, after " +
            "chartering a ship from Kalaman to Palanthas.");
	command("say His ship never arrived, and I feared it lost at " +
            "sea.");
        command("say Recently I heard rumours the wreck of the ship can be " +
            "seen washed ashore on a beach east of Palanthas near the " +
            "Northern Wastes.");
        command("say While I don't hold much hope for my acquaintance, " +
            "there is the possibility you may be able to salvage the " +
            "recipe!");
        command("say As a first step, see if you can find the recipe " +
            "in the wreck and bring it to me!");
        TP->add_prop(QUEST_PROP_FOUR, 1);
	return "";
    }

    command("say Thanks, you have helped me a lot. I have nothing " +
        "further I can ask of you!");

    return "";
}

void
calculate_experience(object who, int quest_num)
{
    int xp_base;

    if (CHECK_QUEST(who, quest_num))
    {
	who->catch_msg("Nice job, but no experience second time.\n");
	return;
    }

    if(quest_num == QUEST_ONE)
    {
        xp_base = QUEST_ONE_REWARD;

        who->catch_msg("You feel a bit more experienced!\n");
        if (who->query_wiz_level())
        {
	    who->catch_msg("xp: " + xp_base + "\n");
        }

        who->add_exp(xp_base, 0);
        who->set_bit(4, QUEST_ONE);

        K_QUEST_LOG("quest", "Bishon Fishing Quest", who, xp_base);
    }

    if(quest_num == QUEST_TWO)
    {
        xp_base = QUEST_TWO_REWARD;

        who->catch_msg("You feel a bit more experienced!\n");
        if (who->query_wiz_level())
        {
	    who->catch_msg("xp: " + xp_base + "\n");
        }

        who->add_exp(xp_base, 0);
        who->set_bit(4, QUEST_TWO);

        K_QUEST_LOG("quest", "Bishon Shark Fin Soup Quest", who, xp_base);
    }

    if(quest_num == QUEST_THREE)
    {
        xp_base = QUEST_THREE_REWARD;

        who->catch_msg("You feel a bit more experienced!\n");
        if (who->query_wiz_level())
        {
	    who->catch_msg("xp: " + xp_base + "\n");
        }

        who->add_exp(xp_base, 0);
        who->set_bit(4, QUEST_THREE);

        K_QUEST_LOG("quest", "Bishon Black Noodles Quest", who, xp_base);
    }

    if(quest_num == QUEST_FOUR)
    {
        xp_base = QUEST_FOUR_REWARD;

        who->catch_msg("You feel more experienced!\n");
        if (who->query_wiz_level())
        {
	    who->catch_msg("xp: " + xp_base + "\n");
        }

        who->add_exp(xp_base, 0);
        who->set_bit(4, QUEST_FOUR);

        K_QUEST_LOG("quest", "Bishon Swimming Potion Quest", who, xp_base);
    }

    return;
}


void
give_it_back(object ob, object from)
{
    string what, who;

    what = L(ob->query_short());
    who = from->query_real_name();

    command("say What do you want me to do with this?");
    command("eyebrow quiz");
    command("say Here friend, take it back.");
    command("give " + what + " to " + who);
    command("drop " + what);
}

void
receive_bonito(object ob, object from)
{
    string what;

    // Check if the player has ever caught a bonito
    if(!FISHING_MANAGER->query_num_caught_fish(from, "Balifor bonito"))
    {
	command("emote smells the " +ob->query_short()+ " sceptically.");
        command("say This bonito doesn't smell very fresh. You didn't " +
            "catch this yourself did you?");
        command("say Bring me a fresh Balifor bonito you have caught " +
            "yourself please!");
        ob->remove_object();
        return;
    }

    command("say Ahah! Wonderful! A fresh Balifor bonito!");
    command("congratulate " +from->query_real_name());
    command("emote happily gives the bonito to the chef in the kitchen.");
    command("say Here! As promised, your reward!");

    setuid();
    seteuid(getuid());
    object platter = clone_object(PLATTER);
    platter->add_name("_quest_reward");
    platter->move(TO, 1);

    what = L(platter->query_short());
    command("give platter to "+from->query_real_name());
    command("drop platter");

    calculate_experience(from, QUEST_ONE);

    ob->remove_object();
}

void
receive_fin(object ob, object from)
{
    string what;

    // command("say fin heap: " +ob->num_heap());

    if (!CHECK_QUEST(from, QUEST_ONE))
    {
        command("say Thanks, but didn't I ask you to get me " +
            "a Balifor bonito?");
        ob->remove_object();
	return;
    }

    if(ob->num_heap() < 5)
    {
        int fins = ob->num_heap() + from->query_prop(SHARK_FIN_NUM);

        if(fins < 5)
        {
            from->add_prop(SHARK_FIN_NUM, fins);
            command("say Great! That's " +LANG_NUM2WORD(fins)+ 
                " shark fins!");
            command("say Bring me another " +LANG_NUM2WORD((5 - fins))+
                " and i'll reward you!");

            ob->remove_object();
            return;
        }
    }

    command("say Ahah! Wonderful! That's the five shark fins I was after!");
    command("congratulate " +from->query_real_name());
    command("emote happily gives the shark fins to the chef in the kitchen.");
    command("say Here! As promised, your reward!");

    from->remove_prop(SHARK_FIN_NUM);
    ob->remove_object();

    setuid();
    seteuid(getuid());
    object platter = clone_object(SOUP);
    platter->add_name("_quest_reward");
    platter->move(TO, 1);

    what = L(platter->query_short());
    command("give " +what+ " to "+from->query_real_name());
    command("drop " +what);

    calculate_experience(from, QUEST_TWO);
}

void
receive_sac(object ob, object from)
{
    if (!CHECK_QUEST(from, QUEST_ONE))
    {
        command("say Thanks, but didn't I ask you to get me " +
            "a Balifor bonito?");
        ob->remove_object();
	return;
    }

    if (!CHECK_QUEST(from, QUEST_TWO))
    {
        command("say Thanks, but didn't I ask you to get me " +
            "five shark fins?");
        ob->remove_object();
	return;
    }

    if(ob->query_sac_fullness())
    {
        command("sigh sadly");
        command("say This ink sac has no ink!");
        command("say I need you to bring me one with the ink still " +
            "in it!");
        ob->remove_object();
        return;
    }
	
    command("say Ahah! Wonderful! The ink sac of a collosal squid!");
    command("congratulate " +from->query_real_name());
    command("emote happily gives the ink sac to the chef in the kitchen.");
    command("say Here! As promised, your reward!");

    seteuid(getuid(this_object()));
    MONEY_MAKE_GC(2)->move(this_object(), 1);

    command("give coins to "+from->query_real_name());
    command("drop coins");

    calculate_experience(from, QUEST_THREE);

    ob->remove_object();
}

string
ask_recipe()
{
    if (CHECK_QUEST(this_player(), QUEST_FOUR))
    {
        command("say Thanks for making me a swimming potion! I " +
            "appreciate it!");
	return "";
    }

    if (this_player()->query_prop(QUEST_TASKED_POTION))
    {
        command("say According to the recipe, you will need " +
            "a sea lion heart and some water.");
        command("say ...and a mortar to mix the potion in " +
            "and a vial to hold the mixture.");
        command("say You could probably get those last two " +
            "items at the alchemists in the Merchants Quarter.");
	return "";
    }

    command("say Potion of swimming? Now that could come in handy!");
    command("think");
    return "";
}

string
ask_potion()
{
    if (!CHECK_QUEST(this_player(), QUEST_THREE))
    {
        command("say A recipe? Sorry I can't help you with that.");
	return "";
    }

    if (this_player()->query_prop(QUEST_RETURNED_RECIPE))
    {
        command("eyebrow");
        command("say Thanks for getting me the recipe for swimming " +
            "potions!");
        command("say Shame I have no skill in making them!");
        command("grumble");
        command("say The recipe said to mix a potion of swimming you " +
            "need to put water and a sea lion heart in a mortar, and " +
            "have a vial on hand... really, how hard " +
            "could that be?");
	return "";
    }

    command("say Yes, a recipe for a potion of swimming! I've always " +
        "wanted to swim across the Palanthas harbour, but never had " +
        "the skill!");
    return "";
}

void
receive_recipe(object ob, object from)
{
    if (!CHECK_QUEST(from, QUEST_ONE))
    {
        command("eyebrow");
        command("say Thanks, but didn't I ask you to get me " +
            "a Balifor bonito?");
        ob->remove_object();
	return;
    }

    if (!CHECK_QUEST(from, QUEST_TWO))
    {
        command("eyebrow");
        command("say Thanks, but didn't I ask you to get me " +
            "something else? Maybe five shark fins?");
        ob->remove_object();
	return;
    }

    if (!CHECK_QUEST(from, QUEST_THREE))
    {
        command("eyebrow");
        command("say Thanks, but didn't I ask you to get me " +
            "something else? Maybe an ink sac?");
        ob->remove_object();
	return;
    }

    if (from->query_prop(QUEST_RETURNED_RECIPE))
    {
        command("eyebrow");
        command("say Thanks, but you've already given me the recipe? " +
            "I need you to bring me the main ingredient, a heart " +
            "of a sea lion.");
        ob->remove_object();
	return;
    }

    command("smile glee");
    command("say Ahah! Wonderful! The recipe for the potion of swimming!");
    command("unfurl scroll");
    command("read scroll");
    command("emote tugs on his walrus moustache thoughtfully.");
    command("say I think I can make this, but it looks like i'll need " +
        "an ingredient I don't have... the heart of a sea lion.");
    command("say Bring me the heart of a sea lion, and i'll see if i can " +
        "make it!");

    from->add_prop(QUEST_RETURNED_RECIPE, 1);

    ob->remove_object();
}

void
quest_four_part_two(object from)
{
    from->add_prop(QUEST_TASKED_POTION, 1);
    command("say Ok, I clearly don't have the skill to mix potions, " +
        "even though it seems even 'amateurs' should be able to!");
    command("boggle");
    command("say Anyway, perhaps you'd have better success. " +
        "Can you try make the potion of swimming and give it to me?");
    command("say Unfortunately I ruined the sea lion heart when mixing, " +
        "so you'll need to somehow find another one.");
    command("shrug");

}

void
receive_heart(object ob, object from)
{
    if (!CHECK_QUEST(from, QUEST_ONE))
    {
        command("eyebrow");
        command("say Thanks, but didn't I ask you to get me " +
            "a Balifor bonito?");
        ob->remove_object();
	return;
    }

    if (!CHECK_QUEST(from, QUEST_TWO))
    {
        command("eyebrow");
        command("say Thanks, but didn't I ask you to get me " +
            "something else? Maybe five shark fins?");
        ob->remove_object();
	return;
    }

    if (!CHECK_QUEST(from, QUEST_THREE))
    {
        command("eyebrow");
        command("say Thanks, but didn't I ask you to get me " +
            "something else? Maybe an ink sac?");
        ob->remove_object();
	return;
    }

    if (!from->query_prop(QUEST_RETURNED_RECIPE))
    {
        command("eyebrow curious");
        command("say Thanks, but not sure why you brought me this?");
        command("shrug");
        ob->remove_object();
	return;
    }

    command("cheer");
    command("say Well done! A sea lion heart!");
    command("say Ok, let's see if i can make this potion.");
    set_alarm(1.5, 0.0, &command("emote gets a heavy marble mortar from the kitchen."));
    set_alarm(3.0, 0.0, &command("emote puts a sea lion heart in a heavy marble mortar."));
    set_alarm(4.5, 0.0, &command("emote adds a glass of water to the heavy marble mortar."));
    set_alarm(6.0, 0.0, &command("emote tries to mix a potion of swimming but fails, " +
        "ruining the ingredients."));
    set_alarm(6.5, 0.0, &command("curse"));
    set_alarm(7.0, 0.0, &quest_four_part_two(from));

    ob->remove_object();
}

void
reward_fourth_quest(object from)
{
    command("say Thank you for that!");
    command("say Here! As promised, a reward!");

    seteuid(getuid(this_object()));
    MONEY_MAKE_PC(5)->move(this_object(), 1);

    command("give coins to "+from->query_real_name());
    command("drop coins");

    calculate_experience(from, QUEST_FOUR);
}

void
receive_potion(object ob, object from)
{
    if (!CHECK_QUEST(from, QUEST_ONE))
    {
        command("eyebrow");
        command("say Thanks, but didn't I ask you to get me " +
            "a Balifor bonito?");
        ob->remove_object();
	return;
    }

    if (!CHECK_QUEST(from, QUEST_TWO))
    {
        command("eyebrow");
        command("say Thanks, but didn't I ask you to get me " +
            "something else? Maybe five shark fins?");
        ob->remove_object();
	return;
    }

    if (!CHECK_QUEST(from, QUEST_THREE))
    {
        command("eyebrow");
        command("say Thanks, but didn't I ask you to get me " +
            "something else? Maybe an ink sac?");
        ob->remove_object();
	return;
    }

    if (CHECK_QUEST(from, QUEST_FOUR))
    {
        command("eyebrow");
        command("say Thanks, another potion of swimming?");
        command("emote stores the sea-green potion away in the " +
        "kitchen.");
        ob->remove_object();
	return;
    }

    if (!from->query_prop(QUEST_RETURNED_RECIPE))
    {
        command("eyebrow curious");
        command("say Thanks, but didn't I ask for the recipe?");
        command("shrug");
        ob->remove_object();
	return;
    }

    command("say Nice work! Let's see...");
    command("smell potion");
    set_alarm(0.5, 0.0, &command("say Smells like a potion of swimming..."));
    set_alarm(1.0, 0.0, &command("emote tastes a sea-green potion."));
    set_alarm(1.5, 0.0, &command("say Mmm... salty. Yep, that's a swimming potion!"));
    set_alarm(2.0, 0.0, &command("emote stores the sea-green potion away in the " +
        "kitchen."));
    set_alarm(2.5, 0.0, &reward_fourth_quest(from));

    ob->remove_object();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(ob->id("_balifor_bonito"))
    {
	set_alarm(1.0, 0.0, &receive_bonito(ob, from));
	return;
    }
    else if(ob->id("_shark_fin_"))
    {
	set_alarm(1.0, 0.0, &receive_fin(ob, from));
	return;
    }
    else if(ob->id("_giant_squid_ink_sac"))
    {
	set_alarm(1.0, 0.0, &receive_sac(ob, from));
	return;
    }
    else if(ob->id("_bishon_potion_scroll"))
    {
	set_alarm(1.0, 0.0, &receive_recipe(ob, from));
	return;
    }
    else if(ob->id("_sealion_heart"))
    {
	set_alarm(1.0, 0.0, &receive_heart(ob, from));
	return;
    }
    else if(ob->id("_bishon_quest_potion"))
    {
	set_alarm(1.0, 0.0, &receive_potion(ob, from));
	return;
    }
    else if(ob->id("_quest_reward"))
    {
	return;
    }
    else if(strlen(ob->query_coin_type()))
    {
	return;
    }
    else
      set_alarm(1.0, 0.0, &give_it_back(ob, from));

    return;
}
