/*
* /d/Sparkle/area/jade/npc/family.c
* A generic relative of the Runaway.
* Created 2017-01-23 by Martin Berka on Genesis MUD
*/

#include "../defs.h"

inherit "/std/monster";
inherit OBJ_DIR + "shared_functions"; //Common knowledge for quest
inherit OBJ_DIR + "burden"; //Speed limited for gauntlet

#include "../bandit_quest_constants.h"
#include <ss_types.h>
#include "/d/Shire/common/make_money.h"
#include <wa_types.h> //For holding

/* Definitions */
#define ARM_DIR_2 "/d/Sparkle/area/faerie/arm/"
/*Already has the right style*/

/* Global variables */
int alarm_id,   //The id of the alarm for summoning attacks by the attic archer
    delayed_action;     //A flag allowing catch_say to delay its own execution

/* Prototypes */
void call_down_attack(int explicit = 1);
int     kidnap_choke();
int     kidnap_knock();
int     kidnap_pear(object pear, int reentry = 0);
void    kidnap_stumble_home(object player);
int     pre_stumble();
void    quest_intro();

/*
 * Function name: create_monster
 * Description  : NPC constructor
 */
create_monster()
{
    if (!IS_CLONE)
    {
        return;
    }

    string famname = one_of_list( ({"aril", "arcas", "blenkit", "bren",
        "brylan", "celtier",
        "codris","cosa", "cherven", "dorynn", "drev", "ekip", "evuntu",
        "flet", "foris", "gormin", "groznu", "holos", "hliv", "imor",
        "javna", "jesin", "klotny", "levus", "lipa", "mishlev", "mwot",
        "nots", "ofir", "permis", "pyosen", "querz", "rodin", "rusal",
        "remeas", "silenas", "sosnuh", "toru", "trefyn", "ulir", "vesenz",
        "vyar", "wenos", "yenor", "zyarn"}) );

    set_name(famname);
    set_living_name(famname);
    add_name(QUEST_FAMILY);

    set_race_name("human");
    set_adj( ({
        one_of_list( ({"gentle", "cheerful", "sad", "worried",
            "angry", "smiling", "cheeky", "grim", "friendly", "calm",
            "snarling", "laughing", "determined", "fierce",
            "concerned", "scared", "frightened", "nervous", "busy", "mad",
            "thoughtful", "quiet", "loud", "tired",
            "energetic", "careful", "fearful", "hard-working"}) ),
        one_of_list( ({"strong", "slender", "short", "fat", "scrawny",
            "hairy", "blue-eyed", "black-eyed", "green-haired",
            "long-legged", "big-eared", "lithe",
            "muscled", "strong", "brown-eyed", "brown-haired",
            "bearded", "grey-haired", "weak", "green-eyed", "dirty", "slim",
            "balding", "long-legged", "chubby"}) ) }) );
    set_stats( ({50, 50, 70, 50, 50, 40}), 40);
    MAKE_MONEY;
    set_alignment(200);

    set_skill(SS_WEP_SWORD,60);
    set_skill(SS_PARRY,50);
    set_skill(SS_DEFENCE,50);
    set_skill(SS_WEP_MISSILE, 100); //These are incredible rangers,
    set_skill(SS_AWARENESS, 100); //who can count money and harm remotely.
    set_skill(SS_HIDE, 100); //and hide in trees and especially attics.

    add_prop(NPC_I_NO_FEAR, 1);

    family_index = FAMILY_RANGE + 1 + random(4);
    //Family beyond the range are not eligible for quest roles; no doubles.
    set_gender(family_index % 2 ? G_MALE : G_FEMALE);

    set_chat_time(20);

    /* General fruit-/forest-related chats. Each NPC gets a slightly different
     * combination to reduce risk of repetition.
     */
    add_chat(one_of_list( ({
        "Buy some fruits! Buy all the fruits! Else they'll go to waste.",
        "Don't touch the trees. Or the fence. Actually, best just go to "
                + "the fruit stand, buy all you can carry and leave."}) ));

    if (random(2)) //Bored of forest
    {
        add_chat("Fruit for breakfast, fruit for lunch, fruit for dinner. "
            + "What I wouldn't give for vegetables!");
        add_chat("Pears should be ripe soon. The pears are always ripe here.");
    }
    else //Interested
    {
        add_chat("The forest is bitter, but with a bit of cultivation, "
            + "the fruits are positively intoxicating.");
        add_chat("I wonder if this soil could handle avocado. It seems to take "
            + "anything else we plant in it!");
    }

    add_chat(one_of_list( ({"Trail's done. Nice to see it works!",
        "Not sure that trail was worth it - oh well, hard to undo it now."}) ));

    add_act(one_of_list( ({"frown", "emote paces around grimly."}) ));

    /*Quest-introductory. Since name of runaway differs, and TP
    * is unclear, must avoid using the name in discussion not initiated by
    * player*/
    add_chat(one_of_list( ({"It's been several days, I'm getting worried. We "
        + "should look again.",
        "We searched the forest and the nearby road. Nothing." }) ));
    add_chat(one_of_list( ({"The bandits were easier to handle when they lived "
        + "here. Now the road's no good if you're hauling something.",
        "Right in the orchard! Coming up out of the ground! Much good it did "
        + "them."}) ));

    //Asks
    add_ask( ({"task","tasks", "help", "job", "quest", "assistance"}),
        "@@quest_intro");
    add_ask( ({"live","living","life"}),
        "@@ask_live");
    add_ask( ({"bandit", "bandits", "thief", "highwayman"}),
        "@@ask_bandit");
    add_ask( ({"barkhound", "barkhounds", "bark", "bite", "wolf", "wolves",
        "mossy wolf"}),
        "@@ask_barkhound");
    add_ask( ({"cart"}),
        "@@ask_cart");
    add_ask( ({"fence", "barricade", "palisade", "barrier"}),
        "say It's our main de...fence, always has been. Keep away from it if "
        + "you know what's good for you.", 1);
    add_ask( ({"farm", "orchard", "family"}),
        "We've been here since anyone can remember. The forest is not exactly "
        + "safe, but we know how to handle it. Nothing much changes, at least "
        + " it didn't until the bandits turned on us. "
        + "And now we've had to open up the path...", 1);
    add_ask( ({"name", "names", "who are you"}),
        "@@ask_name");
    add_ask( ({"ogre", "ogres", "ferocious ogres"}),
        "say Sure, some are ferocious - part of why we have the fence. Others "
        + "we have known for ages.", 1);
    add_ask( ({"skin", "green", "green skin"}),
        "say It's called the Jade Forest for a reason - sooner or later, "
        + "it changes everyone.", 1);
    add_ask( ({"origan", "leader", "chief", "bandit leader", "bandit chief"}),
        "say I haven't seen that Origan fellow myself, but I hear he's a mean "
        + "sort with an odd sword. "
        + "The bandits are different with him in charge.", 1);
    add_ask( ({"path", "trail", "open"}),
        "say We usually hide from the outside, but since we can't send the "
        + "cart to "
        + "Sparkle now, we had to reveal the way here to get customers. It "
        + "brought you here, so I guess it worked.",1 );
    add_ask( ({"sparkle", "market"}),
        "say Normally we'd send a cart and sell most of "
        + "our fruit in Sparkle's Market Square, but now the bandits always "
        + "intercept it. Sparkle doesn't care - all they do is talk about low "
        + "tariffs and limited funds. Their law and stops at the gates.", 1);


    set_act_time(20 + random(10));

    set_random_move(15); //With thanks to Arman for the example
    set_restrain_path(ROOM_DIR + "jade");
    set_monster_home( file_name(previous_object()) );

    alarm_id = 0; //No alarm is active

    add_name(QUEST_BURDEN); //For kidnapping
    set_slots(W_BOTH);

    set_alarm(0.5, 0.0, "arm_me");

}

