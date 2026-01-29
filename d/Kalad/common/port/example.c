/*
    example.c

    Example of an inside room with a few npcs.
    Port district based on /d/Kalad/common/port/s39.c

    Fysix, March 1998
 */

#include "default.h"

inherit PORT_ROOM;

// The room has 1 seller npc and 2 guard npcs
object seller,
*guard = allocate(2);

// Clone npcs into this room
void
reset_room()
{
    seller = clone_npcs(seller, NPC + "hbseller");
    guard = clone_npcs(guard, NPC + "hbguard");

    // Let the npcs team
    guard[0]->team_join(guard[1]);
    guard[0]->team_join(seller);
}

void
create_port_room()
{
    set_short("Entrance room of the Halfling Brewery");
    set_long("You are standing in the grand entrance room of The Halfling "+
      "Brewery. The strong, earthy smell of beer fills the room with its "+
      "wonderful scent. To the west is a large plank wall, forming a "+
      "separate room. Looking to the east you can see a wooden archway, "+
      "and beyond that, another larger room.\n");

    add_prop(ROOM_I_INSIDE, 1);
    // Room is inside, so don't do set_hear_bell(1)

    // All items in the long description should be described here,
    // as well as other items you find by examining items
    add_item(({"large plank wall", "large wall", "plank wall", "wall"}),
      "Set within the wall is a small door.\n");
    add_item(({"small door", "door"}),
      "An ordinary, albeit small door. " +
      "A plaque hangs upon it.\n");
    add_item(({"wooden archway", "archway"}),
      "An opening in the east "+
      "that leads to another room.\n");
    add_item("floor", "The floor is made of long wooden planks.\n");
    add_item(({"planks", "wooden planks", "long wooden planks"}),
      "Long wooden planks make up the floor of the room.\n");
    add_item(({"ceiling", "wooden ceiling"}),
      "The wooden ceiling is supported by " +
      "long sturdy wooden beams.\n");
    add_item(({"beams", "wooden beams", "sturdy wooden beams"}),
      "Long sturdy wooden beams meet eachother high " +
      "above you in the center of the room, " +
      "supporting the ceiling.\n");

    // Add a readable sign to the room
    add_sign("sign", "read", "Manager's Office - DO NOT DISTURB -\n");

    add_exit(PORT + "s38", "west");
    add_exit(PORT + "s26", "north");
    add_exit(PORT + "s40", "east");

    reset_room();
}

