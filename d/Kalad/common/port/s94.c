#include "default.h"
inherit PORT_ROOM;

#define SAILOR PORT + "npc/sailor1"
object ob1;
object ob2;

void
create_port_room()
{
    add_prop(ROOM_NO_TIME_DESC,1);

    set_short("Intersection of two Long Piers");
    set_long("You are standing at the intersection of two long wooden "+
      "piers that are within the bay. One travels northward from here "+
      "while the other heads in an east-west direction. An enormous ship "+
      "is docked to your northwest. The "+
      "wooden planks of the pier seem to creak and groan with the slightest "+
      "movement and the sound of water violently hitting against the supports assaults "+
      "your senses. The cry of seagulls fills the air.\n");
    add_item(({"bay"}),"A beautiful expanse of water that sparkles with "+
      "an azure color.\n");
    add_item(({"wooden planks","planks","wooden plank","plank"}),"Although "+
      "they groan and creak with your every movement, the weather-beaten "+
      "wood seems sturdy enough.\n");
    add_item(({"water"}),"It fills the bay.\n");
    add_item(({"supports","support"}),"Large wooden logs that hold the pier "+
      "above the water line.\n");
    add_item(({"enormous ship","ship"}),"An ancient looking galleon whose "+
      "massive masts tower above the docks.\n");
    add_exit(PORT + "s93", "west");
    add_exit(PORT + "s87", "north");
    add_exit(PORT + "s95", "east");
    reset_room();
}

reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(SAILOR);
	ob1 -> move_living("xxx",TO);
    }

    if(!ob2)
    {
	ob2 = clone_object(SAILOR);
	ob2 -> move_living("xxx",TO);
	ob1 -> team_join(ob2);
    }

}