/*
 * Function name: add_introduced
 * Description  : When the player introduces themselves, introduce if unknown.
 */
void
add_introduced(string str)
{
    if (!interactive(TP) || TP->query_met(query_name()))
    {
        return;
    }

    command("introduce me to " + query_living_name(TP) + "");
}

/*
 * Function name: arm_me
 * Description  : Equip weapons and armor
 */
void
arm_me()
{
    FIXEUID;

    //Weapon; archer duty leads to wielding bow instead.
    clone_object(one_of_list( ({WEP_DIR + "fruit_knife", WEP_DIR + "billhook",
        "/d/Calia/argos/swterr/weapons/axe"}) ))->move(TO);

    object torso = clone_object(one_of_list( ({ARM_DIR + "banleather",
        ARM_DIR_2 + "sh_lvest", ARM_DIR_2 + "burlap_shirt"
    }) ));
    torso->set_at(A_ARMS | A_BODY);
    torso->move(TO);

    clone_object( ARM_DIR_2 + one_of_list( ({"l_pants",
        "burlap_pants"}) ))->move(TO); //legs

    if (!random(4))  //Every fourth one wears herb gloves for picking
    {
        clone_object("/d/Shire/frogmorton/obj/herb_gloves")->move(TO);
    }

    command("wear all");
    command("wield all");
}

