/*
 * Nov hut to sell foods and drinks
 * -- Finwe, November 2007
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include <terrain.h>

inherit FAERUN_INDOORS_BASE;
inherit "/d/Shire/lib/inn";

#define PRICELIST_ID  ({"pricelist","list","prices", "menu"})

#define VAMPIRES_OBJ_DIR  "/d/Faerun/guilds/vampires/obj/"

#define WIZARD_ENTRY_BACKROOM_LOG(x,y)   write_file("/d/Faerun/private/restrictlog/guilds/fire_knives/" + x, extract(ctime(time()), \
                            4, 15) +" "+ y )

static object hut_npc;

void
create_indoor_room()
{
    add_prop(ROOM_S_MAP_FILE, "sword_mt_map.txt");

    set_short("A quiet backroom");
    set_extraline("In this quiet secluded room the air is warmer than in "
    +"the front. The wooden walls surrounding the area are sturdier and "
    +"look freshly made. A painting hangs on one of the walls. Crowning "
    +"the walls, a domed ceiling seems to "
    +"absorb the light emanating from the stove and candles placed "
    +"underneath and on top of the table around which are some barrel "
    +"chairs on which you can sit. A pair of guard dogs are watching "
    +"you carefully.");

    add_item(({"walls", "wall"}),
    "The wooden walls are sturdy and effective at keeping the warmth "
    +"inside the backroom. There is a painting hanging on one of "
    +"the walls.\n");
    
    add_item(({"roof", "ceiling"}),
    "The domed ceiling crowns the walls and seems alive by virtue "
    +"of the shadows cast from the candles which dance around it.\n");
    
    add_item(({"dog", "dogs", "pair of guard dogs", "guard dogs"}),
    "Powerful, attentive and vicious, these guard dogs ensure the "
    +"absolute peace in the quitet backroom.\n");
    
    add_item(({"shadows"}),
    "The light of the candles flickers slightly with the small "
    +"+whistles of wind that make their way inside the hut.\n");
    
    add_item(({"stove"}),
    "Underneath the table is a small stove maintaining the room "
    +"warm and cozy.\n");
    
    add_item(({"candle", "candles"}),
    "The candles are strategically placed around the backroom "
    +"to avoid being knocked or put out by the wind. From them "
    +"enough light is cast in the small room.\n");
    
    add_item(({"table"}),
    "A small wooden table with a white cloth over it. Homely and comfortable.\n");
    
    add_item(({"chair", "chairs"}),
    "Four high round chairs with the back like half a barrel; large and upholstered.\n");
    
    add_item(({"floor", "ground"}),
        "The floor is swept clean. It is made of hard-packed dirt and is oddly warm.\n");

    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_prop(ROOM_I_NO_ATTACK, "The guard dogs are watching your every move. You "
    +"would rather try violent behaviours elsewhere!\n");
    add_prop(ROOM_I_NO_STEAL, "The guard dogs are watching your every move. You "
    +"would rather try your luck elsewhere.\n");
    add_item(PRICELIST_ID, "@@pricelist_desc");
    
    room_add_object(VAMPIRES_OBJ_DIR  + "vamp_painting4");

    /*set_room_tell_time(300);
    add_room_tell("The lamp swings overhead, casting shadows around the room.");
    add_room_tell("Something pops in a pan on the stove.");
    add_room_tell("Something bubbles in a pot on the stove.");
    add_room_tell("A cold breeze blows through a chink in the walls.");*/


    //configure_shire_inn();

    add_exit(HR_DIR + "hut_food", "west");

    reset_faerun_room();
}

/*string
pricelist_desc()
{
    return "\nDrinks:\n"+
    "    A glass of water. . . . . . . . .  5 cc\n"+
    "    A cup of tea. . . . . . . . . . .  20 cc\n"+
    "    A glass of cider. . . . . . . . .  20 cc\n"+
    "    A pint of beer. . . . . . . . . .  80 cc\n"+
    "    A glass of white wine . . . . . . 180 cc\n"+
    "\nFood:\n"+
    "    A hard-boiled quail egg . . . . .  50 cc\n"+
    "    A smoked sausage. . . . . . . . .  75 cc\n"+
    "    Squirrel stew. .  . . . . . . . . 100 cc\n"+
    "    Roasted pheasant. . . . . . . . . 160 cc\n\n";
}*/

