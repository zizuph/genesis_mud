
/* 	Equipment Shop of Thalassia

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar

*/

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Genesis/lib/shop";
inherit "/d/Calia/std/water_room";

#define STORE_ROOM THALM+"store"

void
create_water_room()
{
    config_default_trade();
    set_short("An equipment store");
    set_long("You have entered the equipment shop for the city "+
        "of Thalassia. There is a large white marble counter near "+
        "the back of the shop, behind which is the shopkeeper. "+
        "Here you may purchase equipment, clothing, and components "+
        "for use on your journies here in the city and abroad as "+
        "well. You see several things behind the counter that look "+
        "like they may be interesting to you. There is a sign on "+
        "the counter that you can read containing more instructions. "+
        "Next to the sign, you see a poster. To the east you see a "+
        "storeroom where some equipment is kept.\n");

    add_item("poster","The poster shows a picture of a small bubble. "+
        "Below the picture it says:\nPurchase your magical communication "+
        "bubbles here! Only 2 silver each! (<purchase bubble>)\n");

    add_item("storeroom","The storeroom is a small chamber off to the "+
        "east of here containing some of the larger items for sale "+
        "in this shop. You somehow know that you will not be permitted "+
        "to enter the storeroom no matter what you do or say.\n"); 

    add_item(({"things","several things"}),"You could probably "+
        "get a 'list' of things that are available here.\n");

    add_item(({"counter","marble counter","white marble counter",
        "white counter"}),"This white marble counter appears to "+
        "have been carved out of one single piece of marble. It "+
        "must have been quite a large sized block as the counter "+
        "is nearly ten feet long, four feet high and four feet "+
        "across. Behind the counter is the shopkeeper. There is a "+
        "sign on the counter which you can read.\n");

    add_item("shopkeeper","This gentle mermaid floats behind the "+
        "counter, waiting to serve you and watching your every "+
        "move. Her eyes are beautiful to stare into, almost "+
        "hypnotic.\n");

    add_swim_exit(THALM+"major43","west",0,1);
    add_swim_exit(STORE_ROOM, "east", "@@wiz_check",1);

    add_item("sign", "There is a nice looking sign on the counter "+
        "that you can read. It contains instructions on how to use "+
        "this shop.\n");

    add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */

    set_store_room(STORE_ROOM);
}

int
purchase_bubble(string str)
{
    object bubble;

    if (str != "bubble") 
    {
        NF("Purchase bubble?\n");
        return 0;
    }

    if (MONEY_ADD(TP,-24))
    {
         bubble=clone_object(SEA_OBJECTS+"speech_bubble");
         bubble->move(TP);
         TP->catch_msg("You purchase a small magical bubble.\n");
    }
    else 
        TP->catch_msg("You don't seem to have enough money to "+
            "purchase a small magical bubble.\n");

   return 1;
}

/*
 * Function name:   init
 * Description:     Is called for each living that enters this room
 */

void
init()
{
    ::init();   /* You MUST do this in a room-init */
    init_shop(); /* Get the commands from the shop */
    add_action(purchase_bubble, "purchase");
}
