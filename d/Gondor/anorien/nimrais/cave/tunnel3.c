/*
 *	/d/Gondor/anorien/nimrais/cave/tunnel3.c
 *
 *	January 1996, Olorin
 */
#pragma strict_types

inherit "/d/Gondor/common/room.c";

#include <language.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_room()
{
    set_short("a narrow tunnel");
    set_long("@@long_desc@@");

    add_item(({"ground", "floor", "water", }), "The thin stream of "
      + "water is trickling downwards on the tunnel floor.\n");
    add_item(({"tunnel", "walls", }), BSN("The smooth walls are proof that "
      + "the tunnel was not created by mining, but probably by the steady flow "
      + "of water through a softer layer of rock."));
    add_item(({"heap", "rocks", "stones", }), "@@exa_heap@@");

    add_exit(ANO_DIR + "nimrais/trolls/tunnel", "up", 0, 3);
    add_exit(ANO_DIR + "nimrais/cave/tunnel2", "southwest", "@@block_msg@@", 2);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT,  0);
}

public int
block_msg()
{
    if (!(ANO_DIR + "nimrais/cave/tunnel2")->query_heap_state())
    {
        write("The passage leading downwards is blocked by the heap of rocks "
          + "and stones.\n");
        return 1;
    }

    write("You climb over the low heap of rocks.\n");
    return 0;
}

public string
long_desc()
{
    string  desc = "The tunnel turns steeply upwards here. In the other "
                 + "direction, it is descending towards the southwest.";

    if (!(ANO_DIR + "nimrais/cave/tunnel2")->query_heap_state())
    {
        desc += " In the bend a large heap of rocks and stones has "
             +  "gathered and is blocking the passage further downwards.";
    }

    desc += " A thin stream of water is trickling down the slope on the ground.";

    return BSN(desc);
}

public string
exa_heap()
{
    string  desc;

    if (!(ANO_DIR + "nimrais/cave/tunnel2")->query_heap_state())
    {
        desc = "The heap of rocks and stones is blocking the passage "
             + "downwards completely. The rocks and stones probably once "
             + "came sliding down from further upwards, and came to rest "
             + "here.";
    }
    else
        desc = "The ground is covered with many rocks and stones. "
             + "They form a low heap right further down, "
             + "but there should be no problem climbing over them.";

    return BSN(desc);
}

