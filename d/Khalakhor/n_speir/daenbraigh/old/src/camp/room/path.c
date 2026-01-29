/*
 * Basic camp path room
 */

#pragma strict_types;
#include <stdproperties.h>
#include <macros.h>

#include "/d/Khalakhor/sys/defs.h";
#include "/d/Khalakhor/sys/terrain.h";
#include "../../daenbraigh.h";
#include "../../camp/camp.h";

inherit "/d/Khalakhor/std/room";

void
create_path_room (mapping items)
{
  string item_names;
  
  ::create_khalakhor_room();
  item_names = m_indices(items);
  foreach(string item: item_names) {
    switch(item) {
    case "tower":
      add_item(
               ({"tower", "watchtower", "platform", "wooden platform"}),
               items["tower"] ?
               "More just an enclosed wooden platform, now you see clearly it "+
               "has been equipped and manned to provide careful watch.\n" :
                "More just an enclosed wooden platform, it is unclear from "+
                "this position if it is currently inhabited or not.\n"
               );
      break;
    case "tent":
      add_item(
               ({"tent", "command tent", "command tents",
                 "small tent", "small tents"}),
               "Sewn together from the hides of various animals... " +
               "among other things.\n"
               );	
      break;
    case "spike":
      add_item(
               ({ "spike", "spikes", "wooden spike", "wooden spikes" }),
               "They look extremely sharp.\n"
               );
      break;
    case "path":
      add_item(
               ({ "path", "perimeter" }),
               "It is well traveled, as if by frequent patrol.\n"
               );
      break;
    case "pole":
      add_item(
               ({ "pole", "poles", "head", "heads" }),
               "Judging by the expressions on the faces, they all "+
               "died painfully.\n"
               );
      break;
    case "barricade":
      add_item(
               ({ "barricade", "barrier" }),
               items["barricade"] ?
               "Just more wooden spikes mostly with a kind of gate.\n" :
               "You see a dense line of wooden spikes somewhere at a distance.\n"
               );
      break;
    case "hound":
      add_cmd_item(({ "baying", "hound", "hounds", "heads" }), "listen",
                   items["hound"] ?
                   "They don't sound near enough to be a threat... yet.\n":
                   "Tremendous yelps and howls emerge right next to you.\n"
                   );
        
    }
  }

  add_prop(ROOM_I_INSIDE,0);
  set_terrain(TERRAIN_ROAD);

}