/*
 * Function name: ask_bandit
 * Description  : When player asks about bandits
 * Returns      : Empty string
 */
string
ask_bandit()
{
    command("say Bandits? None here any more, but there used to be. Our only "
        + "neighbours, besides the ogres. They were were alright - "
        + "just a few locals getting by the rough way. Not honest work, but "
        + "we could hardly turn up our noses - they'd buy food and pay with "
        + "what we can't make around here. Then that Origan turned up.");
    command("shudder");
    command("say They started recruiting, making demands. Those were bad "
        + "years. "
        + "When they tried to take the farm, we took some lives. They've moved "
        + "to a safer hideout, but still come by to try their luck now and "
        + "then.");

    //TODO: Say only if this is a role-holder
    if(!TP->DID_RUN_QUEST())
    {
      command("frown thoughtfully");
      command("say " + runaway_name(query_living_name(TP))
          + " might not remember how it started.");
      return "";
    }
}


/*
 * Function name: ask_bandit
 * Description  : When player asks about barkhounds
 * Returns      : (string) Empty string
 */
string
ask_barkhound()
{
    switch (random(5))
    {
    case 0:
        command("say I hate those furry vermin, always chewing on the fence!");
    case 1:
        command("say Careful, they're everywhere. We've tried hunting them, "
            + "but I swear the things sprout right out of the ground.");
    case 2:
        command("say A friendly one's been coming around lately - odd, but at "
            + "least we're seeing less of the others.");
    case 3:
        command("say Sure, we say 'bark', but it's a mossy bark, soft as long as "
            + "they're not bristling. One lets us pet him. Their bite is much "
            + "worse.");
    default:
        command("say They'll chew on anything and ayone. I got this the other day "
            + "when I was out checking the fence.");
        command("emote shows off a sickly-green left leg with fresh tooth "
            + "marks.");
    }
    return "";
}


/*
 * Function name: ask_cart
 * Description  : When player asks about the cart or the fruit transporter,
 *      make a reference to the cart quest!
 * Returns      : (string) "" (Response is handled here)
 */
string
ask_cart()
{
    command("say No cart can get through these woods - we "
        + "push a few 'barrows-full of fruit to the road and load themm into a "
        + "friend's. With Sparkle blocked, we've been trying our luck to "
        + "the south.");
    command("emote grimaces in annoyance");
    command("say Whenever we're not there to help, he keeps getting that old "
        + "thing stuck in the mud!");

    return "";
}


/*
 * Function name: ask_name
 * Description  : When player asks about names
 * Returns      : (string) "" (Response is handled here)
 */
string
ask_name()
{
    command("say Names are valuable - once you can tell people apart, you can "
        + "learn their individual strengths and weaknesses. We change ours "
        + "often to keep the bandits guessing. That said...");
    add_introduced("");

    return "";
}


/*
 * Function name: attacked_by
 * Description  : Actions taken when attacked by another.
 *          Also triggers when NPC arrives in a room and attacks another.
 */
