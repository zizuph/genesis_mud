/* object: chess.c
 * desc:   A chess game for two players to play... have fun with it!
 * code:   Fysix@Genesis, January 1997
 */

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <cmdparse.h>

inherit "/std/object";

// Macros
#define TP this_player()
#define TO this_object()
#define ENV(x) environment(x)
#define HE(x) (x)->query_pronoun()
#define HIS(x) (x)->query_possessive()
#define CHECK_PLAYING(x) notify_fail("You are not one of the players.\n");\
  if (member_array((x)->query_real_name(), player) < 0) return 0;

// Number of pieces
#define N      6
#define BLACK  0
#define WHITE  1
// Defines for different kinds of moves
#define M_ILLEGAL      0
#define M_NORMAL       1
#define M_CASTLE_LEFT  2
#define M_CASTLE_RIGHT 3
#define M_ENPASSANT    4

#define W(x)   (WHITE * N + (x)) 
#define B(x)   (BLACK * N + (x))

#define KING   6
#define QUEEN  5
#define ROOK   4
#define KNIGHT 3
#define BISHOP 2 
#define PAWN   1

static string *player = ({ }), darer, dared;
static mixed  p;
static int    active,  // 0 is black's turn, (player[0])
              finished,
              *can_castle_left, *can_castle_right,
              // What piece does player want for promo?
              *promo_piece,
              *king_r, *king_c, // king's row and column
              *check, // player standing check?
              // Info about the last move
              last_r1, last_c1, last_r2, last_c2,
              // time out after max_time since last move, 
              // game can be reset then, default 5 minutes
              max_time = 300, last_time; 
static string *symbol = ({ "   ", " p ", " B ", " N ", " R ", " Q ", " K ",
                                  "#p ", "#B ", "#N ", "#R ", "#Q ", "#K "}),
              *piece_name = ({ "nothing", "pawn", "bishop", "knight",
                               "rook", "queen", "king" });

// Return the player object
object
player_o(int color)
{  return present(find_player(player[color]), environment(this_object())); }

void
init_board()
{
   player = ({ });
   active = WHITE;
   finished = 0;
   can_castle_left = ({1, 1});
   can_castle_right = ({1, 1});
   promo_piece = ({ QUEEN, QUEEN });
   last_r1 = -1; last_c1 = -1; last_r2 = -1; last_c2 = -1;
   king_r = ({7, 0});
   king_c = ({4, 4});
   check = ({0, 0});
   last_time = time();
   
   p = ({
    ({ W(ROOK), W(KNIGHT), W(BISHOP), W(QUEEN), W(KING), 
       W(BISHOP), W(KNIGHT), W(ROOK) }),
    ({ W(PAWN), W(PAWN), W(PAWN), W(PAWN), W(PAWN), W(PAWN), 
       W(PAWN), W(PAWN) }),
    ({0, 0, 0, 0, 0, 0, 0, 0}),
    ({0, 0, 0, 0, 0, 0, 0, 0}),
    ({0, 0, 0, 0, 0, 0, 0, 0}),
    ({0, 0, 0, 0, 0, 0, 0, 0}),
    ({ B(PAWN), B(PAWN), B(PAWN), B(PAWN), B(PAWN), B(PAWN), 
       B(PAWN), B(PAWN) }),
    ({ B(ROOK), B(KNIGHT), B(BISHOP), B(QUEEN), B(KING), 
       B(BISHOP), B(KNIGHT), B(ROOK) })
    });
}

void
create_object()
{
   set_name("game");
   set_short("game of chess");
   set_pshort("games of chess");
   set_long("This is a game of chess, you can get " +
    "some help with 'help chess'. " +
    "@@active_desc@@\n" +
    "@@exa_board@@" +
    "");
    
   add_prop(OBJ_M_NO_GET, "Hands off!\n");
   add_prop(OBJ_I_WEIGHT, 3000);
   add_prop(OBJ_I_VOLUME, 2500);
   
   setuid();
   seteuid(getuid());
   init_board();
}

// Are there playing people?
string
active_desc()
{
   if (!sizeof(player)) return "Nobody is playing right now. ";
   if (time() - last_time > max_time) return "The pieces are covered " +
    "by a thick layer of dust. ";
   return "";
}

