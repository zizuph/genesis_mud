/*
 * hotel.c
 *
 *  A hotel in Calathin of Terel. Here the player can, for
 *  a small fee, have a temporary starting location.
 *
 *  There is a tunnel running under the inn. Originally it was 
 *  intended for use by Shinto's Company, a guild that was 
 *  never finished. It was accessible via the Explorer's room
 *  but the AoD and AoB do not like clubs having exclusive
 *  access to hidden areas, so I have moved the trapdoor into
 *  the tunnels here.
 *
 *  -Lilith May 2008
 *
 *  EXPLORERS CLUB CLOSED, NERULL 2019
 * 
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;
inherit "/lib/trade";
#include "/d/Terel/clubs/explorer/include/explorer_club.h"
#include <money.h>


#define NUM      sizeof(MONEY_TYPES)

/*
 * Prototypes
 */
public string price_long();

/*
 * Global variables
 */
object delsanora,door;

/*
 * Function name: reset_room
 * Description:   clone the hotel keeper if necessary
 */
public void
reset_room()
{
    if (!delsanora) {
        seteuid(getuid());
        delsanora = clone_object(CALATHIN_DIR +"npc/delsanora");
        delsanora->move(CALATHIN_DIR + "inns/inn_main");
    }
}


public mixed
trapdoor()
{

    write("You lift the trapdoor below you and climb through it.\n");
    say(QCTNAME(TP) + " lifts open a trapdoor in the floor, then " +
       "climbs through. The trapdoor closes behind " + HIM_HER + ".\n");

    tell_room(CALATHIN_DIR + "tunnel/tunnel_01", QCTNAME(TP) + 
       " climbs through a trapdoor in the ceiling. Then closes it behind " +
       HIM_HER +".\n");
        TP->move_living("M",CALATHIN_DIR + "tunnel/tunnel_01",1,0);
        return 1;
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    
    set_short("The Silver Tree Inn");
    set_long("This is the Silver Tree Inn. " +
               "You are in the common room of the Inn. Before you is a "+
               "counter with a small bell on it. There is a fireplace to "+
               "your right, and a small table in front of it. On the wall "+
               "behind the counter is a sign with some prices listed. "+
               "You see several doors leading to rentable rooms.\n");

    add_item(({"counter"}), 
        "It's made of solid oak. There is a small slot in it "+
                              "where you can return your key.\n");
    add_item(({"fire","fireplace"}),"A low fire burns in the fireplace "+
        "fighting back the chilling cold that seeps in from the "+
        "entryway.\n");
    add_item("table","The small table stands before the fireplace for "+
                    "visitors to relax at.\n");    
    add_item(({"slot"}), "The shape of the slot reminds you of a key.\n");
    
    add_item(({"list", "pricelist", "sign"}), "@@price_long");

    add_item(({"floor", "oak floor", "planks"}),
        "This floor is made of planks of oak.  It has been polished "+
        "with beeswax and has a warm glow to it. Near the counter "+
        "there is a vague irregularity in the floor.\n");
    add_item(({"irregularity", "vague irregularity","vague irregularity in the floor",
        "trapdoor", "trapdoor in the floor"}),
        "Your keen eyes pick out what appears to be a cleverly concealed "+
        "trapdoor in the floor.\n");
    add_cmd_item(({"trapdoor","trap door"}),
                  ({"lift"}),"@@trapdoor");

    INSIDE;

    door = clone_object(CALATHIN_DIR + "obj/silver_door");
    door->move(TO);
    add_exit(CALATHIN_DIR + "inns/hotel1", "west", "@@check|hotel_1@@");
    add_exit(CALATHIN_DIR + "inns/hotel2", "south",     "@@check|hotel_2@@");
    //add_exit(CALATHIN_DIR + "inns/hotel3", "east", "@@explorer");


    /* Set up the trading system */
    config_default_trade();
                          /* Copper Silver Gold Platinum  */
    set_money_give_out(   ({ 10000,   700,   2,    3 })); /* Max_pay   */
    set_money_give_reduce(({     0,     1,   0,    6 })); /* Threshold */

    reset_room();
}

/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */
public void
init()
{
    ::init();
    add_action("do_read",   "read",   0);
    add_action("do_read",   "study",  0);
    add_action("do_rent",   "rent",   0);
    add_action("do_return", "return", 0);
}

/*
 * Function name: do_read
 * Description:   Handle the read action
 * Returns:       1/0
 */ 
public int
do_read(string str)
{
    NF(capitalize(query_verb()) + " what?\n");
    if (!strlen(str))
                         return 0;
    
    if (str == "pricelist" || str == "list" || str == "prices" ||
                         str == "sign") {
                         write(price_long());
                         return 1;
    }
    return 0;
}

/*
 * Function name: price_long
 * Descrition:    Returns what is written on the price list
 * Returns:       A string that is the pricelist.
 */
public string
price_long()
{
    return (
                     "The list reads:\n"
                  + "    Lodging ...........................1 pc\n"
                  + "You rent a room with 'rent room'.\n");
}

