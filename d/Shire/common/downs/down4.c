inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"

#define QUEST_BARROW  "/d/Gondor/common/quest/nv/edown"

create_room() {
    set_short("a foggy place");
    set_long(break_string(
	  "You find yourself in a grey mess, fog everywhere. "
        + "You can barely see your own hands, these signs are "
        + "not good, not good at all...\n",70));

    add_item("fog",break_string(
	  "This fog has suddenly come upon you now the sunlight is fading. "
	+ "To the north you catch a glimpse of a dark shadow.\n",70));

    add_exit(DOWNS_DIR + "down3", "south", "@@south_noise");
    add_exit(DOWNS_DIR + "stone", "north", "@@north_noise");
    add_exit(DOWNS_DIR + "down4", "east",  "@@quest_test");
    add_exit(DOWNS_DIR + "down4", "west",  "@@make_noise");
}

south_noise() {
    write("You stumble to the south where the fog seems less dense.\n");
}

north_noise() {
    write("You climb up a steep hill and find the moist fog getting denser.\n");
}

make_noise() {
    write("You stumble around, trying to find a way out of the dense fog.\n");
}

quest_test()
{
  QUEST_BARROW->tele_tull_ball_just_to_load_the_room();
  if (QUEST_BARROW->quester_present()) make_noise();
  else {
    this_player()->catch_msg("You stumble off through the fog, and find a place where it gets less dense.\n");
    this_player()->move_living("into the fog",QUEST_BARROW,1,0);
    return 1;
    }
  return 0;
}

