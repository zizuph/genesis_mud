/* File:          /d/Khalakhor/ship/macdunn/faerie/cabin.c
 * Creator:       Teth
 * Date:          November 16, 1997
 * Purpose:       The cabin is a room on the Khalakhor to
 *                Faerie ship. It contains a chest,
 *                /d/Khalakhor/ship/macdunn/faerie/trunk.c
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/faerie/
 *                /d/Khalakhor/open/SHIPLINES
 * Comments:
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/ship/cabin";

#include <stdproperties.h>
#include "local.h"
#include "/d/Khalakhor/sys/terrains.h"

object trunk;

public void
create_cabin()
{
    set_short("the cabin of the Fiu Alladh");
    set_long("   This is the cabin of the Fiu Alladh. Dim " +
      "lighting darkens everything in the room. A bed dominates " +
      "the cramped quarters, while a table stands near the archway. " +
      "A trunk rests against another wall.\n");
    add_item(({"cabin","quarters","cramped quarters",}),"@@query_long");
    add_item(({"lighting","dim lighting"}),"The light in the room " +
      "only comes from natural sources, whatever is able to seep " +
      "in through grooves in the surrounding timber.\n");
    add_item(({"timber","surrounding timber","wall","walls"}),
      "The walls are made of a sturdy timber, that would resist " +
      "any oceanic storm.\n");
    add_item("ceiling","The ceiling is constructed of wooden beams.\n");
    add_item(({"beams","wooden beams"}),"The hefty beams of wood are " +
      "constructed of oak.\n");
    add_item("oak","The oak tree is a typical wood used for ship " +
      "construction.\n");
    add_item("floor","The floor is made of sturdy planks.\n");
    add_item(({"planks","sturdy planks"}),"The sturdy planks appear to " +
      "be constructed of oak.\n");
    add_item(({"walls","wooden walls","wall"}),"Each wall is made of " +
      "oak.\n");
    add_item("bed","The bed is used by the captain of the ship.\n");
    add_cmd_item(({"on bed","down on bed","bed"}),({"lie","rest"}),
      "You rest on the bed for a moment, then stand back up.\n");
    add_item("table","The table is covered with navigational charts, " +
      "and a blob of melted wax.\n");
    add_item(({"charts","navigational charts"}),"They appear to only " +
      "be good for the Faerie to Khalakhor ship route.\n");
    add_cmd_item(({"charts","navigational charts"}),({"get","take"}),
      "Taking the charts would only make sense if you were the " +
      "captain of a ship running between Khalakhor and Faerie!\n");
    add_item("chart","Each chart appears similar. Perhaps looking " +
      "at all the charts may give you a better idea.\n");
    add_item("archway","The archway surrounds the entrance to or exit " +
      "from the cabin.\n");
    add_item("deck","The main deck of the ship lies outside the cabin.\n");
    add_item(({"wax","melted wax","blob","blob of melted wax",
        "blob of wax"}),"The blob of melted wax is a combination of " +
      "colours, perhaps from a series of leaking candles.\n");

    add_exit(THIS_DIR + "deck", "out", 0);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_INSHIP);

    trunk = clone_object(OBJ_DIR + "trunk");
    trunk->move(this_object(), 1);

    set_cabin_sound("@@sounds");
}

public string
sounds()
{
    if (random(2))
        return "The ship does not feel like it is moving at all, " +
        "but that is an artifact of the smooth ride.\n";

    return "The ship glides noiselessly along.\n";
}
