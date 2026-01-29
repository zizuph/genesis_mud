inherit "/std/room";
 
#include "default.h"

object prisoner;

void
reset_room()
{
    if (prisoner)
	return;
    clone_object(TCASTLE_DIR + "npc/prisoner")->move_living("into cell",
							  this_object());
}
 
void
create_room()
{
    set_short("Dark cell");
    set_long( "The cell smells rotten. There are no air "+
	     "circulation in here and no light. There is something "+
	     "engraved on one wall.\n" );
 
    add_item("wall", "There are some words engraved on it.\n");
    add_item("words", "@@word_desc@@");
    add_cmd_item("words", "read", "@@word_desc@@");
 
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
 
    clone_object(TCASTLE_DIR + "doors/cdoor2_b")->move(this_object());
 
    reset_room();
}
 
string
word_desc()
{
    return "Why did you leave me here when you escaped?\n";
}
