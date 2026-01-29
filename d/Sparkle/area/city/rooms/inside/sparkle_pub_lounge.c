/*
 *  /d/Sparkle/area/city/rooms/inside/sparkle_pub_lounge.c
 *
 *  This is a lounge in the Boar's Head Tavern for a bit of fun, games,
 *  and possibly rowdy behavior. One fun thing you can do here is try
 *  to arm-wrestle people. This room contains quests for arm-wrestling
 *  which function "achievement" style. The quest code is located in
 *  the npc who acts as bookie for the arm wrestling.
 *
 *      /d/Sparkle/area/city/npc/skoot.c
 *
 *  Other features here include:
 *    - betting on the arm-wrestling matches
 *    - statistics that reset each day
 *    - all time records
 *    - accounting of how much money has traded hands
 *    - stools you can sit on
 *    - four different roleplay attitudes you can assign yourself
 *      while arm-wrestling to create different messages/experiences.
 *
 *  Much of the accounting code for the arm-wrestling is contained in:
 *
 *      /d/Sparkle/area/city/obj/wrestling_master.c
 *
 *  Arm wrestling data is stored at:
 *
 *      /d/Sparkle/area/city/data/wrestling_data.o
 *
 *  The data is initialized at midnight each day with the only
 *  records that do not reset being the all-time records.
 *
 *  Finally, much of the rest of the code for the experience is stored
 *  in our bookie npc, Skoot:
 *
 *      /d/Sparkle/area/city/npc/skoot.c
 *
 *  Created August 2018, by Cooper Sherry (Gorboth)
 *
 */
#pragma strict_types

#include "../../defs.h"

inherit SPARKLE_ROOM_BASE;
inherit "/d/Emerald/blackwall/delrimmon/legacy/room_chairs";

#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include <time.h>
#include "/d/Sparkle/area/city/sys/session.h"
#include "/d/Emerald/blackwall/delrimmon/legacy/room_chairs.h"


/* definitions */
#define BLOCK_NAME                 "stools"
#define ARM_WRESTLING_CHALLENGE    "_live_i_arm_wrestling_challenge"
#define ACCEPT_CHALLENGE           "_live_s_accept_challenge"
#define RESTING_FROM_MATCH         "_live_i_resting_from_arm_wrestling"
#define ARM_WRESTLING_POS          "_live_i_arm_wrestling_position"
#define WRESTLING_ATTITUDE         "_live_i_wrestling_attitude"
#define ARM_WRESTLED_THIS_LOGIN    "_live_i_arm_wrestled_today"
#define MESSAGE_SPEED              10.0
#define WRESTLING_MASTER           (OBJ_DIR + "wrestling_master")
/* arm-wrestling positions */
#define POS_PRE_LAUNCH             10
#define POS_STARTING                0
#define POS_WINNING                 1
#define POS_ABOUT_TO_WIN            2
#define POS_LOSING                 -1
#define POS_ABOUT_TO_LOSE          -2

/* Prototypes */
public void        create_sparkle();
public void        summon_skoot(int silent = 0);
public int         do_test(string arg);
public int         do_sit(string arg);
public void        do_sit_msgs(object pl, string prep, string name);
public void        do_stand_msgs(object pl, string name);
public string      look_tables();
public void        leave_inv(object ob, object dest);
public string      show_subloc(string subloc, object pl, object for_obj);
public string      sitting_on_chair(string name, object for_obj, int namesonly,
                                    int definite = 1);
public int         check_exit();
public int         do_challenge(string arg);
public object     *query_challengers();
public void        issue_challenge(object who);
public void        no_challengers_accept(object who);
public void        accept_challenge(object who);
public void        begin_challenge();
public void        arm_wrestle(int first_move = 0);
public string      gld_txt(object who, string event, mixed for_opponent = 0);
public void        wrestle_result(int pos_change, object wrestler,
                                  object opponent, string wresult);
public void        opponent_reaction(object wrestler, object opponent,
                                     string wresult);
public void        forfeit_match(object who);
public void        react_forfeit(object who);
public void        end_match(object winner, object loser, string probability);
public string      exa_blackboard();
public int         do_attitude(string arg);
public string      exa_crate();
public void        confirm_matchup();
public void        open_betting();
public void        close_betting();
public int         do_forfeit(string arg);
public int         catch_all(string str);
public int         do_bet(string arg);
public int         complete_payment(object who, string coin_type,
                                    int needed, string reason,
                                    string bet = "none");
public int         do_offer(string arg);
public void        payout_bets(string victor, string odds, int n_rounds,
                               int forfeit = 0);
public void        new_all_time_record(string record_type, string who,
                                        int record_amount);
public string      exa_payouts();
public void        display_records(object who);
public string      exa_all_time_records();
public int         near_midnight();
public void        add_wrestling_fatigue(object who, string w_status);
public string      exa_note();
public string      exa_champions();
public string      exa_betters();

public int         query_my_victories(string s)
                   { return WRESTLING_MASTER->query_victories(s); }


/* Global Variables */
public int         Rounds = 0;
public int         Betting_Open = 0;
public mapping     W_Bets = ([]);
public int         W_Alarm;
public mapping     Victories = ([]);
public mapping     Win_Odds = ([]);
public object     *Arm_Wrestlers = ({ });
public int         Whose_Turn = 0; /* whose turn is it? */
public string      This_Result;
public string      This_Probability;
public object      Opponent_Object;
public float       Round_Delay = MESSAGE_SPEED;
public float       Reaction_Delay = Round_Delay * 0.4;
public int         Opt_Out_Possible = 0;
public string     *Persona_Non_Grata = ({ });

public void        set_this_result(string s) { This_Result = s; }
public void        set_this_probability(string s) { This_Probability = s;}
public mapping     query_bets() { return W_Bets; }
public string *    query_forfeits() { return Persona_Non_Grata; }


/*
 * Function name:        create_sparkle
 * Description  :        set up the room
 */
public void
create_sparkle()
{
    set_short("in a noisy bar lounge");
    set_long("In a noisy bar lounge, off the main area of the pub. A"
     + " large shipping crate is set in the middle of the floor, and"
     + " many stools line the walls beneath a long bar that extends"
     + " along the walls to set drinks and food down. A blackboard is"
     + " on one wall for scorekeeping should anyone want to offer"
     + " a <challenge> to the room.\n\n");

    add_chair(BLOCK_NAME, "[down] [at] [in] [on] [one]"
                        + " [a] [of] [the] [open] [bar] [lounge]"
                        + " 'stool' / 'stools'",
                          10, "on", 0);

    add_item( ({ "bar", "long bar" }),
        "The long bar which runs the length of the walls in the"
      + " lounge is crowded with drinks and food that people are"
      + " picking at as they enjoy the lounge.\n");
    add_item( ({ "cat", "hellcat", "bouncer", "kiki" }),
        "Even here in the lounge you can sometimes hear the deep"
      + " thrumming purr of the hellcat from the bar north of here."
      + " It is like a constant warning against misbehavior.\n");
    add_item( ({ "purr", "deep purr", "purr of the hellcat",
                 "deep thrumming purr", "thrumming purr" }),
        "It is strangely both soothing and the stuff of"
      + " nightmares.\n");
    add_item( ({ "floor", "ground", "down" }),
        "The floor here is a bit of a mess. It sees quite a bit of"
      + " feet and almost as much spilled beer.\n");
    add_item( ({ "mess", "bit of a mess" }),
        "I suppose it would be a bit of a surprise to find it"
      + " in any other state.\n");
    add_item( ({ "state", "state of the floor" }),
        "The state of the floor is no surprise.\n");
    add_item( ({ "surprise", "any other state", "other state" }),
        "Nope.\n");
    add_item( ({ "no surprise" }),
        "Yep.\n");
    add_item( ({ "beer" }),
        "Yes, please.\n");
    add_item( ({ "spilled beer" }),
        "Tragic, but inevitable.\n");
    add_item( ({ "feet" }),
        "Everyone here seems to have them. Well, perhaps a few peg-"
      + "legs do make an appearance from time to time.\n");
    add_item( ({ "peg", "peg leg", "peg legs", "peg-leg",
                 "peg-legs" }),
        "Could you really call this a proper sailor's pub without"
      + " a few?\n");
    add_item( ({ "sailor's pub", "sailors pub", "proper pub",
                 "proper sailor's pub", "proper sailors pub" }),
        "That it be, aye ... that it be ...\n");
    add_item( ({ "barrel", "barrels", "two barrels", "low barrels",
                 "two low barrels" }),
        "They are short, and filled with something heavy to keep"
      + " them from moving during the wrestling matches. Crude, but"
      + " effective!\n");
    add_item( ({ "drink", "drinks", "food" }),
        "Such can be ordered north in the main bar, and then brought"
      + " in here to enjoy.\n");
    add_item( ({ "part of the wall", "parts of the wall",
                 "most parts of the wall" }),
        "There be a bar there .... yaaar.\n");
    add_item( ({ "wall", "walls" }),
        "Stools line the walls where people can sit and watch any"
      + " of the sport that is to be had here in the lounge. They"
      + " are snug up against a long bar that runs the length of"
      + " most parts of the wall.\n");
    add_item( ({ "west wall", "western wall", "west" }),
        "A large scoreboard is situated along the middle of the"
      + " western wall.\n");
    add_item( ({ "east wall", "eastern wall", "east" }),
        "There are a few windows on the eastern wall that overlook"
      + " the walk along the piers outside.\n");
    add_item( ({ "window", "windows" }),
        "The windows are small and filthy.\n");
    add_cmd_item( ({ "window", "windows" }),
                  ({ "open", "close" }),
        "The windows do not have hinges, and clearly are not meant"
      + " to be opened or closed.\n");
    add_item( ({ "south wall", "southern wall", "south" }),
        "The wall to the south is crowded with stools that patrons"
      + " can use to <sit> and watch the arm-wrestling.\n");
    add_item( ({ "north wall", "northern wall" }),
        "A short hallway leads through the north wall into the"
      + " main bar.\n");
    add_item( ({ "hallway", "short hallway" }),
        "The hallway leads out of the lounge and into the great"
      + " hall to the north.\n");
    add_item( ({ "here", "area", "room", "lounge", "bar lounge",
                 "noisy lounge", "noisy bar lounge", }),
        "This lounge is a place for patrons of the bar to enjoy"
      + " their sessions with a bit of sport that isn't available"
      + " in the main bar.\n");
    add_item( ({ "noise" }),
        "Well, that sort of goes without saying in most bars. Or,"
      + " well ... it goes *with* all the saying around you, to"
      + " be precise!\n");
    add_item( ({ "sport", "bit of sport" }),
        "That would be arm-wrestling. This is the place to do it"
      + " if you are up for a <challenge> !\n");
    add_item( ({ "wrestling", "arm-wrestling", "arm wrestling" }),
        "Arm-wrestling is very popular ever since Skoot set up shop"
      + " here as de-facto bookie and manager of arm-wrestling"
      + " challenges and bets. Anyone can <challenge> the room"
      + " and see if they can get a match going, and then anyone"
      + " else can <bet> on the match.\n");
    add_item( ({ "challenge" }),
        "Anyone who wants to can <challenge> the room to try to"
      + " start an arm-wrestling match.\n");
    add_item( ({ "bet", "betting" }),
        "There is a chart beneath the scoreboard listing all the"
      + " payouts for bets on the wrestling matches.\n");
    add_item( ({ "match", "matches", "wrestling match",
                 "wrestling matches" }),
        "If you are in the mood for one, you could <challenge> the"
      + " room yourself!\n");
    add_item( ({ "hall", "main hall", "north", "main bar",
                 "main area", "main area of the pub",
                 "great hall", "great hall to the north" }),
        "Things to the north are quite a bit more crowded than"
      + " what you find here, typically, but this lounge is sometimes"
      + " more fun.\n");
    add_item( ({ "pub", "tavern", "boars head tavern",
                 "boar's head tavern" }),
        "This is but a small part of the pub. The main hall of the tavern"
      + " is north of here, where most of the patrons tend to gather.\n");
    add_item( ({ "patron", "patrons", "bar patron", "bar patrons",
                 "patron of the bar", "patrons of the bar" }),
        "You are one such yourself, are you not?\n");
    add_item( ({ "session", "drinking", "drinking session",
                 "session of drinking", "sessions", "drinking",
                 "drinking sessions" }),
        "It is possible to enjoy a drinking session here, but one"
      + " would need to start it north at the main bar.\n");
    add_item( ({ "ceiling", "up", "roof", }),
        "You've seen one pub roof, you've seen them all.\n");
    add_item( ({ "pub roof" }),
        "Well, you've seen this one, at least.\n");
    add_item( ({ "stool", "stools", "bar stool", "bar stools",
                 "stool along the wall", "stools along the wall" }),
        look_tables);
    add_item( ({ "blackboard", "board", "black board", "chalkboard",
                 "score", "scores", "score board", "scoreboard",
                 "score keeping", "scorekeeping" }),
        exa_blackboard);
    add_item( ({ "crate", "shipping crate", "large crate",
                 "large shipping crate" }), exa_crate);
    add_item( ({ "list", "small list", "record", "records",
                 "all time records", "all-time records",
                 "all-time record", "all-time record",
                 "list of records", "record list",
                 "records list", "list of all time records",
                 "list of all-time records" }),
        exa_all_time_records);
    add_item( ({ "chart", "payouts", "payout", "betting payout",
                 "betting payouts", "payout chart", "payouts chart",
                 "chart of payouts", "betting chart", "betting",
                 "bets", "chart of betting",
                 "chart of betting payouts" }),
        exa_payouts);
    add_item( ({ "something", "scrawl", "lines", "lines of writing",
                 "something scrawled", "scrawled something",
                 "scrawled", "scrawled writing", "corner of the board",
                 "corner of the blackboard", "small note in the corner",
                 "note in the corner",
                 "small note in the corner of the blackboard",
                 "small note in the corner of the board",
                 "note in the corner of the board", "corner" }),
        exa_note);
    add_item( ({ "tally", "tally of champions", "champions",
                 "champions tally", "champion tally",
                 "scroll", "long scroll",
                 "scroll nailed to the wall",
                 "long scroll nailed to the wall" }),
        exa_champions);
    add_item( ({ "betters" }), exa_betters);

    add_cmd_item( ({ "chart", "payouts", "payout", "betting payout",
                 "betting payouts", "payout chart", "payouts chart",
                 "chart of payouts", "betting chart", "betting",
                 "bets", "chart of betting",
                 "chart of betting payouts" }), ({ "read" }),
        exa_payouts);
    add_cmd_item( ({ "list", "small list", "record", "records",
                 "all time records", "all-time records",
                 "all-time record", "all-time record",
                 "list of records", "record list",
                 "records list", "list of all time records",
                 "list of all-time records" }), ({ "read" }),
        exa_all_time_records);
    add_cmd_item( ({ "tally", "tally of champions", "champions",
                 "champions tally", "champion tally",
                 "scroll", "long scroll",
                 "scroll nailed to the wall",
                 "long scroll nailed to the wall" }), ({ "read" }),
        exa_champions);
    add_cmd_item( ({ "blackboard", "board", "black board", "chalkboard",
                 "score", "scores", "score board", "scoreboard",
                 "score keeping", "scorekeeping" }), ({ "read" }),
        exa_blackboard);
    add_cmd_item( ({ "something", "scrawl", "lines", "lines of writing",
                 "something scrawled", "scrawled something",
                 "scrawled", "scrawled writing", "corner of the board",
                 "corner of the blackboard", "small note in the corner",
                 "note in the corner",
                 "small note in the corner of the blackboard",
                 "small note in the corner of the board",
                 "note in the corner of the board", "corner" }),
                 ({ "read" }),
        exa_note);

    /* I do not use this feature lightly - it is very powerful and
     * should not be used often at all. However, this room is intended
     * to be a social hub for the game, and I do not want griefers to
     * be able to cause problems by making it dark. So, we'll use
     * some thematics to intentionally prevent it from ever becoming
     * dark.
     */
    add_prop(ROOM_I_LIGHT, ALWAYS_LIGHT);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_ATTACK, "You sense the dread presence of the"
      + " hellcat lurking just outside the room, and dare not!\n");
    add_prop(ROOM_M_NO_STEAL, "You sense the dread presence of the"
      + " hellcat lurking just outside the room, and dare not!\n");

    add_exit("sparkle_pub", "north", check_exit, 1, 0);

    set_no_exit_msg( ({ "northeast", "southeast", "southwest",
                        "northwest" }),
        "You poke around the corner of the lounge, but find nothing.\n");
    set_no_exit_msg( ({ "east", "west", "south" }),
        "There is a wall in that direction.\n");

    setuid();
    seteuid(getuid());

    reset_room();
} /* create_sparkle */


