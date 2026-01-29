/*
 *  Base functionality for the treasure chart.
 *
 *  To create a new treasure chart, inherit this object and create the
 *  list by overriding the create_treasure_chart() function.
 *
 *  public void
 *  create_treasure_chart()
 *  {
 *     set_short("myth treasure chart");
 *     add_treasure_for_type(TREASURE_MINOR_ITEM1, ({ 
 *         "/d/Gondor/common/obj/shovel",
 *         "/d/Gondor/common/obj/hammer"
 *     }));
 *  }
 *
 *  Both filenames as well as function pointers can be added to the
 *  treasure table. When an item is randomly created, it's either
 *  cloned or the function executed. If the function returns an 
 *  empty array, the next item is attempted.
 */

#include "../defs.h"
#include <money.h>

inherit "/std/object";

mapping treasures_for_type = ([ ]);
public void add_treasure_for_type(string type, mixed treasure);
public object *create_money(int pc, int gc, int sc, int cc);
public object *clone_unique(string filename, int maximum_number);

void
create_treasure_chart()
{
    add_treasure_for_type(TREASURE_MINOR_ITEM1, ({ 
        "/d/Gondor/common/obj/shovel",
        "/d/Gondor/common/obj/hammer",
        &create_money(0, 0, 0, 10)
    }));
}

nomask void 
create_object()
{
    set_short("base treasure chart");

    create_treasure_chart();
}

public void
add_treasure_for_type(string type, mixed treasure)
{
    if (!pointerp(treasure)) treasure = ({ treasure });
    if (!treasures_for_type[type]) treasures_for_type[type] = ({ });
    treasures_for_type[type] += treasure;
}

public mixed
query_treasure_for_type(string type)
{
    if (!treasures_for_type[type]) return ({ });
    return treasures_for_type[type];
}

private object *
clone_treasure(mixed treasure, object player)
{
    if (functionp(treasure)) return treasure(player);
    setuid();
    seteuid(getuid());
    return ({ clone_object(treasure) });
}

public object *
create_treasure_for_type(string type, object player)
{
    mixed *treasure_options = query_treasure_for_type(type);
    while(sizeof(treasure_options))
    {
        mixed selected_treasure = treasure_options[random(sizeof(treasure_options))];
        treasure_options -= ({ selected_treasure });

        object *treasure = clone_treasure(selected_treasure, player);
        if (sizeof(treasure)) return treasure;
    }

    return ({ });
}

public mixed
create_all_treasures_for_type(string type, object player)
{
    object *result = ({ });
    foreach(mixed treasure : query_treasure_for_type(type)) {
        result += clone_treasure(treasure, player);
    }

    return result;
}

public object *
create_money(int pc, int gc, int sc, int cc)
{
    setuid();
    seteuid(getuid());

    object *result = ({ });
    if (pc) result += ({ MONEY_MAKE_PC(pc) });
    if (gc) result += ({ MONEY_MAKE_GC(gc) });
    if (sc) result += ({ MONEY_MAKE_SC(sc) });
    if (cc) result += ({ MONEY_MAKE_CC(cc) });
    return result;
}

public object *
clone_unique(string filename, int maximum_number)
{
    object item = "/lib/unique"->clone_unique(filename, maximum_number);
    if (objectp(item)) return ({ item });
    return ({ });
}
