/*
 * firestorm.c
 *
 * This npc is the 'questmaster' for the Eye of the Beast and
 * Calian Sup. Guru Quests in Eldoral. Aside from that, there's
 * nothing particularly special about him.
 *
 * One possibility still under consideration is that once freed
 * at the end of the sup. guru quest, the dragon will come to assist
 * calians driving off krougs during any kroug raid that happens 
 * before the dragon resets.
 *
 * Note, the dragon is currently set up so that the guru quest does
 * not reset, it's strictly once-per-boot.
 *
 * Khail, Jan 8/96
 *
 * Revision history: 
 * 14/2/99   Made quest crypts reset each time the chain resets, otherwise 
 *           in the really long reboots we're getting this quest is too 
 *           rare.
 *                                              - Maniac 
 */
#pragma strict_types

#include "defs.h"
#include <ss_types.h>
#include <filter_funs.h>
#include "../guru_quest.h"

/* Unarmed attacks and hitlocs */
#define A_BITE 0
#define A_LCLAW 1
#define A_RCLAW 2
#define A_TAIL 3
#define H_HEAD 0
#define H_BODY 1
#define H_TAIL 2
#define H_RARM 3
#define H_LARM 4
#define H_RLEG 5
#define H_LLEG 6
#define H_RWING 7
#define H_LWING 8

/* Prop defines */
#define CURRENT_I_ELDORAL_QUEST "_current_i_eldoral_quest"

inherit "/std/act/chat";
inherit "/std/act/asking";
inherit "/std/combat/unarmed";
inherit "/std/creature";
inherit "/std/act/domove";
inherit "/std/act/action";

public string *remembered;
public int act_alarm;
public object chain;

public string quest_give();
public void decide_quest(object who);
public string ask_dead();
public void add_introduced(string who);
public void react_intro(string who);
public varargs void emote_hook(string emote, object actor, string adverb = 0);
public void react_offend(object actor);
public void return_greet(object actor);
public void init_firestorm_acts();
public void next_firestorm_act(int i);
public void head_for_palace();
public void second_stop_to_palace();

/*
 * Function name: reset_chain
 * Description  : Clones and/or replaces the chain holding Firestorm
 *                in place.
 * Arguments    : n/a  
 * Returns      : n/a
 */
public void
reset_chain()
{
    if (chain)
        chain->remove_object();

    seteuid(getuid());
    chain = clone_object(OBJ + "chain");
    chain->move(environment(TO));
    chain->set_dragon(TO);
    remove_prop(DRAGON_S_WAS_RELEASED);
    GURU_BRAIN->reset_quest(); 
}

/*
 * Function name: query_rem_name
 * Description  : Artificial met/nonmet for Firestorm. If the
 *                player tested has been remembered, return their
 *                race. Otherwise return their real name.
 * Arguments    : who - Object pointer to living to test for met/nonmet.
 * Returns      : A string, either the race of 'who', or their
 *                real name.
 */
public string
query_rem_name(object who)
{
    if (member_array(who->query_real_name(), remembered) < 0)
        return who->query_race();
    else
        return capitalize(who->query_real_name());
}

/*
 * Function name: is_calian
 * Description  : A simple function to test if a player is a calian.
 * Arguments    : who - Object pointer to player to test.
 * Returns      : 0 - Not a calian.
 *                1 - Calian.
 */
public int
is_calian(object who)
{
    return (who->query_guild_name_occ() == C_GURU_GUILD_NAME);
}

/*
 * Function name: extra_long
 * Description  : Some extra info for a VBFC'd long regarding
 *                the chained status of the dragon.
 * Arguments    : n/a
 * Returns      : A string containing the extra long desc.
 */
public string
extra_long()
{
    if (!query_prop(DRAGON_S_WAS_RELEASED))
        return "A massive iron chain shackles the dragon to the " +
            "ground.";
    else
        return "";
}

