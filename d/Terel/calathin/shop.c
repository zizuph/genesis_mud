/*
 * shop.c
 *
 * The silver forest trading post of Calathin.  Original version based on
 * Nick's shop and Tricky's shop in hobittown.  Modified by Vader on 920625.
 *
 * Sorgum.
 * Updated by Shinto 10-21-98
 */

#include "/d/Terel/include/Terel.h"
inherit "/d/Terel/std/shop";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>

#define STORE_ROOM CALATHIN_DIR +"store" 

/*
 * Function name:   create_shop
 * Description:     Initialize this shop
 * Returns:
 */
public void
create_shop()
{
    set_store_room(STORE_ROOM);
    
    set_long("You are in a large hollow in a tree.  There are many shelves " +
          "here where various goods are kept.  There is a counter here, " +
          "and behind it is a wall with some words painted on it.  It " +
          "says 'SILVER FOREST TRADING POST  owner Talok Smitt'.  " +
          "There is a ladder going up to the upper portions of the " +
          "tree here, and the exit is to the south. " +
          "There is also a small sign with more instructions.\n");
    
    set_short("Silver Forest Trading Post");
    set_shop_name("Silver Forest Trading Post");
    set_keeper_file(CALATHIN_DIR +"npc/smitt");

    hated_race = ({"goblin", "gnome"});
    favoured_race = ({"human","elf","half-elf"});    
    suspected_race = ({"dwarf", "kender", "hobbit"});

    add_exit(CALATHIN_DIR+ "square2_1", "south", 0);
    add_exit(STORE_ROOM,                       "up",    "@@wiz_check");
}
