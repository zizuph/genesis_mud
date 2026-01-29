/*
 * /d/Gondor/common/dwarf_guild/npc/player.c
 *
 * Copyright (C) Stas van der Schaaf - January 7 1994
 *               Mercade @ Genesis
 *
 * This dude sits in the pub in the Dwarven race guild. He plays chess. If
 * you manage to solve all his problems, he will reward you. To allow
 * players to use algebraic notation I wrote the function parse_move and I
 * must admit that I find that a very neat function! :-)
 *
 * Players that are working on some problems will be saved and only after
 * four weeks the are forgotten.
 *
 * Revision history:
 * Gwyneth 4 November 2000 - Replaced ~elessar/lib/goodkill.h with
 *                           /d/Gondor/common/lib/logkill.c
 */

inherit "/d/Gondor/common/dwarf_guild/npc/remember";

#include <const.h>
#include <formulas.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/common/lib/logkill.c"
#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "../dwarf.h"
#include "../chess.h"

#define SAVE_FILE         (DWARVEN_RACE_GUILD_NPCS + "chessplayer_save")
#define MY_NAME           "oin"
#define BASE              40
#define COMPUTE_STAT      (((BASE * 3) / 4) + random(BASE / 2) + 1)
#define COMPUTE_SKILL     max(COMPUTE_STAT, 100)
#define CLONE_OBJECT(s)   clone_object(s)->move(this_object(), 1)
#define PROBLEM_MAX_TIME  2419200 /* four weeks before I forget */
#define PICK_PROBLEMS     7 /* problems picked initially */
#define MAY_NOT_SOLVE     2 /* need not solve all problems */
#define PROBLEMS_VARIABLE "current_problems"
#define CHESSBOARD        (DWARVEN_RACE_GUILD_OBJECTS + "chess")
#define CHESSBOARD_ID     (DWARVEN_RACE_GUILD_PREFIX + "chessboard")
#define DIE               (DWARVEN_RACE_GUILD_OBJECTS + "die")
#define DIE_ID            (DWARVEN_RACE_GUILD_PREFIX + "die")

#define FALSE_REACTIONS                                                  \
    ({ ("You stupid " + ((TP->query_gender() == G_FEMALE) ? "woman" :    \
       TP->query_race_name()) + "! Cannot you come up with something " + \
       "better"),                                                        \
       "What??? This isn't checkers",                                    \
       "Oh no! Are my problems really that hard to solve",               \
       "A pitiful display",                                              \
       "How on earth can you come up with that",                         \
       "Better luck next time",                                          \
       "It was a mistake to play with you",                              \
    })
#define FALSE_EMOTES_WITH_TARGET \
    ({ "duh at ", "laugh at ", "comfort ", "chuckle at " })
#define FALSE_EMOTES_NO_TARGET \
    ({ "twist", "contemplate", "chuckle", "rolleyes" })
#define FALSE_EMOTION (random(2) ?           \
    (ONE_OF_LIST(FALSE_EMOTES_WITH_TARGET) + CAP(TP->query_real_name())) : \
    ONE_OF_LIST(FALSE_EMOTES_NO_TARGET))

#define GOOD_REACTIONS                          \
    ({ "Very well played",                      \
       "Way to go",                             \
       "A correct solution indeed",             \
       "You must be a lover of the noble game", \
       "Excellent, you solved the problem",     \
       "They seem so easy to you",              \
       "You are almost as good as I am",        \
    })
#define GOOD_EMOTES_WITH_TARGET \
    ({ "smile at ", "nod at ", "applaud to ", "compliment " })
#define GOOD_EMOTES_NO_TARGET \
    ({ "cheer", "clap", "smile", "applaud" })
#define GOOD_EMOTION (random(2) ?                                         \
    (ONE_OF_LIST(GOOD_EMOTES_WITH_TARGET) + CAP(TP->query_real_name())) : \
    ONE_OF_LIST(GOOD_EMOTES_NO_TARGET))

