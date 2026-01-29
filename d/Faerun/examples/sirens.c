/* /d/Ravenloft/core/darkon/martira_bay/sirens.c
 *
 *  Siren   s Lament in the city of Martira Bay.
 *
 *  Nerull, 2014
 *  Updated by Leia, November 2014 to add Descs, items,
 *  menu.
 *
 */

#include "defs.h";
#include <stdproperties.h>
#include <money.h>
#include <language.h>
#include <macros.h>
inherit MAR_STD_ROOM;

object key;

// Defines added by Leia so that they can quickly be grabbed later.
// Room descs
public string sir_short = "At the Siren's Lament Inn";
public string sir_long = "You have entered the Siren's Lament Inn. "
    +"Not known as a high establishment, this is the type of inn for "
    +"those of a shadier nature. The cracks between the floorboards "
    +"are caked with mud, and the floor itself is awash with the salt "
    +"of the nearby bay. The pungent smell of food spiced heavily to "
    +"mask flavour combined with tobacco smoke is less than "
    +"appealing. All around are tables filled with patrons who try "
    +"their hardest to avoid eye contact while playing games of "
    +"chance. Before you stands a bar, and on the bar a sign that "
    +"lists the food and spirits of the day.\n";

//Item descs
public string sir_walls = "The walls here contain various paintings of "
    +"local landmarks that were clearly commissioned from less than "
    +"well-known artists. Near the door there are two windows on either "
    +"side, the only other links from this establishment to the outside "
    +"world.\n";
public string sir_windows = "The windows are caked with grime so thick "
    +"that it is nearly impossible to see through them. It is possible"
    +"to vaguely see the mist that permeates the streets.\n";
public string sir_tables = "The tables within the inn are almost "
    +"completely seated with only a few open spots left. Most of the "
    +"patrons have their faces buried behind cards, under hoods, or in "
    +"a glass of ale. No one seems to make eye contact except for the "
    +"occasional glance that implores you to look away. There is a "
    +"table in the corner that you might be able to <sit> at.\n";
public string sir_patrons = "There a patrons of all types within the inn. "
    +"They appear to be of all races, shapes, and sizes. None, however, "
    +"appear beyond reproach, and you suspect that many are of "
    +"ill-repute.\n";
public string sir_bar = "The bar sits at the back of the inn, along the "
    +"wall opposite the door. It is around chest high and appears to "
    +"have been crafted from sea worn wood, likely washed ashore from "
    +"boats lost at sea. A sign sits on the bar that lists the daily "
    +"food and drink options. There are some chairs near the bar that "
    +"you might be able to <sit> in.\n";
public string sir_menu = "The sign appears to be framed with the same "
    +"wood the bar was crafted from with a centre of pure slate. There "
    +"are words scribbled on it in chalk. Perhaps you could <read> the "
    +"sign to see what they say.\n";

//Items for cloning
public string sirens_key = MAR + "/obj/sirens_key.c";
public string sir_ale = MAR + "/obj/sir_ale.c";
public string sir_bread_cheese = MAR+ "/obj/sir_bread_cheese.c";
public string sir_grog = MAR + "/obj/sir_grog.c";
public string sir_sailor = MAR + "/obj/sir_sailor.c";
public string sir_stew = MAR + "/obj/sir_stew.c";
public string sir_grub = MAR + "/obj/sir_grub.c";
public string sir_water = MAR + "/obj/sir_water.c";


int
check_keyholders()
{
	if (!(key = present("_sirens_key_inn", this_player())))
	{
		write("You don't have the key you need to go upstairs!\n");

		return 1;
	}

	return 0;
}


/*
 * Function to display the menu at the Siren's Lament
 */

int
read(string str)
{
    write(""
      +"   Spirits:                        \n"
      +"   Well Water                 10 cc\n"
      +"   Siren's Ale                12 cc\n"
      +"   Martira Bay Grog           72 cc\n"
      +"   The Angry Sailor          100 cc\n"
      +"\n"
      +"   Entrees:                        \n"
      +"   Cheese and Bread           25 cc\n"
      +"   Beef and Vegetable Stew    80 cc\n"
      +"   Grub of the Moment*       160 cc\n"
      +"\n"
      +"   Key to a room             160 cc\n"
      +"\n"
      +"You can only order a maximum of 20 items at a time.\n"
      +"\n"
      +"*Grub of the Moment is a dish that rotates on a\n"
      +"specific time frame. Come back on regularly in order\n"
      +"to experience your selection again.\n"
      );
    return 1;
}

