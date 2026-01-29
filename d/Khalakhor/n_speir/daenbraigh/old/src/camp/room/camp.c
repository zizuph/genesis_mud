/*
 * Basic camp room
 */

#pragma strict_types;
#include <stdproperties.h>
#include <macros.h>

#include "/d/Khalakhor/sys/defs.h";
#include "/d/Khalakhor/sys/terrain.h";
#include "../../daenbraigh.h";
#include "../../camp/camp.h";

inherit "/d/Khalakhor/std/room";
inherit DAENBRAIGH_BASE;

void
create_camp_room(mapping items)
{
  string item_names;
  
  ::create_khalakhor_room();

  item_names = m_indices(items);
  foreach(string item: item_names) {
    switch(item) {
    case 'tower':
      add_item(
               ({"tower", "watchtower", "platform", "wooden platform"}),
               (
                "More just an enclosed wooden platform, it is unclear from "+
                "this position if it is currently inhabited or not.\n"
                )
               );
    case 'tent':
      add_item(
               ({"tent", "command tent", "command tents",
                 "small tent", "small tents"}),
               (
                "Sewn together from the hides of various animals... " +
                "among other things.\n")
               );	
    }
  }

  
