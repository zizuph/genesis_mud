/*
 * villa1/kitchen
 *
 *  Lilith, Feb 2022
 *
 */

#pragma strict_types

#include "villa1.h"

inherit V1 +"housebase";
inherit "/d/Gondor/open/fireplace/fireplace";

#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>

inherit V1 +"housebase";

#define SEE_NORTH	({ V1 + "terrace_w", V1 +"pool" })

object table;

public string
north_view(void)
{
    object *live = get_view(SEE_NORTH);

    if (!sizeof(live))
	return "a large terrace and the Sybarus Sea beyond.";

    return COMPOSITE_LIVE(live) + " enjoying the terrace "+
    "and the view of the Sybarus Sea.";
}

public string
table_inv(void)
{
    if (!table) return "";
    return table->describe_table();
}

int do_terrace();

/*
 * Function name:        create_house_room()
 * Description  :        Creates a house room from from the base file
 *                       "housebase.c"
 */
void 
create_house_room()
{
    room_add_object(HOBJ + "counter_v1");
    room_add_object(HOBJ + "cauldron_v1");
    room_add_object(HOBJ + "pantry_v1");
    room_add_object(HOBJ + "bench_dining_e");
    room_add_object(HOBJ + "bench_dining_w");
    room_add_object(HOBJ + "tall_chair_n");
    room_add_object(HOBJ + "tall_chair_s");
    room_add_object(HOBJ + "chute");

    // Handling this a little differently because the room calls
    // a function in it.
    table = clone_object(HOBJ +"table_v1_dining");	
    table->move(this_object());

    add_exit("terrace_w",  "north", do_terrace);
    add_exit("front_hall", "east");

    set_short("villa kitchen");
    set_long("This spacious, airy room is the kitchen and dining "+
      "area of the villa. @@table_inv@@ Two high-backed chairs "+
      "sit at either end of the table, which is flanked by two "+
      "benches as well. "+
      "A long counter made of white onyx stretches along the "+
      "south wall, where it meets a pantry in the southeast "+
      "corner. You can see a small chute underneath it. "+
      "The west wall has a large fireplace made of basalt columns "+
      "with an iron cauldron resting within it. "+
      "Some potted plants grace the large north-facing window, "+
      "from which you can see @@north_view@@ "+ 
      "\n");

    set_items_kitchen();
    set_items_stone();
    set_fire_container("fireplace");
    add_help_topic("here",  "/d/Avenir/houses/help/kitchen_help");
    add_help_topic("room",  "/d/Avenir/houses/help/kitchen_help");

    add_item( ({"south wall", "southern wall", "south"}),
      "The southern wall is windowless, with a counter and "+
      "a pantry.\n");
    add_item( ({"door"}),
      "This door leads north, out onto the terrace.\n");
    add_item( ({"terrace", "garden", "pool"}),
      "There is a terrace outside, with a seating area around "+
      "a firepit, and a pool. You'd need to go outside to get "+
      "a better look.\n");
    add_item( ({"east wall", "eastern wall", "east"}),
      "The eastern wall here is made from slabs of white onyx " +
      "that are striped with milky opaque and translucent bands " +
      "that glow when light shines through.\n");
    add_item( ({"west wall", "western wall", "west"}),
      "The western wall here is made from slabs of white onyx " +
      "that with a large basalt fireplace built in.\n");
    add_item( ({"north wall", "northern wall", "north"}),
      "The north wall has a door and large window with a " +
      "panoramic view of the terrace and pool.\n");
    add_item( ({"fireplace", "stone fireplace", "basalt fireplace",
	"basalt columns", "fire", "basalt"}),
      "A fireplace made of basalt stone has an iron cauldron " +
      "hanging within it, above a freshly laid fire.\n");
    add_item( ({ "window", "north window"}), "You can see "+
      "a large terrace with a pool, and beyond it, the "+
      "Sea of Sybarus.\n");


}

/*
 *  do_terrace - fake a door to outside.
 */
int
do_terrace()
{
    write("You open the door and step out onto the terrace.\n");
    return 0;
}

/*
 * init - use to add the commands to the room.
 */
void 
init()
{
    ::init();
    // add the fire-related commands from Gondor.
    ::init_fire();
}
