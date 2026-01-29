#include "../stddefs.h"
#include "/sys/stdproperties.h"

#pragma save_binary

inherit ELFROOM;

#define OUT SHOREDIR + "inside"

#define SHORT "Inside a wardrobe"

#define LONG \
  "The cabinet contains a much larger wardrobe " + \
  "inside. So large, in fact, " + \
  "that you have plenty of room here. Weird. " + \
  "Has to be some kind of " +  \
  "extradimensional effect.\n"


#define WALL_ITEM ({"wall", "walls"})
#define WALL_DESC "The walls seem to be made of plain, solid wood.\n"

#define WOOD_ITEM "wood"
#define WOOD_DESC "It is solid.\n"

#define FLOOR_ITEM "floor"
#define FLOOR_DESC "The floor is plain, wide, and quite solid oak planks.\n"

#define CEILING_ITEM "ceiling"
#define CEILING_DESC "It is pale blue.\n"

object door;

create_room()
{
  set_short(SHORT);
  set_long( WRAP(LONG));

  add_item(   WALL_ITEM, WRAP(   WALL_DESC));
  add_item(   WOOD_ITEM, WRAP(   WOOD_DESC));
  add_item(  FLOOR_ITEM, WRAP(  FLOOR_DESC));
  add_item(CEILING_ITEM, WRAP(CEILING_DESC));

  add_prop(ROOM_I_INSIDE, 1);

  stock();
}

reset_room()
{
  stock();
}

stock()
{

  if (!door) {
    door = clone_object("/std/door");
    door->set_other_room(OUT);
    door->set_door_id("cabinet door");
    door->set_door_name(({"door", "wardrobe door", 
			    "small door", "cabinet door"}));
    door->set_open_desc("  There is a small open door in the south wall.\n");
    door->set_closed_desc("  There is a small closed door in the south wall.\n");
    door->set_pass_command(({"south", "enter door", "go door", 
			       "go through door"}));
    door->set_fail_pass("The door is closed.\n");
    door->move(this_object());
  }
}

init() 
{
  ::init();
}
