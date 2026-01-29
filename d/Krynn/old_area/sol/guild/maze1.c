/* Maze to the guild by Lord Rastlin */
/* modified to inherit the base file by Aridor, 09/94 */

#include "/d/Krynn/common/defs.h"
#include "guild.h"
#include "local.h"
#include <ss_types.h>
#include <macros.h>

inherit MAZE_BASE;

void
create_maze()
{
    set_long("You are walking in the forest. " +
	     "The forest is very thick, and it looks " +
	     "the same where ever you look. " +
	     "On one of the trees is a small wooden sign. " +
	     "To the north can you see the people of Solace " +
	     "walk around.\n");

    add_exit(C_SOLACE, "north");
    add_exit(TDIR + "maze2", "east");
    add_exit(TDIR + "maze2", "west");

    add_item(({"sign", "wooden sign"}), 
	     "It is a small wooden sign with some arcane writing,\n" +
	     "you may be able to read it.\n");
    add_cmd_item("sign", "read", "@@my_read");
}

void
init()
{
    add_action("goto_hall", "hall");
    ::init();
}

int
goto_hall()
{
    if (TP->query_skill(SS_LANGUAGE) > 31)
      {
	  write("You take the shortcut to the entrance of the old guild.\n");
	  TP->move_living("along a shortcut", ENTRANCE);
	  return 1;
      }
    return 0;
}

int
my_read()
{
    write("You examine the script closely.....\n");
    if (TP->query_skill(SS_LANGUAGE) > 31)
      write("Your translation is a bit rough, but you get the idea that\n" + 
	    "by typing 'hall' you will go straight to the guild hall.\n");
    else
      write("You can't seem to get the gist of this message.\n");
    return 1;
}
