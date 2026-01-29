/*
 *	/d/Gondor/ithilien/emyn-arnen/house4.c
 *
 *	Copyright (c) 1994, 1997 by Christian Markus
 *
 *	Coded by Olorin
 *
 *	Modification log:
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

object  door;

public void
create_gondor()
{
    set_short("a hut in a village in Emyn Arnen");
    set_long(BSN("This is a small hut with a single room. The only door "
      + "is leading southwest back onto the road. The ground is "
      + "littered with broken furniture, ashes from old fires, and "
      + "many shards of glass and pottery."));
    add_item(({"ceiling", "roof"}), BSN(
        "The roof of this hut seems still to hold, but in many "
      + "places it is possible to see the sky through holes in it."));
    add_item(({"ground", "floor"}), BSN(
        "The floor is covered by broken furniture, ashes from old fires, "
      + "and many shards of glass and pottery. The wooden planks "
      + "which once covered the ground have rotten away in places so "
      + "that the earth below is uncovered. In the northern corner "
      + "a large wooden board is lying on the ground."));
    add_item(({"corner", "northern corner", "wooden board", "board",
        "large board", "large wooden booard"}), BSN(
        "In the northern corner of the room, there is a wooden "
      + "board lying on the ground. It looks different from the wooden "
      + "planks that once were the floor of the room."));
    add_item(({"furniture", "broken furniture", "ashes"}), BSN(
        "It is hard to make out what kind of furniture was in the hut "
      + "before everything was smashed and most parts were burnt. But it "
      + "looks like once the walls of the hut were lined with many "
      + "shelves. Now most of the wood has been burned and ashes are "
      + "almost all that is left. Among the remains of the furniture "
      + "you can also see many shards from broken bottles and "
      + "earthenware and burnt and torn scrolls and books."));
    add_item(({"shards", "bottles", "pottery", "earthenware"}), BSN(
        "Among the broken furniture you find besides burnt and torn "
      + "scrolls and books large amounts of broken bottles and "
      + "earthenware. You assume that many different things were stored "
      + "in the shelves before they were destroyed or stolen, but since "
      + "nothing seems to remain of them, you have no idea what they "
      + "might have been."));
    add_item(({"scrolls", "books", "papers", "pages"}), BSN(
        "Long ago this hut must have belonged to a learned man, perhaps "
      + "a healer or a scribe, since among the broken furniture and the "
      + "shards on the ground, you also find small "
      + "pieces of paper and parchment, shreds of many scrolls and books "
      + "that were kept in the shelves of this hut long ago. Looking "
      + "through them, you have to realize that there is nothing left "
      + "which one could read. Most of the scrolls and books was clearly "
      + "burnt and all what is left are shreds so small that they "
      + "escaped the notice of the looters."));

    add_item(({"window", "windows", "door"}), BSN(
        "All that remains of the windows and the door leading southwest " +
        "onto the street are empty holes in the wall."));

    add_exit(ITH_DIR + "emyn-arnen/vrdn",     "southwest", 0, 1);

    add_prop(OBJ_S_SEARCH_FUN,"do_search");
    add_prop(OBJ_I_SEARCH_TIME, 1);

    door = clone_object(ITH_DIR + "emyn-arnen/obj/h4up_door");
    door->move(TO);
}

string
do_search(object pl, string str)
{
    if (!strlen(str) || (str != "corner" && str != "board" &&
        str != "northern corner" && str != "wooden board"))
        return 0;

    if (!door)
        return 0;
    if (door->query_open())
        return 0;
    if (door->query_closed_desc() != "")
        return 0;
    door->set_closed_desc("There is a closed trap door leading down.\n");
    change_my_desc(door->query_closed_desc(), door);
    say(QCTNAME(TP) + " searches the northern corner and finds a "
      + "trap door leading down.\n");
    return BSN("When you examine the wooden board in the northern "
      + "corner, you notice that it is a trap door leading into a "
      + "cellar under the house.");
}

void
reset_room()
{
    door->reset_door();
}