/*
 * Prototypes
 */
int do_solution(string str);
int do_complaint(string str);
private void update_problems();

/*
 * Global variables
 */
mapping current_problems = ([ ]);
/*
 * The index of the mapping is the real name of the player. In it you
 * find a mixed ({ int time_last_meet, array of int problem number })
 */
static  object chessboard      =  0;
static  int    current_problem = -1; /* illegal init */
static  object current_player  =  0;

void
create_monster() 
{
    set_name(MY_NAME);
    add_name( ({ "player", "chessplayer" }) );
    set_living_name(MY_NAME);
    set_race_name("dwarf");

    set_adj("old");
    add_adj("gracefully-bearded");

    set_long("You are looking at an old, yet gracefully-bearded dwarf. " +
        "He is the father of the the bartender of this pub and he is a " +
        "master in the noble art of playing chess. If you ask him to play " +
        "a game with him, I am sure that he will do you the honour.\n");

    set_title("son of Cloin, master in the art of chess");

    set_gender(G_MALE);

    set_base_stat(SS_STR, COMPUTE_STAT);
    set_base_stat(SS_DEX, COMPUTE_STAT);
    set_base_stat(SS_CON, COMPUTE_STAT);
    set_base_stat(SS_WIS, COMPUTE_STAT + 20);
    set_base_stat(SS_INT, COMPUTE_STAT);
    set_base_stat(SS_DIS, COMPUTE_STAT);

    REFRESH;  /* hp, mana, fatigue  */
    FIX_EUID; /* set the euid right */

    set_alignment(200);

    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_WEP_AXE,      COMPUTE_SKILL);
    set_skill(SS_PARRY,        COMPUTE_SKILL);
    set_skill(SS_DEFENCE,      COMPUTE_SKILL);
    set_skill(SS_AWARENESS,    COMPUTE_SKILL);
    set_skill(SS_UNARM_COMBAT, COMPUTE_SKILL);

    set_mm_in(" arrives.");
    set_mm_out(" walks away.");

    set_npc_save_file(SAVE_FILE);
    create_remember( ({ PROBLEMS_VARIABLE }) );
    current_problems = query_npc_variable(PROBLEMS_VARIABLE);
    if (!mappingp(current_problems))
    {
        current_problems = ([ ]);
    }

    set_dont_answer_unseen(1);
    add_ask( ({ "game", "chess", "play", "play a game", "play chess",
        "instruction", "instructions" }),
        VBFC_ME("ask_play_chess"));
    add_ask( ({ "next", "next problem", "problem" }),
        VBFC_ME("ask_next_problem"));
    add_ask( ({ "complain", "complaint" }),
        VBFC_ME("ask_complaint"));

    set_alarm(1.0, 0.0, reset_monster);
    set_alarm(1.0, 0.0, update_problems);
}

void
arm_chessplayer()
{
    object ob;

    fix_souls();

    CLONE_OBJECT(DWARVEN_RACE_GUILD_ARMOURS + "k_cloak");
    CLONE_OBJECT(DWARVEN_RACE_GUILD_ARMOURS + "k_sweater");
    CLONE_OBJECT(DWARVEN_RACE_GUILD_ARMOURS + "k_pants");

    CLONE_OBJECT(DIE);
    CLONE_OBJECT(DIE);

    ob = clone_object(DWARVEN_RACE_GUILD_ARMOURS + "npc_belt");
    ob->move(this_object(), 1);
    ob->set_owner_name(MY_NAME);

    command("wear all");

    ob = clone_object(DWARVEN_RACE_GUILD_OBJECTS + "wallet");
    ob->move(this_object(), 1);

    MONEY_MAKE_GC(random( 5))->move(ob, 1);
    MONEY_MAKE_SC(random(10))->move(ob, 1);
    MONEY_MAKE_CC(random(20))->move(ob, 1);
}

void
init_living()
{
    ::init_living();

    add_action(do_solution,  "solution");
    add_action(do_complaint, "complaint");
}