// Draw the chess board
string
board_desc(int color)
{
int    i, j, inc;
string s = "", top_color, bottom_color, *c = allocate(2);

   // Put some character behind the active color
   c[BLACK] = "black" + (active == BLACK ? "*" : "");
   c[WHITE] = "white" + (active == WHITE ? "*" : "");

   // Which color is at the bottom of the screen?
   top_color = (color == WHITE ? c[BLACK]: c[WHITE]);
   bottom_color = (color == WHITE ? c[WHITE]: c[BLACK]);
   
   inc = (color == WHITE ? -1 : 1);

   for (i = 7 * color; i >= 0 && i < 8; i += inc)
   {
      s += "  +---+---+---+---+---+---+---+---+  ";
      if (i == 7 * color) s += top_color;
      s += sprintf("\n%d ", i + 1);
      for (j = 7 * (1 - color); j >= 0 && j < 8; j -= inc)
         s += "|" + (p[i][j] ? symbol[p[i][j]] : ((i+j)%2 ? " . " : "   "));
      s += "|\n";
   }
   s += "  +---+---+---+---+---+---+---+---+  " + bottom_color;
   if (color == WHITE)
      s += "\n    A   B   C   D   E   F   G   H\n";
   else
      s += "\n    H   G   F   E   D   C   B   A\n";
   
   return s;
}

// The player examines the board, if the player is the one
// who plays black, turn the board around for him
string
exa_board()
{
   if (!sizeof(player))
      return board_desc(WHITE);
   if (TP->query_real_name() == player[BLACK])
      return board_desc(BLACK);
   return board_desc(WHITE);
}

// Give a message to one of the two players, indicated with 'color'
void
tell_player(string s, int color)
{
object o;

   if (!(o = player_o(color))) return;
   o->catch_msg(s);
}

// Give the other people (who are not playing) a message
void
tell_others(string s)
{
object *o = ({ });

   if (sizeof(player)) o = ({player_o(BLACK), player_o(WHITE)});
   o -= ({ 0 });
   tell_room(ENV(TO), s, o);
}

// Returns 0 (black) for pieces 1-6 and 1 for pieces 7-12 (white)
int
query_color(int piece)
{  return (!piece ? 0 : (piece - 1) / N); }

// Returns the sort of a piece (KING, QUEEN etc), stripped of color
int
query_sort(int piece)
{  return (!piece ? 0 : (piece - 1) % N + 1); }

/* Function: location_safe
 * Desc:     Is a certain location safe?
 * Args:     int r, c = row and column
 *           int color = safe from which color? (i.e. color is the
 *                       enemy's color)
 * Returns:  1 - if safe, 0 - if not safe
 */
