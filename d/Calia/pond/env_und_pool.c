/* This is a room in the elemental area northeast of the
frog pond in Calia. By Bishop, 5.2.99 */

inherit "/std/room";

#include <stdproperties.h>
#include <ss_types.h>
#include <pond.h>
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>

public string pool();
public int do_enter(string str);

create_room()
{
    set_short("On a ledge over an underground pool");

    set_long("You are standing on a ledge a couple of feet over" +
        " the surface of an underground pool. The ledge is cast" +
        " in shadow as the light from above the pool doesn't reach" +
        " here. A corridor leads into the mountain to your east.\n");

    add_item("ledge", "The ledge is completely dry, in spite of" +
        " being so close to water.\n");
    add_item(({"underground pool", "pool"}), "@@pool@@\n");
    add_item(({"shadow", "shadows"}), "Someone could easily hide" +
        " in the deep shadows here.\n");
    add_item("corridor", "The corridor is big enough that a large" +
        " human could walk without crouching down.\n");

    add_prop(ROOM_I_HIDE, 10);
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(FPATH + "und_corridor", "east", 0, 1);
    add_exit(FPATH + "underground_pool", "_no_exit_", 1, 1, 1);
}

string
pool()
{
    object pool = find_object("/d/Calia/pond/underground_pool");
    object *pool_live;

    if (!pool)
    {
        return "Some of the light from above reaches this dark" +
            " pool, refracting off its surface. The water is" +
            " completely still.";
    }    
    else
    if (pool->query_prop(ROOM_I_LIGHT) > 0 
        || TP->query_prop(LIVE_I_SEE_DARK))
    {
        pool_live = FILTER_LIVE(all_inventory(pool));

        if(sizeof(pool_live))
        {
            return "Some of the light from above reaches this dark" +
                " pool, refracting off its surface. The water is" +
                " only disturbed by the movements of " +
            COMPOSITE_ALL_LIVE(pool_live) + ".";
        }
        else
        {
            return "Some of the light from above reaches this dark" +
                " pool, refracting off its surface. The water is" +
                " completely still.";
        }
    }
    else
    {
        return "The pool seems completely dark.";
    }
}

 

int
do_enter(string str)
{
    if (str == "pool" || str == "the pool")
    {
        write("You wade into the pool. The water is a bit cold.\n");
        tell_room(environment(TP), QCTNAME(TP) + " wades into the" +
            " pool.\n", TP);
        TP->move_living("M", FPATH + "underground_pool", 1);
        tell_room(environment(TP), QCTNAME(TP) + " arrives from the"+
            " shore.\n", TP);
        return 1;
    }
    else
    {
        notify_fail("Enter what? The pool perhaps?\n");
        return 0;
    }
}

void
init()
{
    add_action(do_enter, "enter");
    add_action(do_enter, "wade");
    ::init();
}
