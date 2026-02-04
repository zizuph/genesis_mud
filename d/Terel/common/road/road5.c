// Modification log:
//   Lilith  Jan 2022 - updated the path on the north exit to the moors.

inherit "/std/room.c";

create_room() {

    set_short("Moor road ");
    set_long("This is a simple stony road that leads out across a " +
             "great moor. Patches of ice and snow are sprinkled " +
             "upon the rocky grass. The sky is dreary, the wind cold. " +
             "You can see signs of danger lurking everywhere, and you " +
             "wonder if you are strong enough to survive if you " +
             "were to adventure further north.\n" +
	         "There is a cornerstone to the west.\n");
    add_exit("/d/Terel/common/road/road4", "east",0);
    add_exit("/d/Terel/common/road/cornerstone", "west",0);
    add_exit("/d/Terel/common/moor/main/moor1", "north",0);
}