int
location_safe(int r, int c, int color)
{
int i, j;

   // scan horizontal line, check for rook, queen and king
   for (i = c - 1; i >= 0; i--)
      if (p[r][i]) {
         if (query_color(p[r][i]) != color) break;
         if (query_sort(p[r][i]) == ROOK || query_sort(p[r][i]) == QUEEN)
            return 0;
         if (i == c - 1 && query_sort(p[r][i]) == KING) return 0;
         break;
      }
   
   for (i = c + 1; i < 8; i++)
      if (p[r][i]) {
         if (query_color(p[r][i]) != color) break;
         if (query_sort(p[r][i]) == ROOK || query_sort(p[r][i]) == QUEEN)
            return 0;
         if (i == c + 1 && query_sort(p[r][i]) == KING) return 0;
         break;
      }
   
   // scan vertical line, check for rook, queen and king
   for (i = r - 1; i >= 0; i--)
      if (p[i][c]) {
         if (query_color(p[i][c]) != color) break;
         if (query_sort(p[i][c]) == ROOK || query_sort(p[i][c]) == QUEEN)
            return 0;
         if (i == r - 1 && query_sort(p[i][c]) == KING) return 0;
         break;
      }
   
   for (i = r + 1; i < 8; i++)
      if (p[i][c]) {
         if (query_color(p[i][c]) != color) break;
         if (query_sort(p[i][c]) == ROOK || query_sort(p[i][c]) == QUEEN)
            return 0;
         if (i == r + 1 && query_sort(p[i][c]) == KING) return 0;
         break;
      }
   
   // scan first diagonal, check for bishop, queen and king
   for (i = r - 1, j = c - 1; i >= 0 && j >= 0; i--, j--)
      if (p[i][j]) {
         if (query_color(p[i][j]) != color) break;
         if (query_sort(p[i][j]) == BISHOP || query_sort(p[i][j]) == QUEEN)
            return 0;
         if (i == r - 1 && query_sort(p[i][j]) == KING) return 0;
         break;
      }
   
   for (i = r + 1, j = c + 1; i < 8 && j < 8; i++, j++)
      if (p[i][j]) {
         if (query_color(p[i][j]) != color) break;
         if (query_sort(p[i][j]) == BISHOP || query_sort(p[i][j]) == QUEEN)
            return 0;
         if (i == r + 1 && query_sort(p[i][j]) == KING) return 0;
         break;
      }
   
   // scan second diagonal, check for bishop, queen and king
   for (i = r - 1, j = c + 1; i >= 0 && j < 8; i--, j++)
      if (p[i][j]) {
         if (query_color(p[i][j]) != color) break;
         if (query_sort(p[i][j]) == BISHOP || query_sort(p[i][j]) == QUEEN)
            return 0;
         if (i == r - 1 && query_sort(p[i][j]) == KING) return 0;
         break;
      }
   
   for (i = r + 1, j = c - 1; i < 8 && j >= 0; i++, j--)
      if (p[i][j]) {
         if (query_color(p[i][j]) != color) break;
         if (query_sort(p[i][j]) == BISHOP || query_sort(p[i][j]) == QUEEN)
            return 0;
         if (i == r + 1 && query_sort(p[i][j]) == KING) return 0;
         break;
      }

   // check for knights, check eight positions, a real pain in the ass
   if ((i = r - 2) >= 0) {
      if ((j = c - 1) >= 0) 
         if (query_sort(p[i][j]) == KNIGHT && query_color(p[i][j]) == color)
            return 0;
      if ((j = c + 1) < 8) 
         if (query_sort(p[i][j]) == KNIGHT && query_color(p[i][j]) == color)
            return 0;
   }
   if ((i = r - 1) >= 0) {
      if ((j = c - 2) >= 0)
         if (query_sort(p[i][j]) == KNIGHT && query_color(p[i][j]) == color)
            return 0;
      if ((j = c + 2) < 8)
         if (query_sort(p[i][j]) == KNIGHT && query_color(p[i][j]) == color)
            return 0;
   }
   if ((i = r + 2) < 8) {
      if ((j = c - 1) >= 0) 
         if (query_sort(p[i][j]) == KNIGHT && query_color(p[i][j]) == color)
            return 0;
      if ((j = c + 1) < 8) 
         if (query_sort(p[i][j]) == KNIGHT && query_color(p[i][j]) == color)
            return 0;
   }
   if ((i = r + 1) < 8) {
      if ((j = c - 2) >= 0)
         if (query_sort(p[i][j]) == KNIGHT && query_color(p[i][j]) == color)
            return 0;
      if ((j = c + 2) < 8)
         if (query_sort(p[i][j]) == KNIGHT && query_color(p[i][j]) == color)
            return 0;
   }
      
   // check for nasty pawns
   if (color == BLACK)
   {
      // can be attacked only by black pawns under row no 6 (on scale 0-7).
      if (r < 6)
      {
         if (c > 0 && p[r + 1][c - 1] == B(PAWN)) return 0;
         if (c < 7 && p[r + 1][c + 1] == B(PAWN)) return 0;
      }
   }
   else
   {
      // can be attacked only by white pawns above row no 1 (on scale 0-7).
      if (r > 1)
      {
         if (c > 0 && p[r - 1][c - 1] == W(PAWN)) return 0;
         if (c < 7 && p[r - 1][c + 1] == W(PAWN)) return 0;
      }
   }

   return 1;
}

/* function: move_ok
 * desc:     Can the piece be moved like we want it?
 *           It doesn't check if it leaves the player 'check' in
 *           the new position. A full check on 'check' is made on
 *           castling though.
 * args:     int piece, row1, column1, row2, column2
 * returns:  See the defines M_ above:
 *           0 - illegal move, 1 - normal move
 *           2 - castle, 3 - pawn taking pawn en passant
 */
