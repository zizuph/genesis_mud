inherit "/std/room";

create_room() {

    set_short("Road");
    set_long("This is the highlands, near the mountain steppes. A road\n" +
             "forms here and leads down across the snowy barren lands to\n" +
             "the east. Far east and south a forest can be seen, its snow\n" +
	     "laden top glistening like silver.\n");
    add_exit("/d/Terel/common/road/road7", "east",0);
    add_exit("/d/Terel/mountains/ice1","west",0);
}

