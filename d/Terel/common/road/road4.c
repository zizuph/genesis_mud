inherit "/std/room.c";

create_room() {

    set_short("Road");
    set_long("This is a simple stony road that leads out across a\n" +
             "great moor. Patches of ice and snow are sprinkled out\n" +
             "upon the rocky grass. The sky is dreary, the wind cold.\n" +
	     "The road leads west and north.\n");
    add_exit("/d/Terel/common/road/road3", "north",0);
    add_exit("/d/Terel/common/road/road5", "west",0);
}