int
move_ok(int piece, int r1, int c1, int r2, int c2)
{
int color, sort, color2, sort2, i, j, r_inc, c_inc;

   color = query_color(piece);
   sort = query_sort(piece);
   color2 = query_color(p[r2][c2]);
   sort2 = query_sort(p[r2][c2]);
   
   // Calculate row and column increments
   r_inc = (r2 > r1 ? 1 : -1);
   if (r2 == r1) r_inc = 0;
   c_inc = (c2 > c1 ? 1 : -1);
   if (c2 == c1) c_inc = 0;
   // This move is illegal for every piece
   if (r1 == r2 && c1 == c2) return M_ILLEGAL;

   notify_fail("You moved the piece, but it moves back magically!\n");   
   switch (sort)
   {
     case PAWN :
      if (!sort2) // If not taking a piece directly
      {
         if (color == WHITE)
         {
            // First pawn move may be two fields at once, on the same column
            // And no piece may be on the third row (index 2)
            if (r1 == 1 && r2 - r1 == 2 && c1 == c2 && !p[3][c1])
               return M_NORMAL;

            if (r2 - r1 != 1) return M_ILLEGAL;

            // Check for taking a piece 'en passant', use info
            // on last move
            if (ABS(c2 - c1) == 1 && p[r1][c2] == B(PAWN) &&
             last_r2 == r1 && last_c2 == c2 && last_r2 - last_r1 == -2)
               return M_ENPASSANT;
            
            // the usual move
            if (c1 != c2) return M_ILLEGAL; // pawn has to stay on one line
         }
         else
         {
            // First pawn move may be two fields at once
            // And no piece may be on the sixth row (index 5)
            if (r1 == 6 && r2 - r1 == -2 && c1 == c2 && !p[4][c1])
               return M_NORMAL;

            if (r2 - r1 != -1) return M_ILLEGAL;

            // Check for taking a piece 'en passant', use info
            // on last move
            if (ABS(c2 - c1) == 1 && p[r1][c2] == W(PAWN) &&
             last_r2 == r1 && last_c2 == c2 && last_r2 - last_r1 == 2)
               return M_ENPASSANT;

            // the usual move
            if (c1 != c2) return M_ILLEGAL; // pawn has to stay on one line
         }
      }
      else // trying to take a piece
      {
         if (color2 == color) return M_ILLEGAL; // Can't take your own piece
         
         // Check on moves
         if (color == WHITE)
         {
            if (r2 - r1 != 1) return M_ILLEGAL;
         }
         else
            if (r2 - r1 != -1) return M_ILLEGAL;
         if (ABS(c2 - c1) != 1) return M_ILLEGAL;
      }
      return M_NORMAL;
      break;

     case BISHOP :
      if (ABS(r2 - r1) != ABS(c2 - c1)) return M_ILLEGAL; // path must be diagonal

      // Check for pieces on its path
      for (i = r1 + r_inc, j = c1 + c_inc; 
            i != r2 || j != c2; i += r_inc, j += c_inc)
         if (p[i][j]) return M_ILLEGAL;
      
      if (sort2)  // Taking a piece? (otherwise just execute the move)
         if (color2 == color) return M_ILLEGAL; // Can't take your own piece
      return M_NORMAL;
      break;

     case KNIGHT :
      r_inc = ABS(r2 - r1);
      c_inc = ABS(c2 - c1);
      if (!(r_inc == 1 && c_inc == 2) && !(r_inc == 2 && c_inc == 1))
         return M_ILLEGAL; // Knights have funny moves :)
         
      if (sort2)  // Taking a piece?
         if (color2 == color) return M_ILLEGAL; // Can't take your own piece
      return M_NORMAL;
      break;

     case ROOK :
      // Rook moves on horizontal/vertical lines
      if (r1 != r2 && c1 != c2) return M_ILLEGAL;
      
      // Check for pieces on its path
      for (i = r1 + r_inc, j = c1 + c_inc; 
            i != r2 || j != c2; i += r_inc, j += c_inc)
         if (p[i][j]) return M_ILLEGAL;
      
      if (sort2) // Taking a piece?
         if (color2 == color) return M_ILLEGAL; // Can't take own color
      return M_NORMAL;
      break;

     case QUEEN :
      // Queen can make lots of moves
      if (r1 != r2 && c1 != c2 && ABS(r2 - r1) != ABS(c2 - c1))
         return M_ILLEGAL;
      
      // Check for pieces on its path
      for (i = r1 + r_inc, j = c1 + c_inc; 
            i != r2 || j != c2; i += r_inc, j += c_inc)
         if (p[i][j]) return M_ILLEGAL;
         
      if (sort2) // Taking a piece?
         if (color2 == color) return M_ILLEGAL; // Can't take your own color
      return M_NORMAL;
      break;

     case KING :
      if (ABS(c2 - c1) >= 2 && r1 == r2) // Trying to castle?
      {
         if (c2 - c1 == 2 && can_castle_right[color])
         {
            // Check if path is free for castle
            notify_fail("You can't castle when there are pieces between " +
             "the king and the rook.\n");
            if (p[r1][5] || p[r1][6]) return M_ILLEGAL;

            // Check if all the fields are safe            
            notify_fail("One of the crucial fields is under attack. " +
             "You can't castle now!\n");
            if (!location_safe(r1, 4, 1 - color) ||
                !location_safe(r1, 5, 1 - color) ||
                !location_safe(r1, 6, 1 - color)) return M_ILLEGAL;

            return M_CASTLE_RIGHT;
         }

         if (c2 - c1 == -2 && can_castle_left[color])
         {
            // Check if path is free for castle
            notify_fail("You can't castle when there are pieces between " +
             "the king and the rook.\n");
            if (p[r1][1] || p[r1][2] || p[r1][3]) return M_ILLEGAL;

            // Check if all the fields are safe
            notify_fail("One of the crucial fields is under attack. " +
             "You can't castle now!\n");
            if (!location_safe(r1, 1, 1 - color) ||
                !location_safe(r1, 2, 1 - color) ||
                !location_safe(r1, 3, 1 - color) ||
                !location_safe(r1, 4, 1 - color)) return M_ILLEGAL;

            return M_CASTLE_LEFT;
         }
      }
      else // normal move otherwise
      {
         // The king can move only one square
         r_inc = ABS(r2 - r1);
         c_inc = ABS(c2 - c1);
         if (r_inc > 1 || c_inc > 1) return M_ILLEGAL;
      
         if (sort2) // Taking a piece?
            if (color2 == color) return M_ILLEGAL;
      }
      return M_NORMAL;
      break;
   }
   return M_ILLEGAL;
}

