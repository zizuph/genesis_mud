inherit "/std/room.c";

#define BUNNY "/d/Dville/deinonychus/tmp/bunny"

/*
 * Function name: create_room()
 * Description  : Create the room.
 * Arguments:     none
 * Returns:       nothing
 */

void
create_room()
{
    set_short("Easter-bunnies hidden place.");
    set_long(break_string("You're in the Easter-bunnies hidden place. " +
	"If you're lucky you'll meet an Easter-bunny here.\n", 70));
    add_exit("/d/Dville/road/road1", "south", 0);
    call_out("reset_room", 1);
}

void
reset_room()
{
    setuid();
    seteuid(getuid(this_object()));
    (clone_object(BUNNY))->move(this_object());
    tell_room(this_object(), "Suddenly an Easter-bunny appears from nowhere.\n");
    call_out("reset_room", 300);
}