void
reset_faerun_room()
{
    /*if (!hut_npc)
        hut_npc = clone_object(NPC_DIR + "hut_food");
    if (!present(hut_npc,this_object()))
        hut_npc->move(this_object());*/
}


/*int
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

    if (!hut_npc || !present(hut_npc))
    {
        notify_fail("There is no one here to buy anything from.\n"+
          "She is gone for now.\n");
        return 0;
    }

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
// drinks
    case "water":
    case "waters":
    case "glass of water":
    case "glasses of water":
        order = clone_object(FOOD_DIR + "water");
        price = 5;
        break;
    case "beer":
    case "pint of beer":
    case "pints of beer":
    case "beers":
        order = clone_object(FOOD_DIR + "beer");
        price = 80;
        break;
    case "tea":
    case "cup of tea":
    case "cups of tea":
    case "cup of teas":
        order = clone_object(FOOD_DIR + "tea");
        price = 20;
        break;
    case "wine":
    case "white wine":
    case "glass of wine":
    case "wines":
    case "white wines":
    case "glass of white wines":
    case "glasses of white wine":
        order = clone_object(FOOD_DIR + "wine");
        price = 180;
        break;
    case "cider":
    case "glass of cider":
    case "glasses of cider":
    case "glass of ciders":
    case "ciders":
        order = clone_object(FOOD_DIR + "cider");
        price = 20;
        break;
// foods
    case "egg":
    case "eggs":
    case "quail egg":
    case "quail eggs":
    case "hard-boiled quail egg":
    case "hard-boiled quail eggs":
        order = clone_object(FOOD_DIR + "qegg");
        price = 50;
        break;
    case "sausage":
    case "sausages":
    case "smoked sausage":
    case "smoked sausages":
        order = clone_object(FOOD_DIR + "sausage");
        price = 75;
        break;
    case "stew":
    case "stews":
    case "squirrel stew":
    case "squirrel stews":
        order = clone_object(FOOD_DIR + "stew");
        price = 100;
        break;
    case "pheasant":
    case "pheasants":
    case "roasted pheasant":
    case "roasted pheasants":
        order = clone_object(FOOD_DIR + "pheasant");
        price = 160;
        break;
    }
    return (({order}) + ({price}));
}*/


int
block_room()
{
    if (this_player()->query_wiz_level()) return 0;

        write("You cannot go there yet.\n");
    return 1;
}


/*
 * Function that allows the player to sit at a table or the bar
 */
int action_sit(string str)
{
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
        this_player()->catch_msg("You sit down in one of the barrel "
        +"chairs near the table.\n");
        say(QCTNAME(this_player()) + " sits down in one of the barrel "
        +"chairs near the table.\n");
        this_player()->add_prop("_sitting_at_table", 1);
        this_player()->add_prop(LIVE_S_EXTRA_SHORT," who is sitting near a "
        +"table");
        return 1;
    }

    else
    {
        this_player()->catch_msg("Where would you like to sit? "
        +"At the table?\n");
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
    }

    else
    {
        this_player()->catch_msg("Stand? Stand up?\n");
        return 1;
    }

    return 1;
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (interactive(ob))
    {
        if (ob->query_wiz_level())
        {
            WIZARD_ENTRY_BACKROOM_LOG("wizard_entry_backroom_log",
            "The immortal " +ob->query_name() 
            +" entered the Fire Knives backroom meeting room in the village.\n");
            
            ob->catch_tell(" >>> YOUR ENTRY HAS BEEN LOGGED. UNLESS YOU HAVE BUSINESS "
            +"HERE, PLEASE IMMEDATELY MOVE ELSEWHERE! <<<\n");
        } 
    }
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
        +"leaving the room.\n");
        ob->remove_prop(LIVE_S_EXTRA_SHORT);
        ob->remove_prop("_sitting_at_table");
    }
}


void
init()
{
    ::init();
    //init_shire_inn();
    //add_action("do_read", "read", 0);
    add_action("action_sit", "sit");
    add_action("action_stand", "stand");
}
