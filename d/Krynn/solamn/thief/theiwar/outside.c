/* created by Aridor 04/21/94 */

#include "../local.h"

inherit ROOM_BASE

#include <macros.h>
#include <ss_types.h>

void
create_thief_room()
{
    set_short("@@my_short");
    set_long("@@my_long");
    add_exit(THEIWAR + "r11","northwest","@@gate_closed");
    add_exit(ON_THE_PLAINS, "down","@@down_the_path");
    set_noshow_obvious(1);
    OUTSIDE;
    add_item(({"path", "ledge"}),
	     "This is a small path hewn into the side of a steep cliff. " +
	     "It is leading downwards in a zig-zag and @@opening_text@@.\n");
    add_item(({"mountainside","cliff","stone"}),
	     "A steep cliff rises upwards and also downwards from here. " +
	     "There is a narrow path here that you can barely stand on.\n");
    add_item(({"opening","gate","entrance"}),
	     "@@entrance_text@@");
}

string
opening_text()
{
    if (!(DOORROOM)->query_gate_state())
      return "an opening into the inside of the mountain is right before you";
    else
      return "it ends right in front of hard stone";
}

string
entrance_text()
{
   if (!(DOORROOM)->query_gate_state())
      return "It is clearly some kind of gate to the inside of the " +
	"mountain. You can enter by going northwest.\n";
    else
      return "You find no opening.\n";
}

string
my_short()
{
    if (!(DOORROOM)->query_gate_state())
      return "End of the path outside the opening.\n" +
	"There are two obvious exits: northwest, down";
    else
      return "End of the path in front of a cliff.\n" +
	"There is one obvious exit: down";
}

string
my_long()
{
    string str = "You are standing at the end of a path which leads down " +
      "the mountainside in one direction. ";
    if (!(DOORROOM)->query_gate_state())
      str += "The gate is currently open and you can enter by going " +
	"northwest.\nThere are two obvious exits: northwest, down.\n";
    else
      str += "Right in front of you in the other direction is a blank " +
	"cliff.\nThere is one obvious exit: down.\n";
    return str;
}

int
gate_closed()
{
    if (!(DOORROOM)->query_gate_state())
      {
	  write("You step into the opening.\n");
	  return 0;
      }
    write("There is no obvious exit northwest.\n");
    return 1;
}

int
down_the_path()
{
    write("You follow the practically invisible path down the mountainside. " +
	  "Suddenly...\n\nYou trip and slide down " +
	  "the last almost vertical part onto the plains.\n");
    find_player("aridor")->catch_msg(TP->query_name() + " leaves THIEFAREA to plains.\n");
    return 0;
}