void
reset_monster()
{
    /* If Oin is killed and reloads, the chessboard may already be there.
     * Take posession of the board and reset it.
     */
    if (present(CHESSBOARD_ID, ENV(TO)) &&
        (!objectp(chessboard)))
    {
        chessboard = present(CHESSBOARD_ID, ENV(TO));
        chessboard->reset_chessboard();
        current_problem = -1;
        TELL_ROOM(ENV(TO), TO, " puts the pieces on the chessboard in their " +
            "initial position.", TO);
    }
    else
    {
        chessboard = clone_object(CHESSBOARD);
        chessboard->move(ENV(TO));
        chessboard->reset_chessboard();
        current_problem = -1;
        TELL_ROOM(ENV(TO), TO, " takes a chessboard from " + POSSESSIVE(TO) +
            " cloak and puts it on the table.", TO);
    }
}

/*
 * Function name: parse_move
 * Description  : This function will check the solution given by the player
 *                for illegal characters. Also the whole solution is made
 *                lower case. It can handle any move that is notated in
 *                algebraic notation as long as it is in extensive notation.
 *                I like this function very much! :-)
 * Arguments    : string - the move to parse
 * Returns      : string - the parsed move
 */
string
parse_move(string in_move)
{
    string *sub_move = explode(in_move, "");
    string tmp;
    int    i;

    in_move = "";

    /* Not enough letters in the solution. Should be at least 3 for castling. */
    if (sizeof(sub_move) < 3)
    {
        return 0;
    }

    /* this is to remove all unwanted characters */
    for (i = 0; i < sizeof(sub_move); i++)
    {
        tmp = lower_case(sub_move[i]);

        if ((member_array(tmp, BOARD_LETTERS) > -1) ||
            (member_array(tmp, BOARD_NUMBERS) > -1) ||
            (member_array(tmp, PIECE_NAMES)   > -1))
        {
            in_move += tmp;
        }
    }

    sub_move = explode(in_move, "");
    in_move = "";

    /* this is to remove all piece names except in the end. */
    for (i = 0; i < (sizeof(sub_move) - 2); i++)
    {
        if (!((member_array(sub_move[i], PIECE_NAMES) > -1) &&
              (member_array(sub_move[i + 1], BOARD_LETTERS) > -1)))
        {
            in_move += sub_move[i];
        }
    }

    return (in_move + sub_move[i] + sub_move[i + 1]);
}

string
ask_next_problem()
{
    string name = (string)TP->query_real_name();
    int    *games;
    int    index;

    if (objectp(current_player) && present(current_player, ENV()) &&
        (current_player != TP))
    {
        npc_say("I am sorry, " + player_name(TP) +
            ", but I am currently playing with " +
            player_name(current_player) + ". When " +
            PRONOUN(current_player) +
            " is done playing, I shall play a game with you.");
        return "";
    }

    current_player = TP;

    if (member_array(name, m_indices(current_problems)) == -1)
    {
        command("hmm");
        npc_say("You should ask me to play a game before you can ask " +
            "for the next problem, " + player_name(TP) + ".");
        return "";
    }

    games = current_problems[name][1];
    index = member_array(current_problem, games);
    index = ((index == -1) ? 0 :
        (((index + 1) == sizeof(games)) ? 0 : (index + 1)));

    current_problem = games[index];
    chessboard->set_position(problems[current_problem + 1]);

    current_problems[name] = ({ time(), games });
    set_npc_variable(PROBLEMS_VARIABLE, current_problems);
    save_npc();

    tell_room(ENV(TO), QCTNAME(TO) + " puts another problem on the board.\n");
    npc_say("If you have found the solution, " + player_name(TP) + ", just " +
        "do \"solution <move>\". If you have a problem, just ask me how " +
        "to \"complain\". If you want me to repeat my instructions, just " +
        "ask me about them. Syntax instructions are on the piece of paper.");

    npc_say("Note that " +
        ((problems[current_problem][0..0] == "#") ? "black" : "white") +
        " is the player that should give mate in two!");

    return "";
}

