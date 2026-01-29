#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <composite.h>
#include <language.h>
#include <cmdparse.h>
 
#define UP(x) (-21 * x)
#define DOWN(x) (21 * x)
#define LEFT(x) (-1 * x)
#define RIGHT(x) (1 * x)
 
int sort_pieces(int arg);
 
public int *black,
           *white,
           turn,
           game_over;
 
static string board;
 
public int
insert_piece(int position)
{
    string ins;
   switch(sort_pieces(position))
   {
        case 1: ins = "X"; break;
        case 0: ins = "+"; break;
        case -1: ins = "O"; break;
    }
    board = extract(board, 0, position * 2 -1) + ins +
        extract(board, position * 2 + 1);
   return -2;
}
 
public void
initialize_board()
{
    board = "+ + + + + + + + + + + + + + + + + + + + + " +
    "+ + + + + + + + + + + + + + + + + + + + + " +
    "+ + + + + + + + + + + + + + + + + + + + + " +
    "+ + + + + + + + + + + + + + + + + + + + + " +
    "+ + + + + + + + + + + + + + + + + + + + + " +
    "+ + + + + + + + + + + + + + + + + + + + + " +
    "+ + + + + + + + + + + + + + + + + + + + + " +
    "+ + + + + + + + + + + + + + + + + + + + + " +
    "+ + + + + + + + + + + + + + + + + + + + + " +
    "+ + + + + + + + + + + + + + + + + + + + + " +
    "+ + + + + + + + + + + + + + + + + + + + + " +
    "+ + + + + + + + + + + + + + + + + + + + + " +
    "+ + + + + + + + + + + + + + + + + + + + + " +
    "+ + + + + + + + + + + + + + + + + + + + + " +
    "+ + + + + + + + + + + + + + + + + + + + + " +
    "+ + + + + + + + + + + + + + + + + + + + + " +
    "+ + + + + + + + + + + + + + + + + + + + + " +
    "+ + + + + + + + + + + + + + + + + + + + + " +
    "+ + + + + + + + + + + + + + + + + + + + + " +
    "+ + + + + + + + + + + + + + + + + + + + + " +
    "+ + + + + + + + + + + + + + + + + + + + + ";
}
 
public int
clean_slate(string arg)
{
    if (arg != "up board")
    {
        notify_fail("What did you want to set up?\n");
        return 0;
    }
 
    write("You set up the board for play.\n");
    say(QCTNAME(this_player()) + " sets up the board for play.\n");
    turn = 1;
    remove_prop("black_prop");
    remove_prop("white_prop");
    game_over = 0;
    black = ({ });
    white = ({ });
    initialize_board();
    return 1;
}
 
public string
con_to_string(int i)
{
    int x, y;
    x = i % 21 + 1;
    y = i / 21 + 1;
    return LANG_WORD(x) + " column " + LANG_WORD(y) + " row";
}
 
public int
convert_position(string arg)
{
    int x, y;
    if (sscanf(arg, "%d %d", x, y) != 2)
        return -1;
    if (x < 1 || y < 1 || x > 21 || y > 21)
        return -1;
    x--; y--;
    return y * 21 + x;
}
 
public int
sort_pieces(int arg)
{
    if (member_array(arg, black) != -1)
        return 1;
    if (member_array(arg, white) != -1)
        return -1;
    return 0;
}
 
public int
check_five(int checkpoint)
{
    int high, shift, i, color, x, y;
    x = checkpoint % 21; y = checkpoint / 21;
    color = sort_pieces(checkpoint);
 
    for (i = 0; i < 5; i++)
    {
        if (x + LEFT(i) < 0) 
            break;
        if (sort_pieces(checkpoint + LEFT(i)) == color)
            high++;
        else
            break;
    }
    for (i = 1; i < 5; i++)
    {
        if (x + RIGHT(i) >= DOWN(1))
            break;
        if (sort_pieces(checkpoint + RIGHT(i)) == color)
            high++;
        else
            break;
    }
    if (high >= 5)
        return 1;
 
    high = 0;
    for (i = 0; i < 5; i++)
    {
        if (y - i < 0)
            break;
        if (sort_pieces(checkpoint + UP(i)) == color)
            high++;
        else
            break;
    }
    for (i = 1; i < 5; i++)
    {
        if (y + i >= DOWN(1))
            break;
        if (sort_pieces(checkpoint + DOWN(i)) == color)
            high++;
        else
            break;
    }
    if (high >= 5)
        return 1;
 
    high = 0;
    for (i = 0; i < 5; i++)
    {
        if (x + LEFT(i) < 0 || y - i < 0) 
            break;
        if (sort_pieces(checkpoint + LEFT(i) + UP(i)) == color)
            high++;
        else
            break;
    }
    for (i = 1; i < 5; i++)
    {
        if (x + RIGHT(i) >= DOWN(1) || y + i >= DOWN(1))
            break;
        if (sort_pieces(checkpoint + RIGHT(i) + DOWN(i)) == color)
            high++;
        else
            break;
    }
    if (high >= 5)
        return 1;
 
    high = 0;
    for (i = 0; i < 5; i++)
    {
        if (y - i < 0 || x + RIGHT(i) >= DOWN(1))
            break;
        if (sort_pieces(checkpoint + UP(i) + RIGHT(i)) == color)
            high++;
        else
            break;
    }
    for (i = 1; i < 5; i++)
    {
        if (y + i >= DOWN(1) || x + LEFT(i) < 0)
            break;
        if (sort_pieces(checkpoint + DOWN(i) + LEFT(i)) == color)
            high++;
        else
            break;
    }
    if (high >= 5)
        return 1;
    return 0;
}
 
