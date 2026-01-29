/* /d/Faerun/guilds/fire_knives/rooms/sh.c
 *
 * Shop in the cellar
 *
 * Nerull 2019
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <money.h>
#include "../guild.h";

inherit FIREKNIVES_STD_ROOM;

int alchemyset_available;
int cuffed_gloves_available;
int cuffed_boots_available;
int belt_available;
int wristsheaths_available;
int corpsepole_available;

static object  merchant;

//Items for cloning
public string alchemyset_str = FIREKNIVES_GUILD_DIR + "obj/alchemy_set.c";
public string cuffed_gloves_str = FIREKNIVES_GUILD_DIR + "obj/cuffed_gloves.c";
public string cuffed_boots_str = FIREKNIVES_GUILD_DIR + "obj/cuffed_boots.c";
public string belt_str = FIREKNIVES_GUILD_DIR + "obj/belt.c";
public string wristsheaths_str = FIREKNIVES_GUILD_DIR + "obj/fire_wristsheaths.c";
public string corpsepole_str = FIREKNIVES_GUILD_DIR + "obj/fireknives_pole_ob.c";


/*
 * Function name: read_buylist
 * Description  : Function to show what's for sale.
 */
int
read_buylist(string str)
{
    if (alchemyset_available <= 0 && cuffed_gloves_available <= 0 && corpsepole_available <= 0 && cuffed_boots_available <= 0 && belt_available <= 0 && wristsheaths_available <= 0)
    {
         write(""
         +"    The display table is currently empty.\n");
         return 1;
    }
    
    write("The display table contains the following items for sale:\n");
    write("\n");
    
    if (alchemyset_available > 0)
    {
        write("    Alchemy set ["+alchemyset_available+"] 8000 cc\n");
    }
    
    if (cuffed_boots_available > 0)
    {
        write("    Cuffed leather boots ["+cuffed_boots_available+"] 3500 cc\n");
    }
    
    if (cuffed_gloves_available > 0)
    {
        write("    Cuffed leather gloves ["+cuffed_gloves_available+"] 3500 cc\n");
    }
    
    if (belt_available > 0)
    {
        write("    Black leather belt ["+belt_available+"] 3000 cc\n");
    }
	
	if (wristsheaths_available > 0)
    {
        write("    Pair of jet-black leather wristsheaths ["+wristsheaths_available+"] 5000 cc\n");
    }
	
	if (corpsepole_available > 0)
    {
        write("    Large wooden pole ["+corpsepole_available+"] 2000 cc\n");
    }
	
    write("\n");

    return 1;
}


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_fireknives_room()
{
    setuid();
    seteuid(getuid());
    
    add_prop(ROOM_I_INSIDE, 1);

    set_short("Black Market Liaison");
    
    set_long("A small encloseted marquee-like space within the cellar. "
    +"The otherwise cold, stone walls are covered in heavy velvet drapes "
    +"adorned with symbols and other ritualistic depictions. The "
    +"atmosphere gives the air of uniqueness and exoticness, reflecting "
    +"the influence of various cultures across the realms assembled "
    +"via the manifold trinkets and souvenirs placed on the "
    +"shelves and display table behind which the liaison rests.\n");
    
    add_item(({"wall", "walls"}),
    "The cold, stone walls and the humidity they expire are "
    +"covered in heavy velvet drapes which cut off their influence "
    +"and give the sense of being somewhere more comfortable.\n");
    
    add_item(({"cellar"}),
    "The cellar is composed by cell-like passageways throughout "
    +"which tunnels lead into areas such as this one.\n");
    
    add_item(({"drapes", "velvet drapes"}),
    "The drapes are thick, heavy, and yet velvet smooth. Their "
    +"fabric absorbs the coldness and keeps the room warm and dry. "
    +"They are decorated with strange symbols and depictions of "
    +"things unknown to you.\n");
    
    add_item(({"depictions", "symbols"}),
    "Try as you might you cannot decipher the meaning of the "
    +"symbols, though they do seem familiar nonetheless. It's as "
    +"if the weavings had been made by recondite tailors in the "
    +"realms.\n");
    
    add_item(({"atmosphere", "space"}),
    "The atmosphere created within this space is one of warmth "
    +"and silence, and being here amidst all that surrounds you "
    +"doesn't seem to be something to be taken for granted.\n");
    
    add_item(({"trinkets", "souvenirs", "vases", "pieces"}),
    "Trinkets and souvenirs are on display across the room, ranging "
    +"from unique vases to pieces of armour from well-known warriors. "
    +"Each and every article tells a story which perhaps the one who "
    +"acquired them would know more about.\n");
    
    add_item(({"display", "glass"}),
    "The display is surfaced by a thin yet strong layer of glass "
    +"covering items of an even rarer nature than the ones on the "
    +"shelves, hinting at their exclusivity or novelty. You may "
    +"<check display table> to see what is currently for sale.\n");
    
    add_item(({"shelves", "shelf"}),
    "The shelves are seldom yet meaningful. They are made of a dark "
    +"rosewood, and seem quite sturdy and well-kept.\n");
    
    add_item(({"table", "display table"}),
    "Of a wood similar to the shelves', the display table is sturdy and "
    +"elegant. A layer of glass covers its display. You may "
    +"<check display table> to see what is currently for sale\n");
 
    
    add_cmd_item(  ({"display table"}),"check","@@read_buylist");

    
    add_exit(FIREKNIVES_ROOMS_DIR + "c3.c", "west");
    
    alchemyset_available = 1;

    reset_faerun_room();
}


/*
 * Function name: inn_hook_cant_pay()
 * String       : price of the item
 * Description  : What happens when you can't buy an item
 */
