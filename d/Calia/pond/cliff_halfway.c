/* This is a room in the elemental area northeast of the
frog pond in Calia. By Bishop, 5.2.99 */

inherit "/std/room";

#include <stdproperties.h>
#include <ss_types.h>
#include <pond.h>
#include <macros.h>
#include <filter_funs.h>
#include <composite.h>

public int do_climb(string str);
public string exa_pool();

create_room()
{
    set_short("On a ledge, halfway up a cliff");

    set_long("You're standing on a ledge about halfway up a cliff." +
        " About fifty feet below lies a hot pool, its warm vapors"+
        " barely reaching you. A like distance above you lies what" +
        " seems to be a larger plateau. The ledge under your feet" +
        " isn't broad enough to provide comfortable footing, and" +
        " you'd need to move further up to get a good view of the" +
        " surrounding area.\n");

    add_item("ledge", "It's narrow and somewhat slippery from the" +
        " steam rising up from the hot springs below.\n");
    add_item("plateau", "The angle is too steep for you to see if" +
        " there's anyone or anything up there.\n");
    add_item(({"hot pool", "pool"}), "It's a good" +
        " distance under you. @@exa_pool@@\n");
    add_item(({"cliff", "cliff face"}), "The cliff is jagged, but" +
        " possible to climb without too much difficulty.\n");
    add_item(({"vapor","vapors"}), "It's evaporated water from the" +
        " springs below.\n");

    add_prop(ROOM_I_HIDE, 90);
    add_prop(ROOM_I_INSIDE, 0);
}

string
exa_pool()
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
            return "You see someone is in the pool: " +
            COMPOSITE_ALL_LIVE(pool_live) + ".";
        }
        else
        {
            return "";
        }
    }
    else
    {
        return "It's dark down there.";
    }
}
int
do_climb(string str)
{
    int skill = TP->query_skill(SS_CLIMB);

    if (str == "down")
    {
        if (skill > 29)
        {
            TP->catch_msg("You climb down the cliff face.\n");
            tell_room(environment(TP), QCTNAME(TP) + " climbs" +
                " down the cliff.\n", TP);
            TP->move_living("M", FPATH + "env_hot_springs", 1);
            tell_room(environment(TP), QCTNAME(TP) + " arrives" +
                " climbing from above.\n", TP);
            return 1;
        }
        else
        {
            notify_fail("It looks too steep.\n");
            return 0;
        }
    }
    else
    if (str == "up")
    {
        if (skill > 29)
        {
            TP->catch_msg("You climb up the cliff face.\n");
            tell_room(environment(TP), QCTNAME(TP) + " climbs" +
                " up the cliff.\n", TP);
            TP->move_living("M", FPATH + "clifftop", 1);
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

void
init()
{
    add_action(do_climb, "climb");
    ::init();
}