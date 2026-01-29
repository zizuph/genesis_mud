#pragma strict_types
 
inherit "/std/object";
 
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
 
#define DEFAULT_SERVER "/d/City/quetzl/games/game_storage"
 
private string board,
               messa,
               game_name,
               game_server,
               *players;
 
private int size,
            inside,
            turn,
            game_over,
            move_number,
            move_type,
            stlong;
 
int query_which_player();

/*
 * Function name: set_game_server
 * Description:   set the file name of the desired game server
 * Arguments:     arg - the file name
 */
 
public void
set_game_server(string arg)
{
    game_server = arg;
}
 
/*
 * Function name: query_game_server
 * Description:   give us the file name of the game server
 * Returns:       the file name
 */
 
public string
query_game_server()
{
    return game_server;
}
 
/*
 * Function name: players_here
 * Description:   Finds out which players are currently playing the game
 * Returns:       Binary sum - 1 for first player, 2 for second player
 */
 
public int
players_here()
{
    int ret;
    if (present(players[0], environment())->query_prop("_p_game") ==
        this_object())
        ret |= 1;
    if (present(players[1], environment())->query_prop("_p_game") ==
        this_object())
        ret |= 2;
    return ret;
}
 
/*
 * Function name: nm
 * Description:   give a message to the other player if they are here,
 *                otherwise store it for later.
 * Arguments:     arg - the message, without the name of the player.
 */
 
public void
nm(string arg)
{
    /*
    if (players_here() & ((turn - 1) * -1 + 1))
        tell_object(present(players[(query_which_player() ? 0 : 1],
            environment()), QCTNAME(this_player()) + arg);
    else
        messa += NAME + arg;
    */
}
 
/*
 * Function name: query_game_over
 * Description:   tell us if the game is over, and if so, who won it.
 * Returns:       0 - game in progress, 1 - player 1 won, 2 - player 2 won
 */
 
public int
query_game_over()
{
    return game_over;
}
 
/*
 * Function name: whose_turn
 * Description:   whose turn is it.
 * Returns:       0 or 1
 */
 
public int
whose_turn()
{
    return turn;
}
 
/*
 * Function name: query_which_player
 * Description:   tells us the number of this_player(), if -1 not playing.
 * Returns:       the player number
 */
 
public int
query_which_player()
{
    return member_array(this_player()->query_real_name(), players);
}
 
/*
 * Function name: vb_review
 * Description:   prints out any stored messages in the game we might have.
 * Arguments:     arg - should be ""
 */
 
public void
vb_review(string arg)
{
    if (strlen(arg))
    {
        notify_fail("View what how?\n");
        return 0;
    }
    if (query_which_player() != whose_turn())
    {
        write("You can't see a replay of your own moves. You'll just have " +
            "to remember.\n");
        return;
    }
    write(messa);
    messa = "";
    return;
}
 
/*
 * Function name: con_to_string (convert to string)
 * Description:   give us a nice listing of a board position.
 * Arguments:     x, y - the position on the board
 * Returns:       A string of the form xth column yth row
 */
 
public string
con_to_string(int x, int y)
{
    return LANG_WORD(x) + " column " + LANG_WORD(y) + " row";
}
 
/*
 * Function name: convert_string
 * Description:   convert the players string into coordinates
 * Arguments:     arg - what the player typed
 * Returns:       array 4 of the positions
 */
 
public int *
convert_string(string arg)
{
    int *t;
    if (move_type)
    {
        t = allocate(4);
        if (sscanf(arg, "%d %d to %d %d", t[0], t[1], t[2], t[3]) != 4)
            return ({ 0, 0, 0, 0 });
        else
            return t;
    }
    t = allocate(2);
    if (sscanf(arg, "%d %d", t[0], t[1]) != 2)
        return ({ 0, 0, 0, 0 });
    return t + ({ 0, 0 });
}
 
/*
 * Function name: set_player
 * Description:   try to give us a new player in the game.
 * Arguments:     player - the name of the player, which - the player number
 *                desired.
 * Returns:       a fail string if not success.
 */
 
