/*
 * treasurechest.c
 *
 * Used in carisca/d5.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/container";

#include "defs.h"
#include <stdproperties.h>
#include <money.h>
#include <macros.h>

string
mylong()
{
    string s;

    s = "This is a metal-reinforced wooden chest used to keep valuables.\n";

    if (query_prop(CONT_I_CLOSED))
        return s + "The chest is closed.\n";

    return s + "The chest is open.\n";
}

void
create_container()
{
    if (!IS_CLONE) return;

    set_short("treasure chest");
    set_long("@@mylong");
    set_name("chest");
    set_adj("treasure");

    add_prop(OBJ_I_VALUE, 2000);

    add_prop(CONT_I_VOLUME, 10000);
    add_prop(CONT_I_WEIGHT, 10000);
    add_prop(CONT_I_REDUCE_WEIGHT, 3);
    add_prop(CONT_I_REDUCE_VOLUME, 3);

    add_prop(CONT_I_MAX_WEIGHT, 40000);
    add_prop(CONT_I_MAX_VOLUME, 40000);
}

int
open(string s)
{
    NF("Open what?\n");
    if (s != "chest" && s != "the chest" && s != "treasure chest")
        return 0;

    NF("The chest is already open.\n");
    if (!query_prop(CONT_I_CLOSED))
        return 0;

    write("You open the chest.\n");
    say(QCTNAME(TP) + " opens a chest.\n");

    remove_prop(CONT_I_CLOSED);
    return 1;
}

int
close(string s)
{
    NF("Close what?\n");
    if (s != "chest" && s != "the chest" && s != "treasure chest")
        return 0;

    NF("The chest is already closed.\n");

    if (query_prop(CONT_I_CLOSED))
        return 0;

    write("You close the chest.\n");
    say(QCTNAME(TP) + " closes a chest.\n");

    add_prop(CONT_I_CLOSED, 1);
    return 1;
}

void
init()
{
    ::init();
    add_action(open, "open");
    add_action(close, "close");
}

void
fill_chest()
{
    seteuid(getuid());
    if (!present("bar", TO))
    {
        clone_object(ROKEDIR + "obj/goldbar")->move(TO);
        clone_object(ROKEDIR + "obj/goldbar")->move(TO);
        clone_object(ROKEDIR + "obj/goldbar")->move(TO);
        clone_object(ROKEDIR + "obj/goldbar")->move(TO);
        clone_object(ROKEDIR + "obj/goldbar")->move(TO);
    }
    if (!present("coin", TO))
        MONEY_MAKE_CC(1000)->move(TO);

    add_prop(CONT_I_CLOSED, 1);
}