/*
 * Function name: create_creature
 * Description  : Turns this creature into Firestorm.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_creature()
{
    remembered = ({});
    set_name("firestorm");
    set_living_name("firestorm");
    add_name("dragon");
    set_race_name("dragon");
    set_adj("massive");
    add_adj("ancient");
    set_long("The creature before you seems to be entirely " +
        "comprised of scales, teeth, and claws. Stretched across " +
        "a heavily muscled frame, the polished scales seem to " +
        "ripple in the light as he moves. Burning red eyes " +
        "follow your every movement, leaving no doubt that " +
        "this is a dragon. @@extra_long@@\n");

    set_stats(({ 180, 180, 180, 180, 180, 180}));

    set_hp(query_max_hp());

    set_skill(SS_DEFENCE, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_BLIND_COMBAT, 100);

    set_attack_unarmed(A_BITE, 50, 90, W_IMPALE, 30, "jaws");
    set_attack_unarmed(A_LCLAW, 80, 80, W_SLASH, 30, "left talons");
    set_attack_unarmed(A_RCLAW, 80, 80, W_SLASH, 30, "right talons");
    set_attack_unarmed(A_TAIL, 75, 90, W_BLUDGEON, 10, "tail");

    set_hitloc_unarmed(H_HEAD, ({90, 80, 90, 100}), 10, "head");
    set_hitloc_unarmed(H_BODY, ({80, 70, 40, 100}), 50, "body");
    set_hitloc_unarmed(H_TAIL, ({80, 80, 80, 100}), 6, "tail");
    set_hitloc_unarmed(H_RARM, ({50, 50, 40, 100}), 10, "right foreleg");
    set_hitloc_unarmed(H_LARM, ({50, 50, 40, 100}), 10, "left foreleg");
    set_hitloc_unarmed(H_RLEG, ({60, 60, 50, 100}), 7, "right hindleg");
    set_hitloc_unarmed(H_LLEG, ({60, 60, 50, 100}), 7, "left hindleg");
    set_hitloc_unarmed(H_RWING, ({50, 50, 40, 100}), 10, "right wing");
    set_hitloc_unarmed(H_LWING, ({50, 50, 40, 100}), 10, "left wing");

    set_alignment(600);

    add_ask(({"quest", "task", "job"}), VBFC_ME("quest_give"), 0);

  /* add_asks for the Eye of the Beast Quest */
    add_ask(({"dead", "undead", }), VBFC_ME("ask_dead"), 0);
    add_ask(({"beast", "beast in the ravine", 
        "beast in the north ravine", "about beast", 
        "about beast in the ravine", "about beast in the north ravine",
        "about the beast", "about the beast in the ravine",
        "about the beast in the north ravine"}),
        VBFC_ME("ask_beast"), 0);
    add_ask(({"ravine", "about ravine", "about the ravine",
        "north ravine", "about north ravine",
        "about the north ravine"}),
        VBFC_ME("ask_ravine"), 0);
    add_ask(({"caverns", "caverns of the dead", "about caverns",
        "about caverns of the dead", "about the caverns",
        "about the caverns of the dead"}),
        VBFC_ME("ask_caverns"), 0);

#ifdef GURU_OPEN
  /* Add_asks for the Calian Sup. Guru Quest. */
    add_ask(({"chain", "about chain", "about the chain"}),
        VBFC_ME("ask_chain"), 0);
    add_ask(({"hand", "hand of a king", "about hand",
        "about hand of a king", "about the hand",
        "about the hand of a king"}),
        VBFC_ME("ask_hand"), 0);
#endif

    add_prop(LIVE_I_SEE_DARK, 10);
    add_prop(LIVE_I_SEE_INVIS, 5);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(OBJ_I_RES_MAGIC, 100);
    add_prop(OBJ_I_RES_POISON, 100);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_alarm(0.5, 0.0, reset_chain);
}

/*
 * Function name: quest_give
 * Description  : Part of the routine that decides which, if any,
 *                quests to give a player. Called by asking.
 * Arguments    : n/a
 * Returns      : "" always.
 */
public string
quest_give()
{
    command("peer " + OB_NAME(TP) + " thoughtfully");
    command("emote rumbles: So it's a challenge you're " +
        "after? Very well, then.");
    set_alarm(0.5, 0.0, &decide_quest(TP));
    return "";
}

