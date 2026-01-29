/*
 * The Meade and Mutton Inn
 * Created By Leia
 * 9/13/2005
 * Basic Inn Code Borrowed from the Prancing Pony
 */

inherit "/d/Shire/std/room";
inherit "/d/Shire/lib/inn";
#include "../defs.h"
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#define PRICELIST_ID  ({"pricelist","list","prices", "menu"})


/* Prototype */
void reset_shire_room();

string player1 = " ";
string player2 = " ";
string turn = " ";
string s1 = " ";
string s2 = " ";
string s3 = " ";
string s4 = " ";
string s5 = " ";
string s6 = " ";
string s7 = " ";
string s8 = " ";
string s9 = " ";

void
create_shire_room()
{
    set_short("The Meade and Mutton Inn");
    set_long("You have entered a vast room that has been furnished quite comfortably. Large stone chairs and couches, padded with bright red cushions, stand about the room. A large counter carved out of the rock itself stands near the back of the room with a sign perched upon it. There is also a small game board of some sorts standing here.\n");
    add_item("sign","The sign has writing on it.\n");
    add_cmd_item("sign","read","The sign reads:\nWelcome to the Meade and Mutton Inn!\n\nRead the pricelist for the menu options.\n\nStays at the inn may also be bought. Examine the pricelist for more info.\n\nPlease leave noisy pets outside the perimeter.\n\n");
    add_item(({"chair", "chairs"}), "The chairs are made out heavy stone and are padded with thick, red cushions.\n");
    add_item(({"couch", "couches"}), "The couches are made out of heavy stone and are padded with thick, red cushions.\n");
    add_item("counter", "The counter melds into the floor and seems to have been carved out of the rock itself.\n");
    add_item(({"board", "game board", "game"}), "This is a small board, with nine squares of sand separated by walls of rock. You instantly recognize this as a Tic Tac Toe board! There are two small sticks lying on either side of it for marking in the sand. There is a small plaque with instructions on it. Perhaps you should examine it.\n");
    add_item("plaque","TIC TAC TOE:\n\n1. This is a game for two players.\n2. To start playing, pick either player one or player two.\n3. When you have decided do: 'set me player #', where # is 1 or 2.\n4. Player 1 takes the first turn of the first game.\n5. After the first game, the loser of the previous game will take the first\n   turn.\n6. The game board is set up like this:\n\n       |       |       \n   1   |   2   |   3   \n_______|_______|_______\n       |       |       \n   4   |   5   |   6   \n_______|_______|_______\n       |       |       \n   7   |   8   |   9   \n       |       |       \n\n7. Player 1 will mark with an 'x' and player 2 with an 'o'.\n8. To mark a square, do 'mark s#' where # is one of the numerals in the square\n   above.\n9. To stop playing, do 'stop playing'.\n10. To win, claim three horizontally, vertically, or diagonally adjacent\n    squares.\n11. You may list the players by doing 'query players'.\n");
    add_item(PRICELIST_ID, "@@pricelist_desc");

// safe rooms
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(OBJ_M_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1); 
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);

    add_exit(SLEEP, "north");
    add_exit(DT16, "south");
    
    /*set_alarm(1.0, 0.0, reset_shire_room);*/
    configure_shire_inn();
    /*add_prop(ROOM_I_NO_CLEANUP,1);*/
}

int check_exit()
{
        if((player1 == TP->query_name()) || (player2 == TP->query_name()))
			return 0;
        write("You have to 'stop playing' the game before you leave the room!\n");
        return 1;
}

string
pricelist_desc()
{
    return "\nDrinks:\n\n"+
    "0. 'A glass of water'  ...........      5 cc\n"+
    "1. 'An ice cold beer' ............     20 cc\n"+
    "2. 'A pint of ale' ...............     50 cc\n"+
    "3. 'A shot of liquor' ............    180 cc\n"+
    "4. 'A fifth of meade' ............    250 cc\n"+
    
	"\nSnacks:\n\n"+
    
    "5. 'A short stack of brownies' ...     15 cc\n"+
    "6. 'A lambchop sandwich' .........     40 cc\n"+
    
    "\nMeals:\n\n"+
    
    "7. 'A bowl of stone soup' ........     75 cc\n"+
    "8. 'A leg of roast mutton' .......    160 cc\n"+
    "9. 'A gigantic meat platter'......    210 cc\n\n"+
    
    "10. 'A night's rest'..............    144 cc\n\n\n"+
    "You may order for other players as well as order for "+
    "multiple players.\n"+
    "Try using 'order <num> <item> for <players>' similar to how you "+
    "target players with an emotion.\n"+
    "You may also 'order <num> <item> for team' to buy things for the "+
    "teammates.\n";
}