/*
 * Function name: create_mar_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_mar_room()
{
    set_extra_longdesc(MAR_DESCR_MASTER->query_description("sirens"));

    set_short(sir_short);
    set_long(sir_long);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);

    update_longdesc();

    add_item( ({"wall", "walls"}), sir_walls);
    add_item( ({"window","windows"}), sir_windows);
    add_item( ({"tables","table"}), sir_tables);
    add_item( ({"patron","patrons"}), sir_patrons);
    add_item( ({"bar"}), sir_bar);
    add_item( ({"sign","menu"}), sir_menu);
    add_cmd_item(  ({"sign","menu"}),"read","@@read");

    add_exit(MAR + "dock3", "west");
    add_exit(MAR + "sirens_start", "up", check_keyholders);

    add_npc(MAR +"npc/citizen", 2);
    add_npc(MAR +"npc/sirens_bartender", 1);

    reset_room();
}

/*
 * Returns the failure message when a player cannot pay
 */
int inn_hook_cant_pay(int price)
{
    write("You haven't got enough money to pay for your order.\n");
    return 0;
}

/*
 * Returns the purchase message when a player buys an item
 */
int inn_hook_player_buys(int price)
{
    write("You place an order at the bar and pay " + price + " copper. "
          +"You quickly receive your order.\n");
    say(QCTNAME(this_player()) + " places an order at the bar.\n");
    return 0;
}

/*
 * Returns the failure message when a player uses a bad syntax
 */
int inn_hook_syntax_failure(string str)
{
    write("What would you like to buy?\n");
    return 0;
}

/*
 * Returns the failure message when a player orders too much
 */
int inn_hook_num_failure(int num)
{
    write("You cannot order more than 20 items at a time.\n");
    return 0;
}

/*
 * Function for ordering food
 */
int order(string str)
{
    string *words;
    int num, tmp, i, price;
    object ob;

    if (!str)
    {
        return inn_hook_syntax_failure(str);
    }

    words = explode(str, " ");
    num = 1;
    if(sizeof(words) > 1)
    {
        tmp = LANG_NUMW(words[0]);
        if (!tmp)
            sscanf(words[0], "%d", tmp);
        if (tmp > 0)
        {
            num = tmp;
            str = implode(words[1 .. sizeof(words)], " ");
        }
    }

    if (num > 20)
    {
      return inn_hook_num_failure(num);
    }

    switch(str)
    {
        case "water":
        case "waters":
        case "well":
        case "well water":
        case "well waters":
            ob = clone_object(sir_water);
            price = num * 10;
            break;
        case "ale":
        case "ales":
        case "siren's":
        case "siren's ale":
        case "siren's ales":
            ob = clone_object(sir_ale);
            price = num * 12;
            break;
        case "grog":
        case "grogs":
        case "bay":
        case "martira":
        case "martira bay":
        case "martira grog":
        case "martira grogs":
        case "bay grog":
        case "bay grogs":
        case "martira bay grog":
        case "martira bay grogs":
            ob = clone_object(sir_grog);
            price = num * 72;
            break;
        case "sailor":
        case "sailors":
        case "angry":
        case "angries":
        case "angrys":
        case "angry sailor":
        case "angry sailors":
        case "the angry sailor":
        case "the angry sailors":
            ob = clone_object(sir_sailor);
            price = num * 100;
            break;
        case "key":
        case "keys":
        case "roomkey":
        case "room key":
            ob = clone_object(sirens_key);
            price = num * 100;
            break;
        case "bread":
        case "breads":
        case "cheese":
        case "cheeses":
        case "bread and cheese":
        case "bread and cheeses":
            ob = clone_object(sir_bread_cheese);
            price = num * 25;
            break;
        case "beef":
        case "beefs":
        case "vegetable":
        case "vegetables":
        case "stew":
        case "stews":
        case "beef and vegetable":
        case "beef and vegetables":
        case "beef and vegetable stew":
        case "beef and vegetable stews":
            ob = clone_object(sir_stew);
            price = num * 80;
            break;
        case "grub":
        case "grubs":
        case "grub of the moment":
        case "grub of the moments":
        case "grubs of the moment":
        case "grubs of the moments":
            ob = clone_object(sir_grub);
            price = num * 160;
            break;
        default:
            return inn_hook_syntax_failure(str);
    }

    if(!MONEY_ADD(this_player(),-price))
    {
        inn_hook_cant_pay(price);
        return 1;
    }

    inn_hook_player_buys(price);
    ob->set_heap_size(num);
    ob->move(this_player(), 1);
    return 1;
}

