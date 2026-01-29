/**********************************************************************
 * - inn.c                                                          - *
 * -                                                                - *
 * - Created by Damaris@Genesis 08/2006                             - *
 **********************************************************************/
#pragma strict_types

inherit "/d/Khalakhor/std/room";
inherit "/d/Khalakhor/lib/tavern";
inherit "/lib/trade.c";

#include "fireplace.c"
#include "sitting.c"
#include <money.h>

#define INN_OBJ ("/d/Khalakhor/sw_speir/samorgan/inn/obj/")
#define NUM sizeof(MONEY_TYPES)
#define VILLAGE ("/d/Khalakhor/sw_speir/samorgan/room/vil0508")
int rent1, rent2, rent3, rent4, rent5, rent6;
object bruce;

string
query_bronze_sign()
{
	return("\n"+
	"          *--------------------*` - - `*--------------------*\n"+
	"          | ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` |\n"+
	"          | `                                             ` |\n"+
	"          | `               The SaMorgan Inn              ` |\n"+
	"          | `               Rooms and Bathing             ` |\n"+
	"          | `       *`----------------------------`*      ` |\n"+
	"          | `                                             ` |\n"+
	"          | `                                             ` |\n"+
	"          | `     Keys are available for private rooms.   ` |\n"+
	"          | `                                             ` |\n"+
	"          | `     You may 'rent room 1-6'                 ` |\n"+
	"          | `                                             ` |\n"+
	"          | `     Please remember to 'check out' at the   ` |\n"+
	"          | `     end of your stay.                       ` |\n"+
	"          | `                                             ` |\n"+
	"          | `     You may also enjoy our lovely public    ` |\n"+
	"          | `     bathing areas.                          ` |\n"+
	"          | `                                             ` |\n"+
	"          | `     <buy male ticket>                       ` |\n"+
	"          | `     <buy female ticket>                     ` |\n"+
	"          | `     <buy public ticket>                     ` |\n"+
	"          | `                                             ` |\n"+
	"          | `                                             ` |\n"+
	"          | ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` |\n"+
	"          *--------------------*` - - `*--------------------*\n");
}

string
inscription()
{
	return("The inscription reads:\n"+
	"Clann 'Ic an t-Sagairt\n");
}

string
menustuff(void)
{
	action_tavern_menu("menu");
	return "";
}

