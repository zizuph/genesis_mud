/*
 * Dust 920813: Entrance to maze
 * exit upwards added. Mortricia 920906.
 * exit eastwards added by Vader on 920924.
 *
 * added 'strange rune' option for looking at the quest
 * so it does not conflict with the Neidar gift.
 * Varian - April, 2020
 */

inherit "/std/room";

#include "/d/Terel/common/terel_defs.h"
#define COLDIR TOWNDIR + "mansion/colors/"

create_room()
{
    set_short("entrance to a maze");
    set_long(break_string("A few traces of old firewood can be seen " +
       "scattered about here.  To the south, there is an entrance " +
       "to a strange maze-like system.  You can also climb up via " +
       "a ladder.  On the south wall, there is a sign.\n", 70));

    add_cmd_item("sign", "read",
	    break_string("The sign says: 'Be warned that thou will be lost " +
	    "if thou pass this door.' Below you see a strange rune.\n",70));
    add_item("sign", "There's nothing special about the sign. Maybe you " +
	    "should read it?\n");
    add_item("ladder", "The ladder seems to be somewhat brittle.\n");
    add_item(({"wood", "firewood"}), "It is old, rotted, and useless.\n");
    add_item( ({"rune", "strange rune", "rune on wall", "wall rune",
		"south wall"}),
		"The rune looks like this:\n" +
		"    |\n" +
		"  +-+\n" +
		"- |6|\n" +
		"  +-+\n" +
		"  |5|\n" +
		"  +-+-+\n" +
		"  |4|3|\n" +
		"  +-+-+-+\n" +
		"    |2|1|\n" +
		"    +-+-+\n" +
	break_string("You wonder if this rune is the path through " +
	    "the secret maze... but - not without reason - you " +
	    "doubt the pervert designer of the maze made it that " +
	    "easy for you....\n",70));

   add_exit(COLDIR + "maze1","south",0);
   add_exit(MANSION + "chapel/marb_sarc", "up", 0);
}
