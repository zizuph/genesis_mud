/*
 * Copyright notice, please read.
 *
 * Copyright Chalmers Datorf|rening, 1992
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/lib/shop";

#include <stdproperties.h>

#include "../defs.h"

#define STORE (LVL1+"store")

void
create_room()
{
    set_short("Shop");
    set_long("You are in the shop in Dwarfheim. Around you are lots of\n"+
             "interesting shelves with various items. There is a small\n"+
             "sign on one of the walls, just above a large counter, behind\n"+
             "which the shopkeeper sits and guards his belongings.\n");

    config_default_trade();

    add_exit(LVL1+"corr1","south");

    add_item("counter","It's a large oak counter.\n");
    add_item("various items","There are many of them, try typing 'list' for more.\n");
    add_item("shopkeeper", "He looks as if he wouldn't mind taking your money.\n");
    add_item("belongings", "Those are the shopkeepers!\n");
    add_item("shelves","The shelves are filled with items.\n");

    add_prop(ROOM_I_INSIDE,1);
    set_store_room(STORE);
}

void
init()
{
  ::init();

  init_shop();
}
