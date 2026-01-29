#include "local.h"

inherit DUNGEON_IN;

#define REMOTE_ROOM DUNGEON+"cc8";
string add_cell_bars();

create_dungeon_room()
{
   set_dungeon_type(ROOM_CELL1);
   ::create_dungeon_room();

   add_cell_door("kmancell9",({ "east", "e" }), DROOM+"cc8", "east", CELL_KEY1);

   add_item(({ "corridor", "steel bars", "bars" }), add_cell_bars);

   add_npc(DNPC + "dungeon_prisoner", 2);
}

string
add_cell_bars()
{
  string room = REMOTE_ROOM;

  if ( LOAD_ERR(room) ) 
    return "You look through the bars and see nothing.\n";

  object *item = all_inventory(find_object(room));
  string room_desc, living_desc;

  if ( sizeof(item) )
  {
    living_desc = COMPOSITE_LIVE(FILTER_LIVE(item));
   
  }

  room_desc = room->long(); 
  if ( living_desc != "nobody" )
    return room_desc+living_desc+".\n";

  return "You look through the baars and see: " + room_desc;
}