/*
 * Function name: decide_quest
 * Description  : Makes a decision on which quests to give a player.
 * Arguments    : who - Object pointer to living looking for a quest.
 * Returns      : n/a
 */
public void
decide_quest(object who)
{
  /* Do nothing if who isn't around. */
    if (!objectp(who) || !present(who, environment()))
        return;

  /* If 'who' hasn't done the Eye of the Beast Quest, send */
  /* him on it. */
    if (!who->test_bit("Calia", ELDORAL_QUEST_GROUP, 
        ELDORAL_BEAST_QUEST_BIT))
    {
        command("emote rumbles: Bring me the eye of the Beast " +
            "in the north ravine, and prove your might.");
        who->add_prop(LIVE_I_BEAST_QUEST,
            who->query_prop(LIVE_I_BEAST_QUEST) | BQ_SPOKE_FIRESTORM);
        return;
    }

  /* Otherwise, there are no quests left, unless the player is */
  /* a Calian, in which case they can do the sup. guru quest. */
    else
    {
        command("emote rumbles: I have no challenges left.");

#ifdef GURU_OPEN
        if (is_calian(who))
        {
            command("emote seems to study you carefully.");
            if (query_prop(DRAGON_S_WAS_RELEASED))
            {
                return;
            }           
            command("emote rumbles: However, thou art a " +
                "Calian, and I am bound by ancient vow to " +
                "aid thee where I might. Release me from " +
                "these chains, and thy skill in combat will " +
                "grow mightily.");
            who->add_prop(LIVE_I_GURU_QUESTING,
                who->query_prop(LIVE_I_GURU_QUESTING) | C_GURU_DRAGON);
        }
#endif
        return;
    }

    command("emote rumbles: I have nothing more for thee.");        
}

/*
 * Function name: ask_dead
 * Description  : Generates the response to being asked about the
 *                dead. (Eye of the Beast Quest)
 * Arguments    : n/a
 * Returns      : ""
 */
public string
ask_dead()
{
  /* No info if they've already done the Eye of the Beast quest. */
    if (TP->test_bit("Calia", ELDORAL_QUEST_GROUP,
        ELDORAL_BEAST_QUEST_BIT))
    {
        command("emote rumbles: They are no longer of concern to " +
            "thee.");
    }
    else
    {
        command("emote rumbles: They are the tortured souls of " +
            "those who long ago sought to free the Beast.");
    }
    return "";
}

/*
 * Function name: ask_beast
 * Description  : Provides some information when asked about the
 *                beast. (Eye of the Beast Quest)
 * Arguments    : n/a
 * Returns      : ""
 */
public string
ask_beast()
{
    if (TP->test_bit("Calia", ELDORAL_QUEST_GROUP,
        ELDORAL_BEAST_QUEST_BIT))
    {
        command("emote rumbles: The beast is no longer thy concern.");
    }
    else
    {
        command("emote rumbles: Beyond the caverns of the dead, in " +
            "the north ravine of the isle, it stalks. Be wise in " +
            "thy movement there, for it may decide thy fate.");
    }
    return "";
}

/*
 * Function name: ask_ravine
 * Description  : Response to give when asked about the ravine.
 *                (Eye of the Beast Quest)
 * Arguments    : n/a
 * Returns      : ""
 */
public string
ask_ravine()
{
    command("emote rumbles: The ravine lies in the north part of " +
        "this isle, through the caverns you must go to reach it.");
    return "";
}

/*
 * Function name: ask_caverns
 * Description  : Response to give when asked about the caverns.
 *                (Eye of the Beast Quest)
 * Arguments    : n/a
 * Returns      : ""
 */
public string
ask_caverns()
{
    command("emote rumbles: Frought with danger are the caverns " +
        "of the dead, and not easy to find. But find them thy " +
        "must if thou wouldst slay the beast.");
    return "";
}

/*
 * Function name: ask_chain
 * Description  : Response to being asked about the chain.
 *                (Calian Sup. Guru quest)
 * Arguments    : n/a
 * Returns      : ""
 */
