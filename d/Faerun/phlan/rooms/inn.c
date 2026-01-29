/* /d/Faerun/phlan/rooms/inn.c
 *
 * Nerull 2019
 *
 * Modified for phlan Tharizdun, 2021
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <money.h>
#include <language.h>
#include <macros.h>
#include <defs.h>



inherit BASE_PHLAN_INDOOR;

/*
*   Items for cloning
*/

    public string phlan_plowmans_lunch = OBJ_DIR + "/plmlnch.c";
    public string phlan_seafood_bisque = OBJ_DIR + "/sfdbsq.c";
    public string phlan_swordfish_steak = OBJ_DIR + "/swfstk.c";
    public string phlan_water = OBJ_DIR + "/water.c";
    public string phlan_white_wine = OBJ_DIR + "/whitewine.c";
    public string phlan_red_wine = OBJ_DIR + "/redwine.c";
    public string crown_key = OBJ_DIR + "/crown_key.c";

object chef;


/*
 * Function to display the menu in Broken Crown Inn
 */

int
read(string str)
{
    write(""
      +"   Beverages:                      \n"
      +"   Water                      10 cc\n"
      +"   White Wine                 72 cc\n"  
      +"   Red Wine                   72 cc\n"      
      +"\n"
      +"   Entrees:                        \n"
      +"   Plowman's Lunch            25 cc\n"
      +"   Seafood Bisque             80 cc\n"
      +"   Swordfish Steak           160 cc\n"
      +"\n"
      +"   Room Key                  144 cc\n"
      +"\n"
      +"You can only order a maximum of 20 items at a time.\n"
      +"\n"
      );
      
    return 1;
}

int
check_keyholders()
{
    object key;
    if(!(key=present("_crown_key_inn",this_player())))
    {    
    write("You don't have the key you need to go upstairs!\n");
    return 1;
    }
    
    return 0;
}
    
/*
*   Check to see if player is on quest
*/

int
check_quest()
{
    if(this_player()->query_prop("_phlan_tour4_start"))
    {
        this_player()->remove_prop("_phlan_tour4_start");
        this_player()->catch_msg("You are ready to return to Daari for your reward.\n");
        this_player()->add_prop("_phlan_tour4_prop", 1);        
        return 0;
    }
} 

/*
 * Description  : Constructor, redefine this to configure your room
 */
 
