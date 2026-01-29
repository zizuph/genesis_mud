#include "local.h"

inherit DUNGEON_IN;

#define REMOTE_ROOM DUNGEON + "cc7";
#define BREAK_STRENGTH 160
string get_desc_bars();
string get_desc_chain();
string cmd_break_chain();

object chains_ob;
int    chains_status;

create_dungeon_room()
{
   ::create_dungeon_room();
   set_dungeon_type(ROOM_CELL1);

   add_cell_door("kmancell0",({ "west", "w" }), DROOM+"cc8", "west", CELL_KEY1);

   add_item(({ "corridor", "steel bars", "bars" }), get_desc_bars);
   add_item(({"chains","chain", "steel chain" }), get_desc_chain); 
   add_cmd_item(({"chains","chain", "steel chain" }), "break", cmd_break_chain); 
   add_npc(DNPC + "wesley", 1);
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

mixed
filter_break_tools(object ob)
{
  if ( ob->query_name() == "hammer" ) return 1;

  return 0;
}

string
cmd_break_chain()
{
  if ( chains_status )
  { 
     return "The chains are already broken.\n";
  }

  if ( TP->query_stat(SS_STR) < BREAK_STRENGTH )
  {
    if ( !sizeof(filter(all_inventory(TP), filter_break_tools)) )
    { 
      return "You feel that the chain is far to strong for you " +
        "to break without any kind of tool to help you.\n";
    }
  }

  write ("You grip the chains with both your hands and pull with all " +
    "your strength.\n");
 
  if ( objectp(chains_ob) )
  {
     tell_room(ENV(TP), QCTNAME(TP) + " breaks the chain holding " +
       QTNAME(chains_ob) + " to the wall.\n", TP);

     TO->break_chains();
     set_alarm(1.0, 0.0, chains_ob->unchain_me(TP));
     return "You break the chains; freeing its victim from their hold!\n";
  }
  else
  {
     return "You break the chains; feeling quite dump that none " +
      "was freed from your actions.\n";
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
