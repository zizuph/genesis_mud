/*
 *  Dragon Claw Pub
 *  Coded by Shinto 110798
 *
 *  Modified: 2 May 2003, by Bleys
 *     - Removed coffee from the menu, since it's not sold here.
 *  Modified: May 2006, by Pasqua
 *     - Fixed the menu so it look more proper
 */

#include "/d/Terel/include/Terel.h"

inherit STDROOM;
inherit "/d/Terel/std/pub";
#define KILL_LOGGER CALATHIN_DIR + "obj/kill_logger"
int race_invis_enemy();
int enemy_check();

object door, keeper;

/*
 * Function name: create_room
 * Description:   Default constructor
 */


public void
create_room()
{
    ::create_room();
    set_short("Dragon Claw Pub");
    set_long("You are now in the Dragon Claw Pub. Four tables stand " +
             "around the center of the room. A bar lines the east and "+
             "south wall with stools for patrons to sit on. There is a "+
             "fireplace against the west wall heating the room. The east "+
             "wall has a doorway to a staircase near the door you entered, "+
             "and the west wall has a door on the far side of the room. "+
             "There is a menu on a table that you can read. \n");

    add_item(({"wall","walls"}), "The walls are made of stone "+
             "to keep out the harsh wind and snow.\n");
    add_item(({"table", "tables"}),
             "They are made of solid oak and stained a dark brown.\n");
    add_item(({"stool","stools"}),
             "The stools are made of oak, and are stained a dark brown.\n");
    add_item("bar",
              "The bar is made of oak, and stained the same dark brown "+
              "as the stools and tables.\n");
    add_item("fireplace", "The fire place is built into the stone walls, "+
              "it keeps the pub warm.\n");
    add_item("staircase","Through the doorway east is a stairway "+
              "leading down to a storage room.\n");
    add_item(({"menu"}), "@@menu");
    add_cmd_item("menu", "read", "@@menu");

    INSIDE;

    add_food (({"steak", "steaks"}), /* ids */
              ({"steak", "steaks"}), /* names */
              "large",            /* adj */
              150,                 /* ammount */
              165,                 /* price */
              0,                   /* short */
              0,                   /* pshort */
              "A thick cut of deer steak.\n", 0);

    add_food (({"soup", "soups"}), /* ids */
              ({"soup", "soups"}), /* names */
              "bean",          /* adj */
              93,                /* ammount */
              70,                /* price */
              0,                 /* short */
              0,                 /* pshort */
              "A large bowl of bean soup.\n", 0);

    add_food (({"squirrel", "squirrels"}), /* ids */
              ({"squirrel", "squirrels"}), /* names */
              "roasted",                  /* adj */
              70,                          /* ammount */
              30,                          /* price */
              0,                           /* short */
              0,                           /* pshort */
              "A good sized squirrel, roasted up.\n", 0);

    add_food (({"jerky", "jerky strip", "jerky strips"}), /* ids */
              ({"jerky", "jerky strip", "jerky strips"}), /* names */
              "strip",                                    /* adj */
              15,                                         /* ammount */
              12,                                         /* price */
              0,                                          /* short */
              0,                                          /* pshort */
              "A long strip of jerky, made from a local animal.\n", 0);
    add_drink (({"beer", "beers"}), /* ids */
            ({"beer", "beers"}), /* names */
            "light",            /* adj */
            100,                 /* soft */
            4,                   /* alco */
            12,                  /* price */
            0,                   /* short */
            0,                   /* pshort */
            "It's a small beer light beer.\n", 0);

    add_drink (({"lager", "lagers"}),    /* ids */
            ({"lager", "lagers"}),    /* names */
               "dragon",                  /* adj */
            62,                           /* soft */
            25,                           /* alco */
            70,                           /* price */
            0,                            /* short */
            0,                            /* pshort */
            "A special brew made exclusivly at the Dragon Claw Pub.\n", 0);

    add_drink (({"whiskey", "whiskeys"}),    /* ids */
            ({"whiskey", "whiskeys"}),    /* names */
            "strong",                      /* adj */
            84,                           /* soft */
            50,                           /* alco */
            260,                          /* price */
            0,                            /* short */
            0,                            /* pshort */
            "A fine whiskey, with a peculiar green colour.\n");

    add_drink (({"water", "waters"}),    /* ids */
            ({"water", "waters"}),    /* names */
            "cold",                       /* adj */
            300,                           /* soft */
            0,                            /* alco */
            10,                           /* price */
            "glass of water",                            /* short */
            "glasses of water",                            /* pshort */
            "A tall glass of water.\n", 0);

    door = clone_object(CALATHIN_DIR + "obj/drag_door");
    door->move(TO);

    add_exit(CALATHIN_DIR +"pubs/drag_stair", "east",0);
    add_exit(CALATHIN_DIR +"pubs/drag_kitch","west",0);
    reset_room ();
}