public void
create_phlan_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("Inside the Cracked Crown Inn");
    
    set_long("Inside the door you find a very comfortable"
    +" inn. Tantalizing smells of savory foods and"
    +" hardwood smoke tease your senses. Square tables"
    +" of polished maple are spaced to both give privacy"
    +" and serve a maximum amount of customers. Comfortable"
    +" chairs surround each table. An open archway in the south"
    +" south leads to what must be the kitchen while a staircase"
    +" gives access to the private rooms above. Lamps mounted"
    +" in sconces on the walls light the room while producing no"
    +" smoke. There is a menu prominently posted on the wall.\n");
    
    add_item(({"door"}),
    "The door lies to the north leading back out to the street.\n");
 
    add_item(({"inn"}),
    "This is the Cracked Crown Inn. Saying it is the best inn in"
    +" town is hollow praise as it is the only inn in town, but"
    +" even in a bigger town it would earn that accolade.\n");

    add_item(({"room", "rooms"}),
    "The inn offers private sleeping arrangements upstairs.\n");
 
    add_item(({"smell", "smells"}),
    "The savory smells of seafoods and burning applewood fill"
    +" your senses and make your mouth water.\n");
 
    add_item(({"wall","walls"}),
    "The walls are made of cedar, reddish hued with black knots."
    +" There are several lamps mounted in sconces providing light.\n");
 
    add_item(({"floor", "ground"}),
    "The rough wooden floor is clean but shows years of use.\n");

    add_item(({"ceiling"}),
    "The ceiling is of knotty cedar, rich red in color. The high peak"
    +" makes the room seem even more spacious than its already"
    +" accommodating size.\n");

    add_item(({"lamp","lamps"}),
    "Polished brass lamps bur brightly in their wrought iron"
    +" sconces. They produce no smoke.\n");

    add_item(({"sconce","sconces"}),
    "The scones are of blackened wrought iron, providing an"
    +" attractive contrast to the polished brass of the lamps.\n");

    add_item(({"kitchen"}),
    "You can catch glimpses of a busy kitchen through the archway. The"
    +" smells of cooking foods waft out tantalizingly.\n");

    add_item(({"archway"}),
    "An archway in the southern wall gives glimpses of the kitchen.\n"
    +" It is chaotic, but seems to be an organized chaos.\n");

    add_item(({"staircase"}),
    "The wooden staircase goes up to the sleeping rooms on the upper level."
    +" You will need a key to have access to the second floor.\n");
    
    add_item(({"chair", "chairs"}),
    "The sturdy wooden chairs are not padded but look as if they would be"
    +" comfortable for the duration of a long meal.\n"); 

    add_item(({"table", "tables"}),
    "The spacious and sturdy tables can hold up to eight people. They are "
    +" spaced far enough apart to allow some privacy.\n");    

    add_item( ({"sign","menu"}), 
    "The menu is burned into a panel of the same cedar as the walls. The"
    +" artful cursive lettering can be <read> to see what is being"
    +" offered.\n");
    
    add_room_tell("A server brings out a platter of food and quickly returns"
        +" to the kitchen."); 
    
    add_cmd_item(  ({"sign","menu"}),"read","@@read");

    add_exit(ROOM_DIR + "road11", "north");
    add_exit(ROOM_DIR + "innkit", "south"); 
    add_exit(ROOM_DIR + "innbed", "up", check_keyholders);    

    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
    
    if (!chef)
    {
        chef = clone_object(NPC_DIR + "chef");
        chef->move(this_object(), 1);
    }
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
    write("You place an order and pay " + price + " copper. "
          +"You quickly receive your order.\n");
    say(QCTNAME(this_player()) + " places an order.\n");
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
            ob = clone_object(phlan_water);
            price = num * 10;
            break;
        case "white wine":
        case "white wines":
            ob = clone_object(phlan_white_wine);
            price = num * 72;
            break;
        case "red wine":
        case "red wines":
            ob = clone_object(phlan_red_wine);
            price = num * 72;
            break;
        case "plowman's lunch":
        case "plowman's lunches":
        case "lunch":
        case "lunches":
            ob = clone_object(phlan_plowmans_lunch);
            price = num * 25;
            break;
        case "seafood bisque":
        case "seafood bisques":
        case "seafood":
        case "bisque":        
        case "bisques":
            ob = clone_object(phlan_seafood_bisque);
            price = num * 80;
            break;
        case "swordfish steak":
        case "swordfish steaks":
        case "steak":
        case "steaks":
        case "swordfish":        
            ob = clone_object(phlan_swordfish_steak);
            price = num * 160;
            break;
        case "room key":
        case "room keys":
        case "key":
        case "keys":        
        case "crown key":
        case "crown keys":
            ob = clone_object(crown_key);
            price = num * 144;
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
 * Function that allows the player to sit at a table
 */
 
int action_sit(string str)
{
    if(this_player()->query_prop("_sitting_at_table"))
    {
        write("But you are already sitting at a table!\n");
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
        this_player()->catch_msg("You sit down on one of the sturdy"
        +" chairs at a table.\n");
        say(QCTNAME(this_player()) + " sits down in one of the sturdy "
        +"chairs at a table.\n");
        this_player()->add_prop("_sitting_at_table", 1);
        this_player()->add_prop(LIVE_S_EXTRA_SHORT," who is sitting at a "
        +" table");
        return 1;
    }


    else
    {
        this_player()->catch_msg("Would you like to sit at a table?\n");
        return 1;
    }

    return 1;
}


/*
 * Function that allows the player to stand from a table
 */
 
int
action_stand(string str)
{
    if(str == "up")
    {
        if(this_player()->query_prop("_sitting_at_table"))
        {
            this_player()->catch_msg("You stand up from your seat at the table.\n");
            say(QCTNAME(this_player())+" stands up from the table.\n");
            this_player()->remove_prop("_sitting_at_table");
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
                
    if(ob->query_prop("_sitting_at_table"))
    {
        ob->catch_msg("You stand up from the table before leaving.\n");
        say(QCTNAME(ob) + " stands up from the table before "
        +"leaving the inn.\n");
        ob->remove_prop(LIVE_S_EXTRA_SHORT);
        ob->remove_prop("_sitting_at_table");
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
