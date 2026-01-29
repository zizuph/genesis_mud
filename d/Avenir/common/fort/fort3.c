// file name:   /d/Avenir/common/outpost/fort3.c
// creator(s):  Kazz    Feb '95
// last update: Denis, Jul'96: Made the room to inherit /d/Avenir/inherit/room
//              Lilith, Apr 2022 Fort Makeover
// purpose:     middle of the fort

# pragma strict_types

#include "/d/Avenir/common/outpost/outpost.h"
#include "/d/Avenir/common/outpost/cave.h"
#include <macros.h>
#include <stdproperties.h>

inherit OUTPOST +"fort_base";

#define SEE_EAST   ({ OUTPOST + "fort5", OUTPOST + "fort3" })
#define SEE_WEST   ({ OUTPOST + "fort2", })
#define SEE_NORTH  ({ OUTPOST + "fort1"})


string 
east_view()
{
  object *inv, *live, room;
  int i;
 
  inv = ({ });
  for(i = 0; i < sizeof(SEE_EAST); i++)
    if((room = find_object(SEE_EAST[i])))
      inv += all_inventory(room);
 
  if(sizeof(inv)) 
  {
    live = FILTER_LIVE(inv);
    live = FILTER_CAN_SEE(live, TP);
    if(sizeof(live))
       return " where you can see "
          + COMPOSITE_LIVE(live);
  }
  return "";
}

string 
west_view()
{
  object *inv, *live, room;
  int i;
 
  inv = ({ });
  for(i = 0; i < sizeof(SEE_WEST); i++)
    if((room = find_object(SEE_WEST[i])))
      inv += all_inventory(room);
 
  if(sizeof(inv)) 
  {
    live = FILTER_LIVE(inv);
    live = FILTER_CAN_SEE(live, TP);
    if(sizeof(live))
       return "You can see "+ COMPOSITE_LIVE(live) +
       " on the other side.\n";
  }
  return "The window looks out into the cave beyond.\n";
}


string north_view()
{
  object *inv, *live, room;
  int i;
 
  inv = ({ });
  for(i = 0; i < sizeof(SEE_NORTH); i++)
    if((room = find_object(SEE_NORTH[i])))
      inv += all_inventory(room);
 
  if(sizeof(inv)) 
  {
    live = FILTER_LIVE(inv);
    live = FILTER_CAN_SEE(live, TP);
    if(sizeof(live))
       return " Inside the guards quarters is "
          + COMPOSITE_LIVE(live) + ".";
  }
  return "";
}

void 
create_domain_room()
{
	// add_exit_views() uses the short, so using lower case and articles.	
    set_short("the west courtyard");
    set_long("This is the west half of the central courtyard "+
        "of Fort Sybarus. It is paved in limestone cobbles that "+ 
        "gleam in the light of the Source. "+		
        "The forecourt and the gate are to the west, dominated "+
        "on each side by a north and south tower. "+	
		"North is the quarters for the dwarven guards who patrol "+
        "the fort and keep the peace.@@north_view@@"+
        " South is a storage area filled with crates that are "+
        "continually replenished by a team of goblin workers. "+
	    "An imposing building has been constructed at the east "+
        "end of the fortress.\n" );

    add_npc(MON + "dw_guard", 3, &->set_fort_wander());
	
    add_exit("fort1", "north");
    add_exit("fort5", "east");
    add_exit("fort2", "west");
    add_exit("fort6", "south");

    add_exit_views(); 
    add_basic_fort(); 	
    add_towers_out(); 
    add_gate_items();
	
    add_item(({"building", "east building", "imposing building",
        "banner", "trefoil symbol"}),
        "The building is extremely well-lighted. It has a "+
        "banner on it with the trefoil symbol of Sybarus.\n");
    add_item(({"storage", "storage area"}), 
        "You an see what looks like a storage area. You'll "+
        "need to go south to learn more.\n");
    add_item(({"forecourt"}), "There is an open area just "+
        "before the gate.\n");
    add_item(({"quarters"}), "It looks like the quarters for "+
        "the guards are north of here.\n");
			 
}


