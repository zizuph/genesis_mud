inherit "/std/room";

create_room() {

    set_short("Road");
    set_long("This road leads across a barren and rocky land, most of\n" +
             "which is coated with snow and ice here. Mountains rise to the\n" +
             "west, the road begins to disappear higher up. A forest of\n" +
	     "silvery pines lies south of here, but a deep ravine makes\n" +
             "that way impossible.\n");
    add_exit("/d/Terel/common/road/road6", "east",0);
    add_exit("/d/Terel/common/road/road8", "west",0);

   add_item("ravine", "It is very deep, with no way to cross it.\n");
}