public string
ask_chain()
{
  /* Non-calians can never do this quest. */
    if (!is_calian(TP))
    {
        command("emote rumbles: It is of no import to thee.");
    }

  /* No sense talking about the chain if it's been broken. */
    else if (query_prop(DRAGON_S_WAS_RELEASED))
    {
        command("emote rumbles: The chain is now broken, " +
            "hewn by the hand of a king.");
    }

  /* No sense asking about the chain if the player's already */
  /* done the quest. */
    else if (TP->test_bit("Calia", ELDORAL_QUEST_GROUP,
        ELDORAL_GURU_QUEST_BIT))
    {
        command("emote rumbles: The chain is no longer " +
            "thy concern.");
    }

  /* Don't tell calians anything about the chain if they */
  /* aren't doing the guru quest. */
    else if (!TP->query_prop(LIVE_I_GURU_QUESTING) & C_GURU_DRAGON)
    {
        command("emote rumbles: The chain is of no import to thee.");
    }

    else
    {
        command("emote rumbles: The chain which imprisons " +
            "me is magic, beyond my powers to break. It is " +
            "said only the hand of a king may break this " +
            "bond.");
    }
    return "";
}

/*
 * Function name: ask_hand
 * Description  : Response to give when asked about the hand of a
 *                king. (Calian Sup. Guru Quest)
 * Arguments    : n/a
 * Returns      : ""
 */
public string
ask_hand()
{
  /* Only calians can do this quest. */
    if (!is_calian(TP))
    {
        command("emote rumbles: It is nothing you need to know.");
    }

  /* No need to talk about the hand when the dragon's been released. */
    else if (query_prop(DRAGON_S_WAS_RELEASED))
    {
        command("emote rumbles: There is no need for the " +
            "hand of a king, for I am free!");
    }

  /* No need to talk when the player's already solved the quest. */
    else if (TP->test_bit("Calia", ELDORAL_QUEST_GROUP,
        ELDORAL_GURU_QUEST_BIT))
    {
        command("emote rumbles: Thou knowest more about the " +
            "hand than I, and thou has already performed the " +
            "service I require once.");
    }

  /* Don't tell calians anything about the chain if they */
  /* aren't doing the guru quest. */
    else if (!TP->query_prop(LIVE_I_GURU_QUESTING) & C_GURU_DRAGON)
    {
        command("emote rumbles: It is nothing you need to know.");
    }

    else
    {
        command("emote rumbles: I know nothing of the hand of " +
            "a king, only that it is the only thing which " +
            "may break this chain. It is, however, something " +
            "of which the wisest of warriors are said to know " +
            "more of. Find one, and perhaps he or she may tell " +
            "thee more.");
    }
    return "";
}

/*
 * Function name: add_introduced
 * Description  : Handles what to do when a player introduces themself.
 * Arguments    : who - The query_real_name() of the person who
 *                      introduced.
 * Returns      : n/a
 */
public void
add_introduced(string who)
{
    set_alarm(0.5, 0.0, &react_intro(who));
}

/*
 * Function name: react_intro
 * Description  : Final reaction to someone introducing themselves to
 *                the dragon.
 * Arguments    : who - Query_real_name() of the player who intro'd.
 * Returns      : n/a
 */
public void
react_intro(string who)
{
    object player;

  /* Make sure it's a player. */
    if (!(objectp(player=find_player(lower_case(who)))))
        return;

  /* Make sure the player's still in the room. */
    if (!present(player, environment()))
        return;

  /* Have we remembered the player yet? If not, greet and */
  /* introduce ourselves, remembering the player's name. */
    if (member_array(who, remembered) < 0)
    {
        command("emote rumbles: Greetings, " + 
            capitalize(player->query_real_name()) + ".");
        command("emote dips his head slightly in your direction.");
        command("emote rumbles: I am known by many names. Those " +
            "who once lived here, however, knew me simply as " +
            "Firestorm.");
        remembered += ({who});
        FILTER_PRESENT_LIVE(users())->add_introduced("firestorm");
    }
    else
    {
        command("say I remember thee, " +
        capitalize(player->query_real_name()) + ". I'm ancient " +
            "by your standards, but far from senile.");
    }
}

