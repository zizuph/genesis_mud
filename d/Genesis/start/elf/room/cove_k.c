#include "../stddefs.h"
#include <stdproperties.h>
#include <language.h>
#include "../desc_include/trade_road.h"
#include "../desc_include/cove.h"

#pragma save_binary

inherit ELFROOM;

#define NORTH  ROOMDIR + "cove_5"
#define SOUTH  ROOMDIR + "cove_3"

#define SHORT  "In a small, sheltered cove"

#define LONG \
  "You are at a wooden pier in a small, sheltered cove, whose soft "+\
  "limestone walls rise around you. " +\
  "An unpaved road goes south to some other piers, and then to " +\
  "the dark forest " +\
  "further south.\n" +\
  "On a post beside this pier, a wooden sign is slowly swaying in the wind.\n"
  
#define POST_ITEM ({"post"})
#define POST_DESC \
  "It has a sign hanging from it in an obvious way.\n"

#define SIGN_ITEM ({"wooden sign", "sign"})
#define SIGN_DESC \
  "The wooden sign has a painting of a silver tree on it.\n"
#define SIGN_READDESC \
  "There is no text on it to read.\n"

#define SHIP_ENTER_MSG \
  " enters the cove below you, mooring at one of the more distant piers.\n"
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
  add_cmd_item(SIGN_ITEM, "read", SIGN_READDESC);

  add_exit(NORTH,  "north",  0);
  add_exit(SOUTH,  "south",  0);

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
