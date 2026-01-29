/* 
 *	/d/Gondor/pelargir/homes/abanshop.c
 *
 *	Copyright (c) 1997 by Christian Markus
 *
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public  void    reset_room();

static  int     Found = random(2);

public void
create_gondor()
{
    add_exit(PELAR_DIR + "streets/admiral07", "north", 0, 0);

    set_short("the abandoned workshop of a carpenter");
    set_long(BSN("A broken workbench on the western wall reveals "
        + "that this was once the workshop of a carpenter, but the "
        + "workbench is all that remains of the tools of his trade. "
        + "The floor is covered by a thick layer of dirt and dust, "
        + "so the carpenter who once worked here must have left a "
        + "long time ago."));

    add_item("workbench", BSN("The workbench is broken in the "
        + "middle, with the ends leaning towards each other. In the "
        + "shadows under the workbench lies a heap of garbage and "
        + "refuse."));
    add_item(({"tool","tools"}), BSN("With the exception of the "
        + "broken workbench, there are no tools visible here. The "
        + "carpenter probably took them with him when he departed."));
    add_item( ({ "wall", "walls", }), BSN("The walls are empty and "
        + "dirty. In a few places you can still see the holes for "
        + "nails holding shelves and tools."));
    add_item( ({ "holes", "nails", "shelves", }), BSN("All that "
        + "remains of the shelves and nails for storing tools and "
        + "other things are holes in the walls. And the holes are "
        + "too small to hold anything."));
    add_item( ({ "floor", "ground", "dirt", "dust", }), BSN("The "
        + "floor is covered by a thick layer of dirt and dust that "
        + "must have been carried in by the wind through the open "
        + "doorway."));
    add_item( ({ "doorway", "door", }), BSN("Where once there was a "
        + "door leading into the workshop, there is only an open "
        + "doorway. In the dirt on the threshold you can even see "
        + "some grass growing."));
    add_item( ({ "grass", "threshold", }), BSN("Green grass is "
        + "growing in the dirt on the threshold of the doorway "
        + "lading out into the street."));
    add_item( ({ "garbage", "refuse", "shadows", "heap", }), 
        BSN("In the shadows under the broken workbench lies a "
            + "rather large heap of garbage and refuse. Without "
            + "a closer look, it seems as if there is a lot of "
            + "old wood in that heap, and perhaps even one or "
            + "two broken tools."));

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(OBJ_I_SEARCH_TIME, 5);

    enable_reset(200);
}

public string
do_search(object pl, string str)
{
    object  saw;

    if (!objectp(pl) || !objectp(present(pl, TO)))
        return 0;

    if (!strlen(str))
        return 0;

    str = LOW(str);

    switch (str)
    {
    case "workbench":
    case "garbage":
    case "refuse":
    case "heap":
        say(QCTNAME(pl) + " searches through the heap of garbage "
            + "under the workbench.\n", pl);
        if (Found || (pl->query_skill(SS_AWARENESS) < (10 + random(15))))
            return "You search through the heap of refuse under the "
                + "workbench, but you do not find anything of "
                + "interest.\n"; 
        saw = clone_object(PELAR_DIR + "obj/saw");
        saw->add_prop(OBJ_M_NO_BUY, 1);
        Found = 1;
        if (saw->move(pl))
        {
            if (saw->move(TO))
                saw->move(TO, 1);
            return "You search through the heap of refuse under the "
                + "workbench.\n"
                + "You find an old saw and drop it again.\n";
        }
        return "You search through the heap of refuse under the "
            + "workbench.\n"
            + "You find an old saw and pick it up.\n";
    }
}

public void
reset_room()
{
    if (Found)
        Found = random(2);
}

public void     set_found(int f) { Found = f; }
public int      query_found()    { return Found; }
