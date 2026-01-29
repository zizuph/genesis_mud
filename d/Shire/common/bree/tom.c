inherit "/d/Shire/room";

#include "/d/Shire/common/defs.h"

create_room() {
    set_short("Tom's living room");
    set_long(break_string(
	  "This is Tom Bombadil's living room, this is "
	+ "where he rests and reads his ancient books. "
	+ "From here he keeps an eye on his forest. "
	+ "The place is perfectly clean.\n",70));

/* item used for scavenger hunt, 2001
    clone_object("/d/Shire/scav_hunt/lilies")->move(this_object(), 1);
*/

    add_exit(BREE_DIR + "tome", "south");

    reset_room();
}

reset_room() {
    if (!present("bombadil"))
        clone_object(BREE_DIR + "npc/bombadil")->move(this_object());
}
