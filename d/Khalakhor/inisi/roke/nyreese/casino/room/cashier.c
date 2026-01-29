 /*
  * Cashier of the new Cadu Casino
  * Here you can buy and sell markers needed for gambling in the casino
  */
#pragma strict_types

inherit "/std/room";
inherit "/lib/trade";

#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include "../defs.h"
#include "../obj/marker_utils.h"
        

#define DEBUG(x) find_player("treacher")->catch_msg("DEBUG: " + x +"\n")

int cashier_here = 0;
    
string
read_sign()
{
    return
    " _________________________________________________ \n" +
    "|  _____________________________________________  |\n" +
    "| |                                             | |\n" +
    "| | *** C A D U  C A S I N O  M A R K E R S *** | |\n" +
    "| |                                             | |\n" +
    "| |        Red marker:   1 silver coin          | |\n" +
    "| |        Green marker: 1 gold coin            | |\n" + 
    "| |        Blue marker:  1 platinum coin        | |\n" +
    "| |                                             | |\n" +
    "| | Note: The markers can only be bought with   | |\n" +
    "| |       the correct type of coin.             | |\n" +
    "| |_____________________________________________| |\n" +
    "|_________________________________________________|\n\n";  
}

string
cashier_desc()
{
    if(cashier_here)
        return "Through the bars you see a cashier standing with a pleasant smile on her face.\n";
    else
        return "";
}

string
cashier_item()
{
    if(cashier_here)
        return "The cashier stands behind the barred opening, out of harms way. She is " +
               "dressed in fine clothes and looks at you with a pleasant smile. When she " +
               "notice you looking at her, she makes an almost unnoticable nod towards the " +
               "golden sign.\n";
    else
        return "You find no cashier.\n";
}

void
cashier_leave()
{
    object *liv = FILTER_LIVE(all_inventory(this_object()));
    if(sizeof(liv) > 0)
    {
        set_alarm(600.0, 0.0, &cashier_leave()); 
    }
    else
    {
        cashier_here = 0;
    }   
}

void
cashier_arrive()
{
    if(!cashier_here)
    {
        cashier_here = 1;
        tell_room(TO, "A cashier appears behind the barred opening and smiles at you.\n");  
        set_alarm(15.0, 0.0, &cashier_leave());  
    }
}

void
create_room()
{
    set_short("casino cashier");
    set_long("You are standing next to a shimmering mithril wall covering the entire " +
             "east side. In the middle of the wall a barred opening has been carved out, " +
             "almost creating a shadow in the bright reflections. To the west lies the " +
             "great hall of the casino.\n" +
             "Beside the opening a golden sign has been put up.\n" +
             "@@cashier_desc@@");

    add_item(({"wall", "shimmering wall", "mithril wall"}),
             "Though difficult to see without shielding your eyes from the bright reflections, " +
             "the wall is truly a wonder. Created from a single massive block of mithril, the wall " +
             "covers the entire wall, except from the opening that has been carved out directly " +
             "from the wall.\n");
    add_item(({"opening", "barred opening", "bars", "window"}),
             "The opening is positioned in the middle of the wall, and has several crossed bars " +
             "making it impossible to pass anything through the opening besides smaller objects.\n");
    add_item(({"hall", "great hall"}),
             "The great hall lies to the west, where you see alot of people hurrying by.\n");
    add_item(({"cashier"}), "@@cashier_item@@");
    add_item(({"sign", "golden sign"}), "@@read_sign@@");
    add_cmd_item("sign", "read", "@@read_sign");

    add_exit(CASINO + "room/hall", "west");

    config_default_trade();
    set_money_give_max(1000000);
    set_money_give_out(({0, 85000, 7000, 600 }));
    set_money_give_reduce(({0, 0, 0, 0}));
    set_money_accept(({0, 1, 1, 1}));
}

void
init()
{
    ::init();
    add_action(do_buy, "buy");
    add_action(do_sell, "sell");

    set_alarm(10.0, 0.0, &cashier_arrive());
}