int inn_hook_cant_pay(int price)
{
    write("You haven't got enough money to pay for your order.\n");
    return 0;
}


/*
 * Function name: inn_hook_player_buys()
 * String       : price of the item
 * Description  : What happens when you buy an item
 */
int inn_hook_player_buys(int price)
{
    write("You pay "
    + price + " copper to the the shady vigilant man "
    +"for the merchandize.\n");

    say(QCTNAME(this_player()) + " buys something "
    +"from the shady vigilant man.\n");
    return 0;
}


/*
 * Function name: inn_hook_syntax_failure()
 * String       : words
 * Description  : Failure if you type the wrong syntax
 */
int inn_hook_syntax_failure(string str)
{
    write("What would you like to buy?\n");
    return 0;
}

/*
 * Function name: inn_hook_num_failure()
 * String       : number of items
 * Description  : Failure if you try to buy too much
 */
int inn_hook_num_failure(int num)
{
    write("You cannot buy more than one merchandize "
    +"at a time.\n");
    return 0;
}


/*
 * Function name: order()
 * String       : the item to purchase
 * Description  : Function to allowing buying of items.
 */
int order(string str)
{
    string *words;
    int num, tmp, i, price, item;
    object ob;

    if (!str)
    {
        return inn_hook_syntax_failure(str);
    }

    // Can't buy if none is present.
    if (alchemyset_available <= 0)
    {
        write("There is no such item available! Check again later.\n");
        return 1;
    }
    
    if (belt_available <= 0)
    {
        write("There is no such item available! Check again later.\n");
        return 1;
    }
    
    if (wristsheaths_available <= 0)
    {
        write("There is no such item available! Check again later.\n");
        return 1;
    }
    
    if (cuffed_boots_available <= 0)
    {
        write("There is no such item available! Check again later.\n");
        return 1;
    }
    
    if (corpsepole_available <= 0)
    {
        write("There is no such item available! Check again later.\n");
        return 1;
    }
    
    if (corpsepole_available <= 0)
    {
        write("There is no such item available! Check again later.\n");
        return 1;
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

    if (num > 1)
    {
        return inn_hook_num_failure(num);
    }

    switch(str)
    {
        case "alchemy set":
        case "set":
        case "alchemyset":
            ob = clone_object(alchemyset_str);
            price = num * 8000;
            
            item = 1;

            //alchemyset_available = alchemyset_available -1;
            break;
        case "belt":
        case "black leather belt":
        case "leather belt":
        case "black belt":
            ob = clone_object(belt_str);
            price = num * 3000;
            
            item = 2;

            //belt_available = belt_available -1;
			break;
		case "wristsheath":
        case "wristsheaths":
        case "jet-black wristsheaths":
            ob = clone_object(wristsheaths_str);
            price = num * 5000;
            
            item = 3;

            //wristsheaths_available = wristsheaths_available -1;
            break;
        case "boots":
        case "cuffed leather boots":
        case "cuffed boots":
        case "leather boots":
            ob = clone_object(cuffed_boots_str);
            price = num * 3500;
            
            item = 4;

            //cuffed_boots_available = cuffed_boots_available -1;
            break;
        case "gloves":
        case "cuffed leather gloves":
        case "cuffed gloves":
        case "leather gloves":
            ob = clone_object(cuffed_gloves_str);
            price = num * 3500;
            
            item = 5;

            //cuffed_gloves_available = cuffed_gloves_available -1;
            break;
	    case "pole":
        case "large pole":
        case "large wooden pole":
        case "wooden pole":
            ob = clone_object(corpsepole_str);
            price = num * 2000;
              
            item = 6;;    

            //corpsepole_available = corpsepole_available -1;
            break;
        default:
            return inn_hook_syntax_failure(str);
    }
    
    switch(item)
    {
        case 1:     
        alchemyset_available = alchemyset_available -1;
        break;
        
        case 2:     
        belt_available = belt_available -1;
        break;
        
        case 3:     
        wristsheaths_available = wristsheaths_available -1;
        break;
        
        case 4:     
        cuffed_gloves_available = cuffed_gloves_available -1;
        break;
        
        case 5:     
        cuffed_gloves_available = cuffed_gloves_available -1;
        break;
        
        case 6:     
        corpsepole_available = corpsepole_available -1;
        break;
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


void
reset_faerun_room()
{
    ::reset_faerun_room();
    
    if (random(100) > 50)
    {
        alchemyset_available = alchemyset_available + 1;
        
        if (alchemyset_available >= 3)
        {
            alchemyset_available = 3;
        }
        
        belt_available = belt_available + 1;
        
        if (belt_available >= 7)
        {
            belt_available = 7;
        }
		
		wristsheaths_available = wristsheaths_available + 1;
        
        if (wristsheaths_available >= 4)
        {
            wristsheaths_available = 4;
        }
        
        cuffed_boots_available = cuffed_boots_available + 1;
        
        if (cuffed_boots_available >= 7)
        {
            cuffed_boots_available = 7;
        }
        
        cuffed_gloves_available = cuffed_gloves_available + 1;
        
        if (cuffed_gloves_available >= 7)
        {
            cuffed_gloves_available = 7;
        }
		
		corpsepole_available = corpsepole_available + 1;
        
        if (corpsepole_available >= 7)
        {
            corpsepole_available = 7;
        }
    }
    
    if (!merchant)
    {
        merchant = clone_object(FIREKNIVES_GUILD_DIR + "npc/shady_man");
        merchant->move(this_object(), 1);
    }
}


/*
 * Function name: init()
 * Description  : initilizes the buy and out commands.
 */
void init()
{
    ::init();
    add_action(order, "buy");
}
