/* General Shop of Vingaard Keep by Morrigan, Jan 97      */
/* Based on the General Shop in Calia by Maniac         */
/*
 * Louie April 2006 - Set greed to 100.
 */

#pragma save_binary

inherit "/lib/shop";

#include <stdproperties.h>
#include <macros.h>
#include "../knight/guild.h"

inherit IN_BASE;

object keeper;

int
greed_buy()
{
    return 100;
/*
    if (MEMBER(TP))
        return 75;
    else
        return 100;
*/
}

greed_sell()
{
    return 100;
/*
    if (MEMBER(TP))
        return 81;
    else
        return 100;
*/
}

void
reset_vin_room()
{
    if (!keeper)
        {
        keeper = clone_object(VNPC + "kharn");
        keeper->move(TO);
    }
}

/*
* Function name:   create_room
* Description:     Initialize this room
* Returns:
*/
void
create_vin_room()
{
    config_default_trade();
/*
    set_money_greed_buy("@@greed_buy@@");
    set_money_greed_sell("@@greed_sell@@");
*/
    set_money_greed_buy(100);
    set_money_greed_sell(100);
    set_short("Equipment Store of Vingaard Keep");
    set_long("This is the general store of Vingaard Keep. This room has " +
         "only a small entranceway, while the majority of it lies behind " +
         "a counter that spans the width of the room. Interestingly, " +
         "the counter is quite low. A sign is perched on the counter. " +
         "The store exits south, into the street.\n");
    set_store_room(VROOM + "general_store2");
    AI(({"small entranceway","entranceway"}),"It is where you are " +
        "standing, in front of the counter.\n");
    AI(({"ceiling","wall","floor"}),"Composed of granite, it looks like " +
        "most others in Vingaard Keep.\n");
    AI("walls","They look like all the other walls in Vingaard Keep.\n");
    AI("granite","This rock is mined from the Vingaard Mountains.\n");
    AI(({"counter","low counter"}),"The low counter is most likely " +
        "for those with low legs.\n");
    ACI(({"sign","burnings"}),"read","@@do_read");
    AI("sign","The sign is made of wood, with burnings on it.\n");
    AI("burnings","A darker colour than the rest of the wood, you could " +
        "read the burnings.\n");
    AI("wood","The wood is a soft wood, perhaps fir.\n");    
    AI("street","The street leads to other areas in Vingaard Keep.\n");
    AE(VROOM + "general_store2", "north", "@@wiz_check", 0, 1);
    AE(VROOM + "ss2", "south", 0);
    INSIDE;
    query_store_room()->load_me();
    reset_vin_room();
}

/*
* Function name:   init
* Description:     Is called for each living that enters this room
* Returns:
*/
void
init()
{
    ::init();   /* You MUST do this in a room-init */
    init_shop();
}

/*
* Function name:   wiz_check
* Description:     Check if a player is a wizard
    * Returns:         0 if the player is a wizard
    *                  1 otherwise
*/
int
wiz_check()
{
    object tp;
    
    tp = TP;
    if (tp->query_wiz_level())
        return 0;
    write("Some magic force keeps you from going north.\n");
    say(QCTNAME(tp) + " tries to go northwest but fails.\n");
    return 1;
}

int
do_read(string str)
{   
    if (str == "sign")
        {
        write("Welcome to the General Store!\n" +
              "Remember, you may not sell here, only buy.\n");
        return 1;
    }
    else
        {
        NF("Read what? The sign?\n");
        return 0;
    }
}

int
do_buy(string str)
{
   int playeralign;    

    NF("The shopkeeper is not here to buy from.\n");
    if (!P(keeper, TO))
        return 0;
    NF("The shopkeeper says: I will not sell to those such as you!\n");
    playeralign = TP->query_alignment();
    if (playeralign < 0)
        {
        if (!TP->query_prop(I_WAS_EVIL))
        TP->add_prop(I_WAS_EVIL, 1);
        }
    NF("The shopkeeper says: I will not sell to those such as you!\n");
    if (TP->query_prop(I_WAS_EVIL))
        return 0;
    return ::do_buy(str);
    
}

int
do_sell(string str)
{
    TP->catch_msg("We don't buy anything here, try next door!\n");
    return 1;
}