void
reset_shire_room()
{
}

void
init()
{
    ::init();
    init_shire_inn();
    add_action("do_read", "read", 0);
    add_action("set_player", "set", 0);
    add_action("view_board", "view", 0);
    add_action("do_stop", "stop", 0);
    add_action("do_mark", "mark", 0);
    add_action("query_players", "query");
}

int
do_read(string str)
{
    if (!str)
        return 0;
    if (member_array(str, PRICELIST_ID) == -1)
        return 0;
    write(pricelist_desc());
    return 1;
}

int
do_order(string str) 
{

/*    if (!barliman || !present(barliman))
    {
        notify_fail("There is no-one here to buy anything from.\n"+
          "The innkeeper has been killed!\n");
        return 0;
    }*/

    return ::do_order(str);
}


mixed *
get_order(string item_name)
{
    object order;
    int price;

    setuid(); seteuid(getuid());
    switch (item_name)
    {
    case "water":
    case "waters":
    case "glass of water":
    case "0":
        order = clone_object(OBJS_DIR + "water");
        price = 5;
        break;
    case "beer":
    case "cold beer":
    case "nice cold beer":
    case "beers":
    case "cold beers":
    case "nice cold beers":
    case "1":
        order = clone_object(OBJS_DIR + "beer");
        price = 20;
        break;
    case "ale":
    case "pint":
    case "pint of ale":
    case "ales":
    case "pints":
    case "pints of ale":
    case "2":
        order = clone_object(OBJS_DIR + "ale");
        price = 50;
        break;
    case "liquor":
    case "shot of liquor":
    case "shots of liquor":
    case "liquors":
    case "3":
        order = clone_object(OBJS_DIR + "liquor");
        price = 180;
        break;
    case "meade":
    case "fifth of meade":
    case "meades":
    case "fifths of meade":
    case "4":
        order = clone_object(OBJS_DIR + "meade");
        price = 250;
        break;
    case "brownies":
    case "stack of brownies":
    case "stacks of brownies":
    case "short stack of brownies":
    case "short stacks of brownies":
    case "stack":
    case "stacks":
    case "5":
        order = clone_object(OBJS_DIR + "brownies");
        price = 15;
        break;
    case "sandwich":
    case "lambchop sandwich":
    case "sandwiches":
    case "lambchop sandwiches":
    case "6":
        order = clone_object(OBJS_DIR + "sandwich");
        price = 38;
        break;
    case "soup":
    case "stone soups":
    case "stone soups":
    case "soups":
    case "bowl of soup":
    case "bowls of soup":
    case "bowls of stone soup":
    case "bowl of stone soup":
    case "bowl":
    case "bowls":
    case "7":
        order = clone_object(OBJS_DIR + "soup");
        price = 75;
        break;
    case "mutton":
    case "leg of mutton":
    case "muttons":
    case "legs of mutton":
    case "leg of roast mutton":
    case "legs of roast mutton":
    case "8":
        order = clone_object(OBJS_DIR + "mutton");
        price = 160;
        break;
    case "platter":
    case "gigantic feast":
    case "gigantic meat platter":
    case "platters":
    case "gigantic platters":
    case "gigantic meat platters":
    case "9":
        order = clone_object(OBJS_DIR + "platter");
        price = 210;
        break;

    case "key":
    case "night's rest":
    case "a night's rest":
    case "10":
        order = clone_object(OBJS_DIR + "inn_rune");
        price = 144;
        break;
    }
    return (({order}) + ({price}));
}

int
set_player(string str)
{
	if (str == "me player 1")
		if (player1 == " ")
		{
			if (player2 == TP->query_name())
			{
				write("You are already playing as player 2!\n");
				return 1;
			}
			
			else
			{
				write("Okay, you are now player 1. You pick up a stick and get ready to play.\n");
				player1 = TP->query_name();
				turn = player1;
				return 1;
			}
		}

		else
		{
			if (player1 == TP->query_name())
			{
				write("You are already playing as player 1!\n");
				return 1;
			}

			if (player2 == TP->query_name())
			{
				write("You are already playing as player 2!\n");
				return 1;
			}

			else
			{
				write("Sorry, but someone is already playing as player 1!\n");
				return 1;
			}
		}

	if (str == "me player 2")
		if (player2 == " ")
		{
			if (player1 == TP->query_name())
			{
				write("You are already playing as player 1!\n");
				return 1;
			}
			
			else
			{
				write("Okay, you are now player 2. You pick up a stick and get ready to play.\n");
				player2 = TP->query_name();
				return 1;
			}
		}

		else
		{
			if (player2 == TP->query_name())
			{
				write("You are already playing as player 2!\n");
				return 1;
			}

			if (player1 == TP->query_name())
			{
				write("You are already playing as player 1!\n");
				return 1;
			}

			else
			{
				write("Sorry, but someone is already playing as player 1!\n");
				return 1;
			}
		}
}

