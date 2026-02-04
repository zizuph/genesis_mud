/*
 * Dwarven stronghold inn 
 * copied from cal_inn.c
 * Tomas  -- Jan 2000
 */

#include "/d/Terel/include/Terel.h"

inherit STDROOM;
inherit "/d/Terel/std/pub";

int race_invis_enemy();
object keeper;



/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Stronghold messhall");
    set_long("The messhall looks spotless. Long tables " +
       "and benches line up in the middle of the room. " +
       "A serving line can be seen against the far wall. " +
       "A menu hangs above the serving line. To the east " +
       "looks like the pub.\n");

    add_item(({"table", "tables"}),
             "They are made of solid oak. They look clean enough to " +
             "eat off off.\n");
 
    add_item(({"benches","chairs","bench","chair"}),
             "Benches run along each side of the long tables.\n");

    add_item(({"iron brazier","iron braziers","brazier","braziers"}),
       "Iron pot braziers containing some sort of slow burning " +
       "fuel provide light to the barracks.\n");

    add_item(({"serving line","line"}),
       "A well ordered serving line has been roped off for efficiency " +
       "purposes.\n");

    add_item(({"walls","ceiling","floor"}),
       "The room like the rest of the stronghold was mined out of " +
       "solid rock. The walls are sparten, and bare. The floor " +
       "is kept clean of any debris.\n");

    add_item(({"menu"}), "@@menu");

    add_cmd_item("menu", ({"read", "list"}), ({"@@read_menu", "@@read_menu"}));

    INSIDE;

    add_food (({"stew", "stews","beef stew"}), /* ids */
              ({"stew", "stews","beef stew"}), /* names */
              "beef",              /* adj */
              150,                 /* ammount */
              150,                 /* price */
              0,                   /* short */
              0,                   /* pshort */
              "A thick bowl of beefy stew.\n", 0);

    add_food (({"steak", "steaks","venision","venision steak"}), /* ids */
              ({"steak", "steaks","venision","venision steak"}), /* names */
              "venision",        /* adj */
              93,                /* ammount */
              100,                /* price */
              0,                 /* short */
              0,                 /* pshort */
              "A large juicy piece of venision!\n", 0);

    add_food (({"of mutton", "legs","mutton","leg of mutton"}), /* ids */
              ({"of mutton", "mutton legs","mutton","leg of mutton"}), /* names */
              "leg",                  /* adj */
              70,                          /* ammount */
              50,                          /* price */
              0,                           /* short */
              0,                           /* pshort */
              "This is a leg of freshly roasted mutton!\n", 0);

    add_food (({"tac", "hard tac", "hard tacs"}), /* ids */
              ({"tac", "hard tac", "hard tacs"}), /* names */
              "hard",                                    /* adj */
              15,                                         /* ammount */
              10,                                         /* price */
              0,                                          /* short */
              0,                                          /* pshort */
              "A hard piece of chewy bread, excellent for when on the trail.\n", 0);

    add_exit(MOUNTAIN_DIR + "stronghld/fortf","north",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/forti","east",0,1);

    reset_room ();

}

public void
reset_room()
{
    if (!keeper) {
        seteuid(getuid());
        keeper = clone_object(MOUNTAIN_DIR +"stronghld/npc/inn_keep");
        keeper->move(TO);
    }
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
                keeper->command("say Damn ghosts! These mountains " +
                                "are full of em!");
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
            "Beef Stew ................... 165 Copper coins\n" +
            "Venision Steak ............... 70 Copper Coins\n" +
            "Leg of Mutton ................ 30 Copper Coins\n" +
            "Hard Tac ..................... 12 Copper Coins\n");
}


/*
 * Function name: read_menu
 * Description:   Handle the read action for the menu
 * Returns:       1/0
 */
public int
read_menu ()
{
    write(menu());
    say(QCTNAME(this_player()) + " reads the menu on the south wall.\n");
    return 1;
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



