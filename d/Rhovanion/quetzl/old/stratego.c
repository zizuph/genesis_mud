#pragma strict_types
 
#include "defs.h"
#include <macros.h>
 
inherit GAME;
 
#define GAME_NAME "Stratego"
 
#define RANKS ({ "Marshall", "General", "Colonel", "Major", "Captain",  \
    "Lieutenant", "Sergeant", "Miner", "Scout", "Spy", "Bomb", "Flag" })
 
#define SYMBOLS ({"1", "2", "3", "4", "5", "6", "7", "8", "9", "S", "B", "F"})
 
#define START_NUMS ({ 1, 1, 2, 3, 4, 4, 4, 5, 8, 1, 6, 1 })
 
public mixed l_to_place;
 
public string *two_boards;
 
static string gPiece;
static int gPlace;
 
public varargs void
malter_board(int which, string a1, int a2, int a3)
{
    set_board(two_boards[which]);
    ::alter_board(a1, a2, a3);
    two_boards[which] = query_board();
}
 
public int
whose_turn()
{
    if (!query_move_type())
        return query_which_player();
    return ::whose_turn();
}
 
public int *
convert_string(string arg)
{
    int *t = allocate(4);
    if (query_move_type())
        return ::convert_string(arg);
    if (sscanf(arg, "%s at %d %d", gPiece, t[0], t[1]) != 3)
        return ({ 0, 0, 0 ,0 });
    gPlace = member_array(gPiece, SYMBOLS);
    if (gPlace == -1)
        gPlace = member_array(capitalize(gPiece), RANKS);
    if (gPlace == -1)
        return ({ 0, 0, 0, 0 });
    gPiece = SYMBOLS[gPlace];
    return t;
}
 
public int
vb_lpieces(string arg)
{
    int *p, i, j;
    if (strlen(arg))
    {
        notify_fail("Lpieces what?\n");
        return 0;
    }
    write("You have the following pieces left to place:\n\n");
    p = l_to_place[query_which_player()];
    write("    Total: " + p[0] + "\n");
    for (i = 1, j = sizeof(RANKS); i <= j; i++)
        write(sprintf("    %s: %d\n", RANKS[i-1], p[i]));
    return 1;
}
 
public int
vb_newgame(string arg)
{
    if (strlen(arg))
        return 0;
    set_move_type(0);
    initialize_board(10, 1);
    alter_board("+", 3, 5);
    alter_board("+", 4, 5);
    alter_board("+", 7, 5);
    alter_board("+", 8, 5);
    alter_board("+", 3, 6);
    alter_board("+", 4, 6);
    alter_board("+", 7, 6);
    alter_board("+", 8, 6);
 
    two_boards = ({ query_board(), query_board() });
    l_to_place = ({ ({ 40 }) + START_NUMS, ({ 40 }) + START_NUMS });
    if (query_verb() == "game:")
        tell_room(environment(this_object()), "The board is set up for a " +
            "new game.\n");
    return 1;
}
 
public void
create_game()
{
    set_name("board");
    set_adj("stratego");
    set_game_name(GAME_NAME);
    vb_newgame("");
}
 
public string
valid_setup_piece(int x, int y)
{
    if (!(l_to_place[query_which_player()][gPlace + 1]))
        return "You do not have a " + RANKS[gPlace] + " left to play.\n";
    if (!query_which_player() && y > 4)
        return "You can only place a piece in the top four rows.\n";
    if (query_which_player() && y < 7)
        return "You can only place a piece in the bottom four rows.\n";
    if (query_board_segment(x, y) != " ")
        return "There is already a piece there.\n";
}
 
public varargs string
valid_place_piece(int x, int y, int a, int b)
{
    string t;
    int tmp;
    if (!query_move_type())
        return valid_setup_piece(x, y);
 
    set_board(two_boards[query_which_player()]);
    t = query_board_segment(x, y);
    if (member_array(t, SYMBOLS) == -1)
        return "You don't have a piece there!\n";
    if (t == "B" || t == "F")
        return "You can't move that piece.\n";
 
    if (t != "9")
    {
        if (ABS(y - b) + ABS(x - a) > 1)
                return "You can't move that many spaces.\n";
    }
    else
    {
        if ((x != a && y != b) || (x == a && y == b))
            return "That piece can't move in that way.\n";
        if (a > x)
        {
            tmp = a;
            while(--a > x)
                if (query_board_segment(a, y) != " ")
                    return "You can't move through a piece.\n";
            a = tmp;
        }
        else if (x > a)
        {
            tmp = x;
            while(--x > a)
                if (query_board_segment(x, y) != " ")
                    return "You can't move through a piece.\n";
            x = tmp;
        }
        else if (b > y)
        {
            tmp = b;
            while(--b > y)
                if (query_board_segment(x, b) != " ")
                    return "You can't move through a piece.\n";
            b = tmp;
        }
        else
        {
            tmp = y;
            while(--y > b)
                if (query_board_segment(x, y) != " ")
                    return "You can't move through a piece.\n";
        }
    }
    t = query_board_segment(a, b);
    if ((t != "*") && (t != " "))
        return "You can't move into your own pieces!\n";
}
 
