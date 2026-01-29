/* /d/Faerun/phlan/rooms/phlanpub.c
 *
 * Nerull 2019
 *
 *   Tharizdun 2021
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <money.h>
#include <language.h>
#include <macros.h>
#include <defs.h>



inherit BASE_PHLAN_INDOOR;

//Items for cloning


  public string phlan_pale_ale = ROOM_DIR + "/obj/ale.c";
  public string phlan_apricot_brandy = ROOM_DIR + "/obj/apricot_brandy.c";
  public string phlan_amontillado_sherry = ROOM_DIR + "/obj/sherry.c";
  public string phlan_spiced_rum = ROOM_DIR + "/obj/spiced_rum.c";
  public string phlan_bourbon_whiskey = ROOM_DIR + "/obj/whiskey.c";

object barfly1;
object brandi;


/*
 * Function to display the menu at the Bitter Blade Pub
 */

int
read(string str)
{
    write(""
      +"   Drinks:                         \n"
      +"   Pale Ale                   12 cc\n"
      +"   Amontillado Sherry         60 cc\n"  
      +"   Spiced Rum                 72 cc\n"  
      +"   Apricot Brandy             96 cc\n"      
      +"   Bourbon Whiskey           120 cc\n"
      );
      
    return 1;
}


/*
 * Function name: create_phlan_room
 * Description  : Constructor, redefine this to configure your room
 */
 
public void
create_phlan_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("Inside the Bitter Blade Pub");
    
    set_long("Inside the door you find an energetic, but not"
    +" chaotic room. Customers pop in and out on a regular basis"
    +" for a quick drink or to get something to take with them."
    +" There are multiple tables with chairs if you wish to sit"
    +" and servers that quickly fill your drink order." 
    +" A mural covers the entire southern wall while the east"
    +" and west have round curtained windows that can let in sunlight"
    +" and a breeze. The door back out to the street lies to the"
    +" north. There is a menu prominently posted on the wall.\n");
    
    add_item(({"door"}),
    "The door lies to the north leading back out to the street.\n");
 
    add_item(({"pub"}),
    "This is the Bitter Blade Pub. It is pretty much what you would"
    +" expect of a harbour town pub, but a little... less. There are"
    +" no rowdy drunken sailors groups singing sea shanties, only"
    +" frequent customers and humble surroundings.\n");
 
    add_item(({"wall","walls"}),
    "The walls are of a knotty wood, though you cannot tell what kind."
    +" Years of less than thorough cleaning and pipe smoke have given"
    +" them an indelible yellowish tinge.\n");
 
    add_item(({"floor", "ground"}),
    "The rough wooden floor scratched and marked by years of sliding"
    +" tables and chairs and the heels of countless boots.\n");

    add_item(({"ceiling"}),
    "The ceiling is a bit dusty but not offensively so. It has the"
    +" same yellow nicotine stains as the walls. Suspended from the"
    +" ceiling are several nautical lamps providing light to the room."
    +" Fishing nets hang in the corners providing a seafaring flair.\n");

    add_item(({"lamp","lamps"}),
    "Several brass nautical style lamps are suspended from the ceiling. The"
    +" smoke they emit indicate they are burning whale oil of some kind.\n");

    add_item(({"stain","stains"}),
    "The stains have turned the walls and ceilinggs a yellowish tone."
    +" They are from years of pipe smoke.\n");
    
    add_item(({"chair", "chairs"}),
    "The chairs have thick, blocky legs and plain seats. The backs are"
    +" a weave of netting between two upright supports.\n");

    add_item(({"leg", "legs"}),
    "The legs are square and blocky but definitely sturdy.\n");   

    add_item(({"table", "tables"}),
    "The scratched and ringed surfaces indicate decades of mugs "
    +" and flagons being toasted above, slammed into and spilled"
    +" on them. They have thick blocky wooden legs.\n");   

    add_item( ({"sign","menu"}), 
    "The menu is lettered on parchment and looks fairly new. It must be"
    +" replaced frequently.\n");
    
    add_item( ({"window","windows", "round window", "round windows", "curtained windows"}), 
    "At closer inspection these appear to be portholes, probably taken from"
    +" an old ship of some kind. There are plain cloth curtains that can be"
    +" pulled across them to allow or block the light as needed.\n"); 

    add_item( ({"curtain","curtains", "cloth curtains"}), 
    "The curtains are of plain cloth dyed black.\n");    
    
    add_item( ({"mural"}), 
    "This solves a mystery, if there really was one. The mural shows an"
    +" older style sailing ship plying the Bloodsea, avoiding pirates,"
    +" besting a dragon turtle and most of the other tall tales sailors"
    +" share. The name proudly displayed on the ship's prow is The"
    +" Bitter Blade.\n");     
    
    add_room_tell("A breeze rustles the curtains, causing the lamps to sway."); 
    add_room_tell("A patron lights a pipe, briefly giving off a scent of sulfur"
        +" as the match flares.");     
    
    add_cmd_item(  ({"sign","menu"}),"read","@@read");

    add_exit(ROOM_DIR + "road18", "north");
    
    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
    
/*
*   Bar patrons
*/    
    
    if (!barfly1)
    {
        barfly1 = clone_object(NPC_DIR + "barfly1");
        barfly1->move(this_object(), 1);
    }
    
    if (!brandi)
    {
        brandi= clone_object(NPC_DIR + "brandi");
        brandi->move(this_object(), 1);
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
          +" A server quickly brings you your beverages.\n");
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
 * Function for ordering drinks
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


    switch(str)
    {
        case "ale":
        case "ales":
            ob = clone_object(phlan_pale_ale);
            price = num * 12;
            break;
        case "sherry":
        case "sherries":
            ob = clone_object(phlan_amontillado_sherry);
            price = num * 60;
            break;
        case "rum":
        case "rums":
            ob = clone_object(phlan_spiced_rum);
            price = num * 72;
            break;
        case "brandy":
        case "brandies":
            ob = clone_object(phlan_apricot_brandy);
            price = num * 96;
            break;
        case "whiskey":
        case "whiskeys":
            ob = clone_object(phlan_bourbon_whiskey);
            price = num * 120;
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
        this_player()->catch_msg("You sit down on one of the wooden"
        +" chairs at a table.\n");
        say(QCTNAME(this_player()) + " sits down in one of the wooden"
        +" chairs at a table.\n");
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
 * Function that allows the player to stand from a table or the bar
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