/*
 * Function name: emote_hook
 * Description  : Handles what to do when an emote is performed
 *                in the room.
 * Arguments    : emote - The command verb for the emote.
 *                actor - Object pointer to the person who used emote.
 *                adverb - Option string describing adverbs to the
 *                         emote.
 * Returns      : n/a
 */
public varargs void
emote_hook(string emote, object actor, string adverb = 0)
{
    switch(emote)
    {
        case "kick":
        case "slap":
        case "poke":
        case "snarl":
            set_alarm(1.0, 0.0, &react_offend(actor));
            break;
        case "greet":
        case "bow":
            set_alarm(1.0, 0.0, &return_greet(actor));
            break;
    }
}

/*
 * Function name: react_offend
 * Description  : A nice little reaction to a handful of offensive
 *                emotes performed on the dragon. Called by emote_hook
 *                when necessary.
 * Arguments    : actor - Object pointer to the player who did the
 *                        emote.
 * Returns      : n/a
 */
public void
react_offend(object actor)
{
    if (!present(actor, environment()))
        return;

    tell_room(environment(), QCTNAME(TO) + " gives a snort, " +
        "and with an almost casual flick of his tail, " +
        "sends " + QTNAME(actor) + " reeling backwards into " +
        "a pool!\n", ({actor}));
    actor->catch_msg(QCTNAME(TO) + " gives a snort, and " +
        "with an almost casual flick of his tail, sends " +
        "you reeling backwards into a pool!\n");
    tell_room(environment(), "SPLASH!\n");
    command("say Mind thy manners, " + query_rem_name(actor));
    command("chuckle .");
    command("say I'd hate to have to hurt thee.");
}

/*
 * Function name: return_greet
 * Description  : Returns the 'greet' emote.
 * Arguments    : actor - Object pointer to the player who greeted
 *                        the dragon.
 * Returns      : n/a
 */
public void
return_greet(object actor)
{
    string temp;

    if (!present(actor, environment()))
        return;

    temp = "Well met, ";

  /* Different response depending on whether or not the player */
  /* has introduced. */
    if (member_array(actor->query_real_name(), remembered) < 0)
    {
        temp += ({"sir", "lady", ""})[actor->query_gender()];
        temp += " " + actor->query_race();
    }
    else
    {
        temp += capitalize(actor->query_real_name());
    }

    command("emote rumbles: " + temp);
}

/*
 * Function name: init_living (MASK)
 * Description  : Called when this object meets another object.
 *                Used here to initialize the custom actions.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
init_living()
{
    ::init_living();
    if (!get_alarm(act_alarm))
       init_firestorm_acts();
}

/*
 * Function name: init_firestorm_acts
 * Description  : Starts the custom act routine running.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
init_firestorm_acts()
{
    next_firestorm_act(0);
}

/*
 * Function name: next_firestorm_act
 * Description  : Delivers the next action in the sequence.
 * Arguments    : i - Integer representing which action to
 *                    perform.
 * Returns      : n/a
 */
public void
next_firestorm_act(int i)
{
  /* Stop acting if nobody is in the room. */
    if (!sizeof(FILTER_OTHER_LIVE(all_inventory(environment()))))
        return;

  /* 'wraparound' for looping actions. */
    if (i > 6)
        i = 0;

    switch(i)
    {
        case 0:
            command("emote rises and stretches out its wings " +
                "full width.");
            break;
        case 1:
            command("emote glances casually over the surroundings.");
            break;
        case 2:
            command("emote suddenly cocks his head to one " +
                "side, and his eyes narrow to slits, as if " +
                "listening to, or for, something.");
            break;
        case 3:
            command("emote suddenly shakes his head lightly, " +
              "as if dismissing some notion.");
            break;
        case 4:
            command("emote casually reaches up to his jaws " +
                "with a razor sharp talon and dislodges a large " +
                "bone from between his teeth.");
            break;
        case 5:
            command("emote careful begins inspecting his scales " +
                "for signs of damage.");
            break;
        case 6:
            if (!query_prop(DRAGON_S_WAS_RELEASED))
                command("emote glares balefully at the sturdy " +
                    "chain holding his hind leg in place.");
            else
                command("emote inspects some raw spots on one " +
                    "of his hind legs, where a few scales " +
                    "seem to have been torn off.");
            break;
    }

    act_alarm = set_alarm(itof(random(60)) + 30.0, 
        0.0, &next_firestorm_act(++i));
}

