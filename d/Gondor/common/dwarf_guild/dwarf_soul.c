/*
 * /d/Gondor/common/dwarf_guild/dwarf_soul.c
 *
 * Copyright (C) Mercade @ Genesis - November 3 1993
 *
 * This is the soul for the dwarven race guild, the Rockfriend Guild! It
 * contains all emotions and other commands members of the guild can perform.
 * The Rockfriend guild was the first guild in Genesis to be "frozen", meaning
 * that it was finished. However, on occasion I like to add some new emotes.
 */

#pragma no_clone
#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/cmd/std/command_driver";

#include "dwarf.h"
#include <adverbs.h>
#include <cmdparse.h>
#include <const.h>
#include <composite.h>
#include <files.h>
#include <filter_funs.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>

#define CHECK_BELT   \
    if (!belt_ok())  \
    {                \
        return 0;    \
    }

#define W_ANYWEAPON     -1  /* This includes all allowed weapon types like W_AXE, W_SWORD etc. */
#define W_AXE_OR_CLUB   -2  /* This includes only axes and clubs. */
#define W_NOT_WIELDED    0  /* not necessarily that the weapon is wielded */
#define W_WIELDED        1  /* necessarily that the weapon is wielded */
#define WIELD_LOCATIONS ({ W_RIGHT, W_BOTH, W_LEFT }) /* the possible locations to wield an axe */

#define SHORT(o)        (o)->check_call((o)->short())
#define SOULDESC(s)     this_player()->add_prop(LIVE_S_SOULEXTRA, (s))

#define LIVE_I_WAS_LAST_BEARHUGGED "_live_i_was_last_bearhugged"
#define LIVE_I_LAST_BEARHUGGED     "_live_i_last_bearhugged"
#define BEARHUG_TIME_ARMS_RELAX    30
#define BEARHUG_TIME_VICTIM_RELAX  60
#define BEARHUG_EXTRA_SS_STR \
    (min((max((75 - TP->query_average_stat()), 0)), 25))
#define BEARHUG_MAXIMUM_HP_LOSS    25
#define MINIMUM_SKILL_TO_SHOW_OFF  20
#define MINIMUM_SKILL_TO_FRIGHTEN  10
#define TWO_THIRD(i)               ((((i) * 2) + random(2 * (i))) / 3)
#define THREE_QUARTER(i)           ((((i) * 3) + random(2 * (i))) / 4)

/* The help topics that exist. */
#define HELP_CATEGORIES ({ "rf", "rockfriend", "rockfriends" })
#define HELP_TOPICS ({ "beards", "belt", "commands", "help", "levels" })

/* Some synonyms for the handle of an axe. */
#define HANDLE_SYNONYMS ({ "grip", "haft", "handle", "helve", "hilt" })

/* The array SHOW_OFF_DIFF_LEVELS has one entry less than the array
 * SHOW_OFF_REACTIONS. The last entry will be displayed if the difference
 * is larger than 70.
 */
#define SHOW_OFF_SIZE_DIFF_LEVELS    8
#define SHOW_OFF_DIFF_LEVELS       ({ -70, -50, -30, -10, 10, 30, 50, 70 })
#define SHOW_OFF_REACTIONS         ({         \
    "laughing at the poor skill displayed",   \
    "not impressed at all",                   \
    "amused by the miserable effort",         \
    "just a little better in the skill",      \
    "capable of doing the same stunts",       \
    "amazed by the moves performed",          \
    "rather impressed by the moves",          \
    "astonished by the demonstration",        \
    "completely flabbergasted by such talent" \
    })

#define GRIP_RANDOM_MESSAGES 2
#define GRIP_EMOTE_ACTOR_MESSAGES ({ \
    "You take a firm grip on your ", \
    "You tighten the grip on your " })
#define GRIP_EMOTE_ONLOOKER_MESSAGES ({ \
    " takes a firm grip on ", \
    " tightens the grip on " })

#define FRIGHTEN_SIZE_DISTANCE_LEVELS 8
#define FRIGHTEN_DISTANCE_LEVELS   ({ 10, 20, 30, 45, 60, 75, 85, 95 })
#define FRIGHTEN_DISTANCES         ({ \
    "almost a meter",                 \
    "more than half a meter",         \
    "nearly half a meter",            \
    "roughly a foot",                 \
    "approximately half a foot",      \
    "several inches",                 \
    "a little more than an inch",     \
    "only a centimeter",              \
    "a hair's-breadth"                \
    })

#define FRIGHTEN_SIZE_REACTION_LEVELS 11
#define FRIGHTEN_REACTION_LEVELS      \
    ({ -80, -60, -40, -20, 0, 15, 30, 45, 60, 75, 85 })
#define FRIGHTEN_REACTIONS_ME      ({ \
    "are terrified to death",         \
    "cry out in terror",              \
    "panic and freak out",            \
    "stagger in mortal fear",         \
    "tremble in agony",               \
    "freeze in complete shock",       \
    "pull away from fear",            \
    "turn a little pale",             \
    "only blink an eye",              \
    "smile without fear",             \
    "are not intimidated at all",     \
    "show no reaction at all"         \
    })
#define FRIGHTEN_REACTIONS_OTHERS  ({ \
    "is terrified to death",          \
    "cries out in terror",            \
    "panics and freaks out",          \
    "staggers in mortal fear",        \
    "trembles in agony",              \
    "freezes in complete shock",      \
    "pulls away from fear",           \
    "turns a little pale",            \
    "only blinks an eye",             \
    "smiles without fear",            \
    "is not intimidated at all",      \
    "shows no reaction at all"        \
    })

#define SWIG_FAIL_ALCO "_alco_"
#define SWIG_FAIL_SOFT "_soft_"
#define SWIG_SIZE_FAIL_LEVELS 9
#define SWIG_ALCO_FAIL_LEVELS \
    ({ 5, 10, 15, 20, 25, 30, 35, 40, 45 })
#define SWIG_ALCO_FAIL_MESSAGES_ME ({                               \
    "You must be as blasted as a Rockfriend can possibly be",       \
    "Being obliviated gets a new meaning",                          \
    "You miserably fail to uphold yourself as Rockfriend",          \
    "One might wonder whether too much alcohol is indeed possible", \
    "You pretend not to be interested in another drink",            \
    "You look around and hope no-one notices",                      \
    "Your throat refuses to function",                              \
    "You seem to try to drink outside your league",                 \
    "You look like you are about to vomit",                         \
    "Maybe you should try something less strong"                    \
    })
#define SWIG_ALCO_FAIL_MESSAGES_OTHERS ({                                 \
    " must be as blasted as a Rockfriend can possibly be",                \
    " gives being obliviated a new meaning",                              \
    " miserably fails to uphold " + OBJECTIVE(TP) + "self as Rockfriend", \
    " wonders whether too much alcohol is indeed possible",               \
    " pretends not to be interested in another drink",                    \
    " looks around, hoping that no-one notices",                          \
    "'s throat refuses to function",                                      \
    " seems to try to drink outside " + POSSESSIVE(TP) + " league",       \
    " looks like " + PRONOUN(TP) + " is about to vomit",                  \
    " should perhaps try something less strong"                           \
    })
#define SWIG_DRINK_LEVELS 10
#define SWIG_DRINK_VERBS_ME ({        \
    " nurse ",                        \
    " sip at ",                       \
    " swallow ",                      \
    " tilt your head back and pour ", \
    " swill ",                        \
    " gulp down ",                    \
    " shoot ",                        \
    " bolt down ",                    \
    " guzzle ",                       \
    " pound back ",                   \
    })
#define SWIG_DRINK_VERBS_OTHERS ({                        \
    " nurses ",                                           \
    " sips at ",                                          \
    " swallows ",                                         \
    " tilts " + POSSESSIVE(TP) + " head back and pours ", \
    " swills ",                                           \
    " gulps down ",                                       \
    " shoots ",                                           \
    " bolts down ",                                       \
    " guzzles ",                                          \
    " pounds back ",                                      \
    })
#define SWIG_DRINK_SUFFIX_ME ({             \
    " until it is finally gone",            \
    " to make the most of just two drinks", \
    ", yearning for more",                  \
    " down your throat",                    \
    "", \
    "", \
    "", \
    "", \
    "", \
    "", \
    })
#define SWIG_DRINK_SUFFIX_OTHERS ({         \
    " until it is finally gone",            \
    " to make the most of just two drinks", \
    ", yearning for more",                  \
    " down " + POSSESSIVE(TP) + " throat",  \
    "", \
    "", \
    "", \
    "", \
    "", \
    "", \
    })
#define SWIG_DRINK_RANDOM_LEVELS 5
#define SWIG_DRINK_RANDOM_MESSAGES ({ \
    " as quickly as possible",        \
    ", one at a time",                \
    ", one by one",                   \
    " until they are all gone",       \
    ", yearning for more",            \
    })

#define SWING_SIZE_DIFF_LEVELS  6
#define SWING_DIFF_LEVELS       ({ 15, 30, 45, 60, 75, 90 })

#define THIRSTY_DEFAULT_MAX 8
#define THIRSTY_DEFAULT_RANGE 9
#define THIRSTY_LEVELS ({ \
    "slightly",           \
    "somewhat",           \
    "mildly",             \
    "normal",             \
    "quite",              \
    "very",               \
    "awfully",            \
    "desperately",        \
    "dwarflike"           \
    })
#define THIRSTY_SEE_SELF ({   \
    "fondly remember you just had a nice drink.", \
    "methodically check your surroundings for beer.", \
    "get that delightful urge to have another drink.", \
    "emit your normal \"Yes, a beer would be nice\" feeling.", \
    "look like you could use another mindblasting brew.", \
    "get a slightly desperate expression on your face, caused by a precarious lack of beer.", \
    "reach your critical fifteen-minutes-without-beer level.", \
    "exclaim: A brew, a brew, my axe for a BREW!", \
    "feel like you could murder for a beer ... or half a dozen beers, for that matter." \
    })