void
attacked_by(object obj)
{
    if ( member_array( obj, query_enemy(-1)) == -1) //New opponent
    {
        command(one_of_list( ({"say After the fruits of our labours, eh?",
            "say You're with them, aren't you!?!", "growl quietly",
            "grit teeth",
            "say You're not welcome here!", "say Bleed like the trees!",
            }) ));
    }

    ::attacked_by(obj);

    command("wield all");
    command("wear all");

    if (alarm_id)
    {
        remove_alarm(alarm_id);
    }
    alarm_id = set_alarm(6.0, 13.0, call_down_attack);
}


/*
 * Function name: filter_family
 * Description  : Filter function for identifying other family members
 */
int
filter_family(object test_me)
{
    return (file_name(test_me) == file_name(this_object()));
}

/*
 * Function name: before_attack
 * Description  : Recurring request for arrows from attic
 * Arguments    : (int) explicit - 1: audibly/visibly request arrows; 0: secret
 */
void
call_down_attack(int explicit = 1)
{
    if (!TO->query_attack()) //If not in combat
    {
        if (explicit)
        {
            command( one_of_list( ({"snort suspiciously", "breathe",
                "stretch"}) ));
        }

        remove_alarm(alarm_id);
        alarm_id = 0;

        return;
    }

    string r;
    if (environment(TO)->query_prop(ROOM_I_INSIDE) ||
        !sscanf(file_name(environment(TO)), THIS_DIR + "jade%s", r))
    {
        return; //Out of attic-range at the moment.
    }

    object attack_target = TO->query_attack();
    object attic = find_object(ARCHER_ROOM);
    string call_message = "";
    if (explicit)
    {
        switch (random(5))
        {
            case 0:
                command("say You'll live to regret this! Or not.");
                break;
            case 1:
                command("say It's never just one of us.");
                break;
            default:
        }

        string archer = attic->query_archer()->query_name();
        switch (random(8))
        {
            case 0:
                call_message = "Whenever you're ready, " + archer + "!";
                break;
            case 1:
                call_message = archer + "! Over here!";
                break;
            case 2:
                call_message = "Can't you shoot any faster, " + archer + "?";
                break;
            case 3:
                call_message = archer + "? I could use a hand here!";
                break;
            case 4:
            case 5:
                command("wave frantically");
                break;
            default:
                command("emote stares upward expectantly.");
        }
        if (call_message != "")
        {
            command("shout " + call_message);
        }
    }
    attic->request_arrow(attack_target, call_message);
}

/*
 * Function name: catch_say
 * Description  : Respond to the apology message for Hurt
 * Arguments    : string say_text - whatever comes after "say"
 */
void
catch_say(string say_text)
{
    if(TP->DID_RUN_QUEST())
    {
        return;
    }

    if (!delayed_action) {
        set_alarm(0.2, 0.0, &catch_say(say_text));
        delayed_action = 1;
        return;
    }
    else
    {
        delayed_action = 0;
    }

    string player_name = query_living_name(TP);
    object token = present(QUEST_TOKEN + "_from_" + player_name, TP);
    if (!token)
    {
        return;
    }

    string test_value = token->query_prop("TOKEN_I_TEST");
    if (test_value == "regrets")
    {
        //Parse for apology
        say_text = lower_case(say_text);
        if (!wildmatch(hurt_message(player_name , 1), say_text))
        {
            command("say What?");
            return;
        }

        token->add_prop("TOKEN_I_TEST", "hurt"); //"Hurt" phase done

        command("emote" + one_of_list( ({"scoffs.", "frowns.", "smiles wryly."}) ));

        //Get pronouns:
        int r_gender = runaway_gender(player_name);
        string r_obj = query_outside_pronoun(r_gender, "object");
        string r_pos = query_outside_pronoun(r_gender, "possessive");

        command("say That's " + r_pos + " apology? Well, good enough for now. "
            + "We all miss " + runaway_name(player_name) + " and want " + r_obj
            + " back safely. Please - tell " + r_obj
            + " to come home. Careful - you might "
            + "not fear bandits on the roads, but we have a history with them. "
            + "They will go out of their way to spite us.");
        return;
    }

    if (test_value == "hurt") {
        string run_name = runaway_name(player_name); //Name, gender, pronouns
        command("say Please tell " + runaway_name(player_name)
            + " to come home.");
        return;
    }
}





