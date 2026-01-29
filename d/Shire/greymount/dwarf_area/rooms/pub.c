/*
** The Last Dwarf Standing Pub
** Created By Leia
** February 22, 2006
*/

inherit "/d/Shire/std/room";
inherit "/d/Shire/lib/inn";
#include "../defs.h"
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#define PRICELIST_ID  ({"pricelist","list","prices", "menu"})

void 
init()
{    
    ::init();
    add_action("action_sit", "sit");
    add_action("action_stand", "stand");
    add_action("order", "buy");
    add_action("order", "order");
    init_shire_inn();
    add_action("do_read", "read", 0);
}

int 
action_sit(string str)
{
        if(TP->query_prop(TSIT))
        {
                write("But you are already sitting by the stone table! Not even you are magical enough to sit in two places at once.\n");
                return 1;
        }
           
        if(TP->query_prop(BSIT))
        {
                write("But you are already sitting by the bar! Not even you are magical enough to sit in two places at once!\n");
                return 1;
        }
           
        if(str == "around table" | str == "around a table" | str == "at table" | str == "at a table" | str == "by table" | str == "by a table" | str == "table" | str == "chair around table" | str == "in chair around table" | str == "in a chair around a table" | str == "chair at table" | str == "in chair at table" | str == "in a chair at a table" | str == "chair by table" | str == "in chair by table" | str == "in a chair by a table") 
        {
                TP->catch_msg("You sit down in one of the plush chairs near a table. The bear skin is warm and soft beneath your weight.\n");
                say(QCTNAME(TP) + " sits down in one of the plush chairs near a table and smiles contentedly.\n");
                TP->add_prop(TSIT, 1);
                TP->add_prop(LIVE_S_EXTRA_SHORT," who is sitting near a stone table");
                return 1;
        }
        	
	        if(str == "at bar" | str == "at the bar" | str == "by bar" | str == "by the bar" | str == "bar" | str == "chair at bar" | str == "in chair at bar" | str == "in a chair at the bar" | str == "chair by bar" | str == "in chair by bar" | str == "in a chair by the bar")
        {
                TP->catch_msg("You sit down in one of the plush chairs near the bar. The bear skin is warm and soft beneath your weight.\n");
                say(QCTNAME(TP) + " sits down in one of the plush chairs near the bar and smiles contentedly.\n");
                TP->add_prop(BSIT, 1);
                TP->add_prop(LIVE_S_EXTRA_SHORT," who is sitting near the bar");
                return 1;
        }
	
        else
        {
                TP->catch_msg("Where would you like to sit? By the bar or around a table?\n");
                return 1;
        }
        
        return 1;
}

int 
action_stand(string str)
{
        if(str == "up")
        {
                if(TP->query_prop(TSIT))
                {
                        
                        TP->catch_msg("You stand up and leave the stone table.\n");
                        say(QCTNAME(TP)+" stands up from the stone table.\n");
                        TP->remove_prop(TSIT);
                        TP->remove_prop(LIVE_S_EXTRA_SHORT);
                        return 1;
                }
                
                if(TP->query_prop(BSIT))
                {
                        TP->catch_msg("You stand up and leave the bar.\n");
                        say(QCTNAME(TP)+" stands up from the bar.\n");
                        TP->remove_prop(BSIT);
                        TP->remove_prop(LIVE_S_EXTRA_SHORT);
                        return 1;
                }
        }
        
        else
        {
                TP->catch_msg("Stand? Would you like to stand up?\n");
                return 1;
        }
        
        return 1;
}

void leave_inv(object ob, object to)
{
        ::leave_inv(ob, to);    
        
        if(!objectp(to) || !objectp(ob))
                return;
                
        if(TP->query_prop(TSIT))
        {
                TP->catch_msg("You stand up from the stone table before leaving.\n");
                say(QCTNAME(TP) + " stands up from the stone table as " + HE_SHE(TP) + " leaves.\n");
                TP->remove_prop(LIVE_S_EXTRA_SHORT);
                TP->remove_prop(TSIT);
        }
        
        if(TP->query_prop(BSIT))
        {
                TP->catch_msg("You stand up from the bar before leaving.\n");        
                say(QCTNAME(TP) + " stands up from the bar as " + HE_SHE(TP) + " leaves.\n");
                TP->remove_prop(LIVE_S_EXTRA_SHORT);
                TP->remove_prop(BSIT);
        }
}