#define THIRSTY_SEE_OTHERS ({ \
    "fondly remembers " + PRONOUN(TP) + " just had a nice drink.", \
    "methodically checks " + POSSESSIVE(TP) + " surroundings for beer.", \
    "gets that delightful urge to have another drink.", \
    "emits " + POSSESSIVE(TP) + " normal \"Yes a beer would be nice\" feeling.", \
    "looks like " + PRONOUN(TP) + " could use another mindblasting brew.", \
    "gets a slightly desperate expression on " + POSSESSIVE(TP) + " face, probably caused by a precarious lack of beer.", \
    "reaches " + POSSESSIVE(TP) + " critical fifteen-minutes-without-beer level.", \
    "exclaims: A brew, a brew, my axe for a BREW!", \
    "seems to feel like " + PRONOUN(TP) + " could murder for a beer ... or half a dozen beers, for that matter.", \
    })

#define DEBUG(s) find_player("mercade")->catch_msg(s);

/****************************************************************************
 * Global variables
 */
private static string *show_off_reactions = SHOW_OFF_REACTIONS;
private static string *handle_synonyms = HANDLE_SYNONYMS;

/****************************************************************************
 * Return a proper name of the soul in order to get a nice printout.
 */
string
get_soul_id()
{
    return "rockfriend";
}

/****************************************************************************
 * Identify this as a command soul.
 */
int
query_cmd_soul()
{
    return 1;
}

/****************************************************************************
 * The list of verbs and functions. Please add new in alphabetical order.
 */
mapping
query_cmdlist()
{
    return ([
              "attack"      : "attack",

              "bearhug"     : "bearhug",
              "bonk"        : "bonk",

              "calm"        : "calm",
              "chew"        : "chew",
              "cont"        : "contemplate", /* for lazy people and for me */
              "contemplate" : "contemplate",
              "curse"       : "curse",

              "florish"     : "florish",
              "frighten"    : "frighten",

              "goldsearch"  : "goldsearch",
              "greed"       : "greed",
              "grip"        : "grip",
              "guffaw"      : "guffaw",

              "hail"        : "hail",
              "hmph"        : "hmph",

              "inspect"     : "inspect",

              "list"        : "list",

              "preen"       : "preen",
              "polish"      : "polish",
              "promise"     : "promise",

              "quiver"      : "quiver",

              "rage"        : "rage",
              "rebraid"     : "rebraid",
              "revenge"     : "revenge",
              "rf"          : "rf",

              "show"        : "show",
              "shun"        : "shun",
              "silence"     : "silence",
              "stroke"      : "stroke",
              "swig"        : "swig",
              "swing"       : "swing",

              "thirsty"     : "thirsty",
              "toast"       : "toast",
              "tug"         : "tug",
              "twist"       : "twist",
           ]);
}

/****************************************************************************
 * Below this delimiter I placed some support functions and filter functions.
 * To avoid the use of prototypes, they are all placed before the actual
 * functions.
 */

/*
 * Function name: weapon_matches_type
 * Description  : This is a filter function that returns whether the object
 *                is the right type of weapon. Allows W_ANYWEAPON and
 *                W_AXE_OR_CLUB.
 * Arguments    : object obj - the object to check
 *                int type   - the type of weapon requested
 * Returns      : int - 1 if the object is as requested, else 0
 */
private int
weapon_matches_type(object weapon, int type)
{
    if (!IS_WEAPON_OBJECT(weapon))
    {
        return 0;
    }

    switch(type)
    {
    case W_ANYWEAPON:
        return 1;

    case W_AXE_OR_CLUB:
        return IN_ARRAY(weapon->query_wt(), ({ W_AXE, W_CLUB }) );

    default:
        return (weapon->query_wt() == type); 
    }
}

/*
 * Function name: any_wielded_weapon
 * Description  : This function can be used to find any wielded weapon or
 *                axe on a Rockfriend.
 * Arguments    : int type - the weapon type of the weapon to select.
 * Returns      : object - a wielded weapon or axe.
 */
varargs private object
any_wielded_weapon(int type = W_ANYWEAPON)
{
    object weapon;

    foreach(int wieldloc: WIELD_LOCATIONS)
    {
        if (objectp(weapon = TP->query_weapon(wieldloc)) &&
            weapon_matches_type(weapon, type))
        {
            return weapon;
        }
    }

    return 0;
}

/*
 * Function name: carried_or_wielded_by_this_player
 * Description  : This is a filter function that returns whether TP carries
 *                the object and can see the object. If wielded is set to
 *                W_WIELDED, the object will have to be wielded as well to be
 *                selected.
 * Arguments    : object obj  - the object to check
 *                int wielded - if set to W_WIELDED the object should also be
 *                    a wielded object.
 * Returns      : int - 1 if the player has the object, else 0
 */
private int
carried_or_wielded_by_this_player(object obj, int wielded)
{
    return ((ENV(obj) == TP) && CAN_SEE(TP, obj) &&
        ((wielded == W_WIELDED) ? objectp(obj->query_wielded()) : 1));
}

/*
 * Function name: parse_weapon
 * Description  : This function returns the objectpointer to one single
 *                weapon or axe. Give W_ANYWEAPON if you want any kind of
 *                weapon or W_AXE to only get an axe. Also you can specify
 *                whether the weapon wanted should be wielded or may be
 *                unwielded as well, use W_NOT_WIELDED and W_WIELDED for
 *                that.
 * Arguments    : string str      - whatever text needs to be parsed
 *                string pattern  - the search pattern
 *                int weapon_type - the type of the weapon requested
 *                int be_wielded  - whether the weapon should also be wielded
 * Returns      : object - the objectpointer to the weapon/axe
 */
varargs private object
parse_weapon(string str, string pattern, int weapon_type = W_ANYWEAPON,
    int be_wielded = W_NOT_WIELDED)
{
    object *oblist;

    if (!strlen(str))
    {
        return any_wielded_weapon(weapon_type);
    }

    parse_command(LOW(str), TP, pattern, oblist);

    oblist = NORMAL_ACCESS(oblist, 0, 0);

    oblist = filter(oblist,
        &carried_or_wielded_by_this_player(, be_wielded));

    oblist = filter(oblist, &weapon_matches_type(, weapon_type));

    if (!sizeof(oblist))
    {
        return 0;
    }

    return oblist[0];
}

/*
 * Function name: belt_ok
 * Description  : This function checks whether the player is entitled to
 *                execute the command he wants to execute. An NPC can always
 *                execute the command, however, a player (mortal or wizard)
 *                can only execute the command if he is wearing his/her belt.
 * Returns      : int 1/0 - true if the belt is oke ;-)
 */
private int
belt_ok()
{
    object arm;

    /* NPC's always have their belt, even when they don't have it. */
    if (this_player()->query_npc())
    {
        return 1;
    }

    /* If you are not wearing your belt, the Rockfriend commands cannot
     * be executed and a fail message is not given in order not to mess
     * previous 'notify_fail's. However, when the player carries the belt
     * and the Rockfriend command is forced through "rf", do continue.
     */
    arm = (object)this_player()->query_armour(A_WAIST);
    if (!objectp(arm) ||
        !arm->id(DWARVEN_RACE_GUILD_BELT_ID))
    {
        if ((query_verb() != "rf") ||
            !objectp(arm = present(DWARVEN_RACE_GUILD_BELT_ID, this_player())))
        {
            return 0;
        }
    }

    if (arm->query_owner_name() != this_player()->query_real_name())
    {
        notify_fail("Your name is not branded in your belt. Go see Borin, " +
            "the smith of the " + DWARVEN_RACE_GUILD_NAME + " and get him " +
            "to fix it.\n");
        return 0;
    }

    return 1;
}

/*
 * Function name: beard_description
 * Description  : This will give the beard description for any Rockfriend.
 *                It will parse the player's adjectives and check the level
 *                of the Rockfriend in the guild. For female members, it will
 *                make the description as whiskers.
 * Arguments    : object player - the member to get the description for.
 * Returns      : string - the beard/whiskers description.
 */
private string
beard_description(object player)
{
    string level;

    return (strlen(level = player->query_rockfriend_beard_description()) ?
        (level + " ") : "") +
        (player->query_age() > SILVER_BEARD_AGE ? "silvery " : "") +
        ((player->query_gender() == G_FEMALE) ? "whiskers" : "beard");
}

/*
 * Function name: dwarven_god
 * Description  : Returns the name for the Dwarven God dependant on whether
 *                the player (previous_object()) is a dwarf or not.
 * Returns      : string - the proper name.
 */
public string
dwarven_god()
{
    if (previous_object(-1)->query_race() == "dwarf")
    {
        return "Mahal";
    }

    return "Aule, the God of all Dwarves,";
}

/****************************************************************************
 * Below this line come the actual functions. Please do add new functions in
 * alphabetical order and put service functions before the actual function
 * in order to minimize the number of prototypes.
 */

/****************************************************************************
 * Attack - Attack someone after crying the Dwarven battlecry.
 */
int
attack(string str)
{
/*
 * This should just return the normal kill command with the addition of
 * a battlecry! However, it needs to be piffed up a little.
 */

    CHECK_BELT;

    /* The battlecry is: Baruk Khazad! Khazad aimenu!
     * Axes of the Dwarves! The Dwarves are upon you!
     */
    write("You cry out: Baruk Khazad! Khazad aimenu!\n");
    all(" cries out: Baruk Khazad! Khazad aimenu!");

    /* If you only want to cry the battlecry, we stop here. However, in order
     * not to interfere with other possible attack commands, we return 0,
     * but then without setting a notify_fail.
     */
    if (!strlen(str))
    {
        notify_fail("");
        return 0;
    }

    return CMD_LIVE_SOCIAL->kill(str);
}