// Is the king ok after move?
int
king_ok(int color)
{
   if (location_safe(king_r[color], king_c[color], 1 - color))
      return 1;
   notify_fail("Illegal move, watch your king!\n");
   return 0;
}

// Game is finished!
void
game_finished(int winner)
{
   tell_others(QCTNAME(player_o(winner)) + " won the game of chess!\n");
   tell_player("You won the game of chess!\n", winner);
   tell_player("You lost the game of chess!\n", 1 - winner);
   finished = 1;
}

/* Function: check_castle
 * Desc:     check if the moved piece lifts the possible for castle
 * Args:     int r, c - the position of the piece that is going to be
 *             moved / or taken by the enemy
 *           int piece - the piece concerned
 */
void
check_castle(int r, int c, int piece)
{
int color = query_color(piece);

   if (query_sort(piece) == ROOK)
   {
      if (color == BLACK && r == 7)
      {
         if (c == 0) can_castle_left[color] = 0;
         if (c == 7) can_castle_right[color] = 0;
      }
      if (color == WHITE && r == 0)
      {
         if (c == 0) can_castle_left[color] = 0;
         if (c == 7) can_castle_right[color] = 0;
      }
   }

   if (query_sort(piece) == KING)
   {
      can_castle_left[color] = 0;
      can_castle_right[color] = 0;
   }
}