string
ask_play_chess()
{
    string name = (string)TP->query_real_name();
    int    *games = ({ });
    int    i;
    int    index;

    if (TP->query_npc())
    {
        write("Become an interactive player if you want to play!");
        return "";
    }

    if (TP->test_bit("Gondor", DWARVEN_RACE_GUILD_CHESS_GROUP,
        DWARVEN_RACE_GUILD_CHESS_BIT))
    {
        npc_say("You have already solved my chess-problems, " +
            player_name(TP) + ".");
        return "";
    }

    if (objectp(current_player) && present(current_player, ENV()) &&
        (current_player != TP))
    {
        npc_say("I am sorry, " + player_name(TP) +
            ", but I am currently playing with " +
            player_name(current_player) + ". When " +
            PRONOUN(current_player) +
            " is done playing, I shall play a game with you.");
        return "";
    }

    current_player = TP;

    if (member_array(name, m_indices(current_problems)) != -1)
    {
        npc_say("Oke, " + player_name(TP) + ". I shall tell you again. " +
            "Each of the problems I have designed for you should give " +
            "mate in two. I want you to tell me the first move of those " +
            "two moves. If you want to contemplate a certain position for " +
            "a longer time, you can ask me for the \"next problem\". " +
            "Beside the board is a paper with instructions on the format.");

        return ask_next_problem();
    }

    games = ({ (random(sizeof(problems) / 2) * 2) });

    for(i = 1; i < PICK_PROBLEMS; i++)
    {
        while(member_array((index =
            (random(sizeof(problems) / 2) * 2)), games) != -1);

        games += ({ index });
    }

    npc_say("How good of you to join me, " + player_name(TP) + ". Let us " +
        "play some chess. For you I have prepared " + PICK_PROBLEMS +
        " problems to solve. All problems should go mate in two. If you " +
        "know the solution you may do \"solution <move>\" where <move> should " +
        "comply to the instructions beside the board. You only need to " +
        "tell me the first move that will lead to mate on the second move. " +
        "White is the player to move, unless I tell you otherwise. You may " +
        "ask me for the \"next problem\" if you are done looking at a " +
        "problem one and did not come up with a solution. I will remember " +
        "the problems I have shown you so you may study them while you are " +
        "adventuring elsewhere. If you have a problem or think there is " +
        "something wrong with a position I show you, please ask me how to " +
        "\"complain\" and I will help you.");

    current_problem = games[0];
    chessboard->set_position(problems[current_problem + 1]);

    tell_room(ENV(TO), QCTNAME(TO) + " puts a problem on the board.\n");

    if (problems[current_problem][0..0] == "#")
    {
        npc_say("Note that black is the player that should give mate in two!");
    }

    current_problems[name] = ({ time(), games });
    set_npc_variable(PROBLEMS_VARIABLE, current_problems);
    save_npc();

    return "";
}

