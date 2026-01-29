/* This is a room in the elemental area northeast of the
frog pond in Calia. By Bishop, 5.2.99 */

inherit "/std/room";

#include <stdproperties.h>
#include <ss_types.h>
#include <pond.h>
#include <macros.h>
#include <filter_funs.h>
#include <composite.h>

public string climbers();
public string bathers();
public int do_climb(string str);
public int do_enter(string str);

create_room()
{
    set_short("At the edge of a bubbling pool");

    set_long("You're standing near a bubbling pool that lies at" +
        " the bottom of a cliff. To your south lies a forest, with" +
        " a path leading into it.@@bathers@@ To" +
        " the northwest, at the foot of the mountains, lies a" +
        " barren area.\n");

    add_item(({"spring", "hot spring", "pool"}), "Steam rises up" +
        " from this small hot spring, but the water doesn't seem" +
        " too hot for a bath.\n");
    add_item(({"cliff face", "cliff"}), "The cliff is jagged, and" +
        " you see @@climbers@@. There" +
        " seems to be a plateau on the top of the cliff.\n");
    add_item("plateau", "The angle is all wrong, you can't get a" +
        " good look at it from down here.\n");
    add_item("steam", "It's evaporated water, but at far from a" +
        " scalding temperature.\n");
    add_item("barren area", "The green of the forest gradually" +
        " fades away to make room for the browns and greys of" +
        " an area of strewn boulders and sand. You hear a low" +
        " rumble from there.\n");
    add_item("mountains", "The mountains rise to the north and" +
        " west, casting this area in shadow much of the day.\n");
    add_item("path", "The thin path leads straight into the" +
        " forest.\n");

    add_prop(ROOM_I_HIDE, 90);
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(FPATH + "epath2", "southwest", 0, 1);
    add_exit(FPATH + "epath3", "northwest", 0, 1);
    add_exit(FPATH + "hot_springs", "_no_exit_", 1, 1, 1);
}

string
bathers()
{
    object pool = find_object("/d/Calia/pond/hot_springs");
    object *pool_live;

    if (!pool)
    {
        return "";
    }    
    else
    if (pool->query_prop(ROOM_I_LIGHT) > 0 
        || TP->query_prop(LIVE_I_SEE_DARK))
    {
        pool_live = FILTER_LIVE(all_inventory(pool));

        if(sizeof(pool_live))
        {
            return " You see " +
            COMPOSITE_ALL_LIVE(pool_live) + " soaking in the pool.";
        }
        else
        {
            return "";
        }
    }
    else
    {
        return "It's dark in the pool.";
    }
}

string
climbers()
{
    object half = find_object("/d/Calia/pond/cliff_halfway");
    object *half_live;

    if (!half)
    {
        return "a ledge about halfway up the cliff";
    }    
    else
    if (half->query_prop(ROOM_I_LIGHT) > 0 
        || TP->query_prop(LIVE_I_SEE_DARK))
    {
        half_live = FILTER_LIVE(all_inventory(half));

        if(sizeof(half_live))
        {
            return "a ledge about halfway up the cliff, with " +
            COMPOSITE_ALL_LIVE(half_live) + " standing on it";
        }
        else
        {
            return "a ledge about halfway up the cliff";
        }
    }
    else
    {
        return "that there's a dark spot about halfway up the cliff";
    }
}

int
do_climb(string str)
{
    int skill = TP->query_skill(SS_CLIMB);

    if (str == "cliff" || str == "the cliff")
    {
        if (skill > 29)
        {
            TP->catch_msg("You climb up the cliff face.\n");
            tell_room(environment(TP), QCTNAME(TP) + " climbs" +
                " up the cliff.\n", TP);
            TP->move_living("M", FPATH + "cliff_halfway", 1);
            tell_room(environment(TP), QCTNAME(TP) + " arrives" +
                " climbing from below.\n", TP);
            return 1;
        }
        else
        {
            notify_fail("It looks too steep.\n");
            return 0;
        }
    }
    else
    {
        notify_fail("Climb where?\n");
        return 0;
    }
}

int
do_enter(string str)
{
    if (str == "pool" || str == "into pool" 
        || str == "into the pool")
    {
        write("You ease yourself into the hot waters of the" +
            " pool.\n");
        tell_room(environment(TP), QCTNAME(TP) + " steps into" + 
            " the pool, and eases " +
            TP->query_objective() + "self into the hot waters.\n",
            TP);
        TP->move_living("M", FPATH + "hot_springs", 1);
        tell_room(environment(TP), QCTNAME(TP)+ " arrives and eases"+
            " " +TP->query_objective() + "self into the hot waters"+
            " of the pool.\n", TP);
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
    add_action(do_climb, "climb");
    add_action(do_enter, "enter");
    ::init();
}
