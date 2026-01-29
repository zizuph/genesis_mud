/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/* 
   An example shop coded by Nick, some Ideas and part of code taken from 
   Tricky's shop in hobbitown.

    This is the Northern port of Terel shop. Modified by
    Vader on 10/8/93

    Modified by Sorgum 12/4/94
	            Lilith Feb 2022: added inside prop
*/
#include "/d/Terel/include/Terel.h"
inherit "/d/Terel/std/shop";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>

#define STORE_ROOM    NPORT_DIR + "store" 


/*
 * Function name:   create_shop
 * Description:     Initialize this shop
 * Returns:
 */
public void
create_shop()
{
    set_store_room(STORE_ROOM);
    set_short("General store of the town of Last");
    set_shop_name("General store");    
    set_long("This is a rather large building, made of stones that " +
             "are cut to look like blocks of ice. There are items " +
             "and wares gathered neatly all throughout this store. " +
             "You can purchase supplies for your adventures here. " +
             "Additional items are kept hidden by the shopkeeper." +
             " There is a sign here for instructions for using the shop.\n");
    
    set_keeper_file(NPORT_DIR +"monster/smiley");

    hated_race = ({"elf", "hobbit"});
    favoured_race = ({"human"});    
    suspected_race = ({"dwarf", "goblin", "gnome"});
	add_prop(ROOM_I_INSIDE, 1);
    add_exit(NPORT_DIR + "np_road4", "south", 0);
    add_exit(STORE_ROOM,             "up",    "@@wiz_check");
}

/*
 * Function name: shop_hook_allow_sell
 * Description:	  If you want to do more testing on objects the player intend
 *		  to sell.
 * Argument:	  ob - The object player wants to sell
 * Returns:	  1 if we allow player to sell the object (default)
 */
public int
shop_hook_allow_sell(object ob)
{
    if (MASTER_OB(ob) == TANTO) {
	keeper->command("gasp");
	keeper->command("say I won't buy that accursed knife!");
	keeper->command("say If Benton found out he would kick my ass!");
	NF("");
	return 0;
    }

    if (MASTER_OB(ob) == KATANA) {
	keeper->command("say If you had a real katana I might buy it.");
	keeper->command("say I won't buy a _stone_ katana.");
	NF("");
	return 0;
    }

    if (MASTER_OB(ob) == OSWORD) {
	keeper->command("say I don't buy stone swords like that one!");
	NF("");
	return 0;
    }

    if ((MASTER_OB(ob) == BSWORD) || (MASTER_OB(ob) == LSWORD) ||
	(MASTER_OB(ob) == MDAGGER)) {
	keeper->command("ponder the cabinet");
	NF("");
	return 0;
    }

    return ::shop_hook_allow_sell(ob);
} 

