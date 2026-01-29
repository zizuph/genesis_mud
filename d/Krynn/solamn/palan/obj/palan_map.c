/*
 * Filename:        palan_map
 * Description:     This is a map of Palantas, the players can buy
 *
 * Copyright (c) 2003 by Daniel W. Mathiasen, Boron
 *
 * Revision history:
 * ----------------------
 *
 */
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit "/std/scroll";

void
create_scroll()
{
    set_file(OBJ + "/palan_map.txt");

    set_name("map");
    add_name("_palan_map");
    add_adj(({"parchment"}));

    add_prop(OBJ_I_WEIGHT, 30);
    add_prop(OBJ_I_VOLUME, 70);
    add_prop(OBJ_I_VALUE,  15);

    set_short("parchment map of Palanthas");
    set_long("This is a map of Palanthas drawn on parchment of a high "
            + "quality, someone obviously made a great effort in creating "
            + "this map. You can unroll and read the map with <read map>.\n");

    add_cmd_item("scroll", ({"destroy", "tear", "burn"/*, "eat"*/}),
                 ({"@@tear", "@@tear", "@@burn" /*, "@@eat"*/}));

}

string
tear()
{
    TO->remove_object();
    return "You tear the scroll a part!\n";
}

string
burn()
{
    TO->remove_object();
    return "You burn the scroll until there is nothing but light ashes left!\n"
            + "The ashes blows away in the wind.\n";
}

void
eat()
{
    TO->remove_object();
    write("You chew on the scroll abit and swallow it!\n");
    TP->command("swallow");
    TP->command("burp");
}

