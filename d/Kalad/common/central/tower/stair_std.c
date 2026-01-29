// 20210803 Meton Fixed typo from outter to outer

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()
{
    ::create_room();
    add_prop(ROOM_I_INSIDE,1);

    set_short("spiral staircase");
    set_long(BS("You are on a spiral staircase in the bell tower, " +
      "which curves around the walls in both directions. " +
      "The walls are made of thick, " +
      "interlaying blocks of granite. " +
      "\n"));

    hear_bell = 4; /*deafening: inside bell tower*/

    add_item(({"stair","stairs","staircase","spiral staircase"}),
      BS("They are made of hard stone and curve, out of sight in both directions, " +
      "around the walls of the tower.\n"));
    add_item(({"circular wall","wall","walls"}), BS(
      "The walls are made of thick, interlaying blocks of granite. " +
      "There is an outer and inner wall. " +
      "\n"));
    add_item("outer wall",BS(
      "This is the outside wall of the tower. It is made of " +
      "thick, interlaying blocks of granite.\n"));
    add_item("inner wall",BS(
      "The inner wall is circular and fills the center of the tower. " +
      "It is  made of thick, interlaying blocks of granite.\n"));

} 
