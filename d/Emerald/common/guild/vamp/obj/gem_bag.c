inherit "/std/receptacle";

#include <stdproperties.h>
#include <macros.h>

public int nodrop();

public void
create_receptacle()
{
    set_name("bag");
    add_adj(({ "leather", "gem" }));

    set_long("A fine leather bag.  Inspection of the inside reveals an " +
        "inscribed metal plate sewn into the lining.\n");

    add_item(({ "plate", "metal plate", "inscribed metal plate",
                "inscribed plate" }), 
        "The small, silver plate is inscribed with a peculiar symbol.\n");

    add_item(({ "symbol", "peculiar symbol", "rune", "magical rune" }),
        "A symbol is inscribed into the the silver plate inside the bag.  " +
        "Apparently it is this symbol which gives the bag its unique " +
        "properties.\n");

    add_prop(CONT_I_MAX_WEIGHT, 100000);
    add_prop(CONT_I_MAX_VOLUME, 100000);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_M_NO_DROP, nodrop);
    add_prop(CONT_I_WEIGHT, 200);
    add_prop(CONT_I_VOLUME, 200);
    add_prop(OBJ_M_NO_STEAL, 1);
}

public int
nodrop()
{
    return (this_interactive() != this_player());
}

/*
 * Function name: prevent_enter
 * Description:   Prevent an item from being put in this container
 * Arguments:     1. (object) The object entering
 * Returns:       True if the object is prevented from entering
 */
public int
prevent_enter(object ob)
{
    /* Only gems can be put inside */
    if (!ob->query_gem())
    {
        write("Some force from within the bag resists the " + ob->short() +
            ".  You are unable to put it inside.\n");
        return 1;
    }

    return 0;
}

public void
update_internal(int l, int w, int v)
{
    ::update_internal(l, w / 20, v / 20);
}

public string
query_auto_load()
{
    return MASTER + ":";
}
