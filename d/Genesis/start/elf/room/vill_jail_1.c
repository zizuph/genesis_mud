#include "../stddefs.h"
#include "/sys/stdproperties.h"

#pragma save_binary

inherit ELFROOM;

#define EAST     ROOMDIR + "wine_road_1"
#define WEST     ROOMDIR + "vill_jail_2"

#define NAT_SHORT "Outside the village jail"
#define FOR_SHORT "On a gravel yard"

#define NAT_LONG \
  "You are on a small gravel yard outside the village jail. The yard is "+\
  "surrounded by the jail on the north and west sides, and by a thick hedgerow "+\
  "on the others. There is an opening out to the Wine Road in the east.\n"
#define FOR_LONG \
  "You are on a small gravel yard outside a massive stone house. The yard is "+\
  "surrounded by the house on the north and west sides, and by a thick "+\
  "hedgerow on the others. There is an opening out to the road in the east.\n"

#define HOUSE_ITEM ({"jail", "village jail", "house", "stone house"})
#define HOUSE_DESC \
  "It is a massive, uninviting stone house. Its narrow windows have thick "+\
  "metal bars, and its door is heavily reinforced.\n"

#define YARD_ITEM ({"yard", "small yard", "garden yard"})
#define YARD_DESC \
  "It is a small, square gravel yard in front of the house.\n"

#define GRAVEL_ITEM ({"gravel", "gravel"})
#define GRAVEL_DESC \
  "It consits of small grey, red, yellow and brown stones.\n"

#define WINDOW_ITEM ({"window", "windows"})
#define WINDOW_DESC \
  "The windows all have massive metal bars, making it impossible to enter "+\
  "(or leave) that way.\n"


  
create_room()
{
  set_short(N_KNOW(NAT_SHORT, FOR_SHORT));
  set_long( N_KNOW(WRAP(NAT_LONG),
		   WRAP(FOR_LONG)));

  add_item(  HOUSE_ITEM, WRAP(  HOUSE_DESC));
  add_item( GRAVEL_ITEM, WRAP( GRAVEL_DESC));
  add_item(   YARD_ITEM, WRAP(   YARD_DESC));
  add_item( WINDOW_ITEM, WRAP( WINDOW_DESC));

  add_exit(EAST,      "east", 0);
  add_exit(WEST,      "west", 0);

  stock();
}


stock()
{
}
