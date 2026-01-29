#include "../stddefs.h"
#include <stdproperties.h>
#include <language.h>
#include "../desc_include/trade_road.h"
#include "../desc_include/cove.h"

#pragma save_binary

inherit ELFROOM;

#define SOUTH  ROOMDIR + "cove_4"
#define NORTH  ROOMDIR + "cove_6"

#define SHORT  "On a narrow ledge"

#define LONG \
  "You are on a rock ledge, underneath a limestone overhang. "+\
  "Water laps against the rock beneath you, making it wet and " +\
  "slippery. A wooden post is lodged between two rocks under the " +\
  "water. A path leads south to other piers.\n " +\
  "On the post, a wooden sign hangs loosely.\n"
  
#define POST_ITEM ({"post", "wooden post"})
#define POST_DESC \
  "The wooden post is used both as a mooring and as a sign-holder.\n"

#define SIGN_ITEM ({"wooden sign", "sign"})
#define SIGN_DESC \
  "The wooden sign has a painting of a bagpipe and some letters on it.\n"
#define SIGN_READDESC \
  "The letters read 'Port Macdunn'.\n"

#define LEDGE_ITEM ({"ledge", "rock ledge", "wet ledge"})
#define LEDGE_DESC \
  "The rock ledge is wet and slippery.\n"

#define STONE_ITEM ({"limestone overhang", "overhang"})
#define STONE_DESC \
  "The limestone overhang hides this pier from distant observers.\n"

#define SHIP_ENTER_MSG \
  " enters the cove below you, disappearing under a rock overhang.\n"
#define SHIP_LEAVE_MSG \
  " leaves the cove.\n"

create_room()
{
  set_short(SHORT);
  set_long(WRAP(LONG));

  COVE_STD_ITEMS;
  TRADE_ROAD_STD_ITEMS;
  add_item(POST_ITEM, POST_DESC);
  add_item(SIGN_ITEM, SIGN_DESC);
  add_item(STONE_ITEM, STONE_DESC);
  add_item(LEDGE_ITEM, LEDGE_DESC);
  add_cmd_item(SIGN_ITEM, "read", SIGN_READDESC);

  add_exit(SOUTH,  "south",  0);
  add_exit(NORTH,  "north",  0);

  stock();
}

stock()
{
}

reset_room()
{
  stock();
}

void ship_arrived(mixed where)
{
  tell_room(LOOKOUT, 
	    WRAP(capitalize(LANG_ASHORT(previous_object())) + 
		 SHIP_ENTER_MSG));
  call_other(LOOKOUT, "add_item", 
	     previous_object()->query_name(), previous_object()->query_long());
}

void ship_left(mixed where, mixed to)
{
  tell_room(LOOKOUT, 
	    WRAP(capitalize(LANG_ASHORT(previous_object())) + 
		 SHIP_LEAVE_MSG));
  call_other(LOOKOUT, "remove_item", 
	     previous_object()->query_name());
}
