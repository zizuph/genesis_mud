/*
 * This is an example of a shop that only buys and sells weapons.
 * Finwe, June 2016
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"


inherit "/d/Genesis/lib/shop";
inherit FAERUN_INDOORS_BASE;

// This defines where the items are stored when they are purchased. 
// This is an actual room mortals have no access to.
#define STORE_ROOM "/d/Faerun/examples/wstore"
// If you want to only deal in armours, change this to
// #define STDARMFILE "/std/armour"'
// and replace all STDWEPFILE with STDARMFILE
#define STDWEPFILE "/std/weapon"

static object wep_npc;

void
create_indoor_room()
{
    set_store_room(STORE_ROOM);
    set_short("A basic weapon shop");
    set_long("This is an example of a shop that only deals in weapons.\n");

    add_prop(ROOM_I_INSIDE,1);	/* This is a real room */

    config_default_trade();  /* Set up the trading system */
    set_store_room(STORE_ROOM);

    reset_room();
}

public void
init()
{
    init_shop();
    ::init();
}


void reset_faerun_room()
{
    if (!wep_npc)
        wep_npc = clone_object("/d/Faerun/examples/npcs/woman");
    if (!present(wep_npc,this_object()))
        wep_npc->move(this_object());
}

int
shop_hook_allow_sell(object ob)  
{

    if (!wep_npc || !present(wep_npc))
    {
        notify_fail("There is no one here to sell you anything.\n");
        return 0;
    }

    if (function_exists("create_object", ob) != STDWEPFILE )
    {
        wep_npc->command("say I'm only interested in weapons.");
        NF("");
        return 0;
    }

    return 1;
}

int
shop_hook_allow_buy(object ob)  
{
    if (!wep_npc || !present(wep_npc))
    {
        notify_fail("There is no one here to buy anything.\n");
        return 0;
    }

    if (function_exists("create_object", ob) != STDWEPFILE)
    {
        wep_npc->command("say I'm only interested in weapons and armours.");
        NF("");
        return 0;
    }

    return 1;
}