/*
 * Function name: enter_env
 * Description  : Wrapper for burden.c
 * Arguments    : (object) the destination
 *                (object) the old location
 */
void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    burden_enter_env(dest, old);
}


/*
 * Function name: init_living
 * Description  : Hurt should be ready to respond if the player has reached the
 *      right stage. Adds the catch_say action if player has token and
 *      established contact with Runaway.
 */
void
init_living()
{
    ::init_living();

    if(TP->DID_RUN_QUEST())
    {
        return;
    }

    //Check whether player has token that stores quest phase
    string player_name = query_living_name(TP);
    object token = present(QUEST_TOKEN + "_from_" + lower_case(player_name), TP);
    if (!token)
    {
        return;
    }


    switch (token->query_prop("TOKEN_I_TEST"))
    {
        case "regrets":
        case "hurt":
            /*Two of the methods for kidnapping Dearest - Player is free to
             *kidnap the wrong person.
             */
            add_action(kidnap_knock, "whack");
            add_action(kidnap_choke, "choke");
            break;
        default:
    }

    //Conversation with final role-holder for the good path
    if (runaway_role_index(player_name, HURT) == family_index)
     {
         object token = present(QUEST_TOKEN + "_from_" + player_name, TP);
         if (!token)
         {
             return;
         }

         switch (token->query_prop("TOKEN_I_TEST"))
         {
             case "regrets":
             case "hurt":
                 add_action(catch_say, "say");
                 break;
             default:
         }
     }
}


/*
 * Function name: kidnap_choke
 * Description  : Attempt to kidnap NPC via chokehold
 * Returns      : (int) 1/0 success/fail
 */
int
kidnap_choke()
{
    if(TP->DID_RUN_QUEST())
    {
        return 0;
    }

    write("You do your best to approach " + query_the_name(TP)
        + " without betraying your intent.\n");

    if (member_array( TP, query_enemy(-1) ) > -1)
    {
        write(query_The_name(TP) + " has " + (family_index % 2 ? "his" : "her")
            + " guard up, dodges out of "
            + "your reach and uses the opening to delivers a firm punch to "
            + "your face.\n");
        tell_room(environment(TO), QCTNAME(TP) + " tries to grab " + QTNAME(TO)
                + " and gets punched for it.\n",
            TP);

        TP->set_hp(TP->query_hp() * 9 / 10); //Loses 10% of whatever remains

        return 1;
    }
    if (kidnap_index(query_living_name(TP) == K_CHOKE)
        && !TP->DID_RUN_QUEST())
    {
        int home_already = pre_stumble();
        //NPC may already be in the house, affecting appropriate messages

        write("You suddenly put " + query_the_name(TP)
            + " in a chokehold."
            + (home_already ? " Unable to shake you off, "
                + (family_index % 2 ? "he" : "she") + " leans forward, "
                + "lifting you off the ground, and stumbles towards "
                + "the two-storey house." : "")
            + "\n");
        tell_room(environment(this_object()), QCTNAME(TP) + " puts "
            + QTNAME(TO) + " in a chokehold"
            + (home_already ? "and is dragged away "
                + "as the latter stumbles towards the two-storey house" : "")
            + ".\n",
            TP);
        set_random_move(0);
        kidnap_stumble_home(TP);
        return 1;
    }
    else
    {
        write("You attempt to put " + query_the_name(TP)
            + " in a chokehold, but " + (family_index % 2 ? "he" : "she")
            + " ducks out the way and returns your assault.\n");
        tell_room(environment(TO), QCTNAME(TP) + " attacks " + QTNAME(TO)
            + ".\n",
            TP);
        attack_object(TP);
        return 1;
    }
}


/*
 * Function name: kidnap_knock
 * Description  : Attempt to kidnap NPC by knocking them out
 * Returns      : (int) 1/0 success/fail
 */
