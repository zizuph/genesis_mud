inherit "/std/room";

create_room() {

    set_short("Road");
    set_long("This road leads across a barren and rocky land, some of\n" +
             "which is coated with snow and ice. Mountains rise to the\n" +
             "west, the road winding its way slowly upwards. A silvery\n" +
	     "forest lies south of here. A gathering of stones can be\n" +
             "seen east of here.\n");
    add_exit("/d/Terel/common/road/cornerstone", "east",0);
    add_exit("/d/Terel/common/road/road7", "west",0);
}