/*
 * Function name:       summon_skoot
 * Description  :       restore npc as needed
 * Arguments    :       int silent - true if we don't want the waitress
 *                                   to act as if she's just showing up.
 */
public void
summon_skoot(int silent = 0)
{
    object    npc;
    int       annoying_summons = 0;
    string    stxt;

    if (!present("_sparkle_pub_wrestling_manager"))
    {
        npc = clone_object(NPC_DIR + "skoot");
        npc->move(this_object());
        npc->command("emote arrives.");

        if (!silent)
        {
            npc->command("shout We be havin' a <challenge> or two"
              + " today?");
        }

        npc->arm_me();
    }
} /* summon_skoot */


/*
 * Function name:       reset_room
 * Description  :       clone sign, etcetera
 * Arguments    :       float summon delay - the delay we want for the
 *                                           arrival of the waitress.
 *                                           Default = 2.0
 */
public void
reset_room()
{
    set_alarm(0.0, 0.0, &summon_skoot(1));
} /* reset_room */


/*
 * Function name: init
 * Description:   set up the commands
 */
void
init()
{
    ::init();

    add_action(do_challenge, "challenge");
    add_action(do_challenge, "wrestle");
//  add_action(do_test, "testit");
    add_action(do_attitude, "attitude");
    add_action(do_forfeit, "forfeit");
    add_action(catch_all, "", 1);
    add_action(do_bet, "bet");
    add_action(do_offer, "offer");

    init_room_chairs();
} /* init */


/*
 * Function name:        do_test
 * Description  :        test the messages of the arm wrestling for typos
 */
public int
do_test(string arg)
{
    object  who1 = find_living("gorbjr");
    object  who2 = find_living("gorbothjr");

    if (strlen(arg))
    {
        who1->set_race_name(arg);
        who2->set_race_name(arg);
    }

/*
    wrestle_result(2, who1, who2,
                      (This_Probability + "_" + This_Result));
 */
    this_player()->catch_tell("\n" + gld_txt(who1, This_Result) + "\n");

    return 1;
} /* do_test */


/*
 * Function name:       do_sit
 * Description  :       mask parent to block "sit" and "sit down"
 * Arguments    :       string arg -- whatever the player typed
 * Returns      :       1 on success, 0 on failure
 */
public int
do_sit(string arg)
{
    if (!arg ||
        arg == "down")
    {
        notify_fail("Sit where?\n");
        return 0;
    }
    return ::do_sit(arg);
} /* do_sit */


/*
 * Function name:       do_sit_msgs
 * Description  :       mask parent so the block msgs look right
 * Arguments    :       object pl -- the person who's sitting
 *                      string prep -- the preposition
 *                      string name -- the name of the chair
 */
public void
do_sit_msgs(object pl, string prep, string name)
{
    write("You find an open stool along one of the walls, and"
      + " take a seat.\n");
    say(QCTNAME(pl) + " finds an open stool along the wall and"
      + " takes a seat.\n");
} /* do_sit_msgs */


/*
 * Function name:       do_stand_msgs
 * Description  :       mask parent so the block msgs look right
 * Arguments    :       object pl -- the person who's standing
 *                      string name -- the name of the chair
 */
public void
do_stand_msgs(object pl, string name)
{
    write("You stand up from your stool.\n");
    say(QCTNAME(pl) + " stands up from " + pl->query_possessive()
      + " stool.\n");
} /* do_stand_msgs */


/*
 * Function name:        look_tables
 * Description  :        VBFC for block; include occupants
 * Returns      :        string -- the desc
 */
public string
look_tables()
{
    return "Stools line the walls here, offering a place to <sit> if"
      + " you feel like giving your legs a rest.\n"
         + sitting_on_chair(BLOCK_NAME, this_player(), 0, 0);
} /* look_block */


/*
 * Function name:       leave_inv
 * Description  :       mask parent to be sure that departing players
 *                      are removed from table occupants
 * Arguments    :       object ob -- the departing object
 *                      object dest -- its destination
 *
 * We will use this to have a player forfeit a match if they try to leave
 * in the middle of arm wrestling.
 * 
 * If they leave via a normal exit, they've already been made to stand.
 * However, if they leave by quitting, going netdead, teleporting, etc
 * and we don't call leave_inv_room_chairs(), then they'll still look
 * as if they're here.
 */
public void
leave_inv(object ob, object dest)
{
    if (IN_ARRAY(ob, Arm_Wrestlers))
    {
        forfeit_match(ob);
    }

    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
} /* leave_inv */


/*
 * Function name:       show_subloc
 * Description  :       generate "foo is sitting ..." msg
 *                      for living's desc.
 * Arguments    :       string subloc -- the subloc
 *                      object pl -- the player
 *                      object for_obj -- who's doing the looking
 * Returns      :       string -- the "is sitting" msg
 *
 * This is a mask from the room_chairs.c code, because I don't want to
 * have it be someone sitting at "the" anything ... I want my own
 * verbage here.
 */
public string
show_subloc(string subloc, object pl, object for_obj)
{
    string      name;
    mixed       *chairptr;

    if (this_player()->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
        return "";
    }

    if (subloc != SITTING_S_SUBLOC)
    {
        return pl->show_subloc(subloc, pl, for_obj);
    }

    if (strlen(name = pl->query_prop(LIVE_S_SITTING)) &&
        pointerp(chairptr = query_room_chairs()[name]))
    {
        if (for_obj != pl)
        {
            return capitalize(pl->query_pronoun()) + " is sitting "
              + chairptr[3] + " one of the " + name + " along"
              + " the wall.\n";
        }
        return "You are sitting " + chairptr[3] + " one of the"
          + " stools along the wall.\n";
    }
    return "";
} /* show_subloc */


/*
 * Function name:       sitting_on_chair
 * Description  :       describe who's on the chair.
 * Arguments    :       string name -- the chair name
 *                      object for_obj -- who's doing the looking
 *                      int namesonly -- if true, returns only
 *                              the names of occupants, suitably
 *                              formatted, + " is" or " are"
 *                      int definite -- if true, we use a
 *                                     definite article when
 *                                     we modify the ledge name
 * Returns      :       string -- the desc of the occupants
 *
 * N.B. if namesonly is false, the returned string will have an ending
 * newline. if namesonly is true, it will not. it follows that if you
 * want to embed info about who's sitting on what in the middle of 
 * other text, you set namesonly to true and append your own location
 * string (e.g., " at the desk.").
 *
 * Ugh. I had to mask this one from the parent, too. I just didn't like
 * having the prepositions locked into "a" or "the". I needed "one"
 * or "various." (Gorboth)
 */
public string
sitting_on_chair(string name, object for_obj, int namesonly, int definite = 1)
{
    mixed       *chairptr;
    object      *occupants,
                *others;
    int         i,
                s;
    string      *names,
                 desc,
                 my_art,
                 some = " one of the ";

    my_art = (definite ? " the " : " a ");

    if (!strlen(name) ||
        !pointerp(chairptr = query_room_chairs()[name]) ||
        !(s = sizeof(occupants = chairptr[2])))
    {
        return "";
    }

    if (!objectp(for_obj))
    {
        for_obj = this_player();
    }

    if (s == 1)
    {
        if (occupants[0] != for_obj) 
        {
            desc =  occupants[0]->query_Art_name(for_obj) + " is";
        }
        else
        {
            desc = "You are";
        }
    }
    else
    {
        some = " one of the ";
        if ((i = member_array(for_obj, occupants)) < 0)
        {
            names = occupants->query_art_name(for_obj);
        }
        else
        {
            others = exclude_array(occupants, i, i);
            names = others->query_art_name(for_obj)  +  ({ "you" });
        }
        desc =  capitalize(COMPOSITE_WORDS(names)) + " are each";
    }

    if (!namesonly)
        desc += " sitting " + chairptr[3] + some + name + " along"
          + " the wall.\n";
    return desc;
} /* sitting_on_chair */


/*
 * Function name:    check_exit
 * Description  :    players will stand up before leaving if sitting
 * Returns      :    1 - cannot leave, 0 - can leave
 */
public int
check_exit()
{
    if (IN_ARRAY(this_player(), Arm_Wrestlers))
    {
        write("You cannot just leave! You'd need to <forfeit> the match"
          + " first!\n");
        return 1;
    }

    return check_sitting();
} /* check_exit */


/*
 * Function name:        do_challenge
 * Description  :        Allow a player to either instigate or accept
 *                       a challenge to arm-wrestle.
 * Arguments    :        string arg - what was typed
 * Returns      :        int 1 (always?)
 */
public int
do_challenge(string arg)
{
    object *challengers = query_challengers();
    object *lounge_patrons = FILTER_PLAYERS(all_inventory(this_object()));
    int     nm = near_midnight();
    int     just_wrestled = (time()
                          - this_player()->query_prop(RESTING_FROM_MATCH))
                          < 60;

    summon_skoot();

    if (strlen(arg) && arg != "room" && arg != "the room")
    {
        write("Skoot rumbles: That not be how it works, matey! Ye"
          + " don't choose yer' challenger. Ye just <challenge> and"
          + " see if anyone in the room be wantin' ta have a go!\n");
        return 1;
    }

    if (sizeof(lounge_patrons) < 2)
    {
        write("You are alone in the lounge. I guess you'd better"
          + " wait until someone else is in here before offering a"
          + " challenge to the room.\n");
        return 1;
    }

    if (sizeof(challengers) > 1)
    {
        if (IN_ARRAY(this_player(), challengers))
        {
            write("You have done that already, and the match is on!\n");
            return 1;
        }

        write("You will have to wait for the current match to"
          + " finish up. " + capitalize(challengers[0]->query_real_name())
          + " and " + capitalize(challengers[1]->query_real_name())
          + " are still going at it!\n");
        return 1;
    }

    if (nm)
    {
        write("There " + ((nm > 1) ? "are" : "is") + " less than "
          + LANG_NUM2WORD(nm) + " minute" + ((nm > 1) ? "s" : "")
          + " left until midnight, and Skoot has shut down wrestling"
          + " until the new day. Try again in just a bit.\n");

        return 1;
    }

    if (IN_ARRAY(this_player()->query_real_name(), Persona_Non_Grata))
    {
        write("Skoot stops you, growling: Oh no! Not ye!"
          + " We don't need shellfish like ye who be forfeitin' matches"
          + " after betting be done! Ye won't be sittin' down fer"
          + " challenges any time soon, and that's flat! I might"
          + " change me mind if ye <offer> me 20 platinum, but no"
          + " less!\n");
        return 1;
    }

    /* Someone who just arm wrestled may not start a new challenge
     * immediately. But, they can immediately respond to someone else
     * offering a new challenge.
     */
    if (just_wrestled)
    {
        write("Skoot waves you back, saying: We need to be givin'"
          + " others a chance. Let's see if anyone else wants in"
          + " fer a minute or so.\n");
        return 1;
    }
    else
    {
        this_player()->remove_prop(RESTING_FROM_MATCH);
    }

    if (this_player()->query_fatigue() <
           (this_player()->query_max_fatigue() / 6))
    {
        write("You are too tired. Best gain back some of your"
          + " energy before trying to challenge anyone.\n");
        return 1;
    }

    if (!sizeof(challengers))
    {
        if (!this_player()->query_prop(ARM_WRESTLING_CHALLENGE))
        {
            write("\nYou gaze around, sizing up the competition, getting a"
              + " sense of who might want to accept a challenge from"
              + " you. Do you want to go for it, and put yourself up"
              + " to arm-wrestle anyone in the room? It would involve"
              + " revealing your name by writing it on the challenge"
              + " board. But don't worry that it would"
              + " stick in anyone's memory (no fear of that with all"
              + " the ale going about!) So, if having people know"
              + " your name just during the challenge is acceptable"
              + " to you, issue your <challenge> one more time.\n");
            tell_room(this_object(), QCTNAME(this_player()) + " gazes"
              + " around, seemingly taking stock of who is in here"
              + " right now.\n", this_player());

            this_player()->add_prop(ARM_WRESTLING_CHALLENGE,
                                    POS_PRE_LAUNCH);
            return 1;
        }

        check_sitting();
        write("Scrawling your name on the challenge board, you decide to"
          + " show the room what you're made of. Striding"
          + " to the center of the lounge, you place your elbow on the"
          + " top of the shipping crate, offering your challenge to"
          + " everyone present.\n\n");

        Arm_Wrestlers = ({ this_player() });
        this_player()->remove_prop(ARM_WRESTLING_CHALLENGE);

        issue_challenge(this_player());
        return 1;
    }

    if (challengers[0] == this_player())
    {
        write("You've issued your challenge ... now you must wait"
          + " and see if any care to take you on.\n");
        return 1;
    }

    if (!this_player()->query_prop(ACCEPT_CHALLENGE) == 
        challengers[0]->query_real_name())
    {
        write("Finding this challenge interesting, you take a quick"
          + " moment to size up the situation. If you really do want"
          + " to accept the challenge and arm-wrestle "
          + QTNAME(challengers[0]) + ", then <challenge> one more"
          + " time to go for it.\n");
        tell_room(this_object(), QCTNAME(this_player())
          + " looks intrigued, and seems to be considering the idea"
          + " of a match.\n", this_player());

        this_player()->add_prop(ACCEPT_CHALLENGE,
                                challengers[0]->query_real_name());
        return 1;
    }

    check_sitting();
    write("\nYou accept the challenge in your fashion, sitting down at"
      + " the shipping crate and locking grips, ready to begin.\n\n");

    Arm_Wrestlers += ({ this_player() });

    accept_challenge(this_player());
    this_player()->remove_prop(ACCEPT_CHALLENGE);

    return 1;
} /* do_challenge */


/*
 * Function name:        query_challengers
 * Description  :        Provide a verified list of challengers who
 *                       are involved in Arm Wrestling.
 * Returns      :        object * array of the challenger players
 */
public object *
query_challengers()
{
    int     too_many_challengers = 0;

    /* We need to verify whether the challengers are still in the
     * lounge, and that something hasn't gone wrong in the number
     * of people involved.
     */

    if (sizeof(Arm_Wrestlers) > 2)
    {
        too_many_challengers = 1;
    }

    foreach(object challenger : Arm_Wrestlers)
    {
        if (environment(challenger) != this_object() ||
            too_many_challengers)
        {
            Arm_Wrestlers -= ({ challenger });
        }
    }

    return Arm_Wrestlers;
} /* query_challengers */


/*
 * Function name:        issue_challenge
 * Description  :        Allow a player to offer a challenge to the
 *                       room.
 * Arguments    :        object who - the player issueing the challenge
 */
public void
issue_challenge(object who)
{
    tell_room(this_object(), "\n" + gld_txt(who, "challenge_issued"), who);

    W_Alarm = set_alarm(30.0, 0.0, &no_challengers_accept(who));
} /* issue_challenge */


/*
 * Function name:        no_challengers_accept
 * Description  :        We get here if no one accepts a challenge that
 *                       has been issued to arm wrestle.
 * Arguments    :        object who - the player issueing the challenge
 */
public void
no_challengers_accept(object who)
{
    if (!IN_ARRAY(this_player(), Arm_Wrestlers) ||
        environment(this_player()) != this_object() ||
        sizeof(Arm_Wrestlers) > 1)
    {
        return;
    }

    who->catch_tell("No one seems to want to accept your challenge. You"
      + " let the room know how you feel as you leave the crate, wipe"
      + " your name off the board, and return to where you were.\n");
    tell_room(this_object(), gld_txt(who, "challenge_ignored"), who);

    Arm_Wrestlers -= ({ who });
    who->remove_prop(ARM_WRESTLING_CHALLENGE);

    return;
} /* no_challengers_accept */