public string
set_player(string player, int which)
{
    if (which && (which != 1))
        return "Which position did you want to play?\n";
    if (strlen(players[which]))
        if (players[which] == player)
            return "";
        else
            return capitalize(players[which]) + " is already playing that " +
                "position.\n";
    players[which] = player;
    if (players[0] == players[1])
    {
        players[which] = 0;
        return "You can't play both positions at once.\n";
    }
    this_player()->add_prop("_p_game", this_object());
    return "";
}
 
/*
 * Function name: query_player
 * Description:   tell us the name(s) of the player(s)
 * Arguments:     the player number, -1 gives an array of players.
 * Returns:       The name or names requested.
 */
 
public mixed
query_player(int which)
{
    if (which == 1)
        return players[1];
    if (!which)
       return players[0];
    return players;
}
 
/*
 * Function name: set_move_type
 * Description:   move_type means how we move the pieces - by placing down
 *                new ones, or by rearraning old ones.
 * Arguments:     0 - new pieces, 1 - move old.
 */
 
public void
set_move_type(int arg)
{
    move_type = arg;
}
 
/*
 * Function name: query_move_type
 * Description:   give the move type as described in set_move_type
 * Returns:       0 or 1
 */
 
public int
query_move_type()
{
    return move_type;
}
 
/*
 * Function name: query_move_number
 * Description:   tell us how many moves have already been made
 * Returns:       the move number (0 is no moves made yet.)
 */
 
public nomask int
query_move_number()
{
    return move_number;
}
 
/*
 * Function name: initialize_board
 * Description:   Draw a nice picture of a board.
 * Arguments:     t_size - the square size of the board; t_inside -
 *                if 0, a simple board of + is made - if 1, a board of
 *                squares is made. Pieces replace the + if !t_inside,
 *                and sit in the middle of the squares if t_inside.
 */
 
public void
initialize_board(int t_size, int t_inside)
{
    int i;
    string line = "", chunk;
    board = "";
    size = t_size;
    inside = t_inside;
    if (!inside)
    {
        chunk = "+ ";
        i = size;
        while(i--)
            line += chunk;
        line = extract(line, 0, -1);
        line += "\n";
    }
    else
    {
        chunk = "|   ";
        i = size;
        while(i--)
            line += chunk;
        line += "|\n";
        chunk = "+---";
        board = "   ";
        i = size;
        while(i--)
            board += chunk;
        board += "+\n";
        line += board;
    }
    for (i = 0; i < size; i++)
        board += sprintf("%2d %s", i+1, line);
    chunk = "\n";
    i = size;
    line = (inside ? "   " : " ");
    while(i--)
        chunk = sprintf("%s%d%s", line, (i + 1) % 10, chunk);
    chunk = "  " + chunk;
    if (size > 9)
    {
        chunk = "\n" + chunk;
        i = size;
        while(i--)
            if ((i + 1) / 10)
                chunk = line + ((i + 1) / 10) + chunk;
            else
                chunk = line + " " + chunk;
        chunk = "  " + chunk;
    }
    stlong = strlen(chunk);
    board = chunk + board + "\n";
}
 
/*
 * Function name: position
 * Description:   find a specific x, y position in the board string.
 * Arguments:     x, y - the position desired.
 * Returns:       the string position.
 * Note:          if you alter initialize_board(), this function will not
 *                produce the correct number.
 */
 
public int
position(int x, int y)
{
    x--; y--;
    if (!inside)
        return stlong + 2 * ((size + 1) * y + x) + ((y + 1) * 3) - y;
    return ((4 * (size + 1) + 3) * (y + 1)) + ((4 * size) * y) + stlong +
        (3 * (y + 1)) + x * 4;
}
 
/*
 * Function name: distance_from_edge
 * Description:   tell us how many more spaces we have until we reach the edge
 * Arguments:     x, y - the position
 * Returns:       an array of size 8 with the distances. 0 is straight left,
 *                and the array rotates clockwise.
 */
 
public int *
distance_from_edge(int x, int y)
{
    int s = size - 1;
    x--; y--;
    return ({ x, MIN(x, y), y, MIN(s - x, y), s - x, MIN(s - x, s - y), s - y,
        MIN(x, s - y) });
}
 
/*
 * Function name: on_board
 * Description:   Tell us if a position number is valid.
 * Arguments:     x, y - the position
 * Returns:       0 if not on board, else 1
 */
 
