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
inherit "/lib/bank";

#include <stdproperties.h>
#include <macros.h>

#include "defs.h"
#include S_DOMAIN_SYS_LINKS

void reset_room();

void
create_room()
{
    config_default_trade();

    set_short("Dwarven bank");

    set_long(BS("\nThis is the dwarven branch of the famous Gnome banking chain. A peculiar feeling permeates the room, a pleasant smell caresses your nose wakening strange feelings of greed and want in your mind. In short, the place stinks of money.\nA small plaque is attached to one of the walls.\n"));

    add_prop(ROOM_I_INSIDE, 1);

    add_exit ("corr7","south");

    add_item("plaque","@@standard_bank_sign");
    add_cmd_item("plaque","read", "@@standard_bank_sign");

    set_bank_fee(20);

    config_trade_data();

    room_add_object(S_LINK_BANK_DEPOSIT);

    reset_room();
}

void
reset_room()
{
    object misc;

//     if (!present("deposit", TO))
//     {
// 	say("A small hut suddenly appears in a puff of smoke!\n");
// 	misc = clone_object("/d/Genesis/obj/deposit");
// 	misc->move(this_object(), 1);
//     }

    if (!present("ratty", TO))
        room_add_object(S_LOCAL_NPC_DIR + "ratty");

//     {
// 	say("A small black rat crawls out of a crevice in a corner of the room.\n");
// 	misc = clone_object("/d/Genesis/start/dwarf/monster/ratty.c");
// 	misc->move(TO, 1);
//     }
}

void
init()
{
    ::init();

    bank_init();
}

