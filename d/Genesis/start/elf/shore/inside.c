#include "../stddefs.h"
#include "/sys/stdproperties.h"

#pragma save_binary

inherit ELFROOM;

#define OUT     SHOREDIR + "beach_1"

#define SHORT "Inside a caravan"

#define LONG \
  "The inside of the caravan seems larger than the outside. The walls " + \
  "are painted in a deep blue-green color, and high up, close to the " + \
  "ceiling, there is a painted border of pale grey-brown sea-shells.\n" + \
  "Strangely enough, you cannot see any windows in the walls or any " + \
  "curtains. Fortunately there still is a door you can leave through. "

#define BORDER_ITEM "border"
#define BORDER_DESC "The border is painted in matte grey-brown shades.\n"

#define WINDOW_ITEM ({"window", "windows", "curtain", "curtains"})
#define WINDOW_DESC "There aren't any here to be seen. Weird.\n"

#define SHELL_ITEM ({"shell", "sea-shell", "shells", "sea-shells"})
#define SHELL_DESC "The sea-shells are painted in matte grey-brown shades.\n"

#define WALL_ITEM ({"wall", "walls"})
#define WALL_DESC "The walls seem to be made of plain, solid wood.\n"

#define WOOD_ITEM "wood"
#define WOOD_DESC "It is solid.\n"

#define DOOR_ITEM "door"
#define DOOR_DESC "It is open, and seems to be missing a lock.\n"

#define FLOOR_ITEM ({"floor", "planks" })
#define FLOOR_DESC "The floor is plain, wide, and quite solid oak planks.\n"

#define CEILING_ITEM "ceiling"
#define CEILING_DESC "It is pale blue.\n"

#define KEY_ITEM "key"
#define KEY_FIND_DESC "It's not *that* easy. You have to find out how.\n"


create_room()
{
  set_short(SHORT);
  set_long( WRAP(LONG));

  add_item( BORDER_ITEM, WRAP( BORDER_DESC));
  add_item( WINDOW_ITEM, WRAP( WINDOW_DESC));
  add_item(  SHELL_ITEM, WRAP(  SHELL_DESC));
  add_item(   WALL_ITEM, WRAP(   WALL_DESC));
  add_item(   WOOD_ITEM, WRAP(   WOOD_DESC));
  add_item(   DOOR_ITEM, WRAP(   DOOR_DESC));
  add_item(  FLOOR_ITEM, WRAP(  FLOOR_DESC));
  add_item(CEILING_ITEM, WRAP(CEILING_DESC));
  add_cmd_item(KEY_ITEM, "find", WRAP(KEY_FIND_DESC));

  add_prop(ROOM_I_INSIDE, 1);
  add_exit(OUT,      "out", 0);

  stock();
}

reset_room()
{
  stock();
}

stock()
{
  object obj;

  while((obj = present("bunk", this_object())) != 0)
    obj->remove_object();

  restock_object(OBJDIR + "cabinet",     1, "cabinet");
  restock_object(OBJDIR + "unmade_bunk", 1, "bunk");
}

init() 
{
  ::init();
}