/****************************************************************************
 * Bearhug - Give someone a really big hug. It may actually hurt slightly.
 */
int
bearhug(string str)
{
    object *oblist;
    int    damage;

    CHECK_BELT;

    if (((TP->query_prop(LIVE_I_LAST_BEARHUGGED) +
            BEARHUG_TIME_ARMS_RELAX) > time()) &&
        !(TP->query_wiz_level()))
    {
        notify_fail("You have to give your arms some rest before you can " +
            "give someone a bearhug again.\n");
        return 0;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Give whom a bearhug?\n");
        return 0;
    }

    if (sizeof(oblist) != 1)
    {
        notify_fail("Please select one person to give a bearhug to at a " +
            "time.\n");
        return 0;
    }

    /* Cannot hug an enemy :-) */
    if ((member_array(TP, oblist[0]->query_enemy(-1)) != -1) ||
        (member_array(oblist[0], TP->query_enemy(-1)) != -1))
    {
        notify_fail("Fighting " + oblist[0]->query_the_name(TP) +
            " until death follows and hugging " + OBJECTIVE(oblist[0]) +
            " at the same time is a little contradicting, wouldn't you " +
            "agree?\n");
        return 0;
    }

    if (((oblist[0]->query_prop(LIVE_I_WAS_LAST_BEARHUGGED) +
            BEARHUG_TIME_VICTIM_RELAX) > time()) &&
         !(oblist[0]->query_wiz_level()))
    {
        notify_fail("It looks like " + oblist[0]->query_the_name(TP) +
            " still has to recover from a previous hug. Better not hug " +
            OBJECTIVE(oblist[0]) + " so soon again.\n");
        return 0;
    }

    damage = MIN((TP->query_stat(SS_STR) + BEARHUG_EXTRA_SS_STR -
        ((oblist[0]->query_stat(SS_STR) +
        oblist[0]->query_stat(SS_CON) + 1) / 2)), BEARHUG_MAXIMUM_HP_LOSS);

    TP->add_prop(LIVE_I_LAST_BEARHUGGED, time());
    oblist[0]->add_prop(LIVE_I_WAS_LAST_BEARHUGGED, time());

    if (damage < 1)
    {
        target(" gives you a real bearhug. Luckily " + PRONOUN(TP) +
            " does not harm you.", oblist);
        actor("You give", oblist, " a bearhug. Luckily you do not harm " +
            OBJECTIVE(oblist[0]) + ".");
        all2act(" gives", oblist, " a bearhug. Luckily " + PRONOUN(TP) +
            " does not harm " + OBJECTIVE(oblist[0]) + ".");

        return 1;
    }

    target(" gives you a bearhug. " + CAP(PRONOUN(TP)) + " does that so " +
        "fiercefully that you temporarily cannot breathe and you feel you " +
        "turn a little blue.", oblist);
    actor("You give", oblist, " a bearhug. You do that so fiercefully that " +
        PRONOUN(oblist[0]) + " temporarily cannot breathe and " +
        PRONOUN(oblist[0]) + " turns a little blue.");
    all2act(" gives", oblist, " a bearhug and does that so fiercefully that " +
        PRONOUN(oblist[0]) + " temporarily cannot breathe and " +
        PRONOUN(oblist[0]) + " turns a little blue.");

    oblist[0]->heal_hp(-(damage));
    if (oblist[0]->query_hp() <= 0)
    {
        oblist[0]->do_die(TP);
    }

    return 1;
}

/****************************************************************************
 * Bonk - Bonk someone on the head with an axe you carry.
 */
int
bonk(string str)
{
    object *oblist;
    string player_str;
    object weapon;
    string weapon_str;

    CHECK_BELT;

    if (!strlen(str))
    {
        notify_fail("Bonk whom with which axe or club?\n");
        return 0;
    }

    if (sscanf(str, "%s with %s", player_str, weapon_str) != 2)
    {
        notify_fail("Bonk whom with which axe or club?\nSyntax: bonk <target> " +
            "with <axe>\n");
        return 0;
    }

    weapon = parse_weapon(weapon_str, "[the] %i", W_AXE_OR_CLUB);
    if (!objectp(weapon))
    {
        notify_fail("Which axe or club do you wish to use to bonk with?\n");
        return 0;
    }

    oblist = parse_this(player_str, "[the] %l");
    switch(sizeof(oblist))
    {
    case 0:
        notify_fail("Who do you want to bonk?\n");
        return 0;

    case 1:
        break;

    default:
        notify_fail("You can only bonk one person at a time.\n");
        return 0;
    }

    str = one_of_list(handle_synonyms);
    actor("You bonk", oblist, " on the head with the " + str + " of your " +
        SHORT(weapon) + ".");
    target(" bonks you on the head with the " + str + " of " +
        POSSESSIVE(TP) + " " + SHORT(weapon) + ".", oblist);
    all2actbb(" bonks", oblist, " on the head with the " + str + " of " +
        POSSESSIVE(TP) + " " + SHORT(weapon) + ".");

    return 1;
}

/****************************************************************************
 * Calm - Motion someone to be calm.
 */
int
calm(string str)
{
    object *oblist;

    CHECK_BELT;

    if (!stringp(str))
    {
        SOULDESC("motioning people to be calm");
        write("You gesture downwards with the palms of your hands, " +
            "motioning everybody in the room to calm down.\n");
        allbb(" gestures downwards with the palms of " +
            this_player()->query_possessive() + " hands, motioning " +
            "everybody in the room to calm down.");
        return 1;
    }

    oblist = parse_this(str, "[to] [the] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Motion to whom to be calm?\n");
        return 0;
    }

    str = ((sizeof(oblist) == 1) ? oblist[0]->query_objective() : "them");

    SOULDESC("motioning for calmness");
    actor("You gesture downwards with the palms of your hands towards",
        oblist, ", motioning " + str + " to calm down.");
    all2act(" gestures downards with the palms of " +
        this_player()->query_possessive() + " hands towards", oblist,
        ", motioning " + str + " to be calm.");
    target(" gestures downwards with the palms of " +
        this_player()->query_possessive() + " hands, motioning you to be " +
        "calm.", oblist);
    return 1;
}

/****************************************************************************
 * Chew - Chew on your beard/whiskers when you are nervous.
 */
int
chew(string str)
{
    string beard;

    CHECK_BELT;

    str = check_adverb_with_space(str, "unintentionally");
    beard = beard_description(TP);

    if (str == NO_ADVERB_WITH_SPACE)
    {
        notify_fail("Chew how on your " + beard + "?\n");
        return 0;
    }

    write("Trying to control your temper, you" + str + " chew on your " +
        beard + ".\n");
    say("Trying to control " + POSSESSIVE(TP) + " temper, " + QTNAME(TP) +
        str + " chews on " + POSSESSIVE(TP) + " " + beard + ".\n");

    return 1;
}

/****************************************************************************
 * Contemplate - Rub your beard/whiskers in contemplation.
 */
int
contemplate(string str)
{
    string beard;

    CHECK_BELT;

    if (strlen(str))
    {
        notify_fail("Contemplate what?\n");
        return 0;
    }

    beard = beard_description(TP);

    write("You rub your " + beard + " in contemplation.\n");
    allbb(" rubs " + POSSESSIVE(TP) + " " + beard + " in contemplation.");

    return 1;
}

/****************************************************************************
 * Curse - Call the wrath of Mahal over someone.
 */
int
curse(string str)
{
    object *oblist;

    CHECK_BELT;

    if (!strlen(str))
    {
        write("You call the wrath of Mahal upon those incompetent fools " +
            "that bring harm to you.\n");
        say(QCTNAME(TP) + " calls the wrath of @@dwarven_god:" +
            DWARVEN_RACE_GUILD_SOUL + "@@ upon those incompetent fools that " +
            "cause " + OBJECTIVE(TP) + " harm.\n");
        return 1;
    }

    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Curse at whom?\n");
        return 0;
    }

    actor("You call the wrath of Mahal over", oblist);
    tell_room(environment(this_player()), QCTNAME(this_player()) +
        " calls the wrath of @@dwarven_god:" + DWARVEN_RACE_GUILD_SOUL +
        "@@ over " +
        (living(oblist[0]) ? desc_many(oblist) : COMPOSITE_DEAD(oblist)) +
        ".\n", ({ this_player() }) + oblist);
    oblist->catch_msg(QCTNAME(this_player()) +
        " calls the wrath of @@dwarven_god:" + DWARVEN_RACE_GUILD_SOUL +
        "@@ over you.\n");

    return 1;
}

/****************************************************************************
 * Florish - Florish a weapon you wield.
 */
int
florish(string str)
{
    object weapon;

    CHECK_BELT;

    weapon = parse_weapon(str, "[the] %i", W_ANYWEAPON, W_WIELDED);

    if (!objectp(weapon))
    {
        notify_fail("Which weapon do you wish to florish?\n");
        return 0;
    }

    write("You sweep your " + SHORT(weapon) + " through the air.\n");
    allbb(" sweeps " + POSSESSIVE(TP) + " " + SHORT(weapon) +
        " through the air.");

    return 1;
}

/****************************************************************************
 * Frighten - Frighten someone with an axe you wield.
 */
