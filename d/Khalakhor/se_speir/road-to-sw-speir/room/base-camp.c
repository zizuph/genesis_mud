/*
 * Base file for the camp on the road linking SE Speir and SW Speir
 * Tapakah, 09/2021
 */

#pragma no_clone
#pragma strict_types

#include <macros.h>
#include <filepath.h>
#include "../defs.h"

inherit KSTDROOM;
inherit BASE_ROOM;

object room_npc;

string
describe_tent ()
{
  string desc = "Each room in the camp has a tent established. ";
  string x_desc;
  if (room_type == LEVEL_CAPTAIN)
    x_desc = "The tent in this room is larger than all others, with "+
      "a blue, green and black standard flying over it. It has " +
      "splashes of seawater all around it.";
  else if (room_type == LEVEL_SERGEANT || room_type == LEVEL_LIEUTENANT)
    x_desc = "The tent in this room is somewhat more spacier than the "+
      "ones at the perimeter of the camp.";
  else 
    x_desc = "The tent in this room is of a simple, square design, that "+
      "would allow three or four men to sleep comfortably in it.";

  return desc + x_desc + "\n";  
}

string
setup_long ()
{
  string desc = "You are standing in the recently established camp not far "+
    "west from the plains surrounding Port Macdunn. Judging by the colors "+
    "of the tents, it mostly consists of soldiers from the Macdunn and the "+
    "MacCrimmon clans. It's unclear whether this camp is established "+
    "here as a predecessor to a future fort, or whether it's a "+
    "for a further advance. ";
  return desc;
}

void
add_camp_npc ()
{
  if (room_npc && present(room_npc))
    return;

  object this_npc;
  string *npc_files;

  switch (room_type) {
  case LEVEL_CAPTAIN:
    npc_files = ({"courier", "soldier"});
    break;
  case LEVEL_LIEUTENANT:
    npc_files = ({"standard-bearer"});
    break;
  case LEVEL_SERGEANT:
    npc_files = ({"sergeant"});
    break;
  default:
    npc_files = ({"soldier"});
    if (random(2))
      npc_files += ({"soldier"});
  }
  foreach (string npc_file: npc_files) {
    npc_file = NPCS_DIR + npc_file;
    if (file_size(npc_file + ".c") == -1)
      continue;

    this_npc = clone_object(npc_file);
    this_npc->set_clan(random(2) ? "Maccrimmon" : "Macdunn");
    this_npc->move(TO);
    if (! room_npc)
      room_npc = this_npc;
    else {
      this_npc->set_random_move(20);
      this_npc->set_restrain_path(ROOM_DIR + "camp-");
    }
  }
  room_npc->team_join(this_npc);
}

void
reset_room ()
{
  ::reset_room();
  add_camp_npc();
}

void
create_khalakhor_room ()
{
  ::create_khalakhor_room();
  coords = query_local_coords();
  set_room_type();
  set_short("In a camp next to the rocky shore");
  set_long(setup_long);
  add_item(({"sea", "cala fasdagh", "Cala Fasdagh", "waves"}),
           "The waves, six feet and higher, are constantly crashing "+
           "into the rocky strip between you and the camp. Occasionally "+
           "a bouncing spash lands at your feet.\n");
  add_item(({"rocks", "strip", "shore"}), "The rocks are dark and glistening "+
           "with the sea water. Birds land on them once in a while, "+
           "in search for prey.\n");
  add_item(({"tent", "tents"}),
           describe_tent);
  add_exit(sprintf("tent-%d-%d", coords[0], coords[1]),
           "tent");
  set_alarm(0.5, 0.0, reset_room);
}