/*
 * Function name:        accept_challenge
 * Description  :        Allow a player to accept the challenge
 * Arguments    :        object who - the player accepting the challenge
 */
public void
accept_challenge(object who)
{
    object  wrestler1 = Arm_Wrestlers[0];
    object  wrestler2 = Arm_Wrestlers[1];
    int     wrestler_power;
    int     opponent_power;

    /* Just to be on the safe side, let's initialize the odds mapping. */
    Win_Odds = ([]);

    tell_room(this_object(), gld_txt(who, "challenge_accepted"), who);

    /* Ability in this match is a combination of str + dis */
    wrestler_power = wrestler1->query_stat(0) + wrestler1->query_stat(5);
    opponent_power = wrestler2->query_stat(0) + wrestler2->query_stat(5);

    if (wrestler_power / opponent_power >= 2)
    {
        Win_Odds = ([ wrestler1->query_real_name() : "dominating",
                      wrestler2->query_real_name() : "hopeless" ]);
    }
    else if (opponent_power / wrestler_power >= 2)
    {
        Win_Odds = ([ wrestler1->query_real_name() : "hopeless",
                      wrestler2->query_real_name() : "dominating" ]);
    }
    else
    {
        Win_Odds = ([ wrestler1->query_real_name() : "equal",
                      wrestler2->query_real_name() : "equal" ]);
    }

    W_Alarm = set_alarm((Round_Delay * 0.3), 0.0, confirm_matchup);
} /* accept_challenge */


/*
 * Function name:        begin_challenge
 * Description  :        start the arm wrestling challenge
 */
public void
begin_challenge()
{
    object *challengers = query_challengers();

    summon_skoot();

    if (sizeof(challengers) < 2)
    {
        tell_room(this_object(), "Skoot roars: ... THE"
          + " MATCH BE FORFEIT!?? A SHAMEFUL DISPLAY!!\n");
        Rounds = 0;

        set_alarm(2.0, 0.0, &payout_bets("foo", "bar", 0, "forfeit"));
        return;
    }

    Whose_Turn = random(2);

    tell_room(this_object(), "\nSkoot shouts: BEGIN!!!\n\n");
    W_Alarm = set_alarm((Round_Delay * 0.2), 0.0, &arm_wrestle(1));

    Betting_Open = 0;

    challengers->add_prop(ARM_WRESTLED_THIS_LOGIN, 1);

    return;
} /* begin_challenge */


/*
 * Function name:        gld_txt
 * Description  :        Provide guild-specific text output for nice
 *                       variation and enjoyable things to watch in the
 *                       match based on who is involved (guild roleplay)
 * Arguments    :        object who   - the player involved,
 *                       string event - the type of event to depict
 *                       mixed for_opponent - true if the message is for
 *                                            the opponent (default false)
 *                                            if true - the opponent object
 * Returns      :        string - the text we need
 */
