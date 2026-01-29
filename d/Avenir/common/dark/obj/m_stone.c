// -*-C++-*-
// Stone for magic square quest.
// Made by Boriska@Genesis

inherit "/std/heap";

#include "stdproperties.h"
#include "/d/Avenir/include/magic_square.h"

static string color;

public void
create_heap(void)
{
    set_name("stone");
    set_pname("stones");

    add_prop (HEAP_I_UNIT_WEIGHT, 1);
    add_prop (HEAP_I_UNIT_VOLUME, 1);
    add_prop (HEAP_I_UNIT_VALUE, 1);
    add_prop (HEAP_S_UNIQUE_ID, "hjhj");

    set_heap_size (1);
}

public string
long()
{
    return (num_heap() == 1) ?
    "Small " + color + " stone, polished and round in shape.\n" :
    "Pile of polished and round-shaped " + color + " stones.\n";
}

public void
set_quest_id (string id, int ver)
{
    add_prop (QUEST_ID, id);
    add_prop (QUEST_VERSION, ver);
}

public string
query_color(void)	{ return color; }

public void
set_color (string cl)
{
    color = cl;
    set_short (color + " stone");
    set_pshort(color + " stones");
    add_adj (color);
    add_prop (HEAP_S_UNIQUE_ID, "_avenir_" + color + "_stone");
}

public void
config_split(int new_num, object orig)
{
    ::config_split(new_num, orig);
    add_prop(QUEST_ID, orig->query_prop(QUEST_ID));
    add_prop(QUEST_VERSION, orig->query_prop(QUEST_VERSION));
    set_color(orig->query_color());
}
