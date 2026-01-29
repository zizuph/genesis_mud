/*
 * clear bit helper
 * by Boreaulam, Jan 2017
 */
#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "defs.h"

inherit "/std/object";

void
create_object()
{
    set_name("cb");
    set_adj("green");
    set_short("green cb");
    set_long("This is a green moss. It is rumoured to be a component " +
             "of goblin witch's alchemist recipe.\n");
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
    write("2");
}

void
init()
{
    ::init();
    write("1");
    add_action("cbgcl2", "cbgcl2", 0);
} /* init */


void
cbgcl2()
{
    write("3");
    this_player()->clear_bit(GOBLIN_LOVE_GROUP, GOBLIN_LOVE_BIT);
    this_player()->clear_bit(GOBLIN_DARTS_GROUP, GOBLIN_DARTS_BIT1);
    this_player()->clear_bit(GOBLIN_DARTS_GROUP, GOBLIN_DARTS_BIT2);
}

