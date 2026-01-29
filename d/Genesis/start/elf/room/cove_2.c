#include "../stddefs.h"
#include <stdproperties.h>
#include <language.h>
#include "../desc_include/trade_road.h"
#include "../desc_include/cove.h"

#pragma save_binary

inherit ELFROOM;

#define UPHILL  ROOMDIR + "cove_1"
#define  NORTH  ROOMDIR + "cove_3"

#define SHORT  "In a small, sheltered cove"

#define LONG \
  "You are at a wooden pier in a small, sheltered cove. The cove's soft "+\
  "limestone walls rise around you. " +\
  "An unpaved road goes uphill from the pier to the dark forest in the " +\
  "south. At the north end, it continues to several other piers.\n" +\
  "On a post beside this pier, a wooden sign is slowly swaying in the wind.\n"

#define POST_ITEM ({"post"})
#define POST_DESC \
  "It has a sign hanging from it in an obvious way.\n"

#define SIGN_ITEM ({"wooden sign", "sign"})
#define SIGN_DESC \
  "The wooden sign has a painting of some kind of green gemstone and some letters on it.\n"
#define SIGN_READDESC \
  "The letters read 'Passage to Emerald discontinued'.\n"

#define SHIP_ENTER_MSG \
  " enters the cove below you, mooring at the closest pier.\n"
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
  
  add_exit(UPHILL, "uphill",  0);
  add_exit( NORTH,  "north",  0);

  stock();
}

stock()
{
  restock_object(MONSTERDIR+"mariner", 1, "mariner");
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
