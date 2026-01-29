inherit "/d/Shire/room";

#include "/d/Shire/common/defs.h"

create_room()
{
    set_short("Tom's garden");
    set_long(
	  "You are standing before Tom's Home. It is a beautiful cottage on "
	+ "the top of a hill in the eastern part of the old forest. You are "
	+ "standing between beautiful flowers that have a lovely scent. "
	+ "To the north is Tom's livingroom, where he likes to rest after a "
	+ "long day. The exit of the garden is west.\n");

    add_exit(BREE_DIR + "tom", "north");
    add_exit(DOWNS_DIR + "tomg1", "west");
}
