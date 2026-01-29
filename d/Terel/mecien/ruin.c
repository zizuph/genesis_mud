inherit "/std/room";
#include <macros.h>

create_room(){
set_short("Ancient Ruins");
set_long(
"All about you rise the pillars of some ancient place, dark and forboding," +
"grown over with strange moss and groves of evergreen. They appear almost as " +
"aged trees, preaching the words of some lost mystery, gone. Upon the stone " +
"laid upon the ground here, a silver star is traced, shining bright.\n");

add_item("pillars", "They are of some ancient dark stone.\n");
add_item("moss", "It is a beautiful black moss, very unusual.\n");
add_item("evergreen", "The grow all over, even from the stone " +
  "pillars, causing them to look like trees. They are bright green and seem to " +
"whisper in the wind, presenting a smell of life and freshness to this forsaken place.\n");
add_item("star", "It is a silver four-pointed star traced into the stone.\n");
}


