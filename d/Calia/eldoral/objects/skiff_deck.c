#include "../defs.h"
#include <composite.h>
#include <filter_funs.h>

inherit STDROOM;

public int do_disembark(string str);
public void check_skiff();

object skiff;
string *base_items;

public mixed
query_base_items()
{
    int i,
        j;
    string *temp;
    string *temparr;
    temp = ({});
    temparr = ({});
    if (!base_items || !pointerp(base_items))
        return ({});

    for (i = 0; i < sizeof(base_items); i++)
    {
        if (pointerp(base_items[i][0]) && sizeof(base_items[i][0]))
        temparr = ({base_items[i][0]})[0];
        if (!pointerp(temparr))
            temp += ({temparr});
        else if (sizeof(temparr))
        {
            for (j = 0; j < sizeof(temparr); j++)
                temp += ({temparr[j]});
        }
    }

    return temp;
}

public string
surroundings()
{
    string ret;
    object *temp;
    object *live, *dead;

    if (!skiff || !environment(skiff))
        return("You are in nothing! Better call a wiz to rescue you, " +
            "and leave a bug report.\n");

    ret = environment(skiff)->long();

    temp = FILTER_CAN_SEE(all_inventory(environment(skiff))-({skiff}), TP);
    if (sizeof(dead = FILTER_DEAD(temp)))
        ret += capitalize(COMPOSITE_DEAD(dead)) + "\n";
    if (sizeof(live = FILTER_LIVE(temp)))
        ret += capitalize(COMPOSITE_LIVE(live)) + "\n";
    return ret;
}


public void
create_room()
{
    set_short("inside a small skiff");
    set_long("You are within a small, wooden skiff. The construction " +
        "is rather strange, small craft seems to be made from a " +
        "single piece of wood, carefully carved. It must have " +
        "been a huge piece of wood, as an ornately curved " +
        "dragon has been carved onto the bow of the skiff. " +
        "To make matters worse, there appears to be no logical " +
        "source of motion, yet sail it does.\n");

    add_item(({"surroundings", "view"}), "@@surroundings");
    add_item(({"dragon", "carving", "bow", "figurehead'"}),
        "The dragon has only been carved from the neck up, a " +
        "long slender neck hooked at the end forms an elegant " +
        "S-shaped figurehead carved from the same piece of " +
        "wood as the rest of the skiff.\n");
    base_items = query_item();
    set_alarm(1.0, 0.0, check_skiff);

}

public void
init()
{
    ::init();
    add_action(do_disembark, "disembark");
    add_action(do_disembark, "leave");
}

public int
do_disembark(string str)
{
    if (query_verb() == "leave" &&
        (str != "ship" && str != "skiff"))
        return 0;

    if (!environment(skiff)->query_prop(ROOM_I_IS_SKIFF_PORT))
    {
        write("That water looks much to cold and deep to just " +
            "bail over the side of the skiff into. Plus it's " +
            "small it's just as likely to roll over and drag you " +
            "to the bottom, better hold tight for awhile.\n");
        return 1;
    }

    write("You carefully step out of the skiff.\n");
    say(QCTNAME(TP) + " carefully steps out of the skiff.\n");
    TP->move_living("M", environment(skiff), 1, 0);
    say(QCTNAME(TP) + " carefully steps out of the skiff.\n");
    if (sizeof(FILTER_OTHER_LIVE(all_inventory(TO))))
        return 1;

    write("As soon as you've stepped out of the skiff, it " +
        "slowly slips away out across the water, and vanishes " +
        "into the mist.\n");
    say("As soon as " + QCTNAME(TP) + " steps out of the skiff, it " +
        "slowly slips away out across the water, and vanishes " +
        "into the mist.\n");
    skiff->remove_object();
    remove_object();
    return 1;
}

public void
set_skiff(object ob)
{
    skiff = ob;
}

public object
query_skiff()
{
    return skiff;
}

public object
query_environment()
{
    if (skiff)
        return environment(skiff);
}

public void
check_skiff()
{
    object *temp;
    if (!skiff)
    {
        if (!find_object(OBJ + "skiff"))
            (OBJ + "skiff")->load_me();
        temp = object_clones(find_object(OBJ + "skiff"));
        if (sizeof(temp))
            skiff = temp[sizeof(temp) - 1];
        else
        {
            skiff = clone_object(OBJ + "skiff");
            skiff->move(MOUNT + "mshore2");
        }
    }
}