public string
gld_txt(object who, string event, mixed for_opponent = 0)
{
    object  who_for = ( (for_opponent) ? for_opponent : who);
    string  gtxt = "";
    string  guild_name = who->query_guild_name_occ();
    string  demeanor = "";
    string  he = who->query_pronoun();
    string  him = who->query_objective();
    string  his = who->query_possessive();
//  string  tcname = who->query_The_name(who_for);
//  string  tname = who->query_the_name(who_for);
    string  tcname = capitalize(who->query_real_name());
    string  tname = tcname;
    string  his_opnt = ((for_opponent) ? "you" : his + " opponent");
    string  his_opnts = ((for_opponent) ? "your" : his + " opponent's");
    string  attitude = who->query_prop(WRESTLING_ATTITUDE);

    switch(guild_name)
    {
    case "Angmar Army":
        demeanor = "aggressive";
        break;
    case "Army of Darkness":
        demeanor = "aggressive";
        break;
    case "Ansalon Elvish Archers":
        demeanor = "determined";
        break;
    case "Calian warrior's guild":
        demeanor = "determined";
        break;
    case "Cult of Chemosh":
        demeanor = "aloof";
        break;
    case "Dwarven Warriors of the Neidar Clan":
        demeanor = "aggressive";
        break;
    case "Elemental Clerics of Calia":
        demeanor = "determined";
        break;
    case "Dragonarmy":
        demeanor = "aggressive";
        break;
    case "Gladiator guild":
        demeanor = "aggressive";
        break;
    case "Secret Society of Uncle Trapspringer":
        demeanor = "goofy";
        break;
    case "Solamnian Knights":
        demeanor = "determined";
        break;
    case "Morgul Mages":
        demeanor = "aloof";
        break;
    case "Free Mercenary Guild":
        demeanor = "determined";
        break;
    case "Thornlin Militia":
        demeanor = "determined";
        break;
    case "Order of the Dragon":
        demeanor = "aloof";
        break;
    case "Priests of Takhisis":
        demeanor = "aloof";
        break;
    case "Rangers of the Westlands":
        demeanor = "determined";
        break;
    case "School of High Magic":
        demeanor = "determined";
        break;
    case "Union of the Warriors of Shadow":
        demeanor = "aloof";
        break;
    case "Wizards of High Sorcery":
        demeanor = "aloof";
        break;
    default:
        switch(who->query_race_name())
        {
        case "elf":
        case "wraith":
        case "drow":
        case "presence":
            demeanor = "aloof";
            break;
        case "hobbit":
        case "kender":
        case "halfling":
        case "gnome":
            demeanor = "goofy";
            break;
        case "goblin":
        case "ogre":
        case "orc":
        case "hobgoblin":
            demeanor = "aggressive";
            break;
        case "human":
        case "dwarf":
        case "minotaur":
        case "half-elf":
        case "efreet":
        case "wisp":
        case "golem":
        case "tempest":
        default:
            demeanor = "determined";
            break;
        }
        break;
    }

    if (attitude)
    {
        demeanor = attitude;
    }

    switch(event)
    {
    case "challenge_ignored":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = "Standing up, " + tname + " roars: Cowards! You are"
              + " all COWARDS!! Worthless ... and ... weak.\n"
              + capitalize(he) + " walks away from the crate snarling"
              + " in amusement, wiping " + his + " name off of the board.";
            break;
        case "aloof":
            gtxt = "With no apparent challengers, " + tname + " rises,"
              + " nods silently at the room, and walks away from the"
              + " shipping crate, pausing to wipe " + his + " name off"
              + " of the board.";
            break;
        case "goofy":
            gtxt = tcname + " blinks in disbelief and whines: But! ..."
              + " but!! ... it would have been so fun!\n"
              + capitalize(he) + " sighs deeply and walks away from"
              + " the shipping crate to wipe " + his + " name off of"
              + " the board.";
            break;
        case "determined":
        default:
            gtxt = tcname + " frowns slightly and says: So be it ..."
              + " perhaps another time.\n"
              + "Rising, " + tname + " walks from the shipping crate"
              + " and wipes " + his + " name off of the board.";
            break;
        }
        break;
    case "challenge_issued":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " bellows loudly for all the room to hear,"
              + " scrawls " + his + " name on the challenge board, and"
              + " then strides with a snarl toward the shipping crate."
              + " Straddling a barrel on one side, " + he + " slams "
              + his + " elbow down and proclaims: Who will <challenge>"
              + " me?!";
            break;
        case "aloof":
            gtxt = tcname + " rises and writes " + his + " name on the"
              + " challenge board. Quietly approaching the shipping crate, "
              + he + " sits upon a barrel and slowly extends "
              + his + " elbow out for all to see. Clearly, this is"
              + " a <challenge> you could accept, if you wished to"
              + " take " + him + " on at arm-wrestling.";
            break;
        case "goofy":
            gtxt = tcname + " tiptoes over to scribble " + his + " name"
              + " on the challenge board and then"
              + " leaps suddenly onto a barrel beside"
              + " the shipping crate at the center of the room and"
              + " chirps: C'mon people!! Who will <challenge> me!?"
              + " You know you want to ... but maybe you're all too"
              + " chicken??";
            break;
        case "determined":
        default:
            gtxt = "Crossing the room to write " + his + " name on the"
              + " challenge board, " + tname + " offers a slight smile"
              + " and sits at the shipping crate."
              + " Extending " + his + " elbow out onto the surface, "
              + he + " looks at everyone with raised eyebrows and"
              + " asks: Anybody up for a <challenge> ?";
            break;
        }
        break;
    case "challenge_accepted":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " adds " + his + " name to the board and"
              + " then shouts: Oh, so you want me to teach you"
              + " a lesson, do you??\n"
              + "Snarling savagely, " + he + " plants " + him + "self"
              + " on the opposite side of the crate and accepts the"
              + " challenge, planting " + his
              + " elbow firmly in place.";
            break;
        case "aloof":
            gtxt = tcname + " adds " + his + " name to the board and"
              + " then calmly approaches, sits down in silence,"
              + " locks both gaze and hands, and plants " + his
              + " elbow down on the crate to accept the challenge.";
            break;
        case "goofy":
            gtxt = tcname + " adds " + his + " name to the board and"
              + " bounces over to the crate and perches on"
              + " a barrel, giggling happily, to accept the challenge"
              + " with an elbow planted firmly in place.";
            break;
        case "determined":
        default:
            gtxt = "Sniffing suddenly, " + tname + " adds " + his
              + " name to the board, marches forward, sits, plants an"
              + " elbow in place, and smiles with"
              + " determination to accept the challenge.";
            break;
        }
        break;
    case "hopeless_launch":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " snarls like a frenzied wolverine, throwing "
              + his + " entire body into what amounts to literally"
              + " zero movement whatsoever versus " + his_opnts
              + " steady arm position.";
            break;
        case "aloof":
            gtxt = tcname + " is motionless for a brief second, and then"
              + " flinches with sudden energy in a huge opening effort,"
              + " that ... fails to move " + his_opnts + " arm"
              + " position even slightly.";
            break;
        case "goofy":
            gtxt = tcname + " shrieks triumphantly as " + he + " nearly"
              + " jumps off the barrel in an opening move that"
              + " seems to do absolutely nothing whatsoever to "
              + his_opnts + " arm position.";
            break;
        case "determined":
        default:
            gtxt = tcname + " grunts heavily and gives everything "
              + he + "'s got to a huge opening thrust. Though the"
              + " volume of the grunting increases, there is not"
              + " one inch of movement against " + his_opnts
              + " arm position.";
            break;
        }
        break;
    case "hopeless_launch_reaction":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " snarls: You know - that was TRULY PATHETIC!!"
              + " I thought this would be amusing, but now I'm just bored!";
            break;
        case "aloof":
            gtxt = tcname + " says nothing, but smiles slightly and"
              + " shakes " + his + " head as if to say: not"
              + " a chance.";
            break;
        case "goofy":
            gtxt = tcname + " actually bursts out laughing, and chirps:"
              + " Oh boy! This is going to be hilarious!";
            break;
        case "determined":
        default:
            gtxt = tcname + " frowns slightly, almost with a pitying"
              + " look on " + his + " face, which then breaks into"
              + " a grin.";
            break;
        }
        break;
    case "equal_launch":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " snarls and lurches forward with a sudden"
              + " burst of effort that is met by " + his_opnts
              + " firm resistance."
              + " As both fists quiver to and fro, neither makes"
              + " any real progress.";
            break;
        case "aloof":
            gtxt = tcname + " shifts silently with a sudden"
              + " burst of effort that is met by " + his_opnts
              + " firm resistance."
              + " As both fists quiver to and fro, neither makes"
              + " any real progress.";
            break;
        case "goofy":
            gtxt = tcname + " squeals and bounces around with a sudden"
              + " burst of effort that is met by " + his_opnts
              + " firm resistance."
              + " As both fists quiver to and fro, neither makes"
              + " any real progress.";
            break;
        case "determined":
        default:
            gtxt = tcname + " grunts with a sudden"
              + " burst of effort that is met by " + his_opnts
              + " firm resistance."
              + " As both fists quiver to and fro, neither makes"
              + " any real progress.";
            break;
        }
        break;
    case "equal_launch_reaction":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " laughs savagely, " + his + " eyes"
              + " glaring with fury as " + he + " struggles against "
              + his_opnts + " efforts.";
            break;
        case "aloof":
            gtxt = tcname + " breathes evenly, " + his + " eyes"
              + " narrowing in concentration as " + he + " works to"
              + " hold " + his_opnt + " in check.";
            break;
        case "goofy":
            gtxt = tcname + " huffs and puffs, " + his + " eyes"
              + " bulging in surprise as " + he + " struggles to"
              + " keep the match from turning quickly against " + him
              + ".";
            break;
        case "determined":
        default:
            gtxt = tcname + " winces and hunches forward, " + his
              + " frame working for leverage as " + he + " struggles"
              + " to maintain equilibrium.";
            break;
        }
        break;
    case "dominating_launch":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " roars and throws " + his + " arm forward"
              + " in a thrust that almost ends the match outright. "
              + capitalize (he) + " laughs and shouts: You are nothing!!";
            break;
        case "aloof":
            gtxt = tcname + " is still for a moment, before suddenly"
              + " casting " + his + " arm forward in a thrust that"
              + " nearly forces " + his_opnts + " fist to the crate. "
              + capitalize (he) + " says nothing, but smirks ever so"
              + " slightly.";
            break;
        case "goofy":
            gtxt = tcname + " shouts: Whoooops!! and throws " + his
              + " arm forward in a move that almost wins the contest. "
              + capitalize (he) + " starts to giggle.";
            break;
        case "determined":
        default:
            gtxt = tcname + " makes eye contact as " + he + " throws "
              + his + " powerful arm forward, nearly ending the match. "
              + capitalize (he) + " smiles and raises an eyebrow as"
              + " if to say: Shall we end it here?";
            break;
        }
        break;
    case "dominating_launch_reaction":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " growls in rage and begins pounding the"
              + " crate with " + his + " opposite fist in desperation!";
            break;
        case "aloof":
            gtxt = tcname + " looks quickly between " + his + " own fist"
              + " and the crate a few times.";
            break;
        case "goofy":
            gtxt = tcname + " panics and begins wiggling around in "
              + his + " seat, trying desperately not to lose!";
            break;
        case "determined":
        default:
            gtxt = tcname + " blinks in surprise and bears down, working"
              + " desperately to stave off defeat!";
            break;
        }
        break;
    case "hopeless_recovery":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " howls in sudden blazing fury, and thrusts "
              + his_opnts + " arm, against all odds, back into the"
              + " starting position!";
            break;
        case "aloof":
            gtxt = tcname + " rises in silent menace, and thrusts "
              + his_opnts + " arm, against all odds, back into the"
              + " starting position!";
            break;
        case "goofy":
            gtxt = tcname + " cackles like a maddened hen, thrusting "
              + his_opnts + " arm, against all odds, back into the"
              + " starting position!";
            break;
        case "determined":
        default:
            gtxt = tcname + " taps into hidden reserves, thrusting "
              + his_opnts + " arm, against all odds, back into the"
              + " starting position!";
            break;
        }
        break;
    case "hopeless_recovery_reaction":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " chokes and " + his + " eyes widen in"
              + " shock. " + capitalize(he) + " then throws " + his
              + " head back and, cackling, shouts: I love it!!! You're"
              + " not as boring as I thought you'd be!";
            break;
        case "aloof":
            gtxt = tcname + "'s eyes widen for the briefest instant"
              + " in surprise. Then, smiling slightly, " + he
              + " nods in respect.";
            break;
        case "goofy":
            gtxt = tcname + " squeals in surprise, and shouts:"
              + " Hey, what??! " + capitalize(he) + " then beams"
              + " brightly and begins to laugh.";
            break;
        case "determined":
        default:
            gtxt = tcname + " blinks in surprise and seems, just for"
              + " a moment, at a bit of a loss.";
            break;
        }
        break;
    case "equal_recovery":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " grinds " + his + " teeth together in"
              + " rage, slowly working " + his_opnts + " arm back into"
              + " the starting position!";
            break;
        case "aloof":
            gtxt = tcname + " twists " + his + " entire body in slow"
              + " and careful effort, working " + his_opnts + " arm back"
              + " into the starting position!";
            break;
        case "goofy":
            gtxt = tcname + " bulges " + his + " eyes in effort,"
              + " moving " + his_opnts + " arm gradually back into"
              + " the starting position!";
            break;
        case "determined":
        default:
            gtxt = tcname + " hisses air through " + his
              + " pursed lips as " + he + " slowly moves " + his_opnts
              + " arm back into the starting position!";
            break;
        }
        break;
    case "equal_recovery_reaction":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " growls in frustration, stomping " + his
              + " feet into position for better leverage.";
            break;
        case "aloof":
            gtxt = tcname + " locks eyes with " + his_opnt
              + ", stiffening with effort.";
            break;
        case "goofy":
            gtxt = tcname + " begins to hyperventilate slightly.";
            break;
        case "determined":
        default:
            gtxt = tcname + " lowers " + his + " head and arches"
              + " forward to try for better leverage.";
            break;
        }
        break;
    case "dominating_recovery":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " shakes " + his + " head with a savage grin"
              + " and moves " + his_opnts + " arm quickly back into"
              + " the starting position, saying: I DON'T THINK SO!";
            break;
        case "aloof":
            gtxt = tcname + " appears to relax, and with no apparent"
              + " effort moves " + his_opnts + " arm smoothly back into"
              + " the starting position.";
            break;
        case "goofy":
            gtxt = tcname + " starts to whistle a merry tune as " + he
              + " winks and then easily moves " + his_opnts + " arm"
              + " back into the starting position.";
            break;
        case "determined":
        default:
            gtxt = tcname + " chuckles genuinely as " + he
              + " effortlessly moves " + his_opnts + " arm back into"
              + " the starting position.";
            break;
        }
        break;
    case "dominating_recovery_reaction":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " begins to froth at the mouth, doing"
              + " everything in " + his + " power against " + his_opnts
              + " superior strength.";
            break;
        case "aloof":
            gtxt = tcname + " writhes slightly, trying to find a way"
              + " to prevail against " + his_opnts
              + " superior strength.";
            break;
        case "goofy":
            gtxt = tcname + " wails in despair, working and squirming"
              + " against " + his_opnts + " superior strength.";
            break;
        case "determined":
        default:
            gtxt = tcname + " looks in alarm at " + his_opnt
              + ", watching as all gains are lost.";
            break;
        }
        break;
    case "hopeless_advance":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " roars and pushes with all the fury "
              + he + " can muster. Somehow, it works, and " + his_opnts
              + " arm is moved closer to the crate.";
            break;
        case "aloof":
            gtxt = tcname + " summons forth power hidden deep within,"
              + " somehow managing to push " + his_opnts
              + " arm closer to the crate.";
            break;
        case "goofy":
            gtxt = tcname + " bounces up and down on " + his + " seat"
              + " while pushing like crazy. Amazingly, " + his_opnts
              + " arm inches closer to the crate.";
            break;
        case "determined":
        default:
            gtxt = tcname + " grunts, teeth gritted, and twists "
              + his + " entire body in effort. Surpisingly, " + his_opnts
              + " arm inches closer to the crate.";
            break;
        }
        break;
    case "hopeless_advance_reaction":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " bellows in surprise and looks outraged.";
            break;
        case "aloof":
            gtxt = tcname + " seems genuinely nonplussed.";
            break;
        case "goofy":
            gtxt = tcname + " blinks in disbelief!";
            break;
        case "determined":
        default:
            gtxt = tcname + " frowns, seemingly taken aback.";
            break;
        }
        break;
    case "equal_advance":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " wrenches violently, bearing down with"
              + " a loud snarl. " + capitalize(he) + " roars in"
              + " delight as " + his_opnts
              + " arm is moved closer to the crate.";
            break;
        case "aloof":
            gtxt = tcname + " lowers slowly and twists, bearing down to move "
              + his_opnts + " arm closer to the crate.";
            break;
        case "goofy":
            gtxt = tcname + " snarls like an angry squirrel, " + his
              + " eyebrows arching madly as " + he + " pushes "
              + his_opnts + " arm closer to the crate.";
            break;
        case "determined":
        default:
            gtxt = tcname + " breathes rapidly through " + his
              + " nose, pushing hard as " + he + " moves "
              + his_opnts + " arm closer to the crate.";
            break;
        }
        break;
    case "equal_advance_reaction":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " growls, and begins to shake with effort.";
            break;
        case "aloof":
            gtxt = tcname + " bows " + his + " head to"
              + " concentrate intensely.";
            break;
        case "goofy":
            gtxt = tcname + " shudders, puffing " + his + " cheeks"
              + " in and out with considerable exertion.";
            break;
        case "determined":
        default:
            gtxt = tcname + " gasps slightly, working with great"
              + " effort against the thrust.";
            break;
        }
        break;
    case "dominating_advance":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " grins savagely and jerks " + his
              + " arm forward effortlessly, stopping on purpose"
              + " with " + his_opnts + " arm slightly closer to"
              + " the crate, as if toying with " + his + " prey.";
            break;
        case "aloof":
            gtxt = tcname + " cocks " + his + " head at " + his_opnt
              + " and advances " + his + " arm a small"
              + " amount, stopping intentionally, as if to make a point.";
            break;
        case "goofy":
            gtxt = tcname + " pretends to be scared, and then quickly"
              + " advances " + his + " arm a little way forward,"
              + " stopping intentionally, and then breaking into a grin.";
            break;
        case "determined":
        default:
            gtxt = tcname + " advances " + his + " arm forward a bit,"
              + " stops, and then raises a playful eyebrow at "
              + his_opnt + ".";
            break;
        }
        break;
    case "dominating_advance_reaction":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " bellows in frustration and outrage.";
            break;
        case "aloof":
            gtxt = tcname + " seems a bit thrown off.";
            break;
        case "goofy":
            gtxt = tcname + " blinks in disbelief and frustration!";
            break;
        case "determined":
        default:
            gtxt = tcname + " blanches and tries to refocus.";
            break;
        }
        break;
    case "hopeless_nonrecovery":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " snarls and shudders, violently working"
              + " in vain for any kind of recovery, but it doesn't"
              + " get " + him + " anywhere.";
            break;
        case "aloof":
            gtxt = tcname + " silently writhes, seeking any way to"
              + " try to recover, but achieves nothing.";
            break;
        case "goofy":
            gtxt = tcname + " almost turns blue, trying in desperation"
              + " to stave off loss. Jerking this way and that, all of "
              + his + " efforts to recover are almost sad to watch.";
            break;
        case "determined":
        default:
            gtxt = tcname + " gnashes " + his + " teeth, twisting for"
              + " any kind of position to gain leverage toward recovery,"
              + " but fails to thwart " + his_opnts + " advantage"
              + " even slightly.";
            break;
        }
        break;
    case "hopeless_nonrecovery_reaction":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " snorts: Pah. This is getting boring"
              + " already!";
            break;
        case "aloof":
            gtxt = tcname + " says nothing, but cocks " + his + " head"
              + " slightly, perhaps amused.";
            break;
        case "goofy":
            gtxt = tcname + " beams and tries not to giggle.";
            break;
        case "determined":
        default:
            gtxt = tcname + " smiles, almost looking friendly.";
            break;
        }
        break;
    case "equal_nonrecovery":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " slavers and heaves, snarling in an"
              + " attempt to recover which is met with " + his_opnts
              + " equal resistance, and thus thwarted.";
            break;
        case "aloof":
            gtxt = tcname + " twists for slow leverage, attempting to"
              + " recover, but cannot move things against " + his_opnts
              + " position at all.";
            break;
        case "goofy":
            gtxt = tcname + " hisses like a little fox, trying for"
              + " leverage against " + his + " poor position, but is"
              + " thwarted by " + his_opnts + " equal strength.";
            break;
        case "determined":
        default:
            gtxt = tcname + " whimpers slightly, working with an iron"
              + " effort to recover, but is thwarted by " + his_opnts
              + " equal strength.";
            break;
        }
        break;
    case "equal_nonrecovery_reaction":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " snarls, and " + his
              + " eyes burn eagerly.";
            break;
        case "aloof":
            gtxt = tcname + " releases a slow and even breath in"
          + " preparation.";
            break;
        case "goofy":
            gtxt = tcname + " pales a bit with effort, but inhales"
          + " for the next push with twinkling eyes.";
            break;
        case "determined":
        default:
            gtxt = tcname + " inhales and braces for the next push,"
          + " confident determination in " + his + " eyes.";
            break;
        }
        break;
    case "dominating_nonrecovery":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " pouts in mock fear as " + he + " pushes"
              + " for an easy recovery, only to be met with heroic and"
              + " unexpected resistance. " + capitalize(his)
              + " eyes bulge in complete shock as " + he
              + " looks up at " + his_opnt + "!";
            break;
        case "aloof":
            gtxt = tcname + " smiles calmly as " + he + " pushes"
              + " for an easy recovery, only to be met with heroic and"
              + " unexpected resistance. " + capitalize(his)
              + " eyes flinch in brief surprise as " + he
              + " looks up at " + his_opnt + "!";
            break;
        case "goofy":
            gtxt = tcname + " giggles confidently as " + he + " pushes"
              + " for an easy recovery, only to be met with heroic and"
              + " unexpected resistance. " + capitalize(his)
              + " eyes blink rapidly in total shock as " + he
              + " looks up at " + his_opnt + "!";
            break;
        case "determined":
        default:
            gtxt = tcname + " grins relaxedly as " + he + " pushes"
              + " for an easy recovery, only to be met with heroic and"
              + " unexpected resistance. " + capitalize(his)
              + " face freezes in true shock as " + he
              + " looks up at " + his_opnt + "!";
            break;
        }
        break;
    case "dominating_nonrecovery_reaction":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " bellows loudly in triumph!";
            break;
        case "aloof":
            gtxt = tcname + " seems to rise in " + his + " seat, eyes"
          + " triumphant!";
            break;
        case "goofy":
            gtxt = tcname + " babbles: Yes! Yes!! Yes!!!";
            break;
        case "determined":
        default:
            gtxt = tcname + " breaks into a triumphant grin!";
            break;
        }
        break;
    case "hopeless_stalemate":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " bellows and stomps, throwing violent"
              + " energy and rage into a huge effort that"
              + " does absolutely no good against " + his_opnt + ".";
            break;
        case "aloof":
            gtxt = tcname + " twists and strains, pouring all manner"
              + " of effort and movements into what amounts to"
              + " absolutely nothing whatsoever against " + his_opnt + ".";
            break;
        case "goofy":
            gtxt = tcname + " yelps, whimpers, babbles, and coughs,"
              + " wrenching " + his + " entire body in all sorts of"
              + " efforts, none of which do one bit of good"
              + " against " + his_opnt + ".";
            break;
        case "determined":
        default:
            gtxt = tcname + " groans loudly, putting " + his + " entire"
              + " body into all sorts of pushing and wrenching that"
              + " get " + him + " nowhere against " + his_opnt + ".";
            break;
        }
        break;
    case "hopeless_stalemate_reaction":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " taunts: This is hilarious! Are you trying"
              + " to tickle me?!?";
            break;
        case "aloof":
            gtxt = tcname + " seems very unimpressed.";
            break;
        case "goofy":
            gtxt = tcname + " teases: Oh, sorry, are we starting now?";
            break;
        case "determined":
        default:
            gtxt = tcname + " coughs politely, and grins.";
            break;
        }
        break;
    case "equal_stalemate":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " growls and snarls, pushing violently"
              + " only to meet with " + his_opnts + " equal resistance,"
              + " thus making no progress.";
            break;
        case "aloof":
            gtxt = tcname + " bears silently down, concentrating"
              + " intensely against " + his_opnts + " equal force, making"
              + " no gains.";
            break;
        case "goofy":
            gtxt = tcname + " sniffs and pushes madly, working with all "
              + his + " might against " + his_opnts + " equal strength,"
              + " unable to make any advance.";
            break;
        case "determined":
        default:
            gtxt = tcname + " breathes furiously, finding all"
              + " efforts met by " + his_opnts + " equal resistance that hold "
              + him + " from any forward movement.";
            break;
        }
        break;
    case "equal_stalemate_reaction":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " growls dangerously, and " + his
              + " eyes burn with rage.";
            break;
        case "aloof":
            gtxt = tcname + " offers the slightest hiss, betraying"
              + " fierce effort on " + his + " part.";
            break;
        case "goofy":
            gtxt = tcname + " grimaces, and begins to sweat"
              + " profusely!";
            break;
        case "determined":
        default:
            gtxt = tcname + " seems to stop breathing, and closes "
              + his + " eyes with the effort to hold things where"
              + " they are.";
            break;
        }
        break;
    case "dominating_stalemate":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " grins maliciously as " + he + " pushes"
              + " for an easy win, but " + his_opnts + " resolve is"
              + " heroically brought forth. " + capitalize(his)
              + " eyes bulge in momentary shock as " + he
              + " gets nowhere!";
            break;
        case "aloof":
            gtxt = tcname + " smiles slightly as " + he + " pushes"
              + " for an easy win, but " + his_opnts + " resolve is"
              + " heroically brought forth. " + capitalize(his)
              + " eyes widen in momentary shock as " + he
              + " gets nowhere!";
            break;
        case "goofy":
            gtxt = tcname + " giggles uncontrollably as " + he + " pushes"
              + " for an easy win, but " + his_opnts + " resolve is"
              + " heroically brought forth. " + capitalize(his)
              + " eyes blink rapidly in momentary shock as " + he
              + " gets nowhere!";
            break;
        case "determined":
        default:
            gtxt = tcname + " grins happily as " + he + " pushes"
              + " for an easy win, but " + his_opnts + " resolve is"
              + " heroically brought forth. " + capitalize(his)
              + " face freezes in momentary shock as " + he
              + " gets nowhere!";
            break;
        }
        break;
    case "dominating_stalemate_reaction":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " roars in surprised triumph!";
            break;
        case "aloof":
            gtxt = tcname + " glares in silent determination.";
            break;
        case "goofy":
            gtxt = tcname + " babbles: I can't believe that worked!!";
            break;
        case "determined":
        default:
            gtxt = tcname + " grins with fierce determination!";
            break;
        }
        break;
    case "hopeless_sudden_victory":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " erupts in a frenzied blood-curdling"
              + " scream that shatters a nearby glass! With a sudden"
              + " and shocking SLAM!! " + he + " throws " + his_opnts
              + " fist down to the crate, winning the match!!";
            break;
        case "aloof":
            gtxt = tcname + " twists in an uncanny and disturbing way"
              + " that, with a blaze of unexpected motion, throws "
              + his_opnts + " fist to the crate for an immediate"
              + " and decisive victory!!";
            break;
        case "goofy":
            gtxt = tcname + " shrieks like a goose from hell, whipping"
              + " forward shockingly to drive " + his_opnts + " fist"
              + " against the crate in a sudden and astounding total"
              + " victory!!";
            break;
        case "determined":
        default:
            gtxt = tcname + " cries out with sudden passion and,"
              + " finding some hidden strength, blasts forward to"
              + " pin " + his_opnts + " fist to the crate, winning"
              + " the match!!";
            break;
        }
        break;
    case "hopeless_sudden_victory_reaction":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " sits with with " + his + " mouth hanging"
              + " open, stunned in absolute disbelief!";
            break;
        case "aloof":
            gtxt = tcname + " does not move, and seems to be trying to"
              + " comprehend what has just happened.";
            break;
        case "goofy":
            gtxt = tcname + " blinks rapidly for a minute, and then"
              + " falls off " + his + " barrel, and lies thunderstruck on the"
              + " ground!";
            break;
        case "determined":
        default:
            gtxt = tcname + " looks absolutely stunned, and then bursts"
              + " into astonished laughter!";
            break;
        }
        break;
    case "equal_sudden_victory":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " bellows suddenly in hideous wrath and"
              + " fury, ripping forward with bulging muscles to send "
              + his_opnts + " fist instantly to the crate with a"
              + " loud THUMP!";
            break;
        case "aloof":
            gtxt = tcname + " twitches with sudden blazing speed"
              + " and power, driving " + his_opnts + " unprepared"
              + " fist instantly to the crate with a loud THUMP!";
            break;
        case "goofy":
            gtxt = tcname + " hoots a sudden cry of ferocity and"
              + " blasts forward, taking " + his_opnt + " by complete"
              + " surprise, and driving downward to the crate with"
              + " a loud THUMP!";
            break;
        case "determined":
        default:
            gtxt = tcname + " cries aloud with sudden determination"
              + " and spirit, throwing " + his + " entire body into"
              + " a burst of power that sends " + his_opnts + " fist"
              + " into the crate with a loud THUMP!";
            break;
        }
        break;
    case "equal_sudden_victory_reaction":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " roars in surprised defeat!";
            break;
        case "aloof":
            gtxt = tcname + " glares in silent defeat.";
            break;
        case "goofy":
            gtxt = tcname + " babbles: What?! No ... no !!";
            break;
        case "determined":
        default:
            gtxt = tcname + " blinks in sudden defeat!";
            break;
        }
        break;
    case "dominating_sudden_victory":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " taunts: Let's just put you out of your"
              + " misery, now, shall we?\n" + capitalize(he) 
              + " then presses " + his_opnts + " fist directly to"
              + " the crate in one smooth motion for an easy and"
              + " immediate win.";
            break;
        case "aloof":
            gtxt = tcname + " says: Enough of this.\n" + capitalize(he) 
              + " then presses " + his_opnts + " fist directly to"
              + " the crate in one smooth motion for an easy and"
              + " immediate win.";
            break;
        case "goofy":
            gtxt = tcname + " teases: Who's next?\n" + capitalize(he) 
              + " then presses " + his_opnts + " fist directly to"
              + " the crate in one smooth motion for an easy and"
              + " immediate win.";
            break;
        case "determined":
        default:
            gtxt = tcname + " proclaims: Good match,"
              + " yes, but let's end it now.\n" + capitalize(he) 
              + " then presses " + his_opnts + " fist directly to"
              + " the crate in one smooth motion for an easy and"
              + " immediate win.";
            break;
        }
        break;
    case "dominating_sudden_victory_reaction":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " grumbles loudly.";
            break;
        case "aloof":
            gtxt = tcname + " nods quietly.";
            break;
        case "goofy":
            gtxt = tcname + " sniffs in annoyance!";
            break;
        case "determined":
        default:
            gtxt = tcname + " nods, acknowledging defeat.";
            break;
        }
        break;
    case "hopeless_slow_victory":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " seems to enter some kind of absolute"
              + " battle frenzy, shrieking like an animal as " + he
              + " somehow manages to grind " + his_opnts + " fist"
              + " down bit by bit until it finally is pressed to"
              + " the crate!";
            break;
        case "aloof":
            gtxt = tcname + " inhales quietly, and then appears to"
              + " enter some kind of trance, summoning uncanny reserves"
              + " of hidden strength. Slowly, unbelievably, "
              + his_opnts + " fist is pressed down into the crate!";
            break;
        case "goofy":
            gtxt = tcname + " begins to babble, almost as if speaking"
              + " in tongues! Trembling as the words become louder and"
              + " more shrill, " + his_opnts + " locked fist is moved"
              + " amazingly, surely"
              + " downward to slowly press to the crate!";
            break;
        case "determined":
        default:
            gtxt = tcname + " bares " + his + " teeth and " + his
              + " eyes widen to almost frightening orbs. Finding"
              + " strength no one could have predicted, " + he
              + " curls " + his + " entire body in effort as "
              + his_opnts + " locked fist is pushed downward, closer,"
              + " closer - finally onto the crate!";
            break;
        }
        break;
    case "hopeless_slow_victory_reaction":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " jerks back, all pride and arrogance wiped"
              + " from " + his + " red and blushing face!";
            break;
        case "aloof":
            gtxt = tcname + " peers at " + his_opnt + " with wide"
              + " and burning eyes, clearly in disbelief.";
            break;
        case "goofy":
            gtxt = tcname + " screams in shock and dismay, then sits"
              + " blinking, slowly grinning in amazement.";
            break;
        case "determined":
        default:
            gtxt = tcname + " sits and stares at " + his_opnt + " for"
              + " a moment, dazed by the outcome.";
            break;
        }
        break;
    case "equal_slow_victory":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " begins to snarl, then growl, then roar,"
              + " slowly moving " + his_opnts + " fist closer and"
              + " closer until it finally is pressed to the crate"
              + " for the win.";
            break;
        case "aloof":
            gtxt = tcname + " bows " + his + " head lower and lower,"
              + " slowly moving " + his_opnts + " fist closer and"
              + " closer until it finally is pressed to the crate"
              + " for the win.";
            break;
        case "goofy":
            gtxt = tcname + " quivers, then wiggles, then bounces,"
              + " slowly moving " + his_opnts + " fist closer and"
              + " closer until it finally is pressed to the crate"
              + " for the win.";
            break;
        case "determined":
        default:
            gtxt = tcname + " begins to grunt, then groan, then yell,"
              + " slowly moving " + his_opnts + " fist closer and"
              + " closer until it finally is pressed to the crate"
              + " for the win.";
            break;
        }
        break;
    case "equal_slow_victory_reaction":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " roars in frustration and fury!";
            break;
        case "aloof":
            gtxt = tcname + " sits back silently, frowning.";
            break;
        case "goofy":
            gtxt = tcname + " slaps " + his + " hands on the crate!";
            break;
        case "determined":
        default:
            gtxt = tcname + " scowls at " + his + " loss.";
            break;
        }
        break;
    case "dominating_slow_victory":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " chuckles cruelly, " + his + " eyes"
              + " dancing with pleasure as " + he + " easily pushes "
              + his_opnts + " fist down into the crate for the"
              + " win.";
            break;
        case "aloof":
            gtxt = tcname + " peers into " + his_opnts + " eyes and"
              + " then easily presses downward to win the match with"
              + " a barely perceptible smile on " + his + " lips.";
            break;
        case "goofy":
            gtxt = tcname + " pretends to struggle, then winks at "
              + his_opnt + " as " + he + " presses down for a"
              + " seemingly easy win.";
            break;
        case "determined":
        default:
            gtxt = tcname + " seems to decide that this has gone on"
              + " long enough and easily presses " + his_opnts
              + " gripped fist to the crate for the win.";
            break;
        }
        break;
    case "dominating_slow_victory_reaction":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " looks briefly enraged, but then nods in"
              + " admiration of such clearly superior strength.";
            break;
        case "aloof":
            gtxt = tcname + " appears unconcerned, as if this was"
              + " an expected outcome.";
            break;
        case "goofy":
            gtxt = tcname + " facepalms, as if wondering what " + he
              + " was thinking to go against such an opponent!";
            break;
        case "determined":
        default:
            gtxt = tcname + " sighs and nods in acknowledgement at"
              + " being clearly outmatched.";
            break;
        }
        break;
    case "victory_behavior":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " stands and laughs loudly, pumping " + his
              + " fists in victory before leaving the crate.";
            break;
        case "aloof":
            gtxt = tcname + " stands, nods at " + his_opnt + " and"
              + " departs victoriously.";
            break;
        case "goofy":
            gtxt = tcname + " leaps onto the crate, gives " + his_opnt
              + " a quick double-thumbs-up, and then bounds away,"
              + " grinning in victory.";
            break;
        case "determined":
        default:
            gtxt = tcname + " rises and smiles victoriously. With a"
              + " nod at " + his_opnt + ", " + he + " turns and leaves"
              + " the crate.";
            break;
        }
        break;
    case "defeat_behavior":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " walks away from the crate, growling.";
            break;
        case "aloof":
            gtxt = tcname + " leaves the crate without a word.";
            break;
        case "goofy":
            gtxt = tcname + " stomps huffily away from the crate.";
            break;
        case "determined":
        default:
            gtxt = tcname + " sighs and walks away from the crate.";
            break;
        }
        break;
    case "forfeit":
        switch(demeanor)
        {
        case "aggressive":
            gtxt = tcname + " snarls in disgust, and then laughs in"
              + " mocking tones at " + his + " departed opponent. "
              + capitalize(he) + " rises and stomps away from the"
              + " crate, wiping both names from the board.";
            break;
        case "aloof":
            gtxt = tcname + " appears mildly annoyed at the abrupt"
              + " departure of " + his + " opponent, and then quietly"
              + " leaves the crate without a word to wipe both names"
              + " from the board.";
            break;
        case "goofy":
            gtxt = tcname + " looks baffled for a moment, and then cries"
              + " out in protest at the sudden departure of " + his
              + " opponent. With a frustrated grumble, " + he + " rises"
              + " and trumps away from the crate, wiping both names"
              + " from the board.";
            break;
        case "determined":
        default:
            gtxt = tcname + " frowns for moment, and then smirks at"
              + " the sudden departure of his opponent. Shrugging,"
              + " he rises and leaves the crate to wipe both names"
              + " off of the board.";
            break;
        }
        break;
    default:
        gtxt = "Something seems wrong. Maybe you'd better let Gorboth"
          + " know that all is not well in the world of Arm Wrestling"
          + " challenges today!";
        break;
    }

    return gtxt + "\n\n";
} /* gld_txt */