/*
 * Function name: head_for_palace
 * Description  : This is the 'trigger' function to start Firestorm
 *                towards the crystal palace in the event of a Kroug
 *                attack. As of creation, this is still undecided as
 *                to whether or not to be implemented, but the code
 *                is included for now anyway, even though it's not
 *                used. Note the dragon will only be able to leave
 *                if he has been unchained. In this first part, if
 *                the dragon is able to leave, he is moved into a
 *                temporary underwater room.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
head_for_palace()
{
    command("emote suddenly jerks his head up, as if called " +
        "by an unheard voice.");

    if (!query_prop(DRAGON_S_WAS_RELEASED))
    {
        command("emote rattles the chains shackling him down " +
            "furiously, but to no avail.");
        command("emote raises his head and bellows a horrible " +
        "roar of frustration!");
        return;
    }

    command("emote rumbles: I am needed elsewhere.");
    tell_room(environment(), QCTNAME(TO) + " races with amazing " +
        "speed across the floor of the grotto and dives into " +
        "the waters of the underground lake so swiftly it barely " +
        "forms ripples on the surface, let alone a splash.\n");
    move_living("M", SPECIAL + "water_temp");
    tell_room(environment(), QCTNAME(TO) + " swims swiftly " +
        "into the water from the east.\n");
    set_alarm(60.0, 0.0, second_stop_to_palace);
}

/*
 * Function name: second_stop_to_palace
 * Description  : The second function in the alarmed sequence to have
 *                Firestorm assist the Calians during a Kroug raid.
 *                Here Firestorm moves from the temporary water room
 *                to a temporary air room.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
second_stop_to_palace()
{
    object *temp;

    tell_room(environment(), QCTNAME(TO) + " surges westwards " +
        "through the water.\n");
    ({MOUNT + "mshore1",MOUNT + "mshore2", MOUNT + "mshore3"})->load_me();
    temp = FILTER_LIVE(all_inventory(find_object(MOUNT + "mshore1")));
    temp += FILTER_LIVE(all_inventory(find_object(MOUNT + "mshore2")));
    temp += FILTER_LIVE(all_inventory(find_object(MOUNT + "mshore3")));
    if (sizeof(temp))
        temp->catch_msg("Suddenly, the water near the shore " +
            "explodes in a shower of spray, and from beneath " +
            "its surface emerges " + QNAME(TO) + ", his " +
            "wings pounding furiously as he gains altitude and " +
            "vanishes through the mist and clouds above you, " +
            "headed towards Mount Kyrus.\n");

    move_living("M", SPECIAL + "air_temp");
}

/*
 * Function name: react_freedom
 * Description  : The final reaction of the dragon when he's been
 *                freed of his chains.
 * Arguments    : who - Object pointer to the player who managed
 *                      to break the chain.
 * Returns      : n/a
 */