/*
 * Function name: do_return
 * Description:   Handle the return action
 * Returns:       1/0
 */
public int
do_return(string str)
{
    object key;

    NF(capitalize(query_verb()) + " what?\n");
    if (!strlen(str))
        return 0;
    
    if (str != "key" && str != "iron key")
        return 0;

    key = present("_cal_room_key", TP);
    if (!key)
        return 0;

    write("You put the key in the slot on the counter.\n");
    if (delsanora) 
        delsanora->command("thank " + TP->query_real_name());
    key->remove_object();
    say(QCTNAME(TP) + " returns a key.\n");
    return 1;
}


/*
 * Function name: do_rent
 * Description:   Handle the rent action
 * Returns:       1/0
 */
public int
do_rent(string str)
{
    string pay_type, get_type; string coin_pay_text, coin_get_text;
    int *money_arr;    
    object key;
    string item_name, name;
    int price;

    NF("There is no one here to help you!\n");
    if (!delsanora || !present(delsanora))
                         return 0;

    NF(capitalize(query_verb()) + " what?\n");
    if (!strlen(str))
        return 0;

    NF("The innkeeper refuses your business.\n");
    if(TP->query_race_name() == "goblin" || TP->query_race_name() == "hobgoblin")
        return 0;

    /*
     * Check if the player defines what she wants to pay with
     * and what you would like in return.
     */

    if(sscanf(str, "%s with %s and get %s", item_name, pay_type,
                    get_type) != 3) {
        get_type = "";

        if (sscanf(str, "%s with %s", item_name, pay_type) != 2) {
            pay_type = "";
            item_name = str;
         }
    }

    if (item_name != "room" && item_name != "overnight stay" &&
                         item_name != "lodging")
        return 0;

    price = 1728;

    NF("You failed to rent a room.\n");

    if (sizeof(money_arr = pay(price, TP, pay_type, 0, 0, get_type)) == 1) {
                         if (money_arr[0] == 2) {
        delsanora->command("say You don't have any " + pay_type +
                " coins, silly " + TP->query_nonmet_name() +".");
        return 0;
     }
     if (money_arr[0] == 1) {
            delsanora->command("say The room is a little too " +
                  "expensive to pay for in " + pay_type +
                  " coins, silly " + TP->query_nonmet_name() + ".");
            return 0;
     }
    else {
         delsanora->command("say I don't think so!  You are "+
                        "going to need more money than that, silly "+
                         TP->query_nonmet_name() + ".");
         return 0;
         }
     }

    coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
    coin_get_text = text(exclude_array(money_arr, 0, NUM-1));

    write("You rent a room and pay " + coin_pay_text + ".\n");
    if (coin_get_text) write("You get " + coin_get_text + " back.\n");
    
    name = TP->query_real_name();

    seteuid(getuid());
    key = clone_object(CALATHIN_DIR + "inns/hotel_key");
    key->move(delsanora);
    key->add_name("_cal_room_key");
    key->add_prop("_cal_room_renter", name);
    delsanora->command("give key to " + name);
    if (present(key, delsanora))
        delsanora->command("drop key");
    say(QCTNAME(TP) + " rents a room.\n");
    
    return 1;
}



/*
 * Function name: check
 * Description:   vbfc from add_exit to see if a player is allowed to
 *                enter a hotel room
 * Arguments:     cell - the room name
 * Returns:       0 if player is allowed 1 if not allowed
 */
public int
check(string cell)
{
    int i;
    object room, key, *obs;

    key = present("_cal_room_key", TP);
    if(!key || key->query_prop("_cal_room_renter") != TP->query_real_name()) {
        write("You aren't entitled to go there!\n");
        return 1;
    }

    room = find_object(LAST_DIR + cell);
    if (!room)
        return 0;

    obs = all_inventory(room);
    for (i = 0; i < sizeof(obs); i++) 
        if (living(obs[i])) {
            write("That room is already occupied by someone. "+
                      "Try another one.\n");
            return 1;
        }

    return 0;
}


/*
 * Function name: explorer
 * Description:   vbfc from add_exit to see if a member of the Explorer club
 *                may enter their starting room
 * Arguments:     cell - the room name
 * Returns:       0 if player is allowed 1 if not allowed
 */
/*public int
explorer(string cell)
{
    int i;
    object room, ring, *obs;

/*    ring = present("EXPLORER_RING", TP); */
      //ring = TP->query_prop("_live_i_am_explorer");

  /*  if(!ring) 
    {
        write("You aren't entitled to go there!\n");
        return 1;
    }

    room = find_object(LAST_DIR + cell);
    if (!room)
        return 0;

    obs = all_inventory(room);
    for (i = 0; i < sizeof(obs); i++) 
        if (living(obs[i])) 
        {
            write("That room is already occupied by someone. "+
                      "Try another one.\n");
            return 1;
        }

    return 0;
}*/


