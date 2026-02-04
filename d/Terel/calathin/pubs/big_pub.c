/*
 * pub.c
 *
 * Copied from /doc/examples/trade/pub.c by Vader, and adpated
 * for use in the Terel domain.  Modified on 6/27/92
 *
 * Modified by Sorgum 960101
 * Updated by Shinto 10-21-98
 */

#include <stdproperties.h>
#include "/d/Terel/include/Terel.h"

inherit STDROOM;
inherit "/lib/pub";
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
    ::create_room ();
    set_short("Big Rock Pub");
    set_long("This is the Big Rock Pub, by far one "+
          "of the finest establishments in town. It is " +
          "frequented by everyone in Calathin, plus many a traveler. " +
          "There are paintings all around of all the great people " +
          "that have visited this pub. There are many tables here " +
          "where the patrons sit, chat, and drink their fill. There is a " +
          "menu posted on the south wall. There is a fireplace "+
          "against the south wall to keep the chill out. The bar "+
          "runs along the west wall. Right in the center of the "+
          "east wall is an enormous quartz rock. A stairway leads "+
          "down to the basement along part of the east wall.\n");

    add_item(({"rock","quartz rock","quartz", "enormous quartz rock"}),
           "The rock is clearly 5 feet high and 4 feet in width. "+
           "From the looks of it the pub was built around this rock "+
            "and it was never moved.\n");

    add_item("fireplace" , "The fireplace is set into the south wall. "+
          "The stones used to make it are various shades of grey.\n");

    add_item("bar","The bar is made of pine, and runs the length of "+
           "the west wall.\n");

    add_item(({"table", "tables"}),
          "These tables have seen a lot of use over the years.\n");

    add_item(({"paintings", "painting", "pictures", "picture"}), 
          "You see the unmistakable likenesses of such great ones " +
          "as\n" +
          "Honorable Sorgum\n" +
          "Sir Azireon\n" +
          "Dame Mortricia\n" +
          "Sir Dust\n" +
          "Sir Cedric\n" +
          "Dame Napture\n" +
          "Sir Janus\n" +
          "Sir Redhawk\n" +
          "Honorable Mecien\n"+
          "Sir Trofast\n"+
          "Sir Torm\n"+
          "Sir Tomas\n"+
         "Warden Goldberry\n"+
          "Lord Shinto\n");
   
    add_item(({"menu"}), "@@menu_descrip");

    add_cmd_item("menu", ({"read", "list"}), ({"@@read_menu", "@@read_menu"}));
    door = clone_object(CALATHIN_DIR + "obj/big_door");
    door->move(TO);
    add_exit(CALATHIN_DIR + "pubs/big_base", "down", 0);
    add_drink (({"beer", "beers"}), /* ids */
            ({"beer", "beers"}), /* names */
            "silver",            /* adj */
            100,                 /* soft */
            4,                   /* alco */
            12,                  /* price */
            0,                   /* short */
            0,                   /* pshort */
            "It's a small beer, oddly, silver in color.\n", 0);

    add_drink (({"special", "specials"}),    /* ids */
            ({"special", "specials"}),    /* names */
               "terellian",                  /* adj */
            62,                           /* soft */
            25,                           /* alco */
            70,                           /* price */
            0,                            /* short */
            0,                            /* pshort */
            "A Special brew made exclusivly at the Big Rock Pub.\n", 0);

    add_drink (({"sinvon", "sinvons"}),    /* ids */
            ({"sinvon", "sinvons"}),    /* names */
            "fine",                       /* adj */
            40,                           /* soft */
            2,                            /* alco */
            10,                           /* price */
            0,                            /* short */
            0,                            /* pshort */
            "A shot of sinvon\n", 0);

    add_drink (({"whiskey", "whiskeys"}),    /* ids */
            ({"whiskey", "whiskeys"}),    /* names */
            "green",                      /* adj */
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

    
    INSIDE;

   reset_room();

}


public void
reset_room()
{
    if (!keeper) {
        seteuid(getuid());
        keeper = clone_object(CALATHIN_DIR +"npc/leah");
        keeper->move(TO);
    }
}

/*
 * Function name: menu_descrip
 * Description:   VBFC for the menu
 * Returns:       what is written on the menu
 */
public string
menu_descrip ()
{
    return ("   A Silver Beer             12 cc\n" +
         "   A Shot of Sinvon           10 cc\n" +
         "   A Glass of Water          10 cc\n" +
         "   A Terellian Special       70 cc\n" +
         "   A Green Whiskey          260 cc\n" );
}

/*
 * Function name: read_menu
 * Description:   Handle the read action for the menu
 * Returns:       1/0
 */
public int
read_menu ()
{
    write(menu_descrip());
    say(QCTNAME(this_player()) + " reads the menu on the south wall.\n");
    return 1;
}

/*
 * Function name: init
 * Description:   Initalize the pub actions
 */
void
init()
{
    ::init(); 
    init_pub();
}

/*
 * Function name: pay_hook_player_buys
 * Description:   A hook to redefine if you want own message when player
 *                gets his/hers order.
 * Arguments:     ob - The object player ordered
 *                price - The price the player payed for the object
 */
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
                keeper->command("say Damn rats.");
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
                keeper->command("say I can't see you so I won't serve you.");
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
                keeper->command("say You enter our home and slay us and now "+
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

