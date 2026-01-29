/* /d/Faerun/guilds/fire_knives/rooms/mh.c
 *
 * 
 * Nerull 2019
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <money.h>
#include <language.h>
#include <macros.h>
#include "../guild.h";

inherit FIREKNIVES_STD_ROOM;

//Items for cloning
public string fire_ale = FIREKNIVES_GUILD_DIR + "/obj/fire_ale.c";
public string fire_bread_cheese = FIREKNIVES_GUILD_DIR + "/obj/fire_bread_cheese.c";
public string fire_grog = FIREKNIVES_GUILD_DIR + "/obj/fire_grog.c";
public string fire_death = FIREKNIVES_GUILD_DIR + "/obj/fire_death.c";
public string fire_stew = FIREKNIVES_GUILD_DIR + "/obj/fire_stew.c";
public string fire_cockles = FIREKNIVES_GUILD_DIR + "/obj/fire_cockles.c";
public string fire_grub = FIREKNIVES_GUILD_DIR + "/obj/fire_grub.c";
public string fire_water = FIREKNIVES_GUILD_DIR + "/obj/fire_water.c";
public string fire_rum = FIREKNIVES_GUILD_DIR + "/obj/fire_rum.c";
public string fire_brandy = FIREKNIVES_GUILD_DIR + "/obj/fire_plumbrandy.c";
public string fire_redbeans = FIREKNIVES_GUILD_DIR + "/obj/fire_redbeans_rice.c";

object chef;


/*
 * Function to display the menu at the Siren's Lament
 */

int
read(string str)
{
    write(""
      +"   Spirits:                        \n"
      +"   Well Water                 10 cc\n"
      +"   Ruddock's Ale              12 cc\n"
      +"   Jugular Vein Grog          72 cc\n"
      +"   Black Rum                  72 cc\n"
      +"   Plum Brandy               100 cc\n"
      +"   The Sudden Death          100 cc\n"
      +"\n"
      +"   Entrees:                        \n"
      +"   Cheese and Bread           25 cc\n"
      +"   Cockles and Mussles        25 cc\n"
      +"   Beef and Vegetable Stew    80 cc\n"
      +"   Red beans and Rice         80 cc\n"
      +"   Grub of the Moment*       160 cc\n"
      +"\n"
      +"You can only order a maximum of 20 items at a time.\n"
      +"\n"
      +"*Grub of the Moment is a dish that rotates on a\n"
      +"specific time frame. Come back on regularly in order\n"
      +"to experience your selection again.\n"
      );
      
    return 1;
}