// try to move a piece
int
do_move(string s)
{
int    r1, c1, r2, c2, piece, taken, move_sort; // rows and colums
int    check_new; // player will stand check after move?

   notify_fail("Sorry, but the game is already finished!\n");
   if (finished) return 0;

   // Format s into something like "b1c3"
   notify_fail("Move <from position>, <to position>\n");
   if (!s) return 0;
   s = implode(explode(s, " "), "");
   s = implode(explode(s, ","), "");
   if (strlen(s) != 4) return 0;

   notify_fail("Nobody is playing now!\n");
   if (!sizeof(player)) return 0;

   notify_fail("It's not your turn now!\n");
   if (TP->query_real_name() != player[active]) return 0;
   
   // read rows and colums for moving
   s = capitalize(s[0..1]) + capitalize(s[2..3]);
   c1 = s[0] - 65;
   r1 = s[1] - "1"[0]; 
   c2 = s[2] - 65;
   r2 = s[3] - "1"[0]; 
   
   // Make boundary checks on coordinates
   notify_fail("Invalid move!\n");
   if (r1 < 0 || r2 < 0 || c1 < 0 || c2 < 0) return 0;
   if (r1 > 7 || r2 > 7 || c1 > 7 || c2 > 7) return 0;
   
   // Try to move the piece, make validity checks on the move
   piece = p[r1][c1];
   taken = p[r2][c2];
   notify_fail("There is no piece on that field.\n");
   if (!piece) return 0;
   notify_fail("Move something of your own color.\n");
   if (active != query_color(piece)) return 0;
   
   if (!(move_sort = move_ok(piece, r1, c1, r2, c2))) return 0;
   
   // The move is executed;
   // after the move, a check for 'check' is done, if so,
   // the move is taken back.

   p[r2][c2] = piece;
   p[r1][c1] = 0;
   // Is it a castle move? If so, move an additional rook
   if (move_sort == M_CASTLE_RIGHT)
   {
       p[r1][5] = p[r1][7];
       p[r1][7] = 0;
   }
   if (move_sort == M_CASTLE_LEFT)
   {
       p[r1][3] = p[r1][0];
       p[r1][0] = 0;
   }
   // Is a pawn taking a pawn 'en passant'? If so, remove the other pawn
   if (move_sort == M_ENPASSANT)
   {
      taken = p[r1][c2];
      p[r1][c2] = 0;
   }
   // If king was moved, update old positions
   if (query_sort(piece) == KING)
   {  king_r[active] = r2; king_c[active] = c2; }
   
   // Check if the player's king will be safe after this move
   // If check now, and not check before, move is illegal.
   // Otherwise, player will just loose... don't do anything though
   if (check_new = !king_ok(active))
      if (!check[active])
      {
         // take the move back, castles are pre-checked fully, so
         // castles never have to be taken back.
         p[r1][c1] = piece;
         p[r2][c2] = taken;
         // If a pawn was taken 'en passant', put it back
         if (move_sort == M_ENPASSANT)
            p[r1][c2] = taken;
         // If king was moved, update old positions
         if (query_sort(piece) == KING)
         {  king_r[active] = r1; king_c[active] = c1; }
         return 0;
      }
   
   // --- player didn't put himself in check, so all is okay now -----

   check[active] = check_new;

   // Check if moving the piece lifts the future possibility for
   // castling. Check both on moves of rook / king, and deletion
   // of the rook of the enemy
   check_castle(r1, c1, piece);
   if (query_sort(taken) == ROOK) check_castle(r2, c2, taken);
   
   // Pawn has reached the other side? turn it into a 'promo_piece'
   if (query_sort(piece) == PAWN)
   {
      if (active == BLACK && r2 == 0)
         p[r2][c2] = B(promo_piece[active]);
      if (active == WHITE && r2 == 7)
         p[r2][c2] = W(promo_piece[active]);
   }

   active = 1 - active; // switch active player here! be careful below
   last_r1 = r1; last_c1 = c1; last_r2 = r2; last_c2 = c2;

   // Now the peace has been moved, check for 'check' of the opponent
   check[active] = !king_ok(active);
   
   // --- Give a bunch of messages below ------
   tell_player(board_desc(active), active);
   write(board_desc(1 - active));

   if (taken)
   {
      write("You moved a piece: " + s[0..1] + "x" + s[2..3] + " and took a " +
       piece_name[query_sort(taken)] + " from your opponent.\n"); 
      tell_others(QCTNAME(TP) + " moved a piece " +
       s[0..1] + "x" + s[2..3] + " and took the opponent's " +
       piece_name[query_sort(taken)] + ".\n");
      tell_player("Your opponent moved a piece " +
       s[0..1] + "x" + s[2..3]+ " and took your " + 
       piece_name[query_sort(taken)] + "! ", active);
   }
   else
   {
      write("You moved a piece: " + s[0..1] + "-" + s[2..3] + ".\n"); 
      tell_others(QCTNAME(TP) + " moved a piece " +
       s[0..1] + "-" + s[2..3] + ".\n");
      tell_player("Your opponent moved a piece " +
      s[0..1] + "-" + s[2..3] + ". ", active);
   }
   
   if (check[active])
   {
      write("You have checked your opponent.\n");
      tell_others(QCTNAME(TP) + " has checked " +
       QCTNAME(player_o(active)) + ".!!!\n");
      tell_player(QCTNAME(TP) + " has checked you!!! ", active);
   }
       
   // King is taken? If so, game is finished ofcourse ;)
   if (query_sort(taken) == KING)
      game_finished(1 - active);
   else
      tell_player("It's your turn now.\n", active);

   last_time = time();
   return 1;
}