int
frighten(string str)
{
    object *oblist;
    string player_str;
    object weapon;
    string weapon_str;
    int    skill;
    int    dis;
    int    index;
    int    size;

    CHECK_BELT;

    if (!strlen(str))
    {
        notify_fail("Frighten whom [with which axe]?\n");
        return 0;
    }

    if (objectp(TP->query_attack()))
    {
        notify_fail("You cannot frighten anyone since you are in combat.\n");
        return 0;
    }

    if (sscanf(str, "%s with %s", player_str, weapon_str) == 2)
    {
        weapon = parse_weapon(weapon_str, "[the] %i", W_AXE, W_WIELDED);
    }
    else
    {
        weapon = any_wielded_weapon(W_AXE);
        player_str = str;
    }

    if (!objectp(weapon))
    {
        notify_fail("Frighten whom with which axe?\n");
        return 0;
    }

    oblist = parse_this(player_str, "[the] %l");

    switch(sizeof(oblist))
    {
    case 0:
        notify_fail("Frighten whom [with which axe]?\n");
        return 0;

    case 1:
        break;

    default:
        notify_fail("You can only frighten one person at a time.\n");
        return 0;
    }

    /* We need to typecast this call in order to be able to compare it
     * with the define.
     */
    skill = TP->query_skill(SS_WEP_AXE);

    index = -1;
    size = FRIGHTEN_SIZE_DISTANCE_LEVELS;
    while(++index < size)
    {
        if (skill < FRIGHTEN_DISTANCE_LEVELS[index])
        {
            break;
        }
    }

    weapon_str = FRIGHTEN_DISTANCES[index];

    /* Oke, I admit. This check always gives guildmaster the maximum brave-
     * level.
     */
    if (member_array(oblist[0]->query_real_name(),
        SECURITY->query_guild_masters(DWARVEN_RACE_GUILD_SHORT)) == -1)
    {
        dis = oblist[0]->query_stat(SS_DIS);
        dis = THREE_QUARTER(dis) - skill;

        index = -1;
        size = FRIGHTEN_SIZE_REACTION_LEVELS;
        while(++index < size)
        {
            if (dis < FRIGHTEN_REACTION_LEVELS[index])
            {
                break;
            }
        }
    }
    else
    {
        index = FRIGHTEN_SIZE_REACTION_LEVELS;
    }

    player_str = FRIGHTEN_REACTIONS_OTHERS[index];

    actor("Without warning, you swing your " + SHORT(weapon) + " towards",
        oblist, " and let it stop at " + weapon_str + " away from " +
        POSSESSIVE(oblist[0]) + " neck. " + capitalize(PRONOUN(oblist[0])) +
        " " + player_str + ".");
    target(" swings " + POSSESSIVE(TP) + " " + SHORT(weapon) +
        " towards you without any warning and lets it stop at " +
        weapon_str + " away from your neck. You " +
        FRIGHTEN_REACTIONS_ME[index] + ".", oblist);
    all2actbb(" swings " + POSSESSIVE(TP) + " " + SHORT(weapon) +
        " towards", oblist, " without any warning and lets it stop at " +
        weapon_str + " away from " + POSSESSIVE(oblist[0]) +
        " neck. The latter " + player_str + ".");

    return 1;
}

/****************************************************************************
 * Goldsearch - Search for Gold in your environment.
 */
int
goldsearch(string str)
{
    str = check_adverb_with_space(str, "fanatically");

    CHECK_BELT;

    if (str == NO_ADVERB_WITH_SPACE)
    {
        notify_fail("How do you want to search for gold?\n");
        return 0;
    }

    write("You" + str + " start to search the environment for gold.\n");
    all(str + " starts to search the environment for gold.");
    SOULDESC("searching" + str + " for gold");

    return 1;
}

/****************************************************************************
 * Greed - Greedily eye at someones pocket.
 */
int
greed(string str)
{
    object *oblist;

    CHECK_BELT;

    oblist = parse_this(str, "[at] [the] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Look at whom in a greedy manner?\n");
        return 0;
    }

    targetbb(" greedily eyes at your pocket.", oblist);
    actor("You greedily eye at", oblist, "'s pocket.");
    all2actbb(" greedily eyes at", oblist, "'s pocket.");

    return 1;
}

/****************************************************************************
 * Grip - Take a firm grip at a weapon. Wield it if you don't already.
 */
int
grip(string str)
{
    object weapon;
    object busy_weapon;
    object saved_wf;
    mixed  result;
    int    index;
    int    hands;

    CHECK_BELT;

    weapon = parse_weapon(str, "[on] [the] %i", W_ANYWEAPON, W_NOT_WIELDED);

    if (!objectp(weapon))
    {
        notify_fail("Which weapon do you want to take a firm grip on?\n");
        return 0;
    }

    /* Grip on an already wieled weapon. Just emote. */
    if (objectp(weapon->query_wielded()))
    {
        index = random(GRIP_RANDOM_MESSAGES);
        write(GRIP_EMOTE_ACTOR_MESSAGES[index] + SHORT(weapon) + ".\n");
        allbb(GRIP_EMOTE_ONLOOKER_MESSAGES[index] + POSSESSIVE(TP) + " " +
            SHORT(weapon) + ".");
        return 1;
    }

    if (environment(weapon) != this_player())
    {
        /* Pick up the weapon before you can grip it. */
        if (environment(weapon) == environment(this_player()))
        {
            notify_fail("Pick up the " + SHORT(weapon) +
                 " before you can take a firm grip on it.\n");
            return 0;
        }
        /* Don't grip on a weapon inside a scabbard or holster. */
        if (environment(environment(weapon)) == this_player())
        {
            notify_fail("You cannot take a firm grip on the " +
                 SHORT(weapon) + " while it is in your " +
                 SHORT(environment(weapon)) + ".\n");
            return 0;
        }
        /* Strange, but who knows we might end up here. */
        notify_fail("You cannot seem to take a firm grip on the " +
            SHORT(weapon) + " where it is now.\n");
        return 0;
    }

    /* Oke, we are going to try and wield this weapon using our own
     * own emotions. If the weapon doesn't allow us to set the wield
     * message, the deal is off.
     */
    saved_wf = weapon->query_wf();
    if (objectp(saved_wf) &&
        weapon->query_lock())
    {
        notify_fail("Unfortunately " + LANG_THESHORT(weapon) +
            " refuses you to wield it by taking a firm grip on it. Try to " +
            "wield it using the wield command.\n");
        return 0;
    }

    /* See whether the person has hands left to wield the weapon in. This is
     * done to guard against weapons that have a different unwield() criterion
     * than their wield() check. Specifically, those that use the wielder in
     * the unwield(). */
    hands = weapon->query_hands();
    /* Find out whether the hands needed for the weapon are busy. Yes, I know,
     * it is a rather compact / complex way of writing it down. */
    if (hands != W_ANYH)
    {
        /* Anything covering both hands, if you require a hand. */
        busy_weapon = ((hands < W_FOOTR) ? TP->query_tool(W_BOTH) : 0);
        /* Anything covering the hand that is required. */
        busy_weapon = (busy_weapon ? : TP->query_tool(hands));
        /* Both needed, one may be occupied. */
        if (!objectp(busy_weapon) && (hands == W_BOTH))
        {
            busy_weapon = TP->query_tool(W_RIGHT);
            busy_weapon = (busy_weapon ? : TP->query_tool(W_LEFT));
        }
    }
    /* Any hand required, so only fail is both are used. */
    else if (!objectp(busy_weapon = TP->query_tool(W_BOTH)))
    {
        /* If the left hand is occupied, check for the right hand too,
         * otherwise it is still allowed. */
        busy_weapon = (TP->query_tool(W_LEFT) ? TP->query_tool(W_RIGHT) : 0);
    }

    /* A weapon blocks gripping, so make it an emote. */
    if (objectp(busy_weapon))
    {
        write("You briefly take a grip on the " + SHORT(weapon) +
            ", but then release it again in favour of your " +
            SHORT(busy_weapon) + ".\n");
        allbb(" briefly takes a grip on " + POSSESSIVE(TP) + " " +
            SHORT(weapon) + ", but then releases it again in favour of " +
            POSSESSIVE(TP) + " " + SHORT(busy_weapon) + ".");
        return 1;
    }

    /* If there is a wield protection, we test that too to see whether
     * the player can actually wield it.
     */
    if (objectp(saved_wf))
    {
        result = saved_wf->wield(weapon);

        if (stringp(result))
        {
            notify_fail(result);
            return 0;
        }
        if (result < 0)
        {
            notify_fail("You cannot wield " + LANG_THESHORT(weapon) + ".\n");
            return 0;
        }
    }

    /* Replace the 'wf' variable with our own and make the player wield
     * the weapon.
     */
    weapon->set_wf(TO);
    result = weapon->wield_me();
    weapon->set_wf(saved_wf);

    /* If the wield function returned a string, it failed to wield. */
    if (stringp(result))
    {
        /* If we used a special wield, we must also unwield it. */
        if (objectp(saved_wf))
        {
            saved_wf->unwield(weapon);
        }
        notify_fail(result);
        return 0;
    }

    switch(weapon->query_attack_id())
    {
    case W_LEFT:
        result = "in your left hand";
        break;

    case W_RIGHT:
        result = "in your right hand";
        break;

    case W_BOTH:
        result = "in both your hands";
        break;

    case W_FOOTR:
        result = "on your right foot";
        break;

    case W_FOOTL:
        result = "on your left foot";
        break;

    default:
        result = "somewhere";
    }

    write("Taking a firm grip on it, you wield " + LANG_THESHORT(weapon) +
        " " + result + ".\n");
    allbb(" takes a firm grip on " + POSSESSIVE(TP) + " " + SHORT(weapon) +
        ", therewith wielding it " +
        implode(explode(result, "your"), POSSESSIVE(TP)) + ".");

    return 1;
}

/*
 * Function name: wield
 * Description  : When you wield a weapon gripping it, we don't want any
 *                messages printed other than ours. Returning 1 from this
 *                function, we suppress the wield-text.
 * Arguments    : object weapon - the weapon to wield.
 * Returns      : 1 - always
 */
nomask public mixed
wield(object weapon)
{
    return 1;
}

/****************************************************************************
 * Guffaw - Dwarvish roaring laughter.
 *
 * The form of the emotion is dependant on whether you are indoors or
 * outdoors.
 */
