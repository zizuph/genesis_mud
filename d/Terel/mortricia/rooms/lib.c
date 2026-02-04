/*
    A  test library
 */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()
#define LIB_DIR        "/d/Terel/mortricia/rooms/"

init()
{
    ::init();
    add_action("read_book", "read");
}

void
create_room()
{
    set_short("Basic room");
    set_long(BS("It's a very basic room as you can see. There " +
		"is an index on the wall.\n"));

    add_item("index", "These books can be read:\n" +
	 "book1\n" +
	 "book2\n"
	 );

    add_prop(ROOM_I_INSIDE, 1);
}

read_book(string str)
{
    string text, file;

    file = LIB_DIR + str + ".book";
    if (file_size(file) == -1) {
	write("There is no book in the library labeled: " + str + "\n");
	return 1;
    }
    text = read_file(file);
    write(text);
    say(QCTNAME(TP) + " starts to read a book.\n");
    return 1;
}