public void
react_freedom(object who, object chain)
{
    string name;
    object *others,
           *fresh;
    int i;

    others = filter((chain->query_damagers()), is_calian);
    others -= ({who});

    name = lower_case(who->query_real_name());

    command("emote roars victoriously as his chains fall away, " +
        "and he stretches to his full height!");
    command("grin " + name);
    command("emote rumbles: " + capitalize(name) + ", you have " +
        "done me a great service this day.");

    if (sizeof(others))
    {
        if (sizeof(others) == 1)
        {
            command("emote rumbles: You and your companion.");
        }
        else if (sizeof(others) > 1)
        {
            command("emote rumbles: You and your companions.");
        }
    }

    if (is_calian(who))    
        fresh = filter(others + ({who}), &not() @ &->test_bit("Calia",
            ELDORAL_QUEST_GROUP, ELDORAL_GURU_QUEST_BIT));
    else
        fresh = filter(others, &not() @ &->test_bit("Calia",
            ELDORAL_QUEST_GROUP, ELDORAL_GURU_QUEST_BIT));

    if (!sizeof(fresh) && sizeof(others))
    {
        command("emote rumbles: But I see you have all aided me " +
            "before, there is nothing more than I can do for " +
            "any of you, except thank you all once again.");
        command("emote lowers his head in solemn acknowledgement.");
        return;
    }

    if (!sizeof(fresh) && !sizeof(others))
    {
        command("emote rumbles: But I see you have already aided " +
            "me once, and I can do nothing more than thank you " +
            "once again.");
        command("emote lowers his head in solemn acknowledgement.");
        return;
    }

    if (sizeof(fresh) && !sizeof(others))
    {
        command("emote rumbles: For this, I will grant you a " +
            "special gift.");
    }

    if (sizeof(fresh) && sizeof(others))
    {
        command("emote rumbles: For this, I will grant you all " +
            "a special gift.");
    }

    tell_room(environment(), QCTNAME(TO) + " stares deeply into " +
        "your eyes, and you begin to feel a strange new sense " +
        "of awareness, of skill, of ability to learn. As odd " +
        "as it seems, you feel able to now learn a heightened " +
        "degree of prowess in combat!\n",
        all_inventory(environment()) - fresh);
    command("emote rumbles: I believe thou hast some training " +
        "to do. Good luck, warriors. My thoughts shall be with " +
        "thee, and I shall do what I can to aid thee when " +
        "I can.");

    seteuid(getuid());

    for (i = 0; i < sizeof(fresh); i++)
    {
        BITMASTER->set_bit(ELDORAL_GURU_QUEST_BIT, fresh[i]);
    }
    add_prop(DRAGON_S_WAS_RELEASED, who->query_real_name());

    /* Reset the chain (and crypts) in 4 hrs. */
    set_alarm(14400.0, 0.0, reset_chain);
    return;
}

/*
 * Function name: react_to_eye
 * Description  : Figures out whether or not to reward the player
 *                who just gave us the eye of the beast.
 * Arguments    : ob - Object pointer to the object we received,
 *                     presumably the eye.
 *                who - Object pointer to the player who gave it
 *                      to us.
 * Returns      : n/a
 */
public void
react_to_eye(object ob, object who)
{
  /* Do nothing if 'who' isn't in the room. */
    if (!who || !present(who, environment()))
        return;

  /* Make sure the person who gave the dragon the eye is  */
  /* the one who killed the beast. */
    command("emote examines the green eye very carefully.");
    if (who->query_real_name() != ob->query_killer())
    {
        command("emote rumbles: Very impressive. Even more "+
            "impressive would it be were you the one who slew " +
            "the beast.");
        command("growl");
        return;
    }

    command("emote rumbles: An impressive feat, this is indeed " +
        "the Eye of the Beast. Well done!");

    seteuid(getuid());

    BITMASTER->set_bit(ELDORAL_BEAST_QUEST_BIT, who);
}

/*
 * Function name: show_hook
 * Description  : Allows players to show the eye to Firestorm
 *                instead of giving it to him.
 * Arguments    : what - Object pointer to what the player
 *                       showed him.
 * Returns      : n/a
 */
public void
show_hook(object what)
{
    if (what->id(ELDORAL_BEAST_EYE_NAME))
        set_alarm(0.0, 0.0, &react_to_eye(what, TP));
}

/*
 * Function name: enter_inv (MASK)
 * Description  : Called when another item enters our inventory.
 *                Used here to try and figure out when we've been
 *                given the eye of the beast from the quest with
 *                the same name.
 * Arguments    : ob - Object pointer to object entering our inventyr.
 *                from - Object pointer to 'ob's last environment.
 * Returns      : n/a
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!ob->id(ELDORAL_BEAST_EYE_NAME))
        return;

  /* Ok, it looks like we've been given the eye of the beast. */
  /* 'from' _should_ point to the player who gave it to us. */
    if (!from || !interactive(from))
        return;

    set_alarm(0.0, 0.0, &react_to_eye(ob, from));
}