/*
 * Function that allows the player to sit at a table or the bar
 */
int action_sit(string str)
{
    if(this_player()->query_prop("_sitting_at_sirens_lament_bar"))
    {
        write("But you are already sitting by the bar!\n");
        return 1;
    }

    if(this_player()->query_prop("_sitting_at_sirens_lament_table"))
    {
        write("But you are already sitting by the bar!\n");
        return 1;
    }

    if(str == "around table" | str == "around the table"
    | str == "at table" | str == "at the table"
    | str == "by table" | str == "by the table"
    | str == "table" | str == "chair around table"
    | str == "in chair around table" | str == "in a chair around the table"
    | str == "chair at table"
    |   str == "in chair at table" | str == "in a chair at the table"
    | str == "chair by table"
    | str == "in chair by table" | str == "in a chair by the table")
    {
        this_player()->catch_msg("You sit down in one of the rickety "
        +"chairs near the table in the corner.\n");
        say(QCTNAME(this_player()) + " sits down in one of the rickety "
        +"chairs near the table in the corner.\n");
        this_player()->add_prop("_sitting_at_sirens_lament_table", 1);
        this_player()->add_prop(LIVE_S_EXTRA_SHORT," who is sitting near a "
        +"corner table");
        return 1;
    }

    if(str == "at bar" | str == "at the bar" | str == "by bar"
    | str == "by the bar" | str == "bar" | str == "chair at bar"
    | str == "in chair at bar" | str == "in a chair at the bar"
    | str == "chair by bar" | str == "in chair by bar"
    | str == "in a chair by the bar")
    {
        this_player()->catch_msg("You sit down in one of the "
        +"rickety chairs near the bar.\n");
        say(QCTNAME(this_player()) + " sits down in a rickety "
        +"chair near the bar.\n");
        this_player()->add_prop("_sitting_at_sirens_lament_bar", 1);
        this_player()->add_prop(LIVE_S_EXTRA_SHORT," who is sitting "
        +"near the bar");
        return 1;
    }

    else
    {
        this_player()->catch_msg("Where would you like to sit? "
        +"By the bar or around the corner table?\n");
        return 1;
    }

    return 1;
}

/*
 * Function that allows the player to stand from a table or the bar
 */
int
action_stand(string str)
{
    if(str == "up")
    {
        if(this_player()->query_prop("_sitting_at_sirens_lament_table"))
        {
            this_player()->catch_msg("You stand up and leave the table.\n");
            say(QCTNAME(this_player())+" stands up from the table.\n");
            this_player()->remove_prop("_sitting_at_sirens_lament_table");
            this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
            return 1;
        }

        if(this_player()->query_prop("_sitting_at_sirens_lament_bar"))
        {
            this_player()->catch_msg("You stand up and leave the bar.\n");
            say(QCTNAME(this_player())+" stands up from the bar.\n");
            this_player()->remove_prop("_sitting_at_sirens_lament_bar");
            this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
            return 1;
        }
    }

    else
    {
        this_player()->catch_msg("Stand? Stand up?\n");
        return 1;
    }

    return 1;
}

/*
 * Function to cleanup props if a player leaves before standing
 */
void leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if(!objectp(to) || !objectp(ob))
      return;
                
    if(ob->query_prop("_sitting_at_sirens_lament_table"))
    {
        ob->catch_msg("You stand up from the table before leaving.\n");
        say(QCTNAME(ob) + " stands up from the table before "
        +"leaving the inn.\n");
        ob->remove_prop(LIVE_S_EXTRA_SHORT);
        ob->remove_prop("_sitting_at_sirens_lament_table");
    }

    if(ob->query_prop("_sitting_at_sirens_lament_bar"))
    {
        ob->catch_msg("You stand up from the bar before leaving.\n");
        say(QCTNAME(ob) + " stands up from the bar before "
        +"leaving the inn.\n");
        ob->remove_prop(LIVE_S_EXTRA_SHORT);
        ob->remove_prop("_sitting_at_sirens_lament_bar");
    }
}



void init()
{
    ::init();
    add_action(order, "buy");
    add_action(order, "order");
    add_action("action_sit", "sit");
    add_action("action_stand", "stand");
}

/*
 * Function name: reset_room()
 * Description  : Resets the room
 */
void
reset_room()
{
    update_longdesc();
}