/*
 * Function name:        d20
 * Description  :        Get a 20-sided dice roll
 * Returns      :        the roll
 */
public int
d20()
{
    int     roll = random(20) + 1;
    return (roll);
} /* d20 */


/*
 * Function name:        arm_wrestle
 * Description  :        The arm wrestling match itself
 * Arguments    :        int first_move - true if this is the beginning
 *                                        of the match (default false)
 */
public void
arm_wrestle(int first_move = 0)
{
    object  opponent = Arm_Wrestlers[Whose_Turn];
    object  wrestler;
    string  win_probability;
    int     wrestler_power;
    int     opponent_power;
    int     roll = d20();
    int     wpos;
    int     pos_change = 0;
    string  wresult;

    Whose_Turn = !Whose_Turn;  /* Flip turns each time */

    wrestler = Arm_Wrestlers[Whose_Turn];
    win_probability = Win_Odds[wrestler->query_real_name()];

    /* Ability in this match is a combination of str + dis */
    wrestler_power = wrestler->query_stat(0) + wrestler->query_stat(5);
    opponent_power = opponent->query_stat(0) + opponent->query_stat(5);

    if (first_move)
    {
        switch(roll)
        {
            case 0..18:
                wresult = "launch";
                break;
            default:
                wresult = "sudden_victory";
                pos_change = 2;
                break;
        }

        if (pos_change != 2)
        {
            pos_change = ( (win_probability == "dominating") ? 4 : 0);
        }

        wrestler->add_prop(ARM_WRESTLING_POS, POS_STARTING);
        opponent->add_prop(ARM_WRESTLING_POS, POS_STARTING);

        wrestle_result(pos_change, wrestler, opponent,
                          (win_probability + "_" + wresult));
        return;
    }

    wpos = wrestler->query_prop(ARM_WRESTLING_POS);

    switch(wpos)
    {
        case POS_STARTING..POS_WINNING:
            switch(win_probability)
            {
                case "hopeless":
                    switch(roll)
                    {
                        case 15..18:
                            wresult = "advance";
                            pos_change = 1;
                            break;
                        case 0..14:
                            wresult = "stalemate";
                            pos_change = 0;
                            break;
                        default:
                            wresult = "sudden_victory";
                            pos_change = 2;
                            break;
                    } /* switch(roll) */
                    break;
                case "equal":
                    switch(roll)
                    {
                        case 8..15:
                            wresult = "advance";
                            pos_change = 1;
                            break;
                        case 0..7:
                            wresult = "stalemate";
                            pos_change = 0;
                            break;
                        default:
                            wresult = "sudden_victory";
                            pos_change = 2;
                            break;
                    } /* switch(roll) */
                    break;
                case "dominating":
                    switch(roll)
                    {
                        case 3..14:
                            wresult = "advance";
                            pos_change = 1;
                            break;
                        case 0..2:
                            wresult = "stalemate";
                            pos_change = 0;
                            break;
                        default:
                            wresult = "sudden_victory";
                            pos_change = 2;
                            break;
                    } /* switch(roll) */
                    break;
            } /* switch(win_probability) */
            break;
        case POS_ABOUT_TO_WIN:
            switch(win_probability)
            {
                case "hopeless":
                    switch(roll)
                    {
                        case 0..16:
                            wresult = "stalemate";
                            pos_change = 0;
                            break;
                        default:
                            wresult = "slow_victory";
                            pos_change = 2;
                            break;
                    } /* switch(roll) */
                    break;
                case "equal":
                    switch(roll)
                    {
                        case 0..8:
                            wresult = "stalemate";
                            pos_change = 0;
                            break;
                        default:
                            wresult = "slow_victory";
                            pos_change = 2;
                            break;
                    } /* switch(roll) */
                    break;
                case "dominating":
                    switch(roll)
                    {
                        case 0..3:
                            wresult = "stalemate";
                            pos_change = 0;
                            break;
                        default:
                            wresult = "slow_victory";
                            pos_change = 2;
                            break;
                    } /* switch(roll) */
                    break;
            } /* switch(win_probability) */
            break;
        case POS_LOSING:
        case POS_ABOUT_TO_LOSE:
            switch(win_probability)
            {
                case "hopeless":
                    switch(roll)
                    {
                        case 16..19:
                            wresult = "recovery";
                            pos_change = 3;
                            break;
                        case 0..15:
                            wresult = "nonrecovery";
                            pos_change = 0;
                            break;
                        default:
                            wresult = "sudden_victory";
                            pos_change = 2;
                            break;
                    } /* switch(roll) */
                    break;
                case "equal":
                    switch(roll)
                    {
                        case 14..17:
                            wresult = "recovery";
                            pos_change = 3;
                            break;
                        case 0..13:
                            wresult = "nonrecovery";
                            pos_change = 0;
                            break;
                        default:
                            wresult = "sudden_victory";
                            pos_change = 2;
                            break;
                    } /* switch(roll) */
                    break;
                case "dominating":
                    switch(roll)
                    {
                        case 4..14:
                            wresult = "recovery";
                            pos_change = 3;
                            break;
                        case 0..3:
                            wresult = "nonrecovery";
                            pos_change = 0;
                            break;
                        default:
                            wresult = "sudden_victory";
                            pos_change = 2;
                            break;
                    } /* switch(roll) */
                    break;
            } /* switch(win_probability) */
            break;
        default:
            wresult = "error";
            break;
    } /* switch(wpos) */

    wrestle_result(pos_change, wrestler, opponent,
                      (win_probability + "_" + wresult));
    return;
} /* arm_wrestle */


/*
 * Function name:        wrestle_result
 * Description  :        process the result of a round of arm-wrestling
 * Arguments    :        int - pos_change: the wrestlers position moves:
 *                                          0 - no change
 *                                          1 - one closer to winning
 *                                          2 - wins!
 *                                          3 - recovers to start position
 *                                          4 - strong launch to near win
 *
 *                       object wrestler: the player whose round it was
 *                       object oppoent:  the players opponent
 *                       string wresult:  what happened
 */
