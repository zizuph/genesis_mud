/*
 *  The temporary starting location of the elves 920523 /Tintin 
 */

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include <ss_types.h>

#define ALLOWED_RACES ({ "elf" })

create_room()
{
   set_short("On a small platform");
   set_long(break_string(
       "You are on a small platform " +
       "lodged between two enormous boughs in the crown of a tall tree " +
       "with silver leaves.\n" ,70));

   add_item(({"crown"}), break_string(
      "The crown of the tree has many silver leaves.\n", 70));
   add_item(({"tree","tall tree"}), break_string(
      "The tree supports a platform in its boughs.\n", 70));
   add_item(({"trunk"}), break_string(
      "The trunk of the tree has a wide girth.\n", 70));
   add_item(({"platform","small platform"}), break_string(
      "The platform is ten paces in square and looks like it could support " +
      "a great many people.\n", 70));

   add_item(({"bough","enormous bough","boughs","enormous boughs"}),
      break_string(
      "The boughs look as if nature created them for the purpose of " +
      "supporting a platform.\n", 70));

   add_item(({"leaf","leaves"}), break_string(
      "The leaves of this tree are matched nowhere in the world. " +
      "On a hot day they provide a cool shade and in the midst of winter " +
      "they keep the platform warm and cozy.\n",70));

   add_exit(STAND_DIR + "glade", "down", "@@go_down");
 
   add_prop(ROOM_I_INSIDE, 0);  /* This is an open air room */
}

init()
{
  ::init();
  if (this_player() &&
      member_array(this_player()->query_race(), ALLOWED_RACES) >= 0 &&
      this_player()->query_default_start_location()==file_name(this_object()))
    this_player()->set_default_start_location(STAND_DIR + "room/begin");
}

int
go_down()
{
    if (this_player()->query_race() == "elf")
	write("You nimbly climb down the trunk of the tree.\n");
    else
	if ((random(100) - 10) < this_player()->query_skill(SS_CLIMB))
	    /* We managed to climb safely */
	    write("You manage to safely climb down the tree trunk.\n");
	else
	{
	    /* Hit the player with the ground */
	    say(QCTNAME(this_player()) + "tries to climb down, but looses\n" +
		this_player()->query_possessive() +
		" grip and falls to the ground with a mighty crash.\n");
	    tell_room(STAND_DIR + "glade",
	        QCNAME(this_player()) + " tries to climb down from the tree, but looses\n" +
		this_player()->query_possessive() +
		      " grip and falls to the ground with a mighty crash.\n");
	    write("You loose your grip when trying to climb down and fall to\n" +
		  "the ground with a mighty crash.\n");
	    this_player()->reduce_hit_point(this_player()->query_stat(SS_CON) +
					    this_player()->query_prop(CONT_I_WEIGHT) / 100);
	}
    return 0;
}