int
do_solution(string str)
{
    string name = (string)TP->query_real_name();
    int    *games;
    int    exp = DWARVEN_RACE_GUILD_CHESS_EXP;
    int    index;

    say(QCTNAME(TP) + " suggests a solution to " + QTNAME(TO) + ".\n");

    if (!strlen(str))
    {
        npc_say("And what solution would that be, " + player_name(TP) + "?");
        return 1;
    }

    if (objectp(current_player) && present(current_player, ENV()) &&
        (current_player != TP))
    {
        npc_say("I am sorry, " + player_name(TP) +
            ", but I am currently playing with " +
            player_name(current_player) + ". When " +
            PRONOUN(current_player) +
            " is done playing, I shall play a game with you.");
        return 1;
    }

    current_player = TP;

    if (member_array(name, m_indices(current_problems)) == -1)
    {
        npc_say("You have not asked me to play a game with you, " +
            player_name(TP) + ", so you cannot tell me solutions either.");
        return 1;
    }

    games = current_problems[name][1];

    if ((index = member_array(current_problem, games)) == -1)
    {
        command("contemplate");
        npc_say("I have never showed you this problem to solve, " +
            player_name(TP) + ".");
        return 1;
    }

    if (parse_move(str) != parse_move(problems[current_problem]))
    {
        command(FALSE_EMOTION);
        npc_say(ONE_OF_LIST(FALSE_REACTIONS) + ", " + player_name(TP) + ".");
        npc_say("I shall show you another problem.");
        ask_next_problem();
        return 1;
    }

    command(GOOD_EMOTION);
    npc_say(ONE_OF_LIST(GOOD_REACTIONS) + ", " + player_name(TP) + ".");

    games = exclude_array(games, index, index);

    if (sizeof(games) > MAY_NOT_SOLVE)
    {
        npc_say("I shall show you another problem.");
        current_problems[name] = ({ time(), games });
        set_npc_variable(PROBLEMS_VARIABLE, current_problems);
        save_npc();
        ask_next_problem();
        return 1;
    }

    npc_say("You have solved my quest, " + player_name(TP) + "! I shall " +
        "reward you for this.");
    command("congratulate " + CAP(name));
    write("You feel more experienced.\n");

    chessboard->reset_chessboard();
    current_problem = -1;

    current_problems = m_delete(current_problems, name);
    set_npc_variable(PROBLEMS_VARIABLE, current_problems);
    save_npc();

    TP->set_bit(DWARVEN_RACE_GUILD_CHESS_GROUP, DWARVEN_RACE_GUILD_CHESS_BIT);
    TP->add_exp_quest(exp);
    LOG_QUEST(TP, exp, "DWARVEN CHESS PLAYER");

    return 1;
}

string
ask_complaint()
{
    npc_say("I regret it that you have a problem, " + player_name(TP) +
        ", but I shall try to help you as good as possible. To file a " +
        "complaint, please do \"complaint <message>\" and you shall " +
        "receive a reply as soon as possible. Please be very specific in " +
        "your <message>. State which move you tried, and why you think " +
        "that the position now on the board cannot be solved. With your " +
        "complaint, I shall remember which position in on the board now. " +
        "You can also make a \"bug\" report, but then I will not remember " +
        "which position is on the board.");

    return "";
}

int
do_complaint(string str)
{
    if (!strlen(str))
    {
        npc_say("Just do \"complaint <message>\" to file a complaint.");
        return 1;
    }

    write_file(LOG_DIR + "bugs", ctime(time())[4..9] + ctime(time())[-5..] +
        " " + MASTER + " " + MY_NAME + " (" + TP->query_real_name() + ")\n" +
        "Complaint about chess position " + (current_problem / 2) +
        ".\n<begin of complaint>\n" + BSN(str) + "<end of complaint>\n\n");

    npc_say("Oke, " + player_name(TP) + " you will receive a reply as soon " +
        "as possible.");
    return 1;
}

void
player_leaves(object player)
{
    if (player == current_player)
    {
        current_player = 0;
    }
}

private void
update_problems()
{
    string *players;
    int    index = -1;
    int    size;

    players = m_indices(current_problems);

    size = sizeof(players);
    while(++index < size)
    {
        if (current_problems[players[index]][0] + PROBLEM_MAX_TIME < time())
        {
            current_problems = m_delete(current_problems, players[index]);
        }
    }

    set_npc_variable(PROBLEMS_VARIABLE, current_problems);
    save_npc();
}

/*
 * A service function that allows you to cheat on the quest :-)
 */
mixed
query_position(int index)
{
    if ((index >= sizeof(problems)) ||
        (index < 0))
    {
        return "Illegal index.\n";
    }

    return problems[index];
}

/*
 * We are friendly for other domains, Solamnian knights may not kill him!
 */
int
query_knight_prestige()
{
    return -3;
}
