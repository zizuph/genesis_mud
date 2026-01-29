/* created by Aridor 02/09/94 */

#include "../local.h"

inherit ROOM_BASE

#include <ss_types.h>
#include <macros.h>

int wall = 1;

void
reset_thief_room()
{
    wall = 1;
}

void
create_thief_room()
{
    set_short("In a hallway");
    set_long("This is a hallway leading west from here and an opening to the " +
	     "north. The hallway is cut out of the rock, of course, and it " +
	     "seems to have gone further east in earlier days, but there is " +
	     "now a crude brick wall in this direction@@torn_down@@.\n");
    
    add_exit(TURNC,"north","@@if_open");
    add_exit(CAVERN + "c6","west");
    add_exit(THEIWAR + "r37","east","@@wall");
    
    DARK;
    
    add_item(({"wall","crude wall","brick wall"}),
	     "@@wall_state@@");
    add_item(({"opening","another wall","other wall"}),
	     "@@other_wall_state@@");
    add_cmd_parse("[in] [down] [the] 'east' / 'crude' / 'brick' 'wall'",
		  ({"break","tear","kick"}),"@@break_wall@@");
    add_cmd_parse("[in] [down] [the] 'north' / 'other' / 'another' " +
		  "'wall' / 'opening'",
		  ({"break","tear","kick"}),"@@break_other_wall@@");
    add_cmd_parse("[in] [down] [the] 'wall'",({"break","tear","kick"}),
		  "Which wall do you want to break? The north wall or the " +
		  "east wall?\n");
}

string
torn_down()
{
    if (wall)
      return "";
    return ", which has been torn down again";
}

string
wall_state()
{
    if (wall)
      return "This is a brick wall, blocking your way to the east. You can't " +
	"see anything special about it, though.\n";
    return "This used to be a brick wall, blocking your way to the east. It " +
      "is torn down so you can actually pass through.\n";
}

int
if_open()
{
    if ((TURNC)->query_exit_direction() == "south")
      return 0;
    write("You find that it is impossible to leave the room as the door ends " +
	  "in another wall!\n");
    return 1;
}


int
wall()
{
    if (!wall)
      return 0;
    write("There is a brick wall there, you can't go this way!\n");
    return 1;
}

int
query_wall()
{
    return wall;
}

void
set_wall(int i)
{
    wall = i;
}

string
break_wall()
{
    
    if (!CAN_SEE_IN_ROOM(TP))
      return "It is too dark too see.\n";
    if (!wall)
      return "The wall is already torn down.\n";
    if (random(TP->query_stat(SS_STR)) > 29)
      {
	  wall = 0;
	  tell_room(THEIWAR + "r37",
		    ({"Suddenly, the brick wall crumbles to pieces!\n",
		      "Suddenly, the brick wall crumbles to pieces!\n",
		      "Suddenly, there is a loud crashing noise to your west!\n"}));
	  SAY(" takes a leap and breaks down the brick wall to the east.");
	  return "You break down the brick wall!\n";
      }
    return "You try as hard as you can but you are unable to break the wall.\n";
}

string
break_other_wall()
{
    
    if (!CAN_SEE_IN_ROOM(TP))
      return "It is too dark too see.\n";
    return "You try as hard as you can but you are unable to break the north " +
      "wall.\n";
}

string
other_wall_state()
{
    if ((TURNC)->query_exit_direction() == "south")
      return "You can leave the room through the opening by going north.\n";
    return ("There is a wall blocking the opening to the north. It is impossible " +
	    "to leave the room that way now.\n");
}
