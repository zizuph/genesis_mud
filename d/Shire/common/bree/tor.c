#include "defs.h"

inherit "/std/room";

create_room() {
    set_short("Tom's living room");
    set_long(break_string(
	  "This is Tom Bombadil's living room, this is "
	+ "where he rests and reads his ancient books. "
	+ "From here he keeps an eye on his forest. "
	+ "The place is perfectly clean.\n",70));

    add_exit(STAND_DIR + "tome", "south");

    reset_room();
}

reset_room() {
    if (!present("bombadil"))
        clone_object(STAND_PARENT + "monster/bombadil")->move(this_object());
        clone_object("/d/Shire/dondon/open/gem")->move(this_object());
}