public int
vb_view(string arg)
{
    set_board(two_boards[query_which_player()]);
    return ::vb_view(arg);
}
 
public void
do_place_new(int x, int y)
{
    int who = query_which_player();
    write("You place your piece at the " + con_to_string(x, y) + ".\n");
    say(QCTNAME(this_player()) + " places a piece at the " +
        con_to_string(x, y) + ".\n");
    l_to_place[who][0] = l_to_place[who][0] - 1;
    l_to_place[who][gPlace + 1] = l_to_place[who][gPlace + 1] - 1;
    if (!l_to_place[who][0])
        if (!l_to_place[(who ? 0 : 1)][0])
        {
            say("All the pieces are set up, and the game begins.\n", ({}));
            set_move_type(1);
        }
    malter_board(who, gPiece, x, y);
    malter_board(who ? 0 : 1, "*", x, y);
}
 
public string
query_b_seg(int a, int x, int y)
{
    set_board(two_boards[a]);
    return query_board_segment(x, y);
}
 
public void
do_victory()
{
    write("You capture the enemy flag and win.\n");
    say(QCTNAME(this_player()) + " captures the flag and achieves victory.\n");
    end_game();
    return;
}
 
public varargs void
do_place_piece(int x, int y, int a, int b)
{
    int f, g;
    if (!query_move_type())
   {
        do_place_new(x, y);
        return;
    }
 
    write(sprintf("You move your %s from %d %d to %d %d.\n",
        RANKS[member_array(query_board_segment(x, y), SYMBOLS)],
        x, y, a, b));
    say(QCTNAME(this_player()) + " moves a piece from " +
        sprintf("%d %d to %d %d.\n", x, y, a, b));
 
    if (query_board_segment(a, b) == " ")
    {
        if (!whose_turn())
        {
            f = 1; g = 0;
        }
        else
        {
            g = 1; f = 0;
        }
        malter_board(g, query_b_seg(g, x, y), a, b);
        malter_board(g, " ", x, y);
        malter_board(f, "*", a, b);
        malter_board(f, " ", x, y);
    }
 
    if (f | g)
        return;
    g = member_array(query_b_seg(whose_turn(), x, y), SYMBOLS);
    f = member_array(query_b_seg((whose_turn() ? 0 : 1), a, b), SYMBOLS);
    if (f == g)
    {
        say(sprintf("The %s confronts the %s, and they battle to the death!\n",
            RANKS[g], RANKS[g]), ({}));
        malter_board(0, " ", x, y);
        malter_board(1, " ", x, y);
        malter_board(0, " ", a, b);
        malter_board(1, " ", a, b);
        return;
    }
    if (f == 11)
    {
       do_victory();
       return;
    }
    if (f == 10 && g != 7)
    {
        f = -1;
    }
    if (g == 9 && f == 0)
    {
        g = -1;
    }
    if (f < g)
    {
        if (f == -1)
            say("The " + RANKS[g] + " runs into a bomb and dies.\n", ({}));
        else
            say("The " + RANKS[g] + " confronts a " + RANKS[f] + " and is " +
               "quickly defeated.\n", ({}));
        malter_board(0, " ", x, y);
        malter_board(1, " ", x, y);
        return;
    }
    else
    {
        if (f == 10)
            say("The miner moves forward and defuses the bomb!\n", ({}));
        else if (g == -1)
            say("The spy sneaks up on the Marshall and slays him!\n", ({}));
        else
            say("The " + RANKS[g] + " challenges the " + RANKS[f] + " and " +
                "is victorious.\n", ({}));
        malter_board(0, " ", x, y);
        malter_board(1, " ", x, y);
        malter_board(whose_turn(), SYMBOLS[g], a, b);
        malter_board((whose_turn() ? 0 : 1), "*", a, b);
        return;
    }
}
