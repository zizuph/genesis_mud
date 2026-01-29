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
 *
 * Based on the Dwarfheim bank. The bank fee randomly changes. 
 * If the fee is less than 5%, then the fee is set to 10%. 
 * The max fee is 35%.
 * -- Finwe, May 2001
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Shire/room";
inherit "/lib/bank";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void reset_room();

void
create_shire_room()
{

    config_default_trade();

    set_short("Bank of Bree");
    set_long(
      "This is the bank of Bree. The hobbits themselves never liked "+
      "the idea of a bank, since they don't bother much with money. "
      +"So they let the gnomes take care of that, since more and more "
      +"people stop by this town, the need for a trustworthy bank has "
      +"grown. Behind the iron-barred counter is a gnome with greedy "
      +"little eyes. There is a plaque and a sign on the wall.\n");
    add_item(({"counter", "large counter"}),
        "The counter is made from a single piece of wood. It is " +
        "a deep honey color and gleams from constant polishing.\n");
    add_item(({"gnome","clerk"}),
      "The gnome looks busy as he looks over his books. He " +
      "looks well preserved and ready to assist you.\n");
    add_prop(ROOM_I_INSIDE, 1);

   add_exit(BREE_DIR + "ncross","west",0,1);


    add_item("plaque","@@standard_bank_sign");
    add_cmd_item("plaque","read", "@@standard_bank_sign");

    bank_fee=random (35);
    if(bank_fee<5)
        bank_fee=11;

//    set_bank_fee(random(19) + random(7));
    set_bank_fee(bank_fee);

    config_trade_data();

    room_add_object("/d/Genesis/obj/deposit");

    reset_room();
}

void
reset_room()
{
}

void
init()
{
    ::init();
    bank_init();

}