public void
create_khalakhor_room()
{
	set_short("SaMorgan Inn");
	set_long("\n   A large inviting fireplace resides in the western "+
	"wall of this spacious inn. Placed near the eastern wall is a "+
	"long bar that has a bronze sign and a menu. Just past a few "+
	"tables through the northern archway is obviously the kitchen "+
	"as strange yet wonderful smells are emanating from there along "+
	"with sounds of pots and pans clinking together occasionally. A "+
	"stairway leading upwards to private areas is next to the front "+
	"of the bar. ");
	
	add_item(({"room", "area", "inn", "samorgan inn"}),
	"A large inviting fireplace resides in the western "+
	"wall of this spacious inn. Placed near the eastern wall is a "+
	"long bar that has a bronze sign and a menu. Just past a few "+
	"tables through the northern archway is obviously the kitchen "+
	"as strange yet wonderful smells are emanating from there along "+
	"with sounds of pots and pans clinking together occasionally. A "+
	"stairway leading upwards to private areas is next to the front "+
	"of the bar.\n");
	add_item(({"bar stools", "stools", "stool", "bar stool", "chair", "chairs"}), seat_desc);
	add_my_desc(seat_desc, this_object());
	add_item(({"sign"}), query_bronze_sign);
	add_cmd_item("sign","read", query_bronze_sign);
	add_cmd_item("inscription","read", inscription);
	add_item("menu", menustuff);
	add_item(({"fireplace"}),
	"The fireplace is quite large with an inviting fire dancing "+
	"within.\n");
	add_item(({"fire"}),
	"The fire dances while warming the area.\n" );	
	add_item(({"wall", "walls"}),
	"The walls are lightly coloured with age and the surface is "+
	"slightly roughened.\n");
	add_item(({"ceiling"}),
	"The ceiling is lightly coloured with age.\n");
	add_item(({"up", "stairs", "stairway"}),
	"A large wooden stairway leads upwards.\n");
	add_item(({"floor", "flooring"}),
	"The flooring is hardwood and it has been darkened with age.\n");
	add_item(({"bar", "long bar", "wooden bar"}),
	"This is a long wooden bar with a menu and a small bronze sign "+
	"etched with flowing script placed upon it.\n");
	add_item(({"kitchen", "archway", "arch", "north"}),
	"The kitchen is through the archway in the northern wall.\n");
	add_item(({"coat of arms"}),
	"The coat of arms above the fireplace is of two bronze swords "+
	"crossed above a snarling boar's snout. There is a small "+
	"inscription in the lower right corner.\n");
	add_item(({"swords"}),
	"There are two bronze swords crossed on the coat of arms.\n");
	add_item(({"west", "western wall", "west wall"}),
	"A wall is in that direction with a large fireplace that has "+
	"a coat of arms above it.\n");
	add_item(({"north", "east", "northeast", "northwest", "southeast", "southwest"}),
	"A wall is in that direction.\n");

	add_item(({"south"}),
	"An archway leading to the village is in that direction.\n");
	add_item(({"banister", "highly polished banister", "polish banister", "wooden banister", "wood banister"}),
	"The highly polished wooden banister is sturdy and is "+
	"connected to the stairs that lead up.\n");

	set_tavern_name("SaMorgan Inn");	
	add_tavern_drink(INN_OBJ + "dale");
	add_tavern_drink(INN_OBJ + "pale");
	add_tavern_drink(INN_OBJ + "rwine");
	add_tavern_drink(INN_OBJ + "wwine");
	add_tavern_drink(INN_OBJ + "coffee");
	add_tavern_drink(INN_OBJ + "mocha");
	add_tavern_drink(INN_OBJ + "tea");
	add_tavern_food(INN_OBJ + "deer");
	add_tavern_food(INN_OBJ + "rdragon");
	add_tavern_food(INN_OBJ + "ccake");
	add_tavern_food(INN_OBJ + "gcake");
	add_tavern_wares(({INN_OBJ + "ticketm",
	                   INN_OBJ + "ticketf",
	                   INN_OBJ + "ticketp",
	                   INN_OBJ + "soap",
	                   INN_OBJ + "towel",
	                   }));
	set_tavern_waiter("/d/Khalakhor/sw_speir/samorgan/inn/npc/bruce");
	clone_object("/d/Khalakhor/sw_speir/samorgan/inn/npc/bruce")->move(this_object());
	
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 1);
	
	add_exit("kitchen", "north");
	add_exit("landing", "up");
	add_exit(VILLAGE, "south");
	
	add_fail(({"west", "southwest", "southeast", "northeast", "northwest"}),
	"You walked into a wall.\n"+
	"OUCH! That's gotta hurt!\n");
	add_fail(({"west"}),
	"You have managed to fall straight into the fireplace by not "+
	"paying attention to where you were going!\n\n"+
	"You scream in agony as you suffer second degree burns, before "+
	"managing to stumble back from the fire.\n");
	config_default_trade();
}

