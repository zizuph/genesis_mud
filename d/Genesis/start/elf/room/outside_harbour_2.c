#include "../stddefs.h"
#include "/sys/stdproperties.h"

#pragma save_binary

inherit ELFROOM;

#define SHORT  "Off the coast"

#define LONG \
  "You can see the coast as a thick, white line in the south. There seem "+\
  "to be several reefs between you and it, as the slowly rolling waves " +\
  "here and there break up into white foam.\n"


#define FOAM_ITEM ({"foam"})
#define FOAM_DESC \
  "It looks like white stuff on the survface of the ocean.\n"

#define WAVES_ITEM ({"wave", "waves"})
#define WAVES_DESC \
  "The waves are slowly rolling along.\n"

#define REEFS_ITEM ({"reef", "reefs"})
#define REEFS_DESC \
  "The reefs are submerged, and cannot be seen except through their effect "+\
  "on the waves"

#define LINE_ITEM ({"line", "white line"})
#define LINE_DESC \
  "It might be some kind of white rocks.\n"

#define COAST_ITEM ({"coast"})
#define COAST_DESC \
  "It is too far to make out any details.\n"
  
create_room()
{
  set_short(SHORT);
  set_long(WRAP(LONG));

  add_item(WAVES_ITEM, WAVES_DESC);
  add_item(FOAM_ITEM, FOAM_DESC);
  add_item(REEFS_ITEM, REEFS_DESC);
  add_item(COAST_ITEM, COAST_DESC);
  add_item(LINE_ITEM, LINE_DESC);
  add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

  set_noshow_obvious(1);
  stock();
}

stock()
{

}

reset_room()
{
  stock();
}
