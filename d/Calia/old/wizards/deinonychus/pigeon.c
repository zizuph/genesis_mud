/* pigeons.c->vin38.c, made by Nick modified by percy. */

#include "/d/Krynn/common/defs.h"
inherit "/std/room";
#include "local.h"
#include "guild.h"
#include <macros.h>
#include <money.h>

create_room()
{
    set_short("At the pigeon house");
    set_long("You are in a small room with a lot of pigeons in it. They " +
	     "make a very strange sound and smell funny. You see a small " +
	     "sign on the wall.\n");
    
    add_item("pigeons", "There are both black and white pigeons, they " +
	     "are all over the place.\n");
    add_item("sign", "Someone has written something on the sign.\n");
    add_cmd_item("sign", "read", "Fine carrier pigeons, 99 copper each.\n");
    
    add_exit(VDIR + "f_eaststreet.c", "south", 0);
    
    INSIDE;
    set_alarm(1.0,0.0,"reset_room");
}

reset_room()
{
    if (!P("pig_gnome", TO))
      clone_object(MNSTR + "pig_gnome")->move_living("xx", TO);
}

init()
{
    ::init();
    ADA("buy");
}

buy(str)
{
    object pig,who;
    NF("Buy what did you say?\n");
    if (!str || (str != "pigeon"))
	return 0;

    NF("There is noone here who can sell it to you.\n");
    if (!P("pig_gnome", TO))
	return 0;

    NF("You cannot pay the price.\n");
    if (!MONEY_ADD(TP, -99))
	return 0;

    write("You pay the gnome and he gives you a pigeon.\n");
    say(QCTNAME(TP) + " buys a pigeon from the gnome.\n");

    who = TP;
    pig = clone_object(MNSTR + "pigeon");
    pig->set_owner(who);
    pig->move(who);
    return 1;
}
