/*
 * Dust 920813: This is a room of the maze in the mansion. Only
 * one path leads through it.
 */
inherit "/std/room";
#include <stdproperties.h>

#include "/d/Terel/common/terel_defs.h"
#define COLDIR TOWNDIR + "mansion/colors/"
#define HINTFILE COLDIR + "colorpath.hint"
#define HINTINDEX 4
#define NEXTROOM COLDIR + "maze6"
#define EXITROOM COLDIR + "maze_exit"


create_room()
{
    set_short("maze");
    set_long(break_string("You feel a bit nauseous in this room... " +
	"there's nothing here that could help you finding your way through " +
	"this maze. The floor is foggy and swallows everything lying on " +
	"the floor.\n", 70));
    add_exit("@@select|n@@","north",0,10);
    add_exit("@@select|e@@","east",0,10);
    add_exit("@@select|s@@","south",0,10);
    add_exit("@@select|w@@","west",0,10);
    add_prop(ROOM_I_NO_MAGIC, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
}

/* tidy_up() makes sure all dropped objects are removed (no orientation) */
tidy_up()
{
    object *op;
    int i;

    op = all_inventory(this_object());
    for (i=0; i<sizeof(op); i++)
	if (!interactive(op[i]))
	    (op[i])->remove_object();
}

string
select(string dir)
{
    string hint;

    seteuid(getuid());
    tidy_up();
    if (dir == read_bytes(HINTFILE, HINTINDEX, 1))
	return NEXTROOM;
    return EXITROOM;
}

