/* created by Aridor 02/09/94 */

#include "../local.h"

inherit ROOM_BASE

#include "../guild/guild.h"
#include <macros.h>
#define THIS_ROOMS_VALUE   1


void
init()
{
    ::init();
    ADD("my_say","say");
    ADD("my_say","shout");
    ADD("my_say","ask");
    ADD("my_say","whisper");
    add_action("my_say","'",1);
}


void
create_thief_room()
{
    set_short("In a cavern");
    set_long("This is a narrow cavern. It is still very dark and gloomy in " +
	     "here. The walls just seem to absorb any light within the " +
	     "room.\n");
    
    add_exit(TURNC,"south","@@if_open");
    
    add_prop(ROOM_I_LIGHT, -4);
    
    add_item(({"wall","walls"}),
	     "The walls are all rock, like the floor and the ceiling, and " +
	     "someone just very crudely hacked this cavern into the stone. " +
	     "You can see some strange moss growing on the walls, which " +
	     "might be the reason for the gloominess here in the room.\n");
    add_item("floor",
	     "The floor is not very even here, but you still detect a " +
	     "small button on the floor near the north wall.\n");
    add_item("ceiling",
	     "Like the walls, the ceiling is covered with some kind of " +
	     "black moss.\n");
    add_item(({"moss","strange moss","black moss"}),
	     "This is black moss, and it seems to absorb the light within " +
	     "the room, making everything appear in a very dull and dark " +
	     "shadow. You have the feeling that light isn't the only thing " +
	     "that is absorbed from the moss.\n");
    add_item("button",
	     "It is a small metal button protruding from the floor near " +
	     "the north wall.\n");
    add_cmd_item("button",({"press","push"}),"@@solved_this");
}


string
solved_this()
{
    if (!CAN_SEE_IN_ROOM(TP) && !TP->test_bit("Krynn",GUILD_GROUP, QUEST_BIT))
      return "It is too dark to see.\n";
    if (!sizeof(TP->query_team_others()))
      TP->add_prop(THIEF_I_CAN_ENTER, 
		   TP->query_prop(THIEF_I_CAN_ENTER) | THIS_ROOMS_VALUE);
    return "You press the small button, but nothing seems to happen.\n";
}


int
if_open()
{
    if ((TURNC)->query_exit_direction() == "north")
      return 0;
    write("You find that it is impossible to leave the room as the door " +
	  "ends in a brick wall!\nYou push again, and suddenly you fall " +
	  "through the wall into another room, the wall slamming back " +
	  "into place behind you.\n");
    return 0;
}

int
my_say()
{
    write("You can't seem to articulate yourself.\n");
    return 1;
}