// Dare a player
int
do_challenge(string s)
{
object o, *l;

   notify_fail("Dare whom?\n");
   if (!s) return 0;
   l = FIND_STR_IN_ARR(s, FILTER_LIVE(all_inventory(ENV(TO))));

   notify_fail("There is nobody here to play chess with.\n");
   if (sizeof(l) < 1) return 0;
   notify_fail("You can only challenge one player at a time.\n");
   if (sizeof(l) != 1) return 0;
   
   o = l[0];
   notify_fail("You can't play chess with yourself.\n");
   if (o == TP) return 0;
   dared = o->query_real_name();
   
   notify_fail("People are already playing a game of chess.\n");
   if (sizeof(player)) return 0;
   
   darer = TP->query_real_name();
   o->catch_msg(QCTNAME(TP) + " challenges you to a game of chess, " +
    "accept if you feel up to a challenge.\n");
   write("You challenge " + s + " for a game of chess.\n");
   tell_room(ENV(TO), QCTNAME(TP) + " challenges " + QTNAME(o) +
    " for a game of chess.\n", ({TP, o}) );
   return 1;
}

int
do_accept(string s)
{
object o;

   notify_fail("You have not been challenged to a game of chess.\n");
   if (TP->query_real_name() != dared) return 0;
   
   write("You accept the challenge!\n");
   say(QCTNAME(TP) + " accepts the duel.\n");

   // Randomize who plays with white
   if (random(2))
      player = ({ darer, dared });
   else
      player = ({ dared, darer });

   tell_others(QCTNAME(player_o(BLACK)) + " plays with black, " +
    QTNAME(player_o(WHITE)) + " plays with white.\n");
   tell_player("You play with black.\n", BLACK);
   tell_player("You play with white.\n", WHITE);
   return 1;
}

/* Only one of the players can reset the game, unless the
 * game has timed out
 */
int
do_reset(string s)
{
   if (time() - last_time <= max_time) CHECK_PLAYING(TP);
   
   init_board();
   write("You turn over the board to see what is written on the other side.\n");
   say(QCTNAME(TP) + " turns over the board to see what is " +
    "written on the other side.\n");
   return 1;
}

// This player resigns the game, and has lost!
int
do_resign(string s)
{
int    i;

   CHECK_PLAYING(TP);
   i = member_array(TP->query_real_name(), player);
   write("You resigned the game of chess!\n");
   tell_player("You won the game of chess!\n", 1 - i);
   tell_others(QCTNAME(TP) + " resigned the game of chess.\n");
   finished = 1;
   return 1;
}

// Choose a piece for a pawn that reached the other side
int
do_choose(string s)
{
int i, a;

   CHECK_PLAYING(TP);
   notify_fail("You can choose from queen, rook, bishop, " +
    "or knight for promotion.\n");
   if (!s) return 0;
   if ((i = member_array(s, piece_name)) < 0) return 0;
   
   notify_fail("You can't choose that!\n");
   if (i == PAWN || i == KING || i == 0) return 0;
   
   write("You choose a " + piece_name[i] + " as your promotion piece.\n");
   say(QCTNAME(TP) + " chooses a " + piece_name[i] + " as " +
    HIS(TP) + " promotion piece.\n");

   a = member_array(TP->query_real_name(), player);
   promo_piece[a] = i;
   return 1;
}

int
do_help(string s)
{
   if (s != "chess") return 0;
   write(
    "Help on chess game, commands:\n" +
    "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" +
    "* challenge <player>, accept\n" +
    "* play/move <old position>,<new position> (e.g. play b1,c3)\n" +
    "  also allowed: play b1 c3, play b1c3\n" +
    "* reset (reset the game)\n" +
    "* resign (give up the game)\n" +
    "* choose (a promotion piece, the queen by default) \n\n" +
    "Emotes:\n" +
    "~~~~~~~\n" +
    "cfist, cfoolish, cgood, cknock, crepent \n\n" +
    "The abbreviations:\n" +
    "~~~~~~~~~~~~~~~~~~\n" +
    "K - King, Q - Queen, R - Rook, B - Bishop, N - kNight, P - Pawn\n\n" +
    "Note: the game does not check for 'mate'.\n" +
    "If no move is done for a few minutes, the game can be reset " +
    "by people, other than who are playing the game.\n\n" +
    "");
   return 1;
}