public int
query_game_over()
{
    return game_over;
}
 
public int
my_turn()
{
    return this_player() == query_prop((turn ? "black_prop" : "white_prop"));
}
 
public int
place_piece(string arg)
{
    int i;
 
    if (game_over)
    {
        notify_fail("You should set up a new game before you start " +
            "to play.\n");
        return 0;
    }
 
    if (!query_prop("black_prop") || !query_prop("white_prop"))
    {
        notify_fail("You must have two players to play!\n");
        return 0;
    }
 
    if (!my_turn())
    {
        notify_fail("It is not your turn to play!\n");
        return 0;
    }
 
    i = convert_position(arg);
    if (i == -1)
    {
         notify_fail("Where did you want to place a piece?\n");
        return 0;
    }
 
    if (sort_pieces(i))
    {
        notify_fail("There is already a piece there!\n");
        return 0;
    }
    write("You place one of your pieces on the " + con_to_string(i) + ".\n");
    say(QCTNAME(this_player()) + " plays a piece on the " + con_to_string(i) +
        ".\n");
    if (turn)
        black += ({ i });
    else
        white += ({ i });
    insert_piece(i);
    if (check_five(i))
    {
        write("As you play your piece, you declare victory.\n");
        say(QCTNAME(this_player()) + " declares victory with the placement " +
            "of the last piece.\n");
        game_over = sort_pieces(i);
        return 1;
    }
    turn = (turn ? 0 : 1);
    return 1;
}
 
public void
create_object()
{
    set_name("board");
    set_adj("game");
    set_long("This board is set up for the ancient game of fives, developed " +
        "long ago in Arcoron. If you do not know the rules, shake the board " +
        "and they will be revealed to you!\n");
    game_over = -2;
    initialize_board();
}
 
public int
shake_board(string arg)
{
    if (arg != "board")
    {
        notify_fail("Shake what?\n");
        return 0;
    }
    write("The rules of five are simple:\n\n" +
        "Fives is a game for two players, to begin a game, place the board " +
        "on the ground and set up the board. Then each player should sit at " +
        "the board. Black begins, and the turn alternates after that. Each " +
        "player places one piece on the board in an attempt to make five " +
        "in a row. The first piece must be placed in the center; each piece " +
        "thereafter must be placed adjacent to any existing piece. If you " +
        "place your piece such that two enemy pieces are in a straight line " +
        "from the piece, followed by one more of your pieces (in the form " +
        "XOOX), the two center pieces are captured. Five captures, or five " +
        "in a row wins the game.\n\n" +
        "Quick Summary:\n" +
        "  place <x> <y>   - place a piece at row x column y\n" +
        "  set up board    - begin a new game\n" +
        "  sit at board    - enter yourself as a player in the game\n" +
        "  view board      - look over the board to see all pieces\n" +
        "  rise from board - exit the game\n" +
        "  Five in a row or five captures wins.\n");
    return 1;
}
 
public int
view_board(string arg)
{
    string blah = "";
    string *tb = explode(break_string(board, 41), "\n");
    int i;
    if (arg != "board")
    {
        notify_fail("View what?\n");
        return 0;
    }
    write("                     1 1 1 1 1 1 1 1 1 1 2 2\n" +
          "   1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1\n");
    i = 12;
    while(i--)
        blah = "" + (i + 10) + " " + tb[i+9] + "\n" + blah;
    i = 9;
    while(i--)
        blah = " " + (i + 1) + " " + tb[i] + "\n" + blah;
    write(blah);
    return 1;
}
 
public int
new_player(string arg)
{
    if (arg != "at board")
    {
        notify_fail("Sit at what?\n");
        return 0;
    }
    if (this_player() == query_prop("white_prop") || this_player() ==
        query_prop("black_prop"))
    {
        notify_fail("But you are already playing!\n");
        return 0;
    }
    if (!query_prop("black_prop"))
    {
        add_prop("black_prop", this_player());
        write("You sit down at the board on the black player's position.\n");
        say(QCTNAME(this_player()) + " sits down at the black side of the " +
            "board.\n");
        return 1;
    }
    if (!query_prop("white_prop"))
    {
        add_prop("white_prop", this_player());
        write("You sit down at the board on the white player's position.\n");
        say(QCTNAME(this_player()) + " sits down at the white side of the " +
            "board.\n");
        return 1;
    }
    notify_fail("There are already two players in the game.\n");
    return 0;
}
 
public int
player_out(string arg)
{
    if (arg != "from board")
    {
        notify_fail("Rise from what?\n");
        return 0;
    }
    if (this_player() == query_prop("black_prop"))
        remove_prop("black_prop");
    else if (this_player() == query_prop("white_prop"))
        remove_prop("white_prop");
    write("You stand up from the game.\n");
    say(QCTNAME(this_player()) + " stands from the game.\n");
    return 1;
}
 
public void
init()
{
    ::init();
    add_action("place_piece", "place");
    add_action("clean_slate", "set");
    add_action("new_player", "sit");
    add_action("player_out", "rise");
    add_action("view_board", "view");
   add_action("shake_board", "shake");
}
 
