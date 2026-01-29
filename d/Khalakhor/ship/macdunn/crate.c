/* File:          /d/Khalakhor/ship/macdunn/crate.c
 * Creator:       Teth
 * Date:          November 29, 1997
 * Modifications:
 * Purpose:       This crate contains bolts of wool. Strips of
                  bark can be peeled from it, an herb.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/pier11.c
 *                /d/Khalakhor/ship/macdunn/wool_bolt.c
 *                /d/Krynn/common/herbs/grey_willow.c
 * Comments:      A little something for free.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/receptacle";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "local.h"

int herb;
object wool, willow;

public void
reset_receptacle()
{
    seteuid(getuid());

    herb = 0;

    if (!wool || !present(wool))
    {
        wool = clone_object(MACDUNN_DIR + "wool_bolt");
        wool->set_heap_size(1 + (random(2)));
        wool->move(this_object(), 1);
    }

    this_object()->add_prop(CONT_I_CLOSED, 1);
}

public void
create_receptacle()
{
    set_name("crate");
    add_name("receptacle");
    set_pname("crates");
    set_adj("wood");
    add_adj("wooden");
    add_adj("willow");
    add_adj("knotty");
    set_short("willow crate");
    set_pshort("willow crates");
    set_long("This willow crate is of poor construction, " +
        "made of a knotty wood not often used to make " +
        "receptacles. Flecks of bark seem to be peeling off the " +
        "wood, which is not unusual.\n");
    add_item(({"bark","flecks of bark","flecks","peeling bark",
        "peeling flecks of bark"}),"The peeling flecks of " +
        "bark are typical of willow that is drying out.\n");
    add_item("lid","The lid on the crate does not rest evenly.\n");
    add_item(({"wood","knotty wood"}),"The knotty wood is willow.\n");
    add_cmd_item(({"crate","willow crate","wooden crate",
        "wood crate"}),({"break","destroy","smash"}),"The resilience " +
        "of the wood prevents it from breaking.\n");
    add_cmd_item(({"herb","bark","fleck"}),({"tear","rip","pull",
        "detach","strip","peel"}),"@@get_bark");

    add_prop(CONT_I_WEIGHT, 235350);
    add_prop(CONT_I_MAX_WEIGHT, 278250);
    add_prop(CONT_I_VOLUME, 120000);
    add_prop(CONT_I_MAX_VOLUME, 900025);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_SELL, "If you managed to get this crate to a " +
      "store, please report it as a bug.\n");
    add_prop(OBJ_M_NO_GET, "The crate is too unwieldy for you to " +
      "take.\n");
    add_prop(OBJ_I_VALUE, 220);

    enable_reset(200);
    reset_receptacle();
}

public int
get_bark()
{
    if (herb > 1)
    {
        write("There are no flecks of bark loose enough to strip.\n");
        say(QCTNAME(TP) + " attempts to strip a fleck of bark from " +
          "the crate, but there are none that " + HE + " is able to " +
          "get of any value.\n");
        return 1;
    }

    write("You are able to strip a fleck of bark from the crate!\n");
    say("With some effort, " + QCTNAME(TP) + " is able to strip " +
      "a fleck of bark from the crate!\n");
    willow = clone_object("/d/Krynn/common/herbs/grey_willow");
    willow->move(this_player(), 1);
    herb = herb + 1;
    return 1;
}
