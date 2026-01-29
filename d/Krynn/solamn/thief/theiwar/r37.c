/* created by Aridor 04/19/94 */

#include "../local.h"

inherit ROOM_BASE

#include <macros.h>
#include <ss_types.h>
#define OTHERSIDE (CAVERN + "c7")

void
create_thief_room()
{
    set_short("In a cavern");
    set_long("@@my_long");
    
    add_exit(OTHERSIDE, "west","@@wall");
    add_exit(THEIWAR + "r36", "south");
    
    DARK;
    
    add_item(({"wall","crude wall","brick wall"}),
	     "@@wall_state@@");
    add_cmd_parse("[in] [down] [the] [west] [crude] [brick] 'wall'",
		  ({"break","tear","kick"}),"@@break_wall@@");
    OTHERSIDE->load_me();
}


string
my_long()
{
    if (OTHERSIDE->query_wall())
      return "You are at a dead end. Apparently, the hallway has simply been sealed off " +
	"with a brick wall! This crudely built wall west of you prevents you from going " +
	"west. The hallway leads south only now.\n";
    return "You are at a dead end. Apparently, the hallway used to be sealed off with " +
      "a brick wall! This crudely built wall has been torn down now so that you can go west, " +
      "too.\n";
}

string
wall_state()
{
    if (OTHERSIDE->query_wall())
      return "This is a brick wall, blocking your way to the west. You can't see " +
	"anything special about it, though.\n";
    return "This used to be a brick wall, blocking your way to the east. It is torn " +
      "down so you can actually pass through.\n";
}

int
wall()
{
    if (!OTHERSIDE->query_wall())
      return 0;
    write("There is a wall there, you can't go this way!\n");
    return 1;
}

string
break_wall()
{
    
    if (!CAN_SEE_IN_ROOM(TP))
      return "It is too dark too see.\n";
    if (!OTHERSIDE->query_wall())
      return "The wall is already torn down.\n";
    if (random(TP->query_stat(SS_STR)) > 29)
      {
	  OTHERSIDE->set_wall(0);
	  tell_room(OTHERSIDE,"Suddenly, the brick wall crumbles to pieces!\n");
	  SAY(" takes a leap and breaks down the brick wall to the west.");
	  return "You break down the brick wall!\n";
      }
    return "You try as hard as you can but you are unable to break the wall.\n";
}
