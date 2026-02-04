/*
 * villa1/kitchen
 *
 *  Lilith, Feb 2022
 *
 */

#pragma strict_types

#include "h1.h"

inherit H1 +"housebase";
inherit "/d/Gondor/open/fireplace/fireplace";

#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>

#define SEE_NORTH	({ H1 + "garden" })
#define SEE_SOUTH   ({ H1 + "living" })

object table;

public string
north_view(void)
{
    object *live = get_view(SEE_NORTH);

    if (!sizeof(live))
	return "a bit of enclosed garden with a view of the forest beyond.";

    return COMPOSITE_LIVE(live) + " enjoying the enclosed garden and the "+
        "fresh air.";
}

public string
table_inv(void)
{
    if (!table) return "";
    return table->describe_table();
}

int do_garden();

/*
 * Function name:        create_house_room()
 * Description  :        Creates a house room from from the base file
 *                       "housebase.c"
 */
void 
create_house_room()
{
    room_add_object(HOBJ + "counter1");
    room_add_object(HOBJ + "cauldron1");
    room_add_object(HOBJ + "pantry1");
    room_add_object(HOBJ + "chair_e");
    room_add_object(HOBJ + "chair_w");
    room_add_object(HOBJ + "chute");

    // Handling this a little differently because the room calls
    // a function in it.
    table = clone_object(HOBJ +"table1_kitchen");	
    table->move(this_object());

    add_exit("garden",  "north", do_garden);
    add_exit("living",  "south");
    add_exit("bedroom", "up");

    set_short("townhouse kitchen");
    set_long("This warm, cozy spot is the kitchen of "+
      "the townhouse. @@table_inv@@ Two high-backed chairs "+
      "face each other from opposite ends of the table. "+
      "A long counter made of slate stretches along the "+
      "west wall, where it meets a pantry in the southwest "+
      "corner. There is a small chute underneath it. "+
      "The east wall has a large fireplace made of brick "+
      "and slate with an iron cauldron resting within it. "+
	  "The pine floors gleam with a fresh coat of beeswax. "+
      "There are two large north-facing windows "+
      "from which you can see @@north_view@@ A set of stairs "+ 
      "leads up to the loft.\n");

    set_items_kitchen();
    set_items_stone();
    set_fire_container("fireplace");
    add_help_topic("here",    HELP +"kitchen_help");
    add_help_topic("room",    HELP +"kitchen_help"); 
	add_help_topic("kitchen", HELP +"kitchen_help");

    add_item( ({"south wall", "southern wall", "south"}),
      "In the middle of the south wall is an opening to the "+
      "living room.\n");
    add_item( ({"door"}),
      "This door leads north, out into the garden.\n");
    add_item( ({"west wall", "western wall", "west"}),
      "The western wall here is made of peeled pine logs. A "+
      "slate counter runs the length of it.\n");
    add_item( ({"east wall", "eastern wall", "east"}),
      "The western wall here is made from peeled pine logs. There " +
      "is a large brick and slate fireplace built in.\n");
    add_item( ({"north wall", "northern wall", "north"}),
      "The north wall has a door and two large windows offering "+
      "a view of the garden and the forest beyond.\n");
    add_item( ({"fireplace", "stone fireplace", "brick fireplace",
	  "fire"}),
      "A fireplace made of brick and faced in slate. It has an "+
      "iron cauldron hanging within it, above a freshly laid fire.\n");


}

/*
 *  do_garden - fake a door to outside.
 */
int
do_garden()
{
    write("You open the door and step out into an enclosed garden.\n");
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