public int
on_board(int x, int y)
{
    x--; y--;
    if (x < 0 || y < 0 || x >= size || y >= size)
        return 0;
    return 1;
}
 
/*
 * Function name: alter_board
 * Description:   change one of the board positions to a new string.
 * Arguments:     new - the new string desired. strlen(new) != 1 will
 *                cause problems with the board.
 */
 
public public void
alter_board(string new, int x, int y)
{
    x = position(x, y);
    board = extract(board, 0, x - 1) + new + extract(board, x + 1);
}
 
/*
 * Function name: query_board_size
 * Description:   Tell us how big the board is.
 * Returns:       The square size of the board.
 */
 
public int
query_board_size()
{
    return size;
}
 
/*
 * Function name: query_pieces_placed_inside
 * Description:   tell us how pieces are placed.
 * Returns:       the inside (t_inside) variable as described in
 *                initialize_board
 */
 
public int
query_pieces_placed_inside()
{
    return inside;
}
 
/*
 * Function name: query_board
 * Description:   give us the board string.
 * Returns:       the board string, of course.
 */
 
public string
query_board()
{
    return board;
}
 
/*
 * Function name: set_board
 * Description:   set the board, in case we have to backup some. 
 * Arguments:     str - the board. 
 * Note:          This function is static, and should only be used in cases
 *                where a move must be made to check validity, and moved back
 *                if not valid. Store the string returned by query_board(),
 *                then use it as the arg. Setting it by hand is most likely
 *                going to cause problems with position()
 */
 
static void
set_board(string arg)
{
    board = arg;
}
 
/*
 * Function name: query_board_segment
 * Description:   tell us what x, y looks like (the string)
 * Arguments:     x, y - the position.
 * Returns:       the string of length 1 shown at board position x, y
 */
 
public string
query_board_segment(int x, int y)
{
    x = position(x, y);
    return extract(board, x, x);
}
 
/*
 * Function name: query_long_string
 * Description:   gives us a bigger segment of the board in a straight line.
 * Arguments:     x, y - position; dir - the direction as returned from
 *                distance_from_edge; len - how long the string should be.
 * Returns:       the requested string. Note that x, y is always the first
 *                character of the string.
 */
 
public string
query_long_string(int x, int y, int dir, int len)
{
    string ret = "";
    while(len--)
    {
        if (!on_board(x, y))
            return ret;
        ret += query_board_segment(x, y);
        switch(dir)
        {
            case 7: x--; y++; break;
            case 6: y++; break;
            case 5: x++; y++; break;
            case 4: x++; break;
            case 3: x++; y--; break;
            case 2: y--; break;
            case 1: x--; y--; break;
            case 0: x--; break;
        }
    }
    return ret;
}
 
/*
 * Function name: surrounding_pieces
 * Description:   tell us what pieces surround x, y
 * Arguments:     x, y - the position
 * Returns:       A string of length 8, with each surrounding piece in order
 *                as described by distance_from_edge
 */
 
public string
surrounding_pieces(int x, int y)
{
    string ret = "", tmp;
    int i;
    for (i = 0; i < 8; i++)
    {
        tmp = query_long_string(x, y, i, 2);
        if (strlen(tmp) < 2)
            ret += "#";
        else
            ret += extract(tmp, 1);
    }
    return ret;
}
 
/*
 * Function name: shift
 * Description:   a fairly useless function to move the x or y variable
 *                in a specific direction.
 * Arguments:     old - the old position; x - 1 if x var, 0 if y var;
 *                dir - the direction as described by distance_from_edge
 * Returns:       the new position after shifting.
 */
 
public int
shift(int old, int x, int dir)
{
    if (!x)
    {
        switch(dir)
        {
            case 7: case 6: case 5: return ++old;
            case 0: case 4: return old;
            case 1: case 2: case 3: return --old;
        }
    }
    else
        switch(dir)
        {
            case 7: case 0: case 1: return --old;
            case 2: case 6: return old;
            case 3: case 4: case 5: return ++old;
        }
}
 
/*
 * Function name: end_game
 * Description:   end the game, set the game_over_var, and notify the room.
 */
 