// --- Some cool emotes, ideas by Morrigan@Genesis -----------------------

int
do_fist(string s)
{
   CHECK_PLAYING(TP);
   write("You wildly bang your fist on the chess board in furious anger. " +
    "The pieces do not move a single bit though.\n");
   say(QCTNAME(TP) + " wildly bangs " + HIS(TP) + 
    " fist on the chess board in furious anger. " +
    "The pieces do not move a single bit though.\n");
   return 1;
}

int
do_foolish(string s)
{
   CHECK_PLAYING(TP);
   write("You shake your head in disappointentment as your opponent " +
    "makes a foolish move.\n");
   say(QCTNAME(TP) + " shakes " + HIS(TP) + " head in disappointment as " +
    HIS(TP) + " opponent makes a foolish move.\n");
   return 1;
}

int
do_good(string s)
{
   CHECK_PLAYING(TP);
   write("D A M N!!! I'm good!\n");
   say(QCTNAME(TP) + " loudly exclaims: \"D A M N!!! I'm good!\" while " +
    "making strange gestures with " + HIS(TP) + " hips and arms.\n");
   return 1;
}

int
do_knock(string s)
{
   CHECK_PLAYING(TP);
   write("You try to accidently slip and knock over the pieces " +
    "but they all somehow magically fall into the right places.\n");
   say(QCTNAME(TP) + " tries to accidently slip and knock over the pieces " +
    "but they all somehow magically fall into the right places.\n");
   return 1;
}

int
do_repent(string s)
{
   CHECK_PLAYING(TP);
   write("You shout while shaking your fist wildly in the air: " +
    "REPENT!... and thou shall be saved!\n");
   say(QCTNAME(TP) + " shouts while shaking " + HIS(TP) +
    " fist wildly in the air: " +
    "REPENT!... and thou shall be saved!\n");
   return 1;
}

int
do_stir(string s)
{
object *arr, drink;
int    actor;

   CHECK_PLAYING(TP);

   arr = FIND_STR_IN_ARR(s, all_inventory(TP));
   notify_fail("Stir what?\n");
   if (!sizeof(arr)) return 0;

   notify_fail("You cannot stir more than one thing at once.\n");
   if (sizeof(arr) > 1) return 0;

   drink = arr[0];
   notify_fail("You cannot stir that!\n");
   if (member_array("/std/drink.c", inherit_list(drink)) < 0)
      return 0;

   actor = member_array(TP->query_real_name(), player);
   write("You take your enemy's king from the board and slowly " +
    "stir your " + drink->query_short() + " with it.\n" +
    "After that you carefully wipe the piece clean and put " +
    "it back on the board again, while keeping your face " +
    "perfectly streight.\n");
   tell_others(QCTNAME(TP) + " takes " + HIS(TP) + " opponent from the " +
    "board and slowly stirs " + HIS(TP) + " " + drink->query_short() + 
    " with it.\n" +
    "After that " + HE(TP) + " carefully wipes the piece clean " +
    "and puts it back on the board again, while keeping " +
    HIS(TP) + " face perfectly streight.\n");
   tell_player(QCTNAME(TP) + " takes your king from the " +
    "board and slowly stirs " + HIS(TP) + " " + drink->query_short() +
    " with it.\n" +
    "After that " + HE(TP) + " carefully wipes the piece clean " +
    "and puts it back on the board again, while keeping " +
    HIS(TP) + " face perfectly streight.\n", 1 - actor);
   
   return 1;
}

void
init()
{
   ::init();
   add_action(do_move, "move");
   add_action(do_move, "play");
   add_action(do_accept, "accept");
   add_action(do_challenge, "challenge");
   add_action(do_reset, "reset");
   add_action(do_choose, "choose");
   add_action(do_help, "help");
   add_action(do_resign, "resign");
   
   // some emotes
   add_action(do_fist, "cfist");
   add_action(do_foolish, "cfoolish");
   add_action(do_good, "cgood");
   add_action(do_knock, "cknock");
   add_action(do_repent, "crepent");
   add_action(do_stir, "cstir");
}
