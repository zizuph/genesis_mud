/*
 * The Meade and Mutton Inn
 * Created By Leia
 * 9/13/2005
 */

inherit "/d/Shire/std/room";
inherit "/d/Shire/lib/inn";
#include "../defs.h"
#include "/d/Shire/sys/defs.h"

// #include "/d/Shire/bree/defs.h"
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
    set_long("You have entered a vast room that has been furnished quite comfortably. Large stone chairs and couches, padded with bright red cushions, stand about the room. A large counter carved out of the rock itself stands near the back of the room with a sign perched upon it.\n");
    add_item("sign","The sign has writing on it.\n");
    add_cmd_item("sign","read","The sign reads:\nWelcome to the Meade and Mutton Inn!\n\nRead the pricelist for the menu options.\n\nStays at the inn may also be bought. Examine the pricelist for more info.\n\nPlease leave noisy pets outside the perimeter.\n\n");
    add_item(({"chair", "chairs"}), "The chairs are made out heavy stone and are padded with thick, red cushions.\n");
	add_item(({"couch", "couches"}), "The couches are made out of heavy stone and are padded with thick, red cushions.\n");
	add_item("counter", "The counter melds into the floor and seems to have been carved out of the rock itself.\n");
    add_item(PRICELIST_ID, "@@pricelist_desc");

// safe rooms
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(OBJ_M_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1); 
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);

	/*    add_exit(TOWN_DIR + "innyard","south");
    add_exit(TOWN_DIR + "innfront","west");
    add_exit(OLD_BREE_DIR + "innroom","east");
    add_exit("/d/Shire/bree/rooms/town/connect4", "north");*/

    /*set_alarm(1.0, 0.0, reset_shire_room);*/
    configure_shire_inn();
    /*add_prop(ROOM_I_NO_CLEANUP,1);*/
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
        order = clone_object(OBJ_DIR + "water");
        price = 5;
        break;
    case "beer":
    case "cold beer":
    case "nice cold beer":
    case "beers":
    case "cold beers":
    case "nice cold beers":
    case "1":
        order = clone_object(OBJ_DIR + "beer");
        price = 20;
        break;
    case "ale":
    case "pint":
    case "pint of ale":
    case "ales":
    case "pints":
    case "pints of ale":
    case "2":
        order = clone_object(OBJ_DIR + "ale");
        price = 50;
        break;
    case "liquor":
    case "shot of liquor":
    case "shots of liquor":
    case "liquors":
    case "3":
        order = clone_object(OBJ_DIR + "liquor");
        price = 180;
        break;
    case "meade":
    case "fifth of meade":
    case "meades":
    case "fifths of meade":
    case "4":
        order = clone_object(OBJ_DIR + "meade");
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
        order = clone_object(OBJ_DIR + "brownies");
        price = 15;
        break;
    case "sandwich":
    case "lambchop sandwich":
    case "sandwiches":
    case "lambchop sandwiches":
    case "6":
        order = clone_object(OBJ_DIR + "sandwich");
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
        order = clone_object(OBJ_DIR + "soup");
        price = 75;
        break;
    case "mutton":
    case "leg of mutton":
    case "muttons":
    case "legs of mutton":
	case "leg of roast mutton":
	case "legs of roast mutton":
    case "8":
        order = clone_object(OBJ_DIR + "mutton");
        price = 160;
        break;
    case "platter":
    case "gigantic feast":
	case "gigantic meat platter":
    case "platters":
    case "gigantic platters":
	case "gigantic meat platters":
    case "9":
        order = clone_object(OBJ_DIR + "platter");
        price = 210;
        break;

    case "key":
    case "night's rest":
	case "a night's rest":
    case "10":
        order = clone_object(OBJ_DIR + "inn_rune");
        price = 144;
        break;
    }
    return (({order}) + ({price}));
}

int
set_player(str string)
{
	if (string = "me player 1")
		if (player1 = " ")
		{
			if (player2 = TP->query_name();
			{
				write("You are already playing as player 2!\n");
				return 1;
			}
			
			else
			{
				write("Okay, you are now player 1.\n");
				player1 = TP->query_name();
				return 1;
			}
		}

		else
		{
			if (player1 = TP->query_name();
			{
				write("You are already playing as player 1!\n");
				return 1;
			}

			if (player2 = TP->query_name();
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

	if (string = "me player 2")
		if (player2 = " ")
		{
			if (player1 = TP->query_name();
			{
				write("You are already playing as player 1!\n");
				return 1;
			}
			
			else
			{
				write("Okay, you are now player 2.\n");
				player1 = TP->query_name();
				return 1;
			}
		}

		else
		{
			if (player2 = TP->query_name();
			{
				write("You are already playing as player 2!\n");
				return 1;
			}

			if (player1 = TP->query_name();
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
view_board(str string)
{
	if (string != board)
	{
		write("View what?");
		return 0;
	}

	write(""       |       |       /n   " + s1 + "   |   " + s2 + "   |   " + s3 + "   /n_______|_______|_______/n       |       |       /n   " + s4 + "   |   " + s5 + "   |   " + s6 + "   /n_______|_______|_______/n       |       |       /n   " + s7 + "   |   " + s8 + "   |   " + s9 + "   /n       |       |       /n");
	return 0;
}