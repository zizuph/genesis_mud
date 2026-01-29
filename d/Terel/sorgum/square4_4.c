
/* square4_4.c */

/* metaprat - 920704 */

/* Town square, southeastern corner */

inherit "/std/room.c";

#include "/d/Terel/common/terel_defs.h"

create_room() {
   set_short("Calathin Town Square, Southeast corner");
   set_long(
      "You are on the southeast corner of a bustling town square.  A huge " +
      "pine tree is towering above you to the northwest.  Between you and " +
      "the tree, is a large stone monument.  To your west and southwest, "+
      "an inn and pub form an attraction for the locals.  Beyond those, a "+
      "couple of roads lead away from the square.  A playhouse is " +
   "northeast of you, and another building is north of that.  To " +
   "the east is a building under construction.\n");

   add_item( ({ "huge tree", "pine", "huge pine" }), break_string(
     "The tree looks like an ancient pine, about 100 meters tall or more. " +
     "It is towering above to the northwest.\n", 70) );

   add_item( ({ "buildings" }), break_string(
      "To the west, you see an inn and the pub.  To your northeast, a "+
      "playhouse, further north of which is another building.\n", 70));

   add_item( ({ "town square", "square" }),
      "The square is bustling with people... maybe it's market day here?\n");

   add_item( ({ "mist", "icy mist" }),
      "The mist is just the effect of the chill weather on the water vapor " +
      "in the air.\n");

   add_item( ({ "snow" }),
      break_string(
      "There is no snow here at all, it's all been trodden into oblivion. " +
      "There is a lot of snow on the trees in the forest, and also in the " +
      "landscape visible from here.\n", 70) );

   add_item( ({ "ground", "footprint", "footprints" }),
      break_string(
      "Deeply frozen all year round, the ground never holds footprints.\n",
      70) );

   add_item( ({ "monument", "statue" }),
      break_string(
      "It appears to be someone on a horse, modelled out of granite, and " +
      "facing east.  No other details are visible from this " +
      "distance.\n", 70) );

   add_exit(TOWNDIR + "square4_3", "north", 0);
   add_exit(TOWNDIR + "square3_4", "west", 0);
   add_exit(TOWNDIR + "post",      "east", 0);   
}
