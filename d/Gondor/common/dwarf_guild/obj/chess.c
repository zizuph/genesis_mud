/*
 * /d/Gondor/common/dwarf_guild/obj/chess.c
 *
 * Copyright (C) Stas van der Schaaf - January 13 1994
 *               Mercade @ Genesis
 *
 * This is a chessboard. It can be used to display problems on.
 *
 * Revision history:
 * - 14 August 2005 - made instructions more clearly visible for the dense.
 */

#pragma save_binary

inherit "/std/object";

#include <stdproperties.h>
#include "../dwarf.h"
#include "/d/Gondor/defs.h"

#define CHESSBOARD_ID DWARVEN_RACE_GUILD_PREFIX + "chessboard"
#define BOARD_SMALL   0
#define BOARD_LARGE   1
#define INITIAL  \
  ({ "rnbqkbnr", \
     "pppppppp", \
     "........", \
     "........", \
     "........", \
     "........", \
     "PPPPPPPP", \
     "RNBQKBNR"  })
#define INSTRUCTION_WORDS ({ "paper", "piece of paper", "explanation", \
    "explanations", "instruction", "instructions" })

/*
 * Global variable
 */
string *initial   = INITIAL;
string *position  = initial;
int    board_size = BOARD_LARGE;

void
create_object()
{
    set_name("board");
    add_name("chessboard");
    add_name(CHESSBOARD_ID);

    set_pname("boards");
    add_pname("chessboards");

    add_adj("chess");
    add_adj("wooden");

    set_short("wooden chessboard");
    set_pshort("wooden chessboards");

    set_long("@@long_description@@");

    add_item( ({ "position", "pieces", "problem" }),
	"@@position_description@@");
    add_item( ({ "letters", "numbers" }),
	"Horizontally you see the letters A till H carved into the " +
	"board and vertically you see the numbers 1 till 8 carved into " +
	"it, the left corner on the bottom being labeled A1.\n");

    add_item(INSTRUCTION_WORDS, "@@instruction_description@@");
    add_cmd_item(INSTRUCTION_WORDS, ({ "read" }), "@@instruction_description@@");

    add_prop(OBJ_I_VALUE,   300);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1200);
    add_prop(OBJ_M_NO_GET,
	"You should leave the chessboard there for others to play " +
	"with it.\n");
    add_prop(OBJ_S_WIZINFO, "Examine the object for the most important " +
	"information. It was designed by Mercade for his quest in the " +
	DWARVEN_RACE_GUILD_NAME + ". The functions set_position and " +
	"query_position can be used to set positions into this object " +
	"from other objects handing the quest itself. This board can only " +
	"be used to display the position.");
}

string
long_description()
{
    string str = "It is a wooden chessboard. The black and white squares " +
	"are laid in with dark and light pieces of wood. Some numbers and " +
	"letters are carved in the board to make it easier to name the " +
	"places on it. Do <board small/large> to get a small or large " +
	"display of the position next time you examine it. It is " +
	((board_size == BOARD_SMALL) ? "small" : "large") + " now. There " +
	"is a piece of paper with explanations lying beside the board. ";

    if (position == initial)
    {
	str += "The pieces are currently lined up in the opening position.";
    }
    else if (sizeof(position))
    {
	str += "There is an interesting position displayed on the board.";
    }
    else
    {
	str += "The pieces lay beside and partially on the board. No " +
	    "position is visible on it.";
    }

    return str + "\n";
}

string
instruction_description()
{
    return
    	"EXPLANATION OF THE RULES AND NOTATION\n" +
	"=====================================\n\n" +
	"In the diagrams shown on this board, the white pieces will " +
	"be depicted by the letters in capitals and the black pieces are " +
	"represented by the lower case letters.\n" +
	"The following abbreviations are used: K for King, Q for " +
	"Queen, R for Rook, B for Bishop, N for kNight and P for Pawn.\n\n" +
	"The notation this game uses is the algebraic notation. In " +
	"this notation only the previous position and the new position of " +
	"the moving piece matter. The name of the piece moving and the " +
	"possible piece being captured and the capture itself \"*\", just " +
	"as well as check \"+\" may optionally be added, but will be ignored.\n\n" +
	"Castling is noted as \"0-0\" and \"0-0-0\" for resp. castling on " +
	"kingsside and queensside. If a pawn promotes, add the letter " +
	"of the piece the pawn promotes to.\n" +
        "Case or a space or dash in the move will be ignored. Examples " +
        "of correct moves are:\n" +
        "- \"e2-e4\"   (normal pawn move)\n" +
        "- \"Qd1 e2\"  (normal queen move)\n" +
        "- \"Qe5*Rh8\" (queen takes rook)\n" +
        "- \"0-0\"     (castling on kingsside)\n" +
        "- \"g7 g8r+\" (pawn promoted to rook with check).\n";
}

string
position_description()
{
    string str;
    int    i;

    if (!sizeof(position))
    {
	return "Currently all pieces lay beside the board. There is no " +
	    "position visible on the board.\n";
    }

    str = "The following position is visible on the board.\n\n";

    if (board_size == BOARD_SMALL)
    {
	for (i = 0; i < 8; i++)
	{
	    str += "    " + (8 - i) + " " + position[i] + "\n";
	}

	str += "\n      abcdefgh\n\n";
    }
    else
    {
	str += "\n        a  b  c  d  e  f  g  h\n\n\n";

	for (i = 0; i < 8; i++)
	{
	    str += "    " + (8 - i) + "   " +
		implode(explode(position[i], ""), "  ") + "   " + (8 - i) +
		"\n\n";
	}

	str += "\n        a  b  c  d  e  f  g  h\n\n";
    }

    return str;
}

void
init()
{
    ::init();

    add_action("board", "board");
}

int
board(string str)
{
    if (str == "small")
    {
	if (board_size == BOARD_SMALL)
	{
	    notify_fail("You can already see the small position.\n");
	    return 0;
	}

	board_size = BOARD_SMALL;
	write("Next time you examine the position it will be small.\n");

	return 1;
    }
    else if (str == "large")
    {
	if (board_size == BOARD_LARGE)
	{
	    notify_fail("You can already see the large position.\n");
	    return 0;
	}

	board_size = BOARD_LARGE;
	write("Next time you examine the position it will be large.\n");

	return 1;
    }

    notify_fail("The correct syntax to change the size of the board if you " +
	"examine the position is <board small> to get the small board " +
	"or <board large> to get the large board next time you examine " +
	"the position.\n");
    return 0;
}

void
reset_chessboard()
{
    position = initial;
}

void
set_position(string *lines)
{
    if (sizeof(lines) != 8)
    {
	return;
    }

    position = lines;
}

string *
query_position()
{
    return position;
}