int
guffaw(string str)
{
    object *oblist;
    int     indoors = environment(TP)->query_prop(ROOM_I_INSIDE);

    CHECK_BELT;

    if (!strlen(str))
    {
        if (indoors)
        {
            write("You slap you knees and roar from laughter.\n");
            all(" slaps " + OBJECTIVE(TP) + "self on the knees and " +
                POSSESSIVE(TP) + " roaring laughter fills the room.");
        }
        else
        {
            write("While your belly shakes, you hear your roaring laughter " +
                "echo in the distance.\n");
            say("With a shaking belly " + QTNAME(TP) + " laughs and you " +
                "hear " + POSSESSIVE(TP) + " roaring laughter echo in the " +
                "distance.\n");
        }

        return 1;
    }

    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Guffaw at whom?\n");
        return 0;
    }

    if (indoors)
    {
        targetbb(" points at you and " + POSSESSIVE(TP) +
            " roaring laughter fills the room.", oblist);
        actor("You point at", oblist,
            " and your roaring laughter fills the room.");
        all2actbb(" points at", oblist, " and " + POSSESSIVE(TP) +
            " roaring laughter fills the room.");
    }
    else
    {
        targetbb(" points at you and while " + POSSESSIVE(TP) +
            " belly shakes, you hear " + POSSESSIVE(TP) +
            " roaring laughter echo in the distance.", oblist);
        actor("You point at", oblist, " and while your belly shakes, " +
            "you hear your roaring laughter echo in the distance.");
        all2actbb(" points at", oblist, " and while " + POSSESSIVE(TP) +
            " belly shakes, you can hear " + POSSESSIVE(TP) +
            " roaring laughter echo in the distance.");
    }

    return 1;
}

/****************************************************************************
 * Hail - Greet someone the Dwarven way.
 */
int
hail(string str)
{
    object *oblist = ({ });
    object weapon;

    CHECK_BELT;

    if (strlen(str))
    {
        oblist = parse_this(str, "[the] %l");

        if (!sizeof(oblist))
        {
            notify_fail("Whom do you want to hail?\n");
            return 0;
        }
    }

    if (!objectp(weapon = any_wielded_weapon(W_AXE_OR_CLUB)))
    {
        if (!sizeof(oblist))
        {
            write("You raise your arm and shout: Hail in the name of " +
                "Durin!\n");
            all(" raises " + POSSESSIVE(TP) +
                " arm and shouts: Hail in the name of Durin!");

            return 1;
        }

        target(" raises " + POSSESSIVE(TP) +
            " arm to greet you and shouts: Hail in the name of Durin!",
            oblist);
        actor("You raise your arm to greet", oblist,
            " and shout: Hail in the name of Durin!");
        all2act(" raises " + POSSESSIVE(TP) + " arm to greet", oblist,
            " and shouts: Hail in the name of Durin!");

        return 1;
    }

    if (!sizeof(oblist))
    {
        write("You raise your " + SHORT(weapon) +
            " above your head and shout: Hail in the name of Durin!\n");
        all(" raises " + POSSESSIVE(TP) + " " + SHORT(weapon) +
            " above " + POSSESSIVE(TP) +
            " head and shouts: Hail in the name of Durin!");

        return 1;
    }

    target(" raises " + POSSESSIVE(TP) + " " + SHORT(weapon) +
        " high above your head and shouts: Hail in the name of Durin!",
        oblist);
    actor("You raise your " + SHORT(weapon) + " high above", oblist,
        "'s head and shout: Hail in the name of Durin!");
    all2act(" raises " + POSSESSIVE(TP) + " " + SHORT(weapon) +
        " high above", oblist,
        "'s head" + ((sizeof(oblist) == 1) ? "" : "s") +
        " and shouts: Hail in the name of Durin!");

    return 1;
}

/****************************************************************************
 * Help - Get help on the Rockfriend commands.
 */
int
process_help(string category, string topic)
{
    /* A category is entered, but it's not our category. */
    if (category && !IN_ARRAY(category, HELP_CATEGORIES))
    {
        return 0;
    }

    if (IN_ARRAY(topic, HELP_CATEGORIES))
    {
        topic = "help";
    }

    topic = lower_case(topic);
    if (!IN_ARRAY(topic, HELP_TOPICS))
    {
        /* Only give a specific message if we own the category. */
        if (category)
        {
            write("The Rockfriend help topics are: " +
                COMPOSITE_WORDS(HELP_TOPICS) + ".\n");
            return 1;
        }
        return 0;
    }

    FIX_EUID;

    if (file_size(DWARVEN_RACE_GUILD_HELP + topic) <= 0)
    {
        write("The help topic \"" + topic + "\" was not found, but it " +
            "should exist. Please make a bugreport about this.\n");
        return 1;
    }

    TP->more(read_file(DWARVEN_RACE_GUILD_HELP + topic));
    return 1;
}

/****************************************************************************
 * Hmph - Snort a loud hmph.
 */
int
hmph(string str)
{
    object *oblist;

    CHECK_BELT;

    if (!strlen(str))
    {
        write("You fold your arms and snort a loud \"Hmph\".\n");
        all(" folds " + POSSESSIVE(TP) + " arms and snorts a loud \"Hmph\".");

        return 1;
    }

    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Hmph at whom?\n");
        return 0;
    }

    targetbb(" folds " + POSSESSIVE(TP) +
        " arms and snorts a loud \"Hmph\" at you!", oblist);
    actor("You fold your arms and snort a loud \"Hmph\" at", oblist);
    all2actbb(" folds " + POSSESSIVE(TP) +
        " arms and snorts a loud \"Hmph\" at", oblist);

    return 1;
}

/****************************************************************************
 * Inspect - Inspect a weapon you are carrying.
 */

/*
 * Function name: inspect_living
 * Description  : This function sees whether the player wants to inspect
 *                another player.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - success/failure.
 */
private int
inspect_living(string str)
{
    object *oblist;

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        notify_fail("Please select only one living to inspect at a time.\n");
        return 0;
    }

    write("HMPH! This command does not seem to work yet.\n");
    return 1;
}

int
inspect(string str)
{
    object weapon;

    CHECK_BELT;

    weapon = parse_weapon(str, "[the] %i", W_ANYWEAPON, W_NOT_WIELDED);

    if (!objectp(weapon))
    {
        if (inspect_living(str))
        {
            return 1;
        }

        notify_fail("Which weapon or whom do you wish to inspect?\n");
        return 0;
    }

    write("You inspect the " + SHORT(weapon) + " closely. " +
        weapon->wep_condition_desc());
    allbb(" inspects " + POSSESSIVE(TP) + " " + SHORT(weapon) + " closely.");

    return 1;
}

/****************************************************************************
 * List dwarves - Get a list of all dwarves in the realms.
 */

/*
 * Function name: list_sort_names
 * Description  : This function is used in order to sort the names of the
 *                dwarves alphabetically
 * Arguments    : p1, p2 - the objectpointers of (two) dwarves to sort
 * Returns      : -1 - the name of p1 comes before p2's name
 *                 0 - the names of p1 and p2 are identical
 *                 1 - the name of p2 comes before p1's name
 */
int
list_sort_names(object p1, object p2)
{
    /* No reason to check for equality. Should never happen. */
    return ((p1->query_real_name() < p2->query_real_name()) ? -1 : 1);
}

/*
 * Function name: list_met_wizard
 * Description  : Mortal players cannot see wizards that are not a member
 *                and that he has not met before.
 * Arguments    : object player - the player to see.
 * Returns      : int 1/0 - player will get the name or not.
 */
int
list_met_wizard(object player)
{
    if (!player->query_wiz_level() ||
        this_player()->query_met(player))
    {
        return 1;
    }

    return IS_MEMBER(player);
}

int
list(string str)
{
    object *dwarves;
    int    number_dwarves = 0;
    int    screenwidth;
    string desc = "";
    string tmp;
    string *title;
    string guild_title;
    string name;

    CHECK_BELT;

    if (!strlen(str))
    {
        notify_fail("List what?\n");
        return 0;
    }

    if (!parse_command(str, ({ }),
        "[the] 'dwarfs' / 'dwarves' / 'rockfriends'"))
    {
        notify_fail("List what?\n");
        return 0;
    }

    screenwidth = TP->query_prop(PLAYER_I_SCREEN_WIDTH);
    /* This 8 is for 'member' plus two spaces */
    screenwidth = ((screenwidth <= 0) ? 75 :
        ((screenwidth > 40) ? screenwidth : 40)) - 8;

    dwarves = filter((users() - ({ 0 }) ),
        &operator(==)("dwarf") @ &->query_race());
    dwarves = sort_array(dwarves, list_sort_names);

    foreach(object dwarf: dwarves)
    {
        name = CAP(dwarf->query_real_name());

        /* Only wizards get to see invis people, juniors and non-member
         * wizards.
         */
        if (!TP->query_wiz_level() &&
            (dwarf->query_invis() ||
             (extract(name, -2) == "jr") ||
             (dwarf->query_wiz_level() && !IS_MEMBER(dwarf))))
        {
            continue;
        }

        if (dwarf->query_wiz_level())
        {
            guild_title = dwarf->query_title();
        }
        else
        {
            guild_title = dwarf->query_guild_title_race();
            guild_title = (strlen(guild_title) ?
                ((dwarf->query_guild_family_name() ? "" : "the ") +
                guild_title) : "-- not a Rockfriend --");
        }

        tmp = SECURITY->query_wiz_pretitle(dwarf);
        title = explode(break_string((strlen(tmp) ? (tmp + " "): "") +
            name + " " + guild_title, (screenwidth - 1)), "\n");

        tmp = sprintf("%-*s ", screenwidth, title[0]);
        tmp += sprintf("%-6s\n", (IS_MEMBER(dwarf) ? "Member" : "Dwarf"));

        if (sizeof(title) > 1)
        {
            title = explode(break_string(
                implode(title[1..(sizeof(title) - 1)], " "),
                (screenwidth - 6)), "\n");

            foreach(string title_part: title)
            {
                tmp += sprintf("      %-*s\n", (screenwidth - 6), title_part);
            }
        }

        desc += tmp;
        number_dwarves++;
    }

    write("At present there " + ((number_dwarves == 1) ? "is one dwarf" :
       ("are " + LANG_WNUM(number_dwarves) + " dwarves")) +
       " in the realms.\n" +
"==========================================================================\n" +
"Name                                                                Member\n" +
"\n");
    write(desc);

    return 1;
}

