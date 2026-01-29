/*
   Wayreth.

   clearing.c
   ----------

   Coded ........: 95/05/24
   By ...........: Jeremiah

   Latest update : 95/06/01
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/wayreth/local.h"
#include <composite.h>

inherit WAYOUTROOM;

void
create_wayreth_room()
{
    set_short("In a clearing, at a tower, in the light forest");
    set_long("You find yourself in a small clearing somewhere in the " +
      "light forest. In the middle of the clearing a tall strange " +
      "dark tower rises into the sky. The tower is enclosed in a " +
      "wall-shaped equilateral triangle of the same dark material " +
      "as the tower itself. There is a small tower at each " +
      "point of the triangular wall. An aura of overwhelming and " +
      "powerful magic emanates from the tall tower and its " +
      "protecting walls. There is a pair of large silver and golden " +
      "gates in the north-south going part of the wall in front " +
      "you. The gates lead west, into the courtyard in front of " +
      "the tower.\n");

    OUTSIDE;

    add_item(({"gate", "gates"}), "The gates are made of silver and gold " +
      "and seems as thin as cobweb. Their delicacy are contrasting " +
      "sharply with the immense walls and towers made of highly " +
      "polished black obsidian, magically raised from the bones " +
      "of the earth.\n");

    add_item(({"tower", "towers"}), "There a two different kinds of towers " +
      "in this small clearing. A large tower, rising high into " +
      "sky, and three smaller towers, one at each point of the " +
      "triangular wall enclosing the larger tower.\n");

    add_item(({"small towers", "smaller towers", "small tower"}),  
      "Three circular towers, one at each of the points " +
      "in the triangular wall enclosing the main tower. A row of " +
      "tall narrow windows, placed with equal intervals between " +
      "them all the way around, line each of the towers, almost at " +
      "the top. The towers are made of highly polished black " +
      "obsidian, magically raised from the bones of the earth.\n");

    add_item(({"window", "windows"}), "Windows.\n");

    add_item(({"wall", "walls"}), "The walls.\n");

    add_item(({"large towers", "larger towers", "large tower"}), 
      "A dark tower.\n");

    add_item("clearing", "A small clearing.\n");

    add_item("aura", "An aura.\n");

    add_exit(WFOREST + "forest11", "north", 0, 2);
    add_exit(WFOREST + "forest12", "northeast", 0, 2);
    add_exit(WFOREST + "forest19", "east", 0, 2);
    add_exit(WFOREST + "forest26", "southeast", 0, 2);
    add_exit(WFOREST + "forest25", "south", 0, 2);
    add_exit(WFOREST + "forest24", "southwest", 0, 2);
    add_exit(WTOWER + "yard02", "west", "@@through_gates");
    add_exit(WFOREST + "forest10", "northwest", 0, 2);
} 


int
through_gates()
{
    write("\nThe delicate gates swing silently open, allowing you " +
      "entrance to the Tower's courtyard beyond...\n\n");
    return 0;
}