int
view_board(string str)
{
	if (str != "board")
	{
		write("View what?\n");
		return 1;
	}

	write("\n       |       |       \n" + 
	"   " + s1 + "   |   " + s2 + "   |   " + s3 + "   \n" +
	"_______|_______|_______\n" +
	"       |       |       \n" +
	"   " + s4 + "   |   " + s5 + "   |   " + s6 + "   \n" +
	"_______|_______|_______\n" +
	"       |       |       \n" +
	"   " + s7 + "   |   " + s8 + "   |   " + s9 + "   \n" +
	"       |       |       \n");
	return 1;
}

int
do_stop(string str)
{
	if (str != "playing")
	{
		write("Stop what? Stop playing?\n");
		return 1;
	}

	if (player1 == TP->query_name())
	{
		player1 = " ";
		write("Thanks for playing! Come again!\n");
		if (player2 = " ")
		{
			s1 = " ";
			s2 = " ";
			s3 = " ";
			s4 = " ";
			s5 = " ";
			s6 = " ";
			s7 = " ";
			s8 = " ";
			s9 = " ";
			turn = " ";
		}
		return 1;
	}

	if (player2 == TP->query_name())
	{
		if (player1 = " ")
		{
			s1 = " ";
			s2 = " ";
			s3 = " ";
			s4 = " ";
			s5 = " ";
			s6 = " ";
			s7 = " ";
			s8 = " ";
			s9 = " ";
			turn = " ";
		}
		player2 = " ";
		write("Thanks for playing! Come again!\n");
		return 1;
	}

	else
	{
		write("But you aren't playing!!\n");
		return 1;
	}
}

