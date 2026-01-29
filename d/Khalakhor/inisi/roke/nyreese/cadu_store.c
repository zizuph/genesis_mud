/*
 * cadu_store.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/*
 *   The storage room of the Solamnian drugstore, made by Nick
 *   borrowed by Gresolle for Re  Albi
 *
 *  updated by Amelia, 7/97, to include equipment
 *  check_equip_inventory checks to see if one of
 *  each is available 1) in reset_room 2) when something
 *  is purchased (in leave_inv) to make sure store is
 *  always stocked with backpacks, etc.
 *  
 *  took out sack temporarily;) 8/6/97 Amelia
 *  took out all Earthsea equipment 8/30/97
 *  took out torch/lamp/flask (orig from vladimir's directory)
 * 9/14/97
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/lib/store_support";

#include "defs.h"
#define SHOP NYREESEDIR + "cadu_shop"

void
reset_room()
{
    object ob;

    if (!present("torch", TO))
    {
        ob = clone_object(ROKEDIR + "obj/torch");
        ob->move(TO);
    }
}

void
create_room()
{
    set_short("The shop's store room");
    set_long("This is the store room for the shop.\n");

    add_exit(SHOP, "east");

    INSIDE;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}