public void
wrestle_result(int pos_change, object wrestler, object opponent, string wresult)
{
    string  he = opponent->query_pronoun();
    string  him = opponent->query_objective();
    string  his = opponent->query_possessive();
    string  tcname = capitalize(opponent->query_real_name());
    string  tname = tcname;
    string  wtxt;
    int     wpos = wrestler->query_prop(ARM_WRESTLING_POS);
    int     opos = opponent->query_prop(ARM_WRESTLING_POS);
    string  prob = explode(wresult, "_")[0];
    string  problem_txt = one_of_list(
              ({ "This is going extremely badly! ",
                 "No! You cannot let this happen! ",
                 "Oh dear ... this isn't good ... ",
                 "Arrgh! You've got to do something! ",
                 "",
              }) );
    string  troubled_musings = one_of_list(
              ({ "How are you going to get out of this?",
                 "You'd better figure this out!",
                 "You begin to fear the worst.",
                 "A sinking feeling washes over you.",
                 "",
              }) );

    Rounds++;
    add_wrestling_fatigue(wrestler, prob);

    /* First, let's see if there was a winner this round ... */
    if (pos_change == 2)
    {
        tell_room(this_object(), gld_txt(wrestler, wresult),
            ({ wrestler, opponent }) );
        opponent->catch_tell(gld_txt(wrestler, wresult, 1));

        switch(wresult)
        {
            case "hopeless_sudden_victory":
                wtxt = "To the astonishment of everyone present, you"
                  + " summon up all your strength from deep down and"
                  + " manage to drive " + tname + "'s fist"
                  + " to the crate for an immediate win!";
                break;
            case "equal_sudden_victory":
                wtxt = "Out of nowhere you feel a sudden burst of"
                  + " strength which catches " + tname + " by surprise,"
                  + " allowing you to press " + his + " fist to the crate"
                  + " for an immediate win!";
                break;
            case "dominating_sudden_victory":
                wtxt = "Feeling pretty relaxed verses this much weaker"
                  + " opponent, you decide to skip to the end and easily"
                  + " force " + his + " fist down to the crate for an"
                  + " immediate win.";
                break;
            case "hopeless_slow_victory":
                wtxt = "Somehow, amazingly, you find the strength to"
                  + " continue this unlikely feat, and slowly grind"
                  + " your unwitting (and much stronger) opponent's"
                  + " fist down to the crate for the win!";
                break;
            case "equal_slow_victory":
                wtxt = "Pride is on the line, and you don't feel like"
                  + " losing. Summoning your reserve strength, you"
                  + " grind down on " + tname + "'s fist, forcing"
                  + " it to the crate for the win!";
                break;
            case "dominating_slow_victory":
                wtxt = "This has been amusing, and perhaps a bit more"
                  + " interesting than you thought it would be, but it"
                  + " can really only end one way. You press " + tname
                  + "'s fist easily down to the crate for"
                  + " the win.";
                break;
            default:
                wtxt = "There seems to have been an error. Please"
                  + " mail a wizard.";
                break;
        }

        wrestler->catch_tell(wtxt + "\n");

        wrestler->remove_prop(ARM_WRESTLING_POS);
        opponent->remove_prop(ARM_WRESTLING_POS);

        set_alarm(Reaction_Delay, 0.0,
            &opponent_reaction(wrestler, opponent, wresult));
        set_alarm((Reaction_Delay + 0.1), 0.0,
            &end_match(wrestler, opponent, prob));

        return;
    }

    switch(wresult)
    {
        case "hopeless_advance":
            wtxt = "Throwing everything you've got into this, you seem"
              + " to tap into something special, deep down, and feel,"
              + " to your surprise, " + tname + "'s fist move down"
              + " toward the crate!";
            break;
        case "equal_advance":
            wtxt = "Sensing considerable strength in " + tname + "'s grip,"
              + " you give all you have, bearing forward to slowly and"
              + " surely inch " + his + " fist down toward the crate.";
            break;
        case "dominating_advance":
            wtxt = "This is fun, and so you decide to draw it out a bit,"
              + " slowly (and easily) forcing " + tname + "'s fist down"
              + " toward the crate, taking your time.";
            break;
        case "hopeless_stalemate":
            wtxt = "Straining mightily, you drag on " + tname + "'s"
              + " frighteningly strong grip, and get nowhere! "
              + problem_txt;
            break;
        case "equal_stalemate":
            wtxt = "You pour your energy into an effort to make some"
              + " headway against " + tname + "'s strong grip. It doesn't"
              + " work, and all you can do is hold " + him + " in place!";
            break;
        case "dominating_stalemate":
            wtxt = "Well, this has been fun, but you might as well get"
              + " it over with. Anticipating an easy win, you suddenly"
              + " realize your powerful arm is doing nothing to move "
              + tname + "'s fist in the slightest. This cannot be"
              + " happening!";
            break;
        case "hopeless_recovery":
            wtxt = "Sensing what seems like certain loss, adrenaline"
              + " pounds through your veins, rising as a primal surge"
              + " of power! To everyone's surprise, you grind your"
              + " fist back up to the starting position and hold it"
              + " steady.";
            break;
        case "equal_recovery":
            wtxt = problem_txt + "Mustering all your"
              + " strength, you rock forward to slowly push " + tname
              + "'s fist back into the starting position, and pause" 
              + " to recover your wits.";
            break;
        case "dominating_recovery":
            wtxt = "This is ridiculous, and you are about to prove it."
              + " With ease you return " + tname + "'s fist back to the"
              + " starting position and peer into " + his + " eyes.";
            break;
        case "hopeless_nonrecovery":
            wtxt = problem_txt + "Your mind nearly"
              + " bursts with effort as you do anything and everything"
              + " to try to recover, but you cannot budge " + tname
              + "'s massively powerful fist in the slightest.";
            break;
        case "equal_nonrecovery":
            wtxt = problem_txt + "You throw what you've got against the"
              + " painful position " + tname + " has you in, but nothing"
              + " seems to work. " + troubled_musings;
            break;
        case "dominating_nonrecovery":
            wtxt = "Alright, playtime is over. You curl your lip as"
              + " you sit upright to fix this absurd situation, but ..."
              + " what is this?? You cannot! " + tcname + " is somehow,"
              + " impossibly, holding you pinned in place!";
            break;
        case "hopeless_launch":
            wtxt = "You've probably only got one shot at this ... surprise."
              + " UUNNNNGGG!! You throw your whole body into what you"
              + " hope can start you off with a quick win and ... might"
              + " as well be holding hands with a wrought-iron fencepost."
              + " You stare up into " + tname + "'s amused eyes.";
            break;
        case "equal_launch":
            wtxt = "HRRRP! You launch into a forward assault with all"
              + " your strength, and are brought up short by equal and"
              + " firm resistance. It seems that " + tname + " is going"
              + " to give you a proper match.";
            break;
        case "dominating_launch":
            wtxt = "You hardly imagine there will be much sport in it,"
              + " but you begin the match as expected, moving "
              + tname + "'s fist easily down toward the crate. You"
              + " stop just short of winning, so as to see if there"
              + " can be any story to tell here.";
            break;
        default:
            wtxt = "There appears to have been an error. Please alert"
              + " a wizard.";
            break;
    }

    switch(pos_change)
    {
        case 0:
        case 2:
            break;
        case 1:
            wpos++;
            opos--;
            break;
        case 4:
            wpos = 2;
            opos = -2;
            break;
        default:
            wpos = POS_STARTING;
            opos = POS_STARTING;
            break;
    }

    wrestler->add_prop(ARM_WRESTLING_POS, wpos);
    opponent->add_prop(ARM_WRESTLING_POS, opos);

    wrestler->catch_tell(wtxt + "\n");

    tell_room(this_object(), gld_txt(wrestler, wresult),
        ({ wrestler, opponent }) );
    opponent->catch_tell(gld_txt(wrestler, wresult, 1));

    set_alarm(Reaction_Delay, 0.0,
        &opponent_reaction(wrestler, opponent, wresult));

    W_Alarm = set_alarm(Round_Delay, 0.0, arm_wrestle);
    return;
} /* wrestle_result */


/*
 * Function name:        opponent_reaction
 * Description  :        Provide a reaction from the opponent to a
 *                       wrestlers action.
 * Arguments    :        object wrestler - the wrestler taking the action
 *                       object opponent - the opponent who reacts
 *                       string wresult - the action
 */
public void
opponent_reaction(object wrestler, object opponent, string wresult)
{
    if (sizeof(Arm_Wrestlers) < 2)
    {
        return;
    }

    tell_room(this_object(),
              gld_txt(opponent, wresult + "_reaction"),
              ({ opponent, wrestler }) );
    wrestler->catch_tell("\n"
      + gld_txt(opponent, wresult + "_reaction", wrestler));
    return;
} /* opponent_reaction */


/*
 * Function name:        forfeit_match
 * Description  :        if a player leaves in the middle of a match for
 *                       any reason, the match is called off.
 * Arguments    :        object who - the player who forfeit
 */
public void
forfeit_match(object who)
{
    who->remove_prop(ARM_WRESTLING_POS);
    who->remove_prop(ARM_WRESTLING_CHALLENGE);
    who->remove_prop(ACCEPT_CHALLENGE);

    Arm_Wrestlers -= ({ who });

    if (sizeof(Arm_Wrestlers))
    {
        if (Opt_Out_Possible)
        {
            who->catch_tell("\nYou decide to opt out, and return to where"
              + " you were in the lounge.\n\n");
            Arm_Wrestlers[0]->catch_tell("\n"
              + who->query_The_name(Arm_Wrestlers[0])
              + " stands up and leaves the crate, opting out of the"
              + " match.\n");
            tell_room(this_object(), QCTNAME(who) + " seems to opt"
              + " out of the challenge, and leaves the table. \n\n",
                ({ who, Arm_Wrestlers[0] }) );
            react_forfeit(Arm_Wrestlers[0]);

            remove_alarm(W_Alarm);   /* XXXXX Is this correct? */

            return;
        }

        who->catch_tell("\nYou stand up, breaking grips with your"
          + " opponent, and forfeit the match!\n\n");

        tell_room(this_object(), capitalize(who->query_real_name())
          + " abruptly breaks off " + who->query_possessive()
          + " grip, stands up and walks away from the crate,"
          + " forfeiting the match!\n", who);

        Persona_Non_Grata += ({ who->query_real_name() });

        set_alarm(0.1, 0.0, &react_forfeit(Arm_Wrestlers[0]));

        remove_alarm(W_Alarm);

        set_alarm(2.0, 0.0, begin_challenge);
        return;
    }

    who->catch_tell("You rise and walk away from the arm-wrestling crate.\n");
    tell_room(this_object(), QCTNAME(who) + " rises and walks away from the"
      + " arm-wrestling crate.\n", who);

    remove_alarm(W_Alarm);

    return;
} /* forfeit_match */


/*
 * Function name:        react_forfeit
 * Description  :        Have the remaining player react to the person who
 *                       forfeit the match against them.
 * Arguments    :        object who - the player reacting
 */
public void
react_forfeit(object who)
{
    tell_room(this_object(), gld_txt(Arm_Wrestlers[0], "forfeit"), who);
    
    who->remove_prop(ARM_WRESTLING_POS);
    who->remove_prop(ARM_WRESTLING_CHALLENGE);
    who->remove_prop(ACCEPT_CHALLENGE);

    Arm_Wrestlers -= ({ who });

    who->catch_tell("\nDisplaying your feelings a bit at your lamely departed"
      + " opponent, you stand up and wipe both names from the board before"
      + " walking back to what you were doing"
      + " before. Maybe someone else would accept a <challenge> from"
      + " you?\n\n");

    return;
} /* react_forfeit */


/*
 * Function name:        end_match
 * Description  :        There has been a winner, so we end the match
 *                       and tally the scores, give rewards, etc.
 * Arguments    :        object winner - the player who won
 *                       object lower  - the player who lost
 *                       string probability - the odds the winner would win
 */
public void
end_match(object winner, object loser, string probability)
{
    int     timestamp = time();
    object *both_wrestlers = ({ winner, loser });
    string  victor_prob;
    string  payout_prob;

    both_wrestlers->add_prop(RESTING_FROM_MATCH, timestamp);
    both_wrestlers->remove_prop(ARM_WRESTLING_CHALLENGE);
    both_wrestlers->remove_prop(ACCEPT_CHALLENGE);
    both_wrestlers->remove_prop(ARM_WRESTLING_POS);

    winner->catch_tell("YOU WON THE MATCH!!\n\n"
      + "You acknowledge your win in your own way and return to the"
      + " other parts of the lounge. ");
    loser->catch_tell("YOU LOST THE MATCH.\n\n");

    tell_room(this_object(), gld_txt(winner, "victory_behavior"),
        ({ winner, loser }) );
    loser->catch_tell(gld_txt(winner, "victory_behavior", 1)
      + "Somewhat dejectedly, you rise and return to the lounge proper"
      + " as well.\n\n");
    tell_room(this_object(), gld_txt(loser, "defeat_behavior"),
        loser);

    /* We need to reverse the stuff here to get correct info to the
     * blackboard results via add_victor.
     */
    switch(probability)
    {
        case "hopeless":
            victor_prob = "dominating";
            payout_prob = "underdog";
            break;
        case "dominating":
            victor_prob = "hopeless";
            payout_prob = "favorite";
            break;
        default:
            victor_prob = probability;
            payout_prob = "even";
            break;
    }

    WRESTLING_MASTER->add_victor(winner->query_real_name(), victor_prob,
                                 loser->query_real_name(), Rounds);

    set_alarm(2.0, 0.0, &payout_bets(winner->query_real_name(),
                                     payout_prob, Rounds));

    Arm_Wrestlers = ({ });
    Rounds = 0;

    return;
} /* end_match */


/*
 * Function name:        exa_blackboard
 * Description  :        allow players to check the arm wrestling
 *                       scores
 * Returns      :        string - the blackboard readout
 */
public string
exa_blackboard()
{
/*
    if (!sizeof(m_indices(WRESTLING_MASTER->query_victors())))
    {
        return "The blackboard is blank, currently.\n";
    }
*/
    WRESTLING_MASTER->print_victors(this_player(), Arm_Wrestlers);
    return "";
} /* exa_blackboard */


/*
 * Function name:        do_attitude
 * Description  :        Allow players to set their preferred attitude
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_attitude(string arg)
{
    string *attitudes = ({ "aloof", "goofy", "aggressive", "determined" });
    int     choice = member_array(arg, attitudes);

    if (!strlen(arg))
    {
        notify_fail("You may choose: aloof, goofy, aggressive, or determined"
          + " for your personality during arm wrestling. If you do not select"
          + " one, it will be selected for you based on your guild first, and"
          + " your race second.\n");
        return 0;
    }

    if (choice == -1)
    {
        notify_fail("'" + capitalize(arg) + "' is not an attitude you can"
          + " choose. You can select: aloof, goofy, aggressive, or"
          + " determined for your personality during wrestling.\n");
        return 0;
    }

    write("You decide you're in " + LANG_ADDART(attitudes[choice])
      + " mood, and will act accordingly in any arm-wrestling matches you"
      + " wish to enact with a <challenge>.\n");
    this_player()->add_prop(WRESTLING_ATTITUDE, attitudes[choice]);

    return 1;
} /* do_attitude */


/*
 * Function name:        exa_crate
 * Description  :        Allow players to examine the arm-wrestling
 *                       crate.
 * Returns      :        string - the description
 */
public string
exa_crate()
{
    string  at_crate = COMPOSITE_LIVE(Arm_Wrestlers);

    if (IN_ARRAY(this_player(), Arm_Wrestlers))
    {
        return "You've taken a seat at the crate.\n";
    }

    return "The shipping crate is abount waist-high, and has been set"
      + " diagonally, two low barrels at its opposite points where"
      + " opponents can sit and <challenge> one another at arm-"
      + "wrestling. Maybe you are in the mood yourself? If so, you"
      + " might want to first decide on an <attitude> that reflects"
      + " your personality for the contest.\n\n"
      + "Currently, " + at_crate + " "
      + ((sizeof(Arm_Wrestlers) > 1) ? "are" : "is")
      + " sitting at the crate.\n";
} /* exa_crate */


/*
 * Function name:        confirm_matchup
 * Description  :        We want to have our moderator confirm the
 *                       matchup before making it official and starting
 *                       the betting.
 */
