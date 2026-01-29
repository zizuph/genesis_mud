/* /d/Faerun/guilds/black_flame/rooms/bf_shop.c
 *
 * Nerull 2022
 *
 */

inherit "/d/Faerun/guilds/black_flame/rooms/std/bf_std_room";

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <money.h>
#include "../guild.h";


//Items for cloning
//public string cleaner_str = BF_GUILD_DIR + "obj/c_cleaner.c";
public string water_str = BF_GUILD_DIR + "obj/fire_water.c";
public string set_str = "/d/Faerun/alchemy/large_alchemy_set.c";


/*
 * Function name: read_buylist
 * Description  : Function to show what's for sale.
 */
int
read_buylist(string str)
{
    write("\n");
    write("+-----------------------------------------------------+\n");
    write("|                 Name                 |  Price       |\n");
    write("+-----------------------------------------------------+\n");
    write("| A large alchemy set                  |  8000 Copper |\n");
   // write("| A round black amulet                 |  8000 Copper |\n");
    write("| A jar of Fire water                  |  4000 Copper |\n");
    write("+-----------------------------------------------------+\n");
    write("\n");

    return 1;
}


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_bf_room()
{
    seteuid(getuid());
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    
    set_short("Alchemy supply shop");
    
    set_long("This chamber is surprisingly clean with "
    +"just a few shelves along the walls, displaying the "
    +"most important alchemical items gathered into "
    +"convenient sets for purchase. A long wooden counter "
    +"splits the room in half, effectively keeping the "
    +"customers on one side, and the shopkeeper with his "
    +"goods on the other. You notice a small store room to "
    +"the northeast behind the counter. You think you see "
    +"some components and other equipment through the door, "
    +"before the shopkeeper blocks your view and glares at "
    +"you disapprovingly. There is a plaque here that describes "
    +"the buyable content.\n");
    
    add_item(({"shelves"}),
        "The shelves are very clean, not a speck of dust, "
        +"and the alchemy kits upon them are meticulously "
        +"placed to display their contents.\n");
        
    add_item(({"sets"}),
        "Each set contains necessities for the serious "
        +"alchemist, such as burners, beakers, flasks and "
        +"room for reagents and other components.\n");
        
    add_item(({"wall", "walls"}),
        "The shopkeeper have taken the time and effort "
        +"to actually cover the walls in stone tiling, making "
        +"this room look cleaner and more luxurious than "
        +"all the other rooms.\n");
        
    add_item(({"counter"}),
        "This is a finely crafted wooden counter, running "
        +"along the entire room, splitting it in half. It’s very "
        +"well sanded and polished, and you can almost see your "
        +"own reflection in the shiny surface.\n");
        
    add_item(({"store room"}),
        "You can glimpse some very meticulously ordered and "
        +"marked shelves in the northeast direction. The "
        +"shopkeeper glares at you while you stare intently "
        +"through the opening.\n");
        
    add_item(({"shopkeeper"}),
        "A hooded and hunchbacked figure, dressed in a dark "
        +"coat littered with stains and holes. You see "
        +"various pendants, medallions and crystals hanging "
        +"from iron chains around its neck and from various "
        +"pockets on its clothes. As it shuffles about, you "
        +"notice that it is walking with bare feet.\n");
        
    add_item(({"plaque"}), "This is an old wooden board serving "
    +"as a plaque. It contains a list of ingredients that is used "
    +"for alchemy. Read it.\n");
    
    
    add_cmd_item(  ({"plaque"}),"read","@@read_buylist");
        
    
    add_exit(BF_ROOMS_DIR + "bf_train", "southwest");
       
   
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
    + price + " copper for the alchemy ingredient.\n");

    say(QCTNAME(this_player()) + " buys some "
    +"alchemy ingredient.\n");
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
        case "set":
        case "alchemy set":
        case "large alchemy set":
        case "large set":
            ob = clone_object(set_str);
            
            price = num * 8000;
            
            break;
        
        /*case "amulet":
        case "black amulet":
            ob = clone_object(cleaner_str);
            
            price = num * 8000;
            
            break;*/
            

        case "water":
        case "fire water":
            ob = clone_object(water_str);
            
            price = num * 4000;
            
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


public void
init()
{
    ::init();
    
    add_action(order, "buy");
}
