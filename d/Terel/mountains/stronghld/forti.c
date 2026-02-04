/*
 * Stronghold Pub.
 * Tomas  -- Jan. 2000
 */

#include <stdproperties.h>
#include "/d/Terel/include/Terel.h"

inherit STDROOM;
inherit "/lib/pub";

int race_invis_enemy();

object keeper;

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room ();
    set_short("Pub");
    set_long("The stronghold pub is a favorite among the " +
       "hard working warriors. Several round oaken tables " +
       "surrounded by semi-circular benches are scattered " +
       "about the room. Iron pot braziers hang from chains " +
       "connected to the rafters on the ceiling. A large " +
       "menu is nailed above the long rustic looking bar " +
       "against the far wall.\n");

    add_item("bar","The bar is made of solid oak, and runs the length of "+
           "the south wall.\n");

    add_item(({"table", "tables","chairs","semi-circular benches",
               "benches"}),
          "The tables and benches have seen a lot of use over the years.\n");

    add_item(({"iron brazier","iron braziers","brazier","braziers"}),
       "Iron pot braziers containing some sort of slow burning " +
       "fuel provide light to the barracks.\n");

   
    add_item(({"menu"}), "@@menu_descrip");

    add_cmd_item("menu", ({"read", "list"}), ({"@@read_menu", "@@read_menu"}));

    add_exit(MOUNTAIN_DIR + "stronghld/fortj","north",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/forth","west",0,1);


    add_drink (({"beer", "beers"}), /* ids */
            ({"beer", "beers"}),   /* names */
            "beer",                /* adj */
            25,                    /* soft */
            50,                    /* alco */
            50,                    /* price */
            0,                     /* short */
            0,                     /* pshort */
            "An icy cold brew. Just what you were looking for!\n", 0);

    add_drink (({"ale", "ales"}),         /* ids */
            ({"ale", "ales"}),            /* names */
               "granet",                  /* adj */
            35,                           /* soft */
            55,                           /* alco */
            75,                           /* price */
            0,                            /* short */
            0,                            /* pshort */
            "A thick, robust flavored ale.\n", 0);

    add_drink (({"stout", "stouts"}),    /* ids */
            ({"stout", "stouts"}),    /* names */
            "golden",                       /* adj */
            50,                           /* soft */
            70,                            /* alco */
            100,                           /* price */
            0,                            /* short */
            0,                            /* pshort */
            "A fine golden colored stout brewed by the " +
            "brew meister himself.\n", 0);

    add_drink (({"spirit", "spirits"}),    /* ids */
            ({"spirit", "spirits"}),    /* names */
            "dwarven",                 /* adj */
            84,                           /* soft */
            90,                           /* alco */
            260,                          /* price */
            0,                            /* short */
            0,                            /* pshort */
            "A dragonfire whiskey, guaranteed to grow " +
            "hair on your chest!\n");

    add_drink (({"mead", "meads"}),    /* ids */
            ({"mead", "meads"}),    /* names */
            "dwarven",                 /* adj */
            60,                           /* soft */
            70,                           /* alco */
            125,                          /* price */
            0,                            /* short */
            0,                            /* pshort */
            "A robust, thick flavored mead.\n");


    
    INSIDE;

   reset_room();

}


public void
reset_room()
{
    if (!keeper) {
        seteuid(getuid());
        keeper = clone_object(MOUNTAIN_DIR +"stronghld/npc/brewer");
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
    return ("   A Beer                       50 cc\n" +
         "   A Granet Ale                 75 cc\n" +
         "   A Golden Stout              100 cc\n" +
         "   A Dwarven Spirit            150 cc\n" +
         "   A Mead                      125 cc\n");
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
                keeper->command("say I coulda sworn I heard something!.");
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

    

    if(TP->query_race() == "goblin")
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
                keeper->command("say Goblins will recieve no business "+
                "here!");
                break;
            case 4:
                keeper->command("say No goblins allowed, get out!");
                break;
        }
        return 1;
    }
    return 0;
}




