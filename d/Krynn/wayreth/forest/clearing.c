/*
   Wayreth.

   clearing.c
   ----------

   Coded ........: 95/05/24
   By ...........: Jeremiah

   Latest update : 16/04/09
   By ...........: Arman

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/wayreth/local.h"
#include "/d/Krynn/guilds/wohs/defs.h"
#include <composite.h>

inherit WAYOUTROOM;

void
create_wayreth_room()
{
    set_short("In a clearing before a tower, in the forest of Wayreth");
    set_long("You find yourself in a small clearing somewhere in the " +
      "forest of Wayreth. In the middle of the clearing a pair of tall " +
      "dark towers rise into the sky. The towers are surrounded by " +
      "immense walls of the same black-obsidian material " +
      "as the towers, with a pair of silver and golden " +
      "gates in the north-south going part of the wall in front " +
      "you. The gates lead west, into the courtyard in front of " +
      "the towers.\n");

    OUTSIDE;

    add_item(({"gate", "gates","silver and golden gates"}), 
      "The gates are made of silver and gold " +
      "and seems as thin as cobweb. Their delicacy are contrasting " +
      "sharply with the immense walls and towers made of highly " +
      "polished black obsidian, magically raised from the bones " +
      "of the earth.\n");

    add_item(({"tower", "towers"}), "There a two different kinds of towers " +
      "in this small clearing. Two large towers, rising high into " +
      "sky, and three smaller towers at each point of the " +
      "triangular wall enclosing the larger tower.\n");

    add_item(({"small towers", "smaller towers", "small tower"}),  
      "Three circular towers, one at each of the points " +
      "in the triangular wall enclosing the main tower. The towers " +
      "are made of highly polished black " +
      "obsidian, magically raised from the bones of the earth.\n");

    add_item(({"wall", "walls","immense walls", "triangular walls",
      "triangular wall"}), "Surrounding " +
      "the two large towers is an immense triangular-shaped wall. " +
      "No battlements can be seen on the walls... you imagine there " +
      "is no need for them, with the towers protected by magic.\n");

    add_item(({"large towers", "two large towers", "large tower"}), 
      "Two large towers - over 250 feet tall - rise within the boundaries " +
      "of the triangular walls before you. Here resides the Hall of Mages " +
      "where the council of High Sorcery come to discuss matters of magic, " +
      "and aspiring wizards come to take the Test of High Sorcery.\n");

    add_item("clearing", "You stand in a clearing in the middle of the " +
      "magical forest of Wayreth that surrounds the Tower of High Sorcery " +
      "of Wayreth.\n");

    add_item(({"forest","forest of wayreth","magical forest"}),
      "The forest of Wayreth is a magical forest that surrounds the " +
      "Tower of High Sorcery. The enchantments of the forest " +
      "mean only those the conclave of High Sorcery want to find the tower " +
      "may be able to find the tower.\n");

    add_exit(WFOREST + "forest11", "north", 0, 2);
    add_exit(WFOREST + "forest12", "northeast", 0, 2);
    add_exit(WFOREST + "forest19", "east", 0, 2);
    add_exit(WFOREST + "forest26", "southeast", 0, 2);
    add_exit(WFOREST + "forest25", "south", 0, 2);
    add_exit(WFOREST + "forest24", "southwest", 0, 2);
    add_exit("/d/Krynn/wayreth/tower/yard02", "west", "@@through_gates");
    add_exit(WFOREST + "forest10", "northwest", 0, 2);
} 


int
through_gates()
{
    if(WOHS_IS_MEMBER(TP))
      write("\nThe gates to the Tower of High Sorcery open in welcome " +
            "as you approach.\n\n");
    else
      write("\nThe gates to the Tower of High Sorcery " +
      "open as you approach. It would seem the Wizards of " +
      "High Sorcery are expecting you!\n\n");

    say("The Tower of High Sorcery gates to your west swing open.\n");
    return 0;
}