public void
confirm_matchup()
{
    string  confirm_txt = "Skoot hobbles over, eyes up the"
                        + " both of you, and nods.\n\n";
    string  extra_txt;
    string  odds;
    int     either_is_rookie = 2;
    int     confirm_delay;

    summon_skoot();

    foreach (object who : Arm_Wrestlers)
    {
        if (who->query_prop(ARM_WRESTLED_THIS_LOGIN))
        {
            either_is_rookie--;
        }
    }

    if (either_is_rookie)
    {
        confirm_delay = 20;
        extra_txt = "Skoot says: Now, afore I announce the match,"
          + " ye needs ta know I'll be tellin' folks who ye be. There ain't"
          + " no nameless arm-wrestlin' here! Don't worry, no names will"
          + " stick in these lubber's memories. They're too drunk fer that!"
          + " But, if ye're the type who can't stand ta"
          + " be known, ye'd best <forfeit> now. Don't worry, it won't"
          + " mess up yer scores.\n\n";
    }
    else
    {
        confirm_delay = 10;
        extra_txt = "Skoot says: Alright, ye both know the drill here."
          + " No need to explain it all again. Unless ye feel like"
          + " ye need ta <forfeit>, I be startin' the match a bit"
          + " sooner than if either o ye been a rookie.\n\n";
    }

    foreach (object who : Arm_Wrestlers)
    {
        who->catch_tell(confirm_txt);

        odds = Win_Odds[who->query_real_name()];

        switch(odds)
        {
            case "equal":
                who->catch_tell("Skoot says: "
                  + "Alright, I see we ain't got any favorite"
                  + " or underdog here ... ye be decently matched. Should"
                  + " be interestin'.\n\n");
                break;
            default:
                who->catch_tell("Putting his hand on your shoulder,"
                  + " Skoot says: Ye be the clear "
                  + ((odds == "dominating") ? "favorite" : "underdog")
                  + " here. That'll help with the betting, o'course.\n\n");
                break;
        }

        who->catch_tell(extra_txt);

        who->catch_tell("Skoot says: I'll give ye " + confirm_delay
          + " seconds, then I'll announce the match.\n");
    }

    tell_room(this_object(), "Skoot hobbles over to the"
      + " shipping crate and quietly confers with the two challengers.\n",
        Arm_Wrestlers);

    Opt_Out_Possible = 1;

    W_Alarm = set_alarm(itof(confirm_delay), 0.0, open_betting);
} /* confirm_matchup */


/*
 * Function name:        open_betting
 * Description  :        Our moderator announces the match and opens the
 *                       betting.
 */
public void
open_betting()
{
    int     versus_said = 0;
    string  odds;
    int     equal_matchup = 0;
    string  odds_txt = "";
    string  get_attention = one_of_list(
                            ({ "Hear ye! Hear ye! ",
                               "Mugs down and listen up, lads! ",
                               "Yer attention, lads and lassies! ",
                               "Avast, good folk! Yer attention! ",
                               "Everyone, listen up! ",
                            }) );
    string  talkup_match  = one_of_list(
                            ({ "We have here two challengers who want"
                             + " nothing better than ta prove who be"
                             + " worth their salt! An arm-wrestling"
                             + " match fer the ages!",
                               "Another fierce competition be upon"
                             + " us! Two sit before ye to battle it"
                             + " out in arm-wrestling fer all the"
                             + " bragging rights o' victory!",
                               "We've got here the pleasure o' another"
                             + " match o' the noblest sport - arm-"
                             + "wrestling! Glory and boasting ta the"
                             + " victor, as always!",
                            }) );

    summon_skoot();

    tell_room(this_object(), "\nSkoot walks to the middle"
      + " of the room and bellows: " + upper_case(get_attention)
      + talkup_match + "\n\n");

    tell_room(this_object(), "Skoot continues: HERE BE"
      + " YER CHALLENGERS! ");

    foreach (object who : Arm_Wrestlers)
    {
        odds = Win_Odds[who->query_real_name()];

        switch(odds)
        {
            case "equal":
                equal_matchup++;
                break;
            default:
                odds_txt = ((odds == "dominating")
                       ? " (favored to win)" : " (a clear underdog)");
                break;
        }

        if (equal_matchup == 1)
        {
            tell_room(this_object(), "Evenly matched, we have ");
        }

        tell_room(this_object(), capitalize(who->query_real_name())
          + odds_txt + ((!versus_said) ? " versus " : "! "));

        versus_said++;
    }

    tell_room(this_object(), "Ye have 30 seconds to <bet> yer coins!\n");
    Betting_Open = 1;
    Opt_Out_Possible = 0;

    W_Alarm = set_alarm(30.0, 0.0, close_betting);
    return;
} /* open_betting */


/*
 * Function name:        close_betting
 * Description  :        Our moderator signals that the match is about
 *                       to begin and betting is about to close.
 */
public void
close_betting()
{
    summon_skoot();

    tell_room(this_object(), "\nSkoot announces: Bets are"
      + " closing, lads! The match begins in 5 ... 4 ... 3 ... 2 ...\n");

    W_Alarm = set_alarm(5.0, 0.0, begin_challenge);
    return;
} /* close_betting */


/*
 * Function name:        do_forfeit
 * Description  :        Allow players to manually forfeit the match
 *                       if they do not wish to continue it.
 * Arguments    :        string arg - what was typed
 * Returns      :        int 1 - if we are a legitimate forfeit candidate
 *                       int 0 - otherwise (failure)
 */
public int
do_forfeit(string arg)
{
    if (!IN_ARRAY(this_player(), Arm_Wrestlers))
    {
        return 0;
    }

    forfeit_match(this_player());

    write_file(LOG_DIR + "arm_wrestle_forfeit", 
        TIME2FORMAT(time(), "mm/dd/yyyy")
      + " (" + ctime(time())[11..18] + ") "
      + capitalize(this_player()->query_real_name())
      + " forfeits an arm-wrestling match!\n");

    return 1;
} /* do_forfeit */


/*
 * Function name:        catch_all
 * Description  :        When arm_wrestling, we want to block most commands
 *                       so players don't money around with the situation.
 * Arguments    :        string str
 * Returns      :        1 - to block the command, 0 - to let it through
 */
public int 
catch_all(string str)
{
    if (this_player()->query_wiz_level() ||
        !IN_ARRAY(this_player(), Arm_Wrestlers))
    {
        return 0;
    }

    switch (query_verb())
    {
        case "look":
        case "l":
        case "exa":
        case "forfeit":
        case "say":
        case "shout":
            return 0;
        case "challenge":
            write("You've already done that!\n");
            return 1;
            break;
        default:
            write("You can't do that now! If you really need to do"
              + " something else, you can <forfeit> the arm-wrestling"
              + " match.\n");
            return 1;
            break;
    }
} /* catch_all */


/*
 * Function name:        do_bet
 * Description  :        Allow the player to bet on the wrestling match
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_bet(string arg)
{
    string  instructions = "You may bet 5, 10, or 20 of either gold or"
          + " platinum.\nSimply <bet [amount] [cointype] on"
          + " [challenger]>\n";
    string  coin_type;
    int     bet_amount;
    mixed   challenger;
    string  c_name;
    string  challenger_odds;

    summon_skoot();

    if (sizeof(query_challengers()) < 2)
    {
        notify_fail("There is nothing to bet on right now. You'll need"
          + " to wait until there are two arm-wrestling challengers.\n");
        return 0;
    }

    if (!Betting_Open)
    {
        notify_fail(((sizeof(query_challengers()) < 2) 
          ? "You missed your chance. You cannot bet once"
              + " the match begins! Maybe next time.\n"
          : "Betting is not currently open. You'll need to wait"
          + " until Skoot announces the next"
          + " challenge.\n"));

        return 0;
    }

    if (IN_ARRAY(this_player(), Arm_Wrestlers))
    {
        notify_fail("You cannot bet on your own match!\n");
        return 0;
    }

    if (IN_ARRAY(this_player()->query_real_name(), m_indices(W_Bets)))
    {
        notify_fail("You have already placed your bet. Be patient now"
          + " and wait till everything is settled.\n");
        return 0;
    }

    if (!strlen(arg))
    {
        notify_fail(instructions);
        return 0;
    }

    if (!parse_command(arg, environment(this_player()),
        "%d %w [coin] [coins] 'on' %s", bet_amount, coin_type, 
         challenger))
    {
        notify_fail(instructions);
        return 0;
    }

    challenger = find_living(challenger);

    if (!objectp(challenger))
    {
        notify_fail("There is no such thing to bet on!\n");
        return 0;
    }

    if (!present(challenger, this_object()))
    {
        notify_fail("There is no such person here.\n");
        return 0;
    }

    c_name = challenger->query_real_name();

    if (!bet_amount || (bet_amount > 21) || (bet_amount % 5))
    {
        notify_fail("You can bet 5, 10, or 20 gold or platinum. Other"
          + " amounts are not accepted.\n");
        return 0;
    }

    if (!IN_ARRAY(coin_type, ({ "gold", "platinum" }) ))
    {
        notify_fail(capitalize(coin_type) + " is not an acceptable"
          + " currency here. You can bet either gold or platinum.\n");
        return 0;
    }

    if (!interactive(challenger))
    {
        notify_fail("Bet on " + ((challenger->num_heap()) ?
            "" : "the ") + challenger->short() + "? What nonsense is"
          + " this?\n");
        return 0;
    }

    if (challenger == this_player())
    {
        notify_fail("You daydream briefly about betting on yourself,"
          + " and then realize that perhaps you should pick an actual"
          + " challenger.\n");
        return 0;
    }

    if (!IN_ARRAY(challenger, Arm_Wrestlers))
    {
        notify_fail(capitalize(c_name) + " is not one of the"
          + " arm-wrestling challengers!\n");
        return 0;
    }

    if (!complete_payment(this_player(), coin_type, bet_amount, "bet",
                          c_name))
    {
        /* not a true success, but we catch it here to prevent a
         * lousy-looking "What?" fail message, having already written
         * output to the player from complete_payment.
         */
        return 1;
    }

    W_Bets[this_player()->query_real_name()] = ({ c_name,
                                                  bet_amount,
                                                  coin_type });

    switch (Win_Odds[c_name])
    {
        case "equal":
            challenger_odds = "equally matched";
            break;
        case "dominating":
            challenger_odds = "as favorite";
            break;
        default:
            challenger_odds = "as underdog";
            break;
    }

    write_file(LOG_DIR + "arm_wrestle_bet", 
        TIME2FORMAT(time(), "mm/dd/yyyy")
      + " (" + ctime(time())[11..18] + ") "
      + capitalize(this_player()->query_real_name())
      + " bet " + bet_amount + " " + coin_type + " on "
      + capitalize(c_name) + " (" + challenger_odds + ").\n");

    return 1;

} /* do_bet */


/*
 * Function name:        do_offer
 * Description  :        allow players to pay Skoot to forgive them
 *                       for forfeiting a match after bets were
 *                       accepted.
 * Arguments    :        string arg - what the player typed 
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_offer(string arg)
{
    string  name = this_player()->query_real_name();
    int     banned = IN_ARRAY(name, Persona_Non_Grata);

    if (!banned)
    {
        return 0;
    }

    if (!strlen(arg) || !parse_command(arg, ({}),
        "[20] [twenty] 'platinum' [coin] [coins] 'to'"
      + " [the] [salty] [old] 'dwarf' / 'skoot' / 'Skoot'"))
    {
        notify_fail("You can <offer platinum to dwarf> if you wish to"
          + " try to buy back into his good graces.\n");
        return 0;
    }

    notify_fail(""); /* message handled in complete_payment() */
    return complete_payment(
               this_player(), "platinum", 20, "forgiveness");
} /* do_offer */


/*
 * Function name:        complete_payment
 * Description  :        See if the player has the right number of
 *                       platinum coins for the transaction. If not,
 *                       we let them know.
 * Arguments    :        object who - the player trying to pay
 *                       string coin_type - the type of coin
 *                       int    needed - the amount needed
 *                       string reason - the reason for payment
 *                       string bet - the name of the person we bet on
 *                                    (default = "none")
 * Returns      :        int 1 - successful payment made
 *                           0 - not able to pay
 */
public int
complete_payment(object who, string coin_type, int needed, string reason, string bet = "none")
{
    object  *inv_items = all_inventory(who);
    object  coin;
    object  temp_location;
    object  npc = this_object();
    string  msg_txt;
    mapping amount = ([ 5 : "a bit of", 10 : "some", 20 : "a bunch of" ]);
    object  guy_we_bet_on;

    summon_skoot();

    foreach (object inv_item: inv_items)
    {
        if (inv_item->query_coin_type() == coin_type &&
           (MASTER_OB(inv_item)) == "/std/coins")
        {
            coin = inv_item;
        }
    }

    if (!coin)
    {
        switch (reason)
        {
            case "bet":
                msg_txt = "Skoot growls: Ye be wantin' ta bet - good,"
                  + " good! But, ye will first need ta get the coins! Ye"
                  + " have not a single " + coin_type + " coin to bet"
                  + " with.";
                break;
            default:
                msg_txt = "Skoot scoffs: Ye wantin' ta"
                  + " buy back into me good graces be well and good."
                  + " But ye need be bringin' 20 platinum coins. I"
                  + " ain't carin' for lesser coin, and ye got not"
                  + " a single one to pay with!";
                break;
        }

        who->catch_tell(msg_txt + "\n");
        return 0;
    }

    if (coin->num_heap() < needed)
    {
        switch (reason)
        {
            case "bet":
                msg_txt = "Skoot growls: Ye be wantin' ta bet - good,"
                  + " good! But, ye haven't got enough coin! I see just "
                  + LANG_NUM2WORD(coin->num_heap()) + " " + coin_type
                  + " in yer hands - not enough for that bet!";
                break;
            default:
                msg_txt = "Skoot scoffs: Ye wantin' ta"
                  + " buy back into me good graces be well and good."
                  + " But ye need be bringin' 20 platinum coins. I"
                  + " ain't carin' for lesser coin, and I count just "
                  + LANG_NUM2WORD(coin->num_heap()) + " platinum that"
                  + " you be showin' me!";
                break;
        }

        who->catch_tell(msg_txt + "\n");
        return 0;
    }

    switch (reason)
    {
        case "bet":
            msg_txt = "hoping this bet will pay off.";
            break;
        default:
            msg_txt = "hoping he will forgive you for your earlier"
              + " forfeit.";
            break;
    }

    guy_we_bet_on = find_living(bet);

    who->catch_tell("You pay " + needed + " " + coin_type + " coins"
      + " to Skoot, " + msg_txt + "\n\n");

    switch (reason)
    {
        case "bet":
            msg_txt = "croaks: A bet fer " + capitalize(bet) + " then!"
              + " I'll mark ye down fer that, and"
              + " good luck to ye!";
            break;
        default:
            msg_txt = "grumbles: Ye be settled. Now don't be"
              + " forfeitin' after I take bets again.";
            break;
    }

    who->catch_tell("Skoot counts over the coins, pockets them, and "
      + msg_txt + "\n");

    temp_location = clone_object("/std/room");
    coin->split_heap(needed);
    coin->move(temp_location);
    /* Clean up afterward. */
    temp_location->remove_object();

    if (reason == "forgiveness")
    {
        write_file(LOG_DIR + "arm_wrestle_forgive", 
            TIME2FORMAT(time(), "mm/dd/yyyy")
          + " (" + ctime(time())[11..18] + ") "
          + capitalize(who->query_name())
          + " paid 20 platinum for forfeit forgiveness.\n");

        Persona_Non_Grata -= ({ who->query_real_name() });

        tell_room(environment(who), QCTNAME(who) + " pays "
          + amount[needed] + " " + coin_type + " to Skoot, who"
          + " counts it over and grumbles a private response.\n", who);
    }
    else
    {
        WRESTLING_MASTER->coin_tally("taken", needed, coin_type);

        tell_room(environment(who), QCTNAME(who) + " bets " + amount[needed]
          + " " + coin_type + " on " + capitalize(bet)
          + ".\n", ({ who, guy_we_bet_on }) );
        guy_we_bet_on->catch_tell(who->query_The_name(this_player())
          + " bets " + amount[needed] + " " + coin_type + " on you.\n");
    }

    return 1;
} /* complete_payment */


/*
 * Function name:        payout_bets
 * Description  :        pay the winnings to people who had their
 *                       challenger win the match, or return money
 *                       if the match was forfeit.
 * Arguments    :        string winner - the winner of the match
 *                       string odds   - the odds: even/favorite/underdog
 *                       int n_rounds  - the number of rounds in the match
 *                       int forfeit = 0 (default) true if the match
 *                                     was forfeit, in which we
 *                                     simply return the bet amount
 *                                     to each player.
 *
 * Note: I am not going to babysit players or worry about people who have
 *       problematic connections. If you leave the room for any reason
 *       when the payout occurs, you lose your bet winnings.
 *
 * Payouts are as follows: 
 *
 *     Bet Amount:     Favorite:         Even:     Underdog:
 *     =================================================================
 *              5             6            10            15             
 *             10            12            20            30
 *             20            24            40            60
 *     =================================================================
 *                          +20%         +100%         +200%
 *
 *    exec int i = 5; return ftoi((itof(i) * 0.2)) + i;
 */
