/* 
    Miner Pickaxe
    Made by: Maelstrom, 2016/05

    Updated: 
    Maelstrom, 2017/01

    TODO:

    add lava powered messages when mining. (not sure about this yet)
    "Aided by the power of the diamond edged lava powered pickaxe you smash through the rocks."
    "With the help of the diamond edged lava powered pickaxe you cut through rock like butter."


    random underground caverns(?)
    random underground dungeons with treasure rooms(?) (rooms with traps, requiring items to avoid damage, like hook+rope, throw item to trigger trap, etc)

    % of generate dungeon(with entrance and impenetrable walls) upon making dungeon entrance
    % of generate caverns upon making dungeon entrance
    (so dungeon and cavern generation will be inside the pickaxe =) )

    entrance in dungeon needs lockpick and disarm traps.
    chests in dungeon need lockpick or finding the key on hidden places.

    add grappling hooks.


*/

inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <cmdparse.h>

#include <terrain.h>

#include "../defs.h"
#include "common.c"
#include "../ores/ore_dispenser.c"

#include "miner_pickaxe_actions/miner_pickaxe_definitions.c"

#include "miner_pickaxe_actions/miner_pickaxe_random_rooms.c"

#include "miner_pickaxe_actions/miner_pickaxe_check.c"
#include "miner_pickaxe_actions/miner_pickaxe_dial.c"
#include "miner_pickaxe_actions/miner_pickaxe_dig.c"
#include "miner_pickaxe_actions/miner_pickaxe_prospect.c"
#include "miner_pickaxe_actions/miner_pickaxe_refill.c"


create_weapon()
{
    set_name(({"pickaxe", "axe", "weapon", "tool", "miner_pickaxe"}));
    set_short("diamond edged lava powered pickaxe");
    set_pshort("diamond edged lava powered pickaxes");
    set_long("A crazy gizmo made by Wilziver, or so says the signature, you wouldn't begin to " +
        "understand how this works, but apparently the lava flows from the tank to the custom engine " +
        "that converts it into raw energy, that is then used to activate the complicated inner clockwork, " +
        "which in turn vibrates the pickhead at amazing speeds, which allows the user to easily dig through " +
        "any rocky terrain. There's an inscription along the handle.\n");

    add_item(({"inscription"}), 
       "Remember you can <make> a new entrance if you find rich ore deposits, by <prospect>ing. And once " +
       "inside you should be able to <mine> the walls for them.\n" +
       "Also note you can <check> the lava meter and the speed dial, and also <turn> the speed dial to " +
       "adjust mining speed, although faster speeds means faster lava usage.\n" +
       "If you run out of lava, <refill> the lava tank near a lava source.\n");

    set_adj("heavy");
    set_adj("miner");
    set_adj("iron");
    set_default_weapon(9,8,W_CLUB,W_BLUDGEON,W_ANYH,0);
    add_prop(OBJ_I_WEIGHT,3000);
    add_prop(OBJ_I_VOLUME,500);
    add_prop(OBJ_I_VALUE, 1000);
    add_prop(OBJ_M_NO_GIVE, "You'd never give this to anyone, it's too precious for you. "+
                            "(you can <drop> it to get rid of it though)\n");
    add_prop(OBJ_M_NO_SELL, "You'd never sell this to anyone, it's too precious for you. "+
                            "(you can <drop> it to get rid of it though)\n");
}

/*
 * Function name: query_auto_load
 * Description  : Get the autoload information with the variables to keep.
 * Returns      : string - the autoload string.
 */
string
query_auto_load()
{
    return MASTER;
}

/*
 * Function name: query_recover
 * Description  : Remove recovery of item as it autoloads instead
 * Returns      : 0 / false
 */

string
query_recover()
{
   return 0;
}

void
init()
{
    ::init();
    add_action(do_dig, "make");
    add_action(do_prospect_ore, "prospect");
    add_action(do_turn_dial, "turn");
    add_action(do_turn_dial, "dial");
    add_action(do_refill_lava, "refill");
    add_action(do_check, "check"); //check dial/lava
}