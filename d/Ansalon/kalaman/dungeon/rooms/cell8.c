#include "local.h"

inherit DUNGEON_IN;

#define REMOTE_ROOM DUNGEON+"cc7";
string get_desc_bars();
string get_desc_chain();
string cmd_break_chain();

object chains_ob;
int    chains_status;

create_dungeon_room()
{
   set_dungeon_type(ROOM_CELL1);
   ::create_dungeon_room();

   add_cell_door("kmancell8",({ "west", "w" }), DROOM+"cc7", "west", CELL_KEY1);

   add_item(({ "corridor", "steel bars", "bars" }), get_desc_bars);
   add_item(({"chains","chain", "steel chain" }), get_desc_chain); 
   add_cmd_item(({"chains","chain", "steel chain" }), "break", cmd_break_chain); 

   add_npc(DNPC + "miclo", 1);
}

string
get_desc_bars()
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

string 
get_desc_chain() 
{ 
   string text = "The rusty steel chain is used to keep some prisoners that " + 
    "seem more keen on escaping secured to the cell. It is attached " + 
    "to a large steel ring in the stone wall. "; 
 
  if ( objectp(chains_ob) ) 
  { 
    text += chains_ob->query_The_name(TP) + " is currently chained to the " + 
      "wall.\n"; 
  } 
  else 
  { 
    text += "The chain is currenly not used.\n";
  }


  return text;
}

string
cmd_break_chain()
{
  if ( chains_status )
  { 
     return "The chains are already broken.\n";
  }
  else
  {
     tell_room(ENV(TP), QCTNAME(TP) + " breaks the chain holding " +
       QTNAME(chains_ob) + " to the wall.\n", TP);
     TO->break_chains();
     chains_ob->unchain_me(TP);
     return "You break the chains!\n";
  }
}

int 
query_chains()
{
  return chains_status;
}

void
break_chains()
{
  chains_status=1;
}

void
repair_chains()
{
  chains_status=0;
}

/*
 * Function: add_chains_ob
 */
void
add_prisoner(object prisoner)
{
  chains_ob = prisoner;
}

void
remove_prisoner()
{
  chains_ob = 0;
}

object
query_prisoner()
{
  return chains_ob;
}