/****************************************************************************
 * Preen - Preen your beard/whiskers.
 */
int
preen(string str)
{
    string beard;

    CHECK_BELT;

    str = check_adverb_with_space(str, "proudly");
    beard = beard_description(TP);

    if (str == NO_ADVERB_WITH_SPACE)
    {
        notify_fail("How do you want to preen your " + beard + "?\n");
        return 0;
    }

    write("You" + str + " preen your " + beard + ".\n");
    all(str + " preens " + POSSESSIVE(TP) + " " + beard + ".");

    return 1;
}

/****************************************************************************
 * Promise - promise someone your word as Dwarf, calling upon Mahal.
 */
int
promise(string str)
{
    object *oblist;

    CHECK_BELT;

    oblist = parse_this(str, "[to] [the] %l");
    if (!sizeof(oblist))
    {
        notify_fail("Promise [to] whom?\n");
        return 0;
    }

    actor("You make a promise to", oblist,
        ", by virtue of Mahal and your honour as a Dwarf.");
    tell_room(environment(this_player()), QCTNAME(this_player()) +
        " makes " + desc_many(oblist) + " a promise, by virtue of " +
        "@@dwarven_god:" + DWARVEN_RACE_GUILD_SOUL + "@@ and " +
        POSSESSIVE(TP) + " honour as a Dwarf.\n", ({ this_player() }) + oblist);
    oblist->catch_msg(QCTNAME(this_player()) + " makes you a promise, by " +
        "virtue of @@dwarven_god:" + DWARVEN_RACE_GUILD_SOUL + "@@ and " +
        POSSESSIVE(TP) + " honour as a Dwarf.\n");

    return 1;
}

/****************************************************************************
 * Polish - Polish a weapon you carry.
 */
int
polish(string str)
{
    object weapon;

    CHECK_BELT;

    weapon = parse_weapon(str, "[the] %i", W_ANYWEAPON, W_NOT_WIELDED);

    if (!objectp(weapon))
    {
        notify_fail("Which weapon do you wish to polish?\n");
        return 0;
    }

    write("You buff up your " + SHORT(weapon) + " to a brilliant shine.\n");
    allbb(" buffs up " + POSSESSIVE(TP) + " " + SHORT(weapon) +
        " to a brilliant shine.");

    return 1;
}

/****************************************************************************
 * Quiver - Get very angry and make your beard/whiskers quiver.
 */
int
quiver(string str)
{
    object *oblist;
    string beard;
    string verb;

    CHECK_BELT;

    beard = beard_description(TP);
    verb = ((TP->query_gender() == G_FEMALE) ? "quiver" : "quivers");

    if (!strlen(str))
    {
        write("You are so angry that your " + beard + " " + verb +
            " as you scream in Dwarvish.\n");
        allbb(" is so angry that " + POSSESSIVE(TP) + " " + beard + " " +
            verb + " as " + PRONOUN(TP) + " screams in Dwarvish.");

        return 1;
    }

    oblist = parse_this(str, "[at] [the] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Quiver your " + beard + " at whom?\n");
        return 0;
    }

    target(" is so angry with you that " + POSSESSIVE(TP) + " " + beard + " " +
        verb + " as " + PRONOUN(TP) + " screams at you in Dwarvish.", oblist);
    actor("You are so angry with", oblist, " that your " + beard + " " + verb +
        " as you scream at " +
        ((sizeof(oblist) > 1) ? "them" : OBJECTIVE(oblist[0])) +
        " in Dwarvish.");
    all2act(" is so angry with", oblist, " that " + POSSESSIVE(TP) + " " +
        beard + " " + verb + " as " + PRONOUN(TP) + " screams at " +
        ((sizeof(oblist) > 1) ? "them" : OBJECTIVE(oblist[0])) +
        "in Dwarvish.");

    return 1;
}

/****************************************************************************
 * Rage - Rage in anger.
 */
int
rage(string str)
{
    object *oblist;

    CHECK_BELT;

    if (!strlen(str))
    {
        SOULDESC("raging in anger");
        write("Your cheeks flush red and you jump up and down, screaming " +
            "Dwarvish.\n");
        allbb("'s cheeks flush red and " + PRONOUN(TP) + " jumps up and " +
            "down, screaming in Dwarvish.");

        return 1;
    }

    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Rage at whom?\n");
        return 0;
    }

    SOULDESC("raging in anger");
    target("'s cheeks flush red and jumps up and down, screaming at you " +
        "in Dwarvish.", oblist);
    actor("Your cheeks flush red and you jump up and down, screaming at",
        oblist, " in Dwarvish.");
    all2act(" jumps up and down, screaming at", oblist, " in Dwarvish, while " +
        POSSESSIVE(TP) + " cheeks flush red.");

    return 1;
}

/****************************************************************************
 * Rebraid - Rebraid your beard/whiskers.
 */
int
rebraid(string str)
{
    string beard;

    CHECK_BELT;

    if (strlen(str))
    {
        notify_fail("Rebraid what?\n");
        return 0;
    }

    beard = beard_description(TP);

    write("You rebraid your " + beard + ".\n");
    allbb(" rebraids " + POSSESSIVE(TP) + " " + beard + ".");

    return 1;
}

/****************************************************************************
 * Revenge - Swear to take revenge.
 */
int
revenge(string str)
{
    object *oblist;

    CHECK_BELT;

    if (!strlen(str))
    {
        SOULDESC("looking for revenge");
        write("You swear to gain vengeance on the one who harmed you.\n");
        all(" swears to gain vengeance on the one who harmed " +
            OBJECTIVE(TP) + ".");

        return 1;
    }

    oblist = parse_this(str, "[on] [the] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Whom do you want to gain vengeance on?\n");
        return 0;
    }

    SOULDESC("looking for revenge");
    target(" swears to gain vengeance on you.", oblist);
    actor("You swear to gain vengeance on", oblist);
    all2act(" swears to gain vengeance on", oblist);

    return 1;
}

/****************************************************************************
 * Rf - Perform a Rockfriend command.
 */
int
rf(string str)
{
    string *words;

    CHECK_BELT;

    if (!strlen(str))
    {
        notify_fail("Perform which Rockfriend command? " +
            "Syntax: rf <command> [<arguments>]\n");
        return 0;
    }

    /* Verify whether the command is actually a Rockfriend command. */
    words = explode(str, " ");
    if (!stringp(cmdlist[words[0]]))
    {
        notify_fail("The command " + words[0] +
            " is not a known Rockfriend command.\n");
        return 0;
    }

    /* Prepare the command line argument, if there is one. */
    str = ((sizeof(words) > 1) ? implode(words[1..], " ") : "");

    /* Make a call to the command function. */
    return call_other(this_object(), cmdlist[words[0]], str);
}

/****************************************************************************
 * Show off - Show off with a wielded axe.
 */

/*
 * Function name: show_off
 * Description  : This function prints the message to the spectator and
 *                returns his reaction.
 * Arguments    : object spectator - the spectator.
 *                string wep_desc  - the weapon used.
 *                int    my_skill  - the skill of the actor.
 * Returns      : string - the reaction.
 */
private string
show_off(object spectator, string wep_desc, int my_skill)
{
    int diff_skill;
    int index;
    int size;

    diff_skill = THREE_QUARTER(my_skill) - spectator->query_skill(SS_WEP_AXE);

    /* If the condition is never met, then index will have the value
     * SHOW_OFF_SIZE_DIFF_LEVELS, which is the last entry in the array
     * show_off_reactions.
     */
    index = -1;
    while(++index < SHOW_OFF_SIZE_DIFF_LEVELS)
    {
        if (diff_skill < SHOW_OFF_DIFF_LEVELS[index])
        {
            break;
        }
    }

    spectator->CATCH_MSGBB((" demonstrates " + POSSESSIVE(TP) +
        " skill with " + POSSESSIVE(TP) + " " + wep_desc +
        ". You are " + show_off_reactions[index] + "."), TP);

    /* If the actor cannot see the target, don't give a reaction. */
    return ((CAN_SEE(TP, spectator)) ? show_off_reactions[index] : "");
}

/*
 * Function name: build_reaction
 * Description  : This function actually generates the message, from the
 *                spectators, the weapon used and the skill.
 * Arguments    : object *spectators - the people watching.
 *                string  wep_desc   - the weapon used.
 *                int     my_skill   - my axe-skill.
 * Returns      : string - the reactions of the spectators.
 */
private string
build_reaction(object *spectators, string wep_desc, int my_skill)
{
    string *names;
    string *reactions;
    string *reaction  = ({ });
    string *react_this;
    int    index1;
    int    index2;
    int    size1;
    int    size2;

    names = map(spectators, &->query_the_name(TP));
    reactions = map(spectators, &show_off(, wep_desc, my_skill));

    index1 = -1;
    size1 = sizeof(show_off_reactions);
    while(++index1 < size1)
    {
        react_this = ({ });

        index2 = -1;
        size2 = sizeof(reactions);
        while(++index2 < size2)
        {
            if (reactions[index2] == show_off_reactions[index1])
            {
                react_this += ({ names[index2] });
            }
        }

        if (!sizeof(react_this))
        {
            continue;
        }

        reaction += ({ (COMPOSITE_WORDS(react_this) +
            ((sizeof(react_this) == 1) ? " is " : " are ") +
            show_off_reactions[index1]) });
    }

    return (COMPOSITE_WORDS(reaction));
}