int
kidnap_knock()
{
    if(TP->DID_RUN_QUEST())
    {
        return 0;
    }

    write("You do your best to approach " + query_the_name(TP)
        + " without betraying your intent.\n");
    object rand_bludgeon = one_of_list(all_inventory(TP))->query_short();

    if (member_array( TP, query_enemy(-1) ) > -1)
    {
        write(query_The_name(TP) + " has " + (family_index % 2 ? "his" : "her")
            + " guard up, dodges to the side and uses the opening to deliver "
            + "a firm punch to your face.\n");
        tell_room(environment(TO), QCTNAME(TP) + " tries to bludgeon "
            + QTNAME(TO) + " and gets punched for it.\n",
            TP);

        TP->set_hp(TP->query_hp() * 9 / 10); //Loses 10% of whatever remains

        return 1;
    }

    if ( kidnap_index(query_living_name(TP)) == K_KNOCK
        && !TP->DID_RUN_QUEST())
    {
        int home_already = pre_stumble();
        //Starting messages depend on whether NPC is already in house
        write("You suddenly bludgeon " + query_the_name(TP)
            + " with your " + rand_bludgeon
            + (home_already? "\n" : ". " + (family_index % 2 ? "He" : "She")
                + " sways, leans on you "
                + "for support, and totters towards the two-storey house, "
                + "dragging you along.\n"));
        tell_room(environment(this_object()), QCTNAME(TP)
            + " bludgeons " + QTNAME(this_object()) + " with a " + rand_bludgeon
            + (home_already ? ".\n" : " and is dragged away "
                + "as the latter stumbles towards the two-storey house.\n"),
            TP);

        set_random_move(0);
        kidnap_stumble_home(TP);
        return 1;
    }
    else
    {
        write("You attempt to bludgeon " + query_the_name(TP)
            + " with your " + rand_bludgeon + ", but "
            + (family_index % 2 ? "he" : "she") + " dodges.\n");
        tell_room(environment(this_object()), QCTNAME(TP)
            + " attacks " + QTNAME(this_object()) + ".\n", TP);
        attack_object(TP);
        return 1;
    }
}


/*
 * Function name: kidnap_pear
 * Description  : Attempt to kidnap NPC by hitting with an intoxicating pear.
 *      THIS FUNCTION NAME IS USED IN obj/jade_pear
 * Arguments    : (object) the thrown pear
 *                (int) Re-entry flag used for time delay
 * Returns      : (int) 1/0 success/fail
 */
int
kidnap_pear(object pear, int reentry = 0)
{
    if(TP->DID_RUN_QUEST())
    {
        return 0;
    }

    if (reentry)
    {
        if (member_array( TP, query_enemy(-1) ) > -1)
        {
            write(query_The_name(TP) + " covers "
                + (family_index % 2 ? "his" : "her") + " mouth, charges away "
                + " from the fumes and headbutts your face.\n");
            tell_room(environment(TO), QCTNAME(TO) + " headbutts " + QTNAME(TP)
                    + ".\n",
                TP);

            TP->set_hp(TP->query_hp() * 9 / 10); //Loses 10% of whatever remains

            return 0;
        }

        pear->set_throwing(1); //Suppress the release message
        pear->hit_living_effect(1, 1); //Harmlessly, but successfully

        int home_already = pre_stumble();

        //NPC may already be in the house, affecting appropriate messages
        write("The fumes appear to affect " + query_the_name(TP)
            + " rather strongly. "
            + (home_already ? "" : (family_index % 2 ? "He" : "She")
                + " sways, leans on you for support, and totters "
                + "towards the two-storey house, dragging you along.")
            + "\n");
        tell_room(environment(this_object()),
            "The fumes appear to affect " + QTNAME(this_object())
            + " rather strongly. " +
                (home_already ? "" : (family_index % 2 ? "He" : "She")
                    + " sways, leans on " + QTNAME(TP) + " for support, and "
                    + "stumbles towards the two-storey house, dragging "
                    + QTNAME(TP) + " along.")
            + "\n",
            TP);

        kidnap_stumble_home(TP);
        return 1;
    }
    if (kidnap_index( query_living_name(TP) ) == K_PEAR
        && !TP->DID_RUN_QUEST())
    {
        set_random_move(0); //Make sure NPC stays in place
        set_alarm(0.5, 0.0, &kidnap_pear(pear, 1)); //Announce after throw
        return 1;
    }

    return 0;
    //Default effect of throwing of pear (combat) handled by pear.
}