public int
block_check()
{
    if (FIREKNIVES_MASTER->is_occ_fireknife(this_player()->query_name()) == 0)
    {
        if (!this_player()->query_wiz_level())
        {
            write("The guard dogs slowly pace until "
            +"they stand in front of you "
            +"while growling softly, their eyes focused on yours. You decide "
            +"to reconsider your option and take a few steps backwards.\n");

            tell_room(environment(this_player()), QCTNAME(this_player()) 
            +" steps backwards from the dogs as they move in front of "
            + this_player()->query_possessive()
            +", blocking the way.\n", this_player());

            return 1;
        }
    }
      
    write("The guard dogs raise their heads to look at you, then look down "
    +"and turn around in a submissive gesture.\n");
    
    tell_room(environment(this_player()), QCTNAME(this_player())
    +" receives a furtive glance from the dogs before they lower "
    +"their head and turn around in a submissive gesture.\n", this_player());
        
    return 0;
}


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_fireknives_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("Inside a spacious mess hall");
    
    set_long("Past the archway and into the spacious "
    +"mess hall your senses are "
    +"suddenly assaulted by the intense aroma "
    +"of fresh meat smoke within the "
    +"room. Circular, stone tables have been "
    +"erected in various corners of the "
    +"area, surrounded along its edges by "
    +"stone benches that lean against the "
    +"polished walls of the hall. In the center "
    +"of the room is an oblong bar "
    +"with high stools. The smoke rises from "
    +"the eastern end of the room past "
    +"circular holes leading into what can "
    +"only be the kitchen, and drifts up "
    +"in the air towards the ceiling. You "
    +"see a menu next to the bar.\n");
    
    add_item(({"archway"}),
    "The archway lies to your west leading back "
    +"into the sanctuary. It seems as "
    +"it would elegantly support the structure above it.\n");
 
    add_item(({"mess hall","hall","area","room"}),
    "The room is spacious and loud enough to feel "
    +"alive. Sounds of clanking pots "
    +"and sizzling come from the kitchen, while the "
    +"mess hall overall is brimming "
    +"with chatter and the sound of steps coming "
    +"back and forth from individuals "
    +"ordering drinks at the bar.\n");

    add_item(({"aroma","smell"}),
    "The aroma is intense, of strong spirits and "
    +"the sweet burning of meat.\n");
 
    add_item(({"smoke"}),
    "The smoke comes off from the kitchen through "
    +"the hole, making your mouth "
    +"water with the taste of scented meat and fine spices.\n");
 
    add_item(({"tables","table","stone table","stone tables"}),
    "The tables are low and thick, sculpted from a "
    +"piece of stone in one piece "
    +"around which are benches.\n");
 
    add_item(({"bench","benches","stone bench","stone benches"}),
    "The benches are made from blocks of stone, "
    +"sculpted in the form of an L "
    +"and surrounding the tables facing back from the walls.\n");

    add_item(({"wall","walls","polished wall","polished walls"}),
    "The walls are bare and maintained enough to "
    +"offer a relaxing atmosphere. All "
    +"of the jagged stones have been smoothed out and polished.\n");

    add_item(({"bar","oblong bar"}),
    "The bar in the center of the area is of an oblong "
    +"form with high stools around "
    +"it, from which you can order spirits to drink there "
    +"or carry them back to one of "
    +"the tables.\n");

    add_item(({"stool","stools","high stools","high stool"}),
    "The stools are high and hard, sculpted from "
    +"big chunks of rock in the form of "
    +"an hourglass. They come in various sizes, "
    +"yet all seem to reach the bar all "
    +"the same.\n");

    add_item(({"hole","holes","circular holes",
    "circular hole","end", "eastern end", "kitchen"}),
    "From the eastern end comes the sweet aroma of "
    +"the kitchen. There are holes "
    +"separating it from the rest of the area, with "
    +"trays full of food being placed "
    +"in them and empty ones returning. From them "
    +"the smokey scent drifts up in the "
    +"air, reaching towards the ceiling. \n");

    add_item(({"ceiling"}),
    "The ceiling is visible from here, high up within "
    +"the spacious room. Various holes "
    +"have been punctured into it by some means, "
    +"allowing the majority of the smoke "
    +"to be carried upwards and out.\n");

    add_item(({"floor"}),
    "The floor is clean and well-maintained, kept "
    +"as it was, of stone, often cleand "
    +"and rugged enough to avoid slipping on it.\n");

    add_item( ({"sign","menu"}), "The menu appears "
    +"to be framed with the same "
    +"wood the bar was crafted from with a centre of pure slate. There "
    +"are words scribbled on it in chalk. Perhaps you could <read> the "
    +"sign to see what they say.\n");
    
    add_cmd_item(  ({"sign","menu"}),"read","@@read");

    add_exit(FIREKNIVES_ROOMS_DIR + "o4", "west");

    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
    
    if (!chef)
    {
        chef = clone_object(FIREKNIVES_GUILD_DIR + "npc/chef");
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
        case "well":
        case "well water":
        case "well waters":
            ob = clone_object(fire_water);
            price = num * 10;
            break;
        case "ale":
        case "ales":
        case "siren's":
        case "siren's ale":
        case "siren's ales":
            ob = clone_object(fire_ale);
            price = num * 12;
            break;
        case "grog":
        case "grogs":
        case "vein":
        case "jugular":
        case "jugular vein":
        case "vein grog":
        case "jugular grogs":
        case "jugular grog":
        case "vein grogs":
        case "jugular vein grog":
        case "jugular vein grogs":
            ob = clone_object(fire_grog);
            price = num * 72;
            break;
        case "death":
        case "deaths":
        case "sudden":
        case "sudden death":
        case "sudden deaths":
        case "the sudden death":
        case "the sudden deaths":
            ob = clone_object(fire_death);
            price = num * 100;
            break;
        case "bread":
        case "breads":
        case "cheese":
        case "cheeses":
        case "bread and cheese":
        case "bread and cheeses":
            ob = clone_object(fire_bread_cheese);
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
            ob = clone_object(fire_stew);
            price = num * 80;
            break;
        case "grub":
        case "grubs":
        case "grub of the moment":
        case "grub of the moments":
        case "grubs of the moment":
        case "grubs of the moments":
            ob = clone_object(fire_grub);
            price = num * 160;
            break;
        case "rum":
        case "rums":
        case "black":
        case "black rum":
        case "black rums":
            ob = clone_object(fire_rum);
            price = num * 72;
            break;
        case "plum":
        case "brandy":
        case "plumbrandy":
        case "plumbrandies":
        case "brandies":
        case "plum brandy":
        case "plum brandies":
            ob = clone_object(fire_brandy);
            price = num * 100;
            break;
         case "rice":
        case "beans":
        case "beanses":
        case "rices":
        case "rice and beans":
        case "rice and beanses":
            ob = clone_object(fire_redbeans);
            price = num * 25;
            break;
        case "cockle":
        case "cockles":
        case "mussle":
        case "mussles":
        case "stew":
        case "stews":
        case "cockle and mussle":
        case "cockle and mussles":
        case "cockle and mussle stew":
        case "cockle and mussle stews":
        case "cockles and mussles stews":
        case "cockles and mussles stew":
        case "cockles and mussle stews":
        case "cockles and mussle stew":
            ob = clone_object(fire_cockles);
            price = num * 80;
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
    if(this_player()->query_prop("_sitting_at_bar"))
    {
        write("But you are already sitting by the bar!\n");
        return 1;
    }

    if(this_player()->query_prop("_sitting_at_table"))
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
        this_player()->add_prop("_sitting_at_table", 1);
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
        this_player()->add_prop("_sitting_at_bar", 1);
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
        if(this_player()->query_prop("_sitting_at_table"))
        {
            this_player()->catch_msg("You stand up and leave the table.\n");
            say(QCTNAME(this_player())+" stands up from the table.\n");
            this_player()->remove_prop("_sitting_at_table");
            this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
            return 1;
        }

        if(this_player()->query_prop("_sitting_at_bar"))
        {
            this_player()->catch_msg("You stand up and leave the bar.\n");
            say(QCTNAME(this_player())+" stands up from the bar.\n");
            this_player()->remove_prop("_sitting_at_bar");
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

    if(ob->query_prop("_sitting_at_bar"))
    {
        ob->catch_msg("You stand up from the bar before leaving.\n");
        say(QCTNAME(ob) + " stands up from the bar before "
        +"leaving the inn.\n");
        ob->remove_prop(LIVE_S_EXTRA_SHORT);
        ob->remove_prop("_sitting_at_bar");
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