void
create_shire_room()
{
    config_default_trade();
    set_short("The Last Dwarf Standing Pub");
    set_long("You are in the Last Dwarf Standing Pub. There is a menu on the bar. The entire pub is filled with bustling dwarves, laughing, joking, and carrying on in a boisterous fashion. The pub lives up to its name, as you look around and see two or three dwarves passed out on the floor. The tables as well as the bar are fashioned from stone, as are the chairs. Thankfully, the chairs are padded with bear skin and look to be quite comfortable. The baretender is behind the bar, and seems to be frantically trying to match the pace of the thirsty dwarves.\n"); 
    add_item("bar", "This is a well polised stone bar with a menu on it. Great care was taken in crafting this beautiful centerpiece of the pub.\n");
    add_item("menu", "It's a menu. Perhaps you should try reading it?\n");
    add_item(({"walls", "wall"}), "They are carved out of the stone of the mountain, like most establishments within this settlement.\n"); 
    add_item(({"chairs", "chair"}), "They are comfortable looking stone chairs. Each chair has been expertly carved from stone, padded, and covered with bear skin.\n");
    add_item(({"table", "tables"}), "They are made of a beautiful stone, or perhaps of various stones. It looks as though they have been expertly crafted out of various types of stone, but you cannot find a fitting mark anywhere.\n");
    add_cmd_item("menu", "read", "@@read");
    add_item(({"dwarves"}), "There are many dwarves sitting about the bar, seemingly enjoying themselves greatly.\n");
    set_room_tell_time(120+random(15));
    add_room_tell("Suddenly a fight breaks out amongst the dwarves. Quickly the bartender rushes from behind the bar, grabs both the offending dwarves by the seat of their pants, and escorts them out of the pub.\n");
    add_room_tell("Looking sternly at one of the dwarves at the bar, the bartender declares that he has had enough.\n");
    add_room_tell("Glasses clink together at a nearby table, as the dwarves surrounding it erupt after a toast.\n");
    add_room_tell("The bartender sends a glass sliding down the bar, where an awaiting dwarf quickly stops it with his hand.\n");
    
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(OBJ_M_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1); 
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    

    add_exit(DT16, "west");
    
    reset_shire_room();
    }


string
pricelist_desc()
{	
    return "   __________________________________________ \n" +
"   \\                                         \\ \n" +
"   |\\_________________________________________\\ \n" +
"   ||                                         | \n" +
"   || Welcome to the Last Dwarf Standing Pub  | \n" +
"   ||                                         | \n" +
"   ||                                         | \n" +
"   || We offer the following drinks:          | \n" +
"   ||                                         | \n" +
"   || Beer............................10cc    | \n" +
"   || Wine............................21cc    | \n" +
"   || Ale.............................37cc    | \n" +
"   || Brandy..........................42cc    | \n" +
"   || Whiskey.........................69cc    | \n" +
"   || Draught........................101cc    | \n" +
"   ||                                         | \n" +
"   || Please note:                            | \n" +
"   || Despite years of practice, the bartender| \n" +
"   || can only carry so many items at once.   | \n" +
"   || Please limit your orders to 20 items or | \n" +
"   || less.                                   | \n" +
"   ||                                         | \n" +
"   ||                                         | \n" +
"   ||_________________________________________| \n";
}

void
reset_shire_room()
{
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
    case "beer":
    case "beers":
    case "stout beer":
    case "stout beers":
    case "dwarven beer":
    case "dwarven beers":
    case "stout dwarven beer":
    case "stout dwarven beers":
        order = clone_object(OBJS_DIR + "beer2");
        price = 10;
        break;
    case "wine":
    case "wine":
    case "dark wine":
    case "dark wines":
    case "dwarven wine":
    case "dwarven wines":
    case "dark dwarven wine":
    case "dark dwarven wines":
        order = clone_object(OBJS_DIR + "wine");
        price = 21;
        break;
    case "ale":
    case "ales":
    case "smooth ale":
    case "smooth ales":
    case "dwarven ale":
    case "dwarven ales":
    case "smooth dwarven ale":
    case "smooth dwarven ales":	        
	order = clone_object(OBJS_DIR + "ale2");
        price = 37;
        break;
    case "brandy":
    case "brandies":
    case "strong brandy":
    case "strong brandies":
    case "dwarven brandy":
    case "dwarven brandies":
    case "strong dwarven brandy":
    case "strong dwarven brandies":        
	order = clone_object(OBJS_DIR + "brandy");
        price = 42;
        break;
    case "whiskey":
    case "whiskies":
    case "powerful whiskey":
    case "powerful whiskies":
    case "dwarven whiskey":
    case "dwarven whiskies":
    case "powerful dwarven whiskey":
    case "powerful dwarven whiskies":        
	order = clone_object(OBJS_DIR + "whiskey");
        price = 69;
        break;
    case "draught":
    case "draughts":
    case "mysterious draught":
    case "mysterious draughts":
    case "dwarven draught":
    case "dwarven draughts":
    case "mysterious dwarven draught":
    case "mysterious dwarven draughts":        
	order = clone_object(OBJS_DIR + "draught");
        price = 101;
        break;

    default:
	NF("I don't understand what you want to buy.\n");
	return 0;
    }
    
    

    return (({order}) + ({price}));
}