/*
 * Function name: kidnap_stumble_home
 * Description  : Player has partly incapacitated NPC, but is dragged to the
 *      farmhouse for the start of the gauntlet.
 * Arguments    : (object) The player that is dragged
 */
void
kidnap_stumble_home(object player)
{
    if(TP->DID_RUN_QUEST())
    {
        return;
    }

    string next_step = environment(this_object())->query_prop(PATH_HOME_PROP);
    string player_name = query_living_name(player);

    if (next_step == "!") //The gauntlet start room
    {
        tell_room(environment(this_object()), QCTNAME(this_object())
            + " collapses into a wheelbarrow.\n", this_object());
        object wheelbarrow = environment(TO)->request_wheelbarrow();
        TO->move(wheelbarrow);

        wheelbarrow->start_burden(player_name, 15.0, 180.0);
        //15 seconds to get the wheelbarrow or the NPC, 3 minutes to deliver
        //Wheelbarrow now takes over.

        return;
    }

    if (!strlen(next_step)) //Fallback in case path fails.
    {
        this_object()->move(ROOM_DIR + "jade_house");
        player->move(ROOM_DIR + "jade_house");
    }
    else if (next_step != "!")
    {
        command(next_step);
        player->command(next_step);
        set_alarm(0.5, 0.0, &mob_me( ({NPC_DIR + "family"}), player_name,
            5, 3));
    }
    set_alarm(2.0, 0.0, &kidnap_stumble_home(player));
    alarm_id = set_alarm(4.0, 4.0, &call_down_attack(0));
}


/*
 * Function name: leave_env
 * Description  : Wrapper for burden.c
 * Arguments    : (object) the old location
 *                (object) the destination
 */
void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);
    burden_leave_env(old, dest);
}


/*
 * Function name: long_description
 * Description	: VBFC for the NPC description
 * Returns		: (string) The description
 */
void
long_description()
{
    return capitalize(query_pronoun()) + " has the muscular arms and precise, "
        + "juice-stained fingers of a fruit grower, yet never seems fully "
        + "at ease despite this agrarian occupation. "
        + capitalize(query_possessive()) + " skin is faintly green.";
}


/*
 * Function name: pre_stumble
 * Description	: Checks whether NPC already in house, and alerts surrounding
 *      family before beginning movement.
 * Returns		: (int) home already (1) or not (0)
 */
int
pre_stumble()
{
    tell_room(environment(TP), "Someone shouts: Some fool's after "
        + query_the_name(TO) + "! Send out the cousins!\n");
    mob_me( ({NPC_DIR + "family"}), query_living_name(TP), 5, 3);
    tell_object(find_player("mar"), "TP: " + query_living_name(TP) + "\n");
    int home_already = member_array(
        environment(TO)->query_prop(PATH_HOME_PROP), ({"!", "down"}) );
    return (home_already > -1);
}


/*
 * Function name: query_family_index
 * Description	: Returns NPC family index for external calls
 * Returns		: (int) family_index
 */
int
query_family_index()
{
    return family_index;
}



/*
 * Function name: quest_intro
 * Description  : Introduces the Runaway quest from this NPC's point of view.
 */