public void
reset_room()
{
    if (!keeper) {
        seteuid(getuid());
        keeper = clone_object(CALATHIN_DIR +"npc/barkeep");
        keeper->move(TO);
    }
}

/*
 * Function name: init
 * Description:   Add the 'command items' of this object.
 *                Also call init_pub() to set up the pub.
 */
public void
init()
{
    ::init();
    init_pub();
}

/*
 * Function name: menu
 * Description:   Handle the read action for the menu
 * Returns:       the menu
 */
public string
menu()
{
    return ("The menu reads:\n\n" +
            "Food:\n\n"+
            "Deer Steak ....................165 Copper Coins\n" +
            "Bean Soup ......................70 Copper Coins\n" +
            "Roasted Squirrel ...............30 Copper Coins\n" +
            "Jerky Strip ....................12 Copper Coins\n" +
            "Drinks:\n\n"+
            "Light Beer......................12 Copper Coins\n" +
            "Dragon Lager....................70 Copper Coins\n" +
            "Strong Whiskey.................260 Copper Coins\n" +
//            "Strong Coffee...............100 Copper Coins\n" +
            "Cold Water......................10 Copper Coins\n");
}

int
order(string str)
{
    if(race_invis_enemy())
    {
        NF("");
        return 1;
    }

    return ::order(str);
}

int
race_invis_enemy()
{
    int chat;
    chat = random(5);

    if(TP->query_prop(OBJ_I_INVIS))
    {
        switch(chat)
        {
            case 0:
                keeper->command("peer");
                keeper->command("shrug");
                break;
            case 1..2:
                keeper->command("scratch");
                keeper->command("say That better not be a rat.");
                break;
            case 3:
                keeper->command("say Someone say something?");
                keeper->command("peer");
                break;
            case 4:
                keeper->command("say Who's there?");
                keeper->command("peer");
                break;
        }
        return 1;
    }

    if(!CAN_SEE_IN_ROOM(keeper) || !CAN_SEE(keeper, TP))
    {
        switch(chat)
        {
            case 0:
                keeper->command("say If you want to do business turn on "+
                              "the light.");
                keeper->command("shrug");
                break;
            case 1..2:
                keeper->command("scratch");
                keeper->command("say I can't see what you so I won't serve you.");
                break;
            case 3:
                keeper->command("say Someone say something?");
                keeper->command("peer");
                break;
            case 4:
                keeper->command("say Who's turned out the lights?");
                keeper->command("peer");
                break;
        }
        return 1;
    }

    if(enemy_check())
    {
        switch(chat)
        {
            case 0:
                keeper->command("say You enter our homes and slay us and now "+
                "you want us to do business with you?");
                break;
            case 1:
                keeper->command("say I refuse to do business with enemies of "+
                "our town!");
                break;
            case 2:
                keeper->command("say Get out! I want no business from you!");
                break;
            case 3:
                keeper->command("say You've got a lot of nerve, get out of "+
                "here!");
                break;
            case 4:
                keeper->command("say Leave now, or if the guards don't find "+
                "you I'll call them!");
                break;
        }
        return 1;
    }
    

    if(TP->query_race_name() == "goblin")
    {
        switch(chat)
        {
            case 0:
                keeper->command("say I don't deal with goblins.");
                break;
            case 1:
                keeper->command("say I won't do business with goblins.");
                break;
            case 2:
                keeper->command("say Get out, I don't do business with "+
                "goblins.");
                break;
            case 3:
                keeper->command("say Goblins will recieve no business in "+
                "Calathin.");
                break;
            case 4:
                keeper->command("say No goblins allowed, get out!");
                break;
        }
        return 1;
    }
    return 0;
}


int
enemy_check()
{
    object kill_logger = find_object(KILL_LOGGER);
    if(kill_logger->query_killer(TP->query_name()))
    {
        return 1;
    }
    return 0;

}


/*
 * Function name: pay_hook_player_buys
 * Description:   A hook to redefine if you want own message when player
 *                gets his/hers order.
 * Arguments:     ob - The object player ordered
 *                price - The price the player payed for the object
 */
void
pub_hook_player_buys(object ob, int price)
{
    ::pub_hook_player_buys(ob, price);

    ob->add_prop(OBJ_M_NO_SELL, 1);
}