int
show(string str)
{
    object  weapon;
    object *spectators;
    object *seen_spectators;
    int     my_skill;

    CHECK_BELT;

    if (str == "off")
    {
        weapon = any_wielded_weapon(W_AXE_OR_CLUB);
    }
    else
    {
        weapon = parse_weapon(str, "'off' [with] [the] %i", W_AXE_OR_CLUB, W_WIELDED);
    }

    if (!objectp(weapon))
    {
        notify_fail("Which axe do you want to show off with?\n");
        return 0;
    }

    my_skill = TP->query_skill(SS_WEP_FIRST + weapon->query_wt());

    spectators = FILTER_OTHER_LIVE(all_inventory(ENV(TP)));
    seen_spectators = FILTER_CAN_SEE(spectators, TP);

    if (!sizeof(seen_spectators))
    {
        write("You practice a little with your " + SHORT(weapon) +
            ", though there is no-one around to impress with your skill.\n");

        if (sizeof(spectators))
        {
            /* Make the spectators see, even though the artist does not
             * know that he is being watched.
             */
            map(spectators, &show_off(, SHORT(weapon), my_skill));
        }

        return 1;
    }

    if (my_skill < MINIMUM_SKILL_TO_SHOW_OFF)
    {
        write("Your skills with your " + SHORT(weapon) +
            " are such that you would only embarras yourself if you would " +
            "try to show off with it. Therefore you choose not to do so.\n");

        return 1;
    }

    write("You show off with your " + SHORT(weapon) + ". " +
        CAP(build_reaction(spectators, SHORT(weapon), my_skill)) + ".\n");

    return 1;
}

/****************************************************************************
 * Shun - Turn away from someones affection.
 */
int
shun(string str)
{
    object *oblist;

    CHECK_BELT;

    oblist = parse_this(str, "[the] %l");
    if (!sizeof(oblist))
    {
        notify_fail("Shun whose affection?\n");
        return 0;
    }

    str = ((sizeof(oblist) == 1) ? POSSESSIVE(oblist[0]) : "their");
    actor("You step backwards, turning away from", oblist,
        ", shunning " + str + " affection.");
    targetbb(" steps backwards, turning away from you and shunning your " +
        "affection.", oblist);
    all2actbb(" steps backwards, turning away from", oblist,
        ", shunning " + str + " affection.");

    return 1;
}

/****************************************************************************
 * Silence - Glare at someone in stoic silence.
 */
int
silence(string str)
{
    object *oblist;

    CHECK_BELT;

    oblist = parse_this(str, "[to] [the] %l");
    if (!sizeof(oblist))
    {
        notify_fail("Answer whom with silence?\n");
        return 0;
    }

    SOULDESC("glaring in stoic silence");
    target(" answers you with a stoic silence.", oblist);
    actor("You answer", oblist, " with a stoic silence.");
    all2act(" answers", oblist, " with a stoic silence.");

    return 1;
}

/****************************************************************************
 * Stroke - Stroke your beard/whiskers.
 */
int
stroke(string str)
{
    string beard;
    str = check_adverb_with_space(str, "lovingly");

    CHECK_BELT;

    beard = beard_description(TP);

    if (str == NO_ADVERB_WITH_SPACE)
    {
        notify_fail("Stroke your " + beard + " how?\n");
        return 0;
    }

    write("You stroke your " + beard + str + ".\n");
    allbb(" strokes " + POSSESSIVE(TP) + " " + beard + str + ".");

    return 1;
}

/****************************************************************************
 * Swig - Swallow one or more drinks.
 */

/*
 * Function name: swig_strongest_first
 * Description  : This sort function sorts the array of drinks such that
 *                the strongest drink is tried first. This is only needed
 *                if the player tries to swig 'all'.
 * Arguments    : object drink1 - the first drink to test.
 *                object drink2 - the second drink to test.
 * Returns      : int -1/0/1 - drink1 is larger/equal/less than/to drink2.
 */
int
swig_strongest_first(object drink1, object drink2)
{
    int alco1 = drink1->query_alco_amount();
    int alco2 = drink2->query_alco_amount();

    return ((alco1 > alco2) ? 1 : ((alco1 == alco2) ? 0 : -1));
}

int
swig(string str)
{
    int     index = -1;
    int     size;
    int     num;
    int     alco;
    object *drinks;
    object *drunk = ({ });
    mixed   result;
    string  suffix;
    string  suffix2;

    CHECK_BELT;

    if (!strlen(str) ||
        !parse_command(str, TP, "[the] %i", drinks) ||
        !sizeof(drinks = NORMAL_ACCESS(drinks, 0, 0)))
    {
        notify_fail("Swig what?\n");
        return 0;
    }

    /* Make sure the player only swigs drinks. */
    drinks = filter(drinks, &operator(==)(DRINK_OBJECT, ) @
        &function_exists("create_heap", ));
    if (!sizeof(drinks))
    {
        notify_fail("Perhaps you would like to swig a drink instead.\n");
        return 0;
    }

    /* See whether the drink contains any alcohol. */
    drinks = filter(drinks, &->query_alco_amount());
    if (!sizeof(drinks))
    {
        notify_fail("Swig a non-alcoholic beverage? That is not very " +
            "Rockfriend like! Drink it, if you must.\n");
        return 0;
    }

    drinks = sort_array(drinks, "swig_strongest_first", this_object());
    str = SWIG_FAIL_SOFT;
    foreach(object drink: drinks)
    {
        result = drink->command_drink();
        if (result == 1)
        {
            drunk += ({ drink });
            num += drink->num_heap();
            continue;
        }

        /* This should not happen! */
        if (!stringp(result))
        {
            write("Strange drink, that " + drink->singlular_short() +
                ". It is not swiggable! Very peculiar.\n");
            continue;
        }

        /* If there was an alco problem, set the fail string to alco. */
        if (wildmatch("*too strong for you*", result))
        {
            str = SWIG_FAIL_ALCO;
        }
    }

    /* Player didn't manage to drink a single thing. */
    if (!sizeof(drunk))
    {
        if (str == SWIG_FAIL_SOFT)
        {
            str = drinks[(sizeof(drinks) - 1)]->singular_short();
            write("Your belly must be a bloated bag of water, as you fail " +
                "to drink a single " + str + ".\n");
            allbb(" must have a bloated bag of water for a belly, as " +
                PRONOUN(TP) + " fails to drink a single " + str + ".");
        }
        else
        {
            alco = drinks[(sizeof(drinks) - 1)]->query_alco_amount();
            index = -1;
            while(++index < SWIG_SIZE_FAIL_LEVELS)
            {
                if (alco <= SWIG_ALCO_FAIL_LEVELS[index])
                {
                    break;
                }
            }

            str = drinks[(sizeof(drinks) - 1)]->singular_short();
            write(SWIG_ALCO_FAIL_MESSAGES_ME[index] +
                ", as you fail to stomach a single " + str + ".\n");
            allbb(SWIG_ALCO_FAIL_MESSAGES_OTHERS[index] +
                ", as " + PRONOUN(TP) + " fails to stomach a single " +
                str + ".");
        }
        return 1;
    }

    /* Create the composite message for the drinks and reduce/remove the
     * drinks that have been drunk.
     */
    str = COMPOSITE_DEAD(drunk);
    drunk->remove_drink();

    /* If you drink more than 10, you get the maximal message. */
    num = ((num > SWIG_DRINK_LEVELS) ? (SWIG_DRINK_LEVELS - 1) : (num - 1));

    suffix = SWIG_DRINK_SUFFIX_ME[num];
    if (strlen(suffix))
    {
        suffix2 = SWIG_DRINK_SUFFIX_OTHERS[num];
    }
    else
    {
        suffix = SWIG_DRINK_RANDOM_MESSAGES[random(SWIG_DRINK_RANDOM_LEVELS)];
        suffix2 = suffix;
    }

    write("You" + SWIG_DRINK_VERBS_ME[num] + str + suffix + ".\n");
    allbb(SWIG_DRINK_VERBS_OTHERS[num] + str + suffix2 + ".");
    return 1;
}

/****************************************************************************
 * Swing - Swing someone around in a strong embrace.
 */