public void
payout_bets(string victor, string odds, int n_rounds, int forfeit = 0)
{
    string *betters = m_indices(W_Bets);
    mixed  *bet_array;
    string  bet_choice;
    string  coin_type;
    int     bet_amount;
    string  msg_txt = "Round " + n_rounds + ", and "
                    + capitalize(victor) + " wins ";
    string *winners = ({ });
    int     no_winners;
    object  this_better;
    object  this_winner;
    mixed  *bet_data;
    object  prize;
    int     prize_amount;
    int     i;
    mapping payout = ([ "favorite" : 0.2,
                        "even"     : 1.0,
                        "underdog" : 2.0 ]);
    float   payout_mod = payout[odds];
    object  winner_location;
    int     not_here = 0;

    summon_skoot();

    if (!sizeof(betters))
    {
        if (forfeit)
        {
            tell_room(this_object(), "Skoot mutters:"
              + " Fer once in me life, I be glad no one bet on that"
              + " match! Damned unreliable ... rhmm ... mmmrm ... \n\n");

            return;
        }

        switch (odds)
        {
            case "even":
                msg_txt += "in an even matchup! A pity to see no"
                  + " bets! Ye'd have doubled yer money with a win!";
                break;
            case "favorite":
                msg_txt += "as the clear favorite! Nobody bet on"
                  + " 'em?? T'was easy money to be had!";
                break;
            case "underdog":
            default:
                msg_txt += "as a frickin' underdog! Har har! I suppose"
                  + " ye can't be blamed for not takin' up bettin'"
                  + " on 'em, ye cowards! Coulda been triple yer"
                  + " money!";
                break;
        }

        tell_room(this_object(), "Skoot cries: " + msg_txt + "\n\n");

        return;
    }

    if (forfeit)
    {
        tell_room(this_object(), "Skoot makes his"
          + " way around the room to return bet monies, grumbling"
          + " angrily.\n");

        foreach (string better : betters)
        {
            if (!objectp(this_better = present(better, this_object())))
            {
                tell_room(this_object(), "Skoot yells: Ha! "
                  + capitalize(better) + " ain't here?? I keep"
                  + " the bet!\n");

                write_file(LOG_DIR + "arm_wrestle_missing", 
                    TIME2FORMAT(time(), "mm/dd/yyyy")
                  + " (" + ctime(time())[11..18] + ") "
                  + capitalize(better)
                  + " lost out on forfeit repayment as absent?\n");
            }
            else
            {
                bet_data = W_Bets[better];

                this_better->catch_tell("Skoot returns"
                  + " your bet monies: " + bet_data[1] + " "
                  + bet_data[2] + ".\n");

                prize = MONEY_MAKE(bet_data[1], bet_data[2]);

                if (prize->move(this_better))
                {
                    this_better->catch_tell("Ooops! You are carrying"
                      + " too much and drop some of the coins!\n");
                    prize->move(this_object());
                }

                write_file(LOG_DIR + "arm_wrestle_forfeit", 
                    TIME2FORMAT(time(), "mm/dd/yyyy")
                  + " (" + ctime(time())[11..18] + ") "
                  + capitalize(better)
                  + " refunded " + bet_data[1] + " " + bet_data[2]
                  + ".\n");

                tell_room(this_object(), "Skoot pays some " + bet_data[2]
                  + " coins to " + QTNAME(this_better) + ".\n",
                    this_better);

                WRESTLING_MASTER->coin_tally("taken",
                                             -bet_data[1],
                                             bet_data[2]);

            }
        }

        W_Bets = ([]);
        return;
    }

    /* First, let's populate an array with the people who actually
     * won their bets. No need to process the losers.
     */
    foreach(string better : betters)
    {
        if (W_Bets[better][0] == victor)
        {
            winners += ({ better });
        }
    }

    no_winners = !sizeof(winners);

    if (no_winners)
    {
        switch (odds)
        {
        case "even":
            msg_txt += "in an even matchup! Winning bets would"
              + " have doubled, but ye all bet poorly!";
            break;
        case "favorite":
            msg_txt += "as the clear favorite! But looks like"
              + " we've a room 'o real gamblers here. All bets"
              + " were on the underdog, and lost!";
            break;
        case "underdog":
        default:
            msg_txt += "as a frickin' underdog! Har har! Ye all"
              + " bet with the favorite, and ye all lost!";
            break;
        }

        tell_room(this_object(), "Skoot cries: " + msg_txt + "\n\n");

        W_Bets = ([]);
        return;
    }

    switch (odds)
    {
        case "even":
            msg_txt += "in an even matchup! Winning bets double"
              + " thar money!";
            break;
        case "favorite":
            msg_txt += "as the clear favorite! Winning bets ain't"
              + " risk'd much, so only pay 20%!";
            break;
        case "underdog":
        default:
            msg_txt += "as a frickin' underdog! Har har! That'll"
              + " be triple money payouts fer those who risked"
              + " it on 'em!";
            break;
    }

    tell_room(this_object(), "Skoot cries: " + msg_txt + "\n\n");

    foreach (string winner : winners)
    {
        this_winner = find_player(winner);

        if (!objectp(this_winner))
        {
            tell_room(this_object(), "Skoot yells: Ha! "
              + capitalize(winner) + "'s gone and left the realms??"
              + " That one's winning' be mine then!\n");

            write_file(LOG_DIR + "arm_wrestle_missing", 
                TIME2FORMAT(time(), "mm/dd/yyyy")
              + " (" + ctime(time())[11..18] + ") "
              + capitalize(winner)
              + " lost out on payment as absent?\n");
        }
        else
        {
            winner_location = environment(this_winner);
            not_here = (winner_location != this_object());
            bet_data = W_Bets[winner];
            i = bet_data[1];
            prize_amount = ftoi((itof(i) * payout_mod)) + i;

            if (not_here)
            {
                this_winner->catch_tell("A mechanized gnomish"
                  + " parrot flies past and delivers your"
                  + " wrestling-bet winnings: " + prize_amount + " "
                  + bet_data[2] + "!\n");
                tell_room(winner_location, "A mechanized gnomish"
                  + " parrot flies past and delivers some "
                  + bet_data[2] + " coins to " + QTNAME(this_winner)
                  + ".\n", this_winner);
                tell_room(this_object(), "Skoot gives some "
                  + bet_data[2] + " coins to a mechanized gnomish"
                  + " parrot and sends it out a window to find "
                  + QTNAME(this_winner) + ".\n", this_winner);
            }
            else
            {
                this_winner->catch_tell("Skoot pays you"
                  + " your winnings: " + prize_amount + " "
                  + bet_data[2] + "!\n");
                tell_room(this_object(), "Skoot pays some "
                  + bet_data[2] + " coins to " + QTNAME(this_winner)
                  + ".\n", this_winner);
            }

            prize = MONEY_MAKE(prize_amount, bet_data[2]);

            if (prize->move(this_winner))
            {
                this_winner->catch_tell("Ooops! You are carrying"
                  + " too much and drop some of the coins!\n");
                prize->move(this_object());
            }

            write_file(LOG_DIR + "arm_wrestle_bet", 
                TIME2FORMAT(time(), "mm/dd/yyyy")
              + " (" + ctime(time())[11..18] + ") "
              + capitalize(winner)
              + " wins " + prize_amount + " " + bet_data[2] + ".\n");

            WRESTLING_MASTER->coin_tally("paid",
                                          prize_amount,
                                          bet_data[2]);
        }
    }

    tell_room(this_object(), "\nSkoot walks over and erases the two names"
      + " from the challenge board.\n");

    WRESTLING_MASTER->tally_betters(winners);
    W_Bets = ([]);

    return;
} /* payout_bets */


/*
 * Function name:        new_all_time_record
 * Description  :        we call this whenever a new all-time
 *                       record is set for arm-wrestling
 * Arguments    :        string record_type - the record we set
 *                       string who         - the player(s) who set it
 *                       int record_amount  - the new record amount
 */
public void
new_all_time_record(string record_type, string who, int record_amount)
{
    string  record_txt;

    summon_skoot();

    switch(record_type)
    {
        case "total":
            record_txt = "OHO!! Ye be settin' a new all-time record"
              + " fer total wins in one day with that one, " 
              + capitalize(who) + "! Ye'll be the talk o' the town!";
            break;
        case "u_dog":
            record_txt = "'TIS A MIRACLE!! Ye've just set the all-time"
              + " record for single-day wins as an underdog, "
              + capitalize(who) + "! We be not seein' that on just"
              + " any day o' the week!!";
            break;
        case "streak":
            record_txt = "AHOY LADS!! We've got a new record for"
              + " longest win-streak of all-time! Can "
              + capitalize(who) + " actually get another, fer "
              + record_amount + " wins in a row?? It be killin'"
              + " me ta know!!!";
            break;
        default:
            record_txt = "YE GODS!! T'were the longest match I can"
              + " ever remember in this tub! Ye've set the all-time"
              + " record on that one, mateys!!";
            break;
    }

    tell_room(this_object(), "\nSkoot hops up and down and shouts: "
      + record_txt + "\n\nHe crosses and marks down the new record on"
      + " the list beneath the challenge board.\n\n");

    write_file(LOG_DIR + "wrestle_all_time_records", 
        TIME2FORMAT(time(), "mm/dd/yyyy")
      + " (" + ctime(time())[11..18] + ") "
      + capitalize(who) + " sets a new " + record_type
      + " record of " + record_amount + "!\n");
} /* new_all_time_record */


/*
 * Function name:        exa_payouts
 * Description  :        print a chart of the payouts for the player
 * Returns      :        string - the chart
 */
public string
exa_payouts()
{
    string  txt;

    txt = 
    "       .----------------------------------------------------------------.\n"
  + "      |             COIN PAYOUTS - BASED ON WHO YOU BET ON               |\n"
  + "      |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n"
  + "      |                                                                  |\n"
  + "      |   Bet Amount:    On Favorite:    If Even:    On Underdog:        |\n"
  + "      |================================================================= |\n"
  + "      |         5             6            10            15              |\n"
  + "      |        10            12            20            30              |\n"
  + "      |        20            24            40            60              |\n"
  + "      |================================================================= |\n"
  + "       `----------------------------------------------------------------'\n";

    return txt;
} /* exa_payouts */


/*
 * Function name:        display_records
 * Description  :        Print out a fun display of the all-time
 *                       records for arm_wrestling.
 * Arguments    :        object who - the player to print to
 *
 * Nota Bene: I shall exceed my usual restriction of 80 character width
 *            for this function for the sake of text coherence.
 */
public void
display_records(object who)
{
    mapping  all_time_map = WRESTLING_MASTER->all_time_record_check();
    mixed   *at_total = all_time_map["total"];
    mixed   *at_u_dog = all_time_map["u_dog"];
    mixed   *at_rounds = all_time_map["rounds"];
    mixed   *at_streak = all_time_map["streak"];
    string   vs_txt;

    string   r_txt;
    string   border;
    string   midder;
    string   llower;
    string   total;
    string   udog;
    string   streak;
    string   longst;

    border = "   \\  :  /       \\  :  /       \\  :  /       \\  :  /       \\  :  /\n"
           + "`. __/ \\__ .' `. __/ \\__ .' `. __/ \\__ .' `. __/ \\__ .' `. __/ \\__ .'\n"
           + "_ _\\     /_ _ _ _\\     /_ _ _ _\\     /_ _ _ _\\     /_ _ _ _\\     /_ _\n"
           + "   /_   _\\       /_   _\\       /_   _\\       /_   _\\       /_   _\\\n"
           + " .'  \\ /  `.   .'  \\ /  `.   .'  \\ /  `.   .'  \\ /  `.   .'  \\ /  `.\n"
           + "   /  |  \\       /  :  \\       /  :  \\       /  :  \\       /  |  \\\n";

    midder = "      |                                                       |\n"
           + "   \\  |  /         ARM-WRESTLING ALL-TIME RECORDS:         \\  |  /\n"
           + "`. __/ \\__ .'                                           `. __/ \\__ .'\n"
           + "_ _\\     /_ _   ====================================    _ _\\     /_ _\n"
           + "   /_   _\\                                                 /_   _\\\n";

    llower = "   \\  |  /                                                 \\  |  /\n"
           + "`. __/ \\__ .'   ====================================    `. __/ \\__ .'\n"
           + "_ _\\     /_ _                                           _ _\\     /_ _\n"
           + "   /_   _\\           Longest match of all time:            /_   _\\\n"
           + " .'  \\ /  `.                                             .'  \\ /  `.\n";

    total  = " .'  \\ /  `.   "
           + sprintf("%|40s", "Single Day total wins: " + at_total[1] + " by "
                     + capitalize(at_total[0]))
           + "  .'  \\ /  `.\n";

    udog   = "   /  |  \\     "
           + sprintf("%|40s", "Single Day U-Dog wins: " + at_u_dog[1] + " by "
                     + capitalize(at_u_dog[0]))
           + "    /  |  \\\n";

    streak = "      |        "
           + sprintf("%|40s", "Longest Win-Streak: " + at_streak[1] + " by "
                     + capitalize(at_streak[0]))
           + "       |\n";

    longst = "   /  |  \\     "
           + sprintf("%|39s", at_rounds[0] + " at " + at_rounds[1] + " rounds")
           + "     /  |  \\\n"
           + "      |                                                       |\n";

    who->catch_tell(border);
    who->catch_tell(midder);
    who->catch_tell(total);
    who->catch_tell(udog);
    who->catch_tell(streak);
    who->catch_tell(llower);
    who->catch_tell(longst);
    who->catch_tell(border);
    who->catch_tell("\nYou also notice a tally of champions written on a"
      + " long scroll nailed to the wall.\n");

    return;
} /* display_records */


/*
 * Function name:        exa_all_time_records
 * Description  :        show the player the list of all time records
 * Returns      :        null string
 */
public string
exa_all_time_records()
{
    display_records(this_player());
    return "";
} /* exa_all_time_records */


/*
 * Function name:       near_midnight
 * Description  :       get some info about whether it is soon to be
 *                      a day flip.
 * Returns      :       int - 0 if more than 5 minutes till midnight
 *                            otherwise, return number of minutes left
 *                            till midnight.
 */
public int
near_midnight()
{
    string    time_txt = ctime(time());
    int       hour     = atoi(time_txt[11..12]);
    int       minutes  = atoi(time_txt[14..15]);
    int       remain   = 60 - minutes;

    if (hour == 23 && remain < 9)
    {
        return remain;
    }

    return 0;
} /* near_midnight */


/*
 * Function name:        add_wrestling_fatigue
 * Description  :        add fatigue to the player each round. The
 *                       amount of fatigue is as follows:
 *                         - favorite - 5% of total
 *                         - even     - 10% of total
 *                         - underdog - 20% of total
 * Arguments    :        object who - the player
 *                       string w_status - their status (see above)
 */
public void
add_wrestling_fatigue(object who, string w_status)
{
    mapping  fatigue_map = ([ "dominating" : 0.05,
                              "equal"      : 0.1,
                              "hopeless"   : 0.2 ]);
    float    player_fatigue = itof(who->query_max_fatigue());
    int      wrestling_fatigue;

    wrestling_fatigue = ftoi(player_fatigue * fatigue_map[w_status]);
    who->add_fatigue(-wrestling_fatigue);

} /* add_wrestling_fatigue */


/*
 * Function name:        exa_note
 * Description  :        allow players to examine the money tally
 * Returns      :        null string
 */
public string
exa_note()
{
    WRESTLING_MASTER->print_monies(this_player());
    return "";
} /* exa_note */


/*
 * Function name:        exa_champions
 * Description  :        allow players to examine the money tally
 * Returns      :        null string
 */
public string
exa_champions()
{
    WRESTLING_MASTER->print_champions(this_player());
    return "";
} /* exa_champions */


/*
 * Function name:        exa_betters
 * Description  :        allow wizards to see who has won bets so far
 *                       today
 * Returns      :        string
 */
public string
exa_betters()
{
    if (!this_player()->query_wiz_level())
    {
        return "You find no such thing.\n";
    }

    WRESTLING_MASTER->print_betters(this_player());
    return "";
} /* exa_betters */
