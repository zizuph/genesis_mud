/*
 * Random item for the Scavanger hunt
 * Coded by Finwe September 2003
 * Originally coded for the Shire, cleaned up in October 2015
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/std/object";

void
create_object()
{
    seteuid(getuid());
    set_name("fish");
    add_name("dead fish");
    set_pname("dead fishes");
    set_adj("smelly");
    set_adj("old");
    set_long("This is a old, smelly, dead fish. It is partially decomposed " +
        "and stinks terribly. Why anyone would want to keep it is " +
        "anyone's guess.\n");

    add_item(({"bones"}),
        "Most of the bones are gray and look broken or gnawed on. They " +
        "are mostly bare except for some flesh still remaining.\n");
    add_item(({"flesh"}),
        "The flesh is rotten and disgusting looking. It hangs in pieces " +
        "from the bones and smells putrid.\n");
    add_item(({"tail"}),
        "The tail is dried and curled up. It has a chunk missing from it.\n");
    add_item(({"head", "skull"}),
        "The head of the fish is missing. It looks like someone or " +
        "something bit it off.\n");
    add_item(({"fins"}),
        "The fins are dried and curly.\n");

    add_prop(OBJ_I_VALUE, 100);
}