int
check_out(string str)
{
	object key1, key2, key3, key4, key5, key6;
	key1 = present("key1", this_player());
	key2 = present("key2", this_player());
	key3 = present("key3", this_player());
	key4 = present("key4", this_player());
	key5 = present("key5", this_player());
	key6 = present("key6", this_player());

	if (str != "out")
	{
		notify_fail("Do you wish to check out?\n");
		return 0;
	}
	if (!present("bruce", this_object()))
	{
		write("You cannot check out if the innkeeper is "+
		"not present.\n");
		return 1;
	}
	if (str == "out")
	{
		if (present("key1", this_player()))
		{
			object door;
			
			write("You return your key and check out of "+
			"the room.\nThe innkeeper says: I hope your "+
			"stay was pleasant.\n");
			say(QCTNAME(this_player()) + " returns "+
			""+this_player()->query_possessive() + " "+
			"key and checks out of the inn.\n");
			
			rent1 = 0;
			if (key1)
			key1->remove_object();
			return 1;
			door = present("door",
			find_object("/d/Khalakhor/sw_speir/samorgan/inn/room/room1"));
			if(door)
			{
				door->do_close_door();
				door->set_open(0);
			}
		}
		if (present("key2", this_player()))
		{
			write("You return your key and check out of the "+
			"room.\nThe innkeeper says: I hope your stay was "+
			"pleasurable. Visit again as you wish.\n");
			say(QCTNAME(this_player()) + " returns "+
			this_player()->query_possessive() +
			" key and checks out of the inn.\n");
			rent2 = 0;
			
			if (key2)
			key2->remove_object();
			return 1;
		}
		if (present("key3", this_player()))
		{
			write("You return your key and check out of the "+
			"room.\nThe innkeeper says: I hope your stay was "+
			"pleasurable. Visit again as you wish.\n");
			say(QCTNAME(this_player()) + " returns "+
			this_player()->query_possessive() +
			" key and checks out of the inn.\n");
			rent3 = 0;
			if (key3)
			key3->remove_object();
			return 1;
		}
		if (present("key4", this_player()))
		{
			write("You return your key and check out of "+
			"the room.\nThe innkeeper says: I hope your stay "+
			"was enjoyable. Visit again as you wish.\n");
			say(QCTNAME(this_player()) + " returns "+
			this_player()->query_possessive() +
			" key and checks out of the inn.\n");
			rent4 = 0;
			if (key4)
			key4->remove_object();
			return 1;
		}
		if (present("key5", this_player()))
		{
			write("You return your key and check out of "+
			"the room.\nThe innkeeper says: I hope your stay "+
			"was enjoyable. Visit again as you wish.\n");
			say(QCTNAME(this_player()) + " returns "+
			this_player()->query_possessive() +
			" key and checks out of the inn.\n");
			rent5 = 0;
			if (key5)
			key5->remove_object();
			return 1;
		}
		if (present("key6", this_player()))
		{
			write("You return your key and check out of "+
			"the bath.\nThe innkeeper says: I trust you "+
			"enjoyed your bath. Visit again as you wish.\n");
			say(QCTNAME(this_player()) + " returns "+
			this_player()->query_possessive() +
			" key and checks out of the inn.\n");
			rent6 = 0;
			if (key6)
			key6->remove_object();
			return 1;
		}
		else
		write("The innkeeper says: Are you sure you rented a "+
		"room? I don't see your name in my ledger.\n");
		return 1;
	}
}

