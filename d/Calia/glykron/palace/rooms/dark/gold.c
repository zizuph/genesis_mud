#pragma save_binary

inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

object kroug = 0;

int
guarded()
{
    object kroug;

    kroug = present("kroug");
    if (kroug && kroug->query_name() != "corpse"){
	write("The kroug won't let you by!\n");
	say("The kroug blocks " + QCTNAME(TP) + "'s attempt to go north.\n");
	return 1;
    }

    return 0;
}

void
reset_room()
{
    if (kroug)
	return;

    kroug = clone_object(MONSTER("gold_kroug"));
    kroug->move(THIS);
    tell_room(THIS, QCTNAME(kroug) + " arrives.\n");
}

void
create_room()
{
    set_short("The golden room");
    set_long(break_string(
	"This is a small trapezoidal-shaped room whose east and west walls " +
	"slope away to the north.  " +
	"The walls, the bed, and the dresser are all lined with gold.  " +
	"There is a picture on the wall of a lady in a golden dress.  " +
	"\n", 70));
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_LIGHT, 1);
    add_exit(ROOM("dark_stairs"), "south", 0);
    add_exit(ROOM("dark_black"), "north", "@@guarded");
    add_exit(ROOM("dark_silver"), "west", 0);
    add_exit(ROOM("dark_bronze"), "east", 0);
    clone_object(OBJECT("warning_sign"))->move(THIS);
    add_item( ({ "painting", "picture" }),
	 "The painting has been badly damaged.\n");
    add_item("bed", "The golden bed looks comfortable.\n");
    add_item("dresser", "The golden dresser has been broken to splinters.\n");
    call_out("reset_room", 1);
}

public int
clean_up()
{
    if (kroug)
        return 1;

    remove_object();
}