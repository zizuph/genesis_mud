/*  
    Gold Ore

    Made by: Maelstrom, 2016/01

*/

inherit "/std/object";
#include "stdproperties.h"

#include "../common.c";

mapping ORE_TYPE = ORES["gold"];

void
create_object()
{
    set_name(({"ore", "ore_" + ORE_TYPE["name"]}));
    set_short(ORE_TYPE["name"] + " ore");
    set_long(ORE_TYPE["desc"]);
    set_adj(ORE_TYPE["name"]);
    add_prop(OBJ_I_VALUE, ORE_TYPE["value"]);
    add_prop(OBJ_I_WEIGHT, ORE_TYPE["weight"]);
    add_prop(OBJ_I_VOLUME, ORE_TYPE["volume"]);
}