public void
end_game()
{
    environment()->notify_game_winner(players[turn], this_object());
    game_over = turn + 1;
}
 
/*
 * Function name: save_game
 * Description:   saves the game variables for later use.
 * Arguments:     file - the filename.
 * Returns:       1 for success.
 */
 
public int
save_game(string file)
{
    reset_euid();
    if (save_object(file)) return 1; return 0;
}
 
/*
 * Function name: restore_game
 * Description:   retrieve a game
 * Arguments:     file - the filename
 * Returns:       1 for success.
 */
 
public int
restore_game(string file)
{
    reset_euid();
    if (restore_object(file)) return 1; return 0;
}
 
/*
 * Function name: create_game
 * Description:   creation function, used by create_object
 */
 
public void
create_game() {}
 
/*
 * Function name: create_object
 * Description:   make sure we have some variables for everything, then
 *                call create_game
 */
 
public nomask void
create_object()
{
    players = allocate(2);
    initialize_board(1, 0);
    messa = "";
    set_move_type(0);
    set_game_server(DEFAULT_SERVER);
    create_game();
}
 
/*
 * Function name: vb_play
 * Description:   let us try to make a move.
 * Arguments:     arg - what we typed after the verb.
 * Returns:       1 if the move was good, 0 if not.
 * Note:          This function should not normally need to be modified.
 *                It calls the following functions in this object:
 *                valid_place_piece(x, y, (a, b)) - return a fail string
 *                if the move is not valid. (a, b) is used only in
 *                board with move_type == 1 (see set_move_type);
 *                do_place_piece(x, y, (a, b)) - having said the move is 
 *                valid, we proceed to make it.
 *                notify_game_moved(turn, ({ x, y, (a, b) })) is called in
 *                the environment, in case we have a special game room.
 *                The vb_play function checks for the following things:
 *                 our turn to play (and we are playing!)
 *                 valid argument, and all positions on board
 *                 game is not over
 *                 two players, though it is not necessary for both to
 *                  be present.
 */
 
public int
vb_play(string arg)
{
    mixed fail;
    int a1, a2, a3, a4;
    if (game_over)
    {
        notify_fail("The game is over!\n");
        return 0;
    }
    if (whose_turn() != query_which_player())
    {
        notify_fail("It is not your turn to move.\n");
        return 0;
    }
    if (!players[0] || !players[1])
    {
        notify_fail("You must have two players interested in the game " +
            "to play.\n");
        return 0;
    }
    fail = this_object()->convert_string(arg);
    a1 = fail[0];
    a2 = fail[1];
    a3 = fail[2];
    a4 = fail[3];
    fail = 0;
    if (!on_board(a1, a2))
        fail = 1;
    if (query_move_type())
        if (!on_board(a3, a4))
            fail = 1;
    if (fail)
    {
        notify_fail("It isn't quite clear what move you intend to make.\n");
        return 0;
    }
    if (move_type)
        fail = this_object()->valid_place_piece(a1, a2, a3, a4);
    else
        fail = this_object()->valid_place_piece(a1, a2);
    if (stringp(fail) && strlen(fail))
    {
        notify_fail(fail);
        return 0;
    }
    if (move_type)
        this_object()->do_place_piece(a1, a2, a3, a4);
    else
        this_object()->do_place_piece(a1, a2);
    turn = (turn ? 0 : 1);
    move_number++;
    if (!move_type)
        environment()->notify_game_moved(turn, ({ a1, a2 }));
    else
        environment()->notify_game_moved(turn, ({ a1, a2, a3, a4 }));
    return 1;
}
 
/* 
 * Function name: vb_adjourn
 * Description:   save the game if only one person is playing and wishes
 *                to do so.
 * Arguments:     arg - should be ""
 * Returns:       1 if success, 0 if failed.
 * Note:          this function uses the game_server file to determine
 *                what filename it should save in.
 */
 
public int
vb_adjourn(string arg)
{
    if (strlen(arg))
    {
        notify_fail("Adjourn what?\n");
        return 0;
    }
    if (players_here() == 3)
    {
        notify_fail("One of the players must leave the game before it " +
            "can be adjourned. (What if the other wants to sit and stare " +
            "at it for a while?)\n");
        return 0;
    }
    if (query_which_player() == -1)
    {
        notify_fail("Only someone playing the game can adjourn it.\n");
        return 0;
    }
    write("You adjourn the game until later.\n");
    save_game(game_server->add_game(players, game_name, turn));
    initialize_board(1, 0);
    return 1;
}
 