int
rent_room(string str)
{
	object key1, key2, key3, key4, key5, key6;
	string what, for_c, get_c, change;
	int *result, m_res, price;
	
	if (!present("bruce", this_object()))
	{
		write("The innkeeper must be present for you to rent a "+
		"room.\n");
		return 1;
	}
	if (str == "room 1")
	{
		if (present("_samorgan_room_key", this_player()))
		{
			write("You have already rented a room.\n");
			return 1;
		}
		if (rent1 == 1)
		{
			write("The innkeeper says: Room 1 has already "+
			"been rented.\n");
			return 1;
		}
		if (sscanf(str, "%s with %s and get %s", what, for_c,            get_c) != 3)
		{
			if (sscanf(str, "%s with %s", what, for_c) != 2)
			what = str;
		}
		key1 = clone_object(INN_OBJ + "key1");
		price = key1->query_prop(OBJ_I_VALUE);
		result = pay(price, this_player(), for_c, 0, 0, get_c);
		if (sizeof(result) == 1)
		{
			key1->remove_object();
			return 0;
		}
		if (key1->move(this_player()))
		{
			write("The key is too heavy and you drop it on "+
			"the floor.\n");
			say(QCTNAME(this_player())+ " drops something.\n");
			key1->move(environment(this_player()));
		}
		else
		{
			write("The innkeeper hands you a key to room "+
			"1.\n");
			say(QCTNAME(this_player()) + " pays for a room "+
			"and the innkeeper hands "
			+ this_player()->query_objective() + " a key.\n");
		}
		write("You pay "+ text(result[0 .. NUM - 1])+".\n");
		if (change)
		write("You get "+ change + " as change.\n");
		rent1 = 1;
		return 1;
	}
	if (str == "room 2")
	{
		if (present("_samorgan_room_key", this_player()))
		{
			write("You have already rented a room.\n");
			return 1;
		}
		if (rent2 == 1)
		{
			write("The innkeeper says: Room 2 has already "+
			"been rented.\n");
			return 1;
		}
		if (sscanf(str, "%s with %s and get %s", what, for_c,
		get_c) != 3)
		{
			if (sscanf(str, "%s with %s", what, for_c) != 2)
			what = str;
		}
		key2 = clone_object(INN_OBJ + "key2");
		price = key2->query_prop(OBJ_I_VALUE);
		result = pay(price, this_player(), for_c, 0, 0, get_c);
		if (sizeof(result) == 1)
		{
			key2->remove_object();
			return 0;
		}
		if (key2->move(this_player()))
		{
			write("The key is too heavy and you drop it on "+
			"the floor.\n");
			say(QCTNAME(this_player())+ " drops something.\n");
			key2->move(environment(this_player()));
		}
		else
		{
			write("The innkeeper hands you a key to room "+
			"2.\n");
			say(QCTNAME(this_player()) + " pays for a room "+
			"and the innkeeper hands "
			+ this_player()->query_objective() + " a key.\n");
		}
		write("You pay "+ text(result[0 .. NUM - 1])+".\n");
		if (change)
		write("You get "+ change + " as change.\n");
		rent2 = 1;
		return 1;
	}
	if (str == "room 3")
	{
		if (present("_samorgan_room_key", this_player()))
		{
			write("You have already rented a room.\n");
			return 1;
		}
		if (rent3 == 1)
		{
			write("The innkeeper says: Room 3 has already "+
			"been rented.\n");
			return 1;
		}
		if (sscanf(str, "%s with %s and get %s", what, for_c,
		get_c) != 3)
		{
			if (sscanf(str, "%s with %s", what, for_c) != 2)
			what = str;
		}
		key3 = clone_object(INN_OBJ + "key3");
		price = key3->query_prop(OBJ_I_VALUE);
		result = pay(price, this_player(), for_c, 0, 0, get_c);
		if (sizeof(result) == 1)
		{
			key3->remove_object();
			return 0;
		}
		if (key3->move(this_player()))
		{
			write("The key is too heavy and you drop it on "+
			"the floor.\n");
			say(QCTNAME(this_player())+ " drops something.\n");
			key3->move(environment(this_player()));
		}
		else
		{
			write("The innkeeper hands you a key to room "+
			"3.\n");
			say(QCTNAME(this_player()) + " pays for a room "+
			"and the innkeeper hands "
			+ this_player()->query_objective() + " a key.\n");
		}
		write("You pay "+ text(result[0 .. NUM - 1])+".\n");
		if (change)
		write("You get "+ change + " as change.\n");
		rent3 = 1;
		return 1;
	}
	if (str == "room 4")
	{
		if (present("_samorgan_room_key", this_player()))
		{
			write("You have already rented a room.\n");
			return 1;
		}
		if (rent4 == 1)
		{
			write("The innkeeper says: Room 4 has already "+
			"been rented.\n");
			return 1;
		}
		if (sscanf(str, "%s with %s and get %s", what, for_c,
		get_c) != 3)
		{
			if (sscanf(str, "%s with %s", what, for_c) != 2)
			what = str;
		}
		key4 = clone_object(INN_OBJ + "key4");
		price = key4->query_prop(OBJ_I_VALUE);
		result = pay(price, this_player(), for_c, 0, 0, get_c);
		if (sizeof(result) == 1)
		{
			key4->remove_object();
			return 0;
		}
		if (key4->move(this_player()))
		{
			write("The key is too heavy and you drop it on "+
			"the floor.\n");
			say(QCTNAME(this_player())+ " drops something.\n");
			key4->move(environment(this_player()));
		}
		else
		{
			write("The innkeeper hands you a key to room "+
			"4.\n");
			say(QCTNAME(this_player()) + " pays for a room "+
			"and the innkeeper hands "
			+ this_player()->query_objective() + " a key.\n");
		}
		write("You pay "+ text(result[0 .. NUM - 1])+".\n");
		if (change)
		write("You get "+ change + " as change.\n");
		rent4 = 1;
		return 1;
	}
	if (str == "room 5")
	{
		if (present("_samorgan_room_key", this_player()))
		{
			write("You have already rented a room.\n");
			return 1;
		}
		if (rent5 == 1)
		{
			write("The innkeeper says: Room 5 has already "+
			"been rented.\n");
			return 1;
		}
		if (sscanf(str, "%s with %s and get %s", what, for_c,
		get_c) != 3)
		{
			if (sscanf(str, "%s with %s", what, for_c) != 2)
			what = str;
		}
		key5 = clone_object(INN_OBJ + "key5");
		price = key5->query_prop(OBJ_I_VALUE);
		result = pay(price, this_player(), for_c, 0, 0, get_c);
		if (sizeof(result) == 1)
		{
			key5->remove_object();
			return 0;
		}
		if (key5->move(this_player()))
		{
			write("The key is too heavy and you drop it "+
			"on the floor.\n");
			say(QCTNAME(this_player())+ " drops something.\n");
			key5->move(environment(this_player()));
		}
		else
		{
			write("The innkeeper hands you a key to room "+
			"5.\n");
			say(QCTNAME(this_player()) + " pays for a room "+
			"and the innkeeper hands "
			+ this_player()->query_objective() + " a key.\n");
		}
		write("You pay "+ text(result[0 .. NUM - 1])+".\n");
		if (change)
		write("You get "+ change + " as change.\n");
		rent5 = 1;
		return 1;
	}
	if (str == "room 6")
	{
		if (present("_samorgan_room_key", this_player()))
		{
			write("You have already rented a room.\n");
			return 1;
		}
		if (rent6 == 1)
		{
			write("The innkeeper says: Room 6 has already "+
			"been rented.\n");
			return 1;
		}
		if (sscanf(str, "%s with %s and get %s", what, for_c,
		get_c) != 3)
		{
			if (sscanf(str, "%s with %s", what, for_c) != 2)
			what = str;
		}
		key6 = clone_object(INN_OBJ + "key6");
		price = key6->query_prop(OBJ_I_VALUE);
		result = pay(price, this_player(), for_c, 0, 0, get_c);
		if (sizeof(result) == 1)
		{
			key6->remove_object();
			return 0;
		}
		if (key6->move(this_player()))
		{
			write("The key is too heavy and you drop it "+
			"on the floor.\n");
			say(QCTNAME(this_player())+ " drops something.\n");
			key6->move(environment(this_player()));
		}
		else
		{
			write("The innkeeper hands you a key to room "+
			"6.\n");
			say(QCTNAME(this_player()) + " pays for a room "+
			"and the innkeeper hands "
			+ this_player()->query_objective() + " a key.\n");
		}
		write("You pay "+ text(result[0 .. NUM - 1])+".\n");
		if (change)
		write("You get "+ change + " as change.\n");
		rent6 = 1;
		return 1;
	}
	notify_fail("Which room do you wish to rent?\n");
	return 0;
}

