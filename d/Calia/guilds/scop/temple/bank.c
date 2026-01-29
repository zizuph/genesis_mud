
/*
 * bank.c
 *
 * Banking Chamber for the Spirit Circle of Psuchae Temple
 * 
 *
 * Copyright (C): Jaacar (Mike Phipps), August 17th, 2003
 *
 */
 
#pragma strict_types
#pragma save_binary

inherit "/std/room";
inherit "/lib/bank";

#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#include "defs.h"
#include SPIRIT_HEADER

#define NUM sizeof(MONEY_TYPES)

void
create_room()
{
    set_short("A golden temple treasury");
    set_long("In contrast to the simplicity of the concentration chamber "+
        "to the south, this chamber is quite ornamented. Gemstones bejewel "+
        "the heavy gold panels on the walls, and set into the north wall is "+
        "a heavy golden vault with thick hinges. A few robed gnomes are kept "+
        "busy oiling the hinges and polishing the gemstones. Set into the wall "+
        "you see a golden plaque, and beneath it a sign written in a whimsical "+
        "script.\n");

    IN;
    clone_object("/d/Genesis/obj/deposit")->move(this_object(),1);

    add_item(({"plaque","golden plaque"}),"@@standard_bank_sign");
    add_cmd_item("plaque","read","@@standard_bank_sign");

    config_default_trade();
    set_bank_fee(20);
    config_trade_data();
    set_money_give_out(({100000,100000,100000,100000}));
    set_money_give_reduce(({0,0,0,0}));
    set_money_give_max(100000);

    add_prop(ROOM_M_NO_ATTACK,"You cannot attack in here, you are in a "+
        "sacred place!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"You cannot attack in here, you are in "+
        "a sacred place!\n");

    add_exit(SPIRIT_TEMPLE+"training_room","south",0,1);
}

void
init()
{
    ::init();
    bank_init();
}