/*
 * Function name: query_board_extras
 * Description:   Show all the extraneous info the board needs.
 * Returns:       The extra info, to be used by vb_view
 */
 
public string
query_board_extras()
{
    string str;
    if (whose_turn() == query_which_player())
        str = "Your";
    else if (query_player(whose_turn()))
        str = capitalize(query_player(whose_turn())) + "'s";
    else
            str = "Nobody's";
    return str + " turn.\n";
}
 
/*
 * Function name: vb_view
 * Description:   give us a nice printout of the board and extra info.
 * Arguments:     arg - should be "";
 * Returns:       1 if success.
 */
 
public int
vb_view(string arg)
{
    if (strlen(arg))
    {
        notify_fail("View what?\n");
        return 0;
    }
    write(query_board() + query_board_extras());
    return 1;
}
 
/*
 * Function name: vb_concede
 * Description:   admit defeat
 * Arguments:     arg - should be ""
 * Returns:       1 if success
 */
 
public int
vb_concede(string arg)
{
    if (strlen(arg))
    {
        notify_fail("Concede what?\n");
        return 0;
    }
    if (whose_turn() == query_which_player())
        turn = (turn ? 0 : 1);
    write("You concede the game.\n");
    nm(" has conceeded the game.\n");
    end_game();
    return 1;
}
 
/*
 * Function name: enter_game
 * Description:   put a new player in the game.
 * Arguments:     player - the name or object of the player; which - player
 *                number desired.
 * Returns:       1 if added.
 * Note:          This function performs oddly if player != this_player()
 */
 
public int
enter_game(mixed player, int which)
{
    string fail;
    if (objectp(player))
        fail = set_player(player->query_real_name(), which);
    else
        fail = set_player(player, which);
    if (strlen(fail))
    {
        notify_fail(fail);
        return 0;
    }
    write("You begin to play the game.\n");
    say(QCTNAME(this_player()) + " begins to play the game.\n");
    return 1;
}
 
/*
 * Function name: init
 * Description:   give us the game: command.
 */
 
public void
init()
{
    ::init();
    add_action("do_stuff", "game:");
}
 
/*
 * Function name: do_stuff
 * Description:   perform any game related action.
 * Arguments:     arg - string of form <vb> <extraarg> where extraarg may
 *                be ""
 * Returns:       1 if success.
 * Note:          It is possible to make any game: <command> possible by
 *                defining the function vb_<command>(string arg) as a normal
 *                add_actioned() function.
 */
 
public int
do_stuff(string arg)
{
    string *stuff, vb;
    if (query_which_player() == -1)
    {
        notify_fail("But you are not playing!\n");
        return 0;
    }
    if (!arg || !strlen(arg))
    {
        notify_fail("Game: what?\n");
        return 0;
    }
    stuff = explode(arg, " ");
    vb = stuff[0];
    if (sizeof(stuff) > 1)
        arg = implode(exclude_array(stuff, 0, 0), " ");
    else
        arg = "";
    notify_fail("Game: what?");
    return call_other(this_object(), "vb_" + vb, arg);
}
 
/*
 * Function name: set_game_name
 * Description:   set the game name for use by gameservers
 * Arguments:     arg - the name of the game.
 */
 
public void
set_game_name(string arg)
{
    game_name = capitalize(arg);
}
 
/*
 * Function name: query_game_name
 * Description:   tell us what the name of the game is.
 * Returns:       the game name
 */
 
public string
query_game_name()
{
    return game_name;
}
 
/*
 * Function name: set_stlong
 * Description:   a utility function if you intend to modify the top portion
 *                of the board (I use it for GO.)
 * Arguments:     len - the length of the string before the actual board.
 */
 
public void
set_stlong(int len)
{
    stlong = len;
}
 
/*
 * Function name: query_stlong
 * Description:   gives us the length of the header
 * Returns:       the strlen
 */
 
public int
query_stlong()
{
    return stlong;
}
