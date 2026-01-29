/*
 * Base file for the tent in the camp on the road linking SE Speir and SW Speir
 * Tapakah, 09/2021
 */

#pragma no_clone
#pragma strict_types

#include <macros.h>
#include <filepath.h>
#include "../defs.h"

inherit KSTDROOM;
inherit BASE_ROOM;

mixed Search_Junk = ({
  OBJS_DIR + "old-kilt",
  OBJS_DIR + "glenwhilly",
  OBJS_DIR + "flodigarry",
  OBJS_DIR + "old-rarebit",
  OBJS_DIR + "pen-tre-tafarn-y-fedw",
});
int empty = 0;
int count;
string npc;
object *tent_npc;

void
add_tent_npc (string npc_file, int count)
{
  int n;
  if (! tent_npc)
    tent_npc = allocate(count);
  for (n=0; n<count; n++)
    if (! tent_npc[n]) {
      tent_npc[n] = clone_object(npc_file);
      switch (room_type) {
      case LEVEL_SOLDIER:
        tent_npc[n]->set_clan(coords[0] < 17 ? "Maccrimmon" : "Macdunn");
        break;
      case LEVEL_CAPTAIN:
        tent_npc[n]->set_clan("Macdunn");
        break;
      default:
        tent_npc[n]->set_clan(n % 2 ? "Maccrimmon" : "Macdunn");
      }
      tent_npc->move(TO);
    }
  for (n=1; n<count; n++) 
    tent_npc[0]->team_join(tent_npc[n]);
}

void
reset_room ()
{
  ::reset_room();
  if (empty && ! random(3))
    empty = 0;
  add_tent_npc(npc, count);
}

string
search_here (object player, string str)
{
  string item, rest;
  int skill;

  if (sscanf(str, "%s for %s", item, rest) != 2)
    item = str;
  
  if (item != "here" && item != "pile" && item != "stuff")
    return "";

  object *audience = filter(all_inventory(), &->is_camp_warrior());
  if (sizeof(audience))
    return("You do not dare dig deep in presence of "+
           "the tent inhabitants.\n");
  if (empty)
    return "";

  object discovery;
  string *search_list = ({}) + Search_Junk;

  switch (room_type) {
  case LEVEL_CAPTAIN:
    return ""; // nothing to search for at the captain's tent
    break;
  case LEVEL_LIEUTENANT:
    search_list += ({ BODHRAN });
    break;
  case LEVEL_SERGEANT:
    search_list += ({ CARNYX });
    break;
  }
  empty = 1;
  discovery = clone_object(one_of_list(search_list));
  string move_desc =
    "You find a " + discovery->short() + " in the pile and pick it up.\n";
  if (discovery->move(player)) {
    discovery->move(TO);
    move_desc += "You cannot carry it, though, so you drop it on the "+
      "ground.\n";
  }
  return move_desc;
}

string
describe_tent ()
{
  if (! coords)
    coords = query_local_coords();

  string colors = coords[0] < 17 ? "green and blue" : "black and blue";
  
  string desc = "The tent is a square construction based on "+
    "interconnected four wooden poles with a canvas cap and canvas "+
    "flaps on the sides. The tent's cap is decorated with bands of "+
    colors + ".\n";
  return desc;
}

string
setup_room ()
{
  string desc, rank;

  switch (room_type) {
  case LEVEL_SOLDIER:
    desc = "You are standing inside a large tent that is part of "+
      "the new camp. The tent is quite roomy. You can see four bunks "+
      "at the corners of the tent, some military equipment next to "+
      "each one, and a pile of other stuff in the middle of the tent. "+
      "Other than the pile, it's very clean.\n";
    add_item(({"pile", "stuff"}), "It looks like all the stuff the "+
             "soldiers decided to be unnecessary has been piled in "+
             "there, waiting to be discarded. Who knows what you can "+
             "find in there.\n");
    npc = SOLDIER;
    count = 4;
    break;
  case LEVEL_CAPTAIN:
    desc = "You are standing inside a tall tent belonging to the "+
      "captain of the camp. One large bunk is in the far corner, and "+
      "a makeshift desk is near you. Everything is scrupulously clean.\n";
    add_item(({"desk"}), "It is clean and bare. The captain does not "+
             "seem to leave any papers out of his sight.\n");
    npc = CAPTAIN;
    count = 1;
    break;
  default:
    rank = room_type == LEVEL_SERGEANT ? "lower" : "higher";
    npc  = room_type == LEVEL_SERGEANT ? SERGEANT : LIEUTENANT;
    count = 2;
    desc = "You are standing inside a large tent that is part of "+
      "the new camp. The tent is very roomy, as only two bunks are "+
      "in there. Judging by the equipment next to the bunks, the tent "+
      "belongs to the " + rank + " ranked level of command in the "+
      "camp. Surprisingly, you see a pile of stuff in the middle "+
      "of this tent, probably waiting to be discarded.\n";
    add_item(({"pile", "stuff"}), "It looks like all the unnecessary "+
             "junk has been thrown together in there. Who knows, maybe "+
             "you can find something valuable in there.\n");
    break;
  }
  add_tent_npc(npc, count);
  return desc;
}

void
create_khalakhor_room ()
{
  ::create_khalakhor_room();
  coords = query_local_coords();
  set_room_type();
  set_short("In a tent in the camp next to the rocky shore");
  set_long(setup_room());
  add_item(({"tent", "tents"}),
           describe_tent);
  add_item(({"bunk", "bunks"}),
           "The bunks are clean and neatly set.\n");
  add_exit(sprintf("camp-%d-%d", coords[0], coords[1]),
           "out");
  add_prop(OBJ_S_SEARCH_FUN, "search_here");
}
