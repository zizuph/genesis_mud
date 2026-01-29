/*
* Stable area of Bree
* by Rob Cakebread
* Dec 2002
 */

 
 
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "stables.h"
#include <stdproperties.h>
#include <terrain.h>
#include <filter_funs.h>

inherit FAERUN_OUTDOOR_BASE;
inherit "/d/Gondor/common/lib/drink_water.c";
inherit "/d/Shire/std/room/room_tell";

#define FILTER_PONY(x) \
        filter((x), &operator(==)("Pony") @ &->query_name())

#define FILTER_HORSE(x) \
        filter((x), &operator(==)("Horse") @ &->query_name())

/* Globals */
static object Stable_master;

/* Function prototypes */
public string corral_desc();
int yard_security();

void
create_faerun_room()
{
    set_short("Stables");
    set_long("The stables of Bree. The stables are large, housing many fine steeds. Many stalls fill one end of the building, some with horses and others empty. Straw covers the floor. Bales of hay are stacked up against one wall. A door that leads out to the corral.\n");

    add_item(({"door", "corral door"}),
        "It is locked securely.\n");

    add_item(({"hay", "bales of hay", "alfalfa"}),
        "It is freshly cut and stacked up against the walls. " +
        "It is excellent food for the horses.\n");
    add_item(({"horses", "steeds"}),
        "The horses in the stalls are tall magnificent " +
        "creatures, They are muscular and well groomed. " +
        "The steeds are different colors, with " +
        "brown being the common color.\n");
    add_item("ceiling",
        "Large carved beams hold up the roof high above you.\n");
    add_item(({"down", "straw", "floor", "ground"}),
        "Fresh straw cover the ground. It is golden colored " +
        "and smells clean like it was freshly cut.\n");
    add_item(({"stalls", "stall"}),
        "The stalls are a good size, sturdy and made of solid " +
        "wood, and able to house a large " +
        "horse comfortably. Within each stall you see troughs " +
        "for food and water. Some stalls are empty " +
        "while others are occupied.\n");
    add_item(({"troughs", "trough"}),
        "you see troughs in the stalls for food.\n");
    add_item(({"food trough", "food troughs", "wooden food troughs",
            "wooden food trough"}),
        "The food troughs are made of wood and have some hay, alfalfa" +
        "and grain in them for the hungry horses.\n");
    add_item(({"grain", "oats", "sweet molasses", "molasses",
            "corn", "feed"}),
        "You see a mixture of oats, corn, sweet molasses, and " +
        "other good foods in the food troughs.\n");
    add_item(({"walls", "wall"}),
        "The walls are strong and durable, made of planed wood. " +
        "Some shelves and racks are on the walls.\n");
    add_item("racks",
        "The racks stretch across a long wall. On them, are " +
        "various saddles, bridles, halters, and other implements " +
        "of horsmanship.\n");
    add_item("shelves",
        "You see some combs, brushes, bells, blankets, and " +
        "other items stacked on the shelves.\n");
    add_item(({"comb", "combs"}),
        "The combs are made of metal and have teeth to remove " +
        "tangles and debris from the animal's hair.\n");
    add_item(({"brushes", "brush"}),
        "The brush is made of soft, smooth bristles of pure dark " +
        "horsehair blend and is the best finishing brush you've seen. " +
        "The brushes are small and fit in your hand comfortably.\n");
    add_item(({"blankets", "horses blankets"}),
        "The blankets are wool and in many bright colors. They " +
        "are used to cover the horses and for riding.\n");
    add_item(({"saddles", "saddle"}),
        "The saddles are strongly built to withstand and " +
        "protect the rider from extended travel. The saddles " +
        "have a flatter seat allowing greater freedom while " +
        "riding.\n");
    add_item(({"bridle", "bridles"}),
        "These harnesses fit over the horses head and are used " +
        "to guide or restrain the animal. They consist of a " +
        "'U'-shaped metal piece which fits in the mouth and " +
        "leather straps to secure it to the horse.\n");
    add_item(({"halters", "halter"}),
        "These devices are made of leather straps and fit over " +
        "the horses head and neck.\n");

    add_item("corral",
        "@@corral_desc@@");

    add_item("sign",
        "@@corral_sign@@");

    add_prop(OBJ_I_CONTAIN_WATER, 1000000);
    set_drink_from( ({ "trough", "water"}) );
    set_room_tell_time(300 + random(37));
    add_room_tell("A stable boy walks by and pours a bucket of water " +
        "in the trough.");
    add_room_tell("Neighing sounds come from the corral.");
    add_room_tell("A horse trots up to the corral fence.");
    add_room_tell("An irritable dwarf trots by on a pony.");
    add_room_tell("A curious pony pokes her head over the fence, munching " +
        "on some hay.");

    add_exit("yard", "south");
    add_exit("corral", "north", yard_security, 0,1);

    reset_faerun_room();
}

void reset_faerun_room()
{
    if (!Stable_master)
        Stable_master = clone_object(STABLE_MASTER);

    if (!present(Stable_master, this_object()))
        Stable_master->move(this_object());
}


public string
corral_desc()
{
    object other_room;
    mixed opeople;

    if (!LOAD_ERR(STABLES_DIR + "corral"))
        other_room = find_object(STABLES_DIR + "corral");
    else
        return "ERROR: We have a problem in the corral view. Please bug " +
            "report this.";

    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        return "Behind the corral fence you see no horses.\n";
    else
        return "Behind the corral fence you see " + COMPOSITE_LIVE(opeople) + ".\n";
}

public string
corral_sign()
{
    object other_room;
    mixed opeople;
    string sign_ret = "";

    if (!LOAD_ERR(STABLES_DIR + "corral"))
        other_room = find_object(STABLES_DIR + "corral");
    else
        return "ERROR: We have a problem in the corral view. Please bug " +
            "report this.";

    int i;
    int sz = sizeof(opeople);

    opeople = FILTER_PONY(all_inventory(other_room));
    sz = sizeof(opeople);
    sign_ret += "+------------------------------------------------+\n";
    sign_ret += "| Ponies:                                        |\n";
    sign_ret += "+------------------------------------------------+\n";
    for(i = 0; i < sz; i++)
        sign_ret += sprintf("| %3d : %40s |\n", i+1, opeople[i]->short() );
    sign_ret += "+------------------------------------------------+\n";

    opeople = FILTER_HORSE(all_inventory(other_room));
    sz = sizeof(opeople);
    sign_ret += "+------------------------------------------------+\n";
    sign_ret += "| Horses                                         |\n";
    sign_ret += "+------------------------------------------------+\n";
    for(i = 0; i < sz; i++)
        sign_ret += sprintf("| %3d : %40s |\n", i+1, opeople[i]->short() );
    sign_ret += "+------------------------------------------------+\n";
    sign_ret += "\n";
            
    if (!sizeof(opeople))
        return "Behind the corral fence you see no horses or ponies.\n";
    else
        return sign_ret;
}


int
yard_security()
{
    // Let the stable master and tack shop keeper run to corral when attacked
    if (TP->query_wiz_level() || TP->query_name() == "Torvil" ||
        TP->query_race() == "horse")
        return 0;

    write("You can't seem to climb over the corral fence.\n");
    return 1;
}

void
enter_inv(object ob, object from)
{
    object quest_horse;
    object leader_obj;
    object leader;
    int test;

    ::enter_inv(ob, from);
    if (present("__leader_object", ob))
    {
        leader_obj = present("__leader_object", ob);
    }
}


public void
init()
{
    ::init();
    init_drink();
}