void
quest_intro()
{
    command("frown thoughtfully");

    if (TP->DID_RUN_QUEST()) {
        command("say Times are tough, but nothing else springs to mind.");
        return;
    }

    string player_name = query_living_name(TP);
    string f_relation = runaway_relation(player_name, family_index);
    //Relation of Family relative to Runaway
    string f_sub = this_object()->query_pronoun(); //Subject pronoun of Family
    int r_gender = runaway_gender(player_name);
    string r_sub = query_outside_pronoun(r_gender); //Subject pronoun of Runaway
    string r_obj = query_outside_pronoun(r_gender, "object");
    string r_pos = query_outside_pronoun(r_gender, "possessive");
    string r_relation = runaway_relation(player_name, family_index, 1);
    //Relation of Runaway relative to Family (Runaway is __ of Family)
    string run_name = runaway_name(player_name);

    set_long("@@long_description");

    int role_count = 0; //For when Family has multiple roles
    if (runaway_role_index(player_name, REGRETS) == family_index)
    {
        role_count++;
        command("say Yes, we could do with some help. The trouble on the roads "
            + "has everyone "
            + "anxious. A few evenings back, we had a squabble. The things "
            + "that were said do not bear repeating. What matters is that my "
            + r_relation + ", " + run_name + ", took it the worst and stormed "
            + "off down the road. We have not seen " + r_obj + " since.");
        command("sigh deeply");
        command("say I was certainly the worst to dear " + run_name
            + " and think " + r_sub + " might have left for that. Please, can "
            + "you find " + r_obj
            + " and deliver my apologies? Tell " + r_obj + " "
            + regret_message(player_name) + ".");
    }

    if (runaway_role_index(player_name, DEAREST) == family_index)
    {
        if(role_count) {
            command("say And to think that I said all that to my closest "
                + "friend in the world! Apologies won't be enough. Give "
                + r_obj + " this to show that I still care!");
        }
        else
        {
            command("say My " + r_relation
                + " " + run_name + " took off after the big fight! "
                + capitalize(r_sub) + " is the most important person in the "
                + "world to me. " + capitalize(r_sub) + " often talked about "
                + "there being more exciting ways to make a living... I bet "
                + r_sub + "'s become an adventurer! Please, if you find "
                + r_obj + " - give " + r_obj + " this to remember me by.");
        }

        if (!present(QUEST_TOKEN, TP))
        {
            object token = clone_object(OBJ_DIR + "token.c");
            int this_token_index = token_index(player_name);

            string *tokens = TOKEN_NAMES;
            string token_name = tokens[this_token_index];
            string token_adj, token_noun;
            sscanf(token_name, "%s %s", token_adj, token_noun);
            token->set_name(token_noun);
            token->set_adj( token_adj );
            token->add_name(QUEST_TOKEN);
            token->add_name(token_name); //Need this for Runaway to recognize
            token->add_name(QUEST_TOKEN + "_from_" + player_name);
            token->remove_name("object");

            token->add_prop("TOKEN_I_FROM", f_relation);

            tokens = TOKEN_DESCS;
            token->set_long(tokens[this_token_index]);

            token->move(TP);

            write("\n" + query_The_name(TP) + " gives you a "
                + token_name + ".\n\n");
            tell_room(environment(this_object()),
                QCTNAME(this_object()) + " gives "
                + QTNAME(TP) + " a " + token_name + "\n",
                TP);
        }
        else
        {
            write("\n" + query_The_name(TP) + " looks for something.\n\n");
            command("say Oh, I guess you already have my token. I really "
                + "miss " + run_name + ". Please deliver it, and maybe "
                + r_sub + "'ll return?");
            command("smile hopefully");
        }
        role_count++;
    }

    if (runaway_role_index(player_name, HURT) == family_index)
    {
        if(role_count)
        {
            command("say To be fair, " + run_name + " said some very "
                + "hurtful things to me, too. I wouldn't mind an apology "
                + "from " + r_obj + ".");
        }
        else
        {
            command("say An argument three nights back turned ugly. My "
                + r_relation + ", "
                + run_name + ", has some strange ideas, and really tore into "
                + "me when I tried to talk " + r_obj + " out of them. I would "
                + "love an apology, but more than that - I would love to see "
                + r_obj + " again. Please bring " + r_obj + " back to us.");
        }
        role_count++;
    }

    if (role_count == 0)
    {
        int q_index = runaway_role_index(player_name, REGRETS);

        command("say Well, there has been some trouble with my " + r_relation
            + ", " + run_name + ". You might talk to " + r_pos + " "
            + runaway_relation(player_name, q_index) + ".");
    }
}

/*
 * Function name: set_family_index
 * Description  : Give the NPC a unique identity in the Runaway quest
 */
void
set_family_index(int index_value) {
    family_index = index_value;
    set_gender(family_index % 2 ? G_MALE : G_FEMALE);
    if (family_index <= FAMILY_RANGE)
    {          //Make sure no role-holder wanders to an inaccessible place
        set_restrain_path( ({ROOM_DIR + "jade_forest", ROOM_DIR + "jade_yard",
            ROOM_DIR + "jade_stand", ROOM_DIR + "jade_house",
            ROOM_DIR + "jade_attic"}) );
    }
}