int
swing(string str)
{
    object *oblist;
    int    carry_power;
    int    target_weight;
    int    index;
    string t_obj; /* target objective */
    string a_pro; /* actor pronoun    */
    string a_pos; /* actor possessive */

    CHECK_BELT;

    oblist = parse_this(str, "[the] %l [around]");

    switch(sizeof(oblist))
    {
    case 0:
        notify_fail("Swing who around?\n");
        return 0;

    case 1:
        break;

    default:
        notify_fail("Swinging one person around will be enough at one " +
            "time.\n");
        return 0;
    }

    if ((member_array(TP, oblist[0]->query_enemy(-1)) != -1) ||
        (member_array(oblist[0], TP->query_enemy(-1)) != -1))
    {
        notify_fail("While fighting " + oblist[0]->query_the_name(TP) +
            " to death, it is not possible to swing " + OBJECTIVE(oblist[0]) +
            " around. Wrestling is a different sport.\n");
    }

    carry_power = TP->query_prop(CONT_I_MAX_WEIGHT);
    target_weight = oblist[0]->query_prop(OBJ_I_WEIGHT);
    if (carry_power < target_weight)
    {
        write("You try to lift " + oblist[0]->query_the_name(TP) +
            " in order to swing " + OBJECTIVE(oblist[0]) +
            " around, but fail the necessary strength.\n");
        all2act(" tries to lift", oblist, " in order to swing " +
            OBJECTIVE(oblist[0]) + " around, though fails the necessary " +
            "strength to do so.");
        target(" tries to lift you in order to swing you around, but " +
            PRONOUN(TP) + " fails the necessary strength.", oblist);
        return 1;
    }

    /* Minimum target weight is set to 10 kilo. Compute the relative
     * extra carry power of the player. When both actor and target are
     * equally heavy, the carry power == 100. Then we subtract 100.
     */
    target_weight = ((target_weight < 10000) ? 10000 : target_weight);
    carry_power = (carry_power / (target_weight / 100)) - 100;

    /* When SWING_SIZE_DIFF_LEVELS is exceeded, the last element of the
     * array is used.
     */
    index = -1;
    while(++index < SWING_SIZE_DIFF_LEVELS)
    {
        if (carry_power < SWING_DIFF_LEVELS[index])
        {
            break;
        }
    }

    t_obj = oblist[0]->query_objective();
    a_pro = TP->query_pronoun();
    a_pos = TP->query_possessive();
    str = oblist[0]->query_the_name(TP);

    switch(index)
    {
    case 0:
        write("You summon all your strenght to raise " + str +
            " from the ground. After swinging " + t_obj +
            " half a turn, you must let go again.\n");
        all2act(" summons all " + a_pos + " strength to raise", oblist,
            " from the ground. After swinging " + t_obj +
            " half a turn, " + a_pro + " must let go again.");
        target(" summons all " + a_pos + " strength to raise you from " +
            "the ground. After swinging you half a turn, " +
            a_pro + " must let go again.", oblist);
        return 1;

    case 1:
        write("You barely manage to to lift " + str +
            " in your arms and swing " + t_obj + " around once.\n");
        all2act(" barely manages to lift", oblist, " in " + a_pos +
            " arms and swings " + t_obj + " around once.");
        target(" barely manages to lift you in " + a_pos +
            " arms and swings you around once.", oblist);
        return 1;

    case 2:
        write("You lift " + str + " and turn " + t_obj +
            " around in your arms.\n");
        all2act(" lifts", oblist, " and turns " + t_obj + " in " + a_pos +
            " arms.");
        target(" lifts you and turns you in " + a_pos + " arms.", oblist);
        return 1;

    case 3:
        write("You easily lift " + str + " from the ground and swing " +
            t_obj + " around in your arms.\n");
        all2act(" easily lifts", oblist, " from the ground and swings " +
            t_obj + " around in " + a_pos + " arms.");
        target(" easily lifts you from the ground and swings you around in " +
            a_pos + " arms.", oblist);
        return 1;

    case 4:
        write("You raise " + str + " with no visible effort and swing " +
            t_obj + " around in a fond hug.\n");
        all2act(" raises", oblist, " with no visible effort and swings " +
            t_obj + " around in a fond hug.");
        target(" raises you with no visible effort and swings you " +
            "around in a fond hug.", oblist);
        return 1;

    case 5:
        write("With great ease you take " + str +
            " into your arms and swing " + t_obj +
            " around in a strong embrace.\n");
        all2act(" takes", oblist, " into " + a_pos +
            " arms with great ease and swings " + t_obj +
            " around in a strong embrace.");
        target(" takes you into " + a_pos + " arms with great ease and " +
            "swings you around in a strong embrace.", oblist);
        return 1;

    case 6:
        write("You embrace " + str + " with your strong arms, then lift " +
            t_obj + " and sweep " + t_obj +
            " through the air in a double pirouette.\n");
        all2act(" embraces", oblist, " with " + a_pos +
            " strong arms, then lifts the latter and sweeps " + t_obj +
            " through the air in a double pirouette.");
        target(" embraces you with " + a_pos + " strong arms, then lifts " +
            "you and sweeps you through the air in a double pirouette.",
            oblist);
        return 1;
    }
    return 1;
}

/****************************************************************************
 * Thirsty - Appear to be thirsty.
 */
int
thirsty(string str)
{
    int level;

    CHECK_BELT;

    if (str == "help")
    {
        write("You can appear to be thirsty at the following levels: " +
            COMPOSITE_WORDS(THIRSTY_LEVELS) + ". If you omit the " +
            "level, then it will be based on your recent consumption.\n");
        return 1;
    }

    if (!strlen(str))
    {
        level = THIRSTY_DEFAULT_MAX -
            ((TP->query_intoxicated() * THIRSTY_DEFAULT_RANGE) /
             (TP->query_prop(LIVE_I_MAX_INTOX) + 1));
    }
    else
    {
        level = member_array(str, THIRSTY_LEVELS);
        if (level == -1)
        {
            notify_fail("How thirsty do you want to appear? " +
                "Do \"thirsty help\".\n");
            return 0;
        }
    }

    write("You " + THIRSTY_SEE_SELF[level] + "\n");
    allbb(" " + THIRSTY_SEE_OTHERS[level]);
    return 1;
}

/****************************************************************************
 * Toast - Make a toast [to someone].
 */
int
toast(string str)
{
    object *oblist;
    string drink;

    CHECK_BELT;

    /* First see whether the player has a drink on him. */
    oblist = filter(all_inventory(TP),
        &operator(==)(DRINK_OBJECT, ) @ &function_exists("create_heap", ));
    if (!sizeof(oblist))
    {
        notify_fail("You do not have a drink on you.\n");
        return 0;
    }

    /* See whether the drink contains any alcohol. */
    oblist = filter(oblist, &->query_alco_amount());
    if (!sizeof(oblist))
    {
        notify_fail("No Rockfriend would ever toast with a non-alcoholic " +
            "beverage.\n");
        return 0;
    }

    /* Select one drink. Since this only selects on the objects, a heap with
     * 10 beers has just as much chance as a heap with only one glass of wine.
     */
    drink = one_of_list(oblist)->query_short();

    if (!strlen(str))
    {
        write("You raise your " + drink + " and toast to everyones health.\n");
        allbb(" raises " + POSSESSIVE(TP) + " " + drink +
            " and toasts to everyones health.");
        return 1;
    }

    oblist = parse_this(str, "[to] [the] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Toast to whom?\n");
        return 0;
    }

    actor("You raise your " + drink + " and toast to the health of", oblist);
    targetbb(" raises " + POSSESSIVE(TP) + " " + drink +
        " and toasts to your health.", oblist);
    all2actbb(" raises " + POSSESSIVE(TP) + " " + drink + " and toasts to",
        oblist, "'s health.");
    return 1;
}

/****************************************************************************
 * Tug - Tug your beard/whiskers in thoughtfulness.
 */
int
tug(string str)
{
    string beard;
    string *how;
    object *oblist;
    int    female;

    CHECK_BELT;

    if (!strlen(str))
    {
        beard = beard_description(TP);

        /* Yabba dabba HA HA HA! */
        if (TP->query_rockfriend_beard_description() == "fake")
        {
            female = (TP->query_gender() == G_FEMALE);
            write("As you tug at your " + beard + ", you remember that " +
                (female ? "they are not real whiskers" :
                "it is not a real beard") + " yet and embarass yourself.\n");
            allbb(" tugs at " + POSSESSIVE(TP) + " " + beard + ". " +
                capitalize(PRONOUN(TP)) + " immediately remembers that " +
                (female ? "they are not real whiskers" :
                "it is not a real beard") + " yet as " + PRONOUN(TP) +
                " embarasses " + OBJECTIVE(TP) + "self.");
            return 1;
        }

        write("You tug your " + beard + " in thoughtfulness.\n");
        allbb(" tugs " + POSSESSIVE(TP) + " " + beard + " in thoughtfulness.");
        return 1;
    }

    how = parse_adverb_with_space(str, "playfully", 1);

    oblist = parse_this(how[0], "[on] / [at] [the] [beard] [of] [the] %l");

    switch(sizeof(oblist))
    {
    case 0:
        notify_fail("Tug on whose beard [how]?\n");
        return 0;

    case 1:
        if (!IS_MEMBER(oblist[0]))
        {
            notify_fail("You can only tug at the beard or whiskers of " +
                "another Rockfriend.\n");
            return 0;
        }
        break;

    default:
        notify_fail("Please tug at one beard at a time.\n");
        return 0;
    }

    beard = beard_description(oblist[0]);

    /* Make fun of an "Adopted Rockfriend" by pulling his/her fake
     * beard/whiskers. ;-)
     */
    if (oblist[0]->query_rockfriend_beard_description() == "fake")
    {
        actor("You tug" + how[1] + " at", oblist, "'s " + beard +
            " and guess what: It is a fake! In order not to embarass " +
            OBJECTIVE(oblist[0]) + " any further, you do not pull hard.");
        all2actbb(" tugs" + how[1] + " at", oblist, "'s " + beard +
            " and guess what: It is a fake! In order not to embarass the " +
            "Adopted Rockfiend any further, " + PRONOUN(TP) +
            " does not pull hard.", how[1]);
        target(" tugs" + how[1] + " at your " + beard + ". Noticing that " +
            "it is not real, " + PRONOUN(TP) + " does not pull hard in " +
            "order not to embarass you further.", oblist, how[1]);
        return 1;
    }

    actor("You tug" + how[1] + " at", oblist, "'s " + beard + ".");
    all2actbb(" tugs" + how[1] + " at", oblist, "'s " + beard + ".", how[1]);
    target(" tugs" + how[1] + " at your " + beard + ".", oblist);
    return 1;
}

/****************************************************************************
 * Twist - Twist your beard/whiskers in boredom.
 */
int
twist(string str)
{
    string beard;

    CHECK_BELT;

    if (strlen(str))
    {
        notify_fail("Twist what?\n");
        return 0;
    }

    beard = beard_description(TP);

    SOULDESC("twisting " + POSSESSIVE(TP) + " fingers in " + POSSESSIVE(TP) +
        " " + beard + " in boredom");
    write("You twist your fingers in your " + beard + " in boredom.\n");
    allbb(" twists " + POSSESSIVE(TP) + " fingers in " + POSSESSIVE(TP) +
        " " + beard + " in boredom.\n");

    return 1;
}

/****************************************************************************
 * The end.
 */
