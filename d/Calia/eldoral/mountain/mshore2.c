#include "defs.h"

#define HANGING_HORN     "_obj_hanging_horn"

inherit MOUNTBASE;

object skiff;


public int do_hang(string str);

public string
check_horn()
{
    if (query_prop(HANGING_HORN))
    {
        return "An ancient wooden frame rises from the rocky shore, " +
            "a rickety structure which supports a large ram's horn " +
            "by means of rusty iron chains.";
    }
    else
    {
        return "An ancient wooden frame rises crookedly from the " +
            "rocky shore, suspended from which stray iron chains " +
            "hang in cold silence.";
    }
}

public string
check_frame()
{
    if (!query_prop(HANGING_HORN))
        return "The wooden frame isn't constructed very solidly, " +
            "at least not anymore. It might have been quite strong " +
            "at one point, but it's obviously ancient, and the " +
            "damp lake air has taken a toll on the wood.\n";
    else
        return "The wooden frame isn't constructed very solidly, " +
            "at least not anymore. It might have been quite strong " +
            "at one point, but it's obviously ancient, and the damp " +
            "air has taken a toll on the wood. A ram's horn " +
            "is suspended from it by iron chains.\n";
}

public string
check_chains()
{
    string ret;
    ret = "The chains hanging from the wooden frame look very old, " +
        "and from the film of rust appear to have been forged from " +
        "wrought iron. ";
    if (query_prop(HANGING_HORN))
        ret += "A large ram's horn hangs from the chains, " +
            "suspended beneath the wooden frame.\n";
    else
        ret += "The chains hang cold and still, empty now, but " +
            "who knows what they once held.\n";
    return ret;
}

public void
create_room()
{
    extra = "@@check_horn:" + MASTER + "@@";
    create_shore();

    add_item(({"frame", "wooden frame"}), 
        "@@check_frame:/d/Calia/eldoral/mountain/mshore2@@");
    add_item(({"chains", "chain", "iron chain", "iron chains"}),
        "@@check_chains:/d/Calia/eldoral/mountain/mshore2@@");
    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_prop(OBJ_S_WIZINFO, "This room is a 'port'for a " +
        "small boat that players take to get across " +
        "the lake to Eldoral Isle. It's not a normal " +
        "boat, rather it comes when summoned and " +
        "then vanishes once the player reaches the " +
        "other side. Players get it by using the horn " +
        "/d/Calia/eldoral/objects/horn.c, but wizards " +
        "can bring the skiff here by doing " +
        "'Call here try_to_start_skiff'.\n");
    add_prop(ROOM_I_IS_SKIFF_PORT, 1);
    add_prop(ROOM_I_TYPE, ROOM_BEACH);

    add_exit(MOUNT + "mshore3", "east");
    add_exit(MOUNT + "mshore1", "west");
    add_exit(MOUNT + "m16", "south");
}

public void
try_to_start_skiff()
{
    if (!skiff || !objectp(skiff))
    {
        seteuid(getuid());
        skiff = clone_object(OBJ + "skiff");
        skiff->next_sail(0);
    }
    else if (!skiff->query_sailing())
    {
        skiff->next_sail(0);
    }
}

public object
query_skiff()
{
    return skiff;
}

public void
init()
{
    ::init();
    init_shore();
    add_action(do_hang, "hang");
    add_action(do_hang, "suspend");
}

public int
do_hang(string str)
{
    object horn;
    string where;

    notify_fail(capitalize(query_verb()) + " what?\n");

    if (!str || !strlen(str))
        return 0;

    if (sscanf(str, "%s from %s", str, where) != 2)
    {
        notify_fail("Hang what from what?\n");
        return 0;
    }

    if (!objectp(horn = present(str, TP)))
        return 0;

    if (where != "frame" && where != "chains" &&
        where != "wooden frame")
    {
        notify_fail("Hang the " + horn->short() + " from what?\n");
        return 0;
    }

    if (!horn->id("_eldoral_lake_horn"))
    {
        write("The " + horn->short() + " doesn't seem to fit " +
            "properly.\n");
        return 1;
    }

    horn->move(TO);
    horn->hang_horn();
    add_prop(HANGING_HORN, horn);
    TP->add_prop(LIVE_I_HORN_QUEST,
        TP->query_prop(LIVE_I_HORN_QUEST) | HQ_HUNG_HORN);
    write("You carefully hang the horn from the chains in the " +
        "wooden frame.\n");
    say(QCTNAME(TP) + " carefully hangs a horn from the chains in " +
        "wooden frame.\n");
    return 1;
}