void no_rent(string str)
{
	rent1 = 0;
	return;
}

void no_rent2(string str)
{
	rent2 = 0;
	return;
}

void no_rent3(string str)
{
	rent3 = 0;
	return;
}

void no_rent4(string str)
{
	rent4 = 0;
	return;
}

void no_rent5(string str)
{
	rent5 = 0;
	return;
}

void no_rent6(string str)
{
	rent6 = 0;
	return;
}

int
lay_bar(string str)
{
	if((str == "head on bar") || (str == "bar") || (str =="on bar"))
	{
		write("You lay your head on the bar for a moment.\n");
		/* This what others in room see. */
		say(QCTNAME(TP)+" lays "+HIS(TP)+" head on the bar for "+
		"a moment.\n");
		return 1;
	}
	if((str == "head on table") || (str == "table") || (str =="on table"))
	{
		write("You lay your head on the table for a moment.\n");
		
                /* This what others in room see. */
                say(QCTNAME(TP)+" lays "+HIS(TP)+" head on the table for "+
                "a moment.\n");
                return 1;
        }
        else
        {
		notify_fail("Lay what?\n");
		return 0;
	}
}

public void
init()
{
	::init();
	init_tavern();
	init_fire();
	init_seat();
	add_action(check_out, "check");
	add_action(rent_room, "rent");
	add_action(lay_bar, "lay");
	add_action(lay_bar, "rest");
}