int
do_mark(string str)
{
	if (player1 != TP->query_name() && player2 != TP->query_name())
	{
		write("But you aren't playing Tic Tac Toe!\n");
		return 1;
	}

	if (turn != TP->query_name())
	{
		write("But it isn't your turn!\n");
		return 1;
	}
	
	if (str == "s1")	
	{
		if (s1 != " ")
		{
			write("That square has already been marked! Try another square.\n");
			return 1;
		}

		if (s1 == " ")
		{
			if (player1 == TP->query_name())
			{
				write("You mark the square with a small x.\n");
				s1 = "x";
				turn = player2;
				tell_room(TO, "It is now the second player's turn.");
				if ((s1 == "x" && s2 == "x" && s3 == "x") || (s1 == "x" && s4 == "x" && s7 == "x") || (s1 == "x" && s5 == "x" && s9 == "x"))
				{
					tell_room(TO, "Player 1 wins the game!\n");
					tell_room(TO, "       |       |       \n" + 
					"   " + s1 + "   |   " + s2 + "   |   " + s3 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s4 + "   |   " + s5 + "   |   " + s6 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s7 + "   |   " + s8 + "   |   " + s9 + "   \n" +
					"       |       |       \n"); 
					s1 = " ";
					s2 = " ";
					s3 = " ";
					s4 = " ";
					s5 = " ";
					s6 = " ";
					s7 = " ";
					s8 = " ";
					s9 = " ";
					turn = player2;
					tell_room(TO, "It is now the second player's turn.");
					tell_room(TO, "Suddenly the paper is magically clean, and ready to play on again!\n");
				}
				return 1;
			}

			if (player2 == TP->query_name())
			{
				write("You mark the square with a small o.\n");
				s1 = "o";
				turn = player1;
				tell_room(TO, "It is now the first player's turn.");
				return 1;
				if ((s1 == "o" && s2 == "o" && s3 == "o") || (s1 == "o" && s4 == "o" && s7 == "o") || (s1 == "o" && s5 == "o" && s9 == "o"))
				{
					tell_room(TO, "Player 2 wins the game!\n");
					tell_room(TO, "       |       |       \n" + 
					"   " + s1 + "   |   " + s2 + "   |   " + s3 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s4 + "   |   " + s5 + "   |   " + s6 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s7 + "   |   " + s8 + "   |   " + s9 + "   \n" +
					"       |       |       \n"); 
					s1 = " ";
					s2 = " ";
					s3 = " ";
					s4 = " ";
					s5 = " ";
					s6 = " ";
					s7 = " ";
					s8 = " ";
					s9 = " ";
					turn = player1;
					tell_room(TO, "It is now the first player's turn.");
					tell_room(TO, "Suddenly the paper is magically clean, and ready to play on again!\n");
				}
			}

			else
			{
				write("This tic tac toe board is malfunctioning! Please report it to a Gondor wizard immediately!\n");
				return 1;
			}
		}
	}

	if (str == "s2")
	{
		if (s2 != " ")
		{
			write("That square has already been marked! Try another square.\n");
			return 1;
		}

		if (s2 == " ")
		{
			if (player1 == TP->query_name())
			{
				write("You mark the square with a small x.\n");
				s2 = "x";
				turn = player2;
				tell_room(TO, "It is now the second player's turn.");
				if ((s1 == "x" && s2 == "x" && s3 == "x") || (s2 == "x" && s5 == "x" && s8 == "x"))
				{
					tell_room(TO, "Player 1 wins the game!\n");
					tell_room(TO, "       |       |       \n" + 
					"   " + s1 + "   |   " + s2 + "   |   " + s3 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s4 + "   |   " + s5 + "   |   " + s6 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s7 + "   |   " + s8 + "   |   " + s9 + "   \n" +
					"       |       |       \n"); 
					s1 = " ";
					s2 = " ";
					s3 = " ";
					s4 = " ";
					s5 = " ";
					s6 = " ";
					s7 = " ";
					s8 = " ";
					s9 = " ";
					turn = player2;
					tell_room(TO, "It is now the second player's turn.");
					tell_room(TO, "Suddenly the paper is magically clean, and ready to play on again!\n");
				}
				return 1;
			}

			if (player2 == TP->query_name())
			{
				write("You mark the square with a small o.\n");
				s2 = "o";
				turn = player1;
				tell_room(TO, "It is now the first player's turn.");
				if ((s1 == "o" && s2 == "o" && s3 == "o") || (s2 == "o" && s5 == "o" && s8 == "o"))
				{
					tell_room(TO, "Player 2 wins the game!\n");
					tell_room(TO, "       |       |       \n" + 
					"   " + s1 + "   |   " + s2 + "   |   " + s3 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s4 + "   |   " + s5 + "   |   " + s6 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s7 + "   |   " + s8 + "   |   " + s9 + "   \n" +
					"       |       |       \n"); 
					s1 = " ";
					s2 = " ";
					s3 = " ";
					s4 = " ";
					s5 = " ";
					s6 = " ";
					s7 = " ";
					s8 = " ";
					s9 = " ";
					turn = player1;
					tell_room(TO, "It is now the first player's turn.");
					tell_room(TO, "Suddenly the paper is magically clean, and ready to play on again!\n");
				}
				return 1;
			}

			else
			{
				write("This tic tac toe board is malfunctioning! Please report it to a Gondor wizard immediately!\n");
				return 1;
			}
		}
	}

	if (str == "s3")
	{
		if (s3 != " ")
		{
			write("That square has already been marked! Try another square.\n");
			return 1;
		}

		if (s3 == " ")
		{
			if (player1 == TP->query_name())
			{
				write("You mark the square with a small x.\n");
				s3 = "x";
				turn = player2;
				tell_room(TO, "It is now the second player's turn.");
				if ((s1 == "x" && s2 == "x" && s3 == "x") || (s3 == "x" && s6 == "x" && s9 == "x") || (s3 == "x" && s5 == "x" && s7 == "x"))
				{
					tell_room(TO, "Player 1 wins the game!\n");
					tell_room(TO, "       |       |       \n" + 
					"   " + s1 + "   |   " + s2 + "   |   " + s3 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s4 + "   |   " + s5 + "   |   " + s6 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s7 + "   |   " + s8 + "   |   " + s9 + "   \n" +
					"       |       |       \n"); 
					s1 = " ";
					s2 = " ";
					s3 = " ";
					s4 = " ";
					s5 = " ";
					s6 = " ";
					s7 = " ";
					s8 = " ";
					s9 = " ";
					turn = player2;
					tell_room(TO, "It is now the second player's turn.");
					tell_room(TO, "Suddenly the paper is magically clean, and ready to play on again!\n");
				}
				return 1;
			}

			if (player2 == TP->query_name())
			{
				write("You mark the square with a small o.\n");
				s3 = "o";
				turn = player1;
				tell_room(TO, "It is now the first player's turn.");
				if ((s1 == "o" && s2 == "o" && s3 == "o") || (s3 == "o" && s6 == "o" && s9 == "o") || (s3 == "o" && s5 == "o" && s7 == "o"))
				{
					tell_room(TO, "Player 2 wins the game!\n");
					tell_room(TO, "       |       |       \n" + 
					"   " + s1 + "   |   " + s2 + "   |   " + s3 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s4 + "   |   " + s5 + "   |   " + s6 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s7 + "   |   " + s8 + "   |   " + s9 + "   \n" +
					"       |       |       \n"); 
					s1 = " ";
					s2 = " ";
					s3 = " ";
					s4 = " ";
					s5 = " ";
					s6 = " ";
					s7 = " ";
					s8 = " ";
					s9 = " ";
					turn = player1;
					tell_room(TO, "It is now the first player's turn.");
					tell_room(TO, "Suddenly the paper is magically clean, and ready to play on again!\n");
				}
				return 1;
			}

			else
			{
				write("This tic tac toe board is malfunctioning! Please report it to a Gondor wizard immediately!\n");
				return 1;
			}
		}
	}

	if (str == "s4")
	{
		if (s4 != " ")
		{
			write("That square has already been marked! Try another square.\n");
			return 1;
		}

		if (s4 == " ")
		{
			if (player1 == TP->query_name())
			{
				write("You mark the square with a small x.\n");
				s4 = "x";
				turn = player2;
				tell_room(TO, "It is now the second player's turn.");
				if ((s1 == "x" && s4 == "x" && s7 == "x") || (s4 == "x" && s5 == "x" && s6 == "x"))
				{
					tell_room(TO, "Player 1 wins the game!\n");
					tell_room(TO, "       |       |       \n" + 
					"   " + s1 + "   |   " + s2 + "   |   " + s3 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s4 + "   |   " + s5 + "   |   " + s6 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s7 + "   |   " + s8 + "   |   " + s9 + "   \n" +
					"       |       |       \n"); 
					s1 = " ";
					s2 = " ";
					s3 = " ";
					s4 = " ";
					s5 = " ";
					s6 = " ";
					s7 = " ";
					s8 = " ";
					s9 = " ";
					turn = player2;
					tell_room(TO, "It is now the second player's turn.");
					tell_room(TO, "Suddenly the paper is magically clean, and ready to play on again!\n");
				}				
				return 1;
			}

			if (player2 == TP->query_name())
			{
				write("You mark the square with a small o.\n");
				s4 = "o";
				turn = player1;
				tell_room(TO, "It is now the first player's turn.");
				if ((s1 == "o" && s4 == "o" && s7 == "o") || (s4 == "o" && s5 == "o" && s6 == "o"))
				{
					tell_room(TO, "Player 2 wins the game!\n");
					tell_room(TO, "       |       |       \n" + 
					"   " + s1 + "   |   " + s2 + "   |   " + s3 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s4 + "   |   " + s5 + "   |   " + s6 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s7 + "   |   " + s8 + "   |   " + s9 + "   \n" +
					"       |       |       \n"); 
					s1 = " ";
					s2 = " ";
					s3 = " ";
					s4 = " ";
					s5 = " ";
					s6 = " ";
					s7 = " ";
					s8 = " ";
					s9 = " ";
					turn = player1;
					tell_room(TO, "It is now the first player's turn.");
					tell_room(TO, "Suddenly the paper is magically clean, and ready to play on again!\n");
				}				
				return 1;
			}

			else
			{
				write("This tic tac toe board is malfunctioning! Please report it to a Gondor wizard immediately!\n");
				return 1;
			}
		}
	}

	if (str == "s5")
	{
		if (s5 != " ")
		{
			write("That square has already been marked! Try another square.\n");
			return 1;
		}

		if (s5 == " ")
		{
			if (player1 == TP->query_name())
			{
				write("You mark the square with a small x.\n");
				s5 = "x";
				turn = player2;
				tell_room(TO, "It is now the second player's turn.");
				if ((s1 == "x" && s5 == "x" && s9 == "x") || (s3 == "x" && s5 == "x" && s7 == "x") || (s2 == "x" && s5 == "x" && s8 == "x") || (s4 == "x" && s5 == "x" && s6 == "x"))
				{
					tell_room(TO, "Player 1 wins the game!\n");
					tell_room(TO, "       |       |       \n" + 
					"   " + s1 + "   |   " + s2 + "   |   " + s3 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s4 + "   |   " + s5 + "   |   " + s6 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s7 + "   |   " + s8 + "   |   " + s9 + "   \n" +
					"       |       |       \n"); 
					s1 = " ";
					s2 = " ";
					s3 = " ";
					s4 = " ";
					s5 = " ";
					s6 = " ";
					s7 = " ";
					s8 = " ";
					s9 = " ";
					turn = player2;
					tell_room(TO, "It is now the second player's turn.");
					tell_room(TO, "Suddenly the paper is magically clean, and ready to play on again!\n");
				}				
				return 1;
			}

			if (player2 == TP->query_name())
			{
				write("You mark the square with a small o.\n");
				s5 = "o";
				turn = player1;
				tell_room(TO, "It is now the first player's turn.");
				if ((s1 == "o" && s5 == "o" && s9 == "o") || (s3 == "o" && s5 == "o" && s7 == "o") || (s2 == "o" && s5 == "o" && s8 == "o") || (s4 == "o" && s5 == "o" && s6 == "o"))
				{
					tell_room(TO, "Player 2 wins the game!\n");
					tell_room(TO, "       |       |       \n" + 
					"   " + s1 + "   |   " + s2 + "   |   " + s3 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s4 + "   |   " + s5 + "   |   " + s6 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s7 + "   |   " + s8 + "   |   " + s9 + "   \n" +
					"       |       |       \n"); 
					s1 = " ";
					s2 = " ";
					s3 = " ";
					s4 = " ";
					s5 = " ";
					s6 = " ";
					s7 = " ";
					s8 = " ";
					s9 = " ";
					turn = player1;
					tell_room(TO, "It is now the first player's turn.");
					tell_room(TO, "Suddenly the paper is magically clean, and ready to play on again!\n");
				}				
				return 1;
			}

			else
			{
				write("This tic tac toe board is malfunctioning! Please report it to a Gondor wizard immediately!\n");
				return 1;
			}
		}
	}

	if (str == "s6")
	{
		if (s6 != " ")
		{
			write("That square has already been marked! Try another square.\n");
			return 1;
		}
	
		if (s6 == " ")
		{
			if (player1 == TP->query_name())
			{
				write("You mark the square with a small x.\n");
				s6 = "x";
				turn = player2;
				tell_room(TO, "It is now the second player's turn.");
				if ((s4 == "x" && s5 == "x" && s6 == "x") || (s3 == "x" && s6 == "x" && s9 == "x"))
				{
					tell_room(TO, "Player 1 wins the game!\n");
					tell_room(TO, "       |       |       \n" + 
					"   " + s1 + "   |   " + s2 + "   |   " + s3 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s4 + "   |   " + s5 + "   |   " + s6 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s7 + "   |   " + s8 + "   |   " + s9 + "   \n" +
					"       |       |       \n"); 
					s1 = " ";
					s2 = " ";
					s3 = " ";
					s4 = " ";
					s5 = " ";
					s6 = " ";
					s7 = " ";
					s8 = " ";
					s9 = " ";
					turn = player2;
					tell_room(TO, "It is now the second player's turn.");
					tell_room(TO, "Suddenly the paper is magically clean, and ready to play on again!\n");
				}
				return 1;
			}

			if (player2 == TP->query_name())
			{
				write("You mark the square with a small o.\n");
				s6 = "o";
				turn = player1;
				tell_room(TO, "It is now the first player's turn.");
				if ((s4 == "o" && s5 == "o" && s6 == "o") || (s3 == "o" && s6 == "o" && s9 == "o"))
				{
					tell_room(TO, "Player 2 wins the game!\n");
					tell_room(TO, "       |       |       \n" + 
					"   " + s1 + "   |   " + s2 + "   |   " + s3 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s4 + "   |   " + s5 + "   |   " + s6 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s7 + "   |   " + s8 + "   |   " + s9 + "   \n" +
					"       |       |       \n"); 
					s1 = " ";
					s2 = " ";
					s3 = " ";
					s4 = " ";
					s5 = " ";
					s6 = " ";
					s7 = " ";
					s8 = " ";
					s9 = " ";
					turn = player1;
					tell_room(TO, "It is now the first player's turn.");
					tell_room(TO, "Suddenly the paper is magically clean, and ready to play on again!\n");
				}				
				return 1;
			}

			else
			{
				write("This tic tac toe board is malfunctioning! Please report it to a Gondor wizard immediately!\n");
				return 1;
			}
		}
	}

	if (str == "s7")
	{
		if (s7 != " ")
		{
			write("That square has already been marked! Try another square.\n");
			return 1;
		}

		if (s7 == " ")
		{
			if (player1 == TP->query_name())
			{
				write("You mark the square with a small x.\n");
				s7 = "x";
				turn = player2;
				tell_room(TO, "It is now the second player's turn.");
				if ((s1 == "x" && s4 == "x" && s7 == "x") || (s7 == "x" && s8 == "x" && s9 == "x") || (s3 == "x" && s5 == "x" && s9 == "x"))
				{
					tell_room(TO, "Player 1 wins the game!\n");
					tell_room(TO, "       |       |       \n" + 
					"   " + s1 + "   |   " + s2 + "   |   " + s3 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s4 + "   |   " + s5 + "   |   " + s6 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s7 + "   |   " + s8 + "   |   " + s9 + "   \n" +
					"       |       |       \n"); 
					s1 = " ";
					s2 = " ";
					s3 = " ";
					s4 = " ";
					s5 = " ";
					s6 = " ";
					s7 = " ";
					s8 = " ";
					s9 = " ";
					turn = player2;
					tell_room(TO, "It is now the second player's turn.");
					tell_room(TO, "Suddenly the paper is magically clean, and ready to play on again!\n");
				}
				return 1;
			}	

			if (player2 == TP->query_name())
			{
				write("You mark the square with a small o.\n");
				s7 = "o";
				turn = player1;
				tell_room(TO, "It is now the first player's turn.");
				if ((s1 == "o" && s4 == "o" && s7 == "o") || (s7 == "o" && s8 == "o" && s9 == "o") || (s3 == "o" && s5 == "o" && s9 == "o"))
				{
					tell_room(TO, "Player 2 wins the game!\n");
					tell_room(TO, "       |       |       \n" + 
					"   " + s1 + "   |   " + s2 + "   |   " + s3 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s4 + "   |   " + s5 + "   |   " + s6 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s7 + "   |   " + s8 + "   |   " + s9 + "   \n" +
					"       |       |       \n"); 
					s1 = " ";
					s2 = " ";
					s3 = " ";
					s4 = " ";
					s5 = " ";
					s6 = " ";
					s7 = " ";
					s8 = " ";
					s9 = " ";
					turn = player1;
					tell_room(TO, "It is now the first player's turn.");
					tell_room(TO, "Suddenly the paper is magically clean, and ready to play on again!\n");
				}				
				return 1;
			}

			else
			{
				write("This tic tac toe board is malfunctioning! Please report it to a Gondor wizard immediately!\n");
				return 1;
			}
		}
	}

	if (str == "s8")
	{
		if (s8 != " ")
		{
			write("That square has already been marked! Try another square.\n");
			return 1;
		}
	
		if (s8 == " ")
		{
			if (player1 == TP->query_name())
			{
				write("You mark the square with a small x.\n");
				s8 = "x";
				turn = player2;
				tell_room(TO, "It is now the second player's turn.");
				if ((s2 == "x" && s5 == "x" && s8 == "x") || (s7 == "x" && s8 == "x" && s9 == "x"))
				{
					tell_room(TO, "Player 1 wins the game!\n");
					tell_room(TO, "       |       |       \n" + 
					"   " + s1 + "   |   " + s2 + "   |   " + s3 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s4 + "   |   " + s5 + "   |   " + s6 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s7 + "   |   " + s8 + "   |   " + s9 + "   \n" +
					"       |       |       \n"); 
					s1 = " ";
					s2 = " ";
					s3 = " ";
					s4 = " ";
					s5 = " ";
					s6 = " ";
					s7 = " ";
					s8 = " ";
					s9 = " ";
					turn = player2;
					tell_room(TO, "It is now the second player's turn.");
					tell_room(TO, "Suddenly the paper is magically clean, and ready to play on again!\n");
				}

				return 1;
			}

			if (player2 == TP->query_name())
			{
				write("You mark the square with a small o.\n");
				s8 = "o";
				turn = player1;
				tell_room(TO, "It is now the first player's turn.");
				if ((s2 == "o" && s5 == "o" && s8 == "o") || (s7 == "o" && s8 == "o" && s9 == "o"))
				{
					tell_room(TO, "Player 2 wins the game!\n");
					tell_room(TO, "       |       |       \n" + 
					"   " + s1 + "   |   " + s2 + "   |   " + s3 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s4 + "   |   " + s5 + "   |   " + s6 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s7 + "   |   " + s8 + "   |   " + s9 + "   \n" +
					"       |       |       \n"); 
					s1 = " ";
					s2 = " ";
					s3 = " ";
					s4 = " ";
					s5 = " ";
					s6 = " ";
					s7 = " ";
					s8 = " ";
					s9 = " ";
					turn = player1;
					tell_room(TO, "It is now the first player's turn.");
					tell_room(TO, "Suddenly the paper is magically clean, and ready to play on again!\n");
				}
				return 1;
			}

			else
			{
				write("This tic tac toe board is malfunctioning! Please report it to a Gondor wizard immediately!\n");
				return 1;
			}
		}
	}

	if (str == "s9")	
	{
		if (s9 != " ")
		{
			write("That square has already been marked! Try another square.\n");
			return 1;
		}

			if (s9 == " ")
		{
			if (player1 == TP->query_name())
			{
				write("You mark the square with a small x.\n");
				s9 = "x";
				turn = player2;
				tell_room(TO, "It is now the second player's turn.");
				if ((s1 == "x" && s5 == "x" && s9 == "x") || (s3 == "x" && s6 == "x" && s9 == "x") || (s7 == "x" && s8 == "x" && s9 == "x"))
				{
					tell_room(TO, "Player 1 wins the game!\n");
					tell_room(TO, "       |       |       \n" + 
					"   " + s1 + "   |   " + s2 + "   |   " + s3 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s4 + "   |   " + s5 + "   |   " + s6 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s7 + "   |   " + s8 + "   |   " + s9 + "   \n" +
					"       |       |       \n"); 
					s1 = " ";
					s2 = " ";
					s3 = " ";
					s4 = " ";
					s5 = " ";
					s6 = " ";
					s7 = " ";
					s8 = " ";
					s9 = " ";
					turn = player2;
					tell_room(TO, "It is now the second player's turn.");
					tell_room(TO, "Suddenly the paper is magically clean, and ready to play on again!\n");
				}			
				return 1;
			}

			if (player2 == TP->query_name())
			{
				write("You mark the square with a small o.\n");
				s9 = "o";
				turn = player1;
				tell_room(TO, "It is now the first player's turn.");
				if ((s1 == "o" && s5 == "o" && s9 == "o") || (s3 == "o" && s6 == "o" && s9 == "o") || (s7 == "o" && s8 == "o" && s9 == "o"))
				{
					tell_room(TO, "Player 2 wins the game!\n");
					tell_room(TO, "       |       |       \n" + 
					"   " + s1 + "   |   " + s2 + "   |   " + s3 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s4 + "   |   " + s5 + "   |   " + s6 + "   \n" +
					"_______|_______|_______\n" +
					"       |       |       \n" +
					"   " + s7 + "   |   " + s8 + "   |   " + s9 + "   \n" +
					"       |       |       \n"); 
					s1 = " ";
					s2 = " ";
					s3 = " ";
					s4 = " ";
					s5 = " ";
					s6 = " ";
					s7 = " ";
					s8 = " ";
					s9 = " ";
					turn = player1;
					tell_room(TO, "It is now the first player's turn.");
					tell_room(TO, "Suddenly the paper is magically clean, and ready to play on again!\n");
				}			
				return 1;
			}

				else
			{
				write("This tic tac toe board is malfunctioning! Please report it to a Gondor wizard immediately!\n");
				return 1;
			}
		}
	}

	if((s1 == "x" || s1 == "o") && (s2 == "x" || s2 == "o") && (s3 == "x" || s3 == "o") && (s4 == "x" || s4 == "o") && (s5 == "x" || s5 == "o") && (s6 == "x" || s6 == "o") && (s7 == "x" || s7 == "o") && (s8 == "x" || s8 == "o") && (s9 == "x" || s9 == "o"))
	{
		tell_room(TO, "The game is a draw!\n");
		tell_room(TO, "       |       |       \n" + 
		"   " + s1 + "   |   " + s2 + "   |   " + s3 + "   \n" +
		"_______|_______|_______\n" +
		"       |       |       \n" +
		"   " + s4 + "   |   " + s5 + "   |   " + s6 + "   \n" +
		"_______|_______|_______\n" +
		"       |       |       \n" +
		"   " + s7 + "   |   " + s8 + "   |   " + s9 + "   \n" +
		"       |       |       \n"); 
		s1 = " ";
		s2 = " ";
		s3 = " ";
		s4 = " ";
		s5 = " ";
		s6 = " ";
		s7 = " ";
		s8 = " ";
		s9 = " ";
		tell_room(TO, "The turn will default to player 1 as a result of the tie.\n");
		turn = player1;
		tell_room(TO, "Suddenly the paper is magically clean, and ready to play on again!\n");
		return 1;
	}

	else
	{
		write("Mark what?\n");
		return 1;
	}

}

int query_players(string str)
{
	if(str != "players")
	{
		write("Query what? Players?\n");
		return 1;
	}
	
	write(player1 + " is player 1, and " + player2 + " is player 2.\n");
	return 